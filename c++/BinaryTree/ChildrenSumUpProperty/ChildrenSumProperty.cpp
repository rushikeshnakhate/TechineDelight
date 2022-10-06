#include <memory>
#include <iostream>

template<typename T>
struct Node {
    T data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(T data) : data(data) {}
};

template<typename T>
T PrintBinaryTree(std::unique_ptr<Node<T>> &root) {
    if (root == nullptr)
        return 0;

    if (root->left == nullptr && root->right == nullptr) {
        return root->data;
    }

    T left = PrintBinaryTree(root->left);
    T right = PrintBinaryTree(root->right);
    std::cout << left << " " << right << " " << root->data << std::endl;
    if (left + right == root->data) {
        return root->data;
    }
    return -1;
}

int main() {
    std::unique_ptr<Node<int>> root = std::make_unique<Node<int>>(25);
    root->left = std::make_unique<Node<int>>(12);
    root->right = std::make_unique<Node<int>>(13);

    root->left->left = std::make_unique<Node<int>>(7);
    root->left->right = std::make_unique<Node<int>>(5);

    root->right->left = std::make_unique<Node<int>>(6);
    root->right->right = std::make_unique<Node<int>>(10);

    std::cout << PrintBinaryTree(root) << std::endl;

    return 0;
}