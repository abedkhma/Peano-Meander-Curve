#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//assembly functions with its args
extern void peano_meander(u_int64_t degree, u_int64_t *x, u_int64_t *y);

int main(int argc, char** argv) {
    // check whether it becomes a number when calling it
    if (argc != 2) {
        printf("For running the program, please write ./main <parameter>\n");
        printf("The parameter must be between 1 and 8 (included)\n");
        printf("Once the program is done, you will find a new file called graph.svg in the same folder.\n");
        printf("Please open the graph.svg in firefox for best experience.\n");
        printf("Extra: on linux only, running the bash file peano.sh with parameter will run the ./main and will open firefox automaticlly.");
        exit (EXIT_FAILURE);
    }
    
    
    if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
    {
        printf("For running the program, please write ./main <parameter>\n");
        printf("The parameter must be between 1 and 8 (included)\n");
        printf("Once the program is done, you will find a new file called graph.svg in the same folder.\n");
        printf("Please open the graph.svg in firefox for best experience.\n");
        printf("Extra: on linux only, running the bash file peano.sh with parameter will run the ./main and will open firefox automaticlly.");
        return 1;
    }
    // turning the number it gets from the console into int
    int n = atoi(argv[1]);
    if (n<1){
        printf("The number must be Positive and greater than 0.\n");
        return 1;
    }
    //initializing two pointers for x and y
    u_int64_t *x,*y;
    int base = 3;
    double squares = pow(base,(2*n));;
    x =  malloc((squares) * sizeof(u_int64_t));
    y =  malloc((squares) * sizeof(u_int64_t)); 
   

   // -----------------------Start-Zeitmessung-Assember---------------------------------------
    struct timespec startAs;
    struct timespec endAs;

    if(clock_gettime(CLOCK_MONOTONIC, &startAs)){
    printf("ERROR: start time");
    return 1;
    }

    	peano_meander(n,x,y);

    if(clock_gettime(CLOCK_MONOTONIC, &endAs)){
        printf("ERROR: end time");
        return 1;
    }
    
    printf("im here");
    double timeAs = endAs.tv_sec - startAs.tv_sec + 1e-9 *
        (endAs.tv_nsec - startAs.tv_nsec);
    
    printf("the time for assembly part is : %f \n", timeAs);
    // -----------------------End-Zeitmessung-Assember---------------------------------------   


    // -----------------------Start-Zeitmessung-SVG---------------------------------------
    struct timespec startSVG;
    struct timespec endSVG;

    if(clock_gettime(CLOCK_MONOTONIC, &startSVG)){
    printf("ERROR: start time");
    return 1;
    }

    FILE *file = fopen("graph.svg", "w");
    if (file == NULL)
    {
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

    if(clock_gettime(CLOCK_MONOTONIC, &endSVG)){
        printf("ERROR: end time");
        return 1;
    }
    

    double timeSVG = endSVG.tv_sec - startSVG.tv_sec + 1e-9 *
    (endSVG.tv_nsec - startSVG.tv_nsec);
    
    printf("the time for SVG part is : %f \n", timeSVG);
    // -----------------------End-Zeitmessung-SVG---------------------------------------   
    
  
    free(x);
    free(y); 
    return 0;
}
 
