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
***
##3.Longest Substring Without Repeating Characters(尺取法(双指针))
**题意**:求字符串最长不重复字符子序列的长度.
**分析**:
> **暴力**:最直接的方法就是通过枚举所有的头和尾把所有的子串找出来,然后判断这个子串是不是满足其中字符全部不重复.这样的时间复杂度是$O(n ^ 3)$,显然效率极低.
> **尺取法(双指针)** :维护一个双指针,保证头尾之间的序列一定是不重复的,用一个letters表来记录是否重复.不熟悉尺取法(又名双指针)的话会比较困难.该算法时间复杂度$O(n)$,是最佳时间复杂度.

**尺取法的代码**:
```cpp

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        bool letters[260];
        memset(letters, 0, sizeof(letters));
        int head = 0, tail = 0, maxlen = 0;
        letters[s[head]] = true;
        while (tail < s.size()) {
            if (head < tail && letters[s[tail] ]) {
                letters[s[head++]] = false;
                while (s[head - 1] != s[tail]) letters[s[head++]] = false;
            }
            letters[s[tail]] = true;
            maxlen = max(tail - head + 1, maxlen);
            tail++;
        }
        return maxlen;
    }
};
```
***
##5.Longest Palindromic Substring
**题意**:求字符串的最长回问子串.
**分析**:
- 首先很容易想到暴力的方法,把回文子串分成奇数长度和偶数长度两种情况,把每个字符当做回文串的中心,然后求以它为奇数串中心(或者偶数串的左中心),求它为中心的最长回文串的长度.这样复杂度是$O(n ^2)$,LeetCode也能AC....

**暴力的代码:**
```
class Solution {
public:
    string longestPalindrome(string s) {
        int retodd = 0, reteven = 0, odd = 0, even = 0;
        for (int i = 0; i < s.size(); i++) {
            for (int l = i, r = i; l >= 0 && r < s.size(); l--, r++) {
                if (s[l] != s[r]) break;
                if (r - l + 1 > retodd) {
                    retodd = r - l + 1;
                    odd = i;
                } 
            }
            
            for (int l = i, r = i + 1; l >= 0 && r < s.size(); l--, r++) {
                if (s[l] != s[r]) break;
            
                if (r - l + 1 > reteven) {
                    reteven = r - l + 1;
                    even = i;
                } 
            }
        }
        if (retodd > reteven) {
            return s.substr(odd - retodd / 2, retodd);
        } else {
            return s.substr(even - reteven / 2 + 1, reteven);
        }
    }
};
```
**Manacher算法**:强悍的马拉车算法,时间复杂度$O(n)$...
```cpp
class Solution {
public:
    string preProcess(string s)
    {
        int n = s.length();
        if (n == 0) return "^$";
        string ret = "^";
        for (int i = 0; i < n; i++)
            ret += "#" + s.substr(i, 1);
    
        ret += "#$";
        return ret;
    }
    
    string longestpalindrome(string s)
    {
        string T = preProcess(s);
        int n = T.length();
        int* P = new int[n];
        int C = 0, R = 0;
        for (int i = 1; i < n - 1; i++) {
            int i_mirror = 2 * C - i; // 等于i' = C - (i-C)
    
        P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
        // 尝试扩展中心为i的回文
        while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
            P[i]++;
    
        // 如果中心为i的回文超越了R，根据已扩展的回文来调整中心
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
            }
        }
    
        // 找出P中的最大值
        int maxLen = 0;
        int centerIndex = 0;
        for (int i = 1; i < n-1; i++) {
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }
        delete[] P;
    
        return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
    }
    string longestPalindrome(string s) {
        return longestpalindrome(s);
    }
};
```


