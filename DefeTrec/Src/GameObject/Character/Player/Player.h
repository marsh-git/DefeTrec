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

	int exp;			//経験値
	int level;			//レベル
	
	int se;
	int levelupSe;

public:		//コンストラクタ、デストラクタ
	Player(int startX, int startY, int Hp, int startAttackPower, float startSpeed = 20.0f);
	~Player();

public:		//メンバ関数
	void Start();

	void Update();

	void Render();

	void Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) override;

	void Reset();

	void AddScore(int _points);

	void AddFloor();

	void CheckLevel();

	void LevelUp();

	void Attack(Character* character) override;

public:		//GetterとSetter

	inline int GetHp() { return hp; };
	inline int GetMaxHp() { return maxHp; };


};

