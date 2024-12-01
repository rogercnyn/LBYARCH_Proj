# Grayscale Pixel Converter README

## Introduction

The **Grayscale Pixel Converter** is a program that demonstrates the conversion of double-precision floating-point grayscale values into 8-bit unsigned integer values. This is achieved through a high-performance, assembly-optimized function that scales the pixel values from the range of `[0.0, 1.0]` to `[0, 255]` and truncates them into integers, which are used to represent pixel intensities in grayscale images.

The program allows you to either input grayscale values manually, generate random inputs, or benchmark the performance of the conversion process over multiple runs.

## Demonstration
You can watch a demonstration of how to run the program in the following video: [LINK HERE]

The video also provides a walkthrough of the code and a brief explanation of its functionality.

## Explanation

### How the program works

1. **Input Generation:**  
   - The program provides different options for input:  
     - **Manually Input**: You can enter grayscale values directly for each pixel.  
     - **Random Input**: The program generates a random set of grayscale values between 0.0 and 1.0.

2. **Conversion Process:**  
   - The program calls a function written in assembly (`imgCvtGrayDoubleToInt`) for each pixel. The function performs the following steps:  
     - Multiplies the input double value by 255 to scale the grayscale intensity to an 8-bit range.  
     - Converts the scaled value to an integer.  
     - Clamps the value to ensure it stays within the range `[0, 255]`.  
     - Returns the final 8-bit value, which represents the grayscale intensity of the pixel.

3. **Performance Benchmarking:**  
   - The program measures the time it takes to process the entire image, and optionally, the time it takes to process 30 matrices of random inputs, for a performance comparison.  
   - The performance is measured using the high-resolution timer available in the Windows API (`QueryPerformanceCounter`).

4. **Output:**  
   - The program prints the output image in 8-bit unsigned integer format (i.e., pixel values in the range of 0--255).  
   - If performance benchmarking is chosen, execution times are logged and can be exported to a file for analysis.

### Key Features:

- **Assembly-optimized Conversion:** The core of the pixel conversion is implemented in assembly to maximize performance, particularly when processing large images or multiple runs.  
- **Random and Manual Input:** Provides flexibility in testing the performance with either user-defined or random input values.  
- **Performance Benchmarking:** The program tracks and records the time taken for processing, helping to assess the efficiency of the grayscale conversion operation.

---

## Execution Time & Performance Analysis

### Execution Times

The table below summarizes the recorded execution times for different image sizes across 30 runs. The average time for each image size is also provided.

| Image Size | Average Time (seconds) | Recorded Times (seconds) |
|------------|------------------------|---------------------------|
| **10x10**  | 0.0000022300            | 0.0000550000, 0.0000005000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000003000, 0.0000004000, 0.0000004000, 0.0000003000, 0.0000004000, 0.0000005000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000005000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000004000, 0.0000005000, 0.0000004000, 0.0000005000 |
| **100x100**| 0.0000344667            | 0.0000786000, 0.0000330000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000332000, 0.0000328000, 0.0000328000, 0.0000365000, 0.0000328000, 0.0000330000, 0.0000327000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000327000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000328000, 0.0000327000 |
| **1000x1000**| 0.0034339500          | 0.0047376000, 0.0032443000, 0.0033876000, 0.0032063000, 0.0033111000, 0.0035314000, 0.0031988000, 0.0031996000, 0.0031983000, 0.0032802000, 0.0031993000, 0.0045949000, 0.0031986000, 0.0032410000, 0.0031970000, 0.0031934000, 0.0032100000, 0.0039424000, 0.0031964000, 0.0031982000, 0.0031989000, 0.0032474000, 0.0032138000, 0.0034339000, 0.0041349000, 0.0032341000, 0.0032575000, 0.0032054000, 0.0031971000, 0.0044291000 |

### Performance Analysis

- **Small Images (10x10):** The average time for processing small images is extremely low, indicating that the overhead for setup and input generation has a more significant impact than the actual conversion. The variance in execution times suggests that caching and memory access patterns influence performance.
- **Medium Images (100x100):** The average time increases as the image size grows. However, the variance between recorded times is relatively low, indicating stable performance across runs.
- **Large Images (1000x1000):** The average time is significantly higher for larger images. The variance in execution times suggests that memory access patterns, CPU cache usage, and potential context switching play a more critical role at this scale.

---
## Correctness Check
To ensure the accuracy of the conversion process, we manually computed the conversion of various grayscale values and cross-checked them against the program's output. These computations and outputs were documented in a Google Sheets file, which includes screenshots and detailed results for verification. The cross-checking process confirmed that the program accurately converts double-precision floating-point grayscale values to 8-bit unsigned integers within the expected range of 0 to 255.

You can view the detailed documentation and verification results in the Google Sheets file here: 
https://docs.google.com/spreadsheets/d/1Yo1X0QvaNczk_kXvabrvhfB57kqX3-3ft6oAIExDvi4/edit?usp=sharing 

---
## Conclusion

This grayscale pixel converter showcases the power of assembly language for optimizing critical operations and the flexibility of the C programming language for managing input/output and performance measurement. The program not only performs the necessary pixel conversion but also benchmarks the efficiency of the underlying algorithm across multiple test cases.
