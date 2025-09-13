#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>

#include <iostream>

std::shared_ptr<arrow::Table> GenerateTable() {
    arrow::Int64Builder i64builder;
    PARQUET_THROW_NOT_OK(i64builder.AppendValues({1, 2, 3, 4, 5}));
    std::shared_ptr<arrow::Array> i64array;
    PARQUET_THROW_NOT_OK(i64builder.Finish(&i64array));

    arrow::StringBuilder strbuilder;
    PARQUET_THROW_NOT_OK(strbuilder.AppendValues({"some", "string", "content", "in", "rows"}));
    std::shared_ptr<arrow::Array> strarray;
    PARQUET_THROW_NOT_OK(strbuilder.Finish(&strarray));

    std::shared_ptr<arrow::Schema> schema = arrow::schema(
        {arrow::field("int", arrow::int64()), 
         arrow::field("str", arrow::utf8())}
    );

    return arrow::Table::Make(schema, {i64array, strarray});
}

// Write out the data as a parquet file
void WriteParquetFile(arrow::Table const& table) {
    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    PARQUET_ASSIGN_OR_THROW(outfile, arrow::io::FileOutputStream::Open("parquet-arrow-example.parquet"));
    // The last argument to the function call is the size of the RowGroup in
    // the parquet file. Normally you would choose this to be rather large but
    // for the example, we use a small value to have multiple RowGroups.
    PARQUET_THROW_NOT_OK(parquet::arrow::WriteTable(table, arrow::default_memory_pool(), outfile, 3));
}

// 2. Fully read in the file
void ReadWholeFile() {
    std::cout << "Reading parquet-arrow-example.parquet at once" << std::endl;
    std::shared_ptr<arrow::io::ReadableFile> infile;
    PARQUET_ASSIGN_OR_THROW(infile, arrow::io::ReadableFile::Open("parquet-arrow-example.parquet", 
        arrow::default_memory_pool()));
    
    std::unique_ptr<parquet::arrow::FileReader> reader;
    PARQUET_THROW_NOT_OK(parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
    std::shared_ptr<arrow::Table> table;
    PARQUET_THROW_NOT_OK(reader->ReadTable(&table));
    std::cout << "Loaded " << table->num_rows() << " rows in " << table->num_columns()
        << " columns" << std::endl;
    std::cout << table->ToString() << std::endl;
}

void ReadSingleRowGroup() {
    std::cout << "Reading first RowGroup of parquet-arrow-example.parquet" << std::endl;
    std::shared_ptr<arrow::io::ReadableFile> infile;
    PARQUET_ASSIGN_OR_THROW(infile, arrow::io::ReadableFile::Open("parquet-arrow-example.parquet", 
        arrow::default_memory_pool()));
    
    std::unique_ptr<parquet::arrow::FileReader> reader;
    PARQUET_THROW_NOT_OK(parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
    std::shared_ptr<arrow::Table> table;
    PARQUET_THROW_NOT_OK(reader->RowGroup(0)->ReadTable(&table));
    std::cout << "Loaded " << table->num_rows() << " rows in " << table->num_columns()
        << " columns" << std::endl;
    std::cout << table->ToString() << std::endl;
}

void ReadSingleColumn() {
    std::cout << "Reading first Column of parquet-arrow-example.parquet" << std::endl;
    std::shared_ptr<arrow::io::ReadableFile> infile;
    PARQUET_ASSIGN_OR_THROW(infile, arrow::io::ReadableFile::Open("parquet-arrow-example.parquet", 
        arrow::default_memory_pool()));
    
    std::unique_ptr<parquet::arrow::FileReader> reader;
    PARQUET_THROW_NOT_OK(parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
    std::shared_ptr<arrow::ChunkedArray> array;
    PARQUET_THROW_NOT_OK(reader->ReadColumn(0, &array));
    PARQUET_THROW_NOT_OK(arrow::PrettyPrint(*array, 4, &std::cout));
    std::cout << std::endl;
}

// #5: Read only a single column of a RowGroup (this is known as ColumnChunk)
//     from the Parquet file.
void ReadSingleColumnChunk() {
    std::cout << "Reading first ColumnChunk of the first RowGroup of " 
        "parquet-arrow-example.parquet" << std::endl;
    std::shared_ptr<arrow::io::ReadableFile> infile;
    PARQUET_ASSIGN_OR_THROW(infile, arrow::io::ReadableFile::Open("parquet-arrow-example.parquet", 
        arrow::default_memory_pool()));
    
    std::unique_ptr<parquet::arrow::FileReader> reader;
    PARQUET_THROW_NOT_OK(parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
    std::shared_ptr<arrow::ChunkedArray> array;
    PARQUET_THROW_NOT_OK(reader->RowGroup(0)->Column(0)->Read(&array));
    PARQUET_THROW_NOT_OK(arrow::PrettyPrint(*array, 4, &std::cout));
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::shared_ptr<arrow::Table> table = GenerateTable();
    WriteParquetFile(*table);
    ReadWholeFile();
    ReadSingleRowGroup();
    ReadSingleColumn();
    ReadSingleColumnChunk();
    return EXIT_SUCCESS;
}