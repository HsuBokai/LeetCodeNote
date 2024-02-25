/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
	void swap(ListNode* iter, ListNode* n){
		int temp = iter->val;
		iter->val = n->val;
		n->val = temp;
	}
	void sort_helper(ListNode* head, ListNode* end){
		if(head == end || head->next == end) return ;
		int pivot = head->val;
		ListNode* less = head;
		ListNode* equal = head;
		ListNode* iter = head->next;
		while(iter != end){
			if(iter->val < pivot){
				swap(iter, equal->next);
				swap(equal->next, less->next);
				equal = equal->next;
				less = less->next;
			}
			else if(iter->val == pivot){
				swap(iter, equal->next);
				equal = equal->next;
			}
			iter = iter->next;
		}
		swap(head, less);
		sort_helper(head, less);
		sort_helper(equal->next, end);
	}
public:
	ListNode* sortList(ListNode* head) {
		sort_helper(head, NULL);
		return head;
	}
};