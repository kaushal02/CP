/*
https://www.interviewbit.com/problems/palindrome-list/

O(1) space O(N) time
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
int len(ListNode* A) {
    if (A == NULL) return 0;
    return 1 + len(A -> next);
}
int Solution::lPalin(ListNode* A) {
    if (A == NULL) return 1;
    if (A->next == NULL) return 1;
    int N = len(A);
    
    auto B = A;
    for (int i = 1; i < N / 2; i++) {
        B = B->next;
    }
    if (N & 1) {
        B->next = B->next->next;
    }
    auto D = B->next;
    B->next = D->next;
    auto C = D->next;
    if (C == NULL) return A->val == D->val;
    D->next = C->next;
    C->next = D;
    while (D->next != NULL) {
        B->next = D->next;
        D->next = D->next->next;
        B->next->next = C;
        C = B->next;
    }
    while (A != B) {
        if (A->val != C->val) return 0;
        A = A->next;
        C = C->next;
    }
    return B->val == D->val;
}
