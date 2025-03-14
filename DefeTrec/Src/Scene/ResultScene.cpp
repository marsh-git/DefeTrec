#include "ResultScene.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/FadeManager.h"
#include "../Scene/GameScene.h"
#include <DxLib.h>

ResultScene::ResultScene()
	:ResultFont(NULL)
	, DefFont(NULL)
	, count(0) {
	Start();
}

ResultScene::~ResultScene() {
	DeleteFontToHandle(ResultFont);
	DeleteFontToHandle(DefFont);
}

void ResultScene::Start() {
	ResultFont = CreateFontToHandle("Magneto", 200, 5);
	DefFont = CreateFontToHandle("Magneto", 100, 5);
}

void ResultScene::Update() {
	if (InputManager::GetInstance()->IsKeyDown(KEY_INPUT_SPACE)) {
		FadeManager::GetInstance()->FadeIn();
		//StopSoundFile();
		GameScene gameScene;
		gameScene.ResetScene();
		SceneManager::GetInstance()->SetNext(SceneType::Game);
	}

	//0以下の時は増やす		255以上の時は減らす
	if (count >= 255)
		num = -7;
	else if (count <= 0)
		num = 7;
	count += num;
}

void ResultScene::Render() {
	//タイトル

	DrawStringToHandle(150, 200, "GameOver", black, ResultFont);


	// 描画色と透明度の設定		この間にはさんだのは透明度を変化させられる
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count); 

	//スタート
	DrawStringToHandle(300, 700, "Space to Retry", black, DefFont);

	// ブレンドモードのリセット
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ResultScene::ResetScene() {
	count = 0;
}
