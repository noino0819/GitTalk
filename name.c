#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
	char echo_string[50] = "echo ";
	char name[30];
	scanf("%s", name);
	strcat(echo_string, name);
	strcat(echo_string, ">");
	strcat(echo_string, name);
	system(echo_string);
}
