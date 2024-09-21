#include <iostream>
#include <vector>

using namespace std;
int main() {

    return 0;
}

// U - Understand
// 1. What happens if the input list is empty or contains only one string?
//    -> This clarifies how to handle edge cases, especially empty input.
// 2. What if all strings in the list are completely different?
//    -> This is to understand if an empty string should be returned in such cases.

// P - Plan
// 1. Check if the input vector is empty, and if so, return an empty string.
// 2. Find the longest string in the vector (maxStr) to use as a reference for the longest common prefix.
// 3. Initialize a variable maxpfx to store the longest common prefix, starting with maxStr.
// 4. For each string in the input vector, compare it character by character with maxStr.
// 5. For each match, add the character to a temporary prefix string (prefix).
// 6. After comparing a string, if the current prefix is shorter than maxpfx, update maxpfx.
// 7. After iterating through all strings, return maxpfx as the longest common prefix.

// I - Implement
string longestCommonPrefix(vector<string>& strs) {
    string maxStr = "";
    for (const auto & s : strs) {
        if (s.size() > maxStr.size()) {
            maxStr = s;
        }
    }
    string maxpfx = maxStr;
    for (const auto & s : strs) {
        string prefix = "";
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == maxStr[i]) {
                prefix += s[i];
            } else {
                break;
            }
        }
       if (prefix < maxpfx)  {
           maxpfx = prefix;
       } 
        
    }
    return maxpfx;
}


