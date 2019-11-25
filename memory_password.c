#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
	char memory_password[80];
	strcat(memory_password,"git config credential.helper 'cache --timeout=3600'");//한번 로그인을 하면 1시간동안 로그인을 유지한다.
	system(memory_password);
}
