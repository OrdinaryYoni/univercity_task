//toyBank.c
#include "account_data.h"

int main() {
	srand((unsigned int)time(NULL)); //프로그램 실행 시 매번 다른 난수가 나오게 설정
	Account users[MAX_ACCOUNT];
	int user_count = 0;
	int service, bank_service;

	while (1) {
		printf("어떤 서비스를 이용하실 건가요? (1.계좌 생성 2.금융 서비스 3.거래 내역 확인 4.종료): ");
		scanf("%d", &service);
		printf("========================================================================\n");

		if (service == 1) {
			made_account(users, &user_count);
		}
		else if (service == 2 && user_count > 0) {
			printf("어떤 금융 서비스를 이용하실 건가요? (1.입금 2.출금 3.잔액조회 4.이체): ");
			scanf("%d", &bank_service);
			printf("========================================================================\n");
			if (bank_service == 1) {
				deposit(users, user_count);
			}
			else if (bank_service == 2) {
				withdrawal(users, user_count);
			}
			else if (bank_service == 3) {
				checkBalance(users, user_count);
			}
			else if (bank_service == 4) {
				transfer(users, user_count);
			}
			else {
				printf("잘못된 입력입니다. 1~4에서만 입력해주세요.\n\n");
			}
		}
		else if (service == 3 && user_count > 0) {
			checkTransaction(users, user_count);
		}
		else if (service == 4) {
			printf("프로그램을 종료합니다.");
			break;
		}
		else if (user_count == 0) {
			printf("계좌를 먼저 개설해주세요.\n\n");
		}
		else {
			printf("잘못된 입력입니다. 1~4에서만 입력해주세요.\n\n");
		}
	}
}
