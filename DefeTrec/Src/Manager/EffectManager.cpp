#include "EffectManager.h"

//静的メンバ変数の初期化
EffectManager* EffectManager::pInstance = nullptr;

EffectManager::EffectManager()
	: currentFrame(0)
	, frameCounter(0)
	, frameDelay(5)
	, effectX(-64)
	, effectY(-64) {
	LoadDivGraph("Res/Enemy/Particle.png", 18, 18, 1, 64, 64, Particle_png);
}

EffectManager::~EffectManager() {
	for (int i = 0; i < 18; i++)
		DeleteGraph(Particle_png[i]);
}

void EffectManager::CreateInstance() {
	pInstance = new EffectManager();
}

EffectManager* EffectManager::GetInstance() {

	if (pInstance == nullptr) CreateInstance();

	return pInstance;
}

void EffectManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

void EffectManager::Update() {
	frameCounter++;
	if (frameCounter >= frameDelay) {
		frameCounter = 0;
		if (currentFrame <= 18) {
			currentFrame++;
		}
	}
}

void EffectManager::Render() {
	if (currentFrame < 18) {
		DrawGraph(effectX, effectY, Particle_png[currentFrame], TRUE);
	}
}

void EffectManager::WhenDied(int _x, int _y) {
	currentFrame = 0;
	frameCounter = 0;
	// エフェクトの位置を設定
	effectX = _x;
	effectY = _y;
}