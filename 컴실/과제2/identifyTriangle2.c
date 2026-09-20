//identifyTriangle2.c
#include <stdio.h>
#pragma warning(disable:4996)

int checkData(int x, int y, int z);
int isTriangle(int x, int y, int z);


int main() {
	int x, y, z, data_result, result;
	printf("삼각형 세 변의 값을 입력해주세요(공백으로 구분해주세요): ");
	scanf("%d %d %d", &x, &y, &z);
	data_result = checkData(x, y, z);

	if (data_result == 0) {
		printf("값에 음수와 0이 포함되어있습니다. 양수로 입력해주세요.");
	}
	else {
		result = isTriangle(x, y, z);
		if (result == 0) {
			printf("삼각형이 아닙니다!");
		}
		else {
			printf("삼각형입니다!");
		}
	}
}

//데이터 검사(음수랑 0 걸러내기)
int checkData(int x, int y, int z) {
	if (x <= 0 || y <= 0 || z <= 0) {
		return 0;
	}
	else return 1;
}
//삼각형인지 판별
int isTriangle(int x, int y, int z) {
	if (x < y + z && y < x + z && z < x + y){
		return 1;
	}
	else return 0;
}
