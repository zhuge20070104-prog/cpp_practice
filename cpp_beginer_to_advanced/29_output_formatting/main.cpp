#include <iostream>
#include <iomanip>
#include <functional>
#include <map>

struct cout_test {
    enum func_type {
        ENDL,
        FLUSH,
        UNFORMATTED,
        FORMATTED,
        FORMATTED_WITH_VAR,
        RIGHT_JUSTIFIED,
        LEFT_JUSTIFIED,
        INTERNAL_JUSTIFIED,
        FILLED_CHARS,
        BOOL_VAR,
        SHOW_POS,
        BASE,
        UPPERCASE,
        SCIENTIFIC_AND_FIXED,
        PRECISION,
        SHOW_POINT
    };

    
    std::function<void(void)> endl_func = [] () {
        std::cout << "Hello";
        std::cout << "World";
        std::cout << std::endl;

        std::cout << "---------------" << std::endl;
        std::cout << "Hello" << std::endl;
        std::cout << "World" << std::endl;
        std::cout << std::endl;

        std::cout << "Hello\n";
        std::cout << "World\n";

        std::cout << std::endl;
    };

    std::function<void(void)> flush_func = [] () {
        std::cout << "This is a nice message..." << std::endl << std::flush;
        std::cout << std::endl;
    };

    std::function<void(void)> unformatted_func = [] () {
        std::cout << "Unformatted table: " << std::endl;
        std::cout << "Daniel" << " " << "Gray" << " 25" << std::endl;
        std::cout << "Stanley" << " " << "Woods" << " 33" << std::endl;
        std::cout << "Jordan" << " " << "Parker" << " 45" << std::endl;
        std::cout << "Joe" << " " << "Ball" << " 21" << std::endl;
        std::cout << "Josh" << " " << "Carr" << " 27" << std::endl;
        std::cout << "Izaiah" << " " << "Robinson" << " 29" << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> formatted_func = [] () {
        std::cout << "Formatted table: " << std::endl;
        std::cout << std::setw(10) << "Daniel" << std::setw(10) << "Gray" << std::setw(5) << " 25" << std::endl;
        std::cout << std::setw(10) << "Stanley" << std::setw(10) << "Woods" << std::setw(5) << " 33" << std::endl;
        std::cout << std::setw(10) << "Jordan" << std::setw(10) << "Parker" << std::setw(5) << " 45" << std::endl;
        std::cout << std::setw(10) << "Joe" << std::setw(10) << "Ball" << std::setw(5) << " 21" << std::endl;
        std::cout << std::setw(10) << "Josh" << std::setw(10) << "Carr" << std::setw(5) << " 27" << std::endl;
        std::cout << std::setw(10) << "Izaiah" << std::setw(10) << "Robinson" << std::setw(5) << " 29" << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> formatted_with_var_func = [] () {
        int col_width = 14;
        std::cout << "Formatted table with variables" << std::endl;
        std::cout << std::setw(col_width) << "Daniel" << std::setw(col_width) << "Gray" << std::setw(col_width/2) << " 25" << std::endl;
        std::cout << std::setw(col_width) << "Stanley" << std::setw(col_width) << "Woods" << std::setw(col_width/2) << " 33" << std::endl;
        std::cout << std::setw(col_width) << "Jordan" << std::setw(col_width) << "Parker" << std::setw(col_width/2) << " 45" << std::endl;
        std::cout << std::setw(col_width) << "Joe" << std::setw(col_width) << "Ball" << std::setw(col_width/2) << " 21" << std::endl;
        std::cout << std::setw(col_width) << "Josh" << std::setw(col_width) << "Carr" << std::setw(col_width/2) << " 27" << std::endl;
        std::cout << std::setw(col_width) << "Izaiah" << std::setw(col_width) << "Robinson" << std::setw(col_width/2) << " 29" << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> right_justified_func = [] () {
        std::cout << "Right justified table: " << std::endl;
        int col_width = 20;
        std::cout << std::right;
        std::cout << std::setw(col_width) << "Daniel" << std::setw(col_width) << "Gray" << std::setw(col_width/2) << " 25" << std::endl;
        std::cout << std::setw(col_width) << "Stanley" << std::setw(col_width) << "Woods" << std::setw(col_width/2) << " 33" << std::endl;
        std::cout << std::setw(col_width) << "Jordan" << std::setw(col_width) << "Parker" << std::setw(col_width/2) << " 45" << std::endl;
        std::cout << std::setw(col_width) << "Joe" << std::setw(col_width) << "Ball" << std::setw(col_width/2) << " 21" << std::endl;
        std::cout << std::setw(col_width) << "Josh" << std::setw(col_width) << "Carr" << std::setw(col_width/2) << " 27" << std::endl;
        std::cout << std::setw(col_width) << "Izaiah" << std::setw(col_width) << "Robinson" << std::setw(col_width/2) << " 29" << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> left_justified_func = [] () {
        std::cout << "Left justified table: " << std::endl;
        int col_width = 20;
        std::cout << std::left;
        std::cout << std::setw(col_width) << "Daniel" << std::setw(col_width) << "Gray" << std::setw(col_width/2) << " 25" << std::endl;
        std::cout << std::setw(col_width) << "Stanley" << std::setw(col_width) << "Woods" << std::setw(col_width/2) << " 33" << std::endl;
        std::cout << std::setw(col_width) << "Jordan" << std::setw(col_width) << "Parker" << std::setw(col_width/2) << " 45" << std::endl;
        std::cout << std::setw(col_width) << "Joe" << std::setw(col_width) << "Ball" << std::setw(col_width/2) << " 21" << std::endl;
        std::cout << std::setw(col_width) << "Josh" << std::setw(col_width) << "Carr" << std::setw(col_width/2) << " 27" << std::endl;
        std::cout << std::setw(col_width) << "Izaiah" << std::setw(col_width) << "Robinson" << std::setw(col_width/2) << " 29" << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> internal_justified_func = [] () {
        // Internal justified 数字和符号分开打印
        std::cout << "Internal justified" << std::endl;
        std::cout << std::right;
        std::cout << std::setw(10) << -123.45 << std::endl;
        std::cout << std::internal;
        std::cout << std::setw(10) << -123.45 << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> filled_chars_func = [] () {
        std::cout << "Table with filled characters" << std::endl;
        int col_width = 20;
        std::cout << std::setfill('*'); // The fill characters
        std::cout << std::setw(col_width) << "Daniel" << std::setw(col_width) << "Gray" << std::setw(col_width/2) << " 25" << std::endl;
        std::cout << std::setw(col_width) << "Stanley" << std::setw(col_width) << "Woods" << std::setw(col_width/2) << " 33" << std::endl;
        std::cout << std::setw(col_width) << "Jordan" << std::setw(col_width) << "Parker" << std::setw(col_width/2) << " 45" << std::endl;
        std::cout << std::setw(col_width) << "Joe" << std::setw(col_width) << "Ball" << std::setw(col_width/2) << " 21" << std::endl;
        std::cout << std::setw(col_width) << "Josh" << std::setw(col_width) << "Carr" << std::setw(col_width/2) << " 27" << std::endl;
        std::cout << std::setw(col_width) << "Izaiah" << std::setw(col_width) << "Robinson" << std::setw(col_width/2) << " 29" << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> bool_var_func = []() {
        bool condition = true;
        bool other_condition = false;

        std::cout << "condition: " << condition << std::endl;
        std::cout << "other_condition: " << other_condition << std::endl;

        std::cout << std::endl;
        std::cout << std::boolalpha;
        std::cout << "condition: " << condition << std::endl;
        std::cout << "other_condition: " << other_condition << std::endl;
        
        std::cout << std::endl;
        std::cout << std::noboolalpha;
        std::cout << "condition: " << condition << std::endl;
        std::cout << "other_condition: " << other_condition << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> show_pos_func = []() {
        // show_pos, 显示正数前面的加号
        int pos_num = 34;
        int neg_num = -45;

        std::cout << "pos_num: " << pos_num << std::endl;
        std::cout << "neg_num: " << neg_num << std::endl;

        std::cout << std::endl;
        std::cout << std::showpos;
        std::cout << "pos_num: " << pos_num << std::endl;
        std::cout << "neg_num: " << neg_num << std::endl;
        
        std::cout << std::endl;
        std::cout << std::noshowpos;
        std::cout << "pos_num: " << pos_num << std::endl;
        std::cout << "neg_num: " << neg_num << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> base_func = []() {
        int pos_int {717171};
        int neg_int {-47347};
        double double_var {498.32};

        std::cout << std::endl;
        std::cout << "default base format: " << std::endl;
        std::cout << "pos_int: " << pos_int << std::endl;
        std::cout << "neg_int: " << neg_int << std::endl;
        std::cout << "double_var: " << double_var << std::endl;
     
        std::cout << std::endl;
        std::cout << "pos_int in different bases: " << std::endl;
        std::cout << "pos_int(dec): " << std::dec << pos_int << std::endl;
        std::cout << "pos_int(hex): " << std::hex << pos_int << std::endl;
        std::cout << "pos_int(oct): " << std::oct << pos_int << std::endl;

        std::cout << std::endl;
        std::cout << "neg_int in different bases: " << std::endl;
        std::cout << "neg_int(dec): " << std::dec << neg_int << std::endl;
        std::cout << "neg_int(hex): " << std::hex << neg_int << std::endl;
        std::cout << "neg_int(oct): " << std::oct << neg_int << std::endl;

        std::cout << std::endl;
        std::cout << "double_var in different bases: " << std::endl;
        std::cout << "double_var(dec): " << std::dec << double_var << std::endl;
        std::cout << "double_var(hex): " << std::hex << double_var << std::endl;
        std::cout << "double_var(oct): " << std::oct << double_var << std::endl;

        std::cout << std::endl;
    };

    std::function<void(void)> uppercase_func = []() {
        int pos_int = 717171;
        std::cout << "pos_int = (nouppercase: default:) : " << std::endl;
        std::cout << "pos_int(dec): " << std::dec << pos_int << std::endl;
        std::cout << "pos_int(hex): " << std::hex << pos_int << std::endl;
        std::cout << "pos_int(oct): " << std::oct << pos_int << std::endl;

        std::cout << std::endl;
        std::cout << "pos_int(uppercase): " << std::endl;
        std::cout << std::uppercase;
        std::cout << "pos_int(dec): " << std::dec << pos_int << std::endl;
        std::cout << "pos_int(hex): " << std::hex << pos_int << std::endl;
        std::cout << "pos_int(oct): " << std::oct << pos_int << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> scientific_and_fixed_func = []() {
        double a { 3.1415926535897932384626433832795 };
        double b { 2006.0 };
        double c { 1.34e-10};

        std::cout << std::endl;
        std::cout << "double values (default: use scientific where necessary): " << std::endl;
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "c: " << c << std::endl;

        std::cout << std::endl;
        std::cout << "double values (fixed): " << std::endl;
        std::cout << std::fixed;
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "c: " << c << std::endl;

        std::cout << std::endl;
        std::cout << "double values (scientific): " << std::endl;
        std::cout << std::scientific;
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "c: " << c << std::endl;

        std::cout << std::endl;
        std::cout << "double values (back to defaults) : " << std::endl;
        std::cout.unsetf(std::ios::scientific | std::ios::fixed);
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "c: " << c << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> precision_func = []() {
        double a = 3.1415926535897932384626433832795;
        std::cout << "a (default precision(6)): " << a << std::endl;
        std::cout << std::setprecision(10);
        std::cout << "a (precision(10)): " << a << std::endl;
        std::cout << std::setprecision(20);
        std::cout << "a (precision(20)): " << a << std::endl;
        std::cout << std::endl;
    };

    std::function<void(void)> show_point_func = []() {
        double d {34.1};
        double e {101.99};
        double f {12.0};
        double g {45};

        std::cout << std::endl;
        std::cout << "noshowpoint (default): " << std::endl;
        std::cout << "d: " << d << std::endl;
        std::cout << "e: " << e << std::endl;
        std::cout << "f: " << f << std::endl;
        std::cout << "g: " << g << std::endl;

        std::cout << std::endl;
        std::cout << "showpoint: " << std::endl;
        std::cout << std::showpoint;
        std::cout << "d: " << d << std::endl;
        std::cout << "e: " << e << std::endl;
        std::cout << "f: " << f << std::endl;
        std::cout << "g: " << g << std::endl;
        std::cout << std::endl;
    };

    std::map<func_type, std::function<void(void)>> funcs_map {
        {ENDL, endl_func},
        {FLUSH, flush_func},
        {UNFORMATTED, unformatted_func},
        {FORMATTED, formatted_func},
        {FORMATTED_WITH_VAR, formatted_with_var_func},
        {RIGHT_JUSTIFIED, right_justified_func},
        {LEFT_JUSTIFIED, left_justified_func},
        {INTERNAL_JUSTIFIED, internal_justified_func},
        {FILLED_CHARS, filled_chars_func},
        {BOOL_VAR, bool_var_func},
        {SHOW_POS, show_pos_func},
        {BASE, base_func},
        {UPPERCASE, uppercase_func},
        {SCIENTIFIC_AND_FIXED, scientific_and_fixed_func},
        {PRECISION, precision_func},
        {SHOW_POINT, show_point_func}
    };

    void operator()(func_type const& f_type)  {
        funcs_map[f_type]();
    }
};

int main(int argc, char* argv[]) {
    cout_test test;
    test(cout_test::ENDL);
    test(cout_test::FLUSH);
    test(cout_test::UNFORMATTED);
    test(cout_test::FORMATTED); 
    test(cout_test::FORMATTED_WITH_VAR);
    test(cout_test::RIGHT_JUSTIFIED);
    test(cout_test::LEFT_JUSTIFIED);
    test(cout_test::INTERNAL_JUSTIFIED);
    test(cout_test::FILLED_CHARS);
    test(cout_test::BOOL_VAR);
    test(cout_test::SHOW_POS);
    test(cout_test::BASE);
    test(cout_test::UPPERCASE);
    test(cout_test::SCIENTIFIC_AND_FIXED);
    test(cout_test::PRECISION);
    test(cout_test::SHOW_POINT);
    return EXIT_SUCCESS;
}