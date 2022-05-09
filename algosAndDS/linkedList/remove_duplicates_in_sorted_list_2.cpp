#include<iostream>
using namespace std;



struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *dummy = new ListNode(0,head);
        ListNode* slow = dummy;
        
        while(head){
            if(head->next && head->val == head->next->val){
                while(head->next && head->val == head->next->val)
                    head = head->next;
                slow->next = head->next;
            }
            
            else
                slow = slow->next;
            head = head->next;
        }
     
        return dummy->next;
        
        
    }
};



int main(){
	ListNode* node1 = new ListNode(5);
	ListNode* node2 = new ListNode(4, node1);
	ListNode* node3 = new ListNode(4, node2);
	ListNode* node4 = new ListNode(3, node3);
	ListNode* node5 = new ListNode(3, node4);
	ListNode* node6 = new ListNode(2, node5);
	ListNode* node7 = new ListNode(1, node6);

	Solution mySol;
	mySol.deleteDuplicates(node7);
	while(node7){
		cout << node7->val << ' ';
		node7 = node7->next;
	}

	return 0;
}