#include <iostream>
#include <vector>
using namespace std;


// Description:  https://leetcode.com/problems/add-two-numbers/description/


 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 


/*
    Solution:

    Time complexity:    O(max(n, m)) where n and m are the lengths of the two input lists.

    Space complexity:   O(max(n, m))
    
*/

class Solution {
public:
    // Public method that takes two ListNode pointers and returns a ListNode pointer.
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Creates a new ListNode as a dummy head to simplify list manipulation.
        ListNode* dummyHead = new ListNode(0);
        // Uses a 'tail' pointer to keep track of the last node in the result list.
        ListNode* tail = dummyHead;
        // Initializes a 'carry' variable to store the carry-over from adding two digits.
        int carry = 0;
        // Continues as long as at least one of the pointers is not null or carry is non-zero.
        while (l1 || l2 || carry) {
            // Gets the current node's value from l1, or 0 if l1 is null.
            int digit1 = (l1) ? l1->val : 0;
            // Gets the current node's value from l2, or 0 if l2 is null.
            int digit2 = (l2) ? l2->val : 0;
            // Adds the two digits and the carry.
            int sum = digit1 + digit2 + carry;
            // The new digit is the remainder of the sum divided by 10.
            int digit = sum % 10;
            // The new carry is the quotient of the sum divided by 10.
            carry = sum / 10;
            // Creates a new node with the resulting digit and stores it in 'tail'.
            tail->next = new ListNode(digit);
            // Moves the 'tail' pointer to the last node.
            tail = tail->next;
            // Advances l1 to the next node if it is not null.
            l1 = (l1) ? l1->next : nullptr;
            // Advances l2 to the next node if it is not null.
            l2 = (l2) ? l2->next : nullptr;
        }
        // Retrieves the result excluding the dummy head.
        ListNode* result = dummyHead->next;
        // Frees the memory allocated to the dummy head.
        delete dummyHead;
        // Returns the pointer to the start of the resulting list.
        return result;
    }
};

/*
    Submission 100.00% faster than other C++ submissions (28/06/2024):


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
            carry = sum/10;
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

*/




//Test

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
    //printList(l1);
    //printList(l2);
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