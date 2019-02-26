#include "Node.h"
template <typename T> class TreeNode : public Node<T> {
private:
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

public:
  TreeNode();
  TreeNode(const T &data);
  TreeNode(const T &data, TreeNode<T> *parent);

  ~TreeNode();

  void setLeft(TreeNode<T> *left);
  void setRight(TreeNode<T> *right);
  void setParent(TreeNode<T> *parent);

  TreeNode<T> *getLeft();
  TreeNode<T> *getRight();
  TreeNode<T> *getParent();
  TreeNode<T> *getTopOfTree();

  int getTreeHeight();
  int getDepthOfNode();
  int getDepthFromNode();

  int getChildCount();
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

template <typename T> TreeNode<T>::~TreeNode() {
  delete left;
  delete right;
}

template <typename T> void TreeNode<T>::setLeft(TreeNode<T> *left) {
  this->left = left;
  left->setParent(this);
}

template <typename T>
void TreeNode<T>::setRight(TreeNode<T> *right) {
  this->right = right;
  right->setParent(this);
}

template <typename T>
void TreeNode<T>::setParent(TreeNode<T> * parent) {
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
    TreeNode *tempnode = parent;
    // while parent of tempnode exists, change tempnode pointer to parent
    while (tempnode->parent != nullptr) {
      tempnode = tempnode->parent;
    }
    // when tempnode has no parent, it's the top node, return it
    return tempnode;
  }
}

template <typename T> int TreeNode<T>::getTreeHeight() {
  return (getTopOfTree()->getDepthFromNode() + 1);
}

template <typename T> int TreeNode<T>::getDepthOfNode() {
  // if no parent, node is head of tree, return 0
  if (parent == nullptr)
    return 0;
  else {
    // if there is a parent, node is at least depth 1
    int count = 1;
    TreeNode *tempnode = parent;
    // iterate through parents, incrementing count each time
    while (tempnode->parent != nullptr) {
      tempnode = tempnode->parent;
      count++;
    }
    // when there is no parent, we are at the head, return count for depth of
    // original node
    return count;
  }
}

template <typename T> int TreeNode<T>::getDepthFromNode() {
  if (left == nullptr && right == nullptr)
    return 0;
  else {
    int lDepth, rDepth;

    if (left != nullptr)
      lDepth = getDepthFromNode(left);
    else
      lDepth = 0;

    if (right != nullptr)
      rDepth = getDepthFromNode(right);
    else
      rDepth = 0;

    if (lDepth > rDepth)
      return (lDepth + 1);
    else
      return (rDepth + 1);
  }
}

template <typename T> int TreeNode<T>::getChildCount() {
  return ((int)(left != nullptr) + (int)(right != nullptr));
}
