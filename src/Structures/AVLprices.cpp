#include "Structures/AVLprices.h"

#include <iostream>

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::destroyTree(AVLNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::getHeight(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

int AVLTree::compare(const RidePricingData& a, const RidePricingData& b) const {
    if (a.time != b.time) return a.time - b.time;
    if (a.traffic != b.traffic) return a.traffic - b.traffic;
    return a.demand - b.demand;
}

AVLNode* AVLTree::insert(AVLNode* node, RidePricingData data) {
    if (!node) return new AVLNode(data);
    int cmp = compare(data, node->data);
    if (cmp < 0)
        node->left = insert(node->left, data);
    else if (cmp > 0)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && compare(data, node->left->data) < 0) return rightRotate(node);
    if (balance < -1 && compare(data, node->right->data) > 0) return leftRotate(node);
    if (balance > 1 && compare(data, node->left->data) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && compare(data, node->right->data) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVLTree::insert(RidePricingData data) {
    root = insert(root, data);
}

AVLNode* AVLTree::minValueNode(AVLNode* node) const {
    AVLNode* current = node;
    while (current->left) current = current->left;
    return current;
}

AVLNode* AVLTree::remove(AVLNode* node, RidePricingData data) {
    if (!node) return node;
    int cmp = compare(data, node->data);
    if (cmp < 0)
        node->left = remove(node->left, data);
    else if (cmp > 0)
        node->right = remove(node->right, data);
    else {
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else
                *node = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
    }
    if (!node) return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVLTree::remove(RidePricingData data) {
    root = remove(root, data);
}

AVLNode* AVLTree::search(int time, int traffic, int demand) const {
    AVLNode* current = root;
    RidePricingData target(time, traffic, demand, 0.0);
    while (current) {
        int cmp = compare(target, current->data);
        if (cmp == 0)
            return current;
        else if (cmp < 0)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

void AVLTree::printInOrder(AVLNode* node) const {
    if (node) {
        printInOrder(node->left);
        std::cout << "Time: " << node->data.time << ", Traffic: " << node->data.traffic
                  << ", Demand: " << node->data.demand << ", Price: " << node->data.price << std::endl;
        printInOrder(node->right);
    }
}

void AVLTree::printInOrder() const {
    printInOrder(root);
    std::cout << std::endl;
}