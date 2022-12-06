// ELEC 522 Project 1 CUDA Code
// Adapted from Nvidia learning resources and web site
// Note that there is a lot of error checking on GPU setup

// Include files for Helper functions and utilities to work with CUDA
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cstdio>
#include <cstdlib>

// Regular C include file
#include <stdio.h>


// CPU Helper code declaration for CPU function to be detailed later in the file
cudaError_t addWithCuda(int *c, int *a, int *b, unsigned int size);

// CUDA definition for code to actually run on GPU
// Inputs are a and b, result is written into c
// Note that there is no loop as would be on the CPU code
// Simple one dimensional "threadIdx.x" when called sets parallelism
__global__ void addKernel(int *c, int *a, int *b)
{
    int i = blockIdx.x*blockDim.x+threadIdx.x;
    c[i] = a[i] + b[i];
}
// CUDA definition ends
 

// C Code to run on main CPU and then call GPU kernel
int main()
{
    const int arraySize = 64000;
    int a[arraySize] = { 0 };
    int b[arraySize] = { 0 };
    int c[arraySize] = { 0 };
    int i;

    for (i = 0; i < arraySize; i++) {
        a[i] = { i + 1 };
        b[i] = { (i + 1) * 10 };
    }

    // Add vectors in parallel. Call CPU helper function
    // This helper then calls GPU
    cudaError_t cudaStatus;
    cudaStatus = addWithCuda(c, a, b, arraySize);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addWithCuda failed!");
        return 1;
    }

    // After results are returned by GPU, the CPU prints results returned in c vector.
    printf("Vector length is %d\n", arraySize);
    printf("First 8 values {1,2,3,4,5,6,7,8} + {10,20,30,40,50,60,70,80} = {%d,%d,%d,%d,%d,%d,%d,%d}\n",
        c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
    printf("Final 2 values of vector {%d,%d} + {%d,%d} = {%d,%d}\n",
        a[arraySize - 2], a[arraySize - 1], b[arraySize - 2], b[arraySize - 1], c[arraySize - 2], c[arraySize - 1]);

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }

    return 0;
}
// End of main CPU function.


// CPU Helper function for using CUDA to add vectors in parallel.
// The call to the GPU will happen in this helper.
cudaError_t addWithCuda(int *c, int *a, int *b, unsigned int size)
{
    int *dev_a = 0;
    int *dev_b = 0;
    int *dev_c = 0;
    cudaError_t cudaStatus;


    // Parameters set to execute the kernel on GPU
    // Do one iteration of the code. More iterations would give better average time results
    int nIter = 1;
    // Number of parallel threads to execute on the GPU. Here it is the vector length or size.
    // Maximum number of threads per block is 1024.
    int threads = 1024;
    if (threads > 1024)
        fprintf(stderr, "Maximum threads/block is 1024. Increase block size and reduce threads/block. \n\n");
    // Number of blocks on the GPU. Threads can be grouped into blocks for control.
    // For small problem one block is sufficient. If more than 1024 threads increase blocks.
    int blocks = 63;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        exit(EXIT_FAILURE);
    }

    // Allocate GPU buffers for three vectors (two input, one output) 
    // These three buffers on GPU will be where we transfer data from CPU to GPU to do calculation.
    // cudaMalloc allocates space on GPU DRAM
    cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        exit(EXIT_FAILURE);
    }

    cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        exit(EXIT_FAILURE);
    }

    cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        exit(EXIT_FAILURE);
    }

    // Copy input vectors from host memory to GPU buffers.
    // cudaMemcpy is the transfer function and "cudaMemcpyHostToDevice" is the direction.
    // This example uses explicit allocation and copy to see the details in first programs.
    // The "Unified Memory" model would "hide" these details from the programmer.
    cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        exit(EXIT_FAILURE);
    }

    cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        exit(EXIT_FAILURE);
    }

    // Allocate CUDA start and stop events that we'll use for timing analysis
    cudaEvent_t start;
    cudaStatus = cudaEventCreate(&start);

    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "Failed to create start event (error code %s)!\n", cudaGetErrorString(cudaStatus));
        exit(EXIT_FAILURE);
    }

    cudaEvent_t stop;
    cudaStatus = cudaEventCreate(&stop);

    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "Failed to create stop event (error code %s)!\n", cudaGetErrorString(cudaStatus));
        exit(EXIT_FAILURE);
    }

    // Record the start event timestamp on the GPU clock
    cudaStatus = cudaEventRecord(start, NULL);

    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "Failed to record start event (error code %s)!\n", cudaGetErrorString(cudaStatus));
        exit(EXIT_FAILURE);
    }

    // Launch a kernel on the GPU with one thread for each element.
    // This is the actual driver call to the GPU setting the parallelism.
    // blocks and threads set the parallelism; dev_a and dev_b data as already been copied.
    // Result will be written in to dev_c but will remain in GPU until copied back later.
    addKernel<<<blocks, threads>>>(dev_c, dev_a, dev_b);


   // Record the stop event on GPU after "addKernel" finishes.
    cudaStatus = cudaEventRecord(stop, NULL);

    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "Failed to record stop event (error code %s)!\n", cudaGetErrorString(cudaStatus));
        exit(EXIT_FAILURE);
    }

    // Wait for the stop event to complete. This barrier is needed before reading back data.
    cudaStatus = cudaEventSynchronize(stop);

    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "Failed to synchronize on the stop event (error code %s)!\n", cudaGetErrorString(cudaStatus));
        exit(EXIT_FAILURE);
    }


    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);

    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        exit(EXIT_FAILURE);
    }

    // Compute GPU kernel elapsed time as difference of stop and start timestamps.
    float msecTotal = 0.0f;
    cudaStatus = cudaEventElapsedTime(&msecTotal, start, stop);

    if (cudaStatus != cudaSuccess)
    {
        fprintf(stderr, "Failed to get time elapsed between events (error code %s)!\n", cudaGetErrorString(cudaStatus));
        exit(EXIT_FAILURE);
    }

    
		
    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        exit(EXIT_FAILURE);
    }
    else {
        // Compute and print the performance
        float msecPerVectorAdd = msecTotal / nIter;
        double opsPerVectorAdd = 1.0 * (double)size;
        double megaOps = (opsPerVectorAdd * 1.0e-6f) / (msecPerVectorAdd / 1000.0f);
        printf("Performance= %.4f Mops/s, Time= %.4f msec, Size= %.0f Ops\n",
            megaOps, msecPerVectorAdd, opsPerVectorAdd);
        printf("WorkgroupSize: Threads= %u, Blocks= %u, Total Threads= %u\n\n",
            threads, blocks, threads * blocks);
    }
    
    // With GPU kernel completed do garbage collection and free up allocated GPU memory.
    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);
    
    return cudaStatus;
}
