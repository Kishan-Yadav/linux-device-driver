#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
#define FILL 1
#define CONSUME 2
#define EXIT 3
int main() 
{
	char read_data[100];
	int choice;
	ssize_t size;
	int fd = open("/dev/wq_dynamic_device", O_RDWR);
	while(1)
	{
		printf("\nwhat opertion you want to perform\n1.Fill the data\n2.Consume the data\n3.Close the user-app\nEnter the choice\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case FILL:
				write(fd, "hi kishan, please fill the data...", strlen("hi kishan, please fill the data..."));
				break;
			case CONSUME:
				size = read(fd, read_data, 50);
				printf("Read data from kernel =  %s\n", read_data);
				break;
			case EXIT:
				goto exit;
				break;
			default:
				printf("Invalid Inputs\n");
				break;
		}

	}
	exit:
	close(fd);
	return 0;
}
