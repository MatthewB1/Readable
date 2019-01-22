#include "Node.hpp"
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

  void setLeft(const TreeNode<T> *const left);
  void setRight(const TreeNode<T> *const right);
  void setParent(const TreeNode<T> *const parent);

  TreeNode<T> *getLeft();
  TreeNode<T> *getRight();
  TreeNode<T> *getParent();
  TreeNode<T> *getTopOfTree();

  int getTreeDepth();
  int getDepthOfNode();
  int getDepthFromNode();

  int getChildCount();
};