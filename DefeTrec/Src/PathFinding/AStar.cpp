#include "AStar.h"
#include <queue>
#include <cmath>
#include <algorithm>

// A*アルゴリズムを実行する関数
std::vector<Node> AStar::FindPath(int startX, int startY, int goalX, int goalY, const int map[MAP_HEIGHT][MAP_WIDTH]) {
    // オープンリスト (優先度キュー)
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
    // クローズドリスト (探索済みノードのリスト)
    std::vector<Node> closedList;
    // 開始ノードをオープンリストに追加
    openList.emplace(startX, startY, 0, std::abs(goalX - startX) + std::abs(goalY - startY));

    // オープンリストが空になるまでループ
    while (!openList.empty()) {
        // オープンリストの最小f値ノードを取得
        Node current = openList.top();
        openList.pop();

        // 目標ノードに到達した場合、パスを生成して返す
        if (current.x == goalX && current.y == goalY) {
            std::vector<Node> path;
            while (current.parent != nullptr) {
                path.push_back(current);
                current = *current.parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // 現在のノードをクローズドリストに追加
        closedList.push_back(current);

        // 隣接ノードの方向ベクトル
        std::vector<std::pair<int, int>> directions = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
        for (auto& dir : directions) {
            int newX = current.x + dir.first;
            int newY = current.y + dir.second;

            // マップの範囲外または障害物の場合はスキップ
            if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT || map[newY][newX] != 0) {
                continue;
            }

            // 新しいノードのコストを計算
            int newG = current.g + 1;
            int newH = std::abs(goalX - newX) + std::abs(goalY - newY);
            Node neighbor(newX, newY, newG, newH, new Node(current));

            // 隣接ノードがクローズドリストにない場合、オープンリストに追加
            if (std::find(closedList.begin(), closedList.end(), neighbor) == closedList.end()) {
                openList.push(neighbor);
            }
        }
    }

    // パスが見つからなかった場合、空のベクトルを返す
    return {};
}