#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void helper(size_t, vector<int> & nums);

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
