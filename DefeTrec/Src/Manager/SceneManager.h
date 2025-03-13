#pragma once
#include "../Definition.h"
#include "../Manager/FadeManager.h"

class SceneManager {

#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static SceneManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *	@brief	�R���X�g���N�^
	 *	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	 */
	SceneManager();

	/*
	 *	@brief	�f�X�g���N�^
	 */
	~SceneManager();

public:	//�R�s�[�A���n���֎~

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator = (const SceneManager&) = delete;
	SceneManager& operator = (SceneManager&&) = delete;

private:	//�ÓI�����o�֐�
	/*
	 *	@function	CreateInstance
	 *	@brief		���g�̃C���X�^���X�𐶐�
	 *	@return		SceneManager*
	 */
	static void CreateInstance();

public:		//�ÓI�����o�֐�
	/*
	 *	@function	GetInstance
	 *	@brief		���g�̃C���X�^���X���擾����B��̎�i
	 *	@return		CollisionManager*	���g�̃C���X�^���X�̃A�h���X
	 */
	static SceneManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
	 */
	static void DestroyInstance();

#pragma endregion


private:	//�����o�ϐ�
	class BaseScene* pCurrentScene;		//���݂̃V�[��
	SceneType current;
	SceneType next;

	bool changed;			//�V�[���؂�ւ����I���������ǂ���

public:		//�����o�֐�
	void Update();

	void Render();

	void LoadScene();

public:		//Getter��Setter

	void SetNext(SceneType _next);

};


