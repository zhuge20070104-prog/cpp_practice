# Windows cmake build
conan install ..
cmake ..
cmake --build . --config Debug

# branch efficiency testing
"C:\Program Files\NVIDIA Corporation\Nsight Compute 2025.1.0\ncu" --metrics smsp__sass_average_branch_targets_threads_uniform.pct .\bin\warpDivergence.exe