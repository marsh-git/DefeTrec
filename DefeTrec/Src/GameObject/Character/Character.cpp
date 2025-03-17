#include "Character.h"
#include "../Src/Definition.h"
#include "../Src/Manager/CharacterManager.h"
#include "../Src/Manager/MapManager.h"

Character::Character(int startX, int startY, int Hp, int startAttackPower, float startSpeed)
	: GameObject(startX, startY, "Character")
	, hp(Hp)
	, attackPower(startAttackPower)
	, state(IDLE)
	, speed(startSpeed)
	, targetX(startX)
	, targetY(startY)
	, currentFrame(0)
	, frameCounter(0)
	, frameDelay(5)
	, maxHp(Hp) {
	x = startX;
	y = startY;
}

Character::~Character() {

}

//void Character::Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) {
//}

void Character::Render() {
	//非表示なら初期化しない
	if (!isVisible) return;
	// 例: 四角形でキャラクターを描画
	DrawBox(x, y, x + TILE_SIZE, y + TILE_SIZE, yellow, TRUE);
}


void Character::Attack(Character* character) {
	if (character != nullptr) {
		state = ATTACK;
		character->TakeDamage(attackPower);
	}
}

void Character::TakeDamage(int damage) {
	currentFrame = 0;
	hp -= damage;
	state = HIT;
	if (hp <= 0) {
		Die();
	}
}

void Character::Die() {
	int eTilePosX = x / TILE_SIZE;
	int eTilePosY = y / TILE_SIZE;
	CharacterManager* charMng = CharacterManager::GetInstance();
	charMng->CharacterData[eTilePosY][eTilePosX] = 0;

	charMng->RemoveCharacter(this);
}

void Character::Anim() {
	if (!isVisible)
		return;

	frameCounter++;
	if (frameCounter >= frameDelay) {
		frameCounter = 0;
		currentFrame++;
		if (state == WALK || state == WALK_LEFT || state == WALK_RIGHT) {
			if (currentFrame >= 11) {
				currentFrame = 0;
				state = IDLE;
			}
		}
		else if (state == ATTACK || state == ATTACK_LEFT || state == ATTACK_RIGHT) {
			if (currentFrame >= 9) {
				currentFrame = 0;
				state = IDLE;
			}
		}
		else if (state == HIT || state == HIT_LEFT || state == HIT_RIGHT) {
			if (currentFrame >= 5) {
				currentFrame = 0;
				state = IDLE;
			}
		}
		else if (state == IDLE || state == IDLE_LEFT || state == IDLE_RIGHT) {
			if (currentFrame >= 7) {
				currentFrame = 0;
			}
		}
	}
}

bool Character::MovingAnim() {
	if (state == WALK || state == WALK_LEFT || state == WALK_RIGHT) {
		if (x < targetX) x += 2;
		if (x > targetX) x -= 2;
		if (y < targetY) y += 2;
		if (y > targetY) y -= 2;

		if (x - targetX == 0 && y - targetY == 0) {
			x = targetX;
			y = targetY;
			state = IDLE;
			return false;
		}
		return false;
	}
	return true;
}

int Character::GetX() {
	return x;
}

int Character::GetY() {
	return y;
}
