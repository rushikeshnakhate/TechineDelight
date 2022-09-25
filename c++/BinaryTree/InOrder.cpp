#include <memory>
#include <iostream>
#include <vector>
#include <stack>

template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

template<typename T1, typename T2>
T1 &operator<<(T1 &t1, T2 &t2) {
    for (auto x : t2) {
        t1 << x << " ";
    }
    t1 << std::endl;
    return t1;
}

template<typename T>
std::vector<T> PrintInOrderUsingRecurssion(std::shared_ptr<Node<T>> &root) {
    if (root != nullptr) {
        auto left = PrintInOrderUsingRecurssion(root->left);
        auto right = PrintInOrderUsingRecurssion(root->right);
        return std::vector<T>(root->data);
//        std::cout << left;
//        std::copy(right.begin(), right.end(), std::back_insert_iterator<std::vector<T>>(left));
        return left;
    }
    return std::vector<T>(0);
}

template<typename T>
std::vector<T> PrintInOrder1(std::shared_ptr<Node<T>> root) {
    auto current = root;
    std::stack<std::shared_ptr<Node<T>>> s;
    std::vector<T> result;
    while (current != nullptr || !s.empty()) {
        if (current != nullptr) {
            s.push(current);
            current = current->left;
        } else {
            current = s.top();
            s.pop();
            result.push_back(current->data);
            current = current->right;
        }
    }
    return result;
}


struct Tree {
    int data;
    Tree *left, *right;

    Tree(int data) : data(data) {}
};

std::vector<int> Print(Tree *root) {
    Tree *current = root;
    std::stack<Tree *> s;
    std::vector<int> result;
    while (!s.empty() || current != nullptr) {
        if (current != nullptr) {
            s.push(current);
            current = current->left;
        } else {
            current = s.top();
            result.push_back(current->data);
            current = current->right;
            s.pop();
        }
    }
    return result;
}

int main() {

//    Tree *root = new Tree(1);
//    root->left = new Tree(2);
//    root->right = new Tree(3);
//    root->left->left = new Tree(4);
//    root->right->right = new Tree(6);
//    root->right->left = new Tree(5);
//    root->right->left->left = new Tree(7);
//    root->right->left->left = new Tree(8);

    std::shared_ptr<Node<int>> root = std::make_unique<Node<int>>(1);
    root->left = std::make_unique<Node<int>>(2);
    root->right = std::make_unique<Node<int>>(3);
//    root->left->left = std::make_unique<Node<int>>(4);
//    root->right->left = std::make_unique<Node<int>>(5);
//    root->right->right = std::make_unique<Node<int>>(6);
//    root->right->left->right = std::make_unique<Node<int>>(8);
//    root->right->left->left = std::make_unique<Node<int>>(7);
    for (auto x: PrintInOrderUsingRecurssion(root)) {
        std::cout << x << " ";
    }
}