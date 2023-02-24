#include <stdio.h>
#include "directory_check.h"

int main() {
    char path[100];
    printf("Enter the path to check: ");
    scanf("%s", path);
    if (isDirectory(path)) {
        printf("%s is a directory\n", path);
    } else {
        printf("%s is not a directory\n", path);
    }
    return 0;
}
