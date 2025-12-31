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
    cout << "Output: [";
    bool first = true;
    while (head) {
        if (!first) cout << ", ";
        cout << head->val;
        first = false;
        head = head->next;
    }
    cout << "]" << endl;
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Solution solution;
    
    // Example 1: l1 = [2,4,3], l2 = [5,6,4]
    ListNode* l1 = buildList({2, 4, 3});
    ListNode* l2 = buildList({5, 6, 4});
    ListNode* result1 = solution.addTwoNumbers(l1, l2);
    printList(result1);
    deleteList(l1);
    deleteList(l2);
    deleteList(result1);
    
    // Example 2: l1 = [0], l2 = [0]
    l1 = buildList({0});
    l2 = buildList({0});
    ListNode* result2 = solution.addTwoNumbers(l1, l2);
    printList(result2);
    deleteList(l1);
    deleteList(l2);
    deleteList(result2);
    
    // Example 3: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
    l1 = buildList({9, 9, 9, 9, 9, 9, 9});
    l2 = buildList({9, 9, 9, 9});
    ListNode* result3 = solution.addTwoNumbers(l1, l2);
    printList(result3);
    deleteList(l1);
    deleteList(l2);
    deleteList(result3);

    return 0;
}
