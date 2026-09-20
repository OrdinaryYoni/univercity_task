//identifyTriangle3.c
#include <stdio.h>
#pragma warning(disable:4996)

int checkData(int x, int y, int z);
int isTriangle(int* x, int* y, int* z);
int checkTriangleType(int x, int y, int z);

int main() {
	int x, y, z, data_result, result, tri_result;
	printf("삼각형 세 변의 값을 입력해주세요(공백으로 구분해주세요): ");
	scanf("%d %d %d", &x, &y, &z);
	data_result = checkData(x, y, z);

	if (data_result == 0) {
		printf("값에 음수와 0이 포함되어있습니다. 양수로 입력해주세요.");
	}
	else {
		result = isTriangle(&x, &y, &z);
		if (result == 0) {
			printf("삼각형이 아닙니다!");
		}
		else {
			tri_result = checkTriangleType(x, y, z);
			if (tri_result == 30) {
				printf("예각삼각형입니다!");
			}
			else if (tri_result == 90) {
				printf("직각삼각형입니다!");
			}
			else {
				printf("둔각삼각형입니다!");
			}
		}
	}
}

//데이터 검사
int checkData(int x, int y, int z) {
	if (x <= 0 || y <= 0 || z <= 0) {
		return 0;
	}
	else return 1;
}
//삼각형인지 판별 &x를 큰 값으로 만들기
int isTriangle(int* x, int* y, int* z) {
	int temp;
	if (*x <= *y) {
		temp = *x;
		*x = *y;
		*y = temp;
	}
	if (*x <= *z) {
		temp = *x;
		*x = *z;
		*z = temp;
	}
	if (*x < *y + *z) {
		return 1;
	}
	else return 0;
}
//예각, 직각, 둔각삼각형인지 판별
int checkTriangleType(int x, int y, int z) {
	if (x * x < y * y + z * z) {
		return 30;
	}
	else if (x * x == y * y + z * z) {
		return 90;
	}
	else return 180;
}
