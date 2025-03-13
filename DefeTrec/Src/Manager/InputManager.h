#pragma once

/*
 *	@brief	���͊Ǘ��N���X
 *	@tips	�Ǘ�����N���X�͈�ł���ׂ����V���O���g���̃f�[�^�\��
 */
class InputManager{
#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static InputManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *	@brief	�R���X�g���N�^
	 *	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	 */
	InputManager();

	/*
	 *	@brief	�f�X�g���N�^
	 */
	~InputManager() = default;

public:	//�R�s�[�A���n���֎~

	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator = (const InputManager&) = delete;
	InputManager& operator = (InputManager&&) = delete;

private:	//�ÓI�����o�֐�
	/*
	 *	@function	CreateInstance
	 *	@brief		���g�̃C���X�^���X�𐶐�
	 *	@return		InputManager*
	 */
	static void CreateInstance();

public:		//�ÓI�����o�֐�
	/*
	 *	@function	GetInstance
	 *	@brief		���g�̃C���X�^���X���擾����B��̎�i
	 *	@return		InputManager*	���g�̃C���X�^���X�̃A�h���X
	 */
	static InputManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
	 */
	static void DestroyInstance();

#pragma endregion
private:	//�����o�ϐ�

	char keyState[256];		//���݂̃L�[�̏��
	char prevKeyState[256];	//1F�O�̃L�[�̏��

public:		//�����o�֐�
	/*
	 * @function	Update
	 * @brief		�X�V����
	 */
	void Update();

public:		//�L�[�{�[�h�p���͊Ǘ�
	/*
	 * @function	IsKeyDown
	 * @brief		�L�[�������ꂽ���ǂ���
	 * @param[in]	int _key	�L�[�ԍ�
	 * @return		bool
	 * @tips		������Ă��Ȃ���ԁ������ꂽ���
	 */
	inline bool IsKeyDown(int _key) const {
		//	!�O && ��
		return !prevKeyState[_key] && keyState[_key];
	}

	/*
	 * @function	IsKey
	 * @brief		�L�[��������Ă��邩�ǂ���
	 * @param[in]	int _key	�L�[�ԍ�
	 * @return		bool
	 * @tips		������Ă�����
	 */
	inline bool IsKey(int _key) const {
		//	��
		return keyState[_key];
	}

	/*
	 * @function	IsKeyUp
	 * @brief		�L�[�������ꂽ���ǂ���
	 * @param[in]	int _key	�L�[�ԍ�
	 * @return		bool
	 * @tips		�����ꂽ��ԁ�������Ă��Ȃ����
	 */
	inline bool IsKeyUp(int _key) const {
		//	�O && !��
		return prevKeyState[_key] && !keyState[_key];
	}
};

