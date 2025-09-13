#include <iostream>
#include <vector>
#include <bitset>

static inline unsigned part_size(unsigned& whole, unsigned& parts) {
	unsigned part_size = whole / parts;
	whole -= part_size;
	parts -= 1;
	return part_size;
}

// 动态分块
void divide_into_parts(unsigned whole, unsigned parts) {
	if (parts == 0) return;
	std::cout << whole << " divided into " << parts << " parts has part sizes ";
	do {
		std::cout << part_size(whole, parts) << " ";
	} while (parts > 0);
	std::cout << std::endl;
}

// msb_iterative TODO:
// n in range 0..0x7fffffff
static inline unsigned msb_iterative(unsigned x)
{
	unsigned n=0x10000000;
	if (x == 0) return 1;
	while (x < n) 
	{
		n >>= 1;
	}
	return n;
}

static inline unsigned msb_closed(unsigned x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return(x & ~(x >> 1));
}

inline bool is_power_2_iterative(unsigned n) {
	for (unsigned one_bits = 0; n != 0; n >>= 1)
		if ((n & 1) == 1)
			if (one_bits != 0)
				return false;
			else 
				one_bits += 1;
	return true;
}


int main(int argc, char* argv[]) {

    // divide_into_parts(10,3);
    // divide_into_parts(17,6);

    // unsigned x = 0x444;
    // std::cout << "x " << std::bitset<16>((short)x) 
    //             << ", msb_iterative(x) " << std::bitset<16>((short)msb_iterative(x)) << "\n"
    //             << ", msb_closed(x) " << std::bitset<16>((short)msb_closed(x)) << std::endl;

    // bool rc = true;
    // unsigned iterations = 1000000 * 1;
    // {	
    //     for (unsigned i = 1; i < iterations; ++i)
    //         rc &= (msb_iterative(i) <= iterations);
    // }
    // {
    //     for (unsigned i = 1; i < iterations; ++i) {
    //         auto val = msb_closed(i); 
    //         rc &= (val <= iterations);
    //         std::cout << "i: " << i << " val: " << val << "\n";
    //     }      
    // }


    bool rc = is_power_2_iterative(16);
    std::cout << std::boolalpha << "16: " << rc << "\n"; 

    rc = is_power_2_iterative(15);
    std::cout << std::boolalpha << "15: " << rc << "\n"; 
    
    return EXIT_SUCCESS;
}