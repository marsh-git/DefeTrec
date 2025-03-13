#include "GameScene.h"
#include "../Definition.h"
#include "../Manager/InputManager.h"
#include "../Manager/MapManager.h"
#include "../Manager/CharacterManager.h"
#include "../Manager/FadeManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/FloorManager.h"
#include "../Src/GameObject/Character/Enemy/EnemySpawner.h"

GameScene::GameScene() {
	Start();
}

GameScene::~GameScene() {
	// リソースの解放やクリーンアップ処理をここに追加
	delete player;
}

void GameScene::Start() {
	PlaySoundFile("Res/Bgm/GameScene.ogg", DX_PLAYTYPE_LOOP);
	//モデルや画像の読み込み

	//各種インスタンス化
	// マップ生成スクリプトの初期化
	MapManager* mapManager = MapManager::GetInstance();

	// フロアマネージャーの初期化
	FloorManager* floorMng = FloorManager::GetInstance();

	// キャラクターマネージャーの初期化
	CharacterManager* charMng = CharacterManager::GetInstance();

	// プレイヤーの初期化 X,Y,hp,攻撃力, 表示
	player = new Player(7 * TILE_SIZE, 7 * TILE_SIZE, 3, 1);
	pGameObjectArray.push_back(player);

}

void GameScene::Update() {
	if (player->hp <= 0 && InputManager::GetInstance()->IsKeyDown(KEY_INPUT_SPACE)) {
		FadeManager::GetInstance()->FadeIn();
		SceneManager::GetInstance()->SetNext(SceneType::Result);
	}

	//範囲for文	配列やコンテナの要素全てを繰り返す
	//for(1つの型 別名：配列、コンテナ){ 処理 }
	//auto型 型推論 -> 右辺の値から型を作ってくれる。
	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Update();
	}

	// マップの更新
	MapManager::GetInstance()->Update();

	// 配列の要素をすべて更新
	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Update();
	}

	// プレイヤーの移動
	player->Move(FloorManager::GetInstance()->MapRand);

	// 敵の更新
	for (Slime* enemy : CharacterManager::GetInstance()->enemies) {
		enemy->Update();
		enemy->Move(FloorManager::GetInstance()->MapRand);
	}
}

void GameScene::Render() {

	//LoadGraphScreen(960, 0, "Res/UI/UIBackGround.jpeg",FALSE);

	// マップの描画
	MapManager::GetInstance()->Render(FloorManager::GetInstance()->MapRand);

	// 配列の要素をすべて描画
	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Render();
	}

	// 敵キャラクターの描画
	for (Slime* enemy : CharacterManager::GetInstance()->enemies) {
		enemy->Render();
	}
}
