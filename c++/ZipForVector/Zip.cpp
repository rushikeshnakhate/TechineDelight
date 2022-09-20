#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct Tree {
    Tree(const T &v) : value(v), left(nullptr), right(nullptr) {}

    T value;
    Tree<T> *left;
    Tree<T> *right;
};

template<typename T>
struct Tree<T> *newTree(T data) {
    struct Tree<T> *node = new Tree<T>(data);
    node->left = node->right = NULL;
    return (node);
}


template<typename T>
bool isBST(Tree<T> *root, int min, int max) {
    if (root == NULL) {
        return true;
    }
    if (root->value < min || root->value > max) {
        return false;
    }
    return isBST(root->left, min, root->value - 1) &&
           isBST(root->right, root->value + 1, max);
}

template<typename T>
int size(Tree<T> *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + size(root->left) + size(root->right);
}

template<typename T>
int largestBST(Tree<T> *root) {
    // Current SubTree<T>is BST.
    if (isBST(root, INT_MIN, INT_MAX) == true) {
        return size(root);
    }
    // Find largest BST in left and right subtrees.
    return max(largestBST(root->left), largestBST(root->right));
}

int main() {
    struct Tree<int> *root = newTree(67);
    root->left = newTree(72);
    root->right = newTree(77);
    root->left->left = newTree(57);
    printf("Size of the largest BST is %d", largestBST(root));
    return 0;
}