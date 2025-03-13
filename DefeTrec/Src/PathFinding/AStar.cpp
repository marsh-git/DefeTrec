#include "AStar.h"
#include <queue>
#include <cmath>
#include <algorithm>

// A*�A���S���Y�������s����֐�
std::vector<Node> AStar::FindPath(int startX, int startY, int goalX, int goalY, const int map[MAP_HEIGHT][MAP_WIDTH]) {
    // �I�[�v�����X�g (�D��x�L���[)
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    // �N���[�Y�h���X�g (�T���ς݃m�[�h�̃��X�g)
    std::vector<Node> closedList;
    // �J�n�m�[�h���I�[�v�����X�g�ɒǉ�
    openList.emplace(startX, startY, 0, std::abs(goalX - startX) + std::abs(goalY - startY));

    // �I�[�v�����X�g����ɂȂ�܂Ń��[�v
    while (!openList.empty()) {
        // �I�[�v�����X�g�̍ŏ�f�l�m�[�h���擾
        Node current = openList.top();
        openList.pop();

        // �ڕW�m�[�h�ɓ��B�����ꍇ�A�p�X�𐶐����ĕԂ�
        if (current.x == goalX && current.y == goalY) {
            std::vector<Node> path;
            while (current.parent != nullptr) {
                path.push_back(current);
                current = *current.parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // ���݂̃m�[�h���N���[�Y�h���X�g�ɒǉ�
        closedList.push_back(current);

        // �אڃm�[�h�̕����x�N�g��
        std::vector<std::pair<int, int>> directions = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
        for (auto& dir : directions) {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;

            // �}�b�v�͈̔͊O�܂��͏�Q���̏ꍇ�̓X�L�b�v
            if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT || map[newY][newX] != 0) {
                continue;
            }

            // �V�����m�[�h�̃R�X�g���v�Z
            int newG = current.g + 1;
            int newH = std::abs(goalX - newX) + std::abs(goalY - newY);
            Node neighbor(newX, newY, newG, newH, new Node(current));

            // �אڃm�[�h���N���[�Y�h���X�g�ɂȂ��ꍇ�A�I�[�v�����X�g�ɒǉ�
            if (std::find(closedList.begin(), closedList.end(), neighbor) == closedList.end()) {
                openList.push(neighbor);
            }
        }
    }

    // �p�X��������Ȃ������ꍇ�A��̃x�N�g����Ԃ�
    return {};
}