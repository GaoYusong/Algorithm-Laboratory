#ifndef ALGOLAB_SPLAY_H_
#define ALGOLAB_SPLAY_H_

template<typename KeyT, typename ValueT>
class SplayTree {
  struct TreeNode {
    KeyT key;
    ValueT val;
    TreeNode *left, *right;

    TreeNode(const KeyT &_key, const ValueT &_val)
      : key(_key), val(_val)
    {
      
    }
  };

  typedef TreeNode *TreeNodeP;
public:
  SplayTree() {
    root_ = NULL;
  }
  
private:
  TreeNodeP root_;
};
#endif
