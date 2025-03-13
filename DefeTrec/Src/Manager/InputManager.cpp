#include "InputManager.h"
#include <DxLib.h>

#pragma region �V���O���g��
//�ÓI�����o�ϐ��̏�����
InputManager* InputManager::pInstance = nullptr;

/*
 *	@brief	�R���X�g���N�^
 */
InputManager::InputManager() 
	:keyState()
	,prevKeyState() {

}

/*
 *	@function	CreateInstance
 *	@brief		���g�̃C���X�^���X�𐶐�
 *	@return		InputManager*
 */
void InputManager::CreateInstance() {
	pInstance = new InputManager();
}

/*
 *	@function	GetInstance
 *	@brief		���g�̃C���X�^���X���擾����B��̎�i
 *	@return		InputManager*	���g�̃C���X�^���X�̃A�h���X
 *  @tips		�����͈�x����
 */
InputManager* InputManager::GetInstance() {
	
	if(pInstance == nullptr) CreateInstance();

	return pInstance;
}

/*
 *	@function	DestroyInstance
 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
 */
void InputManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

/*
 * @function	Update
 * @brief		�X�V����
 */
void InputManager::Update() {
	//1F�O�̃L�[�̏�Ԃ�ۑ�
	memcpy_s(prevKeyState, 256, keyState, 256);
	//���̃t���[���̏�Ԃ��擾
	GetHitKeyStateAll(keyState);
}
#pragma endregion