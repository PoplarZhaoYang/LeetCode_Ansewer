#LeetCode 通关之路
@(E ACMer)

[toc]

by jibancanyang
***
##1.Two Sum(水)
**分析**:数学里的$\binom{2}{n}$.
**code**:
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    vector<int> ret;
                    ret.push_back(i);
                    ret.push_back(j);
                    return ret;
                }
            }
        }
    }
};
```
***
##2.Add Two Numbers(水)
**分析**大数加法,链表实现.
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ret = new ListNode(0);
        ListNode* cur = ret;
        int op = 0;
        bool c1 = true, c2 = true;
        while (true) {
            int a = 0, b = 0;
            if (c1) {
                a = l1 -> val;
                if (l1 -> next == NULL) c1 = false;
            }
            if (c2) {
                b = l2 -> val;
                if (l2 -> next == NULL) c2 = false;
            }
            cur -> val = (op + a + b) % 10;
            if (op + a + b > 9) op = 1;
            else op = 0;
            cur -> next = new ListNode(0);
            
            if (!c1 && !c2) {
                if (op) {
                    cur = cur -> next;
                    cur -> val = op;
                } else cur -> next = NULL;
                return ret;
            }
            cur = cur -> next;
            if (l1 -> next != NULL) l1 = l1 -> next;
            if (l2 -> next != NULL) l2 = l2 -> next;
        }
    }
};
```

