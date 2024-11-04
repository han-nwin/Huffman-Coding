#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
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

      if (leftChildIndex < static_cast<int>(heap.size()) && heap[leftChildIndex] < heap[smallestChildIndex]) {
        smallestChildIndex = leftChildIndex;
      }

      if (rightChildIndex < static_cast<int>(heap.size()) && heap[rightChildIndex] < heap[smallestChildIndex]) {
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


    void privateInsert(const Comparable & node) {
      heap.push_back(node);
      percolateUp(static_cast<int>(heap.size()-1));

    }

    Comparable privateDeleteMin() {
      if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
      }

      Comparable minElement = heap[0]; // Get the element
      heap[0] = heap[heap.size() - 1]; // Swap it with the last element
      heap.pop_back(); // Remove the last element
                       //
      //If the heap is not empty after removal percolate element at root down
      if (!heap.empty()) {
        percolateDown(0);
      }

      return minElement;
    }

    const Comparable & privateMin() const {
      if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
      }
      return heap[0];
    }


    void privateDisplay(){
      if (heap.empty()) {
        std::cerr << "Heap is empty" << std::endl;
        return;
      }
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

  bool empty() {
    return heap.empty();
  }

  int size() {
    return static_cast<int>(this->heap.size());
  }

  void insert(const Comparable & node) {
    privateInsert(node);
  } 

  Comparable deleteMin() {
    return privateDeleteMin();
  }

  const Comparable & min() const {
    return privateMin();
  }

  void display() {
    this->privateDisplay();
  }
  
  }; //end MinHeap Class


int main(){
  
  //====== READ FROM FILE =====//
  std::ifstream inputFile("merchant.txt"); // Open the file
  if (!inputFile) {
      std::cerr << "Error opening input file!" << std::endl;
      return 1; // Exit if the file couldn't be opened
  }
  
  //Initialize a vector for frequency counting (size 256 for all ASCII chars)
  std::vector<int> charFrequency(256,0);

  char c;
  while (inputFile.get(c)) {
    //cast c into unsigned char then cast to unsigned int to store as an index of charFrequency
    //NOTE we can skip <unsigned int> cast since C++ will implicitly cast it 
    charFrequency[static_cast<unsigned int>(static_cast<unsigned char>(c))]++;
  }
  inputFile.close();

  //==CHECK the frequency of 27 characters
  //std::cout << static_cast<unsigned char>(10) << " is " << charFrequency[10] << std::endl; //10 is a \n
  //std::cout << static_cast<unsigned char>(13) << " is " << charFrequency[13] << std::endl; //13 is a \r
  std::cout << static_cast<unsigned char>(32) << " is " << charFrequency[32] << std::endl; //32 is a space
  for (int i = 97; i <= 122; i++) { //a-z
    std::cout << static_cast<unsigned char>(i) << " is " << charFrequency[i] << std::endl;
  }
  
  //==MAKE a node array
  std::vector<HeapNode<char>> nodes;
  nodes.push_back(HeapNode<char>(charFrequency[32], static_cast<unsigned char>(32)));// Add the space
  for (int i = 97; i <= 122; i++) { //a-z
    nodes.push_back(HeapNode<char>(charFrequency[i], static_cast<unsigned char>(i))); // Add a-z
  }
  //print check 
  for (auto & element : nodes) {
    std::cout << element << std::endl;
  }

  //==MAKE a MinHeap out of the node array
  MinHeap<HeapNode<char>> minHeap(nodes);
  minHeap.display();


/**
  // Initialize MinHeap with integers
  std::vector<int> intValues = {10, 3, 5, 1, 12, 7};
  MinHeap<int> intHeap(intValues);

  std::cout << "Size of intHeap: " << intHeap.size() << std::endl;
  intHeap.display();

  

    // Using MinHeap with HeapNode<char>
  std::vector<HeapNode<char>> nodes = {
      HeapNode<char>(5, 'a'),
      HeapNode<char>(1, 'b'),
      HeapNode<char>(2, 'c'),
      HeapNode<char>(2, 'd'),
      HeapNode<char>(2, 'e'),
      HeapNode<char>(3, 'f'),
  };
  MinHeap<HeapNode<char>> heapWithNodes(nodes);
  std::cout << "Heap with nodes size: " << heapWithNodes.size() << std::endl;
  heapWithNodes.display();

  std::cout << "Min " << heapWithNodes.min() << std::endl;
  heapWithNodes.display();
  std::cout << "Delete Min " << heapWithNodes.deleteMin() << std::endl;
  heapWithNodes.display();
  std::cout << "Min " << heapWithNodes.min() << std::endl;
  heapWithNodes.display();
  std::cout << "Delete Min " << heapWithNodes.deleteMin() << std::endl;
  heapWithNodes.display();
  std::cout << "Min " << heapWithNodes.min() << std::endl;
  heapWithNodes.display();
  std::cout << "Delete Min " << heapWithNodes.deleteMin() << std::endl;
  heapWithNodes.display();
  std::cout << "Min " << heapWithNodes.min() << std::endl;
  heapWithNodes.display();
  std::cout << "Delete Min " << heapWithNodes.deleteMin() << std::endl;
  heapWithNodes.display();
  std::cout << "Min " << heapWithNodes.min() << std::endl;
  heapWithNodes.display();
  std::cout << "Delete Min " << heapWithNodes.deleteMin() << std::endl;
  heapWithNodes.display();
  std::cout << "Min " << heapWithNodes.min() << std::endl;
  heapWithNodes.display();
  std::cout << "Delete Min " << heapWithNodes.deleteMin() << std::endl;
  heapWithNodes.display();

  int i = 0x41;
  char c = static_cast<char>(i);
  std::cout << c << std::endl;
*/
  return 0;
}
