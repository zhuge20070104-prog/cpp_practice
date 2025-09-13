#include "arrow/api.h"
#include "arrow/io/api.h"
#include "arrow/result.h"
#include "arrow/util/type_fwd.h"
#include "parquet/arrow/reader.h"
#include "parquet/arrow/writer.h"

#include <iostream>

arrow::Result<std::shared_ptr<arrow::Table>> GetTable() {
    auto builder = arrow::Int32Builder();
    std::shared_ptr<arrow::Array> arr_x;
    ARROW_RETURN_NOT_OK(builder.AppendValues({1, 3, 5, 7, 1}));
    ARROW_RETURN_NOT_OK(builder.Finish(&arr_x));
    builder.Reset();

    std::shared_ptr<arrow::Array> arr_y;
    ARROW_RETURN_NOT_OK(builder.AppendValues({2, 4, 6, 8, 10}));
    ARROW_RETURN_NOT_OK(builder.Finish(&arr_y));

    auto schema = arrow::schema({
        arrow::field("x", arrow::int32()),
        arrow::field("y", arrow::int32())
    });

    return arrow::Table::Make(schema, {arr_x, arr_y});
}

arrow::Status WriteFullFile(std::string const& path_to_file) {
    using parquet::ArrowWriterProperties;
    using parquet::WriterProperties;

    ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::Table> table, GetTable());

    // 选择压缩
    std::shared_ptr<WriterProperties> props = WriterProperties::Builder().compression(arrow::Compression::SNAPPY)
        ->build();
    
    // 存储array schema的选项，用于快速读取
    std::shared_ptr<ArrowWriterProperties> arrow_props = 
        ArrowWriterProperties::Builder().store_schema()->build();

    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    ARROW_ASSIGN_OR_RAISE(outfile, arrow::io::FileOutputStream::Open(path_to_file));

    ARROW_RETURN_NOT_OK(parquet::arrow::WriteTable(*table.get(), 
                                                   arrow::default_memory_pool(),
                                                   outfile,
                                                   /*chunk_size=*/3,
                                                   props, 
                                                   arrow_props));
    return arrow::Status::OK();
}

arrow::Status ReadFullFile(std::string const& path_to_file) {
    arrow::MemoryPool* pool = arrow::default_memory_pool();
    std::shared_ptr<arrow::io::RandomAccessFile> input;
    ARROW_ASSIGN_OR_RAISE(input, arrow::io::ReadableFile::Open(path_to_file));

    std::unique_ptr<parquet::arrow::FileReader> arrow_reader;
    ARROW_RETURN_NOT_OK(parquet::arrow::OpenFile(input, pool, &arrow_reader));
    
    std::shared_ptr<arrow::Table> table;
    ARROW_RETURN_NOT_OK(arrow_reader->ReadTable(&table));
    std::cout << "Read Full File Result: " << std::endl;
    std::cout << table->ToString() << std::endl;
    return arrow::Status::OK();
}

arrow::Result<std::shared_ptr<arrow::TableBatchReader>> GetRBR() {
    ARROW_ASSIGN_OR_RAISE(std::shared_ptr<arrow::Table> table, GetTable());
    auto reader = std::make_shared<arrow::TableBatchReader>(table);
    reader->set_chunksize(10);
    return reader;
}

arrow::Status WriteInBatches(std::string const& path_to_file) {
    using parquet::ArrowWriterProperties;
    using parquet::WriterProperties;
    
    // Data in Record Batch
    std::shared_ptr<arrow::RecordBatchReader> batch_stream;
    ARROW_ASSIGN_OR_RAISE(batch_stream, GetRBR());

      // 选择压缩
    std::shared_ptr<WriterProperties> props = WriterProperties::Builder().compression(arrow::Compression::SNAPPY)
        ->build();
    
    // 存储array schema的选项，用于快速读取
    std::shared_ptr<ArrowWriterProperties> arrow_props = 
        ArrowWriterProperties::Builder().store_schema()->build();
    
    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    ARROW_ASSIGN_OR_RAISE(outfile, arrow::io::FileOutputStream::Open(path_to_file));
    std::unique_ptr<parquet::arrow::FileWriter> writer;
    ARROW_ASSIGN_OR_RAISE(writer, parquet::arrow::FileWriter::Open(*batch_stream->schema().get(), 
                                                                   arrow::default_memory_pool(),
                                                                   outfile,
                                                                   props,
                                                                   arrow_props));

    // 每个batch作为一个row_group 写入
    for(arrow::Result<std::shared_ptr<arrow::RecordBatch>> maybe_batch: *batch_stream) {
        ARROW_ASSIGN_OR_RAISE(auto batch, maybe_batch);
        ARROW_ASSIGN_OR_RAISE(auto table, arrow::Table::FromRecordBatches(batch->schema(), {batch}));
        ARROW_RETURN_NOT_OK(writer->WriteTable(*table.get(), batch->num_rows()));
    }

    // Write file footer and close
    ARROW_RETURN_NOT_OK(writer->Close());
    return arrow::Status::OK();
}


arrow::Status ReadInBatches(std::string const& path_to_file) {
    arrow::MemoryPool* pool = arrow::default_memory_pool();
    auto reader_properties = parquet::ReaderProperties(pool);
    reader_properties.set_buffer_size(4096 * 4);
    reader_properties.enable_buffered_stream();

    auto arrow_reader_props = parquet::ArrowReaderProperties();
    arrow_reader_props.set_batch_size(128 * 1024);

    parquet::arrow::FileReaderBuilder reader_builder;
    ARROW_RETURN_NOT_OK(reader_builder.OpenFile(path_to_file, 
        /*memory_map=*/false, reader_properties));
    reader_builder.memory_pool(pool);
    reader_builder.properties(arrow_reader_props);

    std::unique_ptr<parquet::arrow::FileReader> arrow_reader;
    ARROW_ASSIGN_OR_RAISE(arrow_reader, reader_builder.Build());
    
    std::shared_ptr<arrow::RecordBatchReader> rb_reader;
    ARROW_RETURN_NOT_OK(arrow_reader->GetRecordBatchReader(&rb_reader));

    for(arrow::Result<std::shared_ptr<arrow::RecordBatch>> maybe_batch: *rb_reader) {
        // 处理每个RecordBatch
        ARROW_ASSIGN_OR_RAISE(auto batch, maybe_batch);
        ARROW_ASSIGN_OR_RAISE(auto table, arrow::Table::FromRecordBatches(batch->schema(), {batch}));
        std::cout << "A Table: " << std::endl;
        std::cout << table->ToString() << std::endl;
    }
    return arrow::Status::OK();
}

arrow::Status RunExamples(std::string const& path_to_file) {
    ARROW_RETURN_NOT_OK(WriteFullFile(path_to_file));
    ARROW_RETURN_NOT_OK(ReadFullFile(path_to_file));
    ARROW_RETURN_NOT_OK(WriteInBatches(path_to_file));
    ARROW_RETURN_NOT_OK(ReadInBatches(path_to_file));
    return arrow::Status::OK();
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " {FileName}.parquet" << std::endl;
        return EXIT_FAILURE;
    }

    std::string path_to_file = argv[1];
    arrow::Status st = RunExamples(path_to_file);
    if(!st.ok()) {
        std::cerr << "Error occurred: " << st.message() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}