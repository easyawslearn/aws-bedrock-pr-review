#include <stdio.h>
#include <string.h>

// TODO: Add support for negative numbers in factorial
int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1); // FIXME: Stack overflow risk for large n
}

// BUG: This function does not check buffer size properly
void unsafe_copy(char *dest, const char *src) {
    strcpy(dest, src); // HACK: Using strcpy without bounds check
}

// REVIEW: Should we use iterative instead of recursive here?
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2); // OPTIMIZE: This is very slow for large n
}

// DEPRECATED: Use `safe_divide` instead
float divide(int a, int b) {
    if (b == 0) return 0; // BUG: Silent failure, should return error code
    return (float)a / (float)b;
}

float safe_divide(int a, int b, int *error) {
    if (b == 0) {
        *error = 1;
        return 0.0;
    }
    *error = 0;
    return (float)a / (float)b;
}

int main() {
    int num = 5;

    printf("Factorial: %d\n", factorial(num));
    printf("Fibonacci: %d\n", fibonacci(num));

    char buffer[10];
    unsafe_copy(buffer, "This is too long"); // REVIEW: May cause buffer overflow

    int error;
    printf("Safe Divide: %f\n", safe_divide(10, 0, &error));
    if (error) {
        // NOTE: Division failed, error handled gracefully
        printf("Error: Division by zero!\n");
    }

    return 0;
}
