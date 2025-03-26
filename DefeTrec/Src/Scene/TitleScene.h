#pragma once
#include "BaseScene.h"


class TitleScene : public BaseScene {
public:		//�R���X�g���N�^�ƃf�X�g���N�^
	TitleScene();
	~TitleScene();


protected:		//�����o�ϐ�
	int TitleFont;
	int DefFont;
	int count;
	int num = 0;

	int bgm;

public:			//�����o�֐�
	/*
	 *	@function	Start
	 *  @brief		����������
	 */
	void Start() override;

	/*
	 *	@function	Update
	 *  @brief		�X�V����
	 */
	void Update() override;

	/*
	 *	@function	Render
	 *  @brief		�`�揈��
	 */
	void Render() override;

	void ResetScene() override;
};