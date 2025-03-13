#pragma once
#include<string>
#include<List>
#include<map>
#include<DxLib.h>


class AudioManager {

#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static AudioManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *	@brief	�R���X�g���N�^
	 *	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	 */
	AudioManager();

	/*
	 *	@brief	�f�X�g���N�^
	 */
	~AudioManager();

public:	//�R�s�[�A���n���֎~

	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator = (const AudioManager&) = delete;
	AudioManager& operator = (AudioManager&&) = delete;

private:	//�ÓI�����o�֐�
	/*
	 *	@function	CreateInstance
	 *	@brief		���g�̃C���X�^���X�𐶐�
	 *	@return		AudioManager*
	 */
	static void CreateInstance();

public:		//�ÓI�����o�֐�
	/*
	 *	@function	GetInstance
	 *	@brief		���g�̃C���X�^���X���擾����B��̎�i
	 *	@return		CollisionManager*	���g�̃C���X�^���X�̃A�h���X
	 */
	static AudioManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
	 */
	static void DestroyInstance();

#pragma endregion

private:	//�����o�ϐ�
	std::map<std::string, int>audioResouceMap;		//���\�[�X�̘A�z�z��
	std::list<class Audio*>pAudioList;			//�G�t�F�N�g�̈ꌳ�Ǘ�	

public:		//�����o�֐�
	/*
	 *	@function	Load
	 *	@brief		�G�t�F�N�g�ǂݍ���
	 *	@param[in]	std::string	_fillPath		�t�@�C���p�X
	 *	@param[in]	std::string	_name			�G�t�F�N�g�ɂ��閼�O
	 *	@param[in]	float _magnification = 1.0f	�g�嗦
	 */
	void Load(std::string _filePath, std::string _name);

	void ChangeVolume(std::string _name, float _volume);

	void PlayOneShot(std::string _name, float _volume = 1.0f);

	void PlayClipAtPoint(std::string _name, float _volume = 1.0f, bool _loop = false);

	void Stop(std::string _name);

	void Update();

};

