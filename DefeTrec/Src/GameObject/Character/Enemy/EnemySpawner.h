#pragma once
#include "../Src/Manager/CharacterManager.h"
#include "../Src/Manager/MapManager.h"
#include "Slime.h"


class EnemySpawner {
#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static EnemySpawner* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	*	@brief	�R���X�g���N�^
	*	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	*/
	EnemySpawner();

	/*
	*	@brief	�f�X�g���N�^
	*/
	~EnemySpawner() = default;

public:	//�R�s�[�A���n���֎~

	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner(EnemySpawner&&) = delete;
	EnemySpawner& operator = (const EnemySpawner&) = delete;
	EnemySpawner& operator = (EnemySpawner&&) = delete;

private:	//�ÓI�����o�֐�
	/*
	*	@function	CreateInstance
	*	@brief		���g�̃C���X�^���X�𐶐�
	*	@return		EnemySpawner*
	*/
	static void CreateInstance();

public:		//�ÓI�����o�֐�
	/*
	*	@function	GetInstance
	*	@brief		���g�̃C���X�^���X���擾����B��̎�i
	*	@return		InputManager*	���g�̃C���X�^���X�̃A�h���X
	*/
	static EnemySpawner* GetInstance();

	/*
	*	@function	DestroyInstance
	*	@brief		���g�̃C���X�^���X���폜����B��̎�i
	*/
	static void DestroyInstance();

#pragma endregion

public:		//�ǂݍ���
	MapManager* mapManager = MapManager::GetInstance();
	CharacterManager* characterManager = CharacterManager::GetInstance();

public:		//�����o�ϐ�
	//�G�̍ő吔�J�E���g
	int enemyNum = 0;

public:		//�����o�֐�
	//�G���o��������֐�
	void SpawnEnemy(int _mapData[MAP_HEIGHT][MAP_WIDTH]);

	//�G��|�������p�̊֐�
	void EnemyDefeated();

	//���Z�b�g
	void Reset();

};

