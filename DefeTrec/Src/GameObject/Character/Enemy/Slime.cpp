#include "Slime.h"
#include "../Src/Definition.h"
#include "../Src/Manager/MapManager.h"
#include "../Src/Manager/CharacterManager.h"
#include "../Src/Pathfinding/AStar.h"
#include "../Player/Player.h"
#include "EnemySpawner.h"
#include <DxLib.h>

//A*アルゴリズムを使用するため
AStar pathfinder;

Slime::Slime(int startX, int startY, int Hp, int startAttackPower)
	: Character(startX, startY, Hp, startAttackPower)
	, count(0) {
	Start();
}

Slime::~Slime() {
	for (int i = 0; i < 21; i++) {
		DeleteGraph(Slime_png[i]);
	}
}

void Slime::Start() {
	LoadDivGraph("Res/Enemy/slime.png", 21, 8, 3, 64, 64, Slime_png);
	frameDelay = 10;
	state = IDLE_LEFT;
	speed = 4.0f;
}

void Slime::Update() {
	//不可視なら処理を飛ばす
	if (!isVisible) {
		return;
	}
	//移動時のアニメーション
	MovingAnim();
	//アニメーション
	Anim();
}

	// 描画
void Slime::Render() {
	if (!isVisible)
		return;
	//書き終わった後に気づいたくそコード
	//if(プレイヤーの位置が左なら)DrawGraph
	//if(プレイヤーの位置が右なら)DrawTurnGraph	でよかった
	switch (state) {
	case Character::IDLE_LEFT:
		DrawGraph(x, y, Slime_png[currentFrame], TRUE);
		break;
	case Character::IDLE_RIGHT:
		DrawTurnGraph(x, y, Slime_png[currentFrame], TRUE);
		break;
	case Character::WALK_LEFT:
		DrawGraph(x, y, Slime_png[currentFrame], TRUE);
		break;
	case Character::WALK_RIGHT:
		DrawTurnGraph(x, y, Slime_png[currentFrame], TRUE);
		break;
	case Character::ATTACK_LEFT:
		DrawGraph(x, y, Slime_png[currentFrame], TRUE);
		break;
	case Character::ATTACK_RIGHT:
		DrawTurnGraph(x, y, Slime_png[currentFrame], TRUE);
		break;
	case Character::HIT_LEFT:
		DrawGraph(x, y, Slime_png[currentFrame], TRUE);
		break;
	case Character::HIT_RIGHT:
		DrawTurnGraph(x, y, Slime_png[currentFrame], TRUE);
		break;
	default:
		break;
	}
#if _DEBUG
	//デバッグ時に当たり判定の四角が見えるようになっている
	DrawBox(targetX, targetY, targetX + TILE_SIZE, targetY + TILE_SIZE, white, false);
#endif
}

//移動
void Slime::Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) {
	if (!isVisible)
		return;

		//MapManager* mMng = MapManager::GetInstance();
	CharacterManager* cMng = CharacterManager::GetInstance();

	int eTilePosX = targetX / TILE_SIZE;
	int eTilePosY = targetY / TILE_SIZE;

	cMng->CharacterData[eTilePosY][eTilePosX] = 2;

	int MoveDir;
	MoveDir = GetRand(3);

	auto playerPos = cMng->GetPlayerPosition();
	int pTilePosX = playerPos.first;
	int pTilePosY = playerPos.second;

	count++;

	Player* player = cMng->GetPlayer();


	if (pTilePosX != -1 && pTilePosY != -1 && count >= 90) { // プレイヤーが見つかった場合
		count = 0;

		if (std::abs(eTilePosX - pTilePosX) <= 4 && std::abs(eTilePosY - pTilePosY) <= 4) {

			if (x >= player->x)
				state = WALK_LEFT;
			if (x <= player->x)
				state = WALK_RIGHT;

			currentFrame = 4;

			auto path = pathfinder.FindPath(eTilePosX, eTilePosY, pTilePosX, pTilePosY, _mapData);
			if (!path.empty()) {
				if (path.size() > 1) {
					targetX = path[0].x * TILE_SIZE;
					targetY = path[0].y * TILE_SIZE;
				}
				else if (path.size() == 1) {
					// すでに隣のタイルにいる場合は移動しない
					Attack(player);
					currentFrame = 8;
				}
			}
		}
		else {
			currentFrame = 4;
			if (MoveDir == 0 && eTilePosY > 0) {
				if (_mapData[eTilePosY - 1][eTilePosX] == 0 && cMng->CharacterData[eTilePosY - 1][eTilePosX] == 0) {
					cMng->CharacterData[eTilePosY][eTilePosX] = 0;
					targetY = y - TILE_SIZE;
					state = WALK_LEFT;
				}
			}
			if (MoveDir == 1 && eTilePosY < MAP_WIDTH - 1) {
				if (_mapData[eTilePosY + 1][eTilePosX] == 0 && cMng->CharacterData[eTilePosY + 1][eTilePosX] == 0) {
					cMng->CharacterData[eTilePosY][eTilePosX] = 0;
					targetY = y + TILE_SIZE;
					state = WALK_RIGHT;
				}
			}
			if (MoveDir == 2 && eTilePosX > 0) {
				if (_mapData[eTilePosY][eTilePosX - 1] == 0 && cMng->CharacterData[eTilePosY][eTilePosX - 1] == 0) {
					cMng->CharacterData[eTilePosY][eTilePosX] = 0;
					targetX = x - TILE_SIZE;
					state = WALK_LEFT;
				}
			}
			if (MoveDir == 3 && eTilePosX < MAP_HEIGHT - 1) {
				if (_mapData[eTilePosY][eTilePosX + 1] == 0 && cMng->CharacterData[eTilePosY][eTilePosX + 1] == 0) {
					cMng->CharacterData[eTilePosY][eTilePosX] = 0;
					targetX = x + TILE_SIZE;
					state = WALK_RIGHT;
				}
			}
		}
	}
}

void Slime::TakeDamage(int damage) {
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	currentFrame = 13;
	hp -= damage;

	if (x >= player->x)
		state = HIT_LEFT;
	if (x <= player->x)
		state = HIT_RIGHT;

	if (hp <= 0) {
		Die();
	}
}

void Slime::Die() {
	int eTilePosX = x / TILE_SIZE;
	int eTilePosY = y / TILE_SIZE;
	CharacterManager* charMng = CharacterManager::GetInstance();
	charMng->CharacterData[eTilePosY][eTilePosX] = 0;

	// 敵が死んだときにEnemySpawnerのEnemyDefeated()を呼び出す
	EnemySpawner* enemySpawner = EnemySpawner::GetInstance();  // もしくはシングルトンで取得
	enemySpawner->EnemyDefeated();

	charMng->RemoveCharacter(this);

	currentFrame = 0;

	// プレイヤーのスコアを更新
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		player->AddScore(1);
	}
}

void Slime::Anim() {
	if (!isVisible)
		return;

	frameCounter++;
	if (frameCounter >= frameDelay) {
		frameCounter = 0;
		currentFrame++;
		if (state == WALK_LEFT) {
			if (currentFrame >= 8) {
				currentFrame = 0;
				state = IDLE_LEFT;
			}
		}
		if (state == WALK_RIGHT) {
			if (currentFrame >= 8) {
				currentFrame = 0;
				state = IDLE_RIGHT;
			}
		}
		else if (state == ATTACK_LEFT) {
			if (currentFrame >= 12) {
				currentFrame = 0;
				state = IDLE_LEFT;
			}
		}
		else if (state == ATTACK_RIGHT) {
			if (currentFrame >= 12) {
				currentFrame = 0;
				state = IDLE_RIGHT;
			}
		}
		else if (state == HIT_LEFT) {
			if (currentFrame >= 16) {
				currentFrame = 0;
				state = IDLE_LEFT;
			}
		}
		else if (state == HIT_RIGHT) {
			if (currentFrame >= 16) {
				currentFrame = 0;
				state = IDLE_RIGHT;
			}
		}
		else if (state == IDLE_LEFT) {
			if (currentFrame >= 4) {
				currentFrame = 0;
			}
		}
		else if (state == IDLE_RIGHT) {
			if (currentFrame >= 4) {
				currentFrame = 0;
			}
		}
	}
}

bool Slime::MovingAnim() {
	if (state == WALK || state == WALK_LEFT || state == WALK_RIGHT) {
		Player* player = CharacterManager::GetInstance()->GetPlayer();

		if (x < targetX) x += speed;
		if (x > targetX) x -= speed;
		if (y < targetY) y += speed;
		if (y > targetY) y -= speed;

		if (x - targetX == 0 && y - targetY == 0) {
			x = targetX;
			y = targetY;
			if (x >= player->x)
				state = IDLE_LEFT;
			if (x <= player->x)
				state = IDLE_RIGHT;
			return false;
		}
		return false;
	}
	return true;
}
