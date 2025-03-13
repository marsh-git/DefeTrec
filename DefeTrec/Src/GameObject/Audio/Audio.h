#pragma once
#include "../GameObject.h"

/*
 *	@brief�@�����I�u�W�F�N�g
 */

class Audio : public GameObject {
private:	//�����o�ϐ�
	bool isLoop;			//���[�v���邩�ǂ���
	int soundHandle;		//���̃n���h��
	float volume;			//����
	float distance;			//��������͈�

public:		//�R���X�g���N�^�ƃf�X�g���N�^
	/*
	 *  @brief		�R���X�g���N�^
	 *	@param[in]	int _soundHandle	���n���h��
	 *	@param[in]	bool _is3D = false	3D�������ǂ���
	 */
	Audio(int _soundHandle);

	/*
	 *  @brief		�f�X�g���N�^
	 */
	~Audio();

public:		//�I�[�o�[���C�h���������o�֐�
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

public:		//�����o�֐�

public:		//Getter��Setter

	/*
	 *	@function	GetSoundHandle
	 *  @brief		���n���h���̎擾
	 *	@return		int
	 */
	inline int GetSoundHandle() const { return soundHandle; }

	/*
	 *	@function	SetLoop
	 *  @brief		���[�v�Đ��̕ύX
	 *	@param[in]	bool _v
	 */
	inline void SetLoop(bool _v) { isLoop = _v; }

	/*
	 *	@function	SetVolume
	 *  @brief		���ʂ̕ύX
	 *	@param[in]	float _v
	 */
	inline void SetVolume(float _v) { volume = _v; }
};

