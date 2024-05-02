/*
https://www.interviewbit.com/problems/partition-list/

O(1) space, O(N) time
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
ListNode* Solution::partition(ListNode* A, int B) {
    ListNode * Hi = new ListNode(0);
    ListNode * Lo = new ListNode(0);
    ListNode * endHi = Hi, * endLo = Lo;
    while (A != NULL) {
        if (A->val < B) {
            endLo->next = A;
            A = A->next;
            endLo = endLo->next;
        }
        else {
            endHi->next = A;
            A = A->next;
            endHi = endHi->next;
        }
    }
    endLo->next = Hi->next;
    endHi->next = NULL;
    return Lo->next;
}

/********** FIRST ATTEMPT: BAD SOLUTION ************/
ListNode* Solution::partition(ListNode* A, int B) {
    if (A == NULL) return A;
    ListNode *F = A, *P = NULL;
    while (F->next != NULL and F->val < B) {
        P = F;
        F = F->next;
    }
    ListNode* Q = F->next;
    while (Q != NULL) {
        if (Q->val < B) {
            F->next = Q->next;
            if (P == NULL) {
                Q->next = A;
                A = Q;
                P = A;
            }
            else {
                Q->next = P->next;
                P->next = Q;
                P = P->next;
            }
            Q = F->next;
        }
        else {
            F = F->next;
            Q = Q->next;
        }
    }
    return A;
}