#include "UIManager.h"
#include "../Manager/CharacterManager.h"


//�ÓI�����o�ϐ��̏�����
UIManager* UIManager::pInstance = nullptr;


UIManager::UIManager() {
	HpBarSide = LoadGraph("Res/UI/HpSide.PNG");
	HpBarMid = LoadGraph("Res/UI/HpMiddle.PNG");
	Font75 = CreateFontToHandle("Magneto", 75, 5);
	Font40 = CreateFontToHandle("Magneto", 40, 5);
	Font50 = CreateFontToHandle("Magneto", 50, 5);
}

UIManager::~UIManager() {
	DeleteGraph(HpBarSide);
	DeleteGraph(HpBarMid);
	DeleteFontToHandle(Font75);
	DeleteFontToHandle(Font40);
	DeleteFontToHandle(Font50);
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
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (!player->isVisible) {
		DrawStringToHandle(960, 900, "Space for Result", black, Font50);
	}
}

void UIManager::RenderUI() {
	// �X�R�A�ƊK���̕\��
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		DrawFormatStringToHandle(970, 150, black, Font40, "Level: %d", player->level);
		DrawFormatStringToHandle(970, 200, black, Font40, "Hp: %d", player->GetMaxHp());
		DrawFormatStringToHandle(970, 250, black, Font40, "Speed: %.2f", -player->speed + 21.0f);
		DrawFormatStringToHandle(970, 300, black, Font40, "Power: %d", player->attackPower);
		DrawFormatStringToHandle(970, 350, black, Font40, "Floor: %d", player->floorCount);
		DrawFormatStringToHandle(970, 400, black, Font40, "Score: %d", player->score);
	}
}

void UIManager::RenderHp() {
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		DrawStringToHandle(970, 10, "HP", black, Font75);
		// HP�o�[�̕\��
		float hpRatio = static_cast<float>(player->GetHp()) / player->GetMaxHp();
		DrawBoxAA(979.0f, 85.0f, 979.0f + 430.0f * hpRatio, 140.0f, green, TRUE);
		//DrawFormatString(970, 500, black, "HP: %d", player->GetHp());
		//DrawFormatString(970, 510, black, "HP: %d", player->maxHp);
		//DrawBoxAA(979.0f, 85.0f, 979.0f + 430.0f * (float)(player->GetHp() / player->maxHp), 140.0f, green, TRUE);
	}
	//hp�o�[
	{
		DrawGraph(970, 80, HpBarSide, TRUE);
		for (int i = 1; i < 6; i++)
			DrawGraph(970 + 64 * i, 80, HpBarMid, TRUE);
		DrawTurnGraph(1354, 80, HpBarSide, TRUE);
	}
}