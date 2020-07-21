
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


int xbase[9]={0,0,0,1,2,2,1,1,2};
int ybase[9]={0,1,2,2,2,1,1,0,0};

void peano_meander(u_int64_t degree, u_int64_t *x, u_int64_t *y);
u_int64_t findPoint(long i,u_int64_t degree,u_int64_t *x, u_int64_t *y);



int main(int argc, char** argv) {

    //--------------------------Start-Checking-Right-Input-----------------------------
    // check whether it becomes a number when calling it
    if (argc != 2) {
        printf("For running the program, please write ./cimp <parameter>\n");
        printf("The parameter must be between 1 and 8 (included)\n");
        printf("Once the program is done, you will find a new file called graph.svg in the same folder.\n");
        printf("Please open the graph.svg in firefox for best experience .\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
    {
        printf("For running the program, please write ./cimp <parameter>\n");
        printf("The parameter must be between 1 and 8 (included)\n");
        printf("Once the program is done, you will find a new file called graph.svg in the same folder.\n");
        printf("Please open the graph.svg in firefox for best experience.\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if (n<1 || n>8){
        printf("The parameter must be between 1 and 8 (included)\n");
        return 1;
    }
    //--------------------------End-Checking-for-Right-Input-----------------------------


    //---------------------------Start-Main-Part-------------------------------------
    //initializing two pointers
    u_int64_t *x,*y;
    // turning the number it gets from the console into int
    int base = 3;
    double squares = pow(base,(2*n));;
    x =  malloc((squares) * sizeof(u_int64_t));
    y =  malloc((squares) * sizeof(u_int64_t)); 

    peano_meander(n,x,y);
    for(int j=0;j<9;j++){
        printf("%ld",x[j]);
    }
    //------------------------------End-Main-Part-------------------------------------


    //------------------------------Start-SVG-------------------------------------------
    FILE *file = fopen("graph.svg", "w");
    if (file == NULL){
    printf("Error\n");
    exit(1);
    }
    double sqrtpoints = sqrt(squares) - 1; // number of points on each axis
    fprintf(file,"<svg viewBox=\"800 -1000 1100 1100\" xmlns=\"http://www.w3.org/2000/svg\">");
    u_int64_t tempx1,tempy1,tempx2,tempy2;
    for (int i = 0;i<squares-1;i++)
    {
    
    tempx1 = x[i]*(900/sqrtpoints) * -1;
    tempy1 =y[i]*(900/sqrtpoints) * -1;
    tempx2 =x[i+1]*(900/sqrtpoints) * -1;
    tempy2 = y[i+1]*(900/sqrtpoints) * -1;
    fprintf(file, "<line x1=\"%ld\" y1=\"%ld\" x2=\"%ld\" y2=\"%ld\" stroke=\"black\" transform=\"scale (-1, 1)\" transform-origin=\"center\" />\n",tempx1,tempy1,tempx2,tempy2);
    }

    fprintf(file,"</svg>");
    fclose(file);
    //------------------------------End-SVG-------------------------------------------

    free(x);
    free(y); 
    return 0;
}
 

void peano_meander(u_int64_t degree, u_int64_t *x, u_int64_t *y)
{
    long counter = 0; //r10
    long i=0; //r11
    int val; //112
    int n; //r13
    int wanted;
    int numOfPoints = pow(3,(2*degree));
    for (long c= -1; c <numOfPoints-1; c++) {
        val = i;
        n = 0;
        while ((val & 0x8) > 0) { 
            n = n + 1; 
            val = val >> 4; 
        }
        if (n == 0)
        {
            findPoint(i,degree,x,y);
            x++;
            y++;
            i = i + 1;
            continue;
        }
        findPoint(i,degree,x,y);
        x++;
        y++;
        i = ((i >> (4 * n)) + 1) << (4 * n);
    }

}

u_int64_t findPoint(long i,u_int64_t degree,u_int64_t *x, u_int64_t *y){
    long index = i & 15;
    u_int64_t xtemp=xbase[index];
    u_int64_t ytemp=ybase[index];
    for (int j = 1; j < degree; j++) {
    i = i >> 4;
    index = i & 15;
    u_int64_t temp;
    int len = (int)pow(3,j);
    switch ((int)index){
        case 0:
            temp = ytemp;
            ytemp=xtemp;
            xtemp=temp;
            break;
        case 1:
            temp = ytemp;
            ytemp=xtemp + len;
            xtemp=temp;
            break;
        case 2:
            ytemp=ytemp+(len*2);
            break;
        case 3:
            xtemp=xtemp+len;
            ytemp=ytemp+(2*len);
            break;
        case 4:
            xtemp=xtemp+(len*2);
            ytemp=ytemp+(len*2);
            break;
        case 5:
            xtemp=(len-1)-xtemp+(len*2);
            ytemp=(len-1)-ytemp+(len);
            break;
        case 6:;
            temp = ytemp;
            ytemp=(len-1)-xtemp+len;
            xtemp=(len-1)-temp+len;
            break;
        case 7:
            temp = ytemp;
            ytemp=(len-1)-xtemp;
            xtemp=(len-1)-temp+len;
            break;
        case 8:
            xtemp=xtemp+(2*len);
            break;
        }
        *x=xtemp;
        *y=ytemp;
    }


}