#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"svg.h"

//assembly functions with its args
extern void peano_meander(u_int64_t degree, u_int64_t *x, u_int64_t *y);

int main(int argc, char** argv) {
    // check whether it becomes a number when calling it
    if (argc != 2) {
        printf("add number please\n");
        return 1;
    }
    //initializing two pointers
    u_int64_t *x,*y;
    // turning the number it gets from the console into int
    int n = atoi(argv[1]);
    int base = 3;
    double squares = pow(base,(2*n));;
    x =  malloc((squares) * sizeof(u_int64_t));
    y =  malloc((squares) * sizeof(u_int64_t)); 
    peano_meander(n,x,y);
    // printing the values of the pointer
    //789 -> 3
    printf("x=["); 
    for (int i = 0;i<squares;i++)
    {
        printf("%ld,", x[i]);        
    }
    printf("]");
    printf("\n");
    printf("y=[");
    for (int i = 0;i<squares;i++)
    {
        printf("%ld,", y[i]);        
    }
    printf("]");
    free(x);
    free(y);
    return 0;
}
 