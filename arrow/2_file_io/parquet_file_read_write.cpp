#include "file_gen.h"

arrow::Status run_main() {
    std::shared_ptr<arrow::io::ReadableFile> in_file;
    ARROW_ASSIGN_OR_RAISE(in_file, arrow::io::ReadableFile::Open("test_in.parquet"));
    std::unique_ptr<parquet::arrow::FileReader> reader;
    PARQUET_THROW_NOT_OK(parquet::arrow::OpenFile(in_file, arrow::default_memory_pool(), &reader));

    std::shared_ptr<arrow::Table> parquet_table;
    PARQUET_THROW_NOT_OK(reader->ReadTable(&parquet_table));

    std::cout << "Parquet table: " << std::endl;
    std::cout << parquet_table->ToString() << std::endl;
    
    std::shared_ptr<arrow::io::FileOutputStream> out_file;
    ARROW_ASSIGN_OR_RAISE(out_file, arrow::io::FileOutputStream::Open("test_out.parquet"));
    PARQUET_THROW_NOT_OK(parquet::arrow::WriteTable(*parquet_table, arrow::default_memory_pool(),
        out_file, 5));
    
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