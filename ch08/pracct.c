#include "apue.h"
#include <sys/acct.h>

#define acct acctv2
#define ac_flag ac_trailer.ac_flag
#define FMT "%-*.*s e = %.0f, chars = %.0f, %c %c %c %c\n"

int main(int argc, char* argv[])
{
	struct acct acdata;
	FILE *fp;
	
	if (argc != 2)
		err_quit("usage: acct filename");
	if ((fp = fopen(argv[1], "r")) == NULL)
		err_sys("can't open %s", argv[1]);
	while (fread(&acdata, sizeof(acdata), 1, fp) == 1) {
		printf(FMT, (int)sizeof(acdata.ac_comm), (int)sizeof(acdata.ac_comm), acdata.ac_comm,
					acdata.ac_etime, acdata.ac_io,
					acdata.ac_flag & ACORE ? 'D' : ' ',
					acdata.ac_flag & AXSIG ? 'X' : ' ',
					acdata.ac_flag & AFORK ? 'F' : ' ',
					acdata.ac_flag & ASU   ? 'S' : ' ');
	}
	if (ferror(fp))
		err_sys("read error");
	exit(0);
}
