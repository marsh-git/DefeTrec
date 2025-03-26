#include "FloorManager.h"
#include "MapManager.h"
#include "SceneManager.h"
#include "../Scene/ResultScene.h"
#include "../GameObject/Character/Enemy/EnemySpawner.h"
#include "../GameObject/Character/Player/Player.h"


//�ÓI�����o�ϐ��̏�����
FloorManager* FloorManager::pInstance = nullptr;

//�R���X�g���N�^
FloorManager::FloorManager() 
	//: playerX(0)
	//, playerY(0) 
{
	// �����}�b�v��ݒ�
	Start();
}

//�V���O���g���̃C���X�^���X�쐬
void FloorManager::CreateInstance() {
	pInstance = new FloorManager();
}

//�쐬�����C���X�^���X�̎擾
FloorManager* FloorManager::GetInstance() {

	if (pInstance == nullptr) CreateInstance();

	return pInstance;
}

//�j��
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
	// �v���C���[�̎擾
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player->floorCount >= 1) {;
		ResultScene::gameClear = true;
		FadeManager::GetInstance()->FadeIn();
		SceneManager::GetInstance()->SetNext(SceneType::Result);
		return;
	}


	EnemySpawner* eSpn = EnemySpawner::GetInstance();
	// �V�����}�b�v�������_���ɐ���
	MapManager::generateRandomMap(MapRand, wallRatio, pathRatio, enemyRatio);
	eSpn->SpawnEnemy(MapRand); 

	//�v���C���[�̃t���A���X�V
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