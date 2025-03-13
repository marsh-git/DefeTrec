#include "TimeManager.h"
#include <DxLib.h>
#include "../Definition.h"

//�ÓI�����o�ϐ��̏�����
TimeManager* TimeManager::pInstance = nullptr;

TimeManager::TimeManager()
	:prevTime(GetNowCount())
	, currentTime(prevTime)
	, deltaTime(currentTime - prevTime)
	, m(0)
	, s(0)
	, ms(0) {
	Start();
}

TimeManager::~TimeManager() {
}

void TimeManager::CreateInstance() {
	pInstance = new TimeManager();
}

TimeManager* TimeManager::GetInstance() {
	if (pInstance == nullptr)
		CreateInstance();
	return pInstance;
}

void TimeManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

void TimeManager::Start() {

}

void TimeManager::Update() {
	//���݂̃t���[���̎��Ԃ��擾
	currentTime = GetNowCount();

	//�E�B���h�E���A�N�e�B�u�ȏꍇ�ɏ�������
	if (!GetNoActiveState()) {
		//1�t���[���O�̎��ԂƂ̍������v�Z
		deltaTime = currentTime - prevTime;

		//���Ԃ̌v�Z
		ms += deltaTime;
		if (ms >= 1000) {
			ms -= 1000;
			s++;
		}
		if (s >= 60) {
			s -= 60;
			m++;
		}

		//deltaTime��Unity�̂悤�Ɉ������߂ɒP�ʂ�ms->s�ɕϊ�
		deltaTime /= 1000.0f;
	}
	//1�t���[���O�̎��Ԃ����݂̎��ԂɍX�V
	prevTime = currentTime;

}

void TimeManager::Render() {
#if _DEBUG
	DrawFormatString(500, 0, red, "%02d:%02d:%03d", m, s, ms);
	DrawFormatString(500, 20, red, "FPS:%.0f", 1.0f / deltaTime);
#endif
}
