#include "AudioManager.h"
#include "../GameObject/Audio/Audio.h"

#pragma region シングルトン

//静的メンバ変数の初期化
AudioManager* AudioManager::pInstance = nullptr;

AudioManager::AudioManager()
	: audioResouceMap()
	, pAudioList() {

}

AudioManager::~AudioManager() {
	for (auto itr : audioResouceMap) {
		DeleteSoundMem(itr.second);
	}
	audioResouceMap.clear();

	for (auto pA : pAudioList) {
		if (pA != nullptr) {
			delete pA;
			pA = nullptr;
		}
	}
}

void AudioManager::CreateInstance() {
	pInstance = new AudioManager();
}

AudioManager* AudioManager::GetInstance() {
	if (pInstance == nullptr) CreateInstance();
	return pInstance;
}

void AudioManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}
#pragma endregion

void AudioManager::Load(std::string _filePath, std::string _name) {
	//読み込み
	int res = LoadSoundMem(_filePath.c_str());

	//連想配列の中に既に登録されているファイルか検索する
	auto itr = audioResouceMap.find(_filePath.c_str());

	if (itr == audioResouceMap.end()) {
		//登録
		audioResouceMap.emplace(_name.c_str(), res);
	}
}

void AudioManager::ChangeVolume(std::string _name, float _volume) {
	if (_name == "All") {
		for (auto pA : pAudioList) {
			//すべての音量の変更
			pA->SetVolume(_volume);
		}
	}
	else {
		for (auto pA : pAudioList) {
			//一部の音量の変更
			if (pA->GetTag() == _name) {
				pA->SetVolume(_volume);
			}
		}
	}

}

void AudioManager::PlayOneShot(std::string _name, float _volume) {
	Audio* pAudioObj = new Audio(DuplicateSoundMem(audioResouceMap[_name]));
	pAudioObj->SetTag(_name);
	pAudioObj->Start();
	pAudioList.push_back(pAudioObj);
}

void AudioManager::PlayClipAtPoint(std::string _name, float _volume, bool _loop) {
	Audio* pAudioObj = new Audio(DuplicateSoundMem(audioResouceMap[_name]));
	pAudioObj->SetTag(_name);
	pAudioObj->SetLoop(_loop);
	pAudioObj->Start();
	pAudioList.push_back(pAudioObj);
}

void AudioManager::Stop(std::string _name) {
	if (_name == "All") {
		for (auto pA : pAudioList) {
			//すべての音量の変更
			StopSoundMem(pA->GetSoundHandle());
		}
	}
	else {
		for (auto pA : pAudioList) {
			//一部の音量の変更
			if (pA->GetTag() == _name) {
				StopSoundMem(pA->GetSoundHandle());
			}
		}
	}
}

void AudioManager::Update() {
	for (auto pA : pAudioList) {
		if (pA == nullptr || !pA->IsVisible())
			continue;

		pA->Update();
	}

	std::erase_if(
		pAudioList,
		[](Audio* _pA) {return !_pA->IsVisible(); }
	);
}
