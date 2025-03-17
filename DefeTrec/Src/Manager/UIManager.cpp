#include "UIManager.h"
#include "../Manager/CharacterManager.h"


//静的メンバ変数の初期化
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
	// スコアと階数の表示
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		DrawFormatStringToHandle(970, 150, black, Font40, "Score: %d", player->score);
		DrawFormatStringToHandle(970, 200, black, Font40, "Floor: %d", player->floorCount);
		//DrawFormatString(970, 75, black, "Score: %d", player->score);
		//DrawFormatString(970, 100, black, "Floor: %d", player->floorCount);
	}
}

void UIManager::RenderHp() {
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		DrawStringToHandle(970, 10, "HP", black, Font75);
		// HPバーの表示
		float hpRatio = static_cast<float>(player->GetHp()) / player->GetMaxHp();
		DrawBoxAA(979.0f, 85.0f, 979.0f + 430.0f * hpRatio, 140.0f, green, TRUE);
		//DrawFormatString(970, 500, black, "HP: %d", player->GetHp());
		//DrawFormatString(970, 510, black, "HP: %d", player->maxHp);
		//DrawBoxAA(979.0f, 85.0f, 979.0f + 430.0f * (float)(player->GetHp() / player->maxHp), 140.0f, green, TRUE);
	}

	DrawGraph(970, 80, HpBarSide, TRUE);
	for(int i = 1; i < 6; i++)
		DrawGraph(970 + 64 * i, 80, HpBarMid, TRUE);
	DrawTurnGraph(1354, 80, HpBarSide, TRUE);
}
