#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int width = 6561;
int counter = 0;

void meander(int x, int y, int w, int i1, int i2,u_int64_t *xp,u_int64_t *xy);


int main(int argc, char** argv) {

    if (argc != 2) {
        printf("add number please\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (n<1){
        printf("The number must be Positive and greater than 0.\n");
        return 1;
    }

    u_int64_t *x,*y;

    int base = 3;
    double squares = pow(base,(2*n));;

    x =  malloc((squares) * sizeof(u_int64_t));
    y =  malloc((squares) * sizeof(u_int64_t));

    // -----------------------Start-Zeitmessung----------------------------------------
    struct timespec start;
    struct timespec end;

    if(clock_gettime(CLOCK_MONOTONIC, &start)){
    printf("ERROR: start time");
    return 1;
    }
    
    meander(0,0,width,0,0,x,y);

    if(clock_gettime(CLOCK_MONOTONIC, &end)){
        printf("ERROR: end time");
        return 1;
    }

    double time = end.tv_sec - start.tv_sec + 1e-9 *
    (end.tv_nsec - start.tv_nsec);
    
    printf("the time is: %f \n", time);
    // -----------------------End-Zeitmessung----------------------------------------
    
    
    for (int i=0;i<81;i++){
        //printf("%d:(%ld,%ld)\n",i++,x[i],y[i]);
    }

    free(x);
    free(y); 
}

void meander(int x, int y, int w, int i1, int i2,u_int64_t *xp,u_int64_t *xy){

     if (w == 1){
        u_int64_t xx = (width - x-1) ;
        u_int64_t yy = (width - y-1);
        xp[counter] =xx;
        xy[counter] =yy;
        counter++;
        return;
    }

    w = w / 3;
    meander(x+2*i1*w,y+2*i1*w, w, i1, i2,xp,xy);
    meander(x+(i1-i2+1)*w, y+(i1+i2)*w, w, i1, 1-i2,xp,xy);
    meander(x+w, y+w, w, i1, 1-i2,xp,xy);
    meander(x+(i1+i2)*w, y+(i1-i2+1)*w, w, 1-i1, 1-i2,xp,xy);
    meander(x+2*i2*w, y+2*(1-i2)*w, w, i1, i2,xp,xy);
    meander(x+(1+i2-i1)*w, y+(2-i1-i2)*w, w, i1, i2,xp,xy);
    meander(x+2*(1-i1)*w, y+2*(1-i1)*w, w, i1, i2,xp,xy);
    meander(x+(2-i1-i2)*w, y+(1+i2-i1)*w, w, 1-i1, i2,xp,xy);
    meander(x+2*(1-i2)*w, y+2*i2*w, w, 1-i1, i2,xp,xy);
}
