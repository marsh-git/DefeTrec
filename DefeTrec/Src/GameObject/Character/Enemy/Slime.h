#pragma once
#include "../Character.h"



class Slime : public Character {
private:		//�����o�ϐ�

	int count;				//�ړ��̂��߂̃J�E���^
	int Slime_png[21];		//�摜�ǂݍ���


public:		//�R���X�g���N�^�A�f�X�g���N�^
	Slime(int startX, int startY, int Hp, int startAttackPower);
	~Slime();

public:		//�����o�֐�
	//�X�^�[�g
	void Start();
	//�A�b�v�f�[�g
	void Update() override;
	//�`��
	void Render() override;
	//�ړ�
	void Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) override;
	//��e��
	void TakeDamage(int damage) override;
	//���S
	void Die() override;
	//�A�j���[�V����
	void Anim() override;
	//�ړ����̃A�j���[�V����
	bool MovingAnim() override;
};

