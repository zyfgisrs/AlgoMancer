#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

template <typename Key, typename Value>
struct Node {
  Node* right;
  Node* left;
  Key key;
  Value value;

  Node(){};

  Node(Key key, Value value)
      : key(key), value(value), right(nullptr), left(nullptr){};

  Node(Key key, Value value, Node* right, Node* left)
      : key(key), value(value), right(right), left(left){};
};

template <typename Key, typename Value>
class Tree {
 private:
  Node<Key, Value>* root;
  int count;

 private:
  /**
   * @brief 私有辅助函数，插入元素
   *
   * @param node 当前检查的节点
   * @param key  插入的键
   * @param value 插入的值
   * @return Node<Key, Value>* 插入完成后返回的节点
   */
  Node<Key, Value>* insert(Node<Key, Value>* node, Key key, Value value) {
    if (node == nullptr) {
      Node<Key, Value>* newNode = new Node<Key, Value>(key, value);
      return newNode;
    }

    if (node->key > key) {
      node->left = insert(node->left, key, value);
    } else if (node->key < key) {
      node->right = insert(node->right, key, value);
    } else {
      node->value = value;
    }

    return node;
  }
  Node<Key, Value>* remove(Node<Key, Value>* node, Key key) {
    if (node == nullptr) {
      throw std::runtime_error("Key not found");
    }

    if (node->key < key) {
      node->right = remove(node->right, key);
    } else if (node->key > key) {
      node->left = remove(node->left, key);
    } else {
      if (node->left == nullptr) {
        Node<Key, Value>* nodeRight = node->right;
        delete node;
        count--;
        return nodeRight;
      }

      if (node->right == nullptr) {
        Node<Key, Value>* nodeLeft = node->left;
        delete node;
        count--;
        return nodeLeft;
      }

      Node<Key, Value>* successor = new Node<Key, Value>();
      successor->right = removeMin(node->right);
      successor->left = node->left;
      successor->key = min(node->right)->key;
      successor->value = min(node->right)->value;
      return successor;
    }
    return node;
  };

  /**
   * @brief 查找元素的私有辅助函数
   *
   * @param node 当前检查的节点
   * @param key  插入的值
   * @return Node<Key, Value>* 包含该键的节点
   */
  Node<Key, Value>* search(Node<Key, Value>* node, Key key) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->key > key) {
      return search(node->left, key);
    } else if (node->key < key) {
      return search(node->right, key);
    } else {
      return node;
    }
  };

  /**
   * @brief 判断树中是否存在指定键的结点
   *
   * @param node 当前检查的结点
   * @param key 指定的键
   * @return true 存在
   * @return false 不存在
   */
  bool contains(Node<Key, Value>* node, Key key) const {
    if (node == nullptr) {
      return false;
    }

    if (node->key > key) {
      return contains(node->left, key);
    } else if (node->key < key) {
      return contains(node->right, key);
    } else {
      return true;
    }
  }

  /**
   * @brief 删除指定结点下键最小的结点
   *
   * @param node 指定的结点
   * @return Node<Key, Value>* 删除最小节点后的结点
   */
  Node<Key, Value>* removeMin(Node<Key, Value>* node) {
    if (!node->left) {
      Node<Key, Value>* rightNode = node->right;
      delete node;
      count--;
      return rightNode;
    }

    node->left = removeMin(node->left);
    return node;
  }

  /**
   * @brief 返回指定结点下的键最小的结点
   *
   * @param node 指定的结点
   * @return Node<Key, Value>* 键最小的结点
   */
  Node<Key, Value>* min(Node<Key, Value>* node) {
    if (node->left) {
      return node->left;
    }
    return node;
  }

 public:
  Tree() : count(0), root(nullptr) {}
  ~Tree() { delete root; };
  // 判断树是否为空
  bool empty() const { return root == nullptr; }

  // 元素的个数
  int size() const { return count; }

  /**
   * @brief 插入元素
   *
   * @param key 要插入的键
   * @param value 要插入的值
   */
  void insert(Key key, Value value) {
    root = insert(root, key, value);
    count++;
  };

  /**
   * @brief 查找元素
   *
   * @param key 要查找的元素的键
   * @return Value 返回找到的元素的值
   */
  Value search(Key key) const {
    Node<Key, Value>* node = search(root, key);
    if (node == nullptr) {
      throw std::runtime_error("Key not found");
    }
    return node->value;
  };

  /**
   * @brief 判断树中是否存在指定键的结点
   *
   * @param key 指定的键
   * @return true 存在
   * @return false 不存在
   */
  bool contains(Key key) const { return contains(root, key); }

  // 删除元素
  void remove(Key key) { root = remove(root, key); };
};

#endif