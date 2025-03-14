#pragma once
#include "MapManager.h"

class FloorManager {

#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static FloorManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	*	@brief	コンストラクタ
	*	@tips	外部で生成されないようにアクセス指定子を private にする
	*/
	FloorManager();

	/*
	*	@brief	デストラクタ
	*/
	~FloorManager() = default;

public:	//コピー、譲渡を禁止

	FloorManager(const FloorManager&) = delete;
	FloorManager(FloorManager&&) = delete;
	FloorManager& operator = (const FloorManager&) = delete;
	FloorManager& operator = (FloorManager&&) = delete;

private:	//静的メンバ関数
	/*
	*	@function	CreateInstance
	*	@brief		自身のインスタンスを生成
	*	@return		FloorManager*
	*/
	static void CreateInstance();

public:		//静的メンバ関数
	/*
	*	@function	GetInstance
	*	@brief		自身のインスタンスを取得する唯一の手段
	*	@return		InputManager*	自身のインスタンスのアドレス
	*/
	static FloorManager* GetInstance();

	/*
	*	@function	DestroyInstance
	*	@brief		自身のインスタンスを削除する唯一の手段
	*/
	static void DestroyInstance();

#pragma endregion

public:			//メンバ変数
    int MapRand[MAP_HEIGHT][MAP_WIDTH];  // マップデータ
    //int playerX, playerY;  // プレイヤーの座標

public:			//メンバ関数
    // 階層を進める処理
    void NextFloor(double wallRatio, double pathRatio, double enemyRatio);

	//リセット
	void Reset();

public:			//GetterとSetter
    // 現在のマップデータを取得
    int (*GetMapData())[MAP_WIDTH];

    // プレイヤーの座標取得
    //int GetPlayerX() const { return playerX; }
    //int GetPlayerY() const { return playerY; }
};
