#include <vector>
#include <stack>
#include <cmath>
using namespace std;
/*
Questions:
1. How do we handle collisions between asteroids moving in opposite directions?
   Answer: By using a stack to keep track of the asteroids moving to the right. When a left-moving asteroid is encountered, we compare it with the top of the stack to determine which asteroid explodes.

2. What determines whether an asteroid will explode or survive during a collision?
   Answer: The asteroid with the smaller absolute value explodes. If both asteroids have the same size, both explode.

Types of Problems:
- Likely: Stack-based problems, simulation of real-world scenarios, collision detection.
- Unlikely: Problems not involving order-based processing or pairwise interactions.

Plain English Explanation:
We need to simulate the collision of asteroids moving in a straight line. Asteroids moving to the right are pushed onto a stack. When a left-moving asteroid is encountered, it collides with the asteroids in the stack moving to the right. Depending on their sizes, one or both asteroids may explode. The surviving asteroids are collected and returned.

Pseudocode:
1. Initialize an empty stack to keep track of asteroids moving to the right.
2. Iterate through each asteroid in the input list:
   a. If the asteroid is moving to the right (positive), push it onto the stack.
   b. If the asteroid is moving to the left (negative):
      i. While the stack is not empty and the top asteroid is moving to the right:
         - Compare the sizes of the top asteroid and the current asteroid.
         - If the top asteroid is smaller, pop it from the stack.
         - If they are equal, pop the top asteroid and discard the current one.
         - If the top asteroid is larger, discard the current asteroid.
      ii. If the current asteroid was not destroyed, push it onto the stack.
3. Convert the stack to a vector to represent the remaining asteroids.
4. Return the resulting vector.
*/
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> past;
        for (const auto& a : asteroids) {
            if (a > 0) {
                past.push_back(a);
            } else {
                while (!past.empty() && past.back() > 0 && past.back() < abs(a)) {
                    past.pop_back();
                    
                }
                if (!past.empty() && past.back() == abs(a)) {
                    past.pop_back();
                } else if (past.empty() || past.back() < 0) {
                    past.push_back(a);
                } 
            }

        }
        return past;
    }
};

/*
Questions:
1. How can we validate if a given pop sequence is possible from a push sequence using a stack?
   Answer: By simulating the push and pop operations using an auxiliary stack and ensuring the pop sequence can be achieved without violating stack order.

2. What conditions must hold true for the pop sequence to be valid?
   Answer: Each element in the pop sequence must match the top of the auxiliary stack after appropriate push operations. The auxiliary stack must be empty at the end.

Types of Problems:
- Likely: Stack manipulation, sequence validation, simulation of data structures.
- Unlikely: Problems not involving ordered data processing or stack-based operations.

Plain English Explanation:
We need to determine if a given sequence of pop operations can result from a sequence of push operations on a stack. By using an auxiliary stack, we simulate the push and pop processes, ensuring that the pop sequence follows the Last-In-First-Out (LIFO) order of the stack.

Pseudocode:
1. Initialize an empty auxiliary stack and a pointer for the pushed sequence.
2. Iterate through each element in the popped sequence:
   a. While the auxiliary stack is empty or the top does not match the current pop element:
      i. If all elements in the pushed sequence have been pushed, return false.
      ii. Push the next element from the pushed sequence onto the auxiliary stack.
   b. If the top of the auxiliary stack matches the current pop element, pop it from the stack.
   c. Otherwise, return false.
3. After processing all elements, return true if the auxiliary stack is empty; otherwise, return false.
*/
class SolutionValidate {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> test_stk;
        int ptr = 0;
        for (int i = 0; i < popped.size(); ++i) {
            while (ptr < pushed.size() && (test_stk.empty() || test_stk.top() != popped[i])) {
                test_stk.push(pushed[ptr]);
                ptr++;
              
            }
            if (test_stk.top() == popped[i]) {
                test_stk.pop();
            } else {
                return false;
            }
        }
        return test_stk.empty() && ptr == pushed.size();
    }
};



/*
Questions:
1. How do we efficiently track recent requests within a sliding time window?
   Answer: By using a queue to store the timestamps of the requests and removing those that fall outside the time window.

2. What is the time complexity of the ping operation in the RecentCounter?
   Answer: O(1) amortized time, since each timestamp is added and removed at most once.

Types of Problems:
- Likely: Queue-based problems, sliding window algorithms, real-time data processing.
- Unlikely: Problems that do not involve temporal ordering or real-time constraints.

Plain English Explanation:
We need to count the number of recent requests within a 3000 milliseconds window. Each time a new request arrives, we add its timestamp to a list and remove any timestamps that are older than 3000 milliseconds from the current request. The size of the remaining list represents the number of recent requests.

Pseudocode:
1. Initialize an empty list to store timestamps and a pointer for the start of the window.
2. For each ping(t):
   a. While the earliest timestamp is less than t - 3000, increment the start pointer.
   b. Add the current timestamp to the list.
   c. Return the number of timestamps within the window.
*/

class RecentCounter {
public:
    vector<int> past_requests;
    int left = 0;
    RecentCounter() {
        
    }
    
    int ping(int t) {
      while (left < past_requests.size() && t - 3000 > past_requests[left]) {
        left++;
      }
      past_requests.push_back(t);
      return past_requests.size() - left ;
    }
};

/*
Questions:
1. How can we implement a queue using two stacks?
   Answer: By using one stack for enqueue operations and another for dequeue operations, transferring elements as needed to maintain queue order.

2. What is the amortized time complexity for enqueue and dequeue operations in the MyQueue implementation?
   Answer: Both enqueue and dequeue operations have an amortized time complexity of O(1).

Types of Problems:
- Likely: Stack and queue manipulation, data structure implementation, algorithm optimization.
- Unlikely: Problems that do not require simulating one data structure using another.

Plain English Explanation:
We need to create a queue using two stacks. One stack (bottomToTop) handles the enqueue operations, while the other stack (topToBottom) handles the dequeue and peek operations. When dequeueing or peeking, if the dequeue stack is empty, we transfer all elements from the enqueue stack to the dequeue stack, reversing the order to maintain queue behavior.

Pseudocode:
1. Initialize two stacks: bottomToTop for enqueue operations and topToBottom for dequeue operations.
2. To push(x):
   a. Push x onto bottomToTop.
3. To pop():
   a. If topToBottom is empty, transfer all elements from bottomToTop to topToBottom.
   b. Pop the top element from topToBottom and return it.
4. To peek():
   a. If topToBottom is empty, transfer all elements from bottomToTop to topToBottom.
   b. Return the top element of topToBottom.
5. To empty():
   a. Return true if both stacks are empty; otherwise, return false.
*/
class MyQueue {
public:
    stack<int> bottomToTop;
    stack<int> topToBottom;
    MyQueue() {
        
    }
    
    void push(int x) {
        bottomToTop.push(x); 

    }

    void refill() {
        if (topToBottom.empty()) {
            while (!bottomToTop.empty()) {
                int top = bottomToTop.top();
                topToBottom.push(top);
                bottomToTop.pop();
            }
        }
    }
    
    int pop() {
        refill();
        int val = topToBottom.top();
        topToBottom.pop();
        return val; 
    }
    
    int peek() {
       refill(); 
       return topToBottom.top();
    }
    
    bool empty() {
       return topToBottom.empty() && bottomToTop.empty();
    }
};



/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */


/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

