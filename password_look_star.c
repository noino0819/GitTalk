#include <stdio.h>
#include <termio.h>

int getch(void);

int main(void) {
	int i = 0; //i는 배열을 증가하면서	배열의 위치를 알려줄 변수임
	char password[30];
	while (20180825) {
		password [i] = getch();
		if (password[i] == '\n') {
			password[i] = '\0';
			break;
		}
		if (i == 29) {
			printf("비밀번호 제한을 초과하셨습니다.");
			break;
		}
		i++;
		printf("*");
	}
	
}
//위에 있는 코드를 사용하면 입력은 password배열에 저장되지만 눈에 보이는건 별로 보입니다. 엔터를 치면 끝나용.

//리눅스에선 getch를 사용할 수 없어 따로 함수로 구현하였습니다.
int getch(void) {
	int ch;
	struct termios buf, save;
	tcgetattr(0, &save);
	buf = save;
	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}
