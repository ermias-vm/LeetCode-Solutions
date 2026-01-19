// Description: https://leetcode.com/problems/min-stack/description/

/*
    Approach: Two Stacks

    Use a main stack to store all elements pushed.
    Use a separate min stack to track minimum values at each state.
    Push to min stack only when value is <= current minimum.
    When popping, also pop from min stack if values match.
    getMin() returns top of min stack in O(1) time.
    This design maintains minimum tracking through push/pop operations.

    Time complexity: O(1) - All operations are constant time.
    Space complexity: O(n) - Two stacks store at most n elements each.
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 1000

typedef struct {
    int* mainStack;
    int* minStack;
    int mainTop;
    int minTop;
    int capacity;
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    obj->capacity = INITIAL_CAPACITY;
    obj->mainStack = (int*)malloc(obj->capacity * sizeof(int));
    obj->minStack = (int*)malloc(obj->capacity * sizeof(int));
    obj->mainTop = -1;
    obj->minTop = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    // Resize if needed
    if (obj->mainTop + 1 >= obj->capacity) {
        obj->capacity *= 2;
        obj->mainStack = (int*)realloc(obj->mainStack, obj->capacity * sizeof(int));
        obj->minStack = (int*)realloc(obj->minStack, obj->capacity * sizeof(int));
    }

    obj->mainStack[++obj->mainTop] = val;

    // Push to min stack if empty or val <= current min
    if (obj->minTop < 0 || val <= obj->minStack[obj->minTop]) {
        obj->minStack[++obj->minTop] = val;
    }
}

void minStackPop(MinStack* obj) {
    if (obj->mainTop < 0) return;

    // If popped value equals min, also pop from min stack
    if (obj->mainStack[obj->mainTop] == obj->minStack[obj->minTop]) {
        obj->minTop--;
    }
    obj->mainTop--;
}

int minStackTop(MinStack* obj) {
    return obj->mainStack[obj->mainTop];
}

int minStackGetMin(MinStack* obj) {
    return obj->minStack[obj->minTop];
}

void minStackFree(MinStack* obj) {
    free(obj->mainStack);
    free(obj->minStack);
    free(obj);
}

// Test
int main() {
    // Example 1: ["MinStack","push","push","push","getMin","pop","top","getMin"]
    // [[],[-2],[0],[-3],[],[],[],[]]
    MinStack* stk = minStackCreate();
    minStackPush(stk, -2);
    minStackPush(stk, 0);
    minStackPush(stk, -3);
    printf("Output: %d, ", minStackGetMin(stk));  // return -3
    minStackPop(stk);
    printf("%d, ", minStackTop(stk));     // return 0
    printf("%d\n", minStackGetMin(stk));  // return -2
    minStackFree(stk);

    return 0;
}
