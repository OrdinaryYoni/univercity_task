#include <stdio.h>
#pragma warning(disable:4996)
#define MAXROOM 50

void check_in(unsigned char room[]);
void check_out(unsigned char room[]);
unsigned int calcMoney(unsigned char capacity, unsigned int day);

int main() {
	unsigned char room[MAXROOM + 1] = { 0 };
	short menu;
	while (1) {
		printf("메뉴 입력(1.입실 2.퇴실 3.종료) : ");
		scanf("%d", &menu);
		if (menu == 1) {
			check_in(room);
		}
		else if (menu == 2) {
			check_out(room);
		}
		else if (menu == 3) {
			break;
		}
		else {
			printf("잘못된 선택지 입니다. 다시 입력해주세요.\n\n");
		}
	}
}

void check_in(unsigned char room[]) {
	short num,room_num;
	printf("입실할 인원 수 입력: ");
	scanf("%d", &num);
	if (num <= 0) {
		printf("잘못된 값입니다. 양수로 입력해주세요.\n\n");
	}
	else if (num > 4) {
		printf("5인 이상부터는 방을 여러개 잡아야 합니다.\n\n");
	}
	else {
		printf("--현재 빈 방--\n");
		for (unsigned char i = 1;i <= MAXROOM;i++) {
			if (room[i] == 0) {
				printf("%d, ", i);
			}
		}
		printf("\n\n");
		while (1) {
			printf("방 번호 입력: ");
			scanf("%d", &room_num);
			if (room_num <= 0 || room_num > 50) {
				printf("잘못된 값입니다. 1~50범위에서 입력해주세요.\n");
			}
			else if (room[room_num] != 0) {
				printf("빈 방이 아닙니다. 다른 방을 선택해주세요.\n");
			}
			else {
				room[room_num] = num;
				printf("%d번 방 입실 완료되었습니다.\n\n", room_num);
				break;
			}
		}
		
	}
}

void check_out(unsigned char room[]) {
	short room_num, day;
	printf("퇴실할 방 번호 입력: ");
	scanf("%d", &room_num);
	if (room_num <= 0 || room_num > 50) {
		printf("잘못된 값입니다. 1~50범위에서 입력해주세요.\n\n");
	}
	else if (room[room_num] == 0) {
		printf("빈 방입니다. 다시 입력해주세요.\n\n");
	}
	else {
		printf("투숙일 입력: ");
		scanf("%d", &day);
		printf("정산할 요금은 %d원입니다.\n", calcMoney(room[room_num], day));
		room[room_num] = 0;
		printf("정상적으로 처리되었습니다.\n\n");
	}
}

unsigned int calcMoney(unsigned char capacity, short day) {
	if (capacity > 2) return (50000 + (capacity - 2) * 5000) * day;
	else return 50000 * day;
}
