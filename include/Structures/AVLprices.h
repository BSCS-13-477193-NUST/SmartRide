#ifndef AVL_TREE_H
#define AVL_TREE_H

struct RidePricingData {
    int time;
    int traffic;
    int demand;
    double price;
    RidePricingData(int t, int tr, int d, double p) : time(t), traffic(tr), demand(d), price(p) {}
};

struct AVLNode {
    RidePricingData data;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(RidePricingData d) : data(d), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void insert(RidePricingData data);
    void remove(RidePricingData data);
    AVLNode* search(int time, int traffic, int demand) const;
    void printInOrder() const;

private:
    AVLNode* root;
    AVLNode* insert(AVLNode* node, RidePricingData data);
    AVLNode* remove(AVLNode* node, RidePricingData data);
    AVLNode* minValueNode(AVLNode* node) const;
    int getHeight(AVLNode* node) const;
    int getBalance(AVLNode* node) const;
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    void printInOrder(AVLNode* node) const;
    void destroyTree(AVLNode* node);
    int compare(const RidePricingData& a, const RidePricingData& b) const;
};

#endif // AVL_TREE_H