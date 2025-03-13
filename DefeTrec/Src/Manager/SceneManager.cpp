#include "SceneManager.h"
#include "../Scene/GameScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/ResultScene.h"
#include "FadeManager.h"

#pragma region �V���O���g��

//�ÓI�����o�ϐ��̏�����
SceneManager* SceneManager::pInstance = nullptr;

SceneManager::SceneManager()
	:pCurrentScene(nullptr)
	, next(SceneType::Title)
	, current((SceneType)INVALID)
	, changed(true) {
	//�J�ڐ�̃V�[���𐶐�����
	switch (next) {
	case SceneType::Title:
		pCurrentScene = new TitleScene();
		break;
	case SceneType::Game:
		pCurrentScene = new GameScene();
		break;
	case SceneType::Result:
		pCurrentScene = new ResultScene();
		break;
	default:
		pCurrentScene = nullptr;
		break;
	}


}

SceneManager::~SceneManager() {
}

void SceneManager::CreateInstance() {
	pInstance = new SceneManager();
}

SceneManager* SceneManager::GetInstance() {
	if (pInstance == nullptr) CreateInstance();
	return pInstance;
}

void SceneManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

#pragma endregion

void SceneManager::Update() {
	//�t�F�[�h�������I�����Ă��Ȃ���΍X�V���Ȃ�
	if (FadeManager::GetInstance()->GetFadeState() != FadeState::FadeEnd)
		return;

	//�V�[���̐؂�ւ��̍ŏ���1�񂾂��t�F�[�h�������s��
	if (changed) {
		changed = false;
		FadeManager::GetInstance()->FadeOut();
	}


	//�V�[�����Ȃ���΍X�V���Ȃ�
	if (pCurrentScene == nullptr)
		return;

	//���݂̃V�[�����X�V
	pCurrentScene->Update();

	//�V�[���̐؂�ւ�������ΑJ�ڂ��s��
	if (current != next)
		LoadScene();
}

void SceneManager::Render() {
	//�t�F�[�h�������I�����Ă��Ȃ���΍X�V���Ȃ�
	//��Fade���ɂ��猩������ꍇ�͋L�q���Ȃ�
	if (FadeManager::GetInstance()->GetFadeState() != FadeState::FadeEnd)
		return;

	//�V�[�����Ȃ���Ε`�悵�Ȃ�
	if (pCurrentScene == nullptr)
		return;

	//���݂̃V�[����`��
	pCurrentScene->Render();
}

void SceneManager::LoadScene() {

	//���݂̃V�[���ԍ�������������
	current = next;

	//���݂̃V�[�����폜
	delete pCurrentScene;
	pCurrentScene = nullptr;

	//���̃V�[���𐶐�����
	switch (next) {
	case SceneType::Title:
		pCurrentScene = new TitleScene();
		break;
	case SceneType::Game:
		pCurrentScene = new GameScene();
		break;
	case SceneType::Result:
		pCurrentScene = new ResultScene();
		break;
	default:
		pCurrentScene = nullptr;
		break;
	}
}

void SceneManager::SetNext(SceneType _next) {
	next = _next;
	changed = true;

	//�V�[���؂�ւ��Ɍ����ăt�F�[�h�������J�n
	FadeManager::GetInstance()->FadeIn();
}

