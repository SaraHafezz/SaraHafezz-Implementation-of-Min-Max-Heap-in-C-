//
//  main.cpp
//
//  Created by Sara Haf on 4/27/24.
//
// Implementation of Min/Max Heap in C++


#include <iostream>
#include <vector>
#include <queue>

class Heap {
private:
    std::vector<int> heap;  // vector that stores heap elements
    bool isMinHeap; // this flag indicatesif its a min or max heap
    
    // maintain heap properties
    void heapifyUp(int index);  // moves an element up to its position
    void heapifyDown(int index);    // moves an element down to its position
    
public:
    // constructor that will initialize a heap
    Heap(bool isMin) : isMinHeap(isMin) {}
    
    // functions
    void insert(int value);
    int extractRoot();
    bool isEmpty() const { return heap.empty(); }
    bool checkHeapProperty();
    void printTraversal();
};

// function - moves an element up to position
void Heap::heapifyUp(int index) {
    if (index <= 0) {
        return;
    }
    
    int parentIndex = (index - 1) / 2;
    
    if ((isMinHeap && heap[index] < heap[parentIndex]) ||
        (!isMinHeap && heap[index] > heap[parentIndex])) {
        std::swap(heap[index], heap[parentIndex]);
        heapifyUp(parentIndex); // Recursively heapify up
    }
}

// function - moves an element down to position
void Heap::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallestOrLargest = index;
    
    if (leftChild < heap.size() &&
        ((isMinHeap && heap[leftChild] < heap[smallestOrLargest]) ||
         (!isMinHeap && heap[leftChild] > heap[smallestOrLargest]))){
        smallestOrLargest = leftChild;
    }
    
    if (rightChild < heap.size() &&
        ((isMinHeap && heap[rightChild] < heap[smallestOrLargest]) ||
         (!isMinHeap && heap[rightChild] > heap[smallestOrLargest]))) {
        smallestOrLargest = rightChild;
    }
    
    if (smallestOrLargest != index) {
        std::swap(heap[index], heap[smallestOrLargest]);
        heapifyDown(smallestOrLargest);
    }
}

// function - inserts an element into heap
void Heap::insert(int value) {
    heap.push_back(value);
    typename std::vector<int>::size_type currentIndex = heap.size() - 1;
    heapifyUp(static_cast<int>(currentIndex));
}

// function - extracts root element from heap
int Heap::extractRoot() {
    if (isEmpty()) {
        std::cerr << "Error: Heap is empty!" << std::endl;
        return -1;
    }
    
    int root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!isEmpty()) {
        heapifyDown(0);
    }
    
    return root;
}

// function - checks to see if the heap satisfies heap property
bool Heap::checkHeapProperty() {
    if (isMinHeap) {
        for (int i = 1; i < heap.size(); ++i) {
            if (heap[i] < heap[(i - 1) / 2]) {
                return false;
            }
        }
    } else {
        for (int i = 1; i < heap.size(); ++i) {
            if (heap[i] > heap[(i - 1) / 2]) {
                return false;
            }
        }
    }
    return true;
}

// function - printing elements from heap in level-order traversal order
void Heap::printTraversal() {
    if (isEmpty()) {
        std::cout << "Heap is empty." << std::endl;
        return;
    }
    
    std::queue<int> q;
    q.push(0); // this starts from the root
    
    while (!q.empty()) {
        auto size = q.size();   // using auto size for the size variable
        for (size_t i = 0; i < size; ++i) {    // using size_t for the i variable
            int current = q.front();
            q.pop();
            std::cout << heap[current] << " ";
            
            int leftChild = 2 * current + 1;
            int rightChild = 2 * current + 2;
            
            if (leftChild < static_cast<int>(heap.size())) {    // converting size method to int using static_cast
                q.push(leftChild);
            }
            if (rightChild < static_cast<int>(heap.size())) {
                q.push(rightChild);
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    int rootValue;
    // prompting user to enter what they want to create - min or max heap
    std::cout << "Enter the root value (0 for Min Heap, 1 for Max Heap): ";
    std::cin >> rootValue;
    
    // this tells us whether the heap should be a min or max heap depending on user's input
    bool isMinHeap = (rootValue == 0);
    
    // this will create a heap object with either a min or max type
    Heap heap(isMinHeap);
    
    int root;
    // prompting user to enter a root value for the binary tree
    std::cout << "Enter the root value of the binary tree: ";
    std::cin >> root;   // storing the root value enterd by the user
    
    heap.insert(root);  // this inserts the root value into the heap
    
    // this asks the user to enter five integers - smaller or larger than the root value
    std::cout << "Enter five integers, each smaller or larger than the root value: ";
    for (int i = 0; i < 5; ++i) {
        int num;
        std::cin >> num;    // prompting the user to enter the numbers coming after the number they entered
        heap.insert(num);   // this inserts the integers entered into the heap
    }
    
    // checking to see if the heap is properly satisfied
    if (heap.checkHeapProperty()) {
        std::cout << "Heap extracted: ";
        // extracting and printing the elements from the heap until it is empty
        while (!heap.isEmpty()) {
            std::cout << heap.extractRoot() << " ";
        }
        std::cout << std::endl;
    } else {
        // if the numbers inputted by the user do not form a valid heap, then display the following error message
        std::cerr << "Error: The submitted numbers do not form a valid heap!" << std::endl;
    }
    return 0;
}
