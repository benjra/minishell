#include "../parsing/mini.h"
#include <unistd.h>
#include <stdlib.h>

int ft_cd(const char *pathname)
{
    char oldpwd[1024];
    char *cwd;

    // Get the current working directory and store it in oldpwd
    if (getcwd(oldpwd, sizeof(oldpwd)) == NULL) {
        perror("getcwd");
        return (1);
    }

    // Change the current working directory
    if (chdir(pathname) != 0) {
        perror("chdir");
        return (1);
    }

    // Update OLDPWD with the old working directory
    if (setenv("OLDPWD", oldpwd, 1) != 0) {
        perror("setenv OLDPWD");
        return (1);
    }

    // Get the new current working directory
    cwd = getcwd(NULL, 0); // Dynamically allocate enough space
    if (cwd == NULL) {
        perror("getcwd");
        return (1);
    }

    // Update PWD with the new working directory
    if (setenv("PWD", cwd, 1) != 0) {
        perror("setenv PWD");
        free(cwd); // Free dynamically allocated memory
        return (1);
    }

    printf("Directory changed to %s\n", pathname);
    free(cwd); // Free dynamically allocated memory
    return (0);
}