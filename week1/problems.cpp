// TF 103 Session 1 Prework By Tony Ho


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <map>
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

// U - Understand
// 1. What should we return if the second string is longer than the first one? 
//    -> Return False, as it cannot be a substring.
// 2. What if the second string is empty? 
//    -> Return True, as an empty string is a substring of any string.

// P - Plan
// 1. Check edge cases: if the second string is empty, return True. 
//    If the second string is longer than the first string, return False.
// 2. Iterate through all possible starting positions in the first string where the second string can begin.
// 3. For each position, check character by character if the second string matches the substring starting at that position.
// 4. If a match is found, return True. If no match is found, return False.

bool isSubstring(const string& s1, const string& s2) {
    if (s2.empty()) return true;
    
    if (s2.length() > s1.length()) return false;

    for (int i = 0; i <= s1.length() - s2.length(); ++i) {
        int j = 0;
        while (j < s2.length() && s1[i + j] == s2[j]) {
            j++;
        }
        if (j == s2.length()) {
            return true;
        }
    }

    return false;
}

// U - Understand
// 1. What should we do if the strings are of different lengths? 
//    -> We can treat the missing digits in the shorter string as zeros.
// 2. What should the function return if both input strings are empty or contain only zeros? 
//    -> If both are empty or contain only zeros, return "0".

// P - Plan
// 1. Start from the last character of both binary strings and move backwards.
// 2. Use two pointers to access the characters in both strings.
// 3. If one string runs out of characters, treat its value as '0'.
// 4. Add the digits from both strings along with the carry.
// 5. Append '1' or '0' to the result based on the sum modulo 2, and update the carry if necessary.
// 6. If there's a carry left after processing all digits, append '1' to the result.
// 7. Return the final result string.

string addBinary(string a, string b) {
    int ptrA = a.size() - 1;
    int ptrB = b.size() - 1;
    int carry = 0;
    string resultBinary = "";
    while (ptrA >= 0 || ptrB >= 0) {
        char aChar = (ptrA >= 0) ? a[ptrA] : '0';
        char bChar = (ptrB >= 0) ? b[ptrB] : '0';
        int opRes = (aChar - '0') + (bChar - '0') + carry;
        string ins = (opRes % 2 != 0) ? "1" : "0";
        carry = (opRes >= 2) ? 1 : 0;
        resultBinary = ins + resultBinary;
        ptrA--;
        ptrB--;
    }
    if (carry > 0) {
        resultBinary = "1" + resultBinary;
    }
    return resultBinary;
}


/*
    Problem: Find the minimum number of replacements needed to reduce `n` to 1. If `n` is even, divide it by 2; if `n` is odd, you can either add 1 or subtract 1.

    Share 2 questions you would ask to help understand the question:
    - Are there constraints on the size of `n`? Specifically, how large can `n` be?
    - Should we consider any optimizations, or are there concerns about time complexity (e.g., for very large values of `n`)?

    List out 2-3 types of problems that we might consider and our belief of match:
    - Recursive approach for number transformations: Likely (since the problem naturally breaks down into smaller subproblems)
    - Dynamic programming to avoid redundant calculations: Neutral (the current implementation is recursive, but it may benefit from memoization or dynamic programming)
    - Handling large input values: Unlikely (the current implementation may struggle with large values due to recursion depth, and no optimizations like memoization are applied)

    Write out in plain English what you want to do:
    - We want to reduce the integer `n` to 1 using the fewest steps possible. If `n` is even, we divide it by 2. If `n` is odd, we either increment or decrement it, then recursively solve the smaller problem. Our goal is to find the minimum number of steps to achieve this.

    Translate each sub-problem into pseudocode:
    1. If `n` is 1, return 0 as no more steps are needed.
    2. If `n` is even, recursively reduce `n` by dividing it by 2.
    3. If `n` is odd, recursively reduce `n` by either adding 1 or subtracting 1, and take the minimum number of steps from both options.
    4. Return the result plus 1 for the current step.

    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: The recursive solution is simple and easy to understand, naturally capturing the problem's recursive nature.
    - Weakness: The algorithm can be inefficient for large inputs due to repeated calculations and deep recursion. It could be improved with memoization or a dynamic programming approach to store intermediate results.
*/

int int_replacement(int n) {
    if (n == 1) return 0;
    return (n % 2 == 0) ? int_replacement(n / 2) : min(int_replacement(n + 1), int_replacement(n - 1));
}
int int_replacement(int n) {
    if (n == 1) return 0;
    return (n % 2 == 0) ? int_replacement(n/2) : min(int_replacement(n + 1), int_replacement(n-1));
}

/*
    Problem: Convert a Roman numeral string to an integer.

    Share 2 questions you would ask to help understand the question:
    - How should we handle invalid Roman numeral inputs (such as incorrect ordering or invalid characters)?
    - Is there a limit on the size of the Roman numeral, or can it be arbitrarily large?

    List out 2-3 types of problems that we might consider and our belief of match:
    - Mapping Roman symbols to integers: Likely (since each Roman numeral corresponds to a specific integer value)
    - Handling subtractive notation (e.g., IV for 4, IX for 9): Likely (this is an essential part of Roman numerals)
    - Handling large Roman numerals: Unlikely (since the largest Roman numeral is well-defined with `MMM` representing 3000)

    Write out in plain English what you want to do:
    - We want to iterate through the Roman numeral string from left to right, converting each symbol to its integer value.
      If a smaller value symbol appears before a larger value symbol, we subtract the smaller value from the total. Otherwise, we add the value to the total.

    Translate each sub-problem into pseudocode:
    1. Create a dictionary to map Roman numeral symbols to their integer values.
    2. Initialize a variable to store the final result.
    3. Iterate through the Roman numeral string.
    4. If the current symbol is smaller than the next symbol, subtract its value; otherwise, add its value.
    5. Return the final result.

    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: The algorithm is efficient and handles all valid Roman numeral inputs correctly.
    - Weakness: The algorithm does not validate the input for invalid Roman numerals or non-Roman characters.
*/

int romanToInt(string s) {
    unordered_map<char, int> roman_map = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
                                          {'C', 100}, {'D', 500}, {'M', 1000}};
    int result = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i + 1 < s.size() && roman_map[s[i]] < roman_map[s[i + 1]]) {
            result -= roman_map[s[i]];
        } else {
            result += roman_map[s[i]];
        }
    }
    return result;
}




/*
    Problem: Convert an integer to a Roman numeral string.

    Share 2 questions you would ask to help understand the question:
    - Should we ensure that the integer falls within the valid range for Roman numerals (1 to 3999)?
    - Are there specific performance requirements, or should we focus on simplicity?

    List out 2-3 types of problems that we might consider and our belief of match:
    - Converting integers to Roman symbols: Likely (since each Roman numeral corresponds to a range of integer values)
    - Handling subtractive notation (e.g., IV for 4, IX for 9): Likely (this is essential to ensure a valid Roman numeral)
    - Handling large integers (greater than 3999): Unlikely (since Roman numerals typically stop at 3999)

    Write out in plain English what you want to do:
    - We want to convert the integer into its Roman numeral equivalent by mapping specific integer ranges to the appropriate Roman symbols.
      We repeatedly subtract the largest Roman numeral that fits into the remaining value of the integer, appending the corresponding Roman symbol to the result string.

    Translate each sub-problem into pseudocode:
    1. Create a list of Roman numeral symbols and their corresponding integer values.
    2. Initialize a string to store the Roman numeral result.
    3. For each value-symbol pair, repeatedly append the symbol to the result while subtracting the value from the integer.
    4. Return the Roman numeral string.

    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: The algorithm is simple and efficiently handles the full range of valid Roman numerals.
    - Weakness: The algorithm does not handle cases where the integer is outside the valid Roman numeral range (greater than 3999 or less than 1).
*/

string intToRoman(int num) {
    vector<pair<int, string>> roman_map = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
                                           {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
                                           {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
    string result = "";
    for (auto &[value, symbol] : roman_map) {
        while (num >= value) {
            result += symbol;
            num -= value;
        }
    }
    return result;
}
