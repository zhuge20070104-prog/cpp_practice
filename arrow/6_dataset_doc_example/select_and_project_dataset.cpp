#include "gen_data.h"

arrow::Status run_main() {
    ARROW_ASSIGN_OR_RAISE(auto file_env, PrepareFileEnv(Normal));
    fs::FileSelector selector;
    selector.base_dir = file_env.data_set_dir;
    ARROW_ASSIGN_OR_RAISE(auto factory, ds::FileSystemDatasetFactory::Make(
        file_env.fs, selector, file_env.format, ds::FileSystemFactoryOptions()
    ));
    ARROW_ASSIGN_OR_RAISE(auto dataset, factory->Finish());
    
    ARROW_ASSIGN_OR_RAISE(auto scan_builder, dataset->NewScan());

    std::vector<std::string> names;
    std::vector<cp::Expression> exprs;

    for(auto const& field: dataset->schema()->fields()) {
        names.push_back(field->name());
        exprs.push_back(cp::field_ref(field->name()));
    }

    names.emplace_back("b_large");
    exprs.push_back(cp::greater(cp::field_ref("b"), cp::literal(1)));
    ARROW_RETURN_NOT_OK(scan_builder->Project(exprs, names));

    ARROW_ASSIGN_OR_RAISE(auto scanner, scan_builder->Finish());
    ARROW_ASSIGN_OR_RAISE(auto table, scanner->ToTable());
    std::cout << "Read " << table->num_rows() << " rows" << std::endl;
    std::cout << table->ToString() << std::endl;
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