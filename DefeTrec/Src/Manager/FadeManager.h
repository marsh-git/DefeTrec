#pragma once
#include "../Definition.h"


class FadeManager {

#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static FadeManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	FadeManager();

	/*
	 *	@brief	デストラクタ
	 */
	~FadeManager();

public:	//コピー、譲渡を禁止

	FadeManager(const FadeManager&) = delete;
	FadeManager(FadeManager&&) = delete;
	FadeManager& operator = (const FadeManager&) = delete;
	FadeManager& operator = (FadeManager&&) = delete;

private:	//静的メンバ関数
	/*
	 *	@function	CreateInstance
	 *	@brief		自身のインスタンスを生成
	 *	@return		FadeManager*
	 */
	static void CreateInstance();

public:		//静的メンバ関数
	/*
	 *	@function	GetInstance
	 *	@brief		自身のインスタンスを取得する唯一の手段
	 *	@return		CollisionManager*	自身のインスタンスのアドレス
	 */
	static FadeManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion

private:		//メンバ変数
	float blend;		//ブレンドパラメータ 0~255, 0:透明 255:不透明
	float time;			//経過時間

	FadeState fadeState;	//フェードの状態


public:			//メンバ関数
	/*
	 *	@function	Update
	 *  @brief		更新処理
	 */
	void Update();

	/*
	 *	@function	Render
	 *  @brief		描画処理
	 *  @tips		純粋仮想関数で実装
	 */
	void Render();

	/*
	 *	@function	FadeIn
	 *  @brief		フェードイン
	 *  @param[in]	float _t = 1.0f		全体時間
	 */
	void FadeIn(float _t = 1.0f);

	/*
	 *	@function	FadeOut
	 *  @brief		フェードアウト
	 *  @param[in]	float _t = 1.0f		全体時間
	 */
	void FadeOut(float _t = 1.0f);

public:			//GetterとSetter

	/*
	 *	@function	GetFadeState
	 *  @brief		フェード状態の取得
	 *  @return		FadeState
	 */
	inline FadeState GetFadeState() const { return fadeState; }

};

