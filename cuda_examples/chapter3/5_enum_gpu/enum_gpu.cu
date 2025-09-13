#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <memory>
#include "utilities.h"


int main(int argc, char* argv[]) {
    cudaDeviceProp prop;
    int count;
    HANDLE_ERROR(cudaGetDeviceCount(&count));
    for(int i=0; i<count; ++i) {
        HANDLE_ERROR(cudaGetDeviceProperties(&prop, i));
        std::cout << "  --- General information of device " << i << "   ---\n";
        std::cout << "Name: " << prop.name << "\n";
        std::cout << "Compute capability: " << prop.major << "." << prop.minor << "\n";
        std::cout << "Clock rate: " << prop.clockRate << "\n";
        std::cout << "Device copy overlap: ";
        if(prop.deviceOverlap) 
            std::cout << "Enabled\n";
        else 
            std::cout << "Disabled\n";
        
        std::cout << "  --- Memory information of device " << i << "   ---\n";
        std::cout << "Total global memory: " << prop.totalGlobalMem << "\n";
        std::cout << "Total const memory: " << prop.totalConstMem << "\n";
        std::cout << "Max mem pitch: " << prop.memPitch << "\n";
        std::cout << "Texture alignment: " << prop.textureAlignment << "\n";

        std::cout << "  --- MP information of device " << i << "   ---\n";
        std::cout << "Multiprocessor count: " << prop.multiProcessorCount << "\n";
        std::cout << "Shared memory per mp: " << prop.sharedMemPerBlock << "\n";
        std::cout << "Register per mp: " << prop.regsPerBlock << "\n";
        std::cout << "Threads in warp: " << prop.warpSize << "\n";
        std::cout << "Max threads per block: " << prop.maxThreadsPerBlock << "\n";

        std::cout << "Max thread dimensons: (" << prop.maxThreadsDim[0] << ", " <<
            prop.maxThreadsDim[1] << ", " << prop.maxThreadsDim[2] << ")\n";  
        
        std::cout << "Max grid dimensons: (" << prop.maxGridSize[0] << ", " <<
            prop.maxGridSize[1] << ", " << prop.maxGridSize[2] << ")\n";
        
        std::cout << "\n";
    }   
    return EXIT_SUCCESS;
}