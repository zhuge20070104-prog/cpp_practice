#include "file_gen.h"

arrow::Status run_main() {
    std::shared_ptr<arrow::io::ReadableFile> in_file;
    ARROW_ASSIGN_OR_RAISE(in_file, arrow::io::ReadableFile::Open(
        "test_in.arrow", arrow::default_memory_pool()));
    ARROW_ASSIGN_OR_RAISE(auto ipc_reader, 
        arrow::ipc::RecordBatchFileReader::Open(in_file));
    
    std::shared_ptr<arrow::RecordBatch> rbatch;
    ARROW_ASSIGN_OR_RAISE(rbatch, ipc_reader->ReadRecordBatch(0));
    std::cout << "In batch: " << std::endl;
    std::cout << rbatch->ToString() << std::endl;

    std::shared_ptr<arrow::io::FileOutputStream> out_file;
    ARROW_ASSIGN_OR_RAISE(out_file, arrow::io::FileOutputStream::Open("test_out.arrow"));
    ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::ipc::RecordBatchWriter> ipc_writer,
        arrow::ipc::MakeFileWriter(out_file, rbatch->schema()));
    
    ARROW_RETURN_NOT_OK(ipc_writer->WriteRecordBatch(*rbatch));
    ARROW_RETURN_NOT_OK(ipc_writer->Close());

    return arrow::Status::OK();
}


int main(int argc, char* argv[]) {
    arrow::Status st = run_main();
    if(!st.ok()) {
        std::cerr << st << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}