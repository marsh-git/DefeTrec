#include "MapManager.h"
#include "FloorManager.h"


//�ÓI�����o�ϐ��̏�����
MapManager* MapManager::pInstance = nullptr;

MapManager::MapManager()
	: currentFrame(0)
	, frameCounter(0)
	, frameDelay(10) {
	LoadDivGraph("Res/Stage/map.png", 40, 6, 7, 64, 64, mapImage);
	LoadDivGraph("Res/Stage/Portal.png", 6, 3, 2, 64, 64, portalImage);
}

//�V���O���g���̃C���X�^���X�쐬
void MapManager::CreateInstance() {
	pInstance = new MapManager();
}

//�쐬�����C���X�^���X�̎擾
MapManager* MapManager::GetInstance() {

	if (pInstance == nullptr) CreateInstance();

	return pInstance;
}

//�j��
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

	// �^�C����`��
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			if (backGroundData[i][j] == 0) {
				DrawBox(j * TILE_SIZE, i * TILE_SIZE,
					j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE,
					GetColor(60, 40, 80), TRUE);
			}
		}
	}
	// �}�b�v��`��
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
	std::srand(std::time(0)); // ���݂̎��Ԃ��V�[�h�Ƃ��Ďg�p

	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			double randomValue = (double)std::rand() / RAND_MAX;
			if (randomValue < wallRatio) {
				map[i][j] = 1; // ��
			}
			else if (randomValue < wallRatio + pathRatio) {
				map[i][j] = 0; // ��
			}
			else {
				map[i][j] = 2; // �G
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
	_mapData[7][7] = 8;  // �|�[�^���𐶐�


	//// ��: �|�[�^�����}�b�v�̓���ʒu�ɐ���
	//for (int y = 0; y < MAP_HEIGHT; ++y) {
	//	for (int x = 0; x < MAP_WIDTH; ++x) {
	//		// ��: �󂫃X�y�[�X�i0�j�Ƀ|�[�^���i�Ⴆ��3�j��z�u
	//		if (_mapData[y][x] == 0) {
	//			_mapData[y][x] = 8;  // �|�[�^���𐶐�
	//			return;  // �ŏ��Ɍ������󂫃X�y�[�X�ɐ���
	//		}
	//	}
	//}
}