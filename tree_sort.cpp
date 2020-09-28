#include <iostream>
#include <vector>
#include "vector_print.h"

using namespace std;

template <typename Iterator>
class Tree {
private:
  struct Node {
    Node *left_child = nullptr, *right_child = nullptr;
    typename Iterator::value_type key;
  };
  
public:
  Tree(Iterator begin, Iterator end) {
    for (Iterator it = begin; it != end; it++) {
      insert_elem(*it);
    }
  }
  
  ~Tree() {
    delete_rec(root);
  }
  
  void insert_elem(const typename Iterator::value_type& key) {
    if (root == nullptr) {
      root = new Node;
      root->key = key;
      return;
    }
    auto curr_node = root;
    while (true) {
      if (key < curr_node->key) {
        if (curr_node->left_child) {
          curr_node = curr_node->left_child;
        } else {
          curr_node->left_child = new Node;
          curr_node->left_child->key = key;
          return;
        }
      } else if (key > curr_node->key) {
        if (curr_node->right_child) {
          curr_node = curr_node->right_child;
        } else {
          curr_node->right_child = new Node;
          curr_node->right_child->key = key;
          return;
        }
      } else {
        return;
      }
    }
  }
  
  void delete_rec(Node* root) {
    if (root == nullptr) {
      return;
    }
    if (root->left_child != nullptr) {
      delete_rec(root->left_child);
    }
    if (root->right_child != nullptr) {
      delete_rec(root->right_child);
    }
    delete root;
  }

  vector<typename Iterator::value_type> get_sorted_keys() {
    vector<typename Iterator::value_type> result;
    visit_tree(root, result);
    return result;
  }

private:
    Node* root = nullptr;
  
  void visit_tree(Node* root, vector<typename Iterator::value_type>& result) {
    if (root == nullptr) {
      return;
    }
    visit_tree(root->left_child, result);
    result.push_back(root->key);
    visit_tree(root->right_child, result);
  }
};




