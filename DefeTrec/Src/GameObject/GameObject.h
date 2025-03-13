#pragma once
#include "../Definition.h"

class GameObject {
public:
	int x, y;			//���W
	bool isVisible;		//�����
	std::string tag;	//�^�O

public:		//�R���X�g���N�^�ƃf�X�g���N�^
	GameObject(int _x, int _y, std::string _tag);

	~GameObject();

public:		//�����o�֐�
	virtual void Start() = 0;
	virtual void Update();
	virtual void Render() = 0;

public:		//Getter��Setter

	/*
	 *	@function	IsVisible
	 *  @brief		�\���t���O�̎擾
	 *  @return		bool
	 */
	inline bool IsVisible() const { return isVisible; }

	/*
	 *	@function	SetVisible
	 *  @brief		�\���t���O�̕ύX
	 *  @param[in]	bool _v	����������l
	 */
	inline void SetVisible(bool _v) { isVisible = _v; }

	/*
	 *	@function		GetTag
	 *  @brief			�^�O�̎擾
	 *  @return			std::string
	 */
	inline std::string GetTag() const { return tag; }

	/*
	 *	@function		SetTag
	 *  @brief			�^�O�̕ύX
	 *  @param[in]		std::string
	 */
	inline void SetTag(std::string _tag) { tag = _tag; }
};

