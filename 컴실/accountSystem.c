#include "account_data.h"

//계좌 생성
void made_account(Account users[], int* count) {
	if (*count >= MAX_ACCOUNT) {
		printf("계좌를 생성할 수 없습니다. 고객센터에 문의하세요.\n\n");
		return 0;
	}

	int num = *count;

	int tail = rand() % 10000;

	sprintf(users[num].accountNum, "0304-8989-%04d", tail);

	printf("이름: ");
	scanf("%s", users[num].name);

	printf("비밀번호: ");
	scanf("%s", users[num].password);

	printf("초기 입금액: ");
	scanf("%lld", &users[num].total);
	users[num].history_count = 0;

	printf("계좌 생성 완료!\n");
	printf("%s님의 계좌 번호는 %s입니다.\n\n", users[num].name, users[num].accountNum);
	(*count)++;
}

//거래내역 생성
void made_history(Account* user, long long money, char* type) {
	Transaction new_transaction;
	new_transaction.money = money;
	new_transaction.total = user->total;
	strcpy(new_transaction.type, type);

	if (user->history_count >= MAX_HISTORY) {
		for (int i = 0; i < MAX_HISTORY - 1; i++) {
			user->history[i] = user->history[i + 1];
		}
		user->history_count--;
	}
	user->history[user->history_count++] = new_transaction;
}

//계좌번호로 계좌 찾기
int find_account_by_num(Account users[], char* acc_num, int count) {
	for (int i = 0; i < count; i++) {
		if (!strcmp(users[i].accountNum, acc_num)) {
			return i;
		}
	}
	return -1;
}
//이름으로 계좌 찾기
int find_account_by_name(Account users[], char* name, int count) {
	for (int i = 0; i < count; i++) {
		if (!strcmp(users[i].name, name)) {
			return i;
		}
	}
	return -1;
}

//비밀번호 확인
int isRightPW(Account user) {
	char pw[20];
	printf("고객 인증을 위해 비밀번호를 입력해주세요: ");
	scanf("%s", pw);

	if (!strcmp(user.password, pw)) {
		printf("인증이 완료되었습니다.\n");
		return 0;
	}
	else {
		printf("[오류] 비밀번호가 올바르지 않습니다.\n\n");
		return -1;
	}
}
