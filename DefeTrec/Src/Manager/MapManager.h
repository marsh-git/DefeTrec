#pragma once
#include <DxLib.h>
#include <cstdlib>
#include <ctime>
#include "../Definition.h"		//マクロを使うため

/*
 *	@brief	マップ管理クラス
 */
class MapManager {
#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static MapManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	MapManager();

	/*
	 *	@brief	デストラクタ
	 */
	~MapManager() = default;

public:	//コピー、譲渡を禁止

	MapManager(const MapManager&) = delete;
	MapManager(MapManager&&) = delete;
	MapManager& operator = (const MapManager&) = delete;
	MapManager& operator = (MapManager&&) = delete;

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
	static MapManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion
protected:		//メンバ変数
	int i = 0;
	int j = 0;

	int currentFrame;
	int frameCounter;
	int  frameDelay;

private:
	int mapImage[40];
	int portalImage[6];

public:		//マップ定数
	//雛形		9:プレイヤー	1:壁	2:スライム	8:ポータル
	/* int MapData[MAP_HEIGHT][MAP_WIDTH] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};*/

	const int backGroundData[MAP_HEIGHT][MAP_WIDTH] =
	{
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0} ,
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0} ,
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0} ,
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0} ,
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0} ,
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0} ,
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0} ,
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}
	};

	int MapData[MAP_HEIGHT][MAP_WIDTH] =
	{
		{ 9, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0} ,
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1} ,
		{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0} ,
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ,
		{ 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 8, 0, 0} ,
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0} ,
		{ 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0}
	};

public:		//メンバ関数
	void Update();

	void Render(int _mapData[MAP_HEIGHT][MAP_WIDTH]);

	void DeleteImage();

	void Anim();

	static void generateRandomMap(int map[MAP_HEIGHT][MAP_WIDTH], double wallRatio, double pathRatio, double enemyRatio);

	void GeneratePortal(int _mapData[MAP_HEIGHT][MAP_WIDTH]);


};
