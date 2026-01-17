// Description: https://leetcode.com/problems/car-fleet/description/

/*
    Approach: Sorting + Monotonic Stack

    Calculate the time each car needs to reach the target: time = (target - position) / speed.
    Pair each car's position with its arrival time.
    Sort cars by position in descending order (closest to target first).
    Use a stack to track distinct fleets based on arrival times.
    If a car takes more time than the car ahead, it forms a new fleet.
    If it takes less time, it catches up and merges with the fleet ahead.

    Time complexity: O(n log n) - Due to sorting.
    Space complexity: O(n) - For storing car pairs and stack.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int position;
    double time;
} Car;

int compare(const void* a, const void* b) {
    Car* carA = (Car*)a;
    Car* carB = (Car*)b;
    return carB->position - carA->position;  // Descending order
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize) {
    if (positionSize == 0) return 0;

    Car* cars = (Car*)malloc(positionSize * sizeof(Car));

    for (int i = 0; i < positionSize; i++) {
        cars[i].position = position[i];
        cars[i].time = (double)(target - position[i]) / speed[i];
    }

    // Sort by position in descending order
    qsort(cars, positionSize, sizeof(Car), compare);

    double* stack = (double*)malloc(positionSize * sizeof(double));
    int top = -1;

    for (int i = 0; i < positionSize; i++) {
        double time = cars[i].time;
        // If current car takes more time, it forms a new fleet
        if (top == -1 || time > stack[top]) {
            stack[++top] = time;
        }
        // Otherwise, it catches up and joins the fleet ahead
    }

    int fleets = top + 1;

    free(cars);
    free(stack);

    return fleets;
}

// Test
int main() {
    // Example 1: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
    int pos1[] = {10, 8, 0, 5, 3};
    int speed1[] = {2, 4, 1, 1, 3};
    printf("Output: %d\n", carFleet(12, pos1, 5, speed1, 5));

    // Example 2: target = 10, position = [3], speed = [3]
    int pos2[] = {3};
    int speed2[] = {3};
    printf("Output: %d\n", carFleet(10, pos2, 1, speed2, 1));

    // Example 3: target = 100, position = [0,2,4], speed = [4,2,1]
    int pos3[] = {0, 2, 4};
    int speed3[] = {4, 2, 1};
    printf("Output: %d\n", carFleet(100, pos3, 3, speed3, 3));

    return 0;
}
