#pragma once
#include "../Character.h"



class Slime : public Character {
private:		//メンバ変数

	int count;				//移動のためのカウンタ
	int Slime_png[21];		//画像読み込み


public:		//コンストラクタ、デストラクタ
	Slime(int startX, int startY, int Hp, int startAttackPower);
	~Slime();

public:		//メンバ関数
	//スタート
	void Start();
	//アップデート
	void Update() override;
	//描画
	void Render() override;
	//移動
	void Move(int _mapData[MAP_HEIGHT][MAP_WIDTH]) override;
	//被弾時
	void TakeDamage(int damage) override;
	//死亡
	void Die() override;
	//アニメーション
	void Anim() override;
	//移動時のアニメーション
	bool MovingAnim() override;
};

