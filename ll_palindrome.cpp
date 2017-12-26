/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
int isPalindrome(ListNode* A) {
    int len = 0;
    ListNode *cur = A;
    while(cur) {
        ++len;
        cur = cur->next;
    }
    
    if (len <= 1) {
        return 1;
    }
    if (len == 2) {
        return A->val == A->next->val;
    }
    
    // Reverse half the list
    ListNode *prev = nullptr;
    cur = A;
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
    int palindrome = 1;
    ListNode *bwdPrev = cur;
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
