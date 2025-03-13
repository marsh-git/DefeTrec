#include "FadeManager.h"
#include "TimeManager.h"

#pragma region シングルトン

//静的メンバ変数の初期化
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
	//フェード処理が完了していたら更新しない
	if (fadeState == FadeState::FadeEnd) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		return;
	}

	//だんだんとフェード処理を行うための計算
	switch (fadeState) {
		//フェードイン
	case FadeState::FadeIn:
		//n秒で 0 -> 255
		blend += 255 * TimeManager::GetInstance()->GetDeltaTime() / time;
		if (blend >= 255) {
			blend = 255;
			fadeState = FadeState::FadeEnd;
		}
		break;
	case FadeState::FadeOut:
		//n秒で 255 -> 0
		blend -= 255 * TimeManager::GetInstance()->GetDeltaTime() / time;
		if (blend <= 0) {
			blend = 0;
			fadeState = FadeState::FadeEnd;
		}
		break;
	}
}

void FadeManager::Render() {
	//フェード処理が完了していたら描画しない
	if (fadeState == FadeState::FadeEnd)
		return;

	//透明度を変化させてフェード処理をする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)blend);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, black, TRUE);
}

void FadeManager::FadeIn(float _t) {
	//各種の変数を初期化
	blend = 0.0f;
	time = _t;
	fadeState = FadeState::FadeIn;
}

void FadeManager::FadeOut(float _t) {
	//各種の変数を初期化
	blend = 255.0f;
	time = _t;
	fadeState = FadeState::FadeOut;
}

