#include <stdio.h>
#include <assert.h>
#include <string>
#include <algorithm>


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

  bool Get(const KeyT &key, ValueT &val)
  {
    RBTreeNodeP p = root_;
    while (p != NULL) {
      if (p->key > key) {
        p = p->left;
      } else if (p->key < key) {
        p = p->right;
      } else {
        val = p->val;
        return true;
      }
    }
    return false;
  }

  void Put(const KeyT &key, const ValueT &val)
  {
    root_ = Put(root_, key, val);
    root_->color = BLACK;
  }

  //@TODO implement it
  void Delete(const KeyT &key)
  {
    
  }

  bool Equal(const RBTree &rbtree) const
  {
    return Equal(root_, rbtree.root_);
  }

  std::string Serialize() const
  {
    std::string tree;
    FmtTree(tree, root_, 0);
    return tree;
  }
  
  bool Deserialize(const std::string &tree)
  {
    if (root_ != NULL)
      return false;
    int i = 0;
    int ret = ParseTree(tree, i, root_);
    if (ret < 0 || !CheckValid(root_)) {
      Clear();
      return false;
    }
    return true;
  }

  void Clear()
  {
    root_ = Destroy(root_);
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
    root->n = 1 + size(root->left) + size(root->right);
    if (is_red(root->right) && !is_red(root->left))
      root = RotateLeft(root);
    if (is_red(root->left) && is_red(root->left->left))
      root = RotateRight(root);
    if (is_red(root->left) && is_red(root->right))
      root = FlipColor(root);
    return root;
  }

  RBTreeNodeP RotateLeft(RBTreeNodeP node)
  {
    RBTreeNodeP x = node->right;
    node->right = x->left;
    x->left = node;
    std::swap(x->color, node->color);
    x->n = node->n;
    node->n = 1 + size(node->left) + size(node->right);
    return x;
  }

  RBTreeNodeP RotateRight(RBTreeNodeP node)
  {
    RBTreeNodeP x = node->left;
    node->left = x->right;
    x->right = node;
    std::swap(x->color, node->color);
    x->n = node->n;
    node->n = 1 + size(node->left) + size(node->right);
    return x;
  }

  RBTreeNodeP FlipColor(RBTreeNodeP node)
  {
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
    return node;
  }

  RBTreeNodeP Destroy(RBTreeNodeP root)
  {
    if (root == NULL)
      return NULL;
    root->left = Destroy(root->left);
    root->right = Destroy(root->right);
    delete root;
    return NULL;
  }

  void FmtTree(std::string &tree, RBTreeNodeP root, int level) const
  {
    for (int i = 0; i < level; i++) {
      tree += std::string("  ");
    }
    tree += '(';
    if (root != NULL) {
      tree += '(';
      int a[3] = {root->key, root->val, (root->color == RED) ? 1 : 0};
      for (int i = 0; i < 3; i++) {
        char buf[100];
        sprintf(buf, "%d", a[i]);
        tree += std::string(buf);
        if (i != 2)
          tree += ' ';
      }
      tree += ')';
      tree += '\n';
      FmtTree(tree, root->left, level + 1);
      tree += '\n';
      FmtTree(tree, root->right, level + 1);
      tree += '\n';
      for (int i = 0; i < level; i++) {
        tree += std::string("  ");
      }
    }

    tree += ')';
  }

  int ParseTree(const std::string &tree, int &i, RBTreeNodeP &root)
  {
    assert(root == NULL);
    int ret, append;

    if (NextToken(tree, i, append) != '(')
      return -1;

    ret = ParseTreeNode(tree, i, root);
    if (ret <= 0)
      return ret;

    if (ParseTree(tree, i, root->left) < 0)
      return -1;
    if (ParseTree(tree, i, root->right) < 0)
      return -1;
    
    root->n = 1 + size(root->left) + size(root->right);
    
    if (NextToken(tree, i, append) != ')')
      return -1;
    return 0;
  }

  int ParseTreeNode(const std::string &tree, int &i, RBTreeNodeP &root)
  {
    int ret, append;
    ret = NextToken(tree, i, append);

    if (ret == ')')
      return 0;
    if (ret != '(')
      return -1;

    int a[3];
    for (int j = 0; j < 3; j++) {
      ret = NextToken(tree, i, a[j]);
      if (ret != '0') {
        return -1;
      }
    }
    if (NextToken(tree, i, append) != ')')
      return -1;
    root = new RBTreeNode(a[0], a[1], (a[2] == 1) ? RED : BLACK);
    return 1;
  }

  int NextToken(const std::string &tree, int &i, int &append)
  {
    while (i < tree.length()
           && (tree[i] == ' ' || tree[i] == '\t' || tree[i] == '\n')) {
      i++;
    }

    if (i >= tree.length()) {
      return 0;
    }

    if (tree[i] == '(') {
      i++;
      return '(';
    } else if (tree[i] == ')') {
      i++;
      return ')';
    } else if (tree[i] >= '0' && tree[i] <= '9') {
      append = 0;
      while (i < tree.length() &&
             tree[i] >= '0' && tree[i] <= '9') {
        append = append * 10 + tree[i] - '0';
        i++;
      }
      return '0';
    } else {
      return -1;
    }
  }

  bool Equal(RBTreeNodeP r1, RBTreeNodeP r2) const
  {
    if (r1 == NULL && r2 == NULL) {
      return true;
    }
    if (r1 == NULL)
      return false;
    if (r2 == NULL)
      return false;

    if (!(r1->key == r2->key && r1->val == r2->val
          && r1->color == r2->color && r1->n == r2->n)) {
      return false;
    }
    return Equal(r1->left, r2->left) && Equal(r1->right, r2->right);
  }

  //@TODO implement it
  bool CheckValid(RBTreeNodeP root)
  {
    return true;
  }
  
  int size(RBTreeNodeP root)
  {
    if (root)
      return root->n;
    return 0;
  }

  bool is_red(RBTreeNodeP node)
  {
    if (node)
      return node->color == RED;
    return false;
  }

  RBTreeNodeP root_;
};
