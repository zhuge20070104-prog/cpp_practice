# Windows cmake build
conan install ..
cmake ..
cmake --build . --config Debug

ncu --metrics smsp__sass_average_data_bytes_per_sector_mem_global_op_ld.pct,l1tex__t_bytes_pipe_lsu_mem_global_op_ld.sum.per_second,l1tex__t_sectors_pipe_lsu_mem_global_op_ld.sum,l1tex__average_t_sectors_per_request_pipe_lsu_mem_global_op_ld.ratio ./bin/cudaMemoryModel.exe 9

  Section: Command line profiler metrics
    -------------------------------------------------------------------- ----------- ------------
    Metric Name                                                          Metric Unit Metric Value
    -------------------------------------------------------------------- ----------- ------------
    l1tex__average_t_sectors_per_request_pipe_lsu_mem_global_op_ld.ratio      sector            4
    l1tex__t_bytes_pipe_lsu_mem_global_op_ld.sum.per_second                  Gbyte/s       304.73
    l1tex__t_sectors_pipe_lsu_mem_global_op_ld.sum                            sector    1,048,576
    smsp__sass_average_data_bytes_per_sector_mem_global_op_ld.pct                  %          100
    -------------------------------------------------------------------- ----------- ------------

ncu --metrics smsp__sass_average_data_bytes_per_sector_mem_global_op_ld.pct,l1tex__t_bytes_pipe_lsu_mem_global_op_ld.sum.per_second,l1tex__t_sectors_pipe_lsu_mem_global_op_ld.sum,l1tex__average_t_sectors_per_request_pipe_lsu_mem_global_op_ld.ratio ./bin/cudaMemoryModel.exe 7

     Section: Command line profiler metrics
    -------------------------------------------------------------------- ----------- ------------
    Metric Name                                                          Metric Unit Metric Value
    -------------------------------------------------------------------- ----------- ------------
    l1tex__average_t_sectors_per_request_pipe_lsu_mem_global_op_ld.ratio      sector            4
    l1tex__t_bytes_pipe_lsu_mem_global_op_ld.sum.per_second                  Gbyte/s       312.73
    l1tex__t_sectors_pipe_lsu_mem_global_op_ld.sum                            sector    1,048,576
    smsp__sass_average_data_bytes_per_sector_mem_global_op_ld.pct                  %          100
    -------------------------------------------------------------------- ----------- ------------


ncu --metrics smsp__sass_average_data_bytes_per_sector_mem_global_op_ld.pct,l1tex__t_bytes_pipe_lsu_mem_global_op_ld.sum.per_second,l1tex__t_sectors_pipe_lsu_mem_global_op_ld.sum,l1tex__average_t_sectors_per_request_pipe_lsu_mem_global_op_ld.ratio ./bin/cudaMemoryModel.exe 2

    Section: Command line profiler metrics
    -------------------------------------------------------------------- ----------- ------------
    Metric Name                                                          Metric Unit Metric Value
    -------------------------------------------------------------------- ----------- ------------
    l1tex__average_t_sectors_per_request_pipe_lsu_mem_global_op_ld.ratio      sector            1
    l1tex__t_bytes_pipe_lsu_mem_global_op_ld.sum.per_second                  Gbyte/s        38.26
    l1tex__t_sectors_pipe_lsu_mem_global_op_ld.sum                            sector    2,097,152
    smsp__sass_average_data_bytes_per_sector_mem_global_op_ld.pct                  %           50
    -------------------------------------------------------------------- ----------- ------------