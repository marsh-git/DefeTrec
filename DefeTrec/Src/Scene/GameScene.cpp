#include "GameScene.h"
#include "../Definition.h"
#include "../Manager/InputManager.h"
#include "../Manager/MapManager.h"
#include "../Manager/CharacterManager.h"
#include "../Manager/FadeManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/FloorManager.h"
#include "../Manager/UIManager.h"
#include "../Src/GameObject/Character/Enemy/EnemySpawner.h"

GameScene::GameScene() {
	Start();
}

GameScene::~GameScene() {
	// ���\�[�X�̉����N���[���A�b�v�����������ɒǉ�
	delete player;
}

void GameScene::Start() {
	PlaySoundFile("Res/Bgm/GameScene.ogg", DX_PLAYTYPE_LOOP);
	//���f����摜�̓ǂݍ���

	//�e��C���X�^���X��
	// �}�b�v�����X�N���v�g�̏�����
	MapManager* mapManager = MapManager::GetInstance();

	// �t���A�}�l�[�W���[�̏�����
	FloorManager* floorMng = FloorManager::GetInstance();

	// �L�����N�^�[�}�l�[�W���[�̏�����
	CharacterManager* charMng = CharacterManager::GetInstance();

	// �v���C���[�̏����� X,Y,hp,�U����, �\��
	player = new Player(7 * TILE_SIZE, 7 * TILE_SIZE, 3, 1);
	pGameObjectArray.push_back(player);

}

void GameScene::Update() {
	if (player->hp <= 0 && InputManager::GetInstance()->IsKeyDown(KEY_INPUT_SPACE)) {
		FadeManager::GetInstance()->FadeIn();
		SceneManager::GetInstance()->SetNext(SceneType::Result);
	}

	//�͈�for��	�z���R���e�i�̗v�f�S�Ă��J��Ԃ�
	//for(1�̌^ �ʖ��F�z��A�R���e�i){ ���� }
	//auto�^ �^���_ -> �E�ӂ̒l����^������Ă����B
	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Update();
	}

	// �}�b�v�̍X�V
	MapManager::GetInstance()->Update();

	// �z��̗v�f�����ׂčX�V
	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Update();
	}

	// �v���C���[�̈ړ�
	player->Move(FloorManager::GetInstance()->MapRand);

	// �G�̍X�V
	for (Slime* enemy : CharacterManager::GetInstance()->enemies) {
		enemy->Update();
		enemy->Move(FloorManager::GetInstance()->MapRand);
	}
}

void GameScene::Render() {

	//LoadGraphScreen(960, 0, "Res/UI/UIBackGround.jpeg",FALSE);

	// �}�b�v�̕`��
	MapManager::GetInstance()->Render(FloorManager::GetInstance()->MapRand);

	// �z��̗v�f�����ׂĕ`��
	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Render();
	}

	// �G�L�����N�^�[�̕`��
	for (Slime* enemy : CharacterManager::GetInstance()->enemies) {
		enemy->Render();
	}

	UIManager::GetInstance()->Render();

}

void GameScene::ResetScene() {
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr)
		player->Reset();

	// �����̃Q�[���I�u�W�F�N�g���폜
	for (auto pObj : pGameObjectArray) {
		delete pObj;
	}
	pGameObjectArray.clear();

	// ���̕K�v�ȃR���|�[�l���g���ď�����
	EnemySpawner::GetInstance()->Reset();

	// �}�l�[�W���[�����Z�b�g
	CharacterManager::GetInstance()->Reset();
	FloorManager::GetInstance()->Reset();

	// �V�[�����ď�����
	Start();

}
