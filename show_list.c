#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
char* show_list();
int main(){
	show_list();
}
char* show_list(void){
	char cat[100] = "cat chattinglist";
	char* select;
	select = (char*)malloc(sizeof(char)*100);
	system("clear");
	printf("---------- 채팅방 목록 ----------\n");
	sleep(1);
	system(cat);
	printf("\n 원하는 채팅방의 이름을 입력하세요 : ");
	scanf("%s", select);
	
	printf("%s 채팅방이 선택되었습니다.\n", select);
	sleep(2);	
	return select;
}
	
