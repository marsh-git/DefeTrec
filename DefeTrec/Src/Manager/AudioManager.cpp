#include "AudioManager.h"
#include "../GameObject/Audio/Audio.h"

#pragma region �V���O���g��

//�ÓI�����o�ϐ��̏�����
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
	//�ǂݍ���
	int res = LoadSoundMem(_filePath.c_str());

	//�A�z�z��̒��Ɋ��ɓo�^����Ă���t�@�C������������
	auto itr = audioResouceMap.find(_filePath.c_str());

	if (itr == audioResouceMap.end()) {
		//�o�^
		audioResouceMap.emplace(_name.c_str(), res);
	}
}

void AudioManager::ChangeVolume(std::string _name, float _volume) {
	if (_name == "All") {
		for (auto pA : pAudioList) {
			//���ׂẲ��ʂ̕ύX
			pA->SetVolume(_volume);
		}
	}
	else {
		for (auto pA : pAudioList) {
			//�ꕔ�̉��ʂ̕ύX
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
			//���ׂẲ��ʂ̕ύX
			StopSoundMem(pA->GetSoundHandle());
		}
	}
	else {
		for (auto pA : pAudioList) {
			//�ꕔ�̉��ʂ̕ύX
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
