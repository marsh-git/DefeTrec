#include "TitleScene.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/FadeManager.h"
#include <DxLib.h>

TitleScene::TitleScene()
	:TitleFont(NULL)
	, DefFont(NULL)
	, count(0) {
	Start();
}

TitleScene::~TitleScene() {
	DeleteFontToHandle(TitleFont);
	DeleteFontToHandle(DefFont);
}

void TitleScene::Start() {
	TitleFont = CreateFontToHandle("Magneto", 250, 5);
	DefFont = CreateFontToHandle("Magneto", 100, 5);
	PlaySoundFile("Res/Bgm/Title_Candy.ogg", DX_PLAYTYPE_LOOP);
}

void TitleScene::Update() {
	if (InputManager::GetInstance()->IsKeyDown(KEY_INPUT_SPACE)) {
		FadeManager::GetInstance()->FadeIn();
		SceneManager::GetInstance()->SetNext(SceneType::Game);
	}

	//0以下の時は増やす		255以上の時は減らす
	if (count >= 255)
		num = -7;
	else if (count <= 0)
		num = 7;
	count += num;
}

void TitleScene::Render() {
	//タイトル
	DrawStringToHandle(125, 200, "DefeTrec", black, TitleFont);



	// 描画色と透明度の設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count); // 透明度を128に設定（半透明）

	//スタート
	DrawStringToHandle(300, 700, "Space to Start", black, DefFont);

	// ブレンドモードのリセット
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
