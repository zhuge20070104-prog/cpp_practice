#include <iostream>
# include <string>

std::string insert_ctrl(std::string& s) {
	char buf[10000];
	char* dest = buf;
	char* end = buf + sizeof(buf) - 4;
	char const* src = s.data();
	size_t count = s.length();
	while (count > 0 && dest < end) {
		if (*src < 0x20 && dest < end) {
			*dest++ = '\\';
			*dest++ = 'x';
			*dest++ = "0123456789ABCDEF"[*src >> 4];
			*dest++ = "0123456789ABCDEF"[*src & 0xf];
			++src;
		}
		else if (dest < buf + sizeof(buf)) {
			*dest++ = *src++;
		}
		else throw std::logic_error("string too long");
		--count;
	}
	return std::move(std::string(buf, dest));
}



int main(int argc, char* argv[]) {
    // \01和\07在C语言中被看做单个数字字符
    // \01 是 ASCII 码为1的字符
    // \07 是 ASCII 码为7的字符
    std::string src("x\01test\07");
    auto res = insert_ctrl(src);
    std::cout << "result: " << res << "\n";
    return EXIT_SUCCESS;
}