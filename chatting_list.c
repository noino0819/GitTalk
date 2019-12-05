#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	struct chatting_list{
		char chatting_room[100];	// 채팅방 이름
		int unread;			// 안읽은 메시지
		int is_it_multi_room;		// 채팅방 옵션
		int key[20];			// 암호화/복호화 키
	}list[100];
	FILE *chatting_fp;
	//struct chatting_list list[100];
	
	chatting_fp = fopen("./chatting_list.txt","rt");
	int i = 0;
	while(fscanf(chatting_fp, "%s%d%d%s",
	list[i].chatting_room,
	&list[i].unread, 
	&list[i].is_it_multi_room,
	list[i].key) != EOF){
		i++; 
	}
	i++;
	fclose(chatting_fp);
	scanf("%s%d%d%s",
	list[i].chatting_room,
	&list[i].unread,
	&list[i].is_it_multi_room,
	list[i].key);
	chatting_fp = fopen("./chatting_list.txt","at");
	/*
	fprintf(chatting_fp, "%s %d %d %s;\n",
	list[i].chatting_room,
	list[i].unread,
	list[i].is_it_multi_room,
	list[i].key);
	*/
	for(i=0;i<6;i++)
		printf("%s %d %d %s\n", 
		list[i].chatting_room, 
		list[i].unread, 
		list[i].is_it_multi_room,
		list[i].key);
}
