#include "FadeManager.h"
#include "TimeManager.h"

#pragma region �V���O���g��

//�ÓI�����o�ϐ��̏�����
FadeManager* FadeManager::pInstance = nullptr;

FadeManager::FadeManager()
	: blend(0.0f)
	, time(0.0f)
	, fadeState(FadeState::FadeEnd) {

}

FadeManager::~FadeManager() {
}

void FadeManager::CreateInstance() {
	pInstance = new FadeManager();
}

FadeManager* FadeManager::GetInstance() {
	if (pInstance == nullptr) CreateInstance();
	return pInstance;
}

void FadeManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

#pragma endregion

void FadeManager::Update() {
	//�t�F�[�h�������������Ă�����X�V���Ȃ�
	if (fadeState == FadeState::FadeEnd) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		return;
	}

	//���񂾂�ƃt�F�[�h�������s�����߂̌v�Z
	switch (fadeState) {
		//�t�F�[�h�C��
	case FadeState::FadeIn:
		//n�b�� 0 -> 255
		blend += 255 * TimeManager::GetInstance()->GetDeltaTime() / time;
		if (blend >= 255) {
			blend = 255;
			fadeState = FadeState::FadeEnd;
		}
		break;
	case FadeState::FadeOut:
		//n�b�� 255 -> 0
		blend -= 255 * TimeManager::GetInstance()->GetDeltaTime() / time;
		if (blend <= 0) {
			blend = 0;
			fadeState = FadeState::FadeEnd;
		}
		break;
	}
}

void FadeManager::Render() {
	//�t�F�[�h�������������Ă�����`�悵�Ȃ�
	if (fadeState == FadeState::FadeEnd)
		return;

	//�����x��ω������ăt�F�[�h����������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)blend);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, black, TRUE);
}

void FadeManager::FadeIn(float _t) {
	//�e��̕ϐ���������
	blend = 0.0f;
	time = _t;
	fadeState = FadeState::FadeIn;
}

void FadeManager::FadeOut(float _t) {
	//�e��̕ϐ���������
	blend = 255.0f;
	time = _t;
	fadeState = FadeState::FadeOut;
}

