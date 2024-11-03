#include <iostream>
#include <vector>

template <typename Comparable>
class MinHeap {
  private:

    std::vector<Comparable> heap;
    int currentSize; //Number of elements


    void percolateDown() {}
    void percolateUp() {}
    void buildHeap() {}



  public:
   
  // Constructor that handles both an empty heap and an array with or without a dummy node
  explicit MinHeap(const std::vector<Comparable>& arr = {}) : heap(arr) {
    if(!heap.empty()) {
      buildHeap();
    }
  };

  int size(){
    return this->heap.size();
  }
  




  }; //end MinHeap Class


int main(int argc, char *argv[]){
  char c = static_cast<char>(0x24);
  std::cout << "test " << c << std::endl;
  return 0;
}
