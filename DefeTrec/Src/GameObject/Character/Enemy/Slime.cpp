#include "Slime.h"
#include "../Src/Definition.h"
#include "../Src/Manager/MapManager.h"
#include "../Src/Manager/CharacterManager.h"
#include "../Src/Pathfinding/AStar.h"
#include "../Player/Player.h"
#include "EnemySpawner.h"
#include <DxLib.h>

//A*�A���S���Y�����g�p���邽��
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
	//�s���Ȃ珈�����΂�
	if (!isVisible) {
		return;
	}
	//�ړ����̃A�j���[�V����
	MovingAnim();
	//�A�j���[�V����
	Anim();
}

	// �`��
void Slime::Render() {
	if (!isVisible)
		return;
	//�����I�������ɋC�Â��������R�[�h
	//if(�v���C���[�̈ʒu�����Ȃ�)DrawGraph
	//if(�v���C���[�̈ʒu���E�Ȃ�)DrawTurnGraph	�ł悩����
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
	//�f�o�b�O���ɓ����蔻��̎l�p��������悤�ɂȂ��Ă���
	DrawBox(targetX, targetY, targetX + TILE_SIZE, targetY + TILE_SIZE, white, false);
#endif
}

//�ړ�
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


	if (pTilePosX != -1 && pTilePosY != -1 && count >= 90) { // �v���C���[�����������ꍇ
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
					// ���łɗׂ̃^�C���ɂ���ꍇ�͈ړ����Ȃ�
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

	// �G�����񂾂Ƃ���EnemySpawner��EnemyDefeated()���Ăяo��
	EnemySpawner* enemySpawner = EnemySpawner::GetInstance();  // �������̓V���O���g���Ŏ擾
	enemySpawner->EnemyDefeated();

	charMng->RemoveCharacter(this);

	currentFrame = 0;

	// �v���C���[�̃X�R�A���X�V
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
