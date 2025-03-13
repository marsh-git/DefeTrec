#pragma once
//	=================================================================
//		[1]	�w�b�_�[���C���N���[�h����ꏊ
//	=================================================================
#include <DxLib.h>
#include <string>

//	=================================================================
//		[2]	�}�N�����`����ꏊ
//	=================================================================
#define WINDOW_WIDTH			(1440)	//	�E�B���h�E�̉���	960
#define WINDOW_HEIGHT			(960)	//	�E�B���h�E�̏c��	960

#define FPS						(120)	//	FPS

#define TILE_SIZE				(64)	//	�}�b�v�P�}�X������̑傫��
#define	MAP_WIDTH				(15)	//	�}�b�v�̕�
#define	MAP_HEIGHT				(15)	//	�}�b�v�̍���

//	�����t���}�N����`	�ϊ��}�N��
#define Deg2Rad(x) ( x * DX_PI_F / 180.0f )	//�f�O���[->���W�A��
#define Rad2Deg(x) ( x * 180.0f / DX_PI_F )	//���W�A��->�f�O���[

//���[���h�x�N�g��
#define VRight		(VGet(1.0f,0.0f,0.0f))	//�E
#define VLeft		(VGet(-1.0f,0.0f,0.0f))	//��
#define VUp			(VGet(0.0f,1.0f,0.0f))	//��
#define VDown		(VGet(0.0f,-1.0f,0.0f))	//��
#define VForward	(VGet(0.0f,0.0f,1.0f))	//�O
#define VBack		(VGet(0.0f,0.0f,-1.0f))	//��

//��x�N�g��
#define VZero		(VGet(0.0f,0.0f,0.0f))
//��x�N�g��
#define VOne		(VGet(1.0f,1.0f,1.0f))

//DxLib�̓ǂݍ��݃G���[
#define INVALID		(-1)


//	=================================================================
//		[2]	�萔���`����ꏊ
//	=================================================================
//	�F
const unsigned int red = GetColor(255, 0, 0);
const unsigned int green = GetColor(0, 255, 0);
const unsigned int blue = GetColor(0, 0, 255);
const unsigned int magenta = GetColor(255, 0, 255);
const unsigned int cyan = GetColor(0, 255, 255);
const unsigned int yellow = GetColor(255, 255, 0);
const unsigned int white = GetColor(255, 255, 255);
const unsigned int black = GetColor(0, 0, 0);
const unsigned int gray = GetColor(128, 128, 128);

//	=================================================================
//		[3]	�񋓒萔���`����ꏊ	
//	=================================================================

enum class SceneType {
	Title,
	Game,
	Result,
};

enum class FadeState {
	FadeIn,
	FadeOut,
	FadeEnd,

};