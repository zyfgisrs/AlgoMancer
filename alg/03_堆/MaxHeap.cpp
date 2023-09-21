#include <iostream>
#include <vector>

template <typename T>
class MaxHeap {
 private:
  std::vector<T>* data;

 public:
  MaxHeap() { data = new std::vector<T>(); }
  ~MaxHeap() { delete data; }

 private:
  int parent(int i) { return (i - 1) / 2; }
  int leftChild(int i) { return i * 2 + 1; }
  int rightChild(int i) { return i * 2 + 2; }

  void shiftUp(int i) {
    while (i > 0 && data->at(parent(i)) < data->at(i)) {
      std::swap(data->at(parent(i)), data->at(i));
      i = parent(i);
    }
  }

  void shiftDown(int i) {
    int max = i;
    int leftc = leftChild(i);
    int rightc = rightChild(i);
    if (leftc < data->size() && data->at(max) < data->at(leftc)) {
      max = leftc;
    }

    if (rightc < data->size() && data->at(max) < data->at(rightc)) {
      max = rightc;
    }

    if (i != max) {
      std::swap(data->at(i), data->at(max));
      shiftDown(max);
    }
  }

 public:
  int size() { return data->size(); }

  bool Empty() { return data->size() == 0; }

  void insert(T element) {
    data->push_back(element);
    shiftUp(data->size() - 1);
  }

  void pop() {
    if (data->size() == 0) return;
    (*data)[0] = data->back();
    data->pop_back();
    shiftDown(0);
  }

  T top() {
    if (data->size() == 0) {
      throw std::runtime_error("Heap is empty");  // 抛出一个更具描述性的异常
    }
    return data->front();
  }

  void show() {
    for (const auto& value : *data) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  MaxHeap<int> heap;
  heap.insert(1);
  heap.insert(2);
  heap.insert(4);
  heap.insert(5);
  heap.insert(6);
  heap.insert(7);
  auto top = heap.top();
  std::cout << top << std::endl;
  heap.pop();
  heap.show();
  std::cout << heap.top() << std::endl;
}