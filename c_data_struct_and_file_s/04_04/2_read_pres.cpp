#include <cstdio>

int main(int argc, char* argv[]) {
    char const* file_name = "presidents.dat";

    struct person
	{
		char name[32];
		int inaguration;
		int age;
	} president;

    int x;
    FILE* fp;

    fp = fopen(file_name, "r");
    if(fp == nullptr) {
        printf("Unable to open %s\n", file_name);
        return -1;
    }

    printf("Enter record to read(1-10):");
    scanf("%d", &x);

    if(x < 1 || x > 10) {
        puts("Invalid input");
        return -1;
    }

    --x;

    fseek(fp, sizeof(person) * x, SEEK_SET);
    fread(&president, sizeof(person), 1, fp);

    printf("President %s was %d years old when inaugurated in %d\n",
        president.name, president.age, president.inaguration);

    return 0;
}
