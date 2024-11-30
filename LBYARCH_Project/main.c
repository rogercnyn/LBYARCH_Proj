#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>

// Declare the assembly function
extern void imgCvtGrayDoubleToInt(double* input, unsigned char* output, int width, int height);

void generateRandomInput(double* input, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        input[i] = (double)rand() / RAND_MAX;
    }
}

void printImageDouble(double* image, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%.2f ", image[i * width + j]);
        }
        printf("\n");
    }
}

void printImageUint8(unsigned char* image, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%3d ", image[i * width + j]);
        }
        printf("\n");
    }
}

int main() {
    int width, height;

    // Input image dimensions with safety checks
    printf("Enter image width: ");
    if (scanf_s("%d", &width) != 1 || width <= 0) {
        printf("Invalid input for width.\n");
        return 1;
    }

    printf("Enter image height: ");
    if (scanf_s("%d", &height) != 1 || height <= 0) {
        printf("Invalid input for height.\n");
        return 1;
    }

    // Allocate memory for input and output arrays
    double* input = malloc(width * height * sizeof(double));
    if (!input) {
        printf("Memory allocation failed for input.\n");
        return 1;
    }

    unsigned char* output = malloc(width * height * sizeof(unsigned char));
    if (!output) {
        printf("Memory allocation failed for output.\n");
        free(input);
        return 1;
    }

    // Initialize random input values
    srand((unsigned int)time(NULL));
    generateRandomInput(input, width, height);

    printf("\nInput Image (Double Precision):\n");
    printImageDouble(input, width, height);

    // Time the assembly function
    LARGE_INTEGER frequency, start, end;
    double elapsedTime;
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start);
    for (int i = 0; i < 30; i++) {
        imgCvtGrayDoubleToInt(input, output, width, height);
    }
    QueryPerformanceCounter(&end);

    elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart / 30;
    printf("\nAverage execution time: %.10f seconds\n", elapsedTime);

    printf("\nOutput Image (8-bit Integer):\n");
    printImageUint8(output, width, height);

    // Free allocated memory
    free(input);
    free(output);

    return 0;
}