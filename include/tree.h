// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>

class PMTree {
 public:
    PMTree(const std::vector<char>& elements);

    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;

        Node(char val) : value(val) {}
    };

    std::shared_ptr<Node> getRoot() const { return _root; }
    size_t getAllPermutations() const { return final_permut; }

 private:
    std::shared_ptr<Node> _root;
    size_t final_permut;

    void buildTree(std::shared_ptr<Node> parent,
                 const std::vector<char>& remaining_elements);
};

std::vector<std::vector<char>> getAllPermuts(const PMTree& tree);
std::vector<char> getPermut1(const PMTree& tree, int num);
std::vector<char> getPermut2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
