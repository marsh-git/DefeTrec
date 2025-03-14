#pragma once
#include "../GameObject/GameObject.h"
#include <vector>

/*
 *	@brief	�V�[�P���X
 *	@tips	���ׂẴV�[���̊��N���X
 */
class BaseScene {
protected:		//�����o�ϐ�
	std::vector<GameObject*> pGameObjectArray;

public:			//�R���X�g���N�^�ƃf�X�g���N�^		

	BaseScene() = default;
	virtual ~BaseScene() {
		//���I�m�ۂ����C���X�^���X�̉��
		/*for (auto pObj : pGameObjectArray) {
			delete pObj;
			pObj = nullptr;
		}*/
	}

public:		//�����o�֐�
	/*
	 *	@function	Start
	 *  @brief		����������
	 *  @tips		�������z�֐��Ŏ���
	 */
	virtual void Start() = 0;

	/*
	 *	@function	Update
	 *  @brief		�X�V����
	 */
	virtual void Update() = 0;

	/*
	 *	@function	Render
	 *  @brief		�`�揈��
	 *  @tips		�������z�֐��Ŏ���
	 */
	virtual void Render() = 0;

	//�V�[���̃��Z�b�g�p�֐�
	virtual void ResetScene() = 0;

public:		//Getter��Setter
};