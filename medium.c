// 8. String to Integer (atoi)
int myAtoi(char* str) {
    int minus;
    char *buf = calloc(12, sizeof(char));
    int len;
    unsigned long result;
    int overflow;
    
    while (*str == ' ')
        str++;

    if (*str == '-') {
        minus = 1;
	str++;
    } else if (*str == '+') {
	    minus = 0;
	    str++;
    } else
	    minus = 0;

    while (*str == '0')
        str++;
    
    len = 0;
    while (len < 11 && isdigit(*str))
        buf[len++] = *str++;

    if (len > 10) {
	    overflow = 1;
	    goto ret_result;
    }
    
    result = 0;
    overflow = 0;
    for (int i = 0; i < len; i++) {
	    result *= 10;
	    result += (buf[i] - '0');
	    if ((minus == 0 && result > 2147483647) ||
		(minus == 1 && result > 2147483648)) {
		    overflow = 1;
		    break;
	    }
    }

ret_result:
    printf("temp:%d %d %s %ld\n", minus, overflow, buf, result);
    if (overflow == 1 && minus == 1)
	    result = -2147483648;
    else if (overflow == 1 && minus == 0)
	    result = 2147483647;
    else if (minus == 1)
	    result = -result;

    return result;
}

// 6. ZigZag Conversion
char* convert(char* s, int numRows) {
    int len = strlen(s);
    int *index = calloc(len, sizeof(int));
    int i, j;
    char *ret = calloc(len + 1, sizeof(char));
    int ret_index;
    int rotate = (2 * numRows) - 2;

    if (rotate == 0)
	    rotate = 1;

    for (i = 0; i < len; i++) {
	    if ((i % rotate) <= (numRows - 1))
		    index[i] = (i % rotate);
	    else
		    index[i] = (rotate - (i % rotate));
    }

write_string:
    /* for (i = 0; i < len; i++) { */
    /* 	    printf("%d ", index[i]); */
    /* } */
    /* printf("\n"); */

    ret_index = 0;
    for (i = 0; i < rotate; i++) {
	    for (j = 0; j < len; j++) {
		    if (index[j] == i) {
			    /* printf("%c", s[j]); */
			    ret[ret_index++] = s[j];
		    }
        }
    }
    return ret;
}

// 5. Longest Palindromic Substring
char* longestPalindrome(char* s) {
	int start, end, index;
	int maxl;
	char *ret;
	int len = strlen(s);
	char *maxp;
	
	index = start = end = 0;
	maxl = 0;

	while (s[index]) {
		// get pivot
		start = end = index;
		while (start > 0 && s[start] == s[start - 1])
			start--;
		while (end < (len - 1) && s[end] == s[end + 1])
			end++;

		//printf("pivot=%d~%d\n", start, end);

		// get palindrome
		while (start > 0 && end < (len - 1) && s[start - 1] == s[end + 1]) {
			start--;
			end++;
		}

		// max?
		if (maxl < (end - start + 1)) {
			//printf("cur-max=%d~%d\n", start, end);
			maxp = &s[start];
			maxl = end - start + 1;
		}
		
		index++;
	}
	ret = calloc(maxl + 1, sizeof(char));
	memcpy(ret, maxp, maxl);
	return ret;
}

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
