#pragma once
#include "../Definition.h"

class GameObject {
public:
	int x, y;			//座標
	bool isVisible;		//可視状態
	std::string tag;	//タグ

public:		//コンストラクタとデストラクタ
	GameObject(int _x, int _y, std::string _tag);

	~GameObject();

public:		//メンバ関数
	virtual void Start() = 0;
	virtual void Update();
	virtual void Render() = 0;

public:		//GetterとSetter

	/*
	 *	@function	IsVisible
	 *  @brief		表示フラグの取得
	 *  @return		bool
	 */
	inline bool IsVisible() const { return isVisible; }

	/*
	 *	@function	SetVisible
	 *  @brief		表示フラグの変更
	 *  @param[in]	bool _v	初期化する値
	 */
	inline void SetVisible(bool _v) { isVisible = _v; }

	/*
	 *	@function		GetTag
	 *  @brief			タグの取得
	 *  @return			std::string
	 */
	inline std::string GetTag() const { return tag; }

	/*
	 *	@function		SetTag
	 *  @brief			タグの変更
	 *  @param[in]		std::string
	 */
	inline void SetTag(std::string _tag) { tag = _tag; }
};

