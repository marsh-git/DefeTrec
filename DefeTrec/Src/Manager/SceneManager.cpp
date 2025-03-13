#include "SceneManager.h"
#include "../Scene/GameScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/ResultScene.h"
#include "FadeManager.h"

#pragma region シングルトン

//静的メンバ変数の初期化
SceneManager* SceneManager::pInstance = nullptr;

SceneManager::SceneManager()
	:pCurrentScene(nullptr)
	, next(SceneType::Title)
	, current((SceneType)INVALID)
	, changed(true) {
	//遷移先のシーンを生成する
	switch (next) {
	case SceneType::Title:
		pCurrentScene = new TitleScene();
		break;
	case SceneType::Game:
		pCurrentScene = new GameScene();
		break;
	case SceneType::Result:
		pCurrentScene = new ResultScene();
		break;
	default:
		pCurrentScene = nullptr;
		break;
	}


}

SceneManager::~SceneManager() {
}

void SceneManager::CreateInstance() {
	pInstance = new SceneManager();
}

SceneManager* SceneManager::GetInstance() {
	if (pInstance == nullptr) CreateInstance();
	return pInstance;
}

void SceneManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

#pragma endregion

void SceneManager::Update() {
	//フェード処理が終了していなければ更新しない
	if (FadeManager::GetInstance()->GetFadeState() != FadeState::FadeEnd)
		return;

	//シーンの切り替えの最初の1回だけフェード処理を行う
	if (changed) {
		changed = false;
		FadeManager::GetInstance()->FadeOut();
	}


	//シーンがなければ更新しない
	if (pCurrentScene == nullptr)
		return;

	//現在のシーンを更新
	pCurrentScene->Update();

	//シーンの切り替えがあれば遷移を行う
	if (current != next)
		LoadScene();
}

void SceneManager::Render() {
	//フェード処理が終了していなければ更新しない
	//※Fade中にちら見せする場合は記述しない
	if (FadeManager::GetInstance()->GetFadeState() != FadeState::FadeEnd)
		return;

	//シーンがなければ描画しない
	if (pCurrentScene == nullptr)
		return;

	//現在のシーンを描画
	pCurrentScene->Render();
}

void SceneManager::LoadScene() {

	//現在のシーン番号を書き換える
	current = next;

	//現在のシーンを削除
	delete pCurrentScene;
	pCurrentScene = nullptr;

	//次のシーンを生成する
	switch (next) {
	case SceneType::Title:
		pCurrentScene = new TitleScene();
		break;
	case SceneType::Game:
		pCurrentScene = new GameScene();
		break;
	case SceneType::Result:
		pCurrentScene = new ResultScene();
		break;
	default:
		pCurrentScene = nullptr;
		break;
	}
}

void SceneManager::SetNext(SceneType _next) {
	next = _next;
	changed = true;

	//シーン切り替えに向けてフェード処理を開始
	FadeManager::GetInstance()->FadeIn();
}

