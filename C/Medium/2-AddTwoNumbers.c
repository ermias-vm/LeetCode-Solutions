// Description: https://leetcode.com/problems/add-two-numbers/description/

/*
    Approach: Iterative with Carry

    Traverse both linked lists simultaneously, adding corresponding digits.
    Maintain a carry value for sums >= 10.
    Use a dummy head node to simplify list construction.
    For each position: sum = digit1 + digit2 + carry, new digit = sum % 10.
    Update carry = sum / 10 for the next iteration.
    Continue until both lists are exhausted and carry is zero.

    Time complexity: O(max(n, m)) - Traverse the longer list.
    Space complexity: O(max(n, m)) - Result list has at most max(n,m)+1 nodes.
*/

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = NULL;
    struct ListNode* tail = &dummy;
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry != 0) {
        int digit1 = (l1 != NULL) ? l1->val : 0;
        int digit2 = (l2 != NULL) ? l2->val : 0;
        int sum = digit1 + digit2 + carry;
        int digit = sum % 10;
        carry = sum / 10;

        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = digit;
        newNode->next = NULL;

        tail->next = newNode;
        tail = newNode;

        if (l1 != NULL) l1 = l1->next;
        if (l2 != NULL) l2 = l2->next;
    }

    return dummy.next;
}

// Test
struct ListNode* buildList(int* nums, int size) {
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* tail = &dummy;

    for (int i = 0; i < size; i++) {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = nums[i];
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }

    return dummy.next;
}

void printList(struct ListNode* head) {
    printf("Output: [");
    int first = 1;
    while (head != NULL) {
        if (!first) printf(", ");
        printf("%d", head->val);
        first = 0;
        head = head->next;
    }
    printf("]\n");
}

void deleteList(struct ListNode* head) {
    while (head != NULL) {
        struct ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Example 1: l1 = [2,4,3], l2 = [5,6,4]
    int nums1a[] = {2, 4, 3};
    int nums1b[] = {5, 6, 4};
    struct ListNode* l1 = buildList(nums1a, 3);
    struct ListNode* l2 = buildList(nums1b, 3);
    struct ListNode* result1 = addTwoNumbers(l1, l2);
    printList(result1);
    deleteList(l1);
    deleteList(l2);
    deleteList(result1);

    // Example 2: l1 = [0], l2 = [0]
    int nums2a[] = {0};
    int nums2b[] = {0};
    l1 = buildList(nums2a, 1);
    l2 = buildList(nums2b, 1);
    struct ListNode* result2 = addTwoNumbers(l1, l2);
    printList(result2);
    deleteList(l1);
    deleteList(l2);
    deleteList(result2);

    // Example 3: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
    int nums3a[] = {9, 9, 9, 9, 9, 9, 9};
    int nums3b[] = {9, 9, 9, 9};
    l1 = buildList(nums3a, 7);
    l2 = buildList(nums3b, 4);
    struct ListNode* result3 = addTwoNumbers(l1, l2);
    printList(result3);
    deleteList(l1);
    deleteList(l2);
    deleteList(result3);

    return 0;
}

