#pragma once
#include "MapManager.h"

class FloorManager {

#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static FloorManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	*	@brief	�R���X�g���N�^
	*	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	*/
	FloorManager();

	/*
	*	@brief	�f�X�g���N�^
	*/
	~FloorManager() = default;

public:	//�R�s�[�A���n���֎~

	FloorManager(const FloorManager&) = delete;
	FloorManager(FloorManager&&) = delete;
	FloorManager& operator = (const FloorManager&) = delete;
	FloorManager& operator = (FloorManager&&) = delete;

private:	//�ÓI�����o�֐�
	/*
	*	@function	CreateInstance
	*	@brief		���g�̃C���X�^���X�𐶐�
	*	@return		FloorManager*
	*/
	static void CreateInstance();

public:		//�ÓI�����o�֐�
	/*
	*	@function	GetInstance
	*	@brief		���g�̃C���X�^���X���擾����B��̎�i
	*	@return		InputManager*	���g�̃C���X�^���X�̃A�h���X
	*/
	static FloorManager* GetInstance();

	/*
	*	@function	DestroyInstance
	*	@brief		���g�̃C���X�^���X���폜����B��̎�i
	*/
	static void DestroyInstance();

#pragma endregion

public:			//�����o�ϐ�
    int MapRand[MAP_HEIGHT][MAP_WIDTH];  // �}�b�v�f�[�^
    //int playerX, playerY;  // �v���C���[�̍��W

public:			//�����o�֐�
    // �K�w��i�߂鏈��
    void NextFloor(double wallRatio, double pathRatio, double enemyRatio);

	//���Z�b�g
	void Reset();

public:			//Getter��Setter
    // ���݂̃}�b�v�f�[�^���擾
    int (*GetMapData())[MAP_WIDTH];

    // �v���C���[�̍��W�擾
    //int GetPlayerX() const { return playerX; }
    //int GetPlayerY() const { return playerY; }
};
