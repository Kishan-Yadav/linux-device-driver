#include<stdio.h>
#include <fcntl.h>
#define DEVICE_NODE "/dev/file_ops_char_device"

int main() 
{
    int fd = open(DEVICE_NODE, O_RDWR);
    if(fd < 0)
    {
        printf("Can not open the device file\n");
       // exit(1);
    }
    else
    {
	printf("device-file open succesfully\n");
    }
    return 0;
}
