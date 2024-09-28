#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void helper(size_t, vector<int> & nums);

/* 
Questions:
1. How do we ensure that triplets are unique?
   Answer: We sort the input array first and skip duplicate elements during the iteration.
2. How do we handle cases where the array contains less than three elements?
   Answer: If the input array has fewer than three elements, no processing is done, and an empty result is returned.

Types of Problems:
- Likely: Finding all unique triplets that sum up to zero using sorting and two-pointer techniques.
- Unlikely: Problems that do not involve arrays or do not focus on sum-based constraints.

Plain English Explanation:
We want to find all unique triplets in the array whose sum is zero. We sort the array and then use the two-pointer technique to search for valid pairs for each element while avoiding duplicates.

Pseudocode:
1. Sort the input array.
2. Loop through each element in the array (i).
3. Skip duplicates of the main element (i).
4. Use two pointers (left and right) to find pairs that sum with nums[i] to zero.
5. Store valid triplets and avoid duplicates.

*/
vector<vector<int>> triplets;
vector<vector<int>> threeSum(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size() - 2; ++i) {
        if (i != 0 && nums[i - 1] == nums[i])
            continue;
        helper(i, nums);
    }
    return triplets;
}

void helper(size_t startidx, vector<int>& nums) {
    size_t right = nums.size() - 1;
    size_t left = startidx + 1;

    while (left < right) {
        int sum = nums[left] + nums[right] + nums[startidx];
        if (sum == 0) {
            triplets.push_back(
                vector<int>{nums[startidx], nums[left], nums[right]});
            right--;
            while (right > left && nums[right] == nums[right + 1]) right--;
            left++;
            while (left < right && nums[left] == nums[left - 1]) left++;
        }
        else if (sum < 0) {
            left++;
            while (left < right && nums[left] == nums[left - 1]) left++;
        }
        else if (sum > 0) {
            right--;
            while (right > left && nums[right] == nums[right + 1]) right--;
        } 
    }
}
/*
Questions:
1. How do we handle non-alphanumeric characters?
   Answer: We skip non-alphanumeric characters by incrementing or decrementing the respective pointers.
2. How do we compare characters case-insensitively?
   Answer: We use the tolower() function to compare characters case-insensitively.

Types of Problems:
- Likely: String manipulation problems, especially palindrome checking.
- Unlikely: Problems not involving strings or character validation.

Plain English Explanation:
We use two pointers, one starting from the beginning and the other from the end of the string. We skip non-alphanumeric characters and compare the remaining characters case-insensitively to check if the string is a palindrome.

Pseudocode:
1. Set left and right pointers to the beginning and end of the string, respectively.
2. While left <= right:
    - Skip non-alphanumeric characters by moving the left or right pointers.
    - Compare the characters at the left and right pointers (case-insensitive).
    - If they don't match, return false.
    - If they match, move both pointers inward.
3. If all characters match, return true.
*/
bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    while (left <= right) {
        while (left < s.size() - 1 && !isalnum(s[left])) {
            left++;
        } 
        while (right >= 0 && !isalnum(s[right])) {
            right--;
        }
        if (left > right) break;
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
/*
Questions:
1. How do we calculate the area between two lines?
   Answer: We calculate the area by multiplying the shorter height by the distance between the two pointers.
2. How do we move the pointers to maximize the area?
   Answer: We move the pointer with the shorter line inward to potentially find a larger area.

Types of Problems:
- Likely: Problems involving finding maximum areas using two pointers (e.g., container with water).
- Unlikely: Problems not related to geometry or area calculations.

Plain English Explanation:
We use two pointers, one starting at the beginning and one at the end of the array. We calculate the area between the two lines and move the pointer with the shorter height inward to try and find a larger area.

Pseudocode:
1. Set the left and right pointers to the beginning and end of the array, respectively.
2. While left < right:
    - Calculate the area between the two lines using the shorter height.
    - Update the maximum area if necessary.
    - Move the pointer corresponding to the shorter height inward.
3. Return the maximum area found.
*/
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int area = 0;
    while (left < right) {
        area = max(area, min(height[left], height[right]) * (right - left));
        if (height[left] < height[right]) left++;
        else right--; 
    }
    return area;
}

int main() {

}
