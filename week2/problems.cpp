#include <iostream>

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


int main() {

}

