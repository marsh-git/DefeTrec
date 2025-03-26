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

Player::Player(int startX, int startY, int Hp, int startAttackPower, float startSpeed)
	: Character(startX, startY, Hp, startAttackPower, startSpeed)
	, exp(0)
	, level(1) {
	CharacterManager::GetInstance()->SetPlayer(this);
	// 画像を読み込む
	LoadDivGraph("Res/Player/Swordsman_Idle.png", 7, 3, 3, 64, 64, pImage_Idle);
	LoadDivGraph("Res/Player/Swordsman_Walk.png", 11, 4, 3, 64, 64, pImage_Walk);
	LoadDivGraph("Res/Player/Swordsman_Atk.png", 9, 3, 3, 64, 64, pImage_Attack);
	LoadDivGraph("Res/Player/Swordsman_Hit.png", 5, 3, 2, 64, 64, pImage_Hit);

	se = LoadSoundMem("Res/Bgm/seAtk.ogg");
	ChangeVolumeSoundMem(255 * 20 / 100, se);

	levelupSe = LoadSoundMem("Res/Bgm/levelUp.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, levelupSe);

	score = 0;
	floorCount = 0;
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


	if (floorCount == 0)
		floorCount = 1;
}

void Player::Render() {
	if (!isVisible) {
		return;
	}
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
	if (moveCount >= speed && state != WALK) {
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
					PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
				}
			}
			else if (_mapData[newTilePosY][newTilePosX] == 8) {
				floorMng->NextFloor(0.15, 0.8, 0.05);  // 次の階層に移動
			}
		}
	}
}

void Player::Reset() {
	score = 0;
	floorCount = 1;
}

void Player::AddScore(int _points) {
	score += _points;
	CheckLevel();
}

void Player::AddFloor() {
	floorCount++;
}

void Player::CheckLevel() {
	float scoreToNextLevel = level * 1.2f; // 次のレベルに必要なスコア
	if (score >= scoreToNextLevel) {
		score -= scoreToNextLevel;
		level++;
		LevelUp();
	}
}

void Player::LevelUp() {
	PlaySoundMem(levelupSe, DX_PLAYTYPE_BACK, TRUE);
	//maxHp += 1; // レベルアップ時に最大HPを増加
	//hp = maxHp; // HPを全回復
	attackPower += 1; // 攻撃力を増加
	//speed -= 0.5;
	// 他のステータスの向上もここに追加
}

void Player::Attack(Character* character) {
	if (character != nullptr) {
		state = ATTACK;
		character->TakeDamage(attackPower);
	}
}
