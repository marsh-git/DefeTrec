#pragma once


/*
 *	@brief	時間管理クラス
 *	@tips	シングルトン
 */


class TimeManager {

#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static TimeManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	TimeManager();

	/*
	 *	@brief	デストラクタ
	 */
	~TimeManager();

public:	//コピー、譲渡を禁止

	TimeManager(const TimeManager&) = delete;
	TimeManager(TimeManager&&) = delete;
	TimeManager& operator = (const TimeManager&) = delete;
	TimeManager& operator = (TimeManager&&) = delete;

private:	//静的メンバ関数
	/*
	 *	@function	CreateInstance
	 *	@brief		自身のインスタンスを生成
	 *	@return		TimeManager*
	 */
	static void CreateInstance();

public:		//静的メンバ関数
	/*
	 *	@function	GetInstance
	 *	@brief		自身のインスタンスを取得する唯一の手段
	 *	@return		CollisionManager*	自身のインスタンスのアドレス
	 */
	static TimeManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion

private:		//メンバ変数
	int prevTime, currentTime;		//１フレーム前の時間と現在の時間
	float deltaTime;				//フレーム間の経過時間

	int m, s, ms;					//分, 秒, ミリ秒

public:			//メンバ関数

	/*
	 *	@function	Start
	 *  @brief		初期化処理
	 */
	void Start();
	/*
	 *	@function	Update
	 *  @brief		更新処理
	 */
	void Update();

	/*
	 *	@function	Render
	 *  @brief		描画処理
	 */
	void Render();

public:			//GetterとSetter

	/*
	 *	@function	GetDeltaTime
	 *  @brief		フレーム間の経過時間を取得
	 */
	inline float GetDeltaTime() const { return deltaTime; }
		
};

