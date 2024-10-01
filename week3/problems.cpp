#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void helper(size_t, vector<int> & nums);
bool knows(const int a, const int b);
/*
Questions:
1. How do we determine if someone is a celebrity?
   Answer: A celebrity is known by everyone but knows no one. We check for these two conditions.
2. How do we optimize the search for a celebrity?
   Answer: First, we find people who are known by everyone. Then, we check if they know anyone else.

Types of Problems:
- Likely: Problems involving social graphs, relationships, or celebrity identification.
- Unlikely: Problems not involving pairwise relationships or hierarchy.

Plain English Explanation:
We want to find if there's a person (celebrity) in a group of people such that this person is known by everyone but knows no one else. We check each person to see if they meet these conditions.

Pseudocode:
1. Loop through all people to find candidates who are known by everyone.
2. For each candidate, check if they know anyone.
3. If a candidate doesn't know anyone, return their index as the celebrity.
4. If no valid candidate is found, return -1.
*/
int findCelebrity(int n) {
    vector<int> people_everyone_knows;
    for (int i = 0; i < n; ++i) {
        bool isKnown = true;
        for (int j = 0; j < n; ++j) {
            if (!knows(j, i)) {
                isKnown = false;
                break;
            }
        }
        if (isKnown) {
            people_everyone_knows.push_back(i);
        }
    }
    if (people_everyone_knows.size() == 0) {
        return -1;
    }
    for (const auto& person : people_everyone_knows) {
        bool knows_someone = false;
        for (int i = 0; i < n; ++i) {
            if (person == i) continue;
            if (knows(person, i)) {
                knows_someone = true;
                break;
            }
        }
        if (!knows_someone) {
            return person;
        }
    }
    return -1;
}
/*
Questions:
1. How do we minimize the number of crossed bricks?
   Answer: By finding the most frequent brick edges where we can place the vertical line.
2. Why do we skip the last brick in each row?
   Answer: The last brick forms the wall's outer edge, so the vertical line cannot cross beyond the wall.

Types of Problems:
- Likely: Problems related to finding optimal cuts or lines, or partitioning data.
- Unlikely: Problems not involving geometry or partitions.

Plain English Explanation:
We want to draw a vertical line through a brick wall such that the number of crossed bricks is minimized. By tracking where the brick edges align (except for the last edge in each row), we can place the line where the fewest bricks will be crossed.

Pseudocode:
1. Create a map to track how many brick edges align at each point.
2. For each row, add the cumulative width of bricks (skipping the last brick) to the map.
3. Find the position where the most edges align.
4. Return the total number of rows minus the number of aligned edges at that position.
*/
int leastBricks(vector<vector<int>>& wall) {
    unordered_map<long, long> openings;
    for (int r = 0; r < wall.size(); ++r) {
        long part = 0;
        for (int c = 0; c < wall[r].size() - 1; ++c) {
            part += (long)wall[r][c];
            openings[part]++;
        }
    }
    long max_openings = 0;
    for (const auto& open : openings) {
        max_openings = max(max_openings, open.second);
    }
    return wall.size() - max_openings;
}


// for the love of god do not do this in c++, lambda function are way to strict!
int leastInterval(vector<char>& tasks, int n) {
    unordered_map<char, int> freq_map;
    auto lambda = [&freq_map](const char& a, const char& b) {
        return freq_map[b] > freq_map[a];
    };
    priority_queue<char, vector<char>, decltype(lambda)> pq(lambda);
    for (const auto& t : tasks)
        freq_map[t]++;
    for (const auto& t : freq_map)
        pq.push(t.first);
    int time = 0;
    while (!pq.empty()) {
        int tmp = n+1;
        vector<char> next;
        int cnt = 0;
        while (tmp-- && !pq.empty()) {
            auto top = pq.top();
            pq.pop();
            freq_map[top]--;
            if (freq_map[top] > 0) {
                next.push_back(top);
            }

            cnt++;
        }
        for (const auto & ch : next) {
            pq.push(ch);
        }
        time += (pq.empty()) ? cnt : n + 1;
        
    }
    return time;
}

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
