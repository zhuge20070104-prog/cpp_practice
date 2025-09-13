#include "file_gen.h"

arrow::Status run_main() {
    std::shared_ptr<arrow::io::ReadableFile> in_file;
    ARROW_ASSIGN_OR_RAISE(in_file, arrow::io::ReadableFile::Open("test_in.csv"));
    std::shared_ptr<arrow::Table> csv_table;
    ARROW_ASSIGN_OR_RAISE(auto csv_reader,
        arrow::csv::TableReader::Make(arrow::io::default_io_context(),
        in_file,
        arrow::csv::ReadOptions::Defaults(),
        arrow::csv::ParseOptions::Defaults(),
        arrow::csv::ConvertOptions::Defaults()));

    ARROW_ASSIGN_OR_RAISE(csv_table, csv_reader->Read());

    std::shared_ptr<arrow::io::FileOutputStream> out_file;
    ARROW_ASSIGN_OR_RAISE(out_file, arrow::io::FileOutputStream::Open("test_out.csv"));
    ARROW_ASSIGN_OR_RAISE(auto csv_writer, arrow::csv::MakeCSVWriter(out_file, csv_table->schema()));

    ARROW_RETURN_NOT_OK(csv_writer->WriteTable(*csv_table));
    ARROW_RETURN_NOT_OK(csv_writer->Close());

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