#include <stdio.h>
main(){
	FILE *fp;
	fp = fopen("/home/dnc28/test.txt","w+");
	fprintf(fp, "This is testing for fprintf...\n");
	fputs("This is testing for fputs...\n", fp);
	fclose(fp);
}
