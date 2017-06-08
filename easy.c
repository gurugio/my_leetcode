// 189. Rotate Array
void rotate(int* nums, int numsSize, int k) {
	int copy[numsSize];
	memcpy(copy, nums, numsSize * sizeof(int));
	if (k > numsSize) k %= numsSize;
	memcpy(&nums[0], &copy[numsSize-k], k * sizeof(int));
	memcpy(&nums[k], &copy[0], (numsSize - k) * sizeof(int));
}

// 7. Reverse Integer
int reverse(int x) {
    int negative;
    unsigned int abs_x;
    unsigned int ret;
    
    abs_x = x;
    negative = 0;
    if (x < 0) {
        abs_x = -x;
        negative = 1;
    }
        
    ret = 0;
    while (abs_x > 0) {
        ret = ret * 10 + abs_x % 10;
        abs_x /= 10;
        printf("%d %d\n", abs_x, ret);
        if (ret > (0x7fffffff/10) && (abs_x != 0)) {
            ret = 0;
            break;
        }
    }
    if (ret > 0x7fffffff) ret = 0;
    
    if (negative)
        ret = -ret;
    return (int)ret;    
}

// 155. Min Stack
typedef struct {
    int *nums;
    int nums_top;
    int size;
    int *mins;
    int mins_top;
} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {
    if (!maxSize) return NULL;
    MinStack *stack = calloc(1, sizeof(*stack));
    stack->nums = calloc(maxSize, sizeof(int));
    stack->mins = calloc(maxSize, sizeof(int));
    stack->size = maxSize;
    stack->nums_top = -1;
    stack->mins_top = -1;
    return stack;
}

void minStackPush(MinStack* obj, int x) {
    obj->nums[++obj->nums_top] = x;
    if (obj->mins_top == -1 || x <= minStackGetMin(obj))
        obj->mins[++obj->mins_top] = x;
}

void minStackPop(MinStack* obj) {
    int x = obj->nums[obj->nums_top--];
    if (x == minStackGetMin(obj))
        obj->mins_top--;
}

int minStackTop(MinStack* obj) {
    return obj->nums[obj->nums_top];
}

int minStackGetMin(MinStack* obj) {
    return obj->mins[obj->mins_top];
}

void minStackFree(MinStack* obj) {
    if (obj) {
        free(obj->mins);
        free(obj->nums);
        free(obj);
    }
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */

// 155. Min Stack
typedef struct {
    int *nums;
    int top;
    int size;
    int min;
} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {
    if (!maxSize) return NULL;
    MinStack *stack = calloc(1, sizeof(*stack));
    stack->nums = calloc(maxSize, sizeof(int));
    stack->top = -1;
    stack->size = maxSize;
    stack->min = -1;
    return stack;
}

void minStackPush(MinStack* obj, int x) {
    int min;
    obj->nums[++obj->top] = x;
    if (obj->min < 0) // first min
        obj->min = obj->top;
    else {
        if (obj->nums[obj->min] > obj->nums[obj->top])
            obj->min = obj->top;
    }
}

void minStackPop(MinStack* obj) {
    if (obj->top >= 0)
        obj->top--;
    if (obj->top < 0)
        obj->min = -1;
    else if (obj->top < obj->min) {
        int i;
        obj->min = 0;
        for (i = 1; i <= obj->top; i++) {
            if (obj->nums[obj->min] > obj->nums[i])
                obj->min = i;
        }
    }
}

int minStackTop(MinStack* obj) {
    return obj->nums[obj->top];
}

int minStackGetMin(MinStack* obj) {
    return obj->nums[obj->min];
}

void minStackFree(MinStack* obj) {
    if (obj) {
        free(obj->nums);
        free(obj);
    }
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */

// 303. Range Sum Query - Immutable
// refer: https://discuss.leetcode.com/topic/29194/java-simple-o-n-init-and-o-1-query-solution
typedef struct {
    int *nums;
    int size;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    int i;
    
    if (numsSize <= 0 || !nums)
        return NULL;
    NumArray *ar = calloc(1, sizeof(*ar));
    ar->nums = calloc(numsSize, sizeof(int));

    ar->nums[0] = nums[0];
    for (i = 1; i < numsSize; i++) {
        ar->nums[i] = ar->nums[i - 1] + nums[i];
    }

    ar->size = numsSize;
    return ar;
}

int numArraySumRange(NumArray* obj, int i, int j) {
    return obj->nums[j] - obj->nums[i - 1];
}

void numArrayFree(NumArray* obj) {
    if (obj) {
        free(obj->nums);
        free(obj);
    }
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * struct NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, i, j);
 * numArrayFree(obj);
 */

// 581. Shortest Unsorted Continuous Subarray
int findUnsortedSubarray(int* nums, int numsSize) {
	int start, end;

	for (start = 0; start < numsSize - 1; start++) {
		if (nums[start] <= nums[start + 1])
			continue;
		break;
	}

	for (end = numsSize - 1; end > start; end--) {
		if (nums[end] >= nums[end - 1])
			continue;
		break;
	}

	if (start < end) {
		int i;
		int max = 0x80000000, min = 0x7fffffff;

		for (i = start; i <= end; i++) {
			if (nums[i] > max)
				max = nums[i];
			if (nums[i] < min)
				min = nums[i];
		}
		for (i = end + 1; i < numsSize; i++) {
			if (nums[i] < max)
				end++;
		}
		for (i = start - 1; i >= 0; i--) {
			if (nums[i] > min)
				start--;
		}
		return end - start + 1;
	} else
		return 0;
}

// 400. Nth Digit
// This took 2 hours...
int findNthDigit(int n) {
    uint32_t digit = 2; // from 2 digit
    uint32_t count = 90;
    char string[36];
    
    digit = 1; // from 2-digit: 10 11 12
    count = 9;
    while (n > digit * count) {
        n -= digit * count;
        digit++;
        count *= 10;
    }
    
    //printf("n-%d digit-%d count-%d\n", n, digit, count);
    
    n--;
    //printf("num-%d\n", (int)pow(10, digit - 1) + n / digit);
    //printf("digit-%d\n", n % digit);
    sprintf(string, "%d\n", (int)pow(10, digit - 1) + n / digit);
    //printf("char-%c\n", string[n % digit]);
    
    return string[n % digit] - 0x30;
}

// 160. Intersection of Two Linked Lists
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *node_a = headA;
    struct ListNode *node_b = headB;
    
    if (headA == headB) return headA;

    while (node_a) {
        struct ListNode *n = node_a->next;
        node_a->next = (unsigned long)(node_a->next) | 0x1;
        if (node_a->next == 0x1)
            break;
        node_a = n;
    }

    while (node_b) {
        if ((unsigned long)(node_b->next) & 0x1)
            break;
        node_b = node_b->next;
    }
    node_a = headA;
    while (node_a) {
        node_a->next = (unsigned long)(node_a->next) & ~0x1;
        node_a = node_a->next;
    }
    return node_b;
}

// 14. Longest Common Prefix
char* longestCommonPrefix(char** strs, int strsSize) {
    int common_len;
    int i;
    char *ret;
    int last;

    if (strsSize == 0)
        common_len = 0;
    else {
        last = strsSize - 1;
        common_len = strlen(strs[last]);
    }
    
    for (i = 0; i < strsSize - 1; i++) {
        char *s, *t;
        
        s = strs[last];
        t = strs[i];

        if (*s == '\0' || *t == '\0') {
            common_len = 0;
            break;
        }
        while (!(*s - *t) && (s - strs[last]) < common_len)
            s++, t++;
        //printf("common-%d\n", s - strs[last]);
        if (common_len > (s - strs[last]))
            common_len = s - strs[last];
    }
end:
    //printf("finalcommon-%d\n", common_len);
    
    ret = calloc(common_len + 1, sizeof(char));
    strncpy(ret, strs[0], common_len);
    return ret;
}

// 67. Add Binary
#define MAX(a,b) ((a) > (b) ? (a) : (b))
char* addBinary(char* a, char* b) {
    int i, j;
    int carry;
    char *result;
    int index;
    int val_a, val_b;
    
    i = strlen(a) - 1; // last character
    j = strlen(b) - 1; // last character 
    index = 0;
    result = calloc(MAX(i, j) + 3 /* one more digit + null */, sizeof(char));
    
    carry = 0;
    while (i >= 0 || j >= 0) {
        if (i >= 0)
            val_a = a[i];
        else
            val_a = '0';

        if (j >= 0)
            val_b = b[j];
        else
            val_b = '0';
        //printf("%x + %x + %d\n", val_a, val_b, carry);
        
        if (val_a == '1' && val_b == '1') {
            result[index] = '0' + carry;
            carry = 1;
        } else if ((val_a == '1' && val_b == '0') ||
                    (val_a == '0' && val_b == '1')) {
            if (carry == 0) {
                result[index] = '1';
                carry = 0;
            } else {
                result[index] = '0';
                carry = 1;
            }
        } else if (val_a == '0' && val_b == '0') {
            result[index] = '0' + carry;
            carry = 0;
        }
        //printf("s=%x c=%d\n", result[index], carry);
        i--, j--, index++;
    }

    if (carry == 1)
        result[index++] = '1';
    for (i = 0; i < index/2; i++) {
        char _t = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = _t;
    }
    result[index] = '\0';
    return result;
}

// 58. Length of Last Word
int lengthOfLastWord(char* s) {
    int len = strlen(s);
    char *p = s + len - 1;
    while (*p && *p == ' ') {
        p--;
        len--;
    }
    //printf("%c\n", *p);
    while (*p && *p != ' ')
        p--;
    return len - (p - s) - 1;
}

// 203. Remove Linked List Elements
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode *prev = NULL;
    struct ListNode *cur = head;
    
    while (head && head->val == val) {
        head = head->next; // remove the first node
    }
    
    cur = head;
    while (cur) {
        //printf("cur-%d\n", cur->val);
        if (cur->val == val) {
            struct ListNode *next = cur->next;
            if (next) {
                //printf("change cur-%d\n", next->val);
                cur->val = next->val;
                cur->next = next->next;
                // new value can be also removing value
                // so check cur again
                continue;
            } else {
                // remove the last node
                prev->next = NULL;
            }
        }
        prev = cur;
        cur = cur->next;
    }
    return head;
}

// 88. Merge Sorted Array
void merge(int* nums1, int m, int* nums2, int n) {
    int i, j, target;
    int *tmp = calloc(m, sizeof(int));
    memcpy(tmp, nums1, m * sizeof(int));
    
    i = j = 0;
    target = 0;
    
    while (i < m && j < n) {
        if (tmp[i] < nums2[j]) {
            nums1[target++] = tmp[i++];
        } else {
            nums1[target++] = nums2[j++];
        }
    }
    while (i < m) {
        nums1[target++] = tmp[i++];
    }
    while (j < n) {
        nums1[target++] = nums2[j++];
    }
    free(tmp);
}

// 225. Implement Stack using Queues
// queue_peek() does not return the last value in queue.
// queue_peek() must returns the value that queue_pop() will return.
struct queue {
	int *buf;
	int size;
	int rear, tail;
};

struct queue *queue_create(int max)
{
	struct queue *q = calloc(1, sizeof(struct queue));
	q->rear = q->tail = 0;
	q->size = max;
	q->buf = calloc(max, sizeof(int));
	return q;
}

void queue_free(struct queue *q)
{
	free(q->buf);
	free(q);
}

void queue_print(struct queue *q)
{
	int i;
	printf("<%d %d>", q->tail, q->rear);
	for (i = 0; i < q->size; i++)
		printf("%d ", q->buf[i]);
	printf("\n");
}

void queue_push(struct queue *q, int val)
{
	q->buf[q->rear] = val;
	q->rear = (q->rear + 1) % q->size;
}

int queue_peek(struct queue *q)
{
	return q->buf[q->tail];
}

int queue_pop(struct queue *q)
{
	int ret = q->buf[q->tail];
	q->tail = (q->tail + 1) % q->size;
	return ret;
}

int queue_size(struct queue *q)
{
	return q->rear - q->tail;
}

bool queue_empty(struct queue *q)
{
	return q->tail == q->rear;
}

typedef struct {
	struct queue *q;
	int *buf;
	int size;
} MyStack;

MyStack* myStackCreate(int maxSize) {
	MyStack *stack = calloc(1, sizeof(MyStack));
	stack->q = queue_create(maxSize);
	stack->buf = calloc(maxSize, sizeof(int));
	stack->size = maxSize;
	return stack;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	queue_push(obj->q, x);
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	int index = 0;
	int i;
	int ret;

	while (!queue_empty(obj->q))
		obj->buf[index++] = queue_pop(obj->q);
	ret = obj->buf[--index];
	for (i = 0; i < index; i++)
		queue_push(obj->q, obj->buf[i]);
	return ret;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
    int index = 0;
	int i;
	int ret;

	while (!queue_empty(obj->q))
		obj->buf[index++] = queue_pop(obj->q);
	ret = obj->buf[index - 1];
	for (i = 0; i < index; i++)
		queue_push(obj->q, obj->buf[i]);
	return ret;
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
	return queue_empty(obj->q);
}

void myStackFree(MyStack* obj) {
	queue_free(obj->q);
	free(obj);
}

// 234. Palindrome Linked List
struct ListNode *reverse(struct ListNode *head) {
	struct ListNode *prev = NULL;
	struct ListNode *next = NULL;
	
	while (head) {
	    //printf("head-%p %d\n", head, head->val);
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}
	//printf("prev-%p %d\n", prev, prev->val);
	return prev;
}

bool isPalindrome(struct ListNode* head) {
	struct ListNode *slow, *fast;
	struct ListNode *last, *prev;;

	if (!head) return true;
    
	slow = fast = head;
	while (fast->next && fast->next->next) {
		//printf("slow-%p %d\n", slow, slow->val);
		fast = fast->next->next;
		slow = slow->next;
	}
	if (fast->next) {
		//printf("slow-%p %d\n", slow, slow->val);
		slow = slow->next;
	}

	//printf("middle-%p %d\n", slow, slow->val);
	last = reverse(slow);

	while (last) {
		//printf("cmp: %d %d\n", head->val, last->val);
		if (head->val != last->val)
			return false;
		last = last->next;
		head = head->next;
	}
	return true;
}

// 1. Two Sum
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct hashnode {
	int key;
	int val;
};

struct hashmap {
	size_t size;
	struct hashnode **storage;
};

struct hashmap *hash_create(int size)
{
	struct hashmap *ret = calloc(1, sizeof(*ret));
	ret->size = size;
	ret->storage = calloc(size, sizeof(struct hashnode *));
	return ret;
}

void hash_destroy(struct hashmap *map)
{
	free(map->storage);
	free(map);
}

void hash_set(struct hashmap *map, int key, int val)
{
	int index = abs(key) % map->size;
	struct hashnode *node;
	
	while (map->storage[index]) {
		index++;
	}
	node = calloc(1, sizeof(struct hashnode));
	node->key = key;
	node->val = val;
	map->storage[index] = node;
	//printf("hash-set[%d]: %d->%d\n", index, key, val);
}

struct hashnode *hash_get(struct hashmap *map, int key)
{
	int index = abs(key) % map->size;
	while (map->storage[index] && map->storage[index]->key != key)
	    index++;
	//printf("hash-get[%d]: %d->%p\n", index, key, map->storage[index]);
	return map->storage[index];
}

int* twoSum(int* nums, int numsSize, int target) {
    int i,j;
    int *ret;
    int remain;
    struct hashmap *map = hash_create(numsSize * 2);
    struct hashnode *node;
    
    for (i = 0; i < numsSize; i++) {
        remain = target - nums[i];
        node = hash_get(map, nums[i]);
        if (node) {
            ret = calloc(2, sizeof(int));
            ret[0] = node->val, ret[1] = i;
            hash_destroy(map);
            return ret;
        }
        hash_set(map, remain, i);
    }
    hash_destroy(map);
    return NULL;
}

// 290. Word Pattern
bool wordPattern(char* pattern, char* str) {
    char *pattern_table[26] = {NULL,};
    int s, t;
    char *del = " ";
    int ch;
    char *ptr;
    
    s = t = 0;
    
    if (pattern[0] == '\0') return false;
    
    // the first tokenizing needs str
    ch = pattern[s++] - 'a';
    pattern_table[ch] = strtok(str, del);
    //printf("add map:%c - %s\n", ch + 'a', pattern_table[ch]);
    while (pattern[s]) {
        int i;
        ch = pattern[s] - 'a';
        ptr = strtok(NULL, del);
        if (!ptr) break;
        
        if (pattern_table[ch] == NULL) {
            for (i = 0; i < 26; i++) {
                if (pattern_table[i] && strcmp(pattern_table[i], ptr) == 0) {
                    //printf("dup map:%c %s\n", i+'a', pattern_table[i]);
                    goto duplicated;
                }
            }
            pattern_table[ch] = ptr;
                //printf("add map:%c - %s\n", ch + 'a', pattern_table[ch]);
        } else {
            if (strcmp(pattern_table[ch], ptr)) {
                    //printf("mismatch map:%c - %s\n", ch + 'a', ptr);
                break;
            }
                //printf("match map:%c - %s\n", ch + 'a', pattern_table[ch]);
        }
        s++;
    }
duplicated:
    return pattern[s] == '\0' && strtok(NULL, del) == NULL;
}

// 507. Perfect Number
bool checkPerfectNumber(int num) {
    int last = sqrt(num);
    int i;
    int sum = 1;
    
    if (num == 1) return false;
    
    for (i = 2; i <= last; i++) {
        if (0 == (num % i)) {
            sum += (i + (num / i));
            //printf("%d %d\n", i, num/i);
        }
    }
    return sum == num;
}

// 111. Minimum Depth of Binary Tree
void traverse(struct TreeNode *root, int cur_depth, int *min_depth) {
    if (root->left == NULL && root->right == NULL && cur_depth < *min_depth) {
        *min_depth = cur_depth;
        return;
    }
    if (root->left) traverse(root->left, cur_depth+1, min_depth);
    if (root->right) traverse(root->right, cur_depth+1, min_depth);
}

int minDepth(struct TreeNode* root) {
    int min = 0xffffff;
    if (!root) return 0;
    traverse(root, 1, &min);
    return min;
}

// 20. Valid Parentheses
bool isValid(char* s) {
    int i;
    char *stack;
    int index = 0;
    
    stack = calloc(strlen(s), sizeof(char));
    for (i = 0; s[i] != '\0'; i++) {
        switch (s[i]) {
            case '(':
            case '[':
            case '{':
                stack[index++] = s[i];
                break;
            case ')':
                if (stack[--index] != '(')
                    goto out;
                break;
            case ']':
                if (stack[--index] != '[')
                    goto out;
                break;
            case '}':
                if (stack[--index] != '{')
                    goto out;
                break;
        }
    }
    free(stack);
out:
    return s[i] == '\0' && index == 0;
}

// 205. Isomorphic Strings
bool isIsomorphic(char* s, char* t) {
    int len = strlen(s);
    int i;
    char s_mapping[256] = {0,};
    char t_mapping[256] = {0,};

    for (i = 0; i < len; i++) {
        if (s_mapping[s[i]] == 0 && t_mapping[t[i]] == 0) {
            s_mapping[s[i]] = t[i];
            t_mapping[t[i]] = s[i];
            //printf("new mapping %c - %c\n", s[i], t[i]);
        } else {
            if (s_mapping[s[i]] == t[i] && t_mapping[t[i]] == s[i]) {
                //printf("match mapping %c - %c\n", s[i], t[i]);
                continue;
            } else {
                //printf("fail %c - %c\n", s[i], t[i]);
                break;
            }
        }
    }
    return i == len;
}

// 438. Find All Anagrams in a String
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
void make_counter(char *s, int len, int *counter) {
    int i = 0;
    for (i = 0; i < len; i++)
        counter[s[i] - 'a']++;
}

bool cmp_counter(int *c1, int *c2) {
    int i;
    for (i = 0; i < 'z' - 'a' + 1; i++) {
        if (c1[i] != c2[i])
            break;
    }
    return i == 'z'-'a'+1;
}

int* findAnagrams(char* s, char* p, int* returnSize) {
    int counter['z'-'a'+1] = {0,};
    int tmp['z'-'a'+1] = {0,};
    int *ret;
    int i, index;
    int plen;
    int slen;
    
    ret = calloc(40960, sizeof(int));
    index = 0;
    slen = strlen(s);
    plen = strlen(p);

    // start at 0
    make_counter(p, plen, counter);
    make_counter(s, plen, tmp);
    if (cmp_counter(counter, tmp)) ret[index++] = 0;
    // start at 1
    for (i = 1; i <= slen - plen; i++) {
        tmp[s[i-1] - 'a']--;
        tmp[s[i+plen-1] - 'a']++;
        if (cmp_counter(counter, tmp))
            ret[index++] = i;
    }
    *returnSize = index;
    return ret;
}

// 38. Count and Say
char* countAndSay(int n) {
    int cur;
    int count = 0;
    int s, t;
    int i;
    char *buf1, *buf2;
    char *source, *target;
    
    if (n == 0) return NULL;
    
    buf1 = calloc(40960, sizeof(char));
    buf2 = calloc(40960, sizeof(char));
    source = buf1;
    target = buf2;
    
    source[0] = '1'; // if n==1
    
    for (i = 1; i < n; i++) {
        count = cur = 0;
        s = t = 0;
        while (source[s]) {
            if (source[cur] == source[s])
                count++;
            else {
                target[t++] = count + '0';
                target[t++] = source[cur];
                count = 1;
                cur = s;
            }
            s++;
        }
        // write the last count
        target[t++] = count + '0';
        target[t++] = source[cur];
        {
            char *_t = source;
            source = target;
            target = _t;
        }
    }
    free(target);
    return source;
}

// 172. Factorial Trailing Zeroes
// time-over version
int trailingZeroes(int n) {
    int zeros = 0;
    int i;
    
    for (i = 0; i <= n; i += 5) {
        int t = i;
        if (i == 0) continue;
        while ((t % 5) == 0) {
            zeros++;
            t /= 5;
        }
    }
    return zeros;
}

// 9. Palindrome Number
#if 0
// my poor version
int digits(int x)
{
    int d = 0;
    int i;
    for (i = x; i != 0; i /= 10)
        d++;
    return d;
}

int get_digit(int x, int d)
{
    int i;
    for (i = 0; i < d; i++)
        x /= 10;
    return x % 10;
}

bool isPalindrome(int x) {
    int di = digits(x);
    int i;
    int match = 0;
    if (x < 0) return false;
    
    //printf("digits=%d\n", di);
    for (i = 0; i < di/2; i++) {
        int h, l;
        l = get_digit(x, i);
        h = get_digit(x, di - 1 - i);
        //printf("%d == %d", h, l);
        if (l != h) return false;
    }
    return true;
}
#endif
// solution version
bool isPalindrome(int x) {
    int rev;
    
    if ((x < 0) || (x != 0 && (x % 10) == 0))
        return false;
    while (x > rev) {
        rev = rev * 10 + x%10;
        x /= 10;
    }
    return x == rev || x == (rev/10);
}

// 26. Remove Duplicates from Sorted Array
int removeDuplicates(int* nums, int numsSize) {
    int cur = 0;
    int i;
    if (numsSize == 0) return 0;
    for (i = 1; i < numsSize; i++) {
        if (nums[cur] != nums[i]) {
            nums[++cur] = nums[i];
        }
    }
    return cur+1;
}

// 141. Linked List Cycle
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head) {
    struct ListNode *two_step, *one_step;
    
    one_step = two_step = head;
    while (1) {
        if (!one_step)
            return false;
        one_step = one_step->next;
        if (!two_step)
            return false;
        two_step = two_step->next;
        if (!two_step)
            return false;
        two_step = two_step->next;
        if (one_step == two_step)
            return true;
    }
}

// 232. Implement Queue using Stacks
struct stack {
	int count;
	int *buf;
};

struct stack *stack_create(int max)
{
	struct stack *s = calloc(1, sizeof(struct stack));
	s->count = 0;
	s->buf = calloc(max, sizeof(int));
	return s;
}

void stack_free(struct stack *s)
{
	free(s->buf);
	free(s);
}

void stack_push(struct stack *s, int x)
{
	s->buf[s->count++] = x;
}

int stack_pop(struct stack *s)
{
	return s->buf[--s->count];
}

int stack_peek(struct stack *s)
{
	return s->buf[s->count - 1];
}

void stack_show(struct stack *s)
{
	int i;
	for (i = s->count - 1; i >= 0; i--)
		printf("%d-", s->buf[i]);
	printf("\b \n");
}

int stack_empty(struct stack *s)
{
	return s->count == 0;
}

int stack_size(struct stack *s)
{
	return s->count;
}

void stack_reverse(struct stack *s)
{
	int center = s->count / 2;
	int i;
	for (i = 0; i < center; i++) {
		int t = s->buf[i];
		s->buf[i] = s->buf[s->count - i - 1];
		s->buf[s->count - i - 1] = t;
	}
}

typedef struct {
       	struct stack *stack;
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate(int maxSize) {
	MyQueue *m;
	m = calloc(1, sizeof(*m));
	m->stack = stack_create(maxSize);
	return m;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	stack_push(obj->stack, x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	int x;
	stack_reverse(obj->stack);
	x = stack_pop(obj->stack);
	stack_reverse(obj->stack);
	return x;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	int x;
	stack_reverse(obj->stack);
	x = stack_peek(obj->stack);
	stack_reverse(obj->stack);
	return x;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	return stack_empty(obj->stack);
}

void myQueueFree(MyQueue* obj) {
	stack_free(obj->stack);
	free(obj);
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * struct MyQueue* obj = myQueueCreate(maxSize);
 * myQueuePush(obj, x);
 * int param_2 = myQueuePop(obj);
 * int param_3 = myQueuePeek(obj);
 * bool param_4 = myQueueEmpty(obj);
 * myQueueFree(obj);
 */

// 119. Pascal's Triangle II
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize) {
    int i, j;
    int *buf = calloc(rowIndex + 1, sizeof(int));

    buf[0] = buf[1] = 1;
    for (i = 2; i <= rowIndex; i++) {
        // make each row
        buf[i] = 1;
        for (j = i - 1; j > 0; j--) {
            buf[j] = buf[j] + buf[j - 1];
        }
        buf[0] = 1;
        
        // print
        /*for (j = 0; j <= i; j++) {
            printf("%d ", buf[j]);
        }
        printf("\n");*/
    }
    *returnSize = rowIndex + 1;
    return buf;
}

// 441. Arranging Coins
int arrangeCoins(int n) {
    double x = n;
    x = 1 + 8 * x;
    int i = (sqrt(x) - 1) / 2;
    //printf("x=%f\n", x);
    //printf("i=%d\n", i);
    return i;
}

// 257. Binary Tree Paths
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define SIZE 512
struct path {
	int tmp[SIZE];
	char *results[SIZE];
	int count;
};

void __getpath(struct TreeNode *root, struct path *path, int level)
{
	if (!root) return;

	path->tmp[level] = root->val;
	//printf("add:%d\n", root->val);
	
	if (root->left)
		__getpath(root->left, path, level+1);
		
	if (root->right)
		__getpath(root->right, path, level+1);
	
	if (!root->left && !root->right) {
		int len = (level + 2) * 3 /* each digit is 3-char include \0 */ + 2 * level/* -> */;
		char *p = calloc(len, sizeof(char));
		int i;
		int r = 0;
		for (i = 0; i < level; i++) {
			r += sprintf(&p[r], "%d->", path->tmp[i]);
			//printf("%d->", path->tmp[i]);
		}
		sprintf(&p[r], "%d", path->tmp[i]);
		//printf("%d\n", path->tmp[i]);
		path->results[path->count] = p;
		path->count++;
	}
}

char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    struct path p;
	char **ret;
	int i;
	
	memset(p.tmp, 0, SIZE);
	p.count = 0;

	__getpath(root, &p, 0);
	*returnSize = p.count;
	ret = calloc(p.count, sizeof(char *));
	for (i = 0; i < p.count; i++)
		ret[i] = p.results[i];
	return ret;
}

// 110. Balanced Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void get_height(struct TreeNode *root, int cur, int *h)
{
    if (!root) return;
    if (cur > *h)
        *h = cur;
    get_height(root->left, cur+1, h);
    get_height(root->right, cur+1, h);
}

#if 0
// SLOW version of get_height
// This version goes to bottom and comes to top to get height.
// But above version only goes to bottom to get height.
#define MAX(a,b) ((a) > (b) ? (a) : (b))
int get_height(struct TreeNode *root)
{
    if (!root) return 0;
    return MAX(get_height(root->left), get_height(root->right)) + 1;
}
#endif

bool isBalanced(struct TreeNode* root) {
    int hl = 0, hr = 0;

    if (!root) return true;

    if (root->left) 
        get_height(root->left, 1, &hl);
    if (root->right)
        get_height(root->right, 1, &hr);
        
    if (hl - hr < -1 || hl - hr > 1)
        return false;
    
    return isBalanced(root->left) && isBalanced(root->right);
}

// 434. Number of Segments in a String
int countSegments(char* s) {
    int count = 0;
    int len = strlen(s);
    int i;
#if 0   
    for (; i < len; i++) {
        if (s[i] != 0x20)
            count++;

        for (; i < len; i++) {
            if (s[i] == 0x20)
                break;
        }
    }
#endif
    s = strtok(s, " ");
    while(s != NULL) {
        count++;
        s = strtok(NULL, " ");
    }
    return count;
}

// 118. Pascal's Triangle
/**
 * Return an array of arrays.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int** columnSizes) {
    int **rows;
    int *row_sizes;
	int i, j;

	rows = calloc(numRows, sizeof(int *));
	row_sizes = calloc(numRows, sizeof(int));

	rows[0] = calloc(1, sizeof(int));
	row_sizes[0] = 1;
	rows[0][0] = 1;
	
	for (i = 1; i < numRows; i++) {
		rows[i] = calloc(i + 1, sizeof(int));
		row_sizes[i] = i+1;
		rows[i][0] = rows[i][i] = 1;

		for (j = 1; j < i; j++) {
			rows[i][j] = rows[i-1][j-1] + rows[i-1][j];
		}

		//for (j = 0; j < i+1; j++)
		//	printf("%d ", rows[i][j]);
		//printf("\n");
	}
	*columnSizes = row_sizes;
	return rows;
}

// 66. Plus One
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int c;
    int i;
    int *ret;
    
    c = 0;
    digits[digitsSize - 1]++;
    if (digits[digitsSize - 1] >= 10) {
        c = 1;
        digits[digitsSize - 1] = 0;
    }
    
    for (i = digitsSize - 2; i >= 0; i--) {
        digits[i] += c;
        if (digits[i] >= 10) {
            c = 1;
            digits[i] = 0;
        } else
            c = 0;
    }
    
    if (c) {
        ret = calloc(digitsSize + 1, sizeof(int));
        memcpy(&ret[1], digits, sizeof(int) * digitsSize);
        ret[0] = 1;
        *returnSize = digitsSize + 1;
    } else {
        ret = calloc(digitsSize, sizeof(int));
        memcpy(ret, digits, sizeof(int) * digitsSize);
        *returnSize = digitsSize;
    }
    return ret;
}

// 101. Symmetric Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int get_count(struct TreeNode *root)
{
    if (root == NULL)
        return 1;
    return 1 + get_count(root->left) + get_count(root->right);
}

void travel_left(struct TreeNode *root, int *array, int *index)
{
    if (!root) {
        //printf("left[%d]->%d\n", *index, 0);
        array[*index] = 0;
        (*index)++;
        return;
    }
    array[*index] = root->val;
    //printf("left[%d]->%d\n", *index, root->val);
    (*index)++;
    travel_left(root->left, array, index);
    travel_right(root->right, array, index);
}

void travel_right(struct TreeNode *root, int *array, int *index)
{
    if (!root) {
        //printf("right[%d]->%d\n", *index, 0);
        array[*index] = 0;
        (*index)++;
        return;
    }
    array[*index] = root->val;
    //printf("right[%d]->%d\n", *index, root->val);
    (*index)++;
    travel_right(root->right, array, index);
    travel_left(root->left, array, index);
}

bool isSymmetric(struct TreeNode* root) {
    int count = get_count(root);
    int *buf[2];
    int i;
    int left_index, right_index;
    
    if (count == 1) return true;
    
    buf[0] = calloc(count, sizeof(int));
    buf[1] = calloc(count, sizeof(int));
    
    left_index = 0;
    right_index = 0;
    travel_left(root->left, buf[0], &left_index);
    travel_right(root->right, buf[1], &right_index);
    
    if (left_index != right_index)
        return false;
        
    for (i = 0; i < left_index; i++) {
        if (buf[0][i] != buf[1][i])
            break;
    }
    
    free(buf[0]);
    free(buf[1]);
    
    if (i == left_index)
        return true;
    return false;
}

// 27. Remove Element
int removeElement(int* nums, int numsSize, int val) {
    int last;
    int first;
    
    last = numsSize - 1;
    first = 0;
    
    while (first <= last) {
        while (nums[last] == val && last > first)
            last--;
        
        while (nums[first] != val && first <= last)
            first++;
        
        if (first >= last)
            break;

        {
            int t;
            t = nums[last];
            nums[last] = nums[first];
            nums[first] = t;
        }
        
    }
    return first;
}

// 367. Valid Perfect Square
#define MAX (64*1024)
bool isPerfectSquare(int num) {
    int i;
    int a, b;
    int last_digit = num % 10;
    
    switch (last_digit) {
        case 0:
            for (a = 10; a < MAX; a += 10) {
                if (num == a*a)
                    return true;
            }
            return false;
            break;
        case 1:
            a = 1, b = 9;
            break;
        case 4:
            a = 2, b = 8;
            break;
        case 9:
            a = 3, b = 7;
            break;
        case 6:
            a = 4, b = 6;
            break;
        case 5:
            for (a = 5; a < MAX; a += 5)
                if (num == a*a)
                    return true;
            return false;
            break;
        default:
            return false;
    }
    for (; a < MAX || b < MAX; a += 10, b += 10) {
        if (num == a*a || num == b*b)
            return true;
    }
    return false;
}

// 345. Reverse Vowels of a String
int is_vowel(char c)
{
    int vowels[] = {1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0};
    c &= ~0x20;
    if (c >= 0x41 && c <= 0x5a)
        return vowels[c - 0x41];
    return 0;
}   
char* reverseVowels(char* s) {
    int i, j;
    int len = strlen(s);
    
    i = 0;
    j = len - 1;
    while (1) {
        char t;
        for (; i < j; i++) {
            if (is_vowel(s[i]))
                break;
        }
        for (; j > i; j--) {
            if (is_vowel(s[j]))
                break;
        }       

        if (i >= j)
            break;

        t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++,j--;
    }
    return s;
}

// 342. Power of Four
bool isPowerOfFour(int num) {
    int i;
    
    for (i = 0; i < 32; i += 2) {
        if (num == (1<<i))
            return true;
    }
    return false;
}

// 198. House Robber - FAIL version
// depth first travle is too slow.
struct head {
	struct node *next;
	int val;
	int visit;
};

struct node {
	struct node *next;
	int index;
};


struct head *build_heap(int *nums, int numsSize)
{
	struct head *heads;
	int i,j;

	heads = calloc(numsSize, sizeof(struct head));
	for (i = 0; i < numsSize; i++) {
		struct head *h;
		struct node *n;
		
		h = &heads[i];
		h->val = nums[i];
		h->visit = 0;
		h->next = NULL;
		
		//printf("head[%d]->", i);
		// t -> [0 ~ (t-2)] -> [(t+2) ~ n]
		for (j = 0; j < i - 1; j++) {
			// add node to head
			//printf("[%d] ", j);
			n = malloc(sizeof(struct node));
			n->index = j;
			n->next = h->next;
			h->next = n;
		}
		for (j = i + 2; j < numsSize; j++) {
			//printf("[%d] ", j);
			n = malloc(sizeof(struct node));
			n->index = j;
			n->next = h->next;
			h->next = n;
		}
		//printf("\n");
	}
	return heads;
}

bool check_side(struct head *heads, int size, int index)
{
	if (heads[index].visit == 1)
		return false;
	if (index == 0 && heads[1].visit == 0)
		return true;
	if (index == size - 1 && heads[index - 1].visit == 0)
		return true;
	if (heads[index - 1].visit == 0 && heads[index + 1].visit == 0)
		return true;
	return false;
}

void travel_heap_depth(struct head *heads, int size, struct head *cur, int sum, int *max)
{
	struct node *n;
	
	cur->visit = 1;
	sum += cur->val;
	//printf("visit=%d sum=%d\n", cur->val, sum);

	if (*max < sum) {
		//printf("set-max=%d\n", sum);
		*max = sum;
	}
	
	n = cur->next;
	while (n != NULL) {
		//printf("try=%d\n", n->index);
		//if (heads[n->index].visit == 0) {
		if (check_side(heads, size, n->index)) 
			travel_heap_depth(heads, size, &heads[n->index],
					  sum, max);
		n = n->next;
	}

	cur->visit = 0;
}

int rob(int* nums, int numsSize)
{
	struct head *heads;
	int max = 0;
	int i, j;
	
	heads = build_heap(nums, numsSize);

	for (j = 0; j < numsSize; j++) {
		for (i = 0; i < numsSize; i++)
			heads[i].visit = 0;
		travel_heap_depth(heads, numsSize, &heads[j], 0, &max);
		//printf("=== max=%d\n", max);
	}

	return max;
}
	
int main(void)
{
	int arr[] = {183,219,57,193,94,233,202,154,65,240,97,234,100,249,186,66,90,238,168,128,177,235,50,81,185,165,217,207,88,80,112,78,135,62,228,247,211};
	//int arr[] = {1,1,1,1};
	//int arr[] = {1,1,3,6,7,10,7,1,8,5,9,1,4,4,3};
	printf("max=%d\n", rob(arr, sizeof(arr)/sizeof(arr[0])));

	return 0;
}


// 21. Merge Two Sorted Lists
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *head;
    struct ListNode *ret;
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    if (l1->val < l2->val) {
        head = l1;
        l1 = l1->next;
    } else {
        head = l2;
        l2 = l2->next;
    }
    ret = head;
    //printf("head=%d\n", head->val);
    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            head->next = l1;
            l1 = l1->next;
            head = head->next;
        } else {
            head->next = l2;
            l2 = l2->next;
            head = head->next;
        }
        //printf("head=%d\n", head->val);
    }
    
    if (l1 != NULL)
        head->next = l1;
    
    if (l2 != NULL)
        head->next = l2;
    
    return ret;
}

// 235. Lowest Common Ancestor of a Binary Search Tree
// 30% version, why so slow?
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q)
{
    struct TreeNode *l, *r;
    if (root == NULL) return NULL;
    if (root == q || root == p)
        return root;
    l = lowestCommonAncestor(root->left, p, q);
    r = lowestCommonAncestor(root->right, p, q);
    if (r && l)
        return root;
    else if (r)
        return r;
    else if (l)
        return l;
    return NULL;
}

// 107. Binary Tree Level Order Traversal II
/* O(n) version
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct queue {
	struct TreeNode *buf[100000];
	int rear;
	int tail;
};

int qcount(struct queue *q)
{
	return q->rear - q->tail;
}

void qpush(struct queue *q, struct TreeNode *p)
{
	assert(q->rear < 100000);
	q->buf[q->rear++] = p;
}

void qprint(struct queue *q)
{
	int i;

	for (i = q->tail; i < q->rear; i++)
		printf("%d ", q->buf[i]->val);
	printf("\n");
}

struct TreeNode *qpop(struct queue *q)
{
	if (q->tail == q->rear)
		return NULL;
	return q->buf[q->tail++];
}

void get_max_level(struct TreeNode *root, int cur, int *max)
{
    if (!root) return;
    if (cur > *max)
        *max = cur;
    get_max_level(root->left, cur + 1, max);
    get_max_level(root->right, cur + 1, max);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrderBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
	int cur_level = 0;
	int max_level = 0;
	int cur_count;
	struct queue *q;
	int *level_count;
	int **level_store;
	int i;
	
	get_max_level(root, 0, &max_level);
	level_count = calloc(max_level + 1, sizeof(int));
	level_store = calloc(max_level + 1, sizeof(int *));
	
	q = malloc(sizeof(*q));
	q->rear = q->tail = 0;

	if (root)
		qpush(q, root);

	while (1) {
		struct TreeNode *t;
		
		cur_count = qcount(q);
		if (cur_count == 0)
			break;
		
		level_count[cur_level] = cur_count;
		level_store[cur_level] = calloc(cur_count, sizeof(int));
		
		//printf("level-%d count-%d\n", cur_level, cur_count);
		//qprint(q);
		
		for (i = 0; i < cur_count; i++) {
			t = qpop(q);
			level_store[cur_level][i] = t->val;
			
			if (t->left)
				qpush(q, t->left);
			if (t->right)
				qpush(q, t->right);
		}
		
		cur_level++;
	}
	free(q);
	
	for (i = 0; i < cur_level/2; i++) {
	    int *t;
	    int d;
	    t = level_store[i];
	    level_store[i] = level_store[cur_level - i - 1];
	    level_store[cur_level - i - 1] = t;
	    
	    d = level_count[i];
	    level_count[i] = level_count[cur_level - i - 1];
	    level_count[cur_level - i - 1] = d;
	}
	
	*columnSizes = level_count;
	*returnSize = cur_level;
	return level_store;
}

// 107. Binary Tree Level Order Traversal II
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
 * I could make this one-path solution with more temporary buffers,
 * so I made this two-path.
 * BUT THIS IS O(n^2)
 */
void get_max_level(struct TreeNode *root, int cur, int *max, int *level_count)
{
    if (!root) return;
    if (cur > *max)
        *max = cur;
    level_count[cur]++;
    get_max_level(root->left, cur + 1, max, level_count);
    get_max_level(root->right, cur + 1, max, level_count);
}

void get_val_level(struct TreeNode *root, int cur, int target, int *store, int *count)
{
    if (!root) return;

    if (cur == target) {
        //printf("level=%d count=%d val=%d\n", cur, *count, root->val);
        store[*count] = root->val;
        (*count)++;
    }
    get_val_level(root->left, cur + 1, target, store, count);
    get_val_level(root->right, cur + 1, target, store, count);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrderBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
    int level = 0;
    int *level_index;
    int **level_store;
    int i;
    int *tmp_level_count = calloc(1000, sizeof(int));
    
    get_max_level(root, 0, &level, tmp_level_count);
    printf("level=%d\n", level);

    /*
     * max leve = 2 -> array size = 3
     */
    level_index = calloc(level + 1, sizeof(int));
    level_store = calloc(level + 1, sizeof(int *));
    
    for (i = 0; i <= level; i++) {
        /* store[0] stores values of the max level */
        int target = level - i;

        if (tmp_level_count[target] != 0)
            level_store[i] = calloc(tmp_level_count[target], sizeof(int));
        //printf("level-%d count=%d store-%p\n", target, tmp_level_count[target], level_store[i]);

        get_val_level(root, 0, target, level_store[i], &level_index[i]);
    }
    
    if (tmp_level_count[0] != 0)
        *returnSize = level + 1;
    else
        *returnSize = 0;
    *columnSizes = level_index;
    return level_store;
}

// 263. Ugly Number
bool isUgly(int num) {
    if (num == 0) return false;
    while ((num % 5) == 0)
        num /= 5;
    while ((num % 3) == 0)
        num /= 3;
    while ((num % 2) == 0)
        num /= 2;
    return num == 1;
}

// 459. Repeated Substring Pattern
int pattern_size(char *str, int old_size)
{
	int size;
	int len = strlen(str);

	for (size = old_size + 1; size <= len; size++) {
        if ((len % size) != 0) continue;
		//printf("size:%s %s %d\n", &str[0], &str[size], size);
		if (strncmp(&str[0], &str[size], size) == 0)
			return size;
	}
	return -1;
}

int pattern_check(char *str, int size)
{
	int index;
	int len = strlen(str);

	for (index = size*2; index <= len; index += size) {
		//printf("cmp:%s %s %d\n", &str[0], &str[index], size);
		if (strncmp(&str[0], &str[index], size) != 0)
			break;
	}
	if (index == len)
		return 1;
	return 0;
}

bool repeatedSubstringPattern(char* s) {
    int size = 0;
	int ret;
    int len = strlen(s);
	
	do {
		size = pattern_size(s, size);
		if (size < 0) break;
		ret = pattern_check(s, size);
		if (ret > 0) break;

	} while (size <= len/2);
	return ret;
}

// 437. Path Sum III
int checkPathSum(struct TreeNode* root, int sum) {
    int count = 0;
    if (!root)
        return 0;
    if (root->val == sum)
        count++;
    return count + checkPathSum(root->left, sum - root->val) 
            + checkPathSum(root->right, sum - root->val);
}

int pathSum(struct TreeNode *root, int sum) {
    if (!root) return 0;
    return checkPathSum(root, sum) +
            pathSum(root->left, sum) +
            pathSum(root->right, sum);
}

// 113. Path Sum II
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct path {
    int index;
    int nums[1024];
    int count;
    int cur_pathes;
    int *pathes_length;
    int **pathes;
};

void __pathSum(struct TreeNode *root, int sum, struct path *path)
{
    int index;
    
    if (!root)
        return;

    path->nums[path->index] = root->val;
    path->index++;
 
    if (!root->left && !root->right && root->val == sum) {
        int i;
        /*for (i = 0; i < path->index; i++)
            printf("%d ", path->nums[i]);
        printf("\n");*/

        if (path->pathes == NULL)
            path->count++;
        else {
            path->pathes_length[path->cur_pathes] = path->index;
            path->pathes[path->cur_pathes] = calloc(path->index, sizeof(int));
            memcpy(path->pathes[path->cur_pathes], path->nums, sizeof(int) * path->index);
            //printf("copy-%d %d\n", path->cur_pathes, path->pathes_length[path->cur_pathes]);
            path->cur_pathes++;

        }
        return;
    }

    index = path->index;
    if (root->left) {
        __pathSum(root->left, sum - root->val, path);
    }
    
    path->index = index;
    if (root->right) {
        __pathSum(root->right, sum - root->val, path);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int sum, int** columnSizes, int* returnSize) {
    struct path p;
    int i;
    
    p.index = 0;
    p.count = 0;
    p.cur_pathes = 0;
    p.pathes_length = NULL;
    p.pathes = NULL;
    
    __pathSum(root, sum, &p);
    
    //printf("count=%d\n", p.count);
    
    p.index = 0;
    p.pathes_length = calloc(p.count, sizeof(int));
    p.pathes = calloc(p.count, sizeof(int *));
    //for (i = 0; i < p.count; i++) {
       // p.pathes_length[i] = calloc(1, sizeof(int));
        //p.pathes[i] = calloc(20, sizeof(int));
    //}
    
    __pathSum(root, sum, &p);
    
    *columnSizes = p.pathes_length;
    *returnSize = p.count;
    
    return p.pathes;
}

//112. Path Sum
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode* root, int sum) {
    if (!root)
        return false;
 
    if (!root->left && !root->right && root->val == sum)
        return true;
    else 
        return hasPathSum(root->left, sum - root->val) ||
                hasPathSum(root->right, sum - root->val);
}

// 70. Climbing Stairs - no calculation version
int climbStairs(int n) {
    int record[1024] = {0,};
    int i;
    
    record[0] = 0;
    record[1] = 1;
    record[2] = 2;
    for (i = 3; i <= n; i++) {
        record[i] = record[i - 1] + record[i - 2];
    }
    return record[n];
}

// 70. Climbing Stairs
#if 0
/*
 * recursion version
 */
int climbStairs(int n) {
    if (n == 1) return 1;
    else if (n == 2) return 2;
    else return climbStairs(n - 1) + climbStairs(n - 2);
}

/*
 * iterative version
 */
struct queue {
    int tail;
    int rear;
    int *buf;
};

void push(struct queue *q, int v)
{
    q->buf[q->rear++] = v;
}

int pop(struct queue *q)
{
    int v;
    do {
        v = q->buf[q->tail++];
        if (q->tail == q->rear)
            break;
    } while (v <= 2);
    return v;
}

int climbStairs(int n)
{
    struct queue *q = malloc(sizeof(struct queue));
    int tmp;
    int step;
    q->buf = calloc(4096000, sizeof(int));
    q->rear = q->tail = 0;
    
    push(q, n);
    while (1) {
        tmp = pop(q);
        if (tmp <= 2)
            break;
        push(q, tmp - 1);
        push(q, tmp - 2);
    }
    
    step = 0;
    for (tmp = 0; tmp < q->rear; tmp++) {
        if (q->buf[tmp] <= 2)
            step += q->buf[tmp];
    }
    free(q->buf);
    free(q);
    return step;
}
#endif

/*
 * FINAL: record the previous results
 */
int _climbStairs(int *record, int n) {
    if (record[n]) {
        //printf("read [%d] = %d", n, record[n]);
        return record[n];
    }
    if (n == 1) return 1;
    else if (n == 2) return 2;
    else {
        record[n] = _climbStairs(record, n - 1) + _climbStairs(record, n - 2);
        //printf("record [%d] = %d", n, record[n]);
        return record[n];
    }
}

int climbStairs(int n) {
    int record[1024] = {0,};
    int i;
    
    record[0] = 0;
    record[1] = 1;
    record[2] = 2;
    return _climbStairs(record, n);
}

//53. Maximum Subarray
//https://discuss.leetcode.com/topic/5000/accepted-o-n-solution-in-java
#define max(a,b) (a) > (b) ? (a) : (b)

int maxSubArray(int* nums, int numsSize) {
    int cur_sum;
    int max_sum;
    int i;
    
    cur_sum = max_sum = nums[0];
    
    for (i = 1; i < numsSize; i++) {
        cur_sum = max(nums[i] + cur_sum, nums[i]);
        
        if (cur_sum > max_sum)
            max_sum = cur_sum;
    }
    
    return max_sum;
}

// 83. Remove Duplicates from Sorted List
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *cur;
    
    cur = head;
    while (cur != NULL) {
        if (cur->next != NULL && cur->val == cur->next->val)
            cur->next = cur->next->next;
        else
            cur = cur->next;
    }
    return head;
}

// 35. Search Insert Position
int searchInsert(int* nums, int numsSize, int target) {
    int i;
    
    if (target <= nums[0])
        return 0;
        
    for (i = 0; i < numsSize; i++) {
        if (nums[i] == target)
            break;
        if (target < nums[i])
            break;
    }
    return i;
}

//231. Power of Two
bool isPowerOfTwo(int n) {
    int i;
    int count = 0;
    int bits = sizeof(int) * 8;
    
    if (n < 0)
        return 0;
        
    for (i = 0; i < bits; i++) {
        if (n & 0x1)
            count++;
        n >>= 1;
    }
    
    return count == 1;
}

// 202. Happy Number
// refer: https://discuss.leetcode.com/topic/12587/my-solution-in-c-o-1-space-and-no-magic-math-property-involved
int get_happy(int n)
{
    int happy = 0;
    while (n > 0) {
        int digit = n % 10;
        happy += digit*digit;
        n /= 10;
    }
    return happy;
}

bool isHappy(int n) {
    int happy;
    int ret;
    int slow;
    int double_fast;
    
    slow = double_fast = n;
    
    while (1) {
        slow = get_happy(slow);    
        double_fast = get_happy(double_fast);
        double_fast = get_happy(double_fast);
        
        if (slow == 1) {
            ret = 1;
            break;
        } else if (slow == double_fast) {
            ret = 0;
            break;
        }
    }
    return ret;
}

//326. Power of Three
bool isPowerOfThree(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return  1;
    return (n % 3) == 0 && isPowerOfThree(n / 3);
}

//121. Best Time to Buy and Sell Stock
int maxProfit(int* prices, int pricesSize) {
	int i;
	int min = 0xfffffff;
	int profit = 0;

	for (i = 0; i < pricesSize; i++) {
		if (prices[i] < min)
			min = prices[i];
		else {
			if (prices[i] - min > profit)
				profit = prices[i] - min;
		}
		//printf("price=%d min=%d profit=%d\n",
		//       arr[i], min, profit);
	}
	
	return profit;
}

char* toHex(int num) {
    int mod;
    char table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char *str = calloc(10, sizeof(char));
    int index = 0;
    int i;
    int minus = 0;
    unsigned int absnum;
    
    if (num == 0) {
        str[index++] = '0';
        absnum = 0;  
    } else if (num > 0) {
        absnum = num;
    }
    else if (num < 0) {
        absnum = -num;
        absnum = ~absnum;
        absnum++;
    }

    while (absnum != 0) {
        mod = absnum % 16;
        absnum /= 16;
        //printf("%d %d\n", mod, absnum);
        str[index++] = table[mod];
    }
    
    for (i = 0; i < index/2; i++) {
        char t = str[i];
        str[i] = str[index - i - 1];
        str[index - i - 1] = t;
    }
    str[index] = 0;
    return str;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
 * refer to: https://discuss.leetcode.com/topic/77335/proper-o-1-space
 */
struct mode_info {
    int cur_val;
    int cur_count;
    int max_count;  // count of each mode
    int mode_count; // # of mode
    int *modes;
};

void travel(struct TreeNode *root, struct mode_info *info)
{
    if (root == NULL) return;
    else {
        travel(root->left, info);
        
        if (info->cur_val != root->val) {
            info->cur_val = root->val;
            info->cur_count = 1;
        } else {
            info->cur_count++;
        }
        
        if (info->cur_count > info->max_count) {
            info->max_count = info->cur_count;
            info->mode_count = 1; // found new mode
        } else if (info->cur_count == info->max_count) {
            if (info->modes != NULL)
                info->modes[info->mode_count] = info->cur_val;
            info->mode_count++; // 
        }
        
        travel(root->right, info);
    }
    return;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMode(struct TreeNode* root, int* returnSize) {
    struct mode_info info;
    memset(&info, 0, sizeof(info));
    
    info.cur_val = 0xffffffff;
    travel(root, &info);
    
    info.cur_val = 0xffffffff;
    info.modes = calloc(info.mode_count, sizeof(int));
    info.mode_count = 0;
    travel(root, &info);

    *returnSize = info.mode_count;
    return info.modes;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    int center;
    struct TreeNode *root;
    
    if (numsSize == 0)
        return NULL;

    root = malloc(sizeof(*root));

    if (numsSize & 0x1) // odd
        center = numsSize/2;
    else //even
        center = numsSize/2 - 1;
    root->val = nums[center];
    root->left = sortedArrayToBST(&nums[0], center);
    root->right = sortedArrayToBST(&nums[center + 1], numsSize - center - 1);
    
    return root;
}

char* addStrings(char* num1, char* num2) {
    int i, j;
    char *sum = calloc(5100, sizeof(char));
    int index = 0;
    int c;
    int v;
    
    c = 0;
    i = strlen(num1) - 1;
    j = strlen(num2) - 1;
    while (i >= 0 || j >= 0 || c == 1) {
        int a, b;
        
        if (i >= 0)
            a = num1[i] - '0';
        else
            a = 0;
            
        if (j >= 0)
            b = num2[j] - '0';
        else
            b = 0;
        
        v = a + b + c;
        if (v >= 10) {
            c = 1;
            v -= 10;
        } else
            c = 0;
        sum[index++] = v + '0';
        i--, j--;
    }

    for (i = 0; i < index/2; i++) {
        char t = sum[i];
        sum[i] = sum[index - i - 1];
        sum[index - i - 1] = t;
    }
    return sum;
}

int missingNumber(int* nums, int numsSize) {
    int sum = (numsSize * (numsSize + 1)) / 2;
    int lacksum = 0;
    int i;
    for (i = 0; i < numsSize; i++)
        lacksum += nums[i];
    return sum - lacksum;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *prev, *cur, *next;

    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;

    
    prev = head;
    cur = head->next;
    head->next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

/**
 * Old version is return *(int *)a - *(int *)b
 * but it's buggy because it cannot sort -2147483648 (-2147483648 - 1 = 2147483647)
 */
static int cmpint(const void *a, const void *b)
{
	int vala = *(int *)a;
	int valb = *(int *)b;
	if (vala > valb)
		return 1;
	else if (vala < valb)
		return -1;
	else
		return 0;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int i, j;
    int *buf;
    int index;
    int *ret;
    
    qsort(nums1, nums1Size, sizeof(int), cmpint);
    qsort(nums2, nums2Size, sizeof(int), cmpint);
    
    buf = calloc(nums2Size, sizeof(int));
    index = 0;
    
    i = j = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] < nums2[j])
            i++;
        else if (nums1[i] > nums2[j])
            j++;
        else {
            buf[index++] = nums1[i];
            i++, j++;
        }
    }

    *returnSize = index;
    return buf;
}

int numtobit(int num)
{
        int table[16] = {0, //0
                    1, //1
                    1, //2
                    2, //3
                    1, //4
                    2, //5
                    2, //6
                    3, //7
                    1, //8 -  1000
                    2, //9 -  1001
                    2, //10 - 1010
                    3, //11 - 1011
                    2, //12 - 1100
                    3, //13 - 1101
                    3, //14 - 1110
                    4}; //15 - 1111
                    
    return table[num/16] + table[num%16];
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** readBinaryWatch(int num, int* returnSize) {
    int count = 0;
    char *tmp[1000];
    char **ret;
    int i, j;
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 60; j++) {
            if (numtobit(i) + numtobit(j) == num) {
                char *t = calloc(6, sizeof(char));
                sprintf(t, "%d:%.2d", i, j);
                tmp[count++] = t;
            }
        }
    }
    ret = calloc(count, sizeof(char *));
    for (i = 0; i < count; i++) {
        ret[i] = tmp[i];
    }
    *returnSize = count;
    return ret;
}

bool containsDuplicate(int* nums, int numsSize) {
    int i;
    
    qsort(nums, numsSize, sizeof(int), numcmp);
    for (i = 0; i < numsSize - 1; i++)
        if (nums[i] == nums[i+1])
            break;
    if (i < numsSize - 1)
        return 1;
    return 0;
}

int longestPalindrome(char* s) {
    int counter[128] = {0,};
    int i;
    int len = strlen(s);
    int sum = 0;
    
    for (i = 0; i < len; i++) {
            counter[s[i]]++;
            if (0 == (counter[s[i]] & 0x1)) /* every second */
                sum++;
    }
    sum <<= 1;
    return sum == len ? sum : sum+1;
}

int hammingDistance(int x, int y) {
    int mask = (1 << 30);
    int distance = 0;
    
    do {
        if ((x & mask) ^ (y & mask))
            distance++;
        mask >>= 1;
    } while (mask);

    return distance;
}

int findComplement(int num) {
    int mask = (1 << 30);
    int i;
    
    while (!(num & mask))
        mask >>= 1;
        
    while (mask > 0) {
        num ^= mask;
        mask >>= 1;
    }
    return num;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fizzBuzz(int n, int* returnSize) {
    char **pp = calloc(n, sizeof(char *));
    char buf[10] = {0,};
    int i;
    
    for (i = 1; i <= n; i++) {
        if ((i % 3) != 0 && (i % 5) != 0)
            sprintf(buf, "%d", i);
        if ((i % 3) == 0)
            sprintf(buf, "Fizz");
        if ((i % 5) == 0)
            strcat(buf, "Buzz");
        pp[i - 1] = calloc(strlen(buf) + 1, sizeof(char));
        strcpy(pp[i - 1], buf);
        memset(buf, 0, 10);
    }
    *returnSize = i - 1;
    return pp;
}

char* reverseString(char* s) {
    int len = strlen(s);
    int i;
    char temp;
    for (i = 0; i < len/2; i++) {
        temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
    return s;
}

int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int count = 0;
    int i;
    int max = 0;
    
    for (i = 0; i < numsSize; i++) {
        if (nums[i] != 0 && i != 0)
            nums[i] = nums[i] + nums[i - 1];
        else if (nums[i] != 0 && i == 0)
            nums[i] = 1;
        else
            nums[i] = 0;
    }
    for (i = 0; i < numsSize; i++) {
        if (nums[i] > max)
            max = nums[i];
    }
    return max;
}

int islandPerimeter(int** grid, int gridRowSize, int gridColSize) {
    int r, c;
    int ret = 0;
    for (r = 0; r < gridRowSize; r++) {
        for (c = 0; c < gridColSize; c++) {
            if (grid[r][c] == 1) {
                if (c - 1 < 0)
                    ret++;
                else if (grid[r][c-1] == 0)
                    ret++;
                
                if (c + 1 >= gridColSize)
                    ret++;
                else if (grid[r][c+1] == 0)
                    ret++;
                
                if (r - 1 < 0)
                    ret++;
                else if (grid[r - 1][c] == 0)
                    ret++;
                    
                if (r + 1 >= gridRowSize)
                    ret++;
                else if (grid[r + 1][c] == 0)
                    ret++;
            }
        }
    }
    return ret;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    int i;
    int count = 0;
    int *ret;
    int index;
#define MASK (1 << 31)

    for (i = 0; i < numsSize; i++) {
        index = nums[i] & ~MASK;
        nums[index - 1] |= MASK;
    }
    
    /*for (i = 0; i < numsSize; i++)
        if (!(nums[i] & MASK))
            count++;*/
            
    ret = calloc(/*count*/numsSize, sizeof(int));
    count = 0;
    for (i = 0; i < numsSize; i++) {
        if (!(nums[i] & MASK))
            ret[count++] = i + 1;
    }
    *returnSize = count;
    return ret;
}

int singleNumber(int* nums, int numsSize) {
    int ret = 0;
    int i;
    for (i = 0; i < numsSize; i++) {
        ret ^= nums[i];
    }
    return ret;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructRectangle(int area, int* returnSize) {
    int width = (int)sqrt(area);
    int length;
    int *ret;
    
    for (;width > 0; width--) {
        if ((area % width) == 0) {
            length = area / width;
            break;
        }
    }
    ret = malloc(sizeof(int) * 2);
    ret[0] = length;
    ret[1] = width;
    *returnSize = 2;
    return ret;
}

int getSum(int a, int b) {
    int c, b1, b2;
    int result = 0;
    unsigned int mask;
    
    c = 0;
    for (mask = 1; mask > 0; mask <<= 1) {
	    b1 = a & mask;
	    b2 = b & mask;
	    if (c)
		    c = mask;
	    else
		    c = 0;
        
        result |= (c ^ b1 ^ b2);
        
        if (c != 0 && (b1 || b2))
            c = 1;
        else if (c == 0 && (b1 && b2))
            c = 1;
        else 
            c = 0;
    }
    return result;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    int left, right;
    if (root == NULL)
        return 0;

    left = maxDepth(root->left);
    right = maxDepth(root->right);
    if (left < right)
        return right+1;
    else
        return left+1;
}

char findTheDifference(char* s, char* t) {
    int i;
    char result = 0;
    int sl = strlen(s);
    int tl = strlen(t);
    
    for (i = 0; i < tl - 1; i++) {
        result ^= s[i];
        result ^= t[i];
    }
    
    return result ^ t[i];
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* invertTree(struct TreeNode* root) {
    struct TreeNode *t;
    
    if (!root)
        return NULL;

    t = root->left;
    root->left = root->right;
    root->right = t;

    invertTree(root->left);
    invertTree(root->right);
    return root;
}

void moveZeroes(int* nums, int numsSize) {
    int i;
    int j;
    int last = -1;
    
    for (i = 0; i < numsSize - 1; i++) {
        if (nums[i] == 0) {
            if (last < 0)
                last = i + 1;
            for (j = last; j < numsSize; j++) {
                if (nums[j] != 0)
                    break;
            }
            if (j >= numsSize)
                break;
            nums[i] = nums[j];
            nums[j] = 0;
            last = j;
        }
    }
}

int numcmp(const void *pa, const void *pb)
{
    return *(int *)pa - *(int *)pb;
}

int findContentChildren(int* g, int gSize, int* s, int sSize) {
    int i;
    int ret = 0;
    int j;
    
    qsort(g, gSize, sizeof(int), numcmp);
    qsort(s, sSize, sizeof(int), numcmp);
    
    for (i = 0; i < sSize; i++) {
        if (s[i] >= g[0])
            break;
    }
    
    for (; i < sSize; i++) {
        if (g[ret] <= s[i])
            ret++;
        if (ret >= gSize)
            break;
    }
    return ret;
}

int minMoves(int* nums, int numsSize) {
    int sum = 0;
    int min = nums[0];
    int i;
    for (i = 0; i < numsSize; i++) {
        sum += nums[i];
        if (nums[i] < min)
            min = nums[i];
    }
    return sum - min * numsSize;
}

bool canConstruct(char* ransomNote, char* magazine) {
    int counter['z'-'a'+1] = {0,};
    int i;
    int msize = strlen(magazine);
    int rsize = strlen(ransomNote);
    
    for (i = 0; i < msize; i++) {
        counter[magazine[i] - 'a']++;
    }
    for (i = 0; i < rsize; i++) {
        counter[ransomNote[i] - 'a']--;
        if (counter[ransomNote[i] - 'a'] < 0)
            return 0;
    }
    return 1;
}

static int cmpint(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int i;
    int *buf;
    int index;
    int *ret;
    
    qsort(nums1, nums1Size, sizeof(int), cmpint);
    qsort(nums2, nums2Size, sizeof(int), cmpint);
    
    buf = calloc(nums2Size, sizeof(int));
    index = 0;
    for (i = 0; i < nums2Size; i++) {
        ret = bsearch(&nums2[i], nums1, nums1Size, sizeof(int), cmpint);
        if (ret) {
            if (index == 0)
                buf[index++] = nums2[i];
            else if (buf[index-1] != nums2[i])
                buf[index++] = nums2[i];
        }
    }
    *returnSize = index;
    return buf;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int sumOfLeftLeaves(struct TreeNode* root) {
    int left = 0;

    if (root == NULL)
        return 0;
    if (root->left != NULL) {
        if (root->left->right == NULL && root->left->left == NULL)
            left = root->left->val;
        else
            left = sumOfLeftLeaves(root->left);
    }
    return left + sumOfLeftLeaves(root->right);
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) {
    struct ListNode *tmp = node->next;
    
    *node = *node->next;
    free(tmp);
}

int firstUniqChar(char* s) {
    int i;
    //int counter['z'-'a'+1];

    int *counter = calloc('z'-'a'+1, sizeof(int));
    int size = strlen(s);
    for (i = 0; i < 'z'-'a'+1; i++)
        counter[i] = 0;
    for (i = 0; i < size; i++) {
        counter[s[i] - 'a']++;
    }
    for (i = 0; i < size; i++) {
        if (counter[s[i] - 'a'] == 1) {
            free(counter);
            return i;
        }
    }
    free(counter);
    return -1;
}

int titleToNumber(char* s) {
    int num = 0;
    while (1) {
        num += *s - 'A' + 1;
        s++;
        if (*s) {
            num *= 26;
            continue;
        } else
            break;
    }
    return num;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == q)
        return 1;
    else if (p && q)
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    else
        return 0;

    /*
     *
     * oneline version
     *return (p == q) || (p && q && (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
     */
}

bool isAnagram(char* s, char* t) {
    int counter_s['z' - 'a' + 1] = {0,};
    int counter_t['z' - 'a' + 1] = {0,};
    char sum = 0;
    int i;
    int len_s = strlen(s);
    int len_t = strlen(t);
    
    if (len_s != len_t)
        return 0;
        
    for (i = 0; i < len_s; i++) {
        counter_s[s[i] - 'a']++;
        counter_t[t[i] - 'a']++;
    }
    return !memcmp(counter_s, counter_t, sizeof(int) * ('z'-'a'+1));
}

#if 0
/*
Boyer-Moore Majority Vote Algorithm
http://www.cs.utexas.edu/~moore/best-ideas/mjrty/
*/
int majorityElement(int* nums, int numsSize) {
    int major = nums[0];
    int count = 1;
    int i;
    
    for (i = 1; i < numsSize; i++) {
        if (nums[i] == major) {
            count++;
        } else if (count == 0) {
            major = nums[i];
            count++;
        } else {
            count--;
        }
    }
    return major;
}
#endif

int majorityElement(int* nums, int numsSize) {
    int major = (numsSize >> 1);
    int i;
    
    qsort(nums, numsSize, sizeof(int), numcmp);
	/* for (i = 0; i < numsSize; i++) */
	/* 	printf("%d\n", nums[i]); */

    
    /*for (i = 0; i < numsSize; i++) {
	    if (nums[i] == nums[i + major])
		    break;
    }
    return nums[i];*/
    return nums[numsSize/2];
}


