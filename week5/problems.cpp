#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

class RecentCounter {
public:
    vector<int> window;
    int left = 0;
    RecentCounter() {}

    int ping(int t) {

        window.push_back(t);
        while (left < window.size() && window[left] < t - 3000) {
            left++;
        }
        return window.size() - left;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
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

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stk;
        int poppedPtr = 0;
        for (int i = 0; i < pushed.size(); ++i) {
            stk.push(pushed[i]);
            while (!stk.empty() && popped[poppedPtr] == stk.top()) {
                stk.pop();
                poppedPtr++;
            }
        }
        for (int i = poppedPtr; i < popped.size(); ++i) {
            if (stk.top() == popped[i]) {
                stk.pop();
            } else {
                return false;
            } 
        }
        return stk.empty();
    }
};





int main() {


}
