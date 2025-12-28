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

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* tail = dummyHead;
        int carry = 0;
        while (l1 || l2 || carry) {
            int digit1 = (l1) ? l1->val : 0;
            int digit2 = (l2) ? l2->val : 0;
            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10;
            tail->next = new ListNode(digit);
            tail = tail->next;
            l1 = (l1) ? l1->next : nullptr;
            l2 = (l2) ? l2->next : nullptr;
        }
        ListNode* result = dummyHead->next;
        delete dummyHead;
        return result;
    }
};

// Test

ListNode* buildList(const std::vector<int>& nums) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int num : nums) {
        tail->next = new ListNode(num);
        tail = tail->next;
    }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    vector<int> nums1 = {2, 4, 3};
    vector<int> nums2 = {5, 6, 4};
    ListNode* l1 = buildList(nums1);
    ListNode* l2 = buildList(nums2);
    // printList(l1);
    // printList(l2);
    Solution solution;
    ListNode* result = solution.addTwoNumbers(l1, l2);
    cout << "Output: ";
    printList(result);

    // Correctamente liberar la memoria de las listas
    deleteList(l1);
    deleteList(l2);
    deleteList(result);

    return 0;
}
