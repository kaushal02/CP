/*
https://www.interviewbit.com/problems/reorder-list/

Linear time, Constant space
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
    return (A == NULL ? 0 : 1 + len(A->next));
}
ListNode* Solution::reorderList(ListNode* A) {
    int x = len(A) - 1 >> 1;
    if (not (x > 0)) return A;
    auto B = A;
    while (x--) {
        B = B->next;
    }
    auto C = B->next;
    while (C->next != NULL) {
        auto D = B->next;
        B->next = C->next;
        C->next = C->next->next;
        B->next->next = D;
    }
    C = B->next;
    B->next = NULL;
    auto D = A;
    while (C != NULL) {
        auto E = D->next;
        D->next = C;
        C = C->next;
        D->next->next = E;
        D = E;
    }
    return A;
}
