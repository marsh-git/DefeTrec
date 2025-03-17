#pragma once
#include "../Src/GameObject/Character/Player/Player.h"


//�v���C���[�̃X�e�[�^�X���Ԃ̕`������邽�߂̃N���X
//UI�S�ʂ�S������
class UIManager {
#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static UIManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *	@brief	�R���X�g���N�^
	 *	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	 */
	UIManager();

	/*
	 *	@brief	�f�X�g���N�^
	 */
	~UIManager();

public:	//�R�s�[�A���n���֎~

	UIManager(const UIManager&) = delete;
	UIManager(UIManager&&) = delete;
	UIManager& operator = (const UIManager&) = delete;
	UIManager& operator = (UIManager&&) = delete;

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
	static UIManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
	 */
	static void DestroyInstance();

#pragma endregion
private:		//�摜�ǂݍ���

    int HpBarSide;
    int HpBarMid;

private:		//�����o�֐�
	int Font75;
	int Font40;
	int Font50;


public:     //�����o�֐�
    void Update();

    void Render();

    void RenderUI();

    void RenderHp();

};

