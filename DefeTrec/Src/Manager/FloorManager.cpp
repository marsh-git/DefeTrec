#include "FloorManager.h"
#include "MapManager.h"
#include "../GameObject/Character/Enemy/EnemySpawner.h"

//静的メンバ変数の初期化
FloorManager* FloorManager::pInstance = nullptr;

//コンストラクタ
FloorManager::FloorManager() 
	//: playerX(0)
	//, playerY(0) 
{
	// 初期マップを設定
	FloorManager::NextFloor(0.15, 0.8, 0.05);
	//MapManager::generateRandomMap(MapRand, 0.15, 0.8, 0.05);
}

//シングルトンのインスタンス作成
void FloorManager::CreateInstance() {
	pInstance = new FloorManager();
}

//作成したインスタンスの取得
FloorManager* FloorManager::GetInstance() {

	if (pInstance == nullptr) CreateInstance();

	return pInstance;
}

//破壊
void FloorManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}


void FloorManager::NextFloor(double wallRatio, double pathRatio, double enemyRatio) {
	EnemySpawner* eSpn = EnemySpawner::GetInstance();
	// 新しいマップをランダムに生成
	MapManager::generateRandomMap(MapRand, wallRatio, pathRatio, enemyRatio);
	eSpn->SpawnEnemy(MapRand); 
}

void FloorManager::Reset() {
	NextFloor(0.15, 0.8, 0.05);
}

int(*FloorManager::GetMapData())[MAP_WIDTH] {
	return MapRand;
}