#include <iostream>
#include <sstream>

#include "point.h"
#include "consts.h"
#include <vector>
#include <boost/algorithm/string.hpp>

#define WITHOUT_NUMPY
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

enum ps_type_t {
    TWO_VERTICALS,
    TWO_VERTICALS_STEPPED,
    VERTICAL_AND_HORIZONTAL,
    MULTI_VERTICALS_STEPPED
};

struct parking_lot_maker_t {
    std::vector<parking_lot_t> two_verticals() {
        std::vector<parking_lot_t> results;
        point_t p0 {4, -2.2};
        point_t p1 {4, -2.2 - 5.5};
        point_t p2 {4 + 2.4, -2.2 - 5.5};
        point_t p3 {4 + 2.4, -2.2};
        parking_lot_t vert {p0, p1, p2, p3};

        point_t h_p0 {p3.x + 0.3 + 5.5, p3.y};
        point_t h_p1 {p3.x + 0.3, p3.y};
        point_t h_p2 {h_p1.x, h_p1.y - 2.4};
        point_t h_p3 {h_p2.x + 5.5, h_p2.y};

        parking_lot_t hori {h_p0, h_p1, h_p2, h_p3};
        results.push_back(vert);
        results.push_back(hori);
        return results;
    }
    
    std::vector<parking_lot_t> two_verticals_stepped() {
        std::vector<parking_lot_t> results;
        point_t p0 {4, -2.2};
        point_t p1 {4, -2.2 - 5.5};
        point_t p2 {4 + 2.4, -2.2 - 5.5};
        point_t p3 {4 + 2.4, -2.2};
        parking_lot_t vert {p0, p1, p2, p3};

        point_t h_p0 {p3.x + 0.3 + 5.5, p3.y+0.4};
        point_t h_p1 {p3.x + 0.3, h_p0.y};
        point_t h_p2 {h_p1.x, h_p1.y - 2.4 + 0.4};
        point_t h_p3 {h_p2.x + 5.5, h_p2.y};

        parking_lot_t hori {h_p0, h_p1, h_p2, h_p3};
        results.push_back(vert);
        results.push_back(hori);
        return results;
    }

    std::vector<parking_lot_t> vertical_and_horizontal() {
        std::vector<parking_lot_t> results;
        point_t p0 {4, -2.2};
        point_t p1 {4, -2.2 - 5.5};
        point_t p2 {4 + 2.4, -2.2 - 5.5};
        point_t p3 {4 + 2.4, -2.2};
        parking_lot_t vert {p0, p1, p2, p3};

        point_t v_p0 {p3.x + 0.3, p3.y};
        point_t v_p1 {v_p0.x, v_p0.y - 2.4};
        point_t v_p2 {v_p1.x + 5.5, v_p1.y};
        point_t v_p3 {v_p2.x, v_p2.y + 2.4};

        parking_lot_t vert1 {v_p0, v_p1, v_p2, v_p3};
        results.push_back(vert);
        results.push_back(vert1);
        return results;
    }
    
    std::vector<parking_lot_t> multi_verticals_stepped() {
        std::vector<parking_lot_t> results;
        point_t p0 {4, -2.2};
        point_t p1 {4, -2.2 - 5.5};
        point_t p2 {4 + 2.4, -2.2 - 5.5};
        point_t p3 {4 + 2.4, -2.2};
        parking_lot_t vert {p0, p1, p2, p3};
        results.push_back(vert);
        for(std::size_t i=1; i<=3; ++i) {
            parking_lot_t vert1 {{p0.x + i*(0.3 + 2.4), p0.y + i* 0.4}, {p1.x + i*(0.3 + 2.4), p1.y + i* 0.4},
                {p2.x +i*(0.3 + 2.4), p2.y + i * 0.4}, {p3.x + i*(0.3 + 2.4), p3.y + i* 0.4}};
            results.push_back(vert1);
        }
        return results;
    }

    void print_a_plot(parking_lot_t const& ps) {
        std::string replaced_0_str = boost::algorithm::replace_all_copy(PointTemp, "{0}", "0");
        boost::algorithm::replace_all(replaced_0_str, "{1}", std::to_string(ps.p0.x));
        boost::algorithm::replace_all(replaced_0_str, "{2}", std::to_string(ps.p0.y));

        std::string replaced_1_str = boost::algorithm::replace_all_copy(PointTemp, "{0}", "1");
        boost::algorithm::replace_all(replaced_1_str, "{1}", std::to_string(ps.p1.x));
        boost::algorithm::replace_all(replaced_1_str, "{2}", std::to_string(ps.p1.y));
        
        std::string replaced_2_str = boost::algorithm::replace_all_copy(PointTemp, "{0}", "2");
        boost::algorithm::replace_all(replaced_2_str, "{1}", std::to_string(ps.p2.x));
        boost::algorithm::replace_all(replaced_2_str, "{2}", std::to_string(ps.p2.y));
            
        std::string replaced_3_str = boost::algorithm::replace_all_copy(PointTemp, "{0}", "3");
        boost::algorithm::replace_all(replaced_3_str, "{1}", std::to_string(ps.p3.x));
        boost::algorithm::replace_all(replaced_3_str, "{2}", std::to_string(ps.p3.y));
        std::cout << replaced_0_str << replaced_1_str << replaced_2_str << replaced_3_str << std::endl;
    }

    void plot_and_save_plot_file(parking_lot_t const& ps) {
        std::vector<float> x_values;
        std::vector<float> y_values;
        x_values.push_back(ps.p0.x); x_values.push_back(ps.p1.x);
        x_values.push_back(ps.p2.x); x_values.push_back(ps.p3.x);

        y_values.push_back(ps.p0.y); y_values.push_back(ps.p1.y);
        y_values.push_back(ps.p2.y); y_values.push_back(ps.p3.y);
        plt::scatter(x_values, y_values, 50.0);
    }
    
    void save_results(std::string const& title, std::vector<parking_lot_t> const& results) {
        plt::clf();
        std::cout << title << "========" << std::endl;
        for(auto const& ps: results) {
           print_a_plot(ps);
           plot_and_save_plot_file(ps);
        }

        std::stringstream result_ss;
        result_ss << title << ".png";
        plt::save(result_ss.str());
        std::cout << title << "========" << std::endl;
        std::cout << std::endl;
    } 

    void operator()(ps_type_t type_) {
        switch (type_) {
        case TWO_VERTICALS:{
            auto res = two_verticals();
            save_results("Two verticals", res);
        }
            break;
        case TWO_VERTICALS_STEPPED:{
            auto res = two_verticals_stepped();
            save_results("Two verticals stepped", res);
        }
            break;

        case VERTICAL_AND_HORIZONTAL: {
            auto res = vertical_and_horizontal();
            save_results("Vertical and horizontal", res);
        }
            break;
        case MULTI_VERTICALS_STEPPED: {
            auto res = multi_verticals_stepped();
            save_results("Multi verticals stepped", res);
        }
        
        default:
            break;
        }
    }
};


int main(int argc, char* argv[]) {
    parking_lot_maker_t p_lot_maker;
    p_lot_maker(ps_type_t::TWO_VERTICALS);
    p_lot_maker(ps_type_t::TWO_VERTICALS_STEPPED);
    p_lot_maker(ps_type_t::VERTICAL_AND_HORIZONTAL);
    p_lot_maker(ps_type_t::MULTI_VERTICALS_STEPPED);

    return EXIT_SUCCESS;
}