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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;
        if (head == NULL) return head;
        ListNode* ret = head;
        ListNode* h = head;
        ListNode* tmp = head;
        ListNode* hh = tmp;
        ListNode* a = tmp;
        for (int i = 0; i < k; ++i) {
            if (tmp == NULL) return ret;
            tmp = tmp->next;
        }
        ListNode* b = a->next;
        ListNode* c = b->next;
        a->next = tmp;
        for (int i = 1; i < k; ++i) {
            c = b->next;
            b->next = a;
            a = b;
            b = c;
        }
        ret = a;
        while (true) {
            hh = tmp;
            a = tmp;
            for (int i = 0; i < k; ++i) {
                if (tmp == NULL) return ret;
                //cout << tmp->val << endl;
                tmp = tmp->next;
            }
            b = a->next;
            c = b->next;
            a->next = tmp;
            for (int i = 1; i < k; ++i) {
                c = b->next;
                b->next = a;
                a = b;
                b = c;
            }
            h->next = a;
            h = hh;
        }
        return NULL;
    }
};