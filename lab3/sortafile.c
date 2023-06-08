/** Author: Bruce C. Molay, edited by Scott Burgess
 ** ------------------------------------------------------------
	A program that uses close, open, fork, and exec to redirect
	the input of sort to a file
	
 ** ------------------------------------------------------------
 **
 **
 *   sortfromfile.c
 *   This program redirects stdin from a file and then runs the
 *   sort tool.  
 *
 *   idea: fork, then in the child, redirect input, then exec

 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<unistd.h>

#define	DFLMODE	0644

#define oops(s,x) { perror(s); exit(x); }

int main(int argc, char *argv[])
{
	pid_t	pid ;
	char	*file;

	/*  did user provide input file?   check here   */
	if ( argc == 1 ){ 
		fprintf(stderr,"usage: sortfromfile filename\n");
		exit(1);
	}
	file = argv[1];
	printf("About to run sort with input from %s\n", file);

	/* create a new process or quit */
	if( (pid = fork() ) == -1 )
		oops("fork", 1);

	/* child does the work */
	if ( pid == 0 ){
		/* YOUR CODE GOES HERE */
		fclose(stdin); 
		FILE* sortf = file;
		if ( fopen(sortf, "r") == -1) {
			oops("open", 2);
		}
		
		if ( execlp("sort", "sort", NULL) == -1) {

		}

	}
	/* parent waits then reports */
	if ( pid != 0 ){
		wait(NULL);
		printf("Done running sort < %s\n", file);
	}
	return 0;
}
