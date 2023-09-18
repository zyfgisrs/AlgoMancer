#include <iostream>

template <typename T>
struct Node {
  T data;
  Node<T>* next;

  Node(T data) : data(data), next(nullptr){};
};

template <typename T>
class LinkedList {
 private:
  Node<T>* head;
  Node<T>* tail;
  int numOfItems;

 public:
  LinkedList() : head(nullptr), tail(nullptr), numOfItems(0){};

  bool empty() { return numOfItems == 0; }

  int size() { return numOfItems; }

  void clear() {
    if (head == nullptr) return;
    Node<T>* nodeToDelete = head;
    while (nodeToDelete != nullptr) {
      Node<T>* nextNode = nodeToDelete->next;
      delete nodeToDelete;
      nodeToDelete = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    numOfItems = 0;
  }

  bool exist(T data) {
    if (head == nullptr) return false;
    Node<T>* current = head;
    while (current != nullptr) {
      if (current->data == data) return true;
      current = current->next;
    }
    return false;
  }

  bool remove(int index) {
    if (head == nullptr || index >= numOfItems || index < 0) {
      return false;
    }

    Node<T>* nodeTodelete = nullptr;

    if (index == 0) {
      Node<T>* nodeTodelete = head;
      head = head->next;
    } else {
      Node<T>* current = head;
      for (int i = 0; i < index - 1; ++i) {
        current = current->next;
      }
      nodeTodelete = current->next;
      current->next = nodeTodelete->next;
    }
    numOfItems--;
    delete nodeTodelete;

    if (numOfItems == 0) {
      tail = nullptr;
    }
    return true;
  }

  bool remove(T data) {
    if (empty()) {
      return false;
    }
    Node<T>* current = head;
    Node<T>* previous = nullptr;

    while (current != nullptr) {
      if (current->data == data) {
        if (previous == nullptr) {
          head = current->next;
        } else {
          previous->next = current->next;
        }
        if (current == tail) {
          tail = previous;
        }
        delete current;
        numOfItems--;
        return true;
      }
      previous = current;
      current = current->next;
    }
    return false;
  }

  bool insert(int index, const T& data) {
    if (index < 0 || index > numOfItems) {
      return false;
    }
    Node<T>* newNode = nullptr;
    try {
      newNode = new Node<T>(data);
    } catch (...) {
      return false;
    }
    if (index == 0) {
      if (head == nullptr) {
        head = newNode;
        tail = newNode;
      } else {
        newNode->next = head;
        head = newNode;
      }
    } else if (index == numOfItems) {
      tail->next = newNode;
      tail = newNode;
    } else {
      Node<T>* current = head;
      for (int i = 0; i < index - 1; i++) {
        current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;
    }
    numOfItems++;
    return true;
  }

  //链表结尾插入元素
  void addLast(T data) { insert(numOfItems, data); }
  //链表开始插入元素
  void addFirst(T data) { insert(0, data); }
  //删除链表第一个元素
  void removeFirst() { remove(0); }
  //删除链表最后一个元素
  void removeLast() { remove(numOfItems - 1); }

  //链表反转，递归实现可能会发生栈溢出
  void reverseLinkedList() {
    if (numOfItems <= 1) {
      return;
    }
    tail = head;
    head = reverseLinkedListHelper(nullptr, head);
  }
  //链表反转helper
  Node<T>* reverseLinkedListHelper(Node<T>* previous, Node<T>* current) {
    if (current == nullptr) {
      return previous;
    }
    Node<T>* nextNode = current->next;
    current->next = previous;
    return reverseLinkedListHelper(current, nextNode);
  }

  bool removeDuplicates() {}

  class Iterator {
   private:
    Node<T>* node;

   public:
    Iterator(Node<T>* node) : node(node){};

    T& operator*() { return node->data; }

    void operator++() { node = node->next; }

    bool operator==(const Iterator& other) const { return node == other.node; }

    bool operator!=(const Iterator& other) const { return node != other.node; }
  };

  Iterator begin() { return Iterator(head); }

  Iterator end() { return nullptr; }
};

class Dog {
 private:
  std::string name;
  int age;

 public:
  Dog(const std::string& name, int age) : name(name), age(age){};

  bool operator==(const Dog& other) {
    return name == other.name && this->age == other.age;
  }

  friend std::ostream& operator<<(std::ostream& os, const Dog& dog) {
    os << dog.name << " " << dog.age;
    return os;
  }
};

int main() {
  LinkedList<Dog> dogList;
  dogList.addLast(Dog("Fido", 12));
  dogList.addLast(Dog("Spot", 13));
  dogList.addLast(Dog("Jack", 14));
  dogList.addLast(Dog("tom", 23));
  std::cout << dogList.size() << std::endl;
  for (auto const& dog : dogList) {
    std::cout << dog << std::endl;
  }
  std::cout << std::endl;
  dogList.reverseLinkedList();
  for (auto const& dog : dogList) {
    std::cout << dog << std::endl;
  }
  std::cout << dogList.exist(Dog("tom", 23)) << std::endl;
  dogList.clear();
  std::cout << dogList.size() << std::endl;
}
