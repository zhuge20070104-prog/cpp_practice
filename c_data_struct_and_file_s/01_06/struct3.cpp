#include <stdio.h>


struct pixel {
    int horz;
    int vert;
    char color;
} top, center, bottom;


void print_pixel(struct pixel* p) {
    printf("The pixel at %d,%d is colored ",
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
        break;
    default:
        puts("invalid");
        break;
    }
}

int main(int argc, char* argv[]) {
    struct pixel* pixels[] = {&top, &center, &bottom};
    top.horz = 320;
    top.vert = 0;
    top.color = 'r';

    center.horz = 320;
    center.vert = 240;
    center.color = 'g';

    bottom.horz = 320;
    bottom.vert = 480;
    bottom.color = 'b';

    for(int i=0; i<3; ++i) {
        print_pixel(pixels[i]);
    } 

    return 0;
}