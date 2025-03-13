#include "UIManager.h"


UIManager::UIManager(Player* _player)
: player(_player){
	LoadDivGraph("Res/UI/HpUI.png", 5, 5, 1, 64, 64, Heart);
}

UIManager::~UIManager() {
	for (int i = 0; i < 5; i++)
		DeleteGraph(Heart[i]);
}

void UIManager::Update() {
}

void UIManager::Render() {
	RenderUI();
	RenderHp(player->GetHp());
}

void UIManager::RenderUI() {
}

void UIManager::RenderHp(int _hp) {

}
