#include "Collision.h"

//bool Collision::IntersectSphereVsSphere(
//    const DirectX::XMFLOAT3& positionA,
//    float radiusA,
//    const DirectX::XMFLOAT3& positionB,
//    float radiusB,
//    DirectX::XMFLOAT3& outPositionB
//)
//{
//    //BからA方向のベクトル
//    DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
//    DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
//    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);//B-Aベクトル
//    DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);//ベクトルの大きさの2乗
//    float lengthSq;
//    DirectX::XMStoreFloat(&lengthSq, LengthSq);
//
//    //距離判定
//    float range = radiusA + radiusB;
//    if (lengthSq > range  * range)
//    {
//        return false;
//    }
//    Vec = DirectX::XMVector3Normalize(Vec);//単位ベクトル化
//    Vec = DirectX::XMVectorScale(Vec,range);//ベクトルに大きさを＊
//    PositionB = DirectX::XMVectorAdd(PositionA, Vec);//押し出す
//    DirectX::XMStoreFloat3(&outPositionB, PositionB);
//    return true;
//}
bool Collision::IntersectCylinderVsCylinder(
    const DirectX::XMFLOAT3& positionA,
    float radiusA,
    float heightA,
    const DirectX::XMFLOAT3& positionB,
    float radiusB,
    float heightB,
    DirectX::XMFLOAT3& outPositionB
)
{
    // Aの足元がBの頭より上なら当たっていない
    if (positionA.y > positionB.y + heightB)
    {
        return false;
    }
    // Aの頭がBの足元より下なら当たっていない
    if (positionA.y + heightA < positionB.y)
    {
        return false;
    }
    // XZ平面での範囲チェック
    float vx = positionB.x - positionA.x;
    float vz = positionB.z - positionA.z;
    float range = radiusA + radiusB;
    float distXZ = sqrtf(vx * vx + vz * vz);
    if (distXZ > range)
    {
        return false;
    }
    // AがBを押し出す
    vx /= distXZ;
    vz /= distXZ;
    outPositionB.x = positionA.x + (vx * range);
    outPositionB.y = positionB.y;
    outPositionB.z = positionA.z + (vz * range);
    return true;
}

//球と円柱
bool Collision::IntersectSphereVsCylinder(
    const DirectX::XMFLOAT3& spherePosition,
    float sphereRadius,
    const DirectX::XMFLOAT3& cylinderPosition,
    float cylinderRadius,
    float cylinderHeight,
    DirectX::XMFLOAT3& outCylinderPosition
)
{
    //Y軸の判定
    if (spherePosition.y > cylinderPosition.y + cylinderHeight)
    {
        return false;
    }
    if (spherePosition.y + sphereRadius < cylinderPosition.y)
    {
        return false;
    }
    // XZ平面での範囲チェック
    float vx = cylinderPosition.x - spherePosition.x;
    float vz = cylinderPosition.z - spherePosition.z;
    float range = sphereRadius + cylinderRadius;
    float distXZ = sqrtf(vx * vx + vz * vz);
    if (distXZ > range)
    {
        return false;
    }
    vx /= distXZ;
    vz /= distXZ;
    outCylinderPosition.x = spherePosition.x + (vx * range);
    outCylinderPosition.y = cylinderPosition.y;
    outCylinderPosition.z = spherePosition.z + (vz * range);
    return true;
}

//レイとモデルの交差判定
bool Collision::IntersectRayVsModel(
    const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, 
    const Model* model, HitResult& result)
{
    //using namespace DirectX;
    //XMVECTOR WorldStart = DirectX::XMLoadFloat3(&start);
    //XMVECTOR WorldEnd = DirectX::XMLoadFloat3(&end);
    //XMVECTOR WorldRayVec = XMVectorSubtract(WorldEnd, WorldStart);
    //XMVECTOR WorldRayLength = XMVector3Length(WorldRayVec);

    ////ワールド空間の例の長さ
    //XMStoreFloat(&result.distance, WorldRayLength);
    //bool hit = false;
    //const ModelResource* resource = model->GetResource();
    //for (const ModelResource::Mesh& mesh : resource->GetMeshes())
    //{
    //    const Model::Node& node = model->GetNodes().at(mesh.nodeIndex);

    //    //レイをワールド空間からローカル空間へ変換
    //    XMMATRIX WorldTransform = DirectX::XMLoadFloat4x4(&node.worldTransform);
    //    XMMATRIX InverseWorldTransform = XMMatrixInverse(nullptr, WorldTransform);

    //    XMVECTOR Start = XMVector3TransformCoord(WorldStart, InverseWorldTransform);
    //    XMVECTOR End = XMVector3TransformCoord(WorldEnd, InverseWorldTransform);
    //    XMVECTOR Vec = XMVectorSubtract(End, Start);
    //    XMVECTOR Dir = XMVector3Normalize(Vec);
    //    XMVECTOR Length = XMVector3Length(Vec);

    //    //レイの長さ
    //    float neart;
    //    XMStoreFloat(&neart, Length);

    //    //三角刑(面)との交差判定
    //    const std::vector<ModelResource::Vertex>& vertices = mesh.vertices;
    //    const std::vector<UINT>indices = mesh.indices;

    //    int materialIndex = -1;
    //    XMVECTOR HitPosition;
    //    XMVECTOR HitNormal;
    //    for (const ModelResource::Subset& subset : mesh.subsets)
    //    {
    //        for (UINT i = 0; i < subset.indexCount; i += 3)
    //        {
    //            UINT index = subset.startIndex + i;
    //            //➀三角形の頂点を抽出
    //            const ModelResource::Vertex& a = vertices.at(indices.at(index));
    //            const ModelResource::Vertex& b = vertices.at(indices.at(index + 1));
    //            const ModelResource::Vertex& c = vertices.at(indices.at(index + 2));

    //            XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
    //            XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
    //            XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

    //            //②三角形の3辺のベクトルを算出
    //            XMVECTOR AB = XMVectorSubtract(B, A);
    //            XMVECTOR BC = XMVectorSubtract(C, B);
    //            XMVECTOR CA = XMVectorSubtract(A, C);

    //            //③三角形の法線ベクトルを算出
    //            XMVECTOR Normal = XMVector3Cross(AB, BC);

    //            //④内積の結果で表裏判定
    //            XMVECTOR Dot = XMVector3Dot(Vec, Normal);
    //            float dot;
    //            DirectX::XMStoreFloat(&dot, Dot);
    //            if (dot >= 0)continue;

    //            //⑤レイと平面の交点を算出
    //            XMVECTOR V = XMVectorSubtract(A, Start);
    //            XMVECTOR T = XMVectorDivide(XMVector3Dot(Normal, V), Dot);
    //            float t;
    //            DirectX::XMStoreFloat(&t, T);
    //            //レイの交点が0以下か交点がレイの長さより長すぎたらスキップ
    //            if (t < 0.0f || t > neart)continue;
    //            
    //            //交点の位置(ベクトル)
    //            XMVECTOR Position = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(Dir, T),Start);

    //            //⑥交点が三角形の内側にあるか判定
    //            //1つ目
    //            XMVECTOR AP = DirectX::XMVectorSubtract(A, Position);
    //            XMVECTOR Cross1 = DirectX::XMVector3Cross(AP, AB);
    //            XMVECTOR Dot1 = DirectX::XMVector3Dot(Cross1, Normal);
    //            float dot1;
    //            DirectX::XMStoreFloat(&dot1, Dot1);
    //            if (dot1 < 0.0f) continue;
    //            //2つ目
    //            XMVECTOR BP = DirectX::XMVectorSubtract(B, Position);
    //            XMVECTOR Cross2 = DirectX::XMVector3Cross(BP, BC);
    //            XMVECTOR Dot2 = DirectX::XMVector3Dot(Cross2, Normal);
    //            float dot2;
    //            DirectX::XMStoreFloat(&dot2, Dot2);
    //            if (dot2 < 0.0f) continue;
    //            //3つ目
    //            XMVECTOR CP = DirectX::XMVectorSubtract(C, Position);
    //            XMVECTOR Cross3 = DirectX::XMVector3Cross(CP, CA);
    //            XMVECTOR Dot3 = DirectX::XMVector3Dot(Cross3, Normal);
    //            float dot3;
    //            DirectX::XMStoreFloat(&dot3, Dot3);
    //            if (dot3 < 0.0f) continue;

    //            //最近距離を更新
    //            neart = t;

    //            //交点と法線を更新
    //            //交点座標
    //            HitPosition = Position;
    //            //面法線ベクトル
    //            HitNormal = Normal;
    //            materialIndex = subset.materialIndex;
    //        }
    //    }
    //    if (materialIndex >= 0)
    //    {
    //        //ローカル空間からワールド空間へ変換
    //        XMVECTOR WorldPosition = DirectX::XMVector3TransformCoord(HitPosition, WorldTransform);
    //        XMVECTOR WorldCrossVec = DirectX::XMVectorSubtract(WorldPosition, WorldStart);
    //        XMVECTOR WorldCrossLength = DirectX::XMVector3Length(WorldCrossVec);
    //        float distance;
    //        DirectX::XMStoreFloat(&distance, WorldCrossLength);

    //        //ヒット情報保存
    //        if (result.distance > distance)
    //        {
    //            XMVECTOR WorldNormal = DirectX::XMVector3TransformNormal(HitNormal, WorldTransform);

    //            result.distance = distance;
    //            result.materialIndex = materialIndex;
    //            DirectX::XMStoreFloat3(&result.position, WorldPosition);
    //            DirectX::XMStoreFloat3(&result.normal, DirectX::XMVector3Normalize(WorldNormal));
    //            hit = true;
    //        }
    //    }
    //}
    //return hit;
DirectX::XMVECTOR WorldStart = DirectX::XMLoadFloat3(&start);
DirectX::XMVECTOR WorldEnd = DirectX::XMLoadFloat3(&end);
DirectX::XMVECTOR WorldRayVec = DirectX::XMVectorSubtract(WorldEnd, WorldStart);
DirectX::XMVECTOR WorldRayLength = DirectX::XMVector3Length(WorldRayVec);
// ワールド空間のレイの長さ
DirectX::XMStoreFloat(&result.distance, WorldRayLength);
bool hit = false;
const ModelResource* resource = model->GetResource();
for (const ModelResource::Mesh& mesh : resource->GetMeshes())
{
    // メッシュノード取得
    const Model::Node& node = model->GetNodes().at(mesh.nodeIndex);
    // レイをワールド空間からローカル空間へ変換
    DirectX::XMMATRIX WorldTransform = DirectX::XMLoadFloat4x4(&node.worldTransform);
    //メッシュの行列を逆行列
    DirectX::XMMATRIX InverseWorldTransform = DirectX::XMMatrixInverse(nullptr, WorldTransform);
    DirectX::XMVECTOR Start = DirectX::XMVector3TransformCoord(WorldStart, InverseWorldTransform);
    DirectX::XMVECTOR End = DirectX::XMVector3TransformCoord(WorldEnd, InverseWorldTransform);
    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(End, Start);
    DirectX::XMVECTOR Dir = DirectX::XMVector3Normalize(Vec);
    DirectX::XMVECTOR Length = DirectX::XMVector3Length(Vec);
    // レイの長さ
    float neart;
    DirectX::XMStoreFloat(&neart, Length);
    // 三角形(面)との交差判定
    const std::vector<ModelResource::Vertex>& vertices = mesh.vertices;
    const std::vector<UINT> indices = mesh.indices;
    int materialIndex = -1;
    DirectX::XMVECTOR HitPosition;
    DirectX::XMVECTOR HitNormal;
    for (const ModelResource::Subset& subset : mesh.subsets)
    {
        for (UINT i = 0; i < subset.indexCount; i += 3)
        {
            UINT index = subset.startIndex + i;

                // 三角形の頂点を抽出
            const ModelResource::Vertex & a = vertices.at(indices.at(index));
            const ModelResource::Vertex& b = vertices.at(indices.at(index + 1));
            const ModelResource::Vertex& c = vertices.at(indices.at(index + 2));
            DirectX::XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
            DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
            DirectX::XMVECTOR C = DirectX::XMLoadFloat3(&c.position);
            // 三角形の三辺ベクトルを算出
            DirectX::XMVECTOR AB = DirectX::XMVectorSubtract(B, A);
            DirectX::XMVECTOR BC = DirectX::XMVectorSubtract(C, B);
            DirectX::XMVECTOR CA = DirectX::XMVectorSubtract(A, C);
            // 三角形の法線ベクトルを算出
            DirectX::XMVECTOR Normal = DirectX::XMVector3Cross(AB, BC);
            // 内積の結果がプラスならば裏向き
            DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(Dir, Normal);
            float dot;
            DirectX::XMStoreFloat(&dot, Dot);
            if (dot >= 0) continue;
            // レイと平面の交点を算出
            DirectX::XMVECTOR V = DirectX::XMVectorSubtract(A, Start);
            //d2/d1
            DirectX::XMVECTOR T = DirectX::XMVectorDivide(DirectX::XMVector3Dot(Normal, V), Dot);
            float t;
            DirectX::XMStoreFloat(&t, T);
            if (t < 0.0f || t > neart) continue; // 交点までの距離が今までに計算した最近距離より

            // 大きい時はスキップ
            DirectX::XMVECTOR Position = DirectX::XMVectorAdd(DirectX::XMVectorMultiply(Dir, T),
                Start);

            // 交点が三角形の内側にあるか判定
            // 1つめ
            DirectX::XMVECTOR AP = DirectX::XMVectorSubtract(A, Position);
            DirectX::XMVECTOR Cross1 = DirectX::XMVector3Cross(AP, AB);
            DirectX::XMVECTOR Dot1 = DirectX::XMVector3Dot(Cross1, Normal);
            float dot1;
            DirectX::XMStoreFloat(&dot1, Dot1);
            if (dot1 < 0.0f) continue;
            // 2つめ
            DirectX::XMVECTOR BP = DirectX::XMVectorSubtract(B, Position);
            DirectX::XMVECTOR Cross2 = DirectX::XMVector3Cross(BP, BC);
            DirectX::XMVECTOR Dot2 = DirectX::XMVector3Dot(Cross2, Normal);
            float dot2;
            DirectX::XMStoreFloat(&dot2, Dot2);
            if (dot2 < 0.0f) continue;
            // 3つめ
            DirectX::XMVECTOR CP = DirectX::XMVectorSubtract(C, Position);
            DirectX::XMVECTOR Cross3 = DirectX::XMVector3Cross(CP, CA);
            DirectX::XMVECTOR Dot3 = DirectX::XMVector3Dot(Cross3, Normal);
            float dot3;
            DirectX::XMStoreFloat(&dot3, Dot3);
            if (dot3 < 0.0f) continue;
            // 最近距離を更新
                neart = t;
            // 交点と法線を更新
            HitPosition = Position;
            HitNormal = Normal;
            materialIndex = subset.materialIndex;
        }
    }
    if (materialIndex >= 0)
    {
        // ローカル空間からワールド空間へ変換
        DirectX::XMVECTOR WorldPosition = DirectX::XMVector3TransformCoord(HitPosition,
            WorldTransform);
        DirectX::XMVECTOR WorldCrossVec = DirectX::XMVectorSubtract(WorldPosition, WorldStart);
        DirectX::XMVECTOR WorldCrossLength = DirectX::XMVector3Length(WorldCrossVec);
        float distance;
        DirectX::XMStoreFloat(&distance, WorldCrossLength);
        // ヒット情報保存//あたった位置,法線などがとれる
        if (result.distance > distance)
        {
            DirectX::XMVECTOR WorldNormal = DirectX::XMVector3TransformNormal(HitNormal,
                WorldTransform);

            result.distance = distance;
            result.materialIndex = materialIndex;
            DirectX::XMStoreFloat3(&result.position, WorldPosition);
            DirectX::XMStoreFloat3(&result.normal, DirectX::XMVector3Normalize(WorldNormal));
            hit = true;
        }
    }
}
return hit;
}
