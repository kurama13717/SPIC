#pragma once
#include<vector>
#include"Burret.h"



class BurretManager
{
public:
	BurretManager();
	~BurretManager();

	//XVˆ—
	void Update(float elapsedTime);

	//•`‰æˆ—
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//ƒfƒoƒbƒOƒvƒŠƒ~ƒeƒBƒu•`‰æ
	void DrawDebugPrimitive();

	// ’eŠÛ“o˜^
	void Register(Burret* burret);

	//’eŠÛ‘Síœ
	void Clear();

	//’eŠÛ”æ“¾
	int GetBurretCount() const { return static_cast<int>(burrets.size()); }

	//’eŠÛæ“¾
	Burret* GetBurret(int index) { return burrets.at(index); }

	//’eŠÛíœ
	void Remove(Burret* burret);

private:
	std::vector<Burret*> burrets;
	std::vector<Burret*> removes;
};