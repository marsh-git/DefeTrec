#include "CharacterManager.h"
#include "EffectManager.h"

//静的メンバ変数の初期化
CharacterManager* CharacterManager::pInstance = nullptr;

//コンストラクタ
CharacterManager::CharacterManager() 
	: player(nullptr){

}

//シングルトンのインスタンス作成
void CharacterManager::CreateInstance() {
	pInstance = new CharacterManager();
}

//作成したインスタンスの取得
CharacterManager* CharacterManager::GetInstance() {

	if (pInstance == nullptr) CreateInstance();

	return pInstance;
}

//破壊
void CharacterManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

//敵を配列に追加
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
		delete character; // メモリを解放
	}
}

void CharacterManager::Reset() {
	// キャラクター関連のリソースをリセット
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
	return { -1, -1 }; // プレイヤーが見つからない場合
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
