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

	pLevel = 0;
	Hp = 0;
	pSpeed = 0.0f;
	pPower = 0;
	Floor = 0;
	Score = 0;
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
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		pLevel = player->level;
		Hp = player->GetMaxHp();
		pSpeed = -player->speed + 21.0f;
		pPower = player->attackPower;
		Floor = player->floorCount;
		Score = player->score;
	}
}

void UIManager::Render() {
	RenderUI();
	RenderHp();
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player == nullptr) {
		DrawStringToHandle(960, 900, "Space for Result", black, Font50);
	}
}

void UIManager::RenderUI() {
	// スコアと階数の表示
	//Player* player = CharacterManager::GetInstance()->GetPlayer();
	//if (player != nullptr) {
		DrawStringToHandle(970, 10, "HP", black, Font75);
		DrawFormatStringToHandle(970, 150, black, Font40, "Level: %d", pLevel);
		DrawFormatStringToHandle(970, 200, black, Font40, "Hp: %d", Hp);
		DrawFormatStringToHandle(970, 250, black, Font40, "Speed: %.2f", pSpeed);
		DrawFormatStringToHandle(970, 300, black, Font40, "Power: %d", pPower);
		DrawFormatStringToHandle(970, 350, black, Font40, "Floor: %d", Floor);
		DrawFormatStringToHandle(970, 400, black, Font40, "Score: %d", Score);
	//}

	DrawFormatStringToHandle(970, 500, black, Font40, "WALK : WASD");
	DrawFormatStringToHandle(970, 550, black, Font40, "ATTACK : WASD");
	DrawFormatStringToHandle(970, 600, black, Font40, "SELECT : SPACE");
}

void UIManager::RenderHp() {
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr) {
		// HPバーの表示
		if (player->isVisible == true) {
			float hpRatio = static_cast<float>(player->GetHp()) / player->GetMaxHp();
			DrawBoxAA(979.0f, 85.0f, 979.0f + 430.0f * hpRatio, 140.0f, green, TRUE);
			//DrawFormatString(970, 500, black, "HP: %d", player->GetHp());
			//DrawFormatString(970, 510, black, "HP: %d", player->maxHp);
			//DrawBoxAA(979.0f, 85.0f, 979.0f + 430.0f * (float)(player->GetHp() / player->maxHp), 140.0f, green, TRUE);
		}
	}
	//hpバー
	{
		DrawGraph(970, 80, HpBarSide, TRUE);
		for (int i = 1; i < 6; i++)
			DrawGraph(970 + 64 * i, 80, HpBarMid, TRUE);
		DrawTurnGraph(1354, 80, HpBarSide, TRUE);
	}
}