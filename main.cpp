#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <sstream>


/**
 * @brief HeapNode structure that hold frequency, value, pointers to left and right child.
 * Provide comparision operator (> < =) based on the primary key (frequency) and secondary key (value)
 * */
template <typename Comparable>
struct HeapNode {
  int frequency; // Primary key
  Comparable value; // Value and also a secondary key
  HeapNode* left;   // Pointer to the left child
  HeapNode* right;  // Pointer to the right child

  //Constructor
  HeapNode(int f, const Comparable & v) : frequency(f), value(v), left(nullptr), right(nullptr){}

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

/**
 * @brief Class that provides Minimum heap data structure
 * The data structure ensures storing comparable elements with the smallest key as the highest priority
 * Provide necessary functions to perform storing, and retrieving data
 * */
template <typename Comparable>
class MinHeap {
  private:

    //Dynamic array to store elements of the heap
    std::vector<Comparable> heap;

    /**
     * @brief Private function to move the lower priority key down the tree.
     * @params int index 
     * @return nothing
     * */
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

    /**
     * @brief Private function to move the higher priority key up the tree
     * @params int index
     * @return nothing
     * */
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

    /**
     * @brief function that build out a heap structure from an array
     * Helper for constructor when users want to initialize the heap with an array
     * @params: nothing
     * @return: nothing
     * */
    void buildHeap() {
      for (int i = static_cast<int>((heap.size()/2 - 1)); i >= 0; i--){
        percolateDown(i);
      }
    }

    /**
     * @brief private function to insert an element into the heap
     * @params: const Comparable & node 
     * @return nothing
     * */
    void privateInsert(const Comparable & node) {
      heap.push_back(node); //Inser the element to the back of the heap array
      percolateUp(static_cast<int>(heap.size()-1)); //move the inserted element to ensure heap structure

    }

    /**
     * @brief private function to retrieve and remove an element from the top of the heap (highest priority)
     * @params nothing
     * @return Comparable minElement
     * */
    Comparable privateDeleteMin() {
      if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
      }

      Comparable minElement = heap[0]; // Copy the element
      heap[0] = heap[heap.size() - 1]; // Swap it with the last element
      heap.pop_back(); // Remove the last element
                       //
      //If the heap is not empty after removal percolate element at root down
      if (!heap.empty()) {
        percolateDown(0);
      }

      return minElement; //return the copy
    }


    /**
     * @brief Private function that return the value of the highest priority element
     * This function does not remove the element from the heap
     * @params nothing
     * @return const Comparable & element
     * */
    const Comparable & privateMin() const {
      if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
      }
      return heap[0];
    }

    /**
     * @brief Function to display the heap to stdout
     * */
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
    
    /**
     * Constructor that handles both an empty heap or an array of HeapNode
     * If user initialize with an array, constructor calls buildHeap() function to 
     * build a heap out of that array.
     * If nothing is given, an empty heap is created.
     * */    
    explicit MinHeap(const std::vector<Comparable> & arr = {}) : heap(arr){
      if(!heap.empty()) {
        buildHeap();
      }
    };

    /**
     * @brief public function that check if the heap is empty
     * @return true/false
     * */
    bool empty() {
      return heap.empty();
    }

    /** 
     * @brief public funtion that return current size of the heap
     * @return int size
     * */
    int size() {
      return static_cast<int>(this->heap.size());
    }
    /**
     * @brief public function that insert an element to the heap
     * @params const Comparable & node 
     * @return nothing
     * */
    void insert(const Comparable & node) {
      privateInsert(node);
    } 

    /**
     * @brief public funtion that delete the highest priority element from the heap and return that element
     * @params nothing
     * @return Comparable element 
     * */
    Comparable deleteMin() {
      return privateDeleteMin();
    }

    /**
     * @brief public function that return the value of the highest priority element
     * This function does not remove the element from the heap
     * @params nothing
     * @return const Comparable & element
     * */
    const Comparable & min() const {
      return privateMin();
    }

    /**
     * @brief public funtion to display the heap to stdout 
     * */
    void display() {
      this->privateDisplay();
    }
    
  }; //end MinHeap Class


/**
 * Helper function to build the codebook
 * params pointer to parent node, a string with inital value, reference of an array of string to store the codebook
 * */
void buildCodebook(const HeapNode<char> * parent, const std::string path, std::vector<std::string> & codebook) {
  //reach the end
  if (parent->left == nullptr && parent->right == nullptr) {
    codebook[static_cast<unsigned int>(parent->value)] = path;
    return;
  }
  
  if (parent->left != nullptr) {
    buildCodebook(parent->left, path + "0", codebook );
  }

  if (parent->right != nullptr) {
    buildCodebook(parent->right, path + "1", codebook);
  }

}

//===MAIN PROGRAM===//
int main(){
  
  //====== READ FROM FILE =====//
  std::ifstream inputFile("merchant.txt"); // Open the file
  if (!inputFile) {
      std::cerr << "Error opening input file!" << std::endl;
      return 1; // Exit if the file couldn't be opened
  }
  
  //Get file size 
  unsigned long fileSize = 0;
  char c;
  while (inputFile.get(c)) {
    if (c != '\n' && c != '\r') {
      fileSize++;
    }
  }
  // Reset the position to the beginning for further processing
  inputFile.clear(); // Clear EOF flag
  inputFile.seekg(0, std::ios::beg);// Reset the position to the beginning if to read the file again

  //Prompt users for an integer
  unsigned long outputLength;
  while (true) {
    std::string input;
    std::cout << "Enter output length: ";
    std::cin >> input;

    std::stringstream ss(input);
    if (!(ss >> outputLength) || !(ss.eof())) {
      std::cerr << "Invalid input. Please enter a valid number." << std::endl;
    }
    else if (outputLength <= 0) {
      std::cerr << "Output length must be a positive number." << std::endl;
    }
    else if (outputLength > fileSize) {
      std::cerr << "Output length too big. Should be <= " << fileSize << std::endl;
    }
    else break;
  }

  //Initialize a vector for frequency counting (size 256 for all ASCII chars)
  //NOTE: charFrequency[x]: stores the frequency of the character that has ASCII value = x.
  //Example: charFrequency[97] = 10: means character 'a'(ASCII = 97) has a frequency of 10
  std::vector<int> charFrequency(256,0);

  std::string inString; //Store N length input String to use later

  while (inputFile.get(c)) {
    if (c != '\n' && c != '\r') {
      //cast c into unsigned char then cast to unsigned int to store as an index of charFrequency array
      //NOTE we can skip <unsigned int> cast since C++ will implicitly cast it 
      charFrequency[static_cast<unsigned int>(static_cast<unsigned char>(c))]++;
      if (inString.length() < outputLength) {
        inString = inString + std::string(1, static_cast<unsigned char>(c));
      }
    }
  }
  inputFile.close();
  

  //==MAKE a node array
  //NOTE: charFrequency[x]: stores the frequency of the character that has ASCII value = x.
  //Example: charFrequency[97] = 10: means character 'a'(ASCII = 97) has a frequency of 10
  std::vector<HeapNode<char>> nodes;
  nodes.push_back(HeapNode<char>(charFrequency[32], static_cast<unsigned char>(32)));// Add the space
  for (int i = 97; i <= 122; i++) { //a-z
    nodes.push_back(HeapNode<char>(charFrequency[i], static_cast<unsigned char>(i))); // Add a-z
  }
  

  //==MAKE a MinHeap out of the node array
  MinHeap<HeapNode<char>> minHeap(nodes);
  std::cout << "\nMin Heap:" << std::endl;

  minHeap.display();//print the heap should only see 27 characters


  //===BUILD prefix-free tree
  //Vector to store all dynamically allocated nodes
  std::vector<HeapNode<char>*> allocatedNodes;

  while(minHeap.size() > 1) {
    HeapNode<char> * left = new HeapNode<char>(minHeap.deleteMin());
    allocatedNodes.push_back(left);//store to free later

    HeapNode<char> * right = new HeapNode<char>(minHeap.deleteMin());
    allocatedNodes.push_back(right);//store to free later

    //Create a dummy node with frequency - sum of 2 children frequency, dummy value: '\0'
    HeapNode<char> dummy(left->frequency + right->frequency, '$');
    //std::cout << "After adding 2 nodes" << std::endl;
    dummy.left = left;
    dummy.right = right;
    minHeap.insert(dummy);
    minHeap.display();
  }
  HeapNode<char> prefixFreeTree = minHeap.deleteMin();
  std::cout << "\nPrefix-free tree: \n"<< prefixFreeTree << std::endl;


  //BUILDING Huffman Codebook
  //NOTE: codebook[x]: stores the bitstring of the character that has ASCII value = x.
  //Example: codebook[97] = 10: means character 'a'(ASCII = 97) has a frequency of 10
  std::vector<std::string> codeBook (256, "");

  //build the codebook from the prefix-free tree
  buildCodebook(&prefixFreeTree, "", codeBook);



  //EXPORT the codebook to an output string
  std::string outString;

  //print check
  std::cout << "\nHuffman Codebook" << std::endl;
  outString = outString + "'" + std::string(1, static_cast<unsigned char>(32)) + "' : " + codeBook[32] + "\n";
  std::cout << "'" << std::string(1, static_cast<unsigned char>(32)) << "' : " << codeBook[32] << std::endl;
  for (int i = 97; i <= 122; i++) {
    outString = outString + "'" + std::string(1, static_cast<unsigned char>(i)) + "' : " + codeBook[i] + "\n";
    std::cout << "'" << std::string(1, static_cast<unsigned char>(i)) << "' : " << codeBook[i] << std::endl;
  }

  // Iterate through each character in inString and encode
  int huffmanBitTotal = 0;
  int asciiBitTotal = 0;

  for (char ch : inString) {
    // Get the Huffman encoding from codebook
    std::string huffmanCode = codeBook[static_cast<unsigned char>(ch)];

    // Calculate the bit length of the Huffman code and update totals
    int huffmanBits = huffmanCode.length();
    huffmanBitTotal += huffmanBits;

    // 7 bits for ASCII encoding
    int asciiBits = 7;
    asciiBitTotal += asciiBits;

    // Append the line to outString
    outString += huffmanCode + "\t\t" + std::to_string(huffmanBitTotal) + "\t\t" + std::to_string(asciiBitTotal) + "\n";
  }


  // Create and open the output file
  std::ofstream outfile("out.txt");  
  if (!outfile) {
    std::cerr << "Error creating output file!" << std::endl;
    return 1;
  }
  // Write output string to the file
  outfile << outString;
  outfile.close();
  std::cout << "\n====Result exported to 'out.txt' file successfully!====" << std::endl;
  
  //Free memory allocated for left and right nodes above
  for (auto & element : allocatedNodes) {
    delete element;
  }

  return 0;
} //end main
 

