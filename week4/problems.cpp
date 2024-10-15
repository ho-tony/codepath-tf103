#include <iostream>
#include <algorithm>
#include <unordered_set>
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;
/*
Questions:
1. How do we merge two sorted linked lists into one sorted list?
   Answer: By iteratively comparing the nodes of both lists and linking them in sorted order.

2. What is the time complexity of the merge process?
   Answer: O(n + m), where n and m are the lengths of the two lists.

Types of Problems:
- Likely: Linked list manipulation, merging algorithms, recursion.
- Unlikely: Problems not involving linked lists or ordered data.

Plain English Explanation:
Given two sorted linked lists, we want to merge them into a single sorted linked list. We can achieve this by comparing the heads of both lists and repeatedly attaching the smaller node to the merged list.

Pseudocode:
1. Create a dummy node to serve as the start of the merged list.
2. Use a pointer to track the current position in the merged list.
3. While both lists are not empty:
   a. Compare the current nodes of both lists.
   b. Attach the smaller node to the merged list and move the corresponding pointer forward.
4. If one list is exhausted, attach the remaining nodes of the other list.
5. Return the next node of the dummy as the head of the merged list.
*/
ListNode* partition(ListNode* head, int x) {
    ListNode lessHead(0);
    ListNode * lessPtr = &lessHead;
    ListNode * ptr = head;
    while (ptr != nullptr) {
        if (ptr->val < x) {
            lessPtr->next = new ListNode(ptr->val);
            lessPtr = lessPtr->next;
        }
        ptr = ptr->next;
    }
    
    ListNode geHead(0);
    ListNode* gePtr = &geHead;
    ptr = head;
    while (ptr != nullptr) {
        if (ptr->val >= x) {
            gePtr->next = new ListNode(ptr->val);
            gePtr = gePtr->next;
        }
        ptr = ptr->next;
    }
    gePtr->next = nullptr;
    lessPtr->next = geHead.next;
    
    return lessHead.next;

}
/*
QQuestions:
1. How do we determine if two strings are anagrams?
   Answer: Two strings are anagrams if they contain the same characters in the same frequency, just rearranged.

2. How can we efficiently group anagrams together?
   Answer: By sorting each string or using a character count as a key in a hash map to group them.

Types of Problems:
- Likely: String manipulation, hashing, grouping similar items.
- Unlikely: Problems not involving strings or character frequency.

Plain English Explanation:
We need to group a list of strings so that each group contains strings that are anagrams of each other. To do this, we can sort each string and use the sorted string as a key in a hash map. All strings that, when sorted, are identical will be grouped together.

Pseudocode:
1. Initialize an empty hash map where the key is the sorted string and the value is a list of anagrams.
2. Iterate through each string in the input list.
   a. Sort the string to create the key.
   b. Append the original string to the list corresponding to the sorted key.
3. Collect all the groups from the hash map and return them.
*/
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> anagrams;
    for (const auto& s : strs) {
        string cpy = s;
        sort(cpy.begin(), cpy.end());
        if (!anagrams.contains(cpy)) {
            anagrams[cpy] = vector<string>();
        }
        anagrams[cpy].push_back(s);
    }
    vector<vector<string>> res_anagrams;
    for (const auto & entry : anagrams) {
        res_anagrams.push_back(entry.second);
    }
    return res_anagrams;
}
/*
Questions:
1. How do we find the length of the longest consecutive sequence in an array?
   Answer: By using a hash set to allow O(1) lookups and iterating to find consecutive numbers.

2. Why do we check if the current number is the start of a sequence?
   Answer: To ensure we only start counting from the beginning of a sequence, avoiding redundant checks.

Types of Problems:
- Likely: Array manipulation, hash tables, sequence detection.
- Unlikely: Problems that don't require tracking or ordering of elements.

Plain English Explanation:
We aim to find the length of the longest sequence of consecutive integers in an unsorted array. By storing all elements in a hash set, we can efficiently check for the presence of consecutive numbers starting from each potential sequence start.

Pseudocode:
1. Insert all numbers into a hash set for O(1) access.
2. Initialize a variable to track the maximum length.
3. Iterate through each number in the array:
   a. If the number is the start of a sequence (i.e., num - 1 is not in the set), proceed.
   b. Incrementally check for the next consecutive numbers and count the sequence length.
   c. Update the maximum length if the current sequence is longer.
4. Return the maximum length found.
*/
int lengthOfLongestSubstring(string s) {
    unordered_set<char> char_set;
    size_t max_len = 0;
    int left = 0;
    for (int i = 0; i < s.size(); ++i) {
        while (char_set.contains(s[i])) {
            char_set.erase(s[left]);
            left++;
        }
        char_set.insert(s[i]);
        max_len = max(max_len, char_set.size());
    }
    return (int) max_len;
}
int main() {

}
