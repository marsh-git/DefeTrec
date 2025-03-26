#include "FloorManager.h"
#include "MapManager.h"
#include "SceneManager.h"
#include "../Scene/ResultScene.h"
#include "../GameObject/Character/Enemy/EnemySpawner.h"
#include "../GameObject/Character/Player/Player.h"


//静的メンバ変数の初期化
FloorManager* FloorManager::pInstance = nullptr;

//コンストラクタ
FloorManager::FloorManager() 
	//: playerX(0)
	//, playerY(0) 
{
	// 初期マップを設定
	Start();
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


void FloorManager::Start() {
	FloorManager::NextFloor(0.15, 0.8, 0.05);
}

void FloorManager::NextFloor(double wallRatio, double pathRatio, double enemyRatio) {
	// プレイヤーの取得
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player->floorCount >= 1) {;
		ResultScene::gameClear = true;
		FadeManager::GetInstance()->FadeIn();
		SceneManager::GetInstance()->SetNext(SceneType::Result);
		return;
	}


	EnemySpawner* eSpn = EnemySpawner::GetInstance();
	// 新しいマップをランダムに生成
	MapManager::generateRandomMap(MapRand, wallRatio, pathRatio, enemyRatio);
	eSpn->SpawnEnemy(MapRand); 

	//プレイヤーのフロアを更新
	if (player != nullptr) {
		player->AddFloor();
	}
}

void FloorManager::Reset() {
	NextFloor(0.15, 0.8, 0.05);
}

int(*FloorManager::GetMapData())[MAP_WIDTH] {
	return MapRand;
}