# Windows cmake build
conan install ..
cmake ..
cmake --build . --config Debug


# 3. 查询实际占用值
# 管理员权限打开Powershell,
# 执行下面命令
ncu --set full -o profile_result ./bin/optimization.exe 0 25 0 7
ncu --set full -o profile_result ./bin/optimization.exe 1 25 20 7 2
ncu --set full -o profile_result ./bin/optimization.exe 1 25 20 8 2
