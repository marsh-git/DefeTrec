#pragma once
#include "../Src/GameObject/Character/Player/Player.h"


//�v���C���[�̃X�e�[�^�X���Ԃ̕`������邽�߂̃N���X
//UI�S�ʂ�S������
class UIManager {
private:
    Player* player; // �v���C���[�̎Q��

    int Heart[5];


public:     //�R���X�g���N�^�ƃf�X�g���N�^
    UIManager(Player* _player);
    ~UIManager();


public:     //�����o�֐�
    void Update();

    void Render();

    void RenderUI();

    void RenderHp(int _hp);

};

