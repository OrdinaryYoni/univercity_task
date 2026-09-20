//bankSystem.c
#include "account_data.h"

//입금
void deposit(Account users[], int count) {
	char account_num[20];
	long long money;

	printf("입금할 계좌번호 입력: ");
	scanf("%s", account_num);

	int num = find_account_by_num(users, account_num, count);
	if (num == -1) {
		printf("[오류] 존재하지 않는 계좌번호입니다.\n\n");
	}
	else {
		printf("입금할 금액 입력: ");
		scanf("%lld", &money);
		if (money < 0) {
			printf("[오류] 잘못된 입력값입니다. 양수로 입력해주세요.\n\n");
		}
		else {
			users[num].total += money;
			made_history(&users[num], money, "입금");
			printf("%s님의 계좌 %s의 거래 후 잔액은 %lld원입니다.\n\n", users[num].name, users[num].accountNum, users[num].total);
		}

	}
}

//출금
void withdrawal(Account users[], int count) {
	char account_num[20];
	long long money;

	printf("출금할 계좌번호 입력: ");
	scanf("%s", account_num);

	int num = find_account_by_num(users, account_num, count);
	int result;
	if (num == -1) {
		printf("[오류] 존재하지 않는 계좌번호입니다.\n\n");
	}
	else {
		result = isRightPW(users[num]);
		if (result == 0) {
			printf("출금할 금액 입력: ");
			scanf("%lld", &money);
			if (money > users[num].total) {
				printf("잔액이 부족합니다.\n\n");
			}
			else {
				if (money < 0) {
					printf("[오류] 잘못된 입력값입니다. 양수로 입력해주세요.\n\n");
				}
				else {
					users[num].total -= money;
					made_history(&users[num], -money, "출금");
					printf("%s님의 계좌 %s의 거래 후 잔액은 %lld원입니다.\n\n", users[num].name, users[num].accountNum, users[num].total);
				}
			}
		}

	}

}

//잔액 조회
void checkBalance(Account users[], int count) {
	char account_num[20];

	printf("잔액 조회할 계좌번호 입력: ");
	scanf("%s", account_num);

	int num = find_account_by_num(users, account_num, count);
	int result;
	if (num == -1) {
		printf("[오류] 존재하지 않는 계좌번호입니다.\n\n");
	}
	else {
		result = isRightPW(users[num]);
		if (result == 0) {
			printf("%s님의 계좌 %s의 잔액은 %lld원입니다.\n\n", users[num].name, users[num].accountNum, users[num].total);
			made_history(&users[num], 0, "잔액 조회");
		}
	}
}

//이체
void transfer(Account users[], int count) {
	char my_num[20], other_num[20];
	long long money;

	printf("본인 계좌번호 입력: ");
	scanf("%s", my_num);
	printf("이체할 상대 계좌번호 입력: ");
	scanf("%s", other_num);

	int num = find_account_by_num(users, my_num, count);
	int num2 = find_account_by_num(users, other_num, count);
	int result;

	if (num == -1 || num2 == -1) {
		printf("[오류] 존재하지 않는 계좌번호입니다.\n\n");
	}
	else {
		result = isRightPW(users[num]);
		if (result == 0) {
			printf("이체할 금액 입력: ");
			scanf("%lld", &money);
			if (money > users[num].total) {
				printf("잔액이 부족합니다.\n\n");
			}
			else {
				if (money < 0) {
					printf("[오류] 잘못된 입력값입니다. 양수로 입력해주세요.\n\n");
				}
				else {
					users[num].total -= money;
					users[num2].total += money;
					made_history(&users[num], money, "이체(송금)");
					made_history(&users[num2], money, "입금");
					printf("%s님의 계좌 %s의 거래 후 잔액은 %lld원입니다.\n\n", users[num].name, users[num].accountNum, users[num].total);
				}
				
			}

		}
	}
}

//거래내역 확인
void checkTransaction(Account users[], int count) {
	char name[20];
	printf("조회할 이름 확인: ");
	scanf("%s", name);
	int num = find_account_by_name(users, name, count);
	if (num == -1) {
		printf("[오류] 존재하지 않는 사용자입니다.\n\n");
	}
	else {
		printf("거래|	거래 종류|	돈\n");
		printf("========================================\n");
		for (int i = 0; i < users[num].history_count; i++) {
			printf("%d|	%s|	%lld\n", i + 1, users[num].history[i].type, users[num].history[i].money);
		}
		printf("\n");
	}
}