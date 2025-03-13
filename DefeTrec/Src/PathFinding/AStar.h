#pragma once
#include <vector>
#include "../Definition.h"

//�m�[�h�̍쐬
struct Node {
    int x, y;       //�m�[�h�̍��W
    int g, h;       //�J�n�n�_����̃R�X�g�A�q���[���X�e�B�b�N�R�X�g
    Node* parent;   //�e�m�[�h�ւ̃|�C���^

    //�R���X�g���N�^
    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {
    }

    //f�l���v�Z����֐�
    int f() const { return g + h; }

    //�m�[�h�̔�r���Z�q �D��x���o���Ƃ��Ɏg��
    bool operator>(const Node& other) const {
        return f() > other.f();
    }
    //�m�[�h�̓�����r
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

//A*�A���S���Y�������s����N���X
class AStar {
public:
    //�p�X��������֐�
    std::vector<Node> 
        FindPath(int startX, int startY, int goalX, int goalY,
                    const int map[MAP_HEIGHT][MAP_WIDTH]);
};