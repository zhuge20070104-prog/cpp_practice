#include <iostream>
#include <functional>

namespace func {

enum FUNCS {
    READ_2D_ARRAY,
    STD_SIZE_2D_ARRAY,
    READ_3D_ARRAY,
    OMMIT_LEFTMOST_DIMENSION,
    OMMIT_LEFTMOST_DIMENSION_3D,
    _3D_ARRAY_WITH_ZEROS,
    MODIFY_DATA_IN_3D_ARRAY
};

auto read_2d_array = []() {
    int packages [][4] {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {3,4,5,6}
    };

    for(std::size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            std::cout << packages[i][j] << "  ";
        }
        std::cout << std::endl;
    }
};

auto std_size_2d_array = []() {
    int packages [][4] {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {3,4,5,6}
    };

    for(std::size_t i = 0; i < std::size(packages); ++i) {
        for (size_t j = 0; j < std::size(packages[i]); ++j) {
            std::cout << packages[i][j] << "  ";
        }
        std::cout << std::endl;
    }
};

auto read_3d_array = []() {
    int house_block [7] [5] [3] {
        {
            {1,2,3},{4,5,6},{7,8,9},{10,11,12},{13,14,15} 
        },
        {
            {16,17,18},{19,20,21},{22,23,24},{25,26,27},{28,29,30}  
        },
        {
            { 31,32,33},{34,35,36},{37,38,39},{40,41,42},{43,44,45} 
        },
        {
             {46,47,48},{49,50,51},{52,53,54},{55,56,57},{58,59,60}  
        },
        {
             {61,62,63},{64,65,66},{67,68,69},{70,71,72},{73,74,75} 
        },
        {
            {76,77,78},{79,80,81},{82,83,84},{85,86,87},{88,89,90}  
        },
        {
             {91,92,93},{94,95,96},{97,98,99},{100,101,102},{103,104,105} 
        }
    };

    for(int i=0; i<std::size(house_block); ++i) {
        for(int j=0; j<std::size(house_block[i]); ++j) {
            for(int k=0; k<std::size(house_block[i][j]); ++k) {
                std::cout << house_block[i][j][k] << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

auto ommit_leftmost_dimension = []() {
    int packages2[][5] = {
        {1,2,3},
        {4,5,6},
        {7,8,9},
        {10,11,12},
		{100,110,120} 
    };

    std::cout << std::endl;

    std::cout << "Ommitting leftmost dimension for 2d array: " << std::endl;
    for(std::size_t i=0; i<std::size(packages2); ++i) {
        for(std::size_t j=0; j<std::size(packages2[i]); ++j) {
            std::cout << "Item(" << i << ", " << j << "): " << packages2[i][j] << std::endl;
        }
    }
};

auto ommit_leftmost_dimension_3d = []() {
    //For 3d and really any multi dimensional array , you have to specify
	//the number of elements in []'s , only the left most is not mandatory.
	//Below is the example for 3D reproduced.Omitting the 5 or the 3 or both
	//will cause a compile error.
    int house_block1 [] [5] [3] {
        
        {
            {1,2,3},{4,5,6},{7,8,9},{10,11,12},{13,14,15} 
        },
        {
            {16,17,18},{19,20,21},{22,23,24},{25,26,27},{28,29,30}  
        },
        {
            { 31,32,33},{34,35,36},{37,38,39},{40,41,42},{43,44,45} 
        },
        {
             {46,47,48},{49,50,51},{52,53,54},{55,56,57},{58,59,60}  
        }
    };

    for(int i=0; i<std::size(house_block1); ++i) {
        for(int j=0; j<std::size(house_block1[i]); ++j) {
            std::cout << "[";
            for(int k=0; k<std::size(house_block1[i][j]); ++k) {
                std::cout << house_block1[i][j][k] << " ";    
            }
            std::cout << "]";
        }
        std::cout << std::endl;
    }
};

auto _3d_array_with_zeros = []() {
    //If you put less elements than the amount specified in the declaration, the compiler
    //will automaticaly fill out those left out with 0 or '\0' is the array is of char.
    // Change the array to int house_block [] [5] [4], and because all inner arrays have 3,
    // elements, the fourth will be autofilled with 0.
    // Also remove some other elements, I chose the {4,5,6} array but you can add others 
    // when recording to make this a bit fun. The left out indexes will be auto filled with 
    // zeros
    int house_block2 [] [5] [4] { 	// Try to make the last dimension 5 and show
									//that the compiler appends 2 zeros
        {
            {1,2,3},{4},{7,8,9},{10,11,12},{13,14,15}  //The one element array will be autofilled
													// with zeros to complete 4 elements
        },
        {
            {16,17,18},{19,20,21},{22,23,24},{25,26,27},{28,29,30}  
        },
        {
            { 31,32,33},{34,35,36},{37,38,39},{40,41,42},{43,44,45} 
        },
        {
             {46,47,48},{49,50,51},{52,53,54},{55,56,57}//,{58,59,60}  // The spots for {58,59,60
																	   // Will be autofilled with 0
        }  
    };

    for(int i=0; i<std::size(house_block2); ++i) {
        for(int j=0; j<std::size(house_block2[i]); ++j) {
            std::cout << "[";
            for(int k=0; k<std::size(house_block2[i][j]); ++k) {
                std::cout << house_block2[i][j][k] << " ";    
            }
            std::cout << "]";
        }
        std::cout << std::endl;
    }
};

auto modify_data_in_3d_array = []() {
    int house_block2 [] [5] [4] { 	// Try to make the last dimension 5 and show
									//that the compiler appends 2 zeros
        {
            {1,2,3},{4},{7,8,9},{10,11,12},{13,14,15}  //The one element array will be autofilled
													// with zeros to complete 4 elements
        },
        {
            {16,17,18},{19,20,21},{22,23,24},{25,26,27},{28,29,30}  
        },
        {
            { 31,32,33},{34,35,36},{37,38,39},{40,41,42},{43,44,45} 
        },
        {
             {46,47,48},{49,50,51},{52,53,54},{55,56,57}//,{58,59,60}  // The spots for {58,59,60
																	   // Will be autofilled with 0
        }  
    };

    house_block2[0][2][1] = 1021;

    for(int i=0; i<std::size(house_block2); ++i) {
        for(int j=0; j<std::size(house_block2[i]); ++j) {
            std::cout << "[";
            for(int k=0; k<std::size(house_block2[i][j]); ++k) {
                std::cout << house_block2[i][j][k] << " ";    
            }
            std::cout << "]";
        }
        std::cout << std::endl;
    }
};

std::function<void(void)> function_maker(FUNCS func_) {
    std::function<void(void)> ret_func = [](){
        std::cout << "No matched function!" << std::endl;
    };

    switch(func_) {
    
    case READ_2D_ARRAY:
        ret_func = read_2d_array;   
    break;
    case STD_SIZE_2D_ARRAY:
        ret_func = std_size_2d_array;
    break;
    case READ_3D_ARRAY:
        ret_func = read_3d_array;
    break;
    case OMMIT_LEFTMOST_DIMENSION:
        ret_func = ommit_leftmost_dimension;
    break;
    case OMMIT_LEFTMOST_DIMENSION_3D:
        ret_func = ommit_leftmost_dimension_3d;
    break;
    case _3D_ARRAY_WITH_ZEROS:
        ret_func = _3d_array_with_zeros;
    break;
    case MODIFY_DATA_IN_3D_ARRAY:
        ret_func = modify_data_in_3d_array;
    break;

    }
    return ret_func;
}

}


int main(int argc, char* argv[]) {
    auto read_2d_array = func::function_maker(func::READ_2D_ARRAY);
    read_2d_array();

    auto std_size_2d_array = func::function_maker(func::STD_SIZE_2D_ARRAY);
    std_size_2d_array();

    auto read_3d_array = func::function_maker(func::READ_3D_ARRAY);
    read_3d_array();

    auto ommit_left_most_dimen = func::function_maker(func::OMMIT_LEFTMOST_DIMENSION);
    ommit_left_most_dimen();

    auto ommit_left_most_dimen_3d = func::function_maker(func::OMMIT_LEFTMOST_DIMENSION_3D);
    ommit_left_most_dimen_3d();

    auto _3d_array_with_zeros = func::function_maker(func::_3D_ARRAY_WITH_ZEROS);
    _3d_array_with_zeros();
    
    auto modify_data_in_3d_array = func::function_maker(func::MODIFY_DATA_IN_3D_ARRAY);
    modify_data_in_3d_array();
    return EXIT_SUCCESS;
}