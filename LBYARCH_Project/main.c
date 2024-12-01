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
    int choice;
    int width, height;

    // Single input matrix
    printf("Pixels and Performance: A Grayscale Pixel Converter\n");
    printf("Convert Double Precision Floats to an Unsigned 8-bit Integer\n\n");

    printf("[1] Enter values yourself\n");
    printf("[2] Randomly generate inputs\n");

    // For testing 
    printf("[3] Run a single input matrix 30 times\n");
    printf("[4] Run 30 randomly generated matrices\n");
    printf("Enter choice: ");
    scanf_s("%d", &choice);

    if (choice < 1|| choice > 4) {
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

    if (choice == 1 || choice == 3) {
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

    if (choice == 2 || choice == 4) {
        // Initialize random input values
        srand((unsigned int)time(NULL));
        generateRandomInput(input, width, height);

        if (choice == 2) {
            printf("\nInput Image (Double Precision):\n");
            printImageDouble(input, width, height);
        }
        printf("\n");
    }
    
   
    // Time the assembly function
    LARGE_INTEGER frequency, start, end;
    double elapsedTime;

    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start); // Start timing
    printf("Calling assembly for each pixel...\n\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int idx = i * width + j;
            output[idx] = imgCvtGrayDoubleToInt(input[idx]); // Process each pixel once
        }
    }

    QueryPerformanceCounter(&end); // End timing
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("[1] Total time elapsed: %.10f seconds\n", elapsedTime);
	if (choice != 3 && choice != 4) {
        printf("\nOutput Image (8-bit Integer):\n");
        printImageUint8(output, width, height);

		// Free allocated memory
		free(input);
		free(output);
		return 0;
	}

    // For choice 3,4 
    double recordedTimes[30];
    recordedTimes[0] = elapsedTime;
    double avg_time = 0 + elapsedTime;
	char filename[30];

    // Repeat the process 29 more times and record the times
    for (int i = 1; i < 30; i++) {
        srand((unsigned int)time(NULL));

		generateRandomInput(input, width, height);
		QueryPerformanceCounter(&start); // Start timing
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int idx = i * width + j;
				output[idx] = imgCvtGrayDoubleToInt(input[idx]); // Process each pixel once
			}
		}
		QueryPerformanceCounter(&end); // End timing
		elapsedTime = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		printf("[%d] Total time elapsed: %.10f seconds\n", i+1,elapsedTime);
		recordedTimes[i] = elapsedTime;
		avg_time += elapsedTime;
	}
    avg_time /= 30;
   
    if (choice == 3) {
        sprintf_s(filename, 30, "tests/fixed_%dx%d.txt", height, width);
    }
    else if (choice == 4) {
        sprintf_s(filename, 30, "tests/random_%dx%d.txt", height, width);
    }
  
	// Export to file, overwrites if file already exists
    FILE* file = fopen(filename, "w");
    
	// Write input to file if fixed input
        if (choice == 3) {
            fprintf(file, "Input Matrix:\n");
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
				    int idx = i * width + j;
                    fprintf(file, "%.2f ", input[idx]); 
                }
                fprintf(file, "\n");
            }

            fprintf(file, "\n"); 
        }

    fprintf(file, "Average Time: %.10f seconds\n", avg_time);
    fprintf(file, "All Recorded Times:\n");
    for (int i = 0; i < 30; i++) {
        fprintf(file, "[%d] %.10f\n", i+1, recordedTimes[i]);
    }
    fclose(file);
    printf("Execution Times exported to '%s'.\n", filename);
   
	fclose(file);

    // Free allocated memory
    free(input);
    free(output);

    return 0;
}
