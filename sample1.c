#include <stdio.h>

// Function to add two numbers
int add(int a, int b) {
    return a + b; // TODO: Handle integer overflow case
}

// Function to subtract two numbers
int subtract(int a, int b) {
    return a - b; // NOTE: Works fine for positive/negative values
}

// Function to multiply two numbers
int multiply(int a, int b) {
    return a * b; // FIXME: Might overflow for large inputs
}

// Function to divide two numbers
float divide(int a, int b) {
    if (b == 0) {
        // BUG: Division by zero should return error, not 0
        return 0;
    }
    return (float)a / (float)b;
}

int main() {
    int x = 10, y = 0;

    printf("Add: %d\n", add(x, y));
    printf("Subtract: %d\n", subtract(x, y));
    printf("Multiply: %d\n", multiply(x, y));
    printf("Divide: %f\n", divide(x, y)); // REVIEW: Should we handle divide-by-zero more gracefully?

    return 0;
}
