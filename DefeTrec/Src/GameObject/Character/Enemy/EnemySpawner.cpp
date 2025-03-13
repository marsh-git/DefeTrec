#include "EnemySpawner.h"
#include "../Src/Manager/FloorManager.h"

//静的メンバ変数の初期化
EnemySpawner* EnemySpawner::pInstance = nullptr;

//コンストラクタ
EnemySpawner::EnemySpawner() : enemyNum(0) {

}

//シングルトンのインスタンス作成
void EnemySpawner::CreateInstance() {
    pInstance = new EnemySpawner();
}

//作成したインスタンスの取得
EnemySpawner* EnemySpawner::GetInstance() {

    if (pInstance == nullptr) CreateInstance();

    return pInstance;
}

//破壊
void EnemySpawner::DestroyInstance() {
    if (pInstance != nullptr) {
        delete pInstance;
        pInstance = nullptr;
    }
}

void EnemySpawner::SpawnEnemy(int _mapData[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (_mapData[y][x] == 2) {
                _mapData[y][x] = 0; // 敵が出現した場所を道に変更
                int startX = x * TILE_SIZE;
                int startY = y * TILE_SIZE;
                int hp = 3;
                int attackPower = 1;

                Slime* newEnemy = new Slime(startX, startY, hp, attackPower);
                characterManager->AddEnemy(newEnemy);
                enemyNum++; // 敵のカウントを増やす
            }
        }
    }
}

// 敵を倒したときにカウントを減らす
void EnemySpawner::EnemyDefeated() {
    if (enemyNum > 0) {
        enemyNum--;
    }

    if (enemyNum == 0) {
        FloorManager* floorManager = FloorManager::GetInstance();
        int (*mapData)[MAP_WIDTH] = floorManager->GetMapData();
        mapManager->GeneratePortal(mapData);
    }
}
