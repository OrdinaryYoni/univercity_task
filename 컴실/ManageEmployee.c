#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#pragma warning(disable:4996)
#define MAX_EMPLOYEE 50

typedef struct {
	int id;
	char name[20];
	char phone[20];
	int birth[3];
}Employee;

int loadEmployees(char filename, Employee users[], int current_year);
void addEmployee(Employee users[], int* count);
int findEmployee(Employee users[], int count);
bool isLeapYear(int year);
bool isValidDate(int y, int m, int d, int current_year);
bool isDuplicateID(Employee users[], int count, int id);

int main() {
	Employee users[MAX_EMPLOYEE];
	char filename = "..\\컴실\\employeeData.txt";

	time_t t = time(NULL);
	struct tm* today = localtime(&t);
	int current_year = today->tm_year + 1900;
	int current_month = today->tm_mon + 1;
	int current_day = today->tm_mday;
	int birth_found = 0;
	int menu;

	int user_count = loadEmployees(filename, users, current_year);
	if (user_count == -1) {
		return 1;
	}

	printf("정상적으로 읽어들인 직원 수: %d명\n\n", user_count);
	printf("===================\n");
	printf("이번 달(%d) 생일자\n");
	for (int i = 0;i < user_count;i++) {
		if (users[i].birth[1] == current_month) {
			printf("%s님: %d일\n", users[i].name, users[i].birth[2]);
			birth_found++;
		}
	}
	if (birth_found == 0) {
		printf("이번 달은 생일자가 없습니다.\n");
	}
	printf("===================\n\n");

	while (1) {
		printf("메뉴를 선택해주세요.(1.직원 정보 등록 2.직원 검색 3.종료): ");
		scanf("%d", &menu);
		if (menu == 1) {
			addEmployee(users, &user_count);
		}
		else if (menu == 2) {
			int result = findEmployee(users, user_count);
			if (result == -1) {
				printf("[오류] 해당하는 직원이 없습니다.\n\n");
			}
			else {
				printf("사번: %d\n", users[result].id);
				printf("이름: %s\n", users[result].name);
				printf("나이: %d\n", current_year - users[result].birth[0]);
				printf("전화번호: %s", users[result].phone);
			}
		}
		else if (menu == 3) break;
		else {
			printf("잘못된 입력입니다. 1~3에서 입력해주세요.");
		}
	}

}

//파일에서 직원 데이터 읽기
int loadEmployees(char filename, Employee users[], int current_year) {
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("[오류] 파일을 '%s'를 읽을 수 없습니다.\n", filename);
		return -1;
	}
	char line[256];
	int line_num = 0;
	int count = 0;

	while (fgets(line, sizeof(line), fp) != NULL && count < MAX_EMPLOYEE) {
		line_num++;
		if (line[0] == '\n' || line[0] == '\r') continue;

		Employee temp;
		int check = sscanf(line, "%d %s %s %d.%d.%d", &temp.id, temp.name, temp.phone, temp.birth[0], temp.birth[1], temp.birth[2]);

		if (check != 6) {
			printf("[오류] %d번째 줄: 데이터 형식이 올바르지 않아 건너뜁니다. -> %s\n", line_num, line);
			continue;
		}
		if (isDuplicateID(users, count, temp.id)) {
			printf("[오류] %d번째 줄: 중복된 사번(%d)입니다. 건너뜁니다.\n", line_num, temp.id);
			continue;
		}
		if (isValidDate(temp.birth[0], temp.birth[1], temp.birth[2], current_year)) {
			printf("[오류] %d번째 줄: 잘못된 생년월일(%d-%d-%d)입니다. 건너뜁니다.\n", line_num, temp.birth[0], temp.birth[1], temp.birth[2]);
			continue;
		}
		users[count] = temp;
		count++;
	}
	fclose(fp);
	return count;

}

//직원 추가
void addEmployee(Employee users[], int* count) {
	int num = *count;
	if (num >= MAX_EMPLOYEE) {
		printf("데이터 입력 한도가 다 찼습니다. 업그레이드를 해주세요.\n");
	}
	else {
		printf("직원 데이터를 입력해주세요(예: 3040000 홍길동 010-1234-4321 2001.02.03): ");
		scanf("%d %s %s %d.%d.%d", &users[num].id, users[num].name, users[num].phone, &users[num].birth[0], &users[num].birth[1], &users[num].birth[2]);
		(*count)++;
	}
}
//직원 찾기
int findEmployee(Employee users[], int count) {
	int id;
	printf("해당 직원의 사번을 입력해 주세요: ");
	scanf("%d", &id);
	for (int i = 0;i < count;i++) {
		if (id == users[i].id) {
			return id;
		}
	}
	return -1;
}

//윤년 검사
bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}
//날짜 유효성 검사
bool isValidDate(int y, int m, int d, int current_year) {
	int day_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (y < 1900 || y > current_year) return true;
	if (m < 1 || m > 12) return true;
	if (m == 2 && isLeapYear(y)) {
		day_in_month[2] = 29;
	}
	if (d < 1 || d > day_in_month[m]) return true;
	return false;
}
//사번 중복 검사 함수
bool isDuplicateID(Employee users[], int count, int id) {
	for (int i = 0;i < count;i++) {
		if (users[i].id == id) return true;
	}
	return false;
}