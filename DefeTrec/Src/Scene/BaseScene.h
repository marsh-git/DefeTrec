#pragma once
#include "../GameObject/GameObject.h"
#include <vector>

/*
 *	@brief	シーケンス
 *	@tips	すべてのシーンの基底クラス
 */
class BaseScene {
protected:		//メンバ変数
	std::vector<GameObject*> pGameObjectArray;

public:			//コンストラクタとデストラクタ		

	BaseScene() = default;
	virtual ~BaseScene() {
		//動的確保したインスタンスの解放
		/*for (auto pObj : pGameObjectArray) {
			delete pObj;
			pObj = nullptr;
		}*/
	}

public:		//メンバ関数
	/*
	 *	@function	Start
	 *  @brief		初期化処理
	 *  @tips		純粋仮想関数で実装
	 */
	virtual void Start() = 0;

	/*
	 *	@function	Update
	 *  @brief		更新処理
	 */
	virtual void Update() = 0;

	/*
	 *	@function	Render
	 *  @brief		描画処理
	 *  @tips		純粋仮想関数で実装
	 */
	virtual void Render() = 0;

	//シーンのリセット用関数
	virtual void ResetScene() = 0;

public:		//GetterとSetter
};