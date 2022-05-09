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
    ListNode* swapPairs(ListNode* head) {
        // If there are less than 2 nodes in the given nodes,
        // then no need to do anything just return the list as it is.
        if(!head || !head->next) return head;
		
        ListNode* dummyNode = new ListNode();
        
        ListNode* prevNode = dummyNode;
        ListNode* currNode = head;
        
        while(currNode && currNode->next){
            prevNode->next = currNode->next;
            currNode->next = prevNode->next->next;
            prevNode->next->next = currNode;
            
            prevNode = currNode;
            currNode = currNode->next;
        }
        
        return dummyNode->next;
    }
};


int main(){
    ListNode* node1 = new ListNode(4);
    ListNode* node2 = new ListNode(3,node1);
    ListNode* node3 = new ListNode(2,node2);
    ListNode* node4 = new ListNode(1,node3);

    ListNode* curr = node4;
    while(curr){
        cout << curr->val << ' ';
        curr = curr->next;
    }

    cout << '\n';
    Solution mySol;
    ListNode*head = mySol.swapPairs(node4);
    curr = head;
    while(curr){
        cout << curr->val << ' ';
        curr = curr->next;
    }
	return 0;
}