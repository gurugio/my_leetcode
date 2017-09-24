// 3. Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(char* s) {
    int len = strlen(s);
    int max, cur_max, end;
    int counter[255];
    
    max = cur_max = end = 0;
    memset(counter, 0, sizeof(int)*255);
    
    while (end < len) {
        if (counter[s[end]] == 0) {
            counter[s[end]]++;
            cur_max++;
            end++;
        } else {
            int c;
            memset(counter, 0, sizeof(int)*255);
            if (max < cur_max)
                max = cur_max;
            cur_max = 0;
            c = s[end];
            // back to non-duplicated character??
            while (s[end-1] != c)
                end--;
        }
    }
    if (max < cur_max)
        max = cur_max;
    return max;
}

// 2. Add Two Numbers
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int c, l, r, v;
    struct ListNode *head, *prev, *cur;
    
    prev = NULL;
    c = 0;
    do {
        l = l1 ? l1->val : 0;
        r = l2 ? l2->val : 0;
        
        v = l + r + c;
        c = v / 10;
        
        cur = calloc(1, sizeof(*cur));
        cur->val = v % 10;
        
        if (!prev)
            head = cur;
        else
            prev->next = cur;
        prev = cur;
        
        l1 = l1 ? l1->next : NULL;
        l2 = l2 ? l2->next : NULL;
    } while (l1 || l2);
    
    if (c) {
        cur = calloc(1, sizeof(*cur));
        cur->val = 1;
        prev->next = cur;
    }
    
    return head;
}
