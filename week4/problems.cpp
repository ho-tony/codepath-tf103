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
