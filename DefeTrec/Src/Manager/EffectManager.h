#pragma once
#include "../Definition.h"

class EffectManager {
#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static EffectManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	EffectManager();

	/*
	 *	@brief	デストラクタ
	 */
	~EffectManager();

public:	//コピー、譲渡を禁止

	EffectManager(const EffectManager&) = delete;
	EffectManager(EffectManager&&) = delete;
	EffectManager& operator = (const EffectManager&) = delete;
	EffectManager& operator = (EffectManager&&) = delete;

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
	static EffectManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion
protected:
	int Particle_png[18];		//画像読み込み

public:		//メンバ変数
	int currentFrame;
	int frameCounter;
	int frameDelay;

	int effectX;
	int effectY;

public:		//メンバ関数

	void Update();

	void Render();

	void WhenDied(int _x, int _y);

public:		//GetterとSetter


};

