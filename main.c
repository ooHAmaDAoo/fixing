#include <stdio.h>
#include <stdlib.h>
#include "circlemath.h"

int main() {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        // Child process
        int radius1 = 3;
        int radius2 = 5;
        double area1 = area(radius1);
        double circumference1 = circumference(radius1);
        double area2 = area(radius2);
        double circumference2 = circumference(radius2);
        printf("Radius: %d\nArea: %.2f\nCircumference: %.2f\n", radius1, area1, circumference1);
        printf("Radius: %d\nArea: %.2f\nCircumference: %.2f\n", radius2, area2, circumference2);
        exit(0);
    } else if (pid < 0) {
        // Error occurred
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else {
        // Parent process
        wait(NULL);
        printf("Child complete\n");
    }

    return 0;
}
