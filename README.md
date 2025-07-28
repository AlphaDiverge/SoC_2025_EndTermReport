# SoC EndTerm Submission
## Data Structures and Algorithms
The entire study was done with the material reference from the website, <a href="https://takeuforward.org/strivers-a2z-dsa-course/strivers-a2z-dsa-course-sheet-2">Striver's DSA Course</a>. The link was provided by my Mentor. As an extra material, I am also reading the Deitel and Deitel C++ book too, to get a stronger grip on classes which was only taken upto the surface level in the CS101 course.

I have done problems regarding these concepts, some of them will be attached in this repo itself beside this .md file. This .md file only consists of basic theory.

### Lesson 1: Basics
This was quite exactly the same as was taught in the basic CS101 course. Introductions to cout, cin, functions, etc. These are quite basic things which were already known to me in detail, hence, no detail explanation is required here.

One important material to discuss here is the Time Complexity.
#### Time Complexity
Measures how an algorithm's runtime grows as input size increases. It focuses on growth trends rather than exact time. Predicting what is the exact time for a partcular program is quite difficult. This is because the input value determines where the program terminates in the cycle. So, rather than exact time, we use the best, worst and average scenarios to judge a program's time requirement vs input size.
 - **Big-O (O) Notation**\
Describes the upper bound (worst-case scenario) of an algorithm's growth rate.
 - **Omega (Ω) Notation**\
Describes the lower bound (best-case scenario) of growth rate.
 - **Theta (Θ) Notation**\
Describes tight bounds where best and worst cases are the same.

An example for O and Ω is taking a linear search of an array. O means the value is the last value of an array when increments start from 0 and Ω means the first element in such a case is the required number. So, both are possibilities. But normally, we use the O notation as working on the worst case gives us a better idea on optimizating the program.

Common Complexities:
 - O(1): Constant time
 - O(log n): Logarithmic (binary search)
 - O(n): Linear
 - O(n²): Quadratic (nested loops)
 - O(2ⁿ): Exponential (recursive Fibonacci)

### Lesson 2: Sorting Techniques
A good portion of these techniques were taken during the CS101 course and its labs. This is one of the most important basic data structures that we can use. Sorting algorithms are the precursors required in array question, where binary sorting can be used, which can reduce the time usage a lot.

Note: For the below sorting methods, I have only added the worst case scenario and not any optimized cases.

The major sorting techniques are shown below,
 - **Selection Sort**\
Time Complexity: Always O(n²).\
This particular method works by choosing the smallest element in the array in each pass through and swaps them into place. It is quite basic.

        void selectionSort(int arr[], int n) {
            for (int i = 0; i < n-1; i++) {
                int min = i;
                for (int j = i+1; j < n; j++) {
                    if (arr[j] < arr[min]) min = j;
                }
                swap(arr[i], arr[min]);
            }
        }

 - **Bubble Sort**\
Time Complexity: Always O(n²).\
This particular method works by swapping two adjacent variables into order. The algorithm does many pass by's and hence at the end the larger variables are 'bubbled' to the end and smaller ones to the start.

        void bubbleSort(int arr[], int n) {
            for (int i = 0; i < n-1; i++) {
                bool swapped = false;
                for (int j = 0; j < n-i-1; j++) {
                    if (arr[j] > arr[j+1]) {
                        swap(arr[j], arr[j+1]);
                        swapped = true;
                    }
                }
                if (!swapped) break;
            }
        }

The normal bubble sort has no bool swapped terms, this has just been added as a mechanism so that, if the array is already sorted, the process ends quickly. But this is quite useless in problems online as most test cases don't follow this. But in real life, such a technique is quite important.

 - **Insertion Sort**\
Time Complexity: Always O(n²).\
This particular method works by passing through all the array elements form the 2nd element onwards. It works by choosing sub arrays and sorting them and then adding 1 more element on and on and placing it in the right spot. It starts at 2 elements, which is easily done. Then the 3rd element in the next run, is placed at the exact spot where it belongs. The same continues forward.

        void insertionSort(int arr[], int n) {
            for (int i = 1; i < n; i++) {
                int key = arr[i], j = i-1;
                while (j >= 0 && arr[j] > key) {
                    arr[j+1] = arr[j];
                    j--;
                }
                arr[j+1] = key;
            }
        }

 - **Merge Sort**\
Time Complexity: Always O(n logn).\
This particular method works by recursively splitting up one particular array further and further into smaller arrays and piecing together the split up arrays, by backtracking the recursion. The elements are merged together in the sorted order only. That means, two arrays are combined back by taking elements from the start of the array one by one, according to which number is smaller or if the array elements are over.

        void merge(int arr[], int l, int m, int r) {
            int n1 = m - l + 1, n2 = r - m;
            int L[n1], R[n2];
            for (int i = 0; i < n1; i++) L[i] = arr[l + i];
            for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
            int i = 0, j = 0, k = l;
            while (i < n1 && j < n2) {
                if (L[i] <= R[j]) arr[k++] = L[i++];
                else arr[k++] = R[j++];
            }
            while (i < n1) arr[k++] = L[i++];
            while (j < n2) arr[k++] = R[j++];
        }
        
        void mergeSort(int arr[], int l, int r) {
            if (l < r) {
                int m = l + (r - l) / 2;
                mergeSort(arr, l, m);
                mergeSort(arr, m+1, r);
                merge(arr, l, m, r);
            }
        }

 - **Quick Sort**\
Time Complexity: Always O(n logn). But it could go upto O[n²} if the pivot is chosen poorly.\
This particular method works by recursively splitting up one particular array further and further into smaller arrays by choosing a pivot element or point in the particular array. If the pivot chosen is close to the median of the data, its fine, else, it could be bad.

        int partition(int arr[], int low, int high) {
            int pivot = arr[high], i = low;
            for (int j = low; j < high; j++) {
                if (arr[j] < pivot) swap(arr[i++], arr[j]);
            }
            swap(arr[i], arr[high]);
            return i;
        }
        
        void quickSort(int arr[], int low, int high) {
            if (low < high) {
                int pi = partition(arr, low, high);
                quickSort(arr, low, pi-1);
                quickSort(arr, pi+1, high);
            }
        }

 - **Recursive Bubble Sort**\
Time Complexity: Always O(n²).\
Its the same time complexity, but easier to write the code for, hence it gets a special mention.

        void recursiveBubbleSort(int arr[], int n) {
            if (n == 1) return;
            for (int i = 0; i < n-1; i++) {
                if (arr[i] > arr[i+1]) swap(arr[i], arr[i+1]);
            }
            recursiveBubbleSort(arr, n-1);
        }

 - **Recursive Insertion Sort**\
Time Complexity: Always O(n²).\
Its the same time complexity, but easier to write the code for, hence it gets a special mention, similar to the recursive bubble sort.

The Merge Sort feels to be best of all the above sorting techniques due to the ability of the Merge Sort to have stable worst case scenario times unlike the Quick Sort which very much depends on the choice of conditions.

### Lesson 3: Arrays
Basic theory is well known, whether it be arrays or vectors. The application was more focused in this chapter. I have attatched some of the problems that I have solved during this exercise.

### Lesson 4: Binary Search
This is the iterative version of the binary search. The binary search works on sorted arrays. The array is split into two parts again and again and checked which part the target belongs to. This reduces the number of elements to go through.

    int binarySearch(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
    
        while (left <= right) {
            int mid = left + (right - left) / 2;
    
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

The same in recursive form is,

    int binarySearchRecursive(const vector<int>& arr, int target, int left, int right) {
        if (left > right) return -1;
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) return binarySearchRecursive(arr, target, mid + 1, right);
        else return binarySearchRecursive(arr, target, left, mid - 1);
    }

Its time complexity is O[logn].\
The only difference is the space complexity which keeps a track of the memory used up by the data. This is greater for the recursive method than the iterative method.\

An issue with binary search is that, the data must be sorted. If unsorted, sorting will also add to it. But for sorted data, binary outperforms linear search(ie: going through each element from start to finish).

### Lesson 5: Strings
This too has been covered in details in the CS101 course. Problems have been solved by me in this, but there is a more comprehensive lesson on strings at the end of the course. Hence, I will add those codes after that.

### Lesson 6: Linked Lists
This too, like strings and arrays have been covered in CS101. But this is quite an important data structure. Hence, its theory is given below.\

A linked list works on the principle of pointers and structs. A struct is a non-primitive data type which holds a builder containing data of any type.

    struct Example{
        int age;
        string name;
        string address;
        int mobile;
    };

Whenever we need to store some data of this sort, we declare an object as,

    Example myobject;

For a linked list, what happens is that, a pointer is declared inside the struct definition so that, one struct object can point to the next element or object.

<img src="https://media.geeksforgeeks.org/wp-content/uploads/20220712172013/Singlelinkedlist.png">

    struct node{
        int value;
        node* next;
    }

Here, node* holds the address value of another data of data type struct.\

A linked list connects the elements with one another and hence stores them. An advantage here commpared to arrays is that the linked list can be made in such a way that the elements are not located next to each other. Hence, not heap of memory must be alloted to it. When needed we can use that memory or leave it. This occurs in the heap, for a linked list as we use the 'new' tag for making a new struct object.\

An important division for linked lists is the direction of traversibility. If we can only move in one direction(ie: only next pointer) then it is a singly-linked linked list. If traversilbility is in both directions(ie: prev and next pointers) then it is a doubly linked list.\

Problems done on this are attached in the repo.

### Lesson 7: Recursion
This is a concept that has very little theory on it. A function calling the same function is termed as recursion. Base cases are setup to prevent infinite looping. Each call to itself returns a value or changes and entity that executes an algorithm. Iterative steps require more coding whereas recursive methods are more easier to code. Recursive steps do have a disadvantage of taking more space to store varaiables as each call might need new variables.\

Problems done will be attatched.

### Lesson 8: Bit Manipulation
This lesson just dealt with basic bit manipulation. The use in problems can be seen from the code i uploaded on my repo. The details discussed were OR, AND, XOR and NOT operations. Also right and left shifts were also taught.

### Lesson 9: Stacks and Queues
These are data structures which are quite important. The stack and queue store data and help them to be taken out in particular order.\

The stack operates on Last In First Out principle(LIFO) and the queue operates on First in First Out principle(FIFO).

<img src="https://miro.medium.com/v2/resize:fit:680/1*gElPyOaYbFQPIDm5ucI8MQ.png">

#### The Stack
The operations to work on the stack are written by us ourselves to match the description.

    class Stack {
      int size;
      int * arr;
      int top;
      public:
        Stack() {
          top = -1;
          size = 1000;
          arr = new int[size];
        }
      void push(int x) {
        top++;
        arr[top] = x;
      }
      int pop() {
        int x = arr[top];
        top--;
        return x;
      }
      int Top() {
        return arr[top];
      }
      int Size() {
        return top + 1;
      }
    };

The pop and push have similar meaning as the vector data type operations.

#### The Queue
The operations to work on the queue are written by us ourselves to match the description.

    class Queue {
      int * arr;
      int start, end, currSize, maxSize;
      public:
        Queue() {
          arr = new int[16];
          start = -1;
          end = -1;
          currSize = 0;
        }
    
      Queue(int maxSize) {
        ( * this).maxSize = maxSize;
        arr = new int[maxSize];
        start = -1;
        end = -1;
        currSize = 0;
      }
      void push(int newElement) {
        if (currSize == maxSize) {
          cout << "Queue is full\nExiting..." << endl;
          exit(1);
        }
        if (end == -1) {
          start = 0;
          end = 0;
        } else
          end = (end + 1) % maxSize;
        arr[end] = newElement;
        cout << "The element pushed is " << newElement << endl;
        currSize++;
      }
      int pop() {
        if (start == -1) {
          cout << "Queue Empty\nExiting..." << endl;
        }
        int popped = arr[start];
        if (currSize == 1) {
          start = -1;
          end = -1;
        } else
          start = (start + 1) % maxSize;
        currSize--;
        return popped;
      }
      int top() {
        if (start == -1) {
          cout << "Queue is Empty" << endl;
          exit(1);
        }
        return arr[start];
      }
      int size() {
        return currSize;
      }
    };

Function names have similar meanings as the vector operators here too.

Just a sidenote, below are the implementations of the stack and queue using each other and some other data structures,
 - **Stack using Queue**

        class Stack {
          queue < int > q;
          public:
            void Push(int x) {
              int s = q.size();
              q.push(x);
              for (int i = 0; i < s; i++) {
        
                q.push(q.front());
                q.pop();
              }
            }
          int Pop() {
            int n = q.front();
            q.pop();
            return n;
          }
          int Top() {
            return q.front();
          }
          int Size() {
            return q.size();
          }
        };

 - **Queue using Stack**

        struct Queue {
          stack < int > input, output;
        
          void Push(int data) {
            while (!input.empty()) {
              output.push(input.top());
              input.pop();
            }
            cout << "The element pushed is " << data << endl;
            input.push(data);
            while (!output.empty()) {
              input.push(output.top());
              output.pop();
            }
          }
          
          int Pop() {
            if (input.empty()) {
              cout << "Stack is empty";
              exit(0);
            }
            int val = input.top();
            input.pop();
            return val;
          }
          
          int Top() {
            if (input.empty()) {
              cout << "Stack is empty";
              exit(0);
            }
            return input.top();
          }
          
          int size() {
            return input.size();
          }
        };

 - **Stack using Linked List**
Assume that stackNode is a struct with necessary data skeleton.

        void stackPush(int x) {
            stackNode * element = new stackNode(x);
            element -> next = top;
            top = element;
            cout << "Element pushed" << "\n";
            size++;
          }

- **Queue using Linked List**

      class QueueNode
      {
       public: 
          int val;
          QueueNode *next;
          QueueNode(int data)
          {
             val = data;
             next = nullptr;
          }
      };  
      QueueNode *Front = nullptr, *Rear = nullptr;


### Lesson 10: Sliding Window Problems and Two Pointer problems
This particular module has little to no theory associated with it, hence i am skipping an theory writing over here. Please refer to some of the solved problems that i have done.

### Lesson 11: Heaps
Heaps are used as an easy representation of binary trees in the form of arrays themselves. The are used to permit operations of sorting like Heap Sort. The are mainly 2 types of heaps that we see, a max-heap where all the parent nodes are larger than their children and for a min-heap the vice-versa.

Also, the arrangement of nodes is given by:
 - Left child = 2i + 1
 - Right child = 2i + 2
 - Parent = (i - 1) / 2

An example of a max-heap is below:

    class MaxHeap {
    private:
        vector<int> heap;
    
        void heapifyUp(int index) {
            int parent = (index - 1) / 2;
            if (index > 0 && heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                heapifyUp(parent);
            }
        }
    
        void heapifyDown(int index) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;
    
            if (left < heap.size() && heap[left] > heap[largest]) 
                largest = left;
            if (right < heap.size() && heap[right] > heap[largest]) 
                largest = right;
    
            if (largest != index) {
                swap(heap[index], heap[largest]);
                heapifyDown(largest);
            }
        }
    
    public:
        void insert(int value) {
            heap.push_back(value);
            heapifyUp(heap.size() - 1);
        }
    
        int extractMax() {
            if (heap.empty()) return -1;
            int max = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);
            return max;
        }
    
        void printHeap() {
            for (int val : heap) cout << val << " ";
            cout << endl;
        }
    };

The operations that can be done are already coded up inside the class of the max-heap.


### Lesson 12: Greedy Algorithms
The below introduction is from various sources. Its hard to explain what a greedy algorithm does, but easy to show its working. Please refer to the solved problems.
1. Introduction to Greedy Algorithms
Greedy algorithms are a class of algorithms that make locally optimal choices at each step with the hope of achieving a globally optimal solution. They are widely used in optimization problems where a sequence of choices leads to the best possible outcome.

Key Idea:
At each decision point, pick the best possible move without reconsidering previous choices.
No backtracking (unlike dynamic programming).

2. Characteristics of Greedy Algorithms
For a problem to be solved using a greedy approach, it must satisfy two properties:

Greedy Choice Property
A global optimum can be reached by selecting a locally optimal choice at each step.
Example: In the Activity Selection Problem, choosing the earliest finishing activity first ensures maximum non-overlapping activities.

Optimal Substructure
The optimal solution to the problem contains optimal solutions to its subproblems.
Example: In Fractional Knapsack, the best way to fill a knapsack of capacity W depends on the best way to fill smaller capacities.

### Lesson 13: Binary Trees
These are data structures that provide easy data tracking and filtering if needed. They are very important in many problems. They mainly has a primary root and each node has two children that could further have more children. Its like an inverted tree. The last node is called as a leaf. The code for a tree is as below:

    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

### Lesson 14: Binary Search Trees
The structures allow for easy searching of required values using the property of a binary tree. It is made in such a way that, the right side child of any node is greater than its parent and the left side node is lesser than its parent. It allows for quick seaching. It's time complexity is O(logn).

### Lesson 15: Graphs
In a very short manner, if we explain what graphs are, they are a type of data structure which has the ability to store information/value of each node and also keeps a track of what node is related to which, ie: are the neighbours linked with the current node. They are incredibly useful in path problems.

### Lesson 16: Dynamic Programming
This is a method where, to find the answers to large and complex problems, we either use a bottom-up process, where we use the values of already known smaller cases to find the answer of the complex case or we could have a top-down approach where, we recursively go through combinations of smaller, known cases to add up to the complex case. Memo-ization could be used to keep track of already computed values to decrease amount of time taken. To get a better idea, refer to the solved problems.

### Lesson 17: Tries
This data structure is similar to a binary tree, but, has a key difference. That is, this data structure can have any number of children as needed, hence, this could be used to store words or user IDs, etc. Theoretically, the trie is only that. A better understanding of this can be received from the solved problems.

### Lesson 18: Strings
Not much theory needed here. This chapter is simply a programming exercise.


#### This is all i completed for the SoC-2025 Project.
