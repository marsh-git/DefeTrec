#pragma once
#include "../Src/Manager/CharacterManager.h"
#include "../Src/Manager/MapManager.h"
#include "Slime.h"


class EnemySpawner {
#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static EnemySpawner* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	*	@brief	コンストラクタ
	*	@tips	外部で生成されないようにアクセス指定子を private にする
	*/
	EnemySpawner();

	/*
	*	@brief	デストラクタ
	*/
	~EnemySpawner() = default;

public:	//コピー、譲渡を禁止

	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner(EnemySpawner&&) = delete;
	EnemySpawner& operator = (const EnemySpawner&) = delete;
	EnemySpawner& operator = (EnemySpawner&&) = delete;

private:	//静的メンバ関数
	/*
	*	@function	CreateInstance
	*	@brief		自身のインスタンスを生成
	*	@return		EnemySpawner*
	*/
	static void CreateInstance();

public:		//静的メンバ関数
	/*
	*	@function	GetInstance
	*	@brief		自身のインスタンスを取得する唯一の手段
	*	@return		InputManager*	自身のインスタンスのアドレス
	*/
	static EnemySpawner* GetInstance();

	/*
	*	@function	DestroyInstance
	*	@brief		自身のインスタンスを削除する唯一の手段
	*/
	static void DestroyInstance();

#pragma endregion

public:		//読み込み
	MapManager* mapManager = MapManager::GetInstance();
	CharacterManager* characterManager = CharacterManager::GetInstance();

public:		//メンバ変数
	//敵の最大数カウント
	int enemyNum = 0;

public:		//メンバ関数
	//敵を出現させる関数
	void SpawnEnemy(int _mapData[MAP_HEIGHT][MAP_WIDTH]);

	//敵を倒した時用の関数
	void EnemyDefeated();

	//リセット
	void Reset();

};

