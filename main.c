#include <stdio.h>
#include <stdlib.h>
#include "circlemath.h"

int main()
{
    int radius1 = 3, radius2 = 5;
    
    pid_t pid = fork();
    
    if (pid == -1)
    {
        printf("Error forking process.\n");
        return 1;
    }

    if (pid == 0)
    {   // child process
        printf("Radius: %d\n", radius1);
        printf("Area: %.2lf\n", area(radius1));
        printf("Circumference: %.2lf\n", circumference(radius1));
        
//        printf("Radius: %d\n", radius2);
  //      printf("Area: %.2lf\n", area(radius2));
    //    printf("Circumference: %.2lf\n", circumference(radius2));
    }
    else
    {
        printf("Radius: %d\n", radius2);
        printf("Area: %.2lf\n", area(radius2));
        printf("Circumference: %.2lf\n", circumference(radius2));   
    }

    return 0;
}
