#include "InputManager.h"
#include <DxLib.h>

#pragma region シングルトン
//静的メンバ変数の初期化
InputManager* InputManager::pInstance = nullptr;

/*
 *	@brief	コンストラクタ
 */
InputManager::InputManager() 
	:keyState()
	,prevKeyState() {

}

/*
 *	@function	CreateInstance
 *	@brief		自身のインスタンスを生成
 *	@return		InputManager*
 */
void InputManager::CreateInstance() {
	pInstance = new InputManager();
}

/*
 *	@function	GetInstance
 *	@brief		自身のインスタンスを取得する唯一の手段
 *	@return		InputManager*	自身のインスタンスのアドレス
 *  @tips		生成は一度だけ
 */
InputManager* InputManager::GetInstance() {
	
	if(pInstance == nullptr) CreateInstance();

	return pInstance;
}

/*
 *	@function	DestroyInstance
 *	@brief		自身のインスタンスを削除する唯一の手段
 */
void InputManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

/*
 * @function	Update
 * @brief		更新処理
 */
void InputManager::Update() {
	//1F前のキーの状態を保存
	memcpy_s(prevKeyState, 256, keyState, 256);
	//今のフレームの状態を取得
	GetHitKeyStateAll(keyState);
}
#pragma endregion