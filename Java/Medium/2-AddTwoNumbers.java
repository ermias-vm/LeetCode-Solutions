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

import java.util.*;

class ListNode {
    int val;
    ListNode next;
    ListNode() {
    }
    ListNode(int val) {
        this.val = val;
    }
    ListNode(int val, ListNode next) {
        this.val = val;
        this.next = next;
    }
}

class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummyHead = new ListNode(0);
        ListNode tail = dummyHead;
        int carry = 0;

        while (l1 != null || l2 != null || carry != 0) {
            int digit1 = (l1 != null) ? l1.val : 0;
            int digit2 = (l2 != null) ? l2.val : 0;
            int sum = digit1 + digit2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            tail.next = new ListNode(digit);
            tail = tail.next;

            l1 = (l1 != null) ? l1.next : null;
            l2 = (l2 != null) ? l2.next : null;
        }

        return dummyHead.next;
    }
}

// Test
class Test {
    public static ListNode buildList(int[] nums) {
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;
        for (int num : nums) {
            tail.next = new ListNode(num);
            tail = tail.next;
        }
        return dummy.next;
    }

    public static String formatList(ListNode head) {
        StringBuilder sb = new StringBuilder("[");
        boolean first = true;
        while (head != null) {
            if (!first) sb.append(", ");
            sb.append(head.val);
            first = false;
            head = head.next;
        }
        sb.append("]");
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: l1 = [2,4,3], l2 = [5,6,4]
        ListNode l1 = buildList(new int[] {2, 4, 3});
        ListNode l2 = buildList(new int[] {5, 6, 4});
        System.out.println("Output: " + formatList(solution.addTwoNumbers(l1, l2)));

        // Example 2: l1 = [0], l2 = [0]
        l1 = buildList(new int[] {0});
        l2 = buildList(new int[] {0});
        System.out.println("Output: " + formatList(solution.addTwoNumbers(l1, l2)));

        // Example 3: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
        l1 = buildList(new int[] {9, 9, 9, 9, 9, 9, 9});
        l2 = buildList(new int[] {9, 9, 9, 9});
        System.out.println("Output: " + formatList(solution.addTwoNumbers(l1, l2)));
    }
}
