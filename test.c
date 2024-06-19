#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
long gettime(int type);
int main(void)
{

	while(1)
	{
		printf("time in second: %ld\n", gettime(2));
		printf("time in milisecond: %ld\n", gettime(1));
		printf("time in microsecond: %ld\n", gettime(3));
		usleep(300 * 1e3);
	}
	return (0);
}

