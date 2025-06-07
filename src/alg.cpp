// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>
#include <memory>
#include <algorithm>
#include "tree.h"

PMTree::PMTree(const std::vector  <char>& elements) {
    if (elements.empty()) {
        _root = nullptr;
        final_permut = 0;
        return;
    }

    _root = std::make_shared<Node>('\0');
    final_permut = 1;

    for (size_t i = 1; i <= elements.size(); ++i) {
        final_permut *= i;
    }

    buildTree(_root, elements);
}

void PMTree::buildTree(std::shared_ptr<Node> parent,
                      const std::vector<char>& rem_elements) {
    if (rem_elements.empty()) {
        return;
    }

    for (char elem : rem_elements) {
        auto child = std::make_shared<Node>(elem);
        parent->children.push_back(child);

        std::vector<char> new_rem;
        for (char e : rem_elements) {
            if (e != elem) {
                new_rem.push_back(e);
            }
        }

        buildTree(child, new_rem);
    }
}

void collectPermutations(std::shared_ptr<PMTree::Node> node,
                        std::vector<char>& curNod,
                        std::vector<std::vector<char>>& result) {
    if (node->value != '\0') {
        curNod.push_back(node->value);
    }

    if (node->children.empty()) {
        result.push_back(curNod);
    } else {
        for (const auto& child : node->children) {
            collectPermutations(child, curNod, result);
        }
    }

    if (node->value != '\0') {
        curNod.pop_back();
    }
}

std::vector<std::vector<char>> getAllPermuts(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    if (!tree.getRoot()) {
        return result;
    }

    std::vector<char> curNod;
    collectPermutations(tree.getRoot(), curNod, result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    auto all_perms = getAllPermuts(tree);
    if (num <= 0 || static_cast<size_t>(num) > all_perms.size()) {
        return {};
    }
    return all_perms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num <= 0 || static_cast<size_t>(num) > tree.getAllPermutations()) {
        return {};
    }

    std::vector<char> result;
    auto curNod = tree.getRoot();
    num--;

    std::vector<int> indxs;
    size_t n = curNod->children.size();
    size_t div = 1;

    for (size_t i = 1; i <= n; ++i) {
        div *= i;
    }

    size_t rem = num;
    for (size_t i = n; i >= 1; --i) {
        div /= i;
        size_t index = rem / div;
        indxs.push_back(index);
        rem %= div;
    }

    curNod = tree.getRoot();
    for (int index : indxs) {
        if (index < 0 || static_cast<size_t>(index) >=
            curNod->children.size()) {
            return {};
        }
        curNod = curNod->children[index];
        result.push_back(curNod->value);
    }
    return result;
}
