#include <cstdio>

struct pixel {
    int horz;
    int vert;
    char color;
} center;

void show_pixel(struct pixel* p) {
    printf("pixel found at %d,%d, color = ",
        p->horz,
        p->vert);
    
    switch (p->color) {
    case 'r':
        puts("red");
        break;
    case 'g':
        puts("green");
        break;
    case 'b':
        puts("blue");
    default:
        puts("invalid");
        break;
    }
}

int main(int argc, char* argv[]) {
    center.horz = 320;
    center.vert = 240;
    center.color = 'r';
    show_pixel(&center);
    return 0;
}