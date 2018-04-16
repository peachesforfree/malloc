
#include "ft_script.h"

int main(void)
{
    int i;

    i = 0;
    printf("getpid(%d)\n", getpid());
    printf("getppid(%d)\n", getppid());
    fork();
    while (1)
        i++;
    return(0);
}