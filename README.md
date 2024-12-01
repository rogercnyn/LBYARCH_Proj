\# Grayscale Pixel Converter README

\## Introduction

The \*\*Grayscale Pixel Converter\*\* is a program that demonstrates the
conversion of double-precision floating-point grayscale values into
8-bit unsigned integer values. This is achieved through a
high-performance, assembly-optimized function that scales the pixel
values from the range of \`\[0.0, 1.0\]\` to \`\[0, 255\]\` and
truncates them into integers, which are used to represent pixel
intensities in grayscale images.

The program allows you to either input grayscale values manually,
generate random inputs, or benchmark the performance of the conversion
process over multiple runs.

\## Explanation

\### How the program works

1\. \*\*Input Generation:\*\*  - The program provides different options
for input:  - \*\*Manually Input\*\*: You can enter grayscale values
directly for each pixel.  - \*\*Random Input\*\*: The program generates
a random set of grayscale values between 0.0 and 1.0.

2\. \*\*Conversion Process:\*\*  - The program calls a function written
in assembly (\`imgCvtGrayDoubleToInt\`) for each pixel. The function
performs the following steps:  - Multiplies the input double value by
255 to scale the grayscale intensity to an 8-bit range.  - Truncates the
scaled value to an integer.  - Clamps the value to ensure it stays
within the range \`\[0, 255\]\`.  - Returns the final 8-bit value, which
represents the grayscale intensity of the pixel.

3\. \*\*Performance Benchmarking:\*\*  - The program measures the time
it takes to process the entire image, and optionally, the time it takes
to process 30 matrices of random inputs, for a performance comparison.
 - The performance is measured using the high-resolution timer available
in the Windows API (\`QueryPerformanceCounter\`).

4\. \*\*Output:\*\*  - The program prints the output image in 8-bit
unsigned integer format (i.e., pixel values in the range of 0--255).  -
If performance benchmarking is chosen, execution times are logged and
can be exported to a file for analysis.

\### Key Features: - \*\*Assembly-optimized Conversion\*\*: The core of
the pixel conversion is implemented in assembly to maximize performance,
particularly when processing large images or multiple runs. - \*\*Random
and Manual Input\*\*: Provides flexibility in testing the performance
with either user-defined or random input values. - \*\*Performance
Benchmarking\*\*: The program tracks and records the time taken for
processing, helping to assess the efficiency of the grayscale conversion
operation.

\### Performance Analysis The performance analysis section allows you to
evaluate the program\'s speed and efficiency when processing large or
multiple images. The execution time of each run is recorded, and the
program computes the average time across 30 runs. This data is written
to a file for further analysis.

\-\--

\## How to Use

\### Steps: 1. \*\*Compile and Run\*\*:  - Compile the C code along with
the assembly function.  - Execute the program.

2\. \*\*Choose an Option\*\*:  - Enter \`1\` to input values manually.
 - Enter \`2\` to generate random inputs.  - Enter \`3\` to test the
performance with a fixed input.  - Enter \`4\` to test the performance
with random inputs.

3\. \*\*Input Dimensions\*\*:  - Enter the width and height for the
image.

4\. \*\*View Results\*\*:  - The program will process the input, convert
the grayscale values, and display the resulting image. It will also show
the execution time for the conversion process.

5\. \*\*Export Results\*\*:  - For options 3 and 4, the execution times
are logged into a text file. This file can be used for performance
analysis.

\-\--

\## Execution Time & Performance Analysis

\### Execution Times

The program records the execution time for each image processing run,
both for a fixed input matrix (if you select option 3) and for randomly
generated matrices (if you select option 4). The execution times are
stored in the \`tests\` directory with filenames that include the image
dimensions.

\- \*\*Fixed Input Test (\`option 3\`)\*\*: The program will use a
single, fixed matrix for all runs. Execution times for 30 runs are
logged, and the average execution time is calculated.

\- \*\*Random Input Test (\`option 4\`)\*\*: The program will generate a
new random matrix for each of the 30 runs. Execution times are again
recorded, and the average execution time is calculated.

\### Example Output:

\`\`\`bash \[1\] Total time elapsed: 0.0001234567 seconds \[2\] Total
time elapsed: 0.0001202345 seconds \... \[30\] Total time elapsed:
0.0001185673 seconds Average Time: 0.0001202345 seconds \`\`\`

\### Performance Export

The recorded execution times and the average time for the 30 runs are
written to a file named \`fixed_XXXxYYY.txt\` or \`random_XXXxYYY.txt\`
(depending on the chosen test). This file contains both the detailed
execution times for each test run and the average time.

\### Performance Analysis

When analyzing the performance, consider the following factors: -
\*\*Image Size\*\*: Larger images will take more time to process, so
analyzing the execution time for different image sizes can provide
insights into how the program scales. - \*\*Assembly Optimization\*\*:
The use of assembly can result in significant performance improvements
compared to high-level implementations, especially when processing
multiple images or larger matrices.

For example, if you notice a significant variance in the execution times
for randomly generated matrices (option 4), it may indicate that factors
like CPU caching or random memory access patterns are influencing the
performance. You could further experiment with different image sizes to
see if the program handles scaling efficiently.

\-\--

\## Conclusion

This grayscale pixel converter showcases both the power of assembly
language for optimizing critical operations and the flexibility of the C
programming language for managing input/output and performance
measurement. The program not only performs the necessary pixel
conversion but also helps benchmark the efficiency of the underlying
algorithm across multiple test cases.

\### Next Steps: - \*\*Optimize for Other Architectures\*\*: You can
modify the assembly code to optimize the conversion for other
architectures (e.g., ARM, or M1/M2 chips). - \*\*Parallelize the
Conversion\*\*: Consider parallelizing the processing of pixels to
further improve performance for large images or in real-time
applications.
