#pragma once
#include "../GameObject.h"
#include "../Src/Definition.h"



//�L�����N�^�[�̊��N���X
//���ׂẴL�����N�^�[�ɕK�v�ȏ���������
class Character : public GameObject {
public:		//�����o�ϐ�
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
	int attackPower; // �U����
	int hp;

	State state;

	float speed;
	float targetX;		//�ړ���ɓo�^������W
	float targetY;		//�ړ���ɓo�^������W

	int currentFrame;
	int frameCounter;
	int frameDelay;

public:		//�R���X�g���N�^�A�f�X�g���N�^
	Character(int startX, int startY, int Hp, int startAttackPower);
	virtual ~Character() = 0;

public:		//�����o�֐�
	// �X�V����
	//virtual void Update();

	// �ړ�����
	virtual void Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) = 0;

	// �`�揈��
	void Render() override;

	//�U���֐�
	virtual void Attack(Character* character);
	//��e�֐�
	virtual void TakeDamage(int damage);

	virtual void Die();

	virtual void Anim();

	virtual bool MovingAnim();

public:		//Getter��Setter
	int GetX();
	int GetY();
};

