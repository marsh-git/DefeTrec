#pragma once
#include "../Character.h"
#include "../Src/Manager/InputManager.h"
#include "../Enemy/Slime.h"
#include "../Src/Definition.h"

class Player : public Character {

private:
	int pImage_Idle[7];
	int pImage_Walk[11];
	int pImage_Attack[9];
	int pImage_Hit[5];

public:		//メンバ変数
	int score;			//倒した敵のスコア
	int floorCount;		//階数

	int maxHp;


public:		//コンストラクタ、デストラクタ
	Player(int startX, int startY, int Hp, int startAttackPower);
	~Player();

public:		//メンバ関数
	void Start();

	void Update();

	void Render();

	void Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) override;

	void Reset();

	void AddScore(int _points);

	void AddFloor();

public:		//GetterとSetter

	inline int GetHp() { return hp; };
	inline int GetMaxHp() { return maxHp; };


};

