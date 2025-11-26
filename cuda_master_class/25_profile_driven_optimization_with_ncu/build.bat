# Windows cmake build
conan install ..
cmake ..
cmake --build . --config Debug


# 3. 查询实际占用值
# 管理员权限打开Powershell,
# 执行下面命令

# 获取occupancy信息
ncu --set full --page details ./bin/optimization.exe 0 25 0 7
ncu --set full -o profile_result ./bin/optimization.exe 1 25 20 7 2
ncu --set full -o profile_result ./bin/optimization.exe 1 25 20 8 2


# 获取 h2d/ d2h/ gpu computing time等信息
nsys profile -o profile_trace ./bin/optimization.exe 0 25 0 7
nsys stats profile_trace.nsys-rep


nsys profile -o profile_trace_1 ./bin/optimization.exe 1 25 20 7 2
nsys stats profile_trace_1.nsys-rep

nsys profile -o profile_trace_2 ./bin/optimization.exe 1 25 20 8 2
nsys stats profile_trace_2.nsys-rep