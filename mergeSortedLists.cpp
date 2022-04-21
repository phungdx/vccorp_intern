#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// Node structure
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Solution 1: Brute force
ListNode* merge2Lists_recursive(ListNode* l1, ListNode* l2){
    if(!l1){
        return l2;
    }

    if(!l2){
        return l1;
    }

    if(l1->val < l2->val){
        l1->next = merge2Lists_recursive(l1->next, l2);
        return l1;
    }

    if(l1->val >= l2->val){
        l2->next = merge2Lists_recursive(l1, l2->next);
        return l2;
    }

    return NULL;
}

ListNode* mergeKLists_1(vector<ListNode*>& lists){
    if(lists.size() == 0) return NULL;

    ListNode* head = lists[0];
    for(int i = 1; i < lists.size(); ++i){
        head = merge2Lists_recursive(head, lists[i]);
    }

    return head;
}


// Solution 2: using priority queue
ListNode* mergeKLists_2(vector<ListNode*>& lists){
    if(lists.size() == 0) return NULL;

    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 0; i < lists.size(); ++i){
        ListNode* head = lists[i];
        while(head){
            pq.push(head->val);
            head = head->next;
        }
    }

    ListNode* start;
    ListNode* end;

    while(!pq.empty()){
        if(start == NULL){
            start = new ListNode(pq.top());
            end = start;
            pq.pop();
        }

        else{
            end->next = new ListNode(pq.top());
            pq.pop();
            end = end->next;
        }
    }

    return start;


}


// Solution 3: devide and conquer
ListNode* mergeK(vector<ListNode*>& lists, int k){
    while(k != 0){
        int i = 0, j = k;
        while(i < j){
            lists[i] = merge2Lists_recursive(lists[i], lists[j]);
            ++i;
            --j;
            if(i >= j){
                k = j;
            }
        }
    }
}

ListNode* mergeKLists_3(vector<ListNode*>& lists){
    if(lists.size() == 0) return NULL;
    if(lists.size() == 1) return lists[0];
    return mergeK(lists, lists.size() - 1);
}



int main(){
    return 0;
}