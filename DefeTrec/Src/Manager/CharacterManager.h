#pragma once
#include "../Definition.h"
#include <vector>
#include "../Src/GameObject/Character/Enemy/Slime.h"
#include "../Src/GameObject/Character/Player/Player.h"


//�L�����N�^�[�̈ʒu���Ǘ�����N���X

class CharacterManager {
#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static CharacterManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *	@brief	�R���X�g���N�^
	 *	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	 */
	CharacterManager();

	/*
	 *	@brief	�f�X�g���N�^
	 */
	~CharacterManager() = default;

public:	//�R�s�[�A���n���֎~

	CharacterManager(const CharacterManager&) = delete;
	CharacterManager(CharacterManager&&) = delete;
	CharacterManager& operator = (const CharacterManager&) = delete;
	CharacterManager& operator = (CharacterManager&&) = delete;

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
	static CharacterManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
	 */
	static void DestroyInstance();

#pragma endregion
protected:		//�����o�ϐ�
	int i = 0;		//�}�b�v�𐶐����邽�߂̕ϐ�
	int j = 0;

public:
	std::vector<Slime*> enemies;		//�L�����N�^�[�̃��X�g
	Player* player;						//�v���C���[

public:			//�L�����N�^�[�z��
	int CharacterData[MAP_HEIGHT][MAP_WIDTH] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

public:		//�����o�֐�
	//�G��ǉ�����֐�
	void AddEnemy(Slime* enemy);
	//�L�����N�^�[�̍폜
	void RemoveCharacter(Character* character);

public:		//Getter��Setter
	Slime* GetEnemyAtPosition(int tileX, int tileY);	//�w��ʒu�ɂ���G�̎擾

	void SetPlayer(Player* player);	//�v���C���[�̐ݒ�
	Player* GetPlayer();	//�v���C���[�̎擾

	std::pair<int, int> GetPlayerPosition();	//�v���C���[�̈ʒu���擾
};

