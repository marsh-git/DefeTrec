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

public:		//�����o�ϐ�


public:		//�R���X�g���N�^�A�f�X�g���N�^
	Player(int startX, int startY, int Hp, int startAttackPower);
	~Player();

public:		//�����o�֐�
	void Start();

	void Update();

	void Render();

	void Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) override;

public:		//Getter��Setter

	inline int GetHp() { return hp; };


};

