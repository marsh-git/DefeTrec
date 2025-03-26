#include "ResultScene.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/FadeManager.h"
#include "../Manager/CharacterManager.h"
#include "../Scene/GameScene.h"
#include <DxLib.h>

bool ResultScene::gameClear = false;

ResultScene::ResultScene()
	:ResultFont(NULL)
	, DefFont(NULL)
	, count(0){
	Start();

}

ResultScene::~ResultScene() {
	DeleteFontToHandle(ResultFont);
	DeleteFontToHandle(DefFont);
	gameClear = false;
	DeleteSoundMem(bgm);
}

void ResultScene::Start() {
	bgm = LoadSoundMem("Res/Bgm/Title_Candy.ogg");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm);
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);

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

	//0�ȉ��̎��͑��₷		255�ȏ�̎��͌��炷
	if (count >= 255)
		num = -7;
	else if (count <= 0)
		num = 7;
	count += num;
}

void ResultScene::Render() {

	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (gameClear) {
		DrawStringToHandle(125, 200, "GameClear!", black, ResultFont);
	}
	else {
		DrawStringToHandle(150, 200, "GameOver", black, ResultFont);
	}

	// �`��F�Ɠ����x�̐ݒ�		���̊Ԃɂ͂��񂾂͓̂����x��ω���������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count); 

	if (gameClear){
		DrawStringToHandle(300, 700, "Space to Restart", black, DefFont);
	}
	else {
		DrawStringToHandle(250, 700, "Space to Retry", black, DefFont);
	}

	// �u�����h���[�h�̃��Z�b�g
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ResultScene::ResetScene() {
	count = 0;
}
