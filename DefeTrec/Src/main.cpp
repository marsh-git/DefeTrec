//=================================================
//	ヘッダーをインクルード
//=================================================
#include<DxLib.h>
#include "Definition.h"
#include "Manager/SceneManager.h"
#include "Manager/TimeManager.h"
#include "Manager/InputManager.h"
#include "Manager/FadeManager.h"
#include "Manager/AudioManager.h"

//=================================================
//	関数を宣言、定義
//=================================================
/*
 * @brief		Windowプログラムのエントリーポイント
 * @param[in]	HINSTANSE	今回は不要
 * @param[in]	HINSTANSE	今回は不要
 * @param[in]	LPSTR		今回は不要
 * @param[in]	int			今回は不要
 * @return		int			今回は不要
 * @tips		WINAPI		今回は不要
 */
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//=================================================
	//	DxLibの初期化処理、理解するまでは触るな
	//=================================================
	//ウィンドウのサイズを変更する
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, FPS);
	//起動時のウィンドウモードの設定
	ChangeWindowMode(true);		//真→Windowモード、偽→Fullスクリーン
	//背景色
	SetBackgroundColor(196, 196, 196);
	SetWindowIconID(333);
	SetWindowText("DefeTrec");
	//DxLibの初期化
	if (DxLib_Init() == -1) {
		return 0;
	}

	//描画先を設定	裏に設定
	SetDrawScreen(DX_SCREEN_BACK);

	//図形描画Zバッファの有効化
	{
		//Zバッファを使用するか：デフォルトはFALSE
		SetUseZBuffer3D(TRUE);
		//Zバッファに書き込むか：デフォルトはFALSE
		SetWriteZBuffer3D(TRUE);
	}

	//ライティング
	{
		//ライトの計算をするか：デフォルトはTRUE
		SetUseLighting(FALSE);
		//標準ライトを使うか：デフォルトはTRUE
		SetLightEnable(FALSE);
	}

	//=================================================
	//	ゲームの初期化処理
	//=================================================
	//FPS調整用
	int time;

	
	//=================================================
	//	ゲームのメインループ
	//=================================================
	while (1) {
		//ウィンドウのメッセージを処理する
		if (ProcessMessage() == -1) break;

		//FPSの調整
		time = GetNowCount();
		//=================================================
		//	マネージャーの更新処理
		//=================================================

		//タイムマネージャーの更新
		TimeManager::GetInstance()->Update();
		//入力管理の更新
		InputManager::GetInstance()->Update();

		//=================================================
		//	ゲームの更新処理
		//=================================================

		//escが押されたらゲームを閉じる
		if (CheckHitKey(KEY_INPUT_ESCAPE))
			break;

		//画面遷移の更新
		FadeManager::GetInstance()->Update();
		// ゲームの描画処理
		SceneManager::GetInstance()->Update();
		//音源の更新
		AudioManager::GetInstance()->Update();

		//画面クリア
		ClearDrawScreen();

		//=================================================
		//	ゲームの描画処理、描画順注意
		//=================================================

		//画面遷移の描画
		FadeManager::GetInstance()->Render();
		//ゲームの描画
		SceneManager::GetInstance()->Render();


		//裏画面と表画面の入れ替え
		ScreenFlip();

		//処理が速すぎるときに待つ
		while (1) {
			if (GetNowCount() - time >= 1000 / FPS) break;
		}
	}
	//=================================================
	//	ゲームの解放処理
	//=================================================
	
	// ゲームの解放処理
	SceneManager::DestroyInstance();
	TimeManager::DestroyInstance();
	InputManager::DestroyInstance();
	FadeManager::DestroyInstance();
	AudioManager::DestroyInstance();

	//=================================================
	//	DxLibの解放処理
	//=================================================
	//DxLibの終了
	DxLib_End();

	return 0;
}