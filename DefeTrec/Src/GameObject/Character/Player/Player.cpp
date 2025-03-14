#include "Player.h"
#include "../Src/Definition.h"
#include "../Src/Manager/InputManager.h"
#include "../Src/Manager/MapManager.h"
#include "../Src/Manager/CharacterManager.h"
#include "../Src/Manager/FloorManager.h"
#include "../Src/Manager/AudioManager.h"

int pTilePosX;
int pTilePosY;
int moveCount = 0;

Player::Player(int startX, int startY, int Hp, int startAttackPower)
	: Character(startX, startY, Hp, startAttackPower) {
	CharacterManager::GetInstance()->SetPlayer(this);
	// 画像を読み込む
	LoadDivGraph("Res/Player/Swordsman_Idle.png", 7, 3, 3, 64, 64, pImage_Idle);
	LoadDivGraph("Res/Player/Swordsman_Walk.png", 11, 4, 3, 64, 64, pImage_Walk);
	LoadDivGraph("Res/Player/Swordsman_Atk.png", 9, 3, 3, 64, 64, pImage_Attack);
	LoadDivGraph("Res/Player/Swordsman_Hit.png", 5, 3, 2, 64, 64, pImage_Hit);

	//atkSE = LoadSoundMem("Res/Bgm/seAtk.ogg");
	AudioManager::GetInstance()->Load("Res/Bgm/seAtk.ogg", "AtkSE");
}

Player::~Player() {
	// 画像を解放する
	for (int i = 0; i < 7; i++) {
		DeleteGraph(pImage_Idle[i]);
	}
	for (int i = 0; i < 11; i++) {
		DeleteGraph(pImage_Walk[i]);
	}
	for (int i = 0; i < 9; i++) {
		DeleteGraph(pImage_Attack[i]);
	}
	for (int i = 0; i < 5; i++) {
		DeleteGraph(pImage_Hit[i]);
	}
}

void Player::Start() {
}

void Player::Update() {
	if (!isVisible)
		return;
	MovingAnim();
	Anim();
}

void Player::Render() {
	if (!isVisible)
		return;
	// 例: 四角形でキャラクターを描画
	// プレイヤーの画像を描画する
	switch (state) {
	case Character::IDLE:
		DrawGraph(x, y, pImage_Idle[currentFrame], TRUE);
		break;
	case Character::WALK:
		DrawGraph(x, y, pImage_Walk[currentFrame], TRUE);
		break;
	case Character::ATTACK:
		DrawGraph(x, y, pImage_Attack[currentFrame], TRUE);
		break;
	case Character::HIT:
		DrawGraph(x, y, pImage_Hit[currentFrame], TRUE);
		break;
	default:
		break;
	}
#if _DEBUG
	DrawBox(targetX, targetY, targetX + TILE_SIZE, targetY + TILE_SIZE, white, false);
#endif
}

void Player::Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) {
	if (!isVisible)
		return;

	FloorManager* floorMng = FloorManager::GetInstance();  // FloorManager のインスタンスを生成
	pTilePosX = targetX / TILE_SIZE;
	pTilePosY = targetY / TILE_SIZE;
	CharacterManager* charMng = CharacterManager::GetInstance();
	charMng->CharacterData[pTilePosY][pTilePosX] = 1;
	InputManager* input = InputManager::GetInstance();

	moveCount++;

	// WASDキーで移動
	if (moveCount >= 20 && state != WALK) {
		int newTilePosX = pTilePosX;
		int newTilePosY = pTilePosY;

		if (input->IsKeyDown(KEY_INPUT_W)) {
			newTilePosY -= 1;
		}
		else if (input->IsKeyDown(KEY_INPUT_S)) {
			newTilePosY += 1;
		}
		else if (input->IsKeyDown(KEY_INPUT_A)) {
			newTilePosX -= 1;
		}
		else if (input->IsKeyDown(KEY_INPUT_D)) {
			newTilePosX += 1;
		}
		else {
			return; // 移動キーが押されていない場合は何もしない
		}

		currentFrame = 0;
		moveCount = 0;

		if (newTilePosX >= 0 && newTilePosX < MAP_WIDTH && newTilePosY >= 0 && newTilePosY < MAP_HEIGHT) {
			if (_mapData[newTilePosY][newTilePosX] == 0) {
				Slime* enemy = charMng->GetEnemyAtPosition(newTilePosX, newTilePosY);
				if (enemy == nullptr) {
					charMng->CharacterData[pTilePosY][pTilePosX] = 0;
					targetX = newTilePosX * TILE_SIZE;
					targetY = newTilePosY * TILE_SIZE;
					state = WALK;
				}
				else {
					Attack(enemy);
					//攻撃時に音声を流す
					AudioManager::GetInstance()->PlayOneShot("AtkSE");
				}
			}
			else if (_mapData[newTilePosY][newTilePosX] == 8) {
				floorMng->NextFloor(0.15, 0.8, 0.05);  // 次の階層に移動
			}
		}
	}
}