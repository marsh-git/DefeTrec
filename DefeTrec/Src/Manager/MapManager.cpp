#include "MapManager.h"
#include "FloorManager.h"


//静的メンバ変数の初期化
MapManager* MapManager::pInstance = nullptr;

MapManager::MapManager()
	: currentFrame(0)
	, frameCounter(0)
	, frameDelay(10) {
	LoadDivGraph("Res/Stage/map.png", 40, 6, 7, 64, 64, mapImage);
	LoadDivGraph("Res/Stage/Portal.png", 6, 3, 2, 64, 64, portalImage);
}

//シングルトンのインスタンス作成
void MapManager::CreateInstance() {
	pInstance = new MapManager();
}

//作成したインスタンスの取得
MapManager* MapManager::GetInstance() {

	if (pInstance == nullptr) CreateInstance();

	return pInstance;
}

//破壊
void MapManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}


void MapManager::Update() {
	Anim();
}

void MapManager::Render(int _mapData[MAP_HEIGHT][MAP_WIDTH]) {

	DrawBox(0, 0, 960, 960, GetColor(125, 125, 125), TRUE);

	// タイルを描く
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			if (backGroundData[i][j] == 0) {
				DrawBox(j * TILE_SIZE, i * TILE_SIZE,
					j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE,
					GetColor(60, 40, 80), TRUE);
			}
		}
	}
	// マップを描く
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			if (_mapData[i][j] == 1) {
				DrawGraph(j * TILE_SIZE, i * TILE_SIZE, mapImage[13], TRUE);
			}
			if (_mapData[i][j] == 8){
					DrawGraph(j * TILE_SIZE, i * TILE_SIZE, portalImage[currentFrame], TRUE);
			}
		}
	}
}

void MapManager::DeleteImage() {
	for (int i = 0; i < 40; i++) {
		DeleteGraph(mapImage[i]);
	}
}

void MapManager::Anim() {

	frameCounter++;
	if (frameCounter >= frameDelay) {
		frameCounter = 0;
		currentFrame++;

		if (currentFrame >= 6) {
			currentFrame = 0;
		}

	}
}

void MapManager::generateRandomMap(int map[MAP_HEIGHT][MAP_WIDTH], double wallRatio, double pathRatio, double enemyRatio) {
	std::srand(std::time(0)); // 現在の時間をシードとして使用

	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			double randomValue = (double)std::rand() / RAND_MAX;
			if (randomValue < wallRatio) {
				map[i][j] = 1; // 壁
			}
			else if (randomValue < wallRatio + pathRatio) {
				map[i][j] = 0; // 道
			}
			else {
				map[i][j] = 2; // 敵
			}
		}
	}

	map[7][7] = 0;
	map[6][7] = 0;
	map[8][7] = 0;
	map[7][6] = 0;
	map[7][8] = 0;

}

void MapManager::GeneratePortal(int _mapData[MAP_HEIGHT][MAP_WIDTH]) {
	_mapData[7][7] = 8;  // ポータルを生成


	//// 例: ポータルをマップの特定位置に生成
	//for (int y = 0; y < MAP_HEIGHT; ++y) {
	//	for (int x = 0; x < MAP_WIDTH; ++x) {
	//		// 例: 空きスペース（0）にポータル（例えば3）を配置
	//		if (_mapData[y][x] == 0) {
	//			_mapData[y][x] = 8;  // ポータルを生成
	//			return;  // 最初に見つけた空きスペースに生成
	//		}
	//	}
	//}
}