#include "TimeManager.h"
#include <DxLib.h>
#include "../Definition.h"

//静的メンバ変数の初期化
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
	//現在のフレームの時間を取得
	currentTime = GetNowCount();

	//ウィンドウがアクティブな場合に処理する
	if (!GetNoActiveState()) {
		//1フレーム前の時間との差分を計算
		deltaTime = currentTime - prevTime;

		//時間の計算
		ms += deltaTime;
		if (ms >= 1000) {
			ms -= 1000;
			s++;
		}
		if (s >= 60) {
			s -= 60;
			m++;
		}

		//deltaTimeをUnityのように扱うために単位をms->sに変換
		deltaTime /= 1000.0f;
	}
	//1フレーム前の時間を現在の時間に更新
	prevTime = currentTime;

}

void TimeManager::Render() {
#if _DEBUG
	DrawFormatString(500, 0, red, "%02d:%02d:%03d", m, s, ms);
	DrawFormatString(500, 20, red, "FPS:%.0f", 1.0f / deltaTime);
#endif
}
