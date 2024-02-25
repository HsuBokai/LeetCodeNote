/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* a = head;
        ListNode* b = head;
        ListNode* bb = head;
        while (true) {
            if (a == NULL) break;
            a = a->next;
            if (a == NULL) break;
            a = a->next;
            bb = b;
            b = b->next;
        }
        if (b == NULL) return head;
        if (b == head) return NULL;
        bb->next = b->next;
        return head;
    }
};