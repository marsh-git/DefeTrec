#pragma once
#include "../Character.h"



class Slime : public Character {
private:		//メンバ変数

	int count;
	int Slime_png[21];


public:		//コンストラクタ、デストラクタ
	Slime(int startX, int startY, int Hp, int startAttackPower);
	~Slime();

public:		//メンバ関数
	void Start();

	void Update() override;

	void Render() override;

	void Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) override;

	void Attack(Character* player) override;

	void TakeDamage(int damage) override;

	void Die() override;

	void Anim() override;

	bool MovingAnim() override;
};

