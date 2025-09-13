#include <stdio.h>

int main(int argc, char* argv[]) {
    float highscore[5];
    highscore[0] = 993.86;
	highscore[1] = 682.01;
	highscore[2]= 639.60;
	highscore[3] = 310.45;
	highscore[4] = 123.25;

    int x = 0;
    puts("Here are the high scores: ");
    for(x=0; x<5; ++x) {
        printf("#%d %.2f\n", x+1, highscore[x]);
    }
    
    return 0;
}