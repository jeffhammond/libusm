#include <stdio.h>
#include <stdlib.h>

#include "libusm.h"

int main(int argc, char* argv[])
{
    size_t bytes = (argc>1) ? atol(argv[1]) : 1000000;
    size_t align = 64;

    cl_int rc = CL_SUCCESS;

    cl_platform_id platforms[3];
    cl_uint num_platforms = 0;
    rc = clGetPlatformIDs( 3, platforms, &num_platforms );
    if (rc != CL_SUCCESS) abort();

    libusm_initialize( platforms[0] );
    printf("libusm initialized\n");

    cl_device_id devices[100];
    cl_uint num_devices = 0;
    rc = clGetDeviceIDs( platforms[0], CL_DEVICE_TYPE_GPU, 100, devices, &num_devices );
    if (rc != CL_SUCCESS) abort();

    printf("found %u OpenCL GPU devices\n", num_devices);

    cl_context context = clCreateContext( NULL /* default properties */,
                                          num_devices, devices,
                                          NULL, NULL, /* no error info callback */
                                          &rc);
    if (rc != CL_SUCCESS) abort();

    void ** ptrs = malloc( sizeof(void*) * num_devices );
    for (unsigned i = 0; i < num_devices; i++) {
        ptrs[i] = clDeviceMemAllocINTEL( context, devices[i],
                                         NULL /* default properties? */,
                                         bytes, align, &rc);
        if (rc != CL_SUCCESS) abort();
        printf("allocated %zu bytes on device %u\n", bytes, i);
    }

    for (unsigned i = 0; i < num_devices; i++) {
        rc = clMemFreeINTEL( context, ptrs[i] );
        if (rc != CL_SUCCESS) abort();
        printf("freed %zu bytes on device %u\n", bytes, i);
    }

    rc = clReleaseContext(context);
    if (rc != CL_SUCCESS) abort();

    printf("ALL DONE\n");
    return 0;
}
