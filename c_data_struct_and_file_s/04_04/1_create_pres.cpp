#include <cstdio>

int main(int argc, char* argv[]) {
    char const* file_name = "presidents.dat";

    FILE* fp;
    struct person {
        char name[32];
        int inaguration;
        int age;
    } presidents[10] = {
        {"George Washington", 1789, 57},
		{"John Adams", 1797, 62},
		{"Thomas Jefferson", 1801, 58},
		{"James Madison", 1809, 58},
		{"James Monroe", 1817, 59},
		{"John Quincy Adams", 1825, 58},
		{"Andrew Jackson", 1829, 62},
		{"Martin Van Buren", 1837, 55},
		{"William Henry Harrison", 1841, 68},
		{"John Tyler", 1841, 51}
    };


    fp = fopen(file_name, "w");
    if(fp == nullptr) {
        printf("Unable to create %s\n", file_name);
        return -1;
    }

    fwrite(presidents, sizeof(person), 10, fp);
    fclose(fp);
    
    return 0;
}