#include <stdio.h>

template<typename KeyT, typename ValueT>
class RBTree {

  enum Color {
    BLACK,
    RED
  };
  
  struct RBTreeNode {
    KeyT key;
    ValueT val;
    RBTreeNode *left, *right;
    int n;
    Color color;

    RBTreeNode(const KeyT &_key, const ValueT &_val, Color _color)
      : key(_key), val(_val), color(_color), left(NULL), right(NULL), n(1)
    { }
  };
  
public:
  RBTree() {
    root_ = NULL;
  }

  void Put(const KeyT &key, const ValueT &val)
  {
    root_ = Put(root_, key, val);
    root_->color = BLACK;
  }
  
  int size() {
    return size(root_);
  }
  
private:


  typedef RBTreeNode *RBTreeNodeP;
  
  RBTreeNodeP Put(RBTreeNodeP root, const KeyT &key, const ValueT &val)
  {
    if (root == NULL) {
      return new RBTreeNode(key, val, RED);
    }

    if (key == root->key) {
      root->val = val;
    } else if (key < root->key) {
      root->left = Put(root->left, key, val);
    } else {
      root->right = Put(root->right, key, val);
    }

    return root;
  }

  RBTreeNodeP RotateLeft(RBTreeNodeP node)
  {
    RBTreeNodeP x = node->right;
    node->right = x->left;
    x->left = node;
    x->color = node->color;
    x->n = node->n;
    node->n = 1 + size(node->left) + size(node->right);
    return x;
  }

  RBTreeNodeP RotateRight(RBTreeNodeP node)
  {
    RBTreeNodeP x = node->left;
    node->left = x->right;
    x->right = node;
    x->color = node->color;
    x->n = node->n;
    node->n = 1 + size(node->left) + size(node->right);
    return x;
  }

  int size(RBTreeNodeP root)
  {
    if (root)
      return root->n;
    return 0;
  }

  RBTreeNodeP root_;
};
