#pragma once
#include <vector>
#include "../Definition.h"

//ノードの作成
struct Node {
    int x, y;       //ノードの座標
    int g, h;       //開始地点からのコスト、ヒューリスティックコスト
    Node* parent;   //親ノードへのポインタ

    //コンストラクタ
    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {
    }

    //f値を計算する関数
    int f() const { return g + h; }

    //ノードの比較演算子 優先度を出すときに使う
    bool operator>(const Node& other) const {
        return f() > other.f();
    }
    //ノードの投下比較
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

//A*アルゴリズムを実行するクラス
class AStar {
public:
    //パスを見つける関数
    std::vector<Node> 
        FindPath(int startX, int startY, int goalX, int goalY,
                    const int map[MAP_HEIGHT][MAP_WIDTH]);
};