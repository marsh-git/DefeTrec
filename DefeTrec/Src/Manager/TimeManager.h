#pragma once


/*
 *	@brief	���ԊǗ��N���X
 *	@tips	�V���O���g��
 */


class TimeManager {

#pragma region �V���O���g���̃f�[�^�\��
private:	//�ÓI�����o�ϐ�
	static TimeManager* pInstance;	//���g�̃C���X�^���X�̃A�h���X���i�[


private:	//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *	@brief	�R���X�g���N�^
	 *	@tips	�O���Ő�������Ȃ��悤�ɃA�N�Z�X�w��q�� private �ɂ���
	 */
	TimeManager();

	/*
	 *	@brief	�f�X�g���N�^
	 */
	~TimeManager();

public:	//�R�s�[�A���n���֎~

	TimeManager(const TimeManager&) = delete;
	TimeManager(TimeManager&&) = delete;
	TimeManager& operator = (const TimeManager&) = delete;
	TimeManager& operator = (TimeManager&&) = delete;

private:	//�ÓI�����o�֐�
	/*
	 *	@function	CreateInstance
	 *	@brief		���g�̃C���X�^���X�𐶐�
	 *	@return		TimeManager*
	 */
	static void CreateInstance();

public:		//�ÓI�����o�֐�
	/*
	 *	@function	GetInstance
	 *	@brief		���g�̃C���X�^���X���擾����B��̎�i
	 *	@return		CollisionManager*	���g�̃C���X�^���X�̃A�h���X
	 */
	static TimeManager* GetInstance();

	/*
	 *	@function	DestroyInstance
	 *	@brief		���g�̃C���X�^���X���폜����B��̎�i
	 */
	static void DestroyInstance();

#pragma endregion

private:		//�����o�ϐ�
	int prevTime, currentTime;		//�P�t���[���O�̎��Ԃƌ��݂̎���
	float deltaTime;				//�t���[���Ԃ̌o�ߎ���

	int m, s, ms;					//��, �b, �~���b

public:			//�����o�֐�

	/*
	 *	@function	Start
	 *  @brief		����������
	 */
	void Start();
	/*
	 *	@function	Update
	 *  @brief		�X�V����
	 */
	void Update();

	/*
	 *	@function	Render
	 *  @brief		�`�揈��
	 */
	void Render();

public:			//Getter��Setter

	/*
	 *	@function	GetDeltaTime
	 *  @brief		�t���[���Ԃ̌o�ߎ��Ԃ��擾
	 */
	inline float GetDeltaTime() const { return deltaTime; }
		
};

