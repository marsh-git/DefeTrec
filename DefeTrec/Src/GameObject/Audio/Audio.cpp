#include "Audio.h"


/*
 *  @brief		�R���X�g���N�^
 *	@param[in]	int _soundHandle	���n���h��
 */
Audio::Audio(int _soundHandle)
	:GameObject(0, 0, "")
	, isLoop(false)
	, soundHandle(_soundHandle)
	, volume(255)
	, distance(800.0f) {
	Start();
}

/*
 *  @brief		�f�X�g���N�^
 */
Audio::~Audio() {
	DeleteSoundMem(soundHandle);
}

/*
 *	@function	Start
 *  @brief		����������
 */
void Audio::Start() {
	if (isLoop)
		PlaySoundMem(soundHandle, DX_PLAYTYPE_LOOP);
	else 
		PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}

/*
 *	@function	Update
 *  @brief		�X�V����
 */
void Audio::Update() {
	//��\���Ȃ�X�V���Ȃ�
	if (!isVisible)
		return;

	//�Đ������ǂ���
	if (CheckSoundMem(soundHandle) == 0)
		isVisible = false;

	//���ʂ̐ݒ�
	ChangeVolumeSoundMem((int)volume, soundHandle);
}

/*
 *	@function	Render
 *  @brief		�`�揈��
 */
void Audio::Render() {
}
