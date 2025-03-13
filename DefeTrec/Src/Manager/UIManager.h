#pragma once
#include "../Src/GameObject/Character/Player/Player.h"


//プレイヤーのステータスや状態の描画をするためのクラス
//UI全般を担当する
class UIManager {
private:
    Player* player; // プレイヤーの参照

    int Heart[5];


public:     //コンストラクタとデストラクタ
    UIManager(Player* _player);
    ~UIManager();


public:     //メンバ関数
    void Update();

    void Render();

    void RenderUI();

    void RenderHp(int _hp);

};

