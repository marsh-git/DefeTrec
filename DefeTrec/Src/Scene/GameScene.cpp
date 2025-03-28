#include "GameScene.h"
#include "../Definition.h"
#include "../Manager/InputManager.h"
#include "../Manager/MapManager.h"
#include "../Manager/CharacterManager.h"
#include "../Manager/FadeManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/FloorManager.h"
#include "../Manager/UIManager.h"
#include "../Manager/EffectManager.h"
#include "../Src/GameObject/Character/Enemy/EnemySpawner.h"

GameScene::GameScene() {
	bgm = LoadSoundMem("Res/Bgm/GameScene.ogg");
	ChangeVolumeSoundMem(255 * 20 / 100, bgm);
	if (CheckSoundMem(bgm) == false)
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
	Start();
}

GameScene::~GameScene() {
	// リソースの解放やクリーンアップ処理をここに追加
	//delete player;
	DeleteSoundMem(bgm);
}

void GameScene::Start() {
	

	//モデルや画像の読み込み
 
	// プレイヤーの初期化 X,Y,hp,攻撃力, 表示
	player = new Player(7 * TILE_SIZE, 7 * TILE_SIZE, 3, 1, 20.0f);
	pGameObjectArray.push_back(player);

	//各種インスタンス化
	// マップ生成スクリプトの初期化
	MapManager* mapManager = MapManager::GetInstance();

	// フロアマネージャーの初期化
	FloorManager* floorMng = FloorManager::GetInstance();

	// キャラクターマネージャーの初期化
	CharacterManager* charMng = CharacterManager::GetInstance();

}

void GameScene::Update() {

	//範囲for文	配列やコンテナの要素全てを繰り返す
	//for(1つの型 別名：配列、コンテナ){ 処理 }
	//auto型 型推論 -> 右辺の値から型を作ってくれる。

	// マップの更新
	MapManager::GetInstance()->Update();
	EffectManager::GetInstance()->Update();
	UIManager::GetInstance()->Update();

	// 配列の要素をすべて更新
	//for (auto pGameObject : pGameObjectArray) {
	//	pGameObject->Update();
	//}
	if (player->isVisible == true) {
		player->Update();
		// プレイヤーの移動
		player->Move(FloorManager::GetInstance()->MapRand);
	}


	// 敵の更新
	for (Slime* enemy : CharacterManager::GetInstance()->enemies) {
		enemy->Update();
		enemy->Move(FloorManager::GetInstance()->MapRand);
	}

	if (player->hp <= 0 && InputManager::GetInstance()->IsKeyDown(KEY_INPUT_SPACE)) {
		FadeManager::GetInstance()->FadeIn();
		SceneManager::GetInstance()->SetNext(SceneType::Result);
		StopSoundMem(bgm);
	}

	if (FloorManager::GetInstance()->clear == true) {
		//player->x = -64;
		//player->y = -64;
		player->Die();
		FadeManager::GetInstance()->FadeIn();
		SceneManager::GetInstance()->SetNext(SceneType::Result);
		StopSoundMem(bgm);
	}
}

void GameScene::Render() {

	//LoadGraphScreen(960, 0, "Res/UI/UIBackGround.jpeg",FALSE);

	// マップの描画
	MapManager::GetInstance()->Render(FloorManager::GetInstance()->MapRand);

	//エフェクト
	EffectManager::GetInstance()->Render();

	// 配列の要素をすべて描画
	/*for (auto pGameObject : pGameObjectArray) {
		pGameObject->Render();
	}*/

	if (player->isVisible == true) {
		player->Render();
	}

	// 敵キャラクターの描画
	for (Slime* enemy : CharacterManager::GetInstance()->enemies) {
		enemy->Render();
	}

	UIManager::GetInstance()->Render();

}

void GameScene::ResetScene() {
	Player* player = CharacterManager::GetInstance()->GetPlayer();
	if (player != nullptr)
		player->Reset();

	// 既存のゲームオブジェクトを削除
	for (auto pObj : pGameObjectArray) {
		delete pObj;
	}
	pGameObjectArray.clear();

	// 他の必要なコンポーネントを再初期化
	EnemySpawner::GetInstance()->Reset();

	// マネージャーをリセット
	CharacterManager::GetInstance()->Reset();

	// シーンを再初期化
	Start();

	FloorManager::GetInstance()->Reset();
}
