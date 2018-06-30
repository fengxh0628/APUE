#include <unistd.h>
#include <stdio.h>

int main()
{
#ifdef _POSIX_V7_ILP32_OFF32
	printf("int, long, pointer and off_t are of 32 bits\n");
#elif defined(_SC_V7_ILP32_OFF32)
	if (sysconf(_SC_V7_ILP32_OFF32) > 0)
		printf("int, long, pointer and off_t are of 32 bits\n");
#else
	printf("no symbol for _SC_V7_ILP_OFF32\n");
#endif


}
