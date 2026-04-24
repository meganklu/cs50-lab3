#include "string.c"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *s = malloc(20);
  if (s == NULL){
    printf("Malloc issue :(\n");
    exit -9;
  }

  char str1[] = "Hello ";
  char str2[] = "world!";
  char str3[] = "Batman";
  char str4[] = "Hello world!";
  char str5[] = ""; // Empty string
  char str6[] = "!@#$%^"; // Special characters
  char str7[] = "Hello\0world!" // String with null terminating character

  mystrcat(s, str5);
  mystrcat(s, str1);
  mystrcat(s, str2);
  mystrcat(s, str5);
  if (strcmp(s, str4) !=0)
  {
    printf("Error: strcat");
  }
  else
    printf("--> strcat OK\n");

  if (mystrlen(s) != strlen(s) 
		  && mystrlen(str5) != strlen(str5)
		  && mystrlen(str6) != strlen(str6)
		  && mystrlen(str7) != strlen(str7))
  {
    printf("Error: strlen");
  }
  else
    printf("--> strlen OK\n");

  mystrcpy(s, str3);
  mystrcpy(s, str6);
  mystrcpy(s, str3);
  if (strcmp(s, str3) !=0
		  && strcmp(mystrcpy(s, str5), str5))
  {
    printf("Error: strcpy");
  }
  else
    printf("--> strcpy OK\n");

  printf("---");

  free(s); 
  return 0;

}
