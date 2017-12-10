#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MY_ID "abcdefg1234"




int main(int argc, char** argv)
{
	int fd = open("/dev/eudyptula/hello", O_RDWR);

	char my_name[sizeof(MY_ID)];
	if(read(fd, my_name, sizeof(MY_ID)) < 0)
		write(2, "Failed test 1\n", 31);

	printf("Actual string: %s\n", my_name);
	if(strncmp(MY_ID, my_name, sizeof(MY_ID)) < 0)
		write(2, "Failed test 2\n", 31);

	if(write(fd, MY_ID, sizeof(MY_ID)) < 0)
		write(2, "Failed test 3\n", 31);
	if(write(fd, "wrongid", 3) > 0)
		write(2, "Failed test 4\n", 31);

	return 0;
}
