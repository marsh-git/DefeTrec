#include "UIManager.h"
#include "../Manager/CharacterManager.h"


//�ÓI�����o�ϐ��̏�����
UIManager* UIManager::pInstance = nullptr;


UIManager::UIManager() {
	LoadDivGraph("Res/UI/HpUI.png", 5, 5, 1, 64, 64, Heart);
}

UIManager::~UIManager() {
	for (int i = 0; i < 5; i++)
		DeleteGraph(Heart[i]);
}

void UIManager::CreateInstance() {
	pInstance = new UIManager();
}

UIManager* UIManager::GetInstance() {

	if (pInstance == nullptr) CreateInstance();

	return pInstance;
}

void UIManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

void UIManager::Update() {
}

void UIManager::Render() {
	RenderUI();
	RenderHp();
}

void UIManager::RenderUI() {
	// �X�R�A�ƊK���̕\��
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		DrawFormatString(970, 75, black, "Score: %d", player->score);
		DrawFormatString(970, 100, black, "Floor: %d", player->floorCount);
	}
}

void UIManager::RenderHp() {
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		DrawFormatString(970, 10, black, "HP: %d", player->GetHp());
	}
}
