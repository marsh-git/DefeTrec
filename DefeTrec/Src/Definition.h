#pragma once
//	=================================================================
//		[1]	ヘッダーをインクルードする場所
//	=================================================================
#include <DxLib.h>
#include <string>

//	=================================================================
//		[2]	マクロを定義する場所
//	=================================================================
#define WINDOW_WIDTH			(1440)	//	ウィンドウの横幅	960
#define WINDOW_HEIGHT			(960)	//	ウィンドウの縦幅	960

#define FPS						(120)	//	FPS

#define TILE_SIZE				(64)	//	マップ１マス当たりの大きさ
#define	MAP_WIDTH				(15)	//	マップの幅
#define	MAP_HEIGHT				(15)	//	マップの高さ

//	引数付きマクロ定義	変換マクロ
#define Deg2Rad(x) ( x * DX_PI_F / 180.0f )	//デグリー->ラジアン
#define Rad2Deg(x) ( x * 180.0f / DX_PI_F )	//ラジアン->デグリー

//ワールドベクトル
#define VRight		(VGet(1.0f,0.0f,0.0f))	//右
#define VLeft		(VGet(-1.0f,0.0f,0.0f))	//左
#define VUp			(VGet(0.0f,1.0f,0.0f))	//上
#define VDown		(VGet(0.0f,-1.0f,0.0f))	//下
#define VForward	(VGet(0.0f,0.0f,1.0f))	//前
#define VBack		(VGet(0.0f,0.0f,-1.0f))	//後

//零ベクトル
#define VZero		(VGet(0.0f,0.0f,0.0f))
//一ベクトル
#define VOne		(VGet(1.0f,1.0f,1.0f))

//DxLibの読み込みエラー
#define INVALID		(-1)


//	=================================================================
//		[2]	定数を定義する場所
//	=================================================================
//	色
const unsigned int red = GetColor(255, 0, 0);
const unsigned int green = GetColor(0, 255, 0);
const unsigned int blue = GetColor(0, 0, 255);
const unsigned int magenta = GetColor(255, 0, 255);
const unsigned int cyan = GetColor(0, 255, 255);
const unsigned int yellow = GetColor(255, 255, 0);
const unsigned int white = GetColor(255, 255, 255);
const unsigned int black = GetColor(0, 0, 0);
const unsigned int gray = GetColor(128, 128, 128);

//	=================================================================
//		[3]	列挙定数を定義する場所	
//	=================================================================

enum class SceneType {
	Title,
	Game,
	Result,
};

enum class FadeState {
	FadeIn,
	FadeOut,
	FadeEnd,

};