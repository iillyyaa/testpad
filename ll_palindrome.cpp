#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Determine if a given list is a palindrome.
 * This solution is linear time, constant memory. It temporarily modifies
 * the list, but returns it to the original state.
 * It is not robust to loops in the list.
 */
int isPalindrome(ListNode * const list) {
    // Obtain the length of the list
    int len = 0;
    for(ListNode *cur = list; cur; ++len) {
        cur = cur->next;
    }

    // Trivial degenerate cases
    if (len <= 1) {
        return 1;
    }

    // Reverse the first half of the list
    ListNode *prev = nullptr;
    ListNode *cur = list;
    int numRev = 0;
    while (numRev < len/2) {
        ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        ++numRev;
    }

    // Now cur points to the second half
    // And prev points to the first half, reversed
    ListNode *fwd = cur;
    ListNode *bwd = prev;
    if (len / 2 == (len-1)/2) {
        // Odd number of nodes, so skip the middle element
        fwd = fwd->next;
    }

    // Re-reverse the first half, while at the same time
    // traversing the second half and comparing the values
    int palindrome = 1;
    ListNode *bwdPrev = cur; // starting point for re-linking the two halfs
    while(fwd && bwd) {
        if (fwd->val != bwd->val) {
            palindrome = 0;
        }

        ListNode *next = bwd->next;
        bwd->next = bwdPrev;
        bwdPrev = bwd;
        bwd = next;
        fwd = fwd->next;
    }

    return palindrome;
}

int main(int argc, char const * const * argv) {
    ListNode *head = nullptr;
    ListNode *tail = nullptr;

    for(int c=1; c<argc; ++c) {
        ListNode *nn = new ListNode(atoi(argv[c]));
        if (tail) {
            tail->next = nn;
        } else {
            head = nn;
        }
        tail = nn;
    }

    std::cerr << "Input:\n";
    for(ListNode *l=head; l; l=l->next) {
        std::cerr << l->val << "\n";
    }

    int palindrome = isPalindrome(head);
    std::cerr << "Output:\n" << palindrome << "\n";

    std::cerr << "List after testing:\n";
    for(ListNode *l=head; l; l=l->next) {
        std::cerr << l->val << "\n";
    }

    return !palindrome;
}
