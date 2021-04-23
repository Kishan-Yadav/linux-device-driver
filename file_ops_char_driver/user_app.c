#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
int main() {
    char read_data[100];
    int fd = open("/dev/file_ops_char_device", O_RDWR);
    write(fd, "hi kishan how are you ?", strlen("hi kishan how are you ?"));
    ssize_t size = read(fd, read_data, 20);
    printf("Read data from kernel =  %s\n", read_data);
    return 0;
}
