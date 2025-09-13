#include <arrow/api.h>
#include <arrow/compute/api.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace cp = arrow::compute;
// 该模板函数仅支持 数字，bool 和 日期时间类型构造
template <typename TYPE, typename = typename std::enable_if<arrow::is_number_type<TYPE>::value | 
                                       arrow::is_boolean_type<TYPE>::value |
                                       arrow::is_temporal_type<TYPE>::value>::type>
arrow::Result<std::shared_ptr<arrow::Array>> GetArrayDataSample(
    std::vector<typename TYPE::c_type> const& values) {
    
    using ArrowBuilderType = typename arrow::TypeTraits<TYPE>::BuilderType;
    ArrowBuilderType builder;
    ARROW_RETURN_NOT_OK(builder.Reserve(values.size()));
    ARROW_RETURN_NOT_OK(builder.AppendValues(values));
    return builder.Finish();
}

cp::FunctionDoc const func_doc {
    "User-defined-function usage to demonstrate registering an out-of-tree function",
    "returns x + y + z",
    {"x", "y", "z"},
    "UDFOptions"
};

arrow::Status SampleFunction(cp::KernelContext* ctx, cp::ExecSpan const& batch, 
    cp::ExecResult* out) {
    
    int64_t const* x = batch[0].array.GetValues<int64_t>(1);
    int64_t const* y = batch[1].array.GetValues<int64_t>(1);
    int64_t const* z = batch[2].array.GetValues<int64_t>(1);
    int64_t* out_values = out->array_span_mutable()->GetValues<int64_t>(1);
    for(int64_t i=0; i<batch.length; ++i) {
        *out_values++ = *x++ + *y++ + *z++;
    }
    return arrow::Status::OK();
}

arrow::Status Execute() {
    std::string const name = "add_three";
    auto func = std::make_shared<cp::ScalarFunction>(name, cp::Arity::Ternary(), func_doc);
    cp::ScalarKernel kernel({arrow::int64(), arrow::int64(), arrow::int64()}, 
        arrow::int64(), SampleFunction);
    kernel.mem_allocation = cp::MemAllocation::PREALLOCATE;
    kernel.null_handling = cp::NullHandling::INTERSECTION;

    ARROW_RETURN_NOT_OK(func->AddKernel(std::move(kernel)));
    auto registry = cp::GetFunctionRegistry();
    ARROW_RETURN_NOT_OK(registry->AddFunction(std::move(func)));

    ARROW_ASSIGN_OR_RAISE(auto x, GetArrayDataSample<arrow::Int64Type>({1, 2, 3}));
    ARROW_ASSIGN_OR_RAISE(auto y, GetArrayDataSample<arrow::Int64Type>({4, 5, 6}));
    ARROW_ASSIGN_OR_RAISE(auto z, GetArrayDataSample<arrow::Int64Type>({7, 8, 9}));
    ARROW_ASSIGN_OR_RAISE(auto res, cp::CallFunction(name, {x, y, z}));

    auto res_array = res.make_array();
    std::cout << "Result: " << std::endl;
    std::cout << res_array->ToString() << std::endl;
    return arrow::Status::OK();
}

int main(int argc, char* argv[]) {
    arrow::Status st = Execute();
    if(!st.ok()) {
        std::cerr << "Error occurred: " << st.message() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
