#include <iostream>
#include <vector>

template <typename Comparable>
    struct HeapNode {
      int frequency; //Primary key
      Comparable value; //secondary key
      
      //Constructor
      HeapNode(int f, const Comparable & v) : frequency(f), value(v) {}

      // Less-than operator for comparing HeapNode objects by key
      bool operator<(const HeapNode & other) const {
        if (frequency == other.frequency) {
          return value < other.value;
        }
        return frequency<other.frequency;
      }

      //Greater-than operator for comparing HeadNode objects by key
      bool operator>(const HeapNode & other) const {
        if (frequency == other.frequency) {
          return value > other.value;
        }
        return frequency>other.frequency;
      }

      // Equal operator for comparing HeapNode objects
      bool operator==(const HeapNode & other) const {
        return frequency == other.frequency && value == other.value;
      }

      // Overload the << operator for printing HeapNode
      friend std::ostream &operator<<(std::ostream &os, const HeapNode &node) {
        os << "{" << node.frequency << ":" << node.value << "}";
        return os;
      }
    };//end of HeapNode struct

template <typename Comparable>
class MinHeap {
  private:
    std::vector<Comparable> heap;


    void percolateDown(int i) {
      int leftChildIndex = 2 * i + 1;
      int rightChildIndex = 2 * i + 2;
      int smallestChildIndex = i;

      if (leftChildIndex <= static_cast<int>(heap.size()) && heap[leftChildIndex] < heap[smallestChildIndex]) {
        smallestChildIndex = leftChildIndex;
      }

      if (rightChildIndex <= static_cast<int>(heap.size()) && heap[rightChildIndex] < heap[smallestChildIndex]) {
        smallestChildIndex = rightChildIndex;
      }

      if(smallestChildIndex != i){
        std::swap(heap[i], heap[smallestChildIndex]);
        percolateDown(smallestChildIndex);
      }
    }


    void percolateUp(int i) {
      // Check if index is out of bounds
      if (i >= static_cast<int>(heap.size())) {
        std::cerr << "Error: Index " << i << " is out of bounds.\n";
        return;  // Or throw an exception if you prefer
      }

      int currIndex = i;

      while (currIndex > 0 && heap[currIndex] < heap[currIndex/2]) {
        std::swap(heap[currIndex], heap[(currIndex - 1)/2]);
        currIndex = (currIndex - 1)/2;
      }

    }


    void buildHeap() {
      for (int i = static_cast<int>((heap.size()/2 - 1)); i >= 0; i--){
        percolateDown(i);
      }
    }

    void privateDisplay(){
      for (auto & element : heap) {
        std::cout << element << ", ";
      }
      std::cout << std::endl;
    }



  public:
   
  // Constructor that handles both an empty heap or an array of HeapNode
  explicit MinHeap(const std::vector<Comparable> & arr = {}) : heap(arr){
    if(!heap.empty()) {
      buildHeap();
    }
  };

  int size(){
    return static_cast<int>(this->heap.size());
  }

  void display(){
    this->privateDisplay();
  }
  




  }; //end MinHeap Class


int main(){
// Initialize MinHeap with integers
  std::vector<int> intValues = {10, 3, 5, 1, 12, 7};
  MinHeap<int> intHeap(intValues);

  std::cout << "Size of intHeap: " << intHeap.size() << std::endl;
  intHeap.display();

  

    // Using MinHeap with HeapNode<char>
  std::vector<HeapNode<char>> nodes = {
      HeapNode<char>(3, 'a'),
      HeapNode<char>(1, 'b'),
      HeapNode<char>(2, 'c')
  };
  MinHeap<HeapNode<char>> heapWithNodes(nodes);
  std::cout << "Heap with nodes size: " << heapWithNodes.size() << std::endl;
  heapWithNodes.display();

  return 0;
}
