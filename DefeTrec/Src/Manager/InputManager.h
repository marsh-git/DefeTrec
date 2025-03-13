#pragma once

/*
 *	@brief	入力管理クラス
 *	@tips	管理するクラスは一つであるべき→シングルトンのデータ構造
 */
class InputManager{
#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static InputManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	InputManager();

	/*
	 *	@brief	デストラクタ
	 */
	~InputManager() = default;

public:	//コピー、譲渡を禁止

	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator = (const InputManager&) = delete;
	InputManager& operator = (InputManager&&) = delete;

private:	//静的メンバ関数
	/*
	 *	@function	CreateInstance
	 *	@brief		自身のインスタンスを生成
	 *	@return		InputManager*
	 */
	static void CreateInstance();

public:		//静的メンバ関数
	/*
	 *	@function	GetInstance
	 *	@brief		自身のインスタンスを取得する唯一の手段
	 *	@return		InputManager*	自身のインスタンスのアドレス
	 */
	static InputManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion
private:	//メンバ変数

	char keyState[256];		//現在のキーの状態
	char prevKeyState[256];	//1F前のキーの状態

public:		//メンバ関数
	/*
	 * @function	Update
	 * @brief		更新処理
	 */
	void Update();

public:		//キーボード用入力管理
	/*
	 * @function	IsKeyDown
	 * @brief		キーが押されたかどうか
	 * @param[in]	int _key	キー番号
	 * @return		bool
	 * @tips		押されていない状態→押された状態
	 */
	inline bool IsKeyDown(int _key) const {
		//	!前 && 今
		return !prevKeyState[_key] && keyState[_key];
	}

	/*
	 * @function	IsKey
	 * @brief		キーが押されているかどうか
	 * @param[in]	int _key	キー番号
	 * @return		bool
	 * @tips		押されている状態
	 */
	inline bool IsKey(int _key) const {
		//	今
		return keyState[_key];
	}

	/*
	 * @function	IsKeyUp
	 * @brief		キーが離されたかどうか
	 * @param[in]	int _key	キー番号
	 * @return		bool
	 * @tips		押された状態→押されていない状態
	 */
	inline bool IsKeyUp(int _key) const {
		//	前 && !今
		return prevKeyState[_key] && !keyState[_key];
	}
};

