#include "Audio.h"


/*
 *  @brief		コンストラクタ
 *	@param[in]	int _soundHandle	音ハンドル
 */
Audio::Audio(int _soundHandle)
	:GameObject(0, 0, "")
	, isLoop(false)
	, soundHandle(_soundHandle)
	, volume(255)
	, distance(800.0f) {
	Start();
}

/*
 *  @brief		デストラクタ
 */
Audio::~Audio() {
	DeleteSoundMem(soundHandle);
}

/*
 *	@function	Start
 *  @brief		初期化処理
 */
void Audio::Start() {
	if (isLoop)
		PlaySoundMem(soundHandle, DX_PLAYTYPE_LOOP);
	else 
		PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}

/*
 *	@function	Update
 *  @brief		更新処理
 */
void Audio::Update() {
	//非表示なら更新しない
	if (!isVisible)
		return;

	//再生中かどうか
	if (CheckSoundMem(soundHandle) == 0)
		isVisible = false;

	//音量の設定
	ChangeVolumeSoundMem((int)volume, soundHandle);
}

/*
 *	@function	Render
 *  @brief		描画処理
 */
void Audio::Render() {
}
