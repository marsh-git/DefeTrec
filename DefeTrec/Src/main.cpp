//=================================================
//	�w�b�_�[���C���N���[�h
//=================================================
#include<DxLib.h>
#include "Definition.h"
#include "Manager/SceneManager.h"
#include "Manager/TimeManager.h"
#include "Manager/InputManager.h"
#include "Manager/FadeManager.h"
#include "Manager/AudioManager.h"

//=================================================
//	�֐���錾�A��`
//=================================================
/*
 * @brief		Window�v���O�����̃G���g���[�|�C���g
 * @param[in]	HINSTANSE	����͕s�v
 * @param[in]	HINSTANSE	����͕s�v
 * @param[in]	LPSTR		����͕s�v
 * @param[in]	int			����͕s�v
 * @return		int			����͕s�v
 * @tips		WINAPI		����͕s�v
 */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//=================================================
	//	DxLib�̏����������A��������܂ł͐G���
	//=================================================
	//�E�B���h�E�̃T�C�Y��ύX����
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, FPS);
	//�N�����̃E�B���h�E���[�h�̐ݒ�
	ChangeWindowMode(true);		//�^��Window���[�h�A�U��Full�X�N���[��
	//�w�i�F
	SetBackgroundColor(196, 196, 196);
	SetWindowIconID(333);
	SetWindowText("DefeTrec");
	//DxLib�̏�����
	if (DxLib_Init() == -1) {
		return 0;
	}

	//�`����ݒ�	���ɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//�}�`�`��Z�o�b�t�@�̗L����
	{
		//Z�o�b�t�@���g�p���邩�F�f�t�H���g��FALSE
		SetUseZBuffer3D(TRUE);
		//Z�o�b�t�@�ɏ������ނ��F�f�t�H���g��FALSE
		SetWriteZBuffer3D(TRUE);
	}

	//���C�e�B���O
	{
		//���C�g�̌v�Z�����邩�F�f�t�H���g��TRUE
		SetUseLighting(FALSE);
		//�W�����C�g���g�����F�f�t�H���g��TRUE
		SetLightEnable(FALSE);
	}

	//=================================================
	//	�Q�[���̏���������
	//=================================================
	//FPS�����p
	int time;

	
	//=================================================
	//	�Q�[���̃��C�����[�v
	//=================================================
	while (1) {
		//�E�B���h�E�̃��b�Z�[�W����������
		if (ProcessMessage() == -1) break;

		//FPS�̒���
		time = GetNowCount();
		//=================================================
		//	�}�l�[�W���[�̍X�V����
		//=================================================

		//�^�C���}�l�[�W���[�̍X�V
		TimeManager::GetInstance()->Update();
		//���͊Ǘ��̍X�V
		InputManager::GetInstance()->Update();

		//=================================================
		//	�Q�[���̍X�V����
		//=================================================

		//esc�������ꂽ��Q�[�������
		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;

		//��ʑJ�ڂ̍X�V
		FadeManager::GetInstance()->Update();
		// �Q�[���̕`�揈��
		SceneManager::GetInstance()->Update();
		//�����̍X�V
		AudioManager::GetInstance()->Update();

		//��ʃN���A
		ClearDrawScreen();

		//=================================================
		//	�Q�[���̕`�揈���A�`�揇����
		//=================================================

		//��ʑJ�ڂ̕`��
		FadeManager::GetInstance()->Render();
		//�Q�[���̕`��
		SceneManager::GetInstance()->Render();


		//����ʂƕ\��ʂ̓���ւ�
		ScreenFlip();

		//��������������Ƃ��ɑ҂�
		while (1) {
			if (GetNowCount() - time >= 1000 / FPS) break;
		}
	}
	//=================================================
	//	�Q�[���̉������
	//=================================================
	
	// �Q�[���̉������
	SceneManager::DestroyInstance();
	TimeManager::DestroyInstance();
	InputManager::DestroyInstance();
	FadeManager::DestroyInstance();
	AudioManager::DestroyInstance();

	//=================================================
	//	DxLib�̉������
	//=================================================
	//DxLib�̏I��
	DxLib_End();

	return 0;
}