#pragma once
#include "BaseScene.h"


class ResultScene : public BaseScene {
public:		//コンストラクタとデストラクタ
	ResultScene();
	~ResultScene();


protected:		//メンバ変数
	int ResultFont;
	int DefFont;
	int count;
	int num = 0;

	int bgm;

public:			//メンバ関数
	/*
	 *	@function	Start
	 *  @brief		初期化処理
	 */
	void Start() override;

	/*
	 *	@function	Update
	 *  @brief		更新処理
	 */
	void Update() override;

	/*
	 *	@function	Render
	 *  @brief		描画処理
	 */
	void Render() override;

	void ResetScene() override;

};

