# Windows cmake build
conan install ..
cmake ..
cmake --build . --config Debug

echo "=== Running Nsight Systems (nsys) for timeline analysis ==="
nsys profile -t cuda,nvtx -o timeline --force-overwrite=true .\bin\parallelReduction.exe
nsys stats timeline.nsys-rep

echo ""
echo "=== Running Nsight Compute (ncu) for detailed kernel analysis ==="
ncu --set basic -o kernel_analysis --force-overwrite .\bin\parallelReduction.exe

echo ""
echo "=== Quick kernel metrics with ncu ==="
ncu --metrics sm__cycles_elapsed.avg,dram__bytes.sum,gpu__time_duration.sum .\bin\parallelReduction.exe