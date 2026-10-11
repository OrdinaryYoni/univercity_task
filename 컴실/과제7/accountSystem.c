//accountSystem.c
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

int  loadUserData(Account users[], char* filename, char* filename2) {
	FILE* fp, * fp2;
	fp = fopen(filename, "r");
	fp2 = fopen(filename2, "r");
	if (fp == NULL || fp2 == NULL) {
		printf("파일 데이터를 읽어들일 수 없습니다.");
		return -1;
	}
	char line[256];
	int line_num = 0, count = 0;

	while (fgets(line, sizeof(line), fp) != NULL && count < MAX_ACCOUNT) {
		line_num++;
		if (line[0] == '\n' || line[0] == '\r' || line[0] == ' ') continue;
		Account temp = { 0 };
		int check = sscanf(line, "%[^,],%[^,],%[^,],%lld", temp.accountNum, temp.name, temp.password, &temp.total);
		if (check != 4) {
			printf("[오류] %d번째 줄: 고객 데이터 형식이 올바르지 않아 건너뜁니다. -> %s", line_num, line);
			continue;
		}
		users[count] = temp;
		count++;
		
	}
	fclose(fp);
	line_num = 0;
	while (fgets(line, sizeof(line), fp2) != NULL) {
		line_num++;
		if (line[0] == '\n' || line[0] == '\r' || line[0] == ' ') continue;
		Transaction temp2 = { 0 };
		char id[20] = { 0 };
		int check = sscanf(line, "%[^,],%[^,],%lld,%lld", id, temp2.type, &temp2.money, &temp2.total);
		if (check != 4) {
			printf("[오류] %d번째 줄: 고객 데이터 형식이 올바르지 않아 건너뜁니다. -> %s", line_num, line);
			continue;
		}
		for (int i = 0;i < count;i++) {
			if (!strcmp(users[i].accountNum, id)) {
				if (users[i].history_count >= MAX_HISTORY) {
					for (int j = 0; j < MAX_HISTORY - 1; j++) {
						users[i].history[j] = users[i].history[j + 1];
					}
					users[i].history_count--;
				}
				users[i].history[users[i].history_count++] = temp2;
				break;
			}
		}

	}
	fclose(fp2);
	return count;
}