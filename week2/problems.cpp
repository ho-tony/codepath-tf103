#include <iostream>
using namespace std;
struct Node {
    int val;
    Node* next;
    Node() : val(0), next(nullptr){}
    Node(int x) : val(x), next(nullptr){}
};

/*
    Function to swap adjacent nodes in a linked list.

    Share 2 questions you would ask to help understand the question:
    - Are the nodes swapped in-place, or do we need to create new nodes and manage memory allocation for each swap?
    - How should the algorithm handle an odd number of nodes (i.e., the last node has no pair to swap with)?

    List out 2-3 types of problems that we might consider and our belief of match:
    - In-place node manipulation: Likely
    - Recursive node swapping: Neutral (since we're using iteration)
    - Handling odd number of nodes: Likely (since the function needs to manage the edge case of an odd-length list)

    - We want to iterate through the linked list and swap adjacent nodes. We'll create a temporary node to serve as a placeholder,
      adjust the pointers to swap nodes in pairs, and handle cases where the list has an odd number of nodes by leaving the last one unswapped.

    Translate each sub-problem into pseudocode:
    1. If the list is empty or has only one node, return the head as no swapping is needed.
    2. Create a temporary node that points to the head of the list.
    3. Use two pointers, `prev` and `ptr`, to track the current node and the previous node.
    4. Swap the next two nodes by adjusting pointers, then move the `ptr` forward by two nodes.
    5. Repeat until no more pairs can be swapped.
    6. Return the new head of the list.

    Translate the pseudocode into Python and share your final answer:
    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: The algorithm works in-place without requiring extra space for node creation.
    - Weakness: There is a potential memory leak due to mismanagement of pointers. The code could benefit from further optimization to avoid such issues.
*/

Node* swap_node_pairs(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node tmp(0);
    tmp.next = head;
    Node* prev = &tmp;
    Node* ptr = head;
    while (ptr != nullptr && ptr->next != nullptr) {
        auto next = ptr->next;
        auto next_next = ptr->next->next;
        ptr->next = next_next;
        next_next = ptr;
        prev->next = next;
        prev = ptr;
        ptr = ptr->next;
    }
    //might be memory leak
    return tmp.next;
}
/*
    Function to rotate a linked list to the right by `k` positions.

    Share 2 questions you would ask to help understand the question:
    - How should the rotation behave if `k` is larger than the length of the linked list?
    - What should we do if `k` is zero or the linked list has only one node? Should the list remain unchanged?

    List out 2-3 types of problems that we might consider and our belief of match:
    - Rotation in a circular linked list: Likely (since we reconnect the end of the list back to the head)
    - Handling large values of `k`: Likely (since `k` can be larger than the list length, we use modulo)
    - Handling small lists (length 1 or empty): Likely (since we check for this at the start of the function)

    Write out in plain English what you want to do:
    - We want to rotate the list to the right by `k` positions. First, we calculate the length of the list and reconnect the last node to the head, making it circular.
      Then, we find the new end of the list based on `k` and break the cycle by setting the next pointer of the new end to `nullptr`. Finally, return the new head.

    Translate each sub-problem into pseudocode:
    1. If the list is empty or has only one node, return the head as no rotation is needed.
    2. Traverse the list to find the last node and the length of the list.
    3. Connect the last node back to the head to form a circular linked list.
    4. Calculate the actual number of rotations needed using `k % length`.
    5. Traverse the list to find the new tail node (which is `len - actualRotations` nodes from the head).
    6. Break the circular link by setting the next pointer of the new tail to `nullptr`.
    7. Return the node following the new tail as the new head of the rotated list.

    Translate the pseudocode into Python and share your final answer:
    (This is the C++ implementation provided.)

    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: The algorithm effectively handles large `k` values and operates in O(n) time.
    - Weakness: The function manipulates pointers multiple times, and ensuring pointer safety and handling edge cases (like empty lists) are crucial to avoid errors.
*/
Node * rotateRight(Node* head, int k) {
    if (head == nullptr || head->next == nullptr) return head;
   Node *ptr = head; 
   Node *prev = nullptr;
   int len = 1;
   while (ptr->next != nullptr) {
    prev = ptr;
    ptr = ptr->next;
    len++;
   }
   ptr->next = head;
   int actualRotations = k % len;
   int endingNode = len - actualRotations;
   ptr = head;
   prev = nullptr;
   while (endingNode-->0) {
    prev = ptr;
    ptr = ptr->next;
   }
   prev->next = nullptr;
   return ptr;

}
/*
    Function to remove the nth node from the end of a linked list.

    Share 2 questions you would ask to help understand the question:
    - How do we handle edge cases where the linked list has fewer than `n` nodes?
    - What should be done if `n` equals the length of the list, meaning the head node needs to be removed?

    List out 2-3 types of problems that we might consider and our belief of match:
    - Traversal to find the length of the list: Likely (since we need to determine the position of the nth node from the end)
    - Removing nodes in a single pass: Neutral (as this algorithm uses two passes; one to calculate length, and one to remove the node)
    - Handling edge cases for small lists: Likely (the function handles cases where there is only one or two nodes)

    Write out in plain English what you want to do:
    - We first calculate the length of the linked list. Then, we traverse the list again, stopping just before the node we want to remove. 
      We adjust the previous node's next pointer to skip over the node to be deleted. If the head is the node to be removed, we update the head.

    Translate each sub-problem into pseudocode:
    1. If the list is empty or contains only one node, return `nullptr` since we are removing the only node.
    2. Traverse the list to find its length.
    3. Create a dummy node that points to the head (to handle cases where the head is removed).
    4. Traverse the list again to stop just before the node that needs to be removed.
    5. Adjust the pointers to skip the node and connect the previous node to the next node.
    6. Return the new head of the list.

    Translate the pseudocode into Python and share your final answer:
    (This is the C++ implementation provided.)

    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: The algorithm is simple and handles edge cases like removing the head node.
    - Weakness: The algorithm requires two passes over the list. It could be optimized to work in a single pass by using the two-pointer technique.
*/

Node* removeNthFromEnd(Node* head, int n) {
    if (head == nullptr || head->next == nullptr) return nullptr;
    int len = 1;
    auto ptr = head;
    while (ptr != nullptr) {
        len++;
        ptr = ptr->next;
    }
    int idx = 0;
    Node*tmp= new Node(-1);
    tmp->next = head;
    auto prev = tmp;
    ptr = head;
    while (++idx < len - n) {
        prev = ptr;
        ptr = ptr->next;
    }
    prev->next = ptr->next;
    return tmp->next;
}
/*
    Function to perform character shifts on a string based on the given shift values.

    Share 2 questions you would ask to help understand the question:
    - How should the shifts behave for large values (e.g., shifts greater than 26)?
    - Should the result wrap around 'z' and continue from 'a' when shifting past the end of the alphabet?

    List out 2-3 types of problems that we might consider and our belief of match:
    - Handling large shift values: Likely (as we use modulo 26 to handle values greater than 26)
    - Calculating prefix sums for shifts: Likely (since we need to accumulate shifts)
    - Handling character wrapping: Likely (since we need to ensure shifts past 'z' wrap to 'a')

    Write out in plain English what you want to do:
    - We need to apply character shifts to each letter in the string based on the given shift values.
      First, we compute the prefix sum of the shifts to accumulate the total shift for each character.
      Then, for each character in the string, we apply the corresponding shift, wrapping around if necessary.

    Translate each sub-problem into pseudocode:
    1. Initialize a prefix sum array from the shifts array, starting from the last shift value and moving left.
    2. Traverse the string and apply the appropriate shift to each character, using modulo 26 for wrapping.
    3. Return the shifted string as the result.

    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: Efficient computation of prefix sums and character shifts ensures the solution works in linear time.
    - Weakness: The algorithm could be more optimized by applying shifts in-place, rather than creating a new string.
*/
string shiftingLetters(string s, vector<int>& shifts) {
    vector<int> prefix_sums(shifts.size(), 0);
    prefix_sums[prefix_sums.size() - 1] = shifts[shifts.size() - 1];
    for (int i = prefix_sums.size() - 2; i >=0; --i) {
       prefix_sums[i] = (prefix_sums[i+1] + shifts[i]) % 26;
    }


    string res = "";
    for (int i = 0; i < s.size(); ++i) {
        res += (s[i] - 'a' + prefix_sums[i]) % 26 + 'a';
    }
    return res;
}
/*
    Function to set matrix elements to zero if a zero is found in any row or column.

    Share 2 questions you would ask to help understand the question:
    - Should we use additional space to track which rows and columns should be zeroed out, or can we modify the matrix in-place?
    - How should we handle the first row and first column, which are used to mark zeroes for the rest of the matrix?

    List out 2-3 types of problems that we might consider and our belief of match:
    - In-place matrix modification: Likely (as we use the first row and first column to store flags)
    - Handling matrix boundaries: Likely (since we treat the first row and column specially)
    - Ensuring pointer safety when modifying the matrix: Neutral (since we handle pointer safety implicitly in C++)

    Write out in plain English what you want to do:
    - We need to set all elements in a row or column to zero if a zero is found in that row or column.
      We'll use the first row and column of the matrix to mark which rows and columns should be zeroed, and then update the matrix accordingly.

    Translate each sub-problem into pseudocode:
    1. Check if the first column contains any zeros and set a flag if it does.
    2. Traverse the matrix and mark the first row and first column if a zero is found.
    3. Update the rest of the matrix based on the flags in the first row and column.
    4. Zero out the first row and column if necessary, based on the initial flags.

    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: The algorithm operates in-place without using additional space, making it memory efficient.
    - Weakness: The logic for handling the first row and column separately adds complexity that can lead to edge cases if not handled carefully.
*/

void setZeroes(vector<vector<int>>& matrix) {
    bool isCol = false;
    int R = matrix.size();
    int C = matrix[0].size();
    for (int i = 0; i < R; i++) {
        if (matrix[i][0] == 0) {
            isCol = true;
        }
        for (int j = 1; j < C; j++) {
            if (matrix[i][j] == 0) {
                matrix[0][j] = 0;
                matrix[i][0] = 0;
            }
        }
    }
    for (int i = 1; i < R; i++) {
        for (int j = 1; j < C; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
    if (matrix[0][0] == 0) {
        for (int j = 0; j < C; j++) {
            matrix[0][j] = 0;
        }
    }
    if (isCol) {
        for (int i = 0; i < R; i++) {
            matrix[i][0] = 0;
        }
    }
}
/*
    Function to find the length of the longest substring that can be obtained by replacing at most `k` characters.

    Share 2 questions you would ask to help understand the question:
    - Should the character replacement be case-sensitive, or should we treat both uppercase and lowercase characters as the same?
    - How should the algorithm handle substrings that include non-alphabetical characters, or are they guaranteed to only contain lowercase letters?

    List out 2-3 types of problems that we might consider and our belief of match:
    - Sliding window technique: Likely (since we are moving the `left` and `right` pointers to adjust the window of consideration)
    - Handling multiple character replacements: Likely (as we need to keep track of how many replacements we’ve used with `k`)
    - Finding the optimal solution by brute force over all possible target characters: Likely (since we iterate over all possible letters and check their validity)

    Write out in plain English what you want to do:
    - For each character in the alphabet, treat that character as the one we want to maximize in the string. 
      Then, using a sliding window approach, count how many replacements (non-matching characters) we can make to form a valid substring of maximal length, keeping track of the longest valid substring.

    Translate each sub-problem into pseudocode:
    1. Initialize `maxlen` to store the length of the longest valid substring found.
    2. For each character in the alphabet:
       a. Use a sliding window approach to check the longest substring that can be formed by replacing at most `k` characters with the current target character.
       b. For each non-matching character encountered, decrement `numk`.
       c. If `numk` is negative (indicating we’ve used up all replacements), move the `left` pointer to shrink the window and adjust `numk`.
    3. Return the maximum length found across all possible target characters.

    Share at least one strong/weak area of your algorithm or future potential work:
    - Strength: The algorithm uses a sliding window approach to efficiently find the longest valid substring for each character.
    - Weakness: The algorithm checks all 26 characters, which increases the runtime. It could potentially be optimized by tracking the most frequent character in the window instead of iterating over every character.
*/

int characterreplacement(string s, int k) {
    int maxlen = 0;
    for (int i = 0; i < 26; ++i) {
        char ch = 'a' + i;
        int left = 0; 
        int numk = k;
        for (int right = 0; right < s.length(); ++right) {
            if (s[right] != ch) {
                numk--; 
                if (numk < 0) {
                    while (s[left] == ch) left++;
                    left++;
                    numk++;
                }
            }
            maxlen = max(right - left + 1, maxlen);
        }
    }
    return maxlen;
}


int main() {

}

