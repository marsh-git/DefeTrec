#pragma once
#include "../Src/GameObject/Character/Player/Player.h"


//プレイヤーのステータスや状態の描画をするためのクラス
//UI全般を担当する
class UIManager {
#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static UIManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	UIManager();

	/*
	 *	@brief	デストラクタ
	 */
	~UIManager();

public:	//コピー、譲渡を禁止

	UIManager(const UIManager&) = delete;
	UIManager(UIManager&&) = delete;
	UIManager& operator = (const UIManager&) = delete;
	UIManager& operator = (UIManager&&) = delete;

private:	//静的メンバ関数
	/*
	 *	@function	CreateInstance
	 *	@brief		自身のインスタンスを生成
	 *	@return		CharacterManager*
	 */
	static void CreateInstance();

public:		//静的メンバ関数
	/*
	 *	@function	GetInstance
	 *	@brief		自身のインスタンスを取得する唯一の手段
	 *	@return		InputManager*	自身のインスタンスのアドレス
	 */
	static UIManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion
private:		//画像読み込み

    int HpBarSide;
    int HpBarMid;

private:		//メンバ関数
	int Font75;
	int Font40;
	int Font50;


public:     //メンバ関数
    void Update();

    void Render();

    void RenderUI();

    void RenderHp();

};

