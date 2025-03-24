#pragma once
#include "../Definition.h"

class EffectManager {
#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static EffectManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *	@brief	�R���X�g���N�^
	 *	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	 */
	EffectManager();

	/*
	 *	@brief	�f�X�g���N�^
	 */
	~EffectManager();

public:	//�R�s�[�A���n���֎~

	EffectManager(const EffectManager&) = delete;
	EffectManager(EffectManager&&) = delete;
	EffectManager& operator = (const EffectManager&) = delete;
	EffectManager& operator = (EffectManager&&) = delete;

private:	//�ÓI�����o�֐�
	/*
	 *	@function	CreateInstance
	 *	@brief		���g�̃C���X�^���X�𐶐�
	 *	@return		CharacterManager*
	 */
	static void CreateInstance();

public:		//�ÓI�����o�֐�
	/*
	 *	@function	GetInstance
	 *	@brief		���g�̃C���X�^���X���擾����B��̎�i
	 *	@return		InputManager*	���g�̃C���X�^���X�̃A�h���X
	 */
	static EffectManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
	 */
	static void DestroyInstance();

#pragma endregion
protected:
	int Particle_png[18];		//�摜�ǂݍ���

public:		//�����o�ϐ�
	int currentFrame;
	int frameCounter;
	int frameDelay;

	int effectX;
	int effectY;

public:		//�����o�֐�

	void Update();

	void Render();

	void WhenDied(int _x, int _y);

public:		//Getter��Setter


};

