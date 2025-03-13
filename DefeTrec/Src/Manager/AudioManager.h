#pragma once
#include<string>
#include<List>
#include<map>
#include<DxLib.h>


class AudioManager {

#pragma region シングルトンのデータ構造
private:	//静的メンバ変数
	static AudioManager* pInstance;	//自身のインスタンスのアドレスを格納


private:	//コンストラクタとデストラクタ
	/*
	 *	@brief	コンストラクタ
	 *	@tips	外部で生成されないようにアクセス指定子を private にする
	 */
	AudioManager();

	/*
	 *	@brief	デストラクタ
	 */
	~AudioManager();

public:	//コピー、譲渡を禁止

	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator = (const AudioManager&) = delete;
	AudioManager& operator = (AudioManager&&) = delete;

private:	//静的メンバ関数
	/*
	 *	@function	CreateInstance
	 *	@brief		自身のインスタンスを生成
	 *	@return		AudioManager*
	 */
	static void CreateInstance();

public:		//静的メンバ関数
	/*
	 *	@function	GetInstance
	 *	@brief		自身のインスタンスを取得する唯一の手段
	 *	@return		CollisionManager*	自身のインスタンスのアドレス
	 */
	static AudioManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		自身のインスタンスを削除する唯一の手段
	 */
	static void DestroyInstance();

#pragma endregion

private:	//メンバ変数
	std::map<std::string, int>audioResouceMap;		//リソースの連想配列
	std::list<class Audio*>pAudioList;			//エフェクトの一元管理	

public:		//メンバ関数
	/*
	 *	@function	Load
	 *	@brief		エフェクト読み込み
	 *	@param[in]	std::string	_fillPath		ファイルパス
	 *	@param[in]	std::string	_name			エフェクトにつける名前
	 *	@param[in]	float _magnification = 1.0f	拡大率
	 */
	void Load(std::string _filePath, std::string _name);

	void ChangeVolume(std::string _name, float _volume);

	void PlayOneShot(std::string _name, float _volume = 1.0f);

	void PlayClipAtPoint(std::string _name, float _volume = 1.0f, bool _loop = false);

	void Stop(std::string _name);

	void Update();

};

