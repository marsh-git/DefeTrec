#include "EnemySpawner.h"
#include "../Src/Manager/FloorManager.h"

//�ÓI�����o�ϐ��̏�����
EnemySpawner* EnemySpawner::pInstance = nullptr;

//�R���X�g���N�^
EnemySpawner::EnemySpawner() : enemyNum(0) {

}

//�V���O���g���̃C���X�^���X�쐬
void EnemySpawner::CreateInstance() {
    pInstance = new EnemySpawner();
}

//�쐬�����C���X�^���X�̎擾
EnemySpawner* EnemySpawner::GetInstance() {

    if (pInstance == nullptr) CreateInstance();

    return pInstance;
}

//�j��
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
                _mapData[y][x] = 0; // �G���o�������ꏊ�𓹂ɕύX
                int startX = x * TILE_SIZE;
                int startY = y * TILE_SIZE;
                int hp = 3;
                int attackPower = 1;

                Slime* newEnemy = new Slime(startX, startY, hp, attackPower);
                characterManager->AddEnemy(newEnemy);
                enemyNum++; // �G�̃J�E���g�𑝂₷
            }
        }
    }
}

// �G��|�����Ƃ��ɃJ�E���g�����炷
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
