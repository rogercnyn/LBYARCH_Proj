#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>

// Declare the updated assembly function
extern unsigned char imgCvtGrayDoubleToInt(double value);

void generateRandomInput(double* input, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        input[i] = (double)(rand() % 101) / 100;
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
    int choice;

    printf("Pixels and Prose kineso\n"); 
    printf("[1] to input values yourself\n[2] randomly generate inputs\n");
	printf("Enter choice: ");
    scanf_s("%d", &choice);

	if (choice != 1 && choice != 2) {
		printf("Invalid choice.\n");
		return 1;
	}

    // Input image dimensions with safety checks
    printf("\nEnter image height: ");
    if (scanf_s("%d", &height) != 1 || height <= 0) {
        printf("Invalid input for height.\n");
        return 1;
    }

    printf("Enter image width: ");
    if (scanf_s("%d", &width) != 1 || width <= 0) {
        printf("Invalid input for width.\n");
        return 1;
    }

    // Allocate memory for input and output arrays
    double* input = malloc(width * height * sizeof(double));
    unsigned char* output = malloc(width * height * sizeof(unsigned char));
    if (!input || !output) {
        printf("Memory allocation failed.\n");
        return 1;
    }


    if (choice == 1) {
        // Accept input values from stdin
        printf("\nEnter %d values for the image:\n", width * height);
        for (int i = 0; i < width * height; i++) {
            if (scanf_s("%lf", &input[i]) != 1) {
                printf("Invalid input for image values.\n");
                free(input);
                free(output);
                return 1;
            }
        }
        printf("\n");
    }
    if (choice == 2) {
        // Initialize random input values
        srand((unsigned int)time(NULL));
        generateRandomInput(input, width, height);
        printf("\nInput Image (Double Precision):\n");
        printImageDouble(input, width, height);
        printf("\n");
    }

    // Time the assembly function
    LARGE_INTEGER frequency, start, end;
    double elapsedTime;

    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start); // Start timing
    printf("Calling assembly for each pixel\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int idx = i * width + j;
            output[idx] = imgCvtGrayDoubleToInt(input[idx]); // Process each pixel once
        }
    }
    QueryPerformanceCounter(&end); // End timing

    elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Total time elapsed: %.6f seconds\n", elapsedTime);
    printf("\nOutput Image (8-bit Integer):\n");
    printImageUint8(output, width, height);

    printf("\nAverage execution time: %.10f seconds\n", elapsedTime);

    // Free allocated memory
    free(input);
    free(output);

    return 0;
}
