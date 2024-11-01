#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    int fd;

    fd = open("../test.txt", O_RDWR);
    write(3, "hola", 4);
    return (0);
}