#include "Node.h"

/*
May want to come back to this file to use smart pointers
will see after profiling
*/
template <typename T> class TreeNode : public Node<T> {
private:
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

public:
  TreeNode();
  TreeNode(const T &data);
  TreeNode(const T &data, TreeNode<T> *parent);

  void setLeft(TreeNode<T> *left);
  void setRight(TreeNode<T> *right);
  void setParent(TreeNode<T> *parent);

  TreeNode<T> *getLeft();
  TreeNode<T> *getRight();
  TreeNode<T> *getParent();
  TreeNode<T> *getTopOfTree();
  TreeNode<T> *getStart();
  TreeNode<T> *getBottomLeft();

  int getTreeHeight();
  int getDepthOfNode();
  int getDepthFromNode();
  int getChildCount();

  static int size(TreeNode<T> *node);
};

template <typename T> TreeNode<T>::TreeNode() : Node<T>() {
  this->left = this->right = this->parent = nullptr;
}

template <typename T> TreeNode<T>::TreeNode(const T &data) : Node<T>(data) {
  this->left = this->right = this->parent = nullptr;
}

template <typename T>
TreeNode<T>::TreeNode(const T &data, TreeNode<T> *parent) : Node<T>(data) {
  this->left = this->right = nullptr;
  this->parent = parent;
}

template <typename T> void TreeNode<T>::setLeft(TreeNode<T> *left) {
  this->left = left;
  left->setParent(this);
}

template <typename T> void TreeNode<T>::setRight(TreeNode<T> *right) {
  this->right = right;
  right->setParent(this);
}

template <typename T> void TreeNode<T>::setParent(TreeNode<T> *parent) {
  this->parent = parent;
}

template <typename T> TreeNode<T> *TreeNode<T>::getLeft() { return left; }

template <typename T> TreeNode<T> *TreeNode<T>::getRight() { return right; }

template <typename T> TreeNode<T> *TreeNode<T>::getParent() { return parent; }

template <typename T> TreeNode<T> *TreeNode<T>::getTopOfTree() {
  // if there's no parent, this is the top node
  if (parent == nullptr)
    return this;
  else {
    TreeNode<T> *tempnode = parent;
    // while parent of tempnode exists, change tempnode pointer to parent
    while (tempnode->parent != nullptr) {
      tempnode = tempnode->parent;
    }
    // when tempnode has no parent, it's the top node, return it
    return tempnode;
  }
}

template <typename T> int TreeNode<T>::getDepthOfNode() {
  if (parent == nullptr)
    return 0;
 //dunno how to fix this function, seg faults :~(
  return 1;
}

template <typename T> int TreeNode<T>::getChildCount() {
  return ((int)(left != nullptr) + (int)(right != nullptr));
}

namespace TreeUtils {
template <typename T> int size(TreeNode<T> *node) {
  if (node == nullptr) {
    return 0;
  } else { // Add the size of the left and right trees, then add 1 (which is the
           // current node)
    return size(node->getLeft()) + size(node->getRight()) + 1;
  }
}
} // namespace TreeUtils
