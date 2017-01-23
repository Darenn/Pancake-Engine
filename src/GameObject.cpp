//
// Created by Darenn on 17/01/2017.
//

#include "../include/GameObject.hpp"

GameObject::GameObject(std::string n) {
    name = n;
    transform = new Transform();
    components = std::vector<Component *> ();
    components.push_back((Component *&&) transform);
}

GameObject::~GameObject() {
    for (int i = 0; i < components.size(); ++i) {
        delete(components[i]);
    }
}

void GameObject::awake() {
    for (int i = 0; i < components.size(); ++i) {
        components[i]->awake();
    }
}

void GameObject::start() {
    for (int i = 0; i < components.size(); ++i) {
        components[i]->start();
    }
}

void GameObject::update() {
    for (int i = 0; i < components.size(); ++i) {
        components[i]->update();
    }
}

void GameObject::lateUpdate() {
    for (int i = 0; i < components.size(); ++i) {
        components[i]->lateUpdate();
    }
}

void GameObject::addComponent(Component& c) {
    components.push_back(&c);
}