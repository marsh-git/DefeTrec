#include "CharacterManager.h"
#include "EffectManager.h"

//�ÓI�����o�ϐ��̏�����
CharacterManager* CharacterManager::pInstance = nullptr;

//�R���X�g���N�^
CharacterManager::CharacterManager() 
	: player(nullptr){

}

//�V���O���g���̃C���X�^���X�쐬
void CharacterManager::CreateInstance() {
	pInstance = new CharacterManager();
}

//�쐬�����C���X�^���X�̎擾
CharacterManager* CharacterManager::GetInstance() {

	if (pInstance == nullptr) CreateInstance();

	return pInstance;
}

//�j��
void CharacterManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

//�G��z��ɒǉ�
void CharacterManager::AddEnemy(Slime* enemy) {
	enemies.push_back(enemy);
}

void CharacterManager::RemoveCharacter(Character* character) {
	EffectManager::GetInstance()->WhenDied(character->x, character->y);

	if (character == player) {
		player->isVisible = false;
		delete player;
	}
	else {
		enemies.erase(std::remove(enemies.begin(), enemies.end(), character), enemies.end());
		delete character; // �����������
	}
}

void CharacterManager::Reset() {
	// �L�����N�^�[�֘A�̃��\�[�X�����Z�b�g
	for (auto enemy : enemies) {
		delete enemy;
	}
	enemies.clear();
	player = nullptr;
}

std::pair<int, int> CharacterManager::GetPlayerPosition() {

	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			if (CharacterData[y][x] == 1) {
				return { x, y };
			}
		}
	}
	return { -1, -1 }; // �v���C���[��������Ȃ��ꍇ
}

Slime* CharacterManager::GetEnemyAtPosition(int tileX, int tileY) {
	for (Slime* enemy : enemies) {
		int eTilePosX = enemy->GetX() / TILE_SIZE;
		int eTilePosY = enemy->GetY() / TILE_SIZE;
		if (eTilePosX == tileX && eTilePosY == tileY) {
			return enemy;
		}
	}
	return nullptr;
}

void CharacterManager::SetPlayer(Player* player) {
	this->player = player;
}

Player* CharacterManager::GetPlayer() {
	return player;
}
