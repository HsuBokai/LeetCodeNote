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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL) return NULL;
        if (head->next == NULL) return head;
        ListNode* a = head;
        ListNode* b = head->next;
        while (true) {
            if (a->val != b->val) {
                if (a == head) {
                    b = a;
                    break;
                }
                if (b->next == NULL) return b;
                if (b->val != b->next->val) break;
            }
            a = a->next;
            b = b->next;
            if (b == NULL) return NULL;
        }
        ListNode* ret = b;
        while (true) {
            if (b->next->next == NULL) return ret;
            else if (b->next->next->val != b->next->val) {
                b = b->next;
            } else {
                a = b->next;
                while (a != NULL && a->val == b->next->val) a = a->next;
                b->next = a;
                if (a == NULL) return ret;
            }
        }
        return ret;
    }
};