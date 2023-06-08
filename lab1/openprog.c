#include <stdio.h>
main(){
  FILE *fp;
  char buff[255];

  fp = fopen("/home/dnc28/test.txt", "r");
  fscanf(fp, "%s", buff);
  printf("5: %s\n", buff);

  
}
