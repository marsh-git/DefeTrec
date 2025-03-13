#pragma once
#include "../Definition.h"


class FadeManager {

#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static FadeManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *	@brief	�R���X�g���N�^
	 *	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	 */
	FadeManager();

	/*
	 *	@brief	�f�X�g���N�^
	 */
	~FadeManager();

public:	//�R�s�[�A���n���֎~

	FadeManager(const FadeManager&) = delete;
	FadeManager(FadeManager&&) = delete;
	FadeManager& operator = (const FadeManager&) = delete;
	FadeManager& operator = (FadeManager&&) = delete;

private:	//�ÓI�����o�֐�
	/*
	 *	@function	CreateInstance
	 *	@brief		���g�̃C���X�^���X�𐶐�
	 *	@return		FadeManager*
	 */
	static void CreateInstance();

public:		//�ÓI�����o�֐�
	/*
	 *	@function	GetInstance
	 *	@brief		���g�̃C���X�^���X���擾����B��̎�i
	 *	@return		CollisionManager*	���g�̃C���X�^���X�̃A�h���X
	 */
	static FadeManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
	 */
	static void DestroyInstance();

#pragma endregion

private:		//�����o�ϐ�
	float blend;		//�u�����h�p�����[�^ 0~255, 0:���� 255:�s����
	float time;			//�o�ߎ���

	FadeState fadeState;	//�t�F�[�h�̏��


public:			//�����o�֐�
	/*
	 *	@function	Update
	 *  @brief		�X�V����
	 */
	void Update();

	/*
	 *	@function	Render
	 *  @brief		�`�揈��
	 *  @tips		�������z�֐��Ŏ���
	 */
	void Render();

	/*
	 *	@function	FadeIn
	 *  @brief		�t�F�[�h�C��
	 *  @param[in]	float _t = 1.0f		�S�̎���
	 */
	void FadeIn(float _t = 1.0f);

	/*
	 *	@function	FadeOut
	 *  @brief		�t�F�[�h�A�E�g
	 *  @param[in]	float _t = 1.0f		�S�̎���
	 */
	void FadeOut(float _t = 1.0f);

public:			//Getter��Setter

	/*
	 *	@function	GetFadeState
	 *  @brief		�t�F�[�h��Ԃ̎擾
	 *  @return		FadeState
	 */
	inline FadeState GetFadeState() const { return fadeState; }

};

