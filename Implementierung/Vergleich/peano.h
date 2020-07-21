    
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




void peano_meander(u_int64_t degree, u_int64_t *x, u_int64_t *y)
{
    long i=0; //r11
    u_int64_t val; //112
    int n; //r13
    int numOfPoints = pow(3,(2*degree));
    for (u_int64_t c= 0; c <numOfPoints; c++) {
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
