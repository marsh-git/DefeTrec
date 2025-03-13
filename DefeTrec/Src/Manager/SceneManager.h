#pragma once
#include "../Definition.h"
#include "../Manager/FadeManager.h"

class SceneManager {

#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static SceneManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	SceneManager();

	/*
	 *	@brief	デストラクタ
	 */
	~SceneManager();

public:	//コピー、譲渡を禁止

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator = (const SceneManager&) = delete;
	SceneManager& operator = (SceneManager&&) = delete;

private:	//静的メンバ関数
	/*
	 *	@function	CreateInstance
	 *	@brief		自身のインスタンスを生成
	 *	@return		SceneManager*
	 */
	static void CreateInstance();

public:		//静的メンバ関数
	/*
	 *	@function	GetInstance
	 *	@brief		自身のインスタンスを取得する唯一の手段
	 *	@return		CollisionManager*	自身のインスタンスのアドレス
	 */
	static SceneManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion


private:	//メンバ変数
	class BaseScene* pCurrentScene;		//現在のシーン
	SceneType current;
	SceneType next;

	bool changed;			//シーン切り替えが終了したかどうか

public:		//メンバ関数
	void Update();

	void Render();

	void LoadScene();

public:		//GetterとSetter

	void SetNext(SceneType _next);

};


