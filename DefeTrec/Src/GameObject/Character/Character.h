#pragma once
#include "../GameObject.h"
#include "../Src/Definition.h"



//キャラクターの基底クラス
//すべてのキャラクターに必要な処理を書く
class Character : public GameObject {
public:		//メンバ変数
enum State {
	IDLE,
	IDLE_UP,
	IDLE_DOWN,
	IDLE_LEFT,
	IDLE_RIGHT,
	WALK,
	WALK_UP,
	WALK_DOWN,
	WALK_LEFT,
	WALK_RIGHT,
	ATTACK,
	ATTACK_UP,
	ATTACK_DOWN,
	ATTACK_LEFT,
	ATTACK_RIGHT,
	HIT,
	HIT_UP,
	HIT_DOWN,
	HIT_LEFT,
	HIT_RIGHT,
};
	int attackPower; // 攻撃力
	int hp;

	State state;

	float speed;
	float targetX;		//移動先に登録する座標
	float targetY;		//移動先に登録する座標

	int currentFrame;
	int frameCounter;
	int frameDelay;

public:		//コンストラクタ、デストラクタ
	Character(int startX, int startY, int Hp, int startAttackPower);
	virtual ~Character() = 0;

public:		//メンバ関数
	// 更新処理
	//virtual void Update();

	// 移動処理
	virtual void Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) = 0;

	// 描画処理
	void Render() override;

	//攻撃関数
	virtual void Attack(Character* character);
	//被弾関数
	virtual void TakeDamage(int damage);

	virtual void Die();

	virtual void Anim();

	virtual bool MovingAnim();

public:		//GetterとSetter
	int GetX();
	int GetY();
};

