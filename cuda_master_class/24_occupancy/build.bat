# Windows cmake build
conan install ..
cmake ..
cmake --build . --config Debug


# CUDA Occupancy Calculator
# 这就是计算一个理论值，三步走
# 1. 在CMake中加入compile options -Xptxas=-v
# 2. 编译 cmake --build . --config Debug
查找下面的section:
ptxas info    : Used 10 registers, used 0 barriers, 360 bytes cmem[0]
里面有used registers和  shared memory
根据这个信息可以去 Nsight Compute中打开 occupancy calculator，
输入这些信息，查询理论的占用值。(Nsight Compute 2025.1.0)

# 3. 查询实际占用值
# 管理员权限打开Powershell,
# 执行下面命令
ncu --set full .\bin\occupancyTest.exe > occupancy.txt

# 4. 在生成的occupancy.txt文件中，搜索occupancy即可，
输出大致如下，

实际对SM的占用率是 71.29%

 Section: Occupancy
    ------------------------------- ----------- ------------
    Metric Name                     Metric Unit Metric Value
    ------------------------------- ----------- ------------
    Block Limit SM                        block           24
    Block Limit Registers                 block           32
    Block Limit Shared Mem                block           32
    Block Limit Warps                     block           12
    Theoretical Active Warps per SM        warp           48
    Theoretical Occupancy                     %          100
    Achieved Occupancy                        %        71.29
    Achieved Active Warps Per SM           warp        34.22
    ------------------------------- ----------- ------------


