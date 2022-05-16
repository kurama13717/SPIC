#include "Graphics/Graphics.h"
#include "Graphics/Model.h"
#include "Input/Input.h"
#include "Player.h"
#include "ResourceManager.h"
// コンストラクタ
Model::Model(const char* filename)
{
	// リソース読み込み
	//resource = std::make_shared<ModelResource>();
	//resource->Load(Graphics::Instance().GetDevice(), filename);
	resource = ResourceManager::Instance().LoadModelResource(filename);
	// ノード
	const std::vector<ModelResource::Node>& resNodes = resource->GetNodes();

	nodes.resize(resNodes.size());
	for (size_t nodeIndex = 0; nodeIndex < nodes.size(); ++nodeIndex)
	{
		auto&& src = resNodes.at(nodeIndex);
		auto&& dst = nodes.at(nodeIndex);

		dst.name = src.name.c_str();
		dst.parent = src.parentIndex >= 0 ? &nodes.at(src.parentIndex) : nullptr;
		dst.scale = src.scale;
		dst.rotate = src.rotate;
		dst.translate = src.translate;

		if (dst.parent != nullptr)
		{
			dst.parent->children.emplace_back(&dst);
		}
	}

	// 行列計算
	const DirectX::XMFLOAT4X4 transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	UpdateTransform(transform);
}

// 変換行列計算
void Model::UpdateTransform(const DirectX::XMFLOAT4X4& transform)
{
	DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);

	for (Node& node : nodes)
	{
		// ローカル行列算出
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(node.scale.x, node.scale.y, node.scale.z);
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&node.rotate));
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(node.translate.x, node.translate.y, node.translate.z);
		DirectX::XMMATRIX LocalTransform = S * R * T;

		// ワールド行列算出
		DirectX::XMMATRIX ParentTransform;
		if (node.parent != nullptr)
		{
			ParentTransform = DirectX::XMLoadFloat4x4(&node.parent->worldTransform);
		}
		else
		{
			ParentTransform = Transform;
		}
		DirectX::XMMATRIX WorldTransform = LocalTransform * ParentTransform;

		// 計算結果を格納
		DirectX::XMStoreFloat4x4(&node.localTransform, LocalTransform);
		DirectX::XMStoreFloat4x4(&node.worldTransform, WorldTransform);
	}
}

//アニメーション更新処理
void Model::UpdateAnimation(float elapsedTime)
{
	//GamePad& gamePad = Input::Instance().GetGamePad();
	//if (gamePad.GetButtonDown() & GamePad::BTN_B)
	//{
	//	PlayAnimation(Animation::Anim_Attack, false, 0.1f);
	//}
	//if (!IsPlayAnimation())
	//{
	//	PlayAnimation(Animation::Anim_Idle, true);
	//}
	//再生中では無ければ更新しない
	if (!IsPlayAnimation())return;

	// ブレンド率の計算
	float blendRate = 1.0f;
	if (animationBlendTime < animationBlendSeconds)
	{
		animationBlendTime += elapsedTime;
		if (animationBlendTime >= animationBlendSeconds)
		{
			animationBlendTime = animationBlendSeconds;
		}
		blendRate = animationBlendTime / animationBlendSeconds;
		blendRate *= blendRate;
	}
	
	//指定のアニメーションデータを取得
	const std::vector<ModelResource::Animation>& animations = resource->GetAnimations();
	const ModelResource::Animation& animation = animations.at(currentAnimationIndex);

	//アニメーションデータからキーフレームデータリストを取得
	const std::vector<ModelResource::Keyframe>& keyframes = animation.keyframes;
	int keyCount = static_cast<int>(keyframes.size());
	for (int keyIndex = 0; keyIndex < keyCount - 1; ++keyIndex)
	{
		//キーフレーム0と次のインデックスキーフレーム1との間を計算して取り出す
		const ModelResource::Keyframe& keyframe0 = keyframes.at(keyIndex);
		const ModelResource::Keyframe& keyframe1 = keyframes.at(keyIndex + 1);
		//キーフレーム0とキーフレーム1の間なら
		if (currentAnimationSeconds >= keyframe0.seconds
			&& currentAnimationSeconds < keyframe1.seconds)
		{
			// 再生時間とキーフレームの時間から補完率を算出する
			float rate = (currentAnimationSeconds - keyframe0.seconds) / (keyframe1.seconds - keyframe0.seconds);
			int nodeCount = static_cast<int>(nodes.size());
			for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
			{
				const ModelResource::NodeKeyData& key0 = keyframe0.nodeKeys.at(nodeIndex);
				const ModelResource::NodeKeyData& key1 = keyframe1.nodeKeys.at(nodeIndex);

				Node& node = nodes[nodeIndex];
				//DirectX::XMVECTOR S0 = DirectX::XMLoadFloat3(&key0.scale);
				//DirectX::XMVECTOR S1 = DirectX::XMLoadFloat3(&key1.scale);
				//DirectX::XMVECTOR R0 = DirectX::XMLoadFloat4(&key0.rotate);
				//DirectX::XMVECTOR R1 = DirectX::XMLoadFloat4(&key1.rotate);
				//DirectX::XMVECTOR T0 = DirectX::XMLoadFloat3(&key0.translate);
				//DirectX::XMVECTOR T1 = DirectX::XMLoadFloat3(&key1.translate);
				//DirectX::XMVECTOR S = DirectX::XMVectorLerp(S0, S1, rate);
				//DirectX::XMVECTOR R = DirectX::XMQuaternionSlerp(R0, R1, rate);

				//DirectX::XMVECTOR T = DirectX::XMVectorLerp(T0, T1, rate);
				//// 計算結果をボーンに格納
				//DirectX::XMStoreFloat3(&node.scale, S);
				//DirectX::XMStoreFloat4(&node.rotate, R);
				//DirectX::XMStoreFloat3(&node.translate, T);
				DirectX::XMVECTOR S = {0,0,0};
				DirectX::XMVECTOR R = {0,0,0};
				DirectX::XMVECTOR T = {0,0,0};
				// ブレンド補完処理
				if (blendRate < 1.0f)
				{
					DirectX::XMVECTOR S0 = DirectX::XMLoadFloat3(&node.scale);
					DirectX::XMVECTOR S1 = DirectX::XMLoadFloat3(&key1.scale);
					DirectX::XMVECTOR R0 = DirectX::XMLoadFloat4(&node.rotate);
					DirectX::XMVECTOR R1 = DirectX::XMLoadFloat4(&key1.rotate);
					DirectX::XMVECTOR T0 = DirectX::XMLoadFloat3(&node.translate);
					DirectX::XMVECTOR T1 = DirectX::XMLoadFloat3(&key1.translate);
					DirectX::XMVECTOR S = DirectX::XMVectorLerp(S0, S1, blendRate);
					DirectX::XMVECTOR R = DirectX::XMQuaternionSlerp(R0, R1, blendRate);
					DirectX::XMVECTOR T = DirectX::XMVectorLerp(T0, T1, blendRate);
					// 計算結果をボーンに格納
					DirectX::XMStoreFloat3(&node.scale, S);
					DirectX::XMStoreFloat4(&node.rotate, R);
					DirectX::XMStoreFloat3(&node.translate, T);
				}
				// 通常の計算
				else
				{
					// 前のキーフレームと次のキーフレームの姿勢を補完
					DirectX::XMVECTOR S0 = DirectX::XMLoadFloat3(&key0.scale);
					DirectX::XMVECTOR S1 = DirectX::XMLoadFloat3(&key1.scale);
					DirectX::XMVECTOR R0 = DirectX::XMLoadFloat4(&key0.rotate);
					DirectX::XMVECTOR R1 = DirectX::XMLoadFloat4(&key1.rotate);
					DirectX::XMVECTOR T0 = DirectX::XMLoadFloat3(&key0.translate);
					DirectX::XMVECTOR T1 = DirectX::XMLoadFloat3(&key1.translate);
					DirectX::XMVECTOR S = DirectX::XMVectorLerp(S0, S1, rate);
					DirectX::XMVECTOR R = DirectX::XMQuaternionSlerp(R0, R1, rate);
					DirectX::XMVECTOR T = DirectX::XMVectorLerp(T0, T1, rate);
					// 計算結果をボーンに格納
					DirectX::XMStoreFloat3(&node.scale, S);
					DirectX::XMStoreFloat4(&node.rotate, R);
					DirectX::XMStoreFloat3(&node.translate, T);
				}
			}
			break;
		}
	}

	//最終フレームの処理
	if (animationEndFlag)
	{
		animationEndFlag = false;
		currentAnimationIndex = -1;
		return;
	}
	currentAnimationSeconds += elapsedTime;

	//再生時間が終端時間を超えたら
	if (currentAnimationSeconds >= animation.secondsLength)
	{
		// 再生時間を巻き戻す
		currentAnimationSeconds -= animation.secondsLength;
		if (!animationLoopFlag)
		{
			currentAnimationSeconds = animation.secondsLength;
			animationEndFlag = true;
		}
		// 再生終了時間にする

	}
}
//アニメーション再生
void Model:: PlayAnimation(int index,bool loop,float blendSeconds)
{
	currentAnimationIndex = index;
	currentAnimationSeconds = 0.0f;
	animationBlendTime = 0.0f;
	animationBlendSeconds = blendSeconds;
	animationLoopFlag = loop;
	animationEndFlag = false;
}
//アニメーション再生中か
bool Model::IsPlayAnimation()const 
{
	if (currentAnimationIndex < 0)return false;
	if (currentAnimationIndex >= resource->GetAnimations().size())return false;
	return true;
}

Model::Node* Model::FindNode(const char* name)
{
	// 全てのノードを総当たりで名前比較する
	for (Node& node : nodes)
	{
		if (::strcmp(node.name, name) == 0)
		{
			return &node;
		}
	}
	// 見つからなかった
	return nullptr;
}


