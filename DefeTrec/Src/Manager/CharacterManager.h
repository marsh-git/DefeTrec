#pragma once
#include "../Definition.h"
#include <vector>
#include "../Src/GameObject/Character/Enemy/Slime.h"
#include "../Src/GameObject/Character/Player/Player.h"


//キャラクターの位置を管理するクラス

class CharacterManager {
#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static CharacterManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	CharacterManager();

	/*
	 *	@brief	デストラクタ
	 */
	~CharacterManager() = default;

public:	//コピー、譲渡を禁止

	CharacterManager(const CharacterManager&) = delete;
	CharacterManager(CharacterManager&&) = delete;
	CharacterManager& operator = (const CharacterManager&) = delete;
	CharacterManager& operator = (CharacterManager&&) = delete;

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
	static CharacterManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion
protected:		//メンバ変数
	int i = 0;		//マップを生成するための変数
	int j = 0;

public:
	std::vector<Slime*> enemies;		//キャラクターのリスト
	Player* player;						//プレイヤー

public:			//キャラクター配列
	int CharacterData[MAP_HEIGHT][MAP_WIDTH] =
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
	};

public:		//メンバ関数
	//敵を追加する関数
	void AddEnemy(Slime* enemy);
	//キャラクターの削除
	void RemoveCharacter(Character* character);

public:		//GetterとSetter
	Slime* GetEnemyAtPosition(int tileX, int tileY);	//指定位置にいる敵の取得

	void SetPlayer(Player* player);	//プレイヤーの設定
	Player* GetPlayer();	//プレイヤーの取得

	std::pair<int, int> GetPlayerPosition();	//プレイヤーの位置を取得
};

