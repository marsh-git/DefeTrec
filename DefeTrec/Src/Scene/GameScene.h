#pragma once
#include "BaseScene.h"
#include "../Src/GameObject/Character/Player/Player.h"
#include "../Src/GameObject/Character/Enemy/Slime.h"


class GameScene : public BaseScene {
protected:
	Player* player;

public:
	GameScene();
	~GameScene();

public:
	void Start() override;

	void Update() override;

	void Render() override;

};

