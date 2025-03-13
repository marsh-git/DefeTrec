#include "GameObject.h"

GameObject::GameObject(int _x, int _y, std::string _tag = "")
	: x(_x)
	, y(_y)
	, isVisible(true)
	, tag(_tag) {
}

GameObject::~GameObject() {
}

void GameObject::Start() {
}

void GameObject::Update() {

}

void GameObject::Render() {
}
