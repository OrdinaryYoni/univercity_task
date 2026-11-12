//identifyTriangle.c
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int isTriangle(long long x[3], long long y[3]);
double getTriangleInfo(int x[3], int y[3]);
long long getDistance(int x1, int y1, int x2, int y2);

int main() {
	int x[3], y[3];
	for (int i = 0;i < 3;i++) {
		printf("삼각형의 %d번째 점 입력\n", i + 1);
		printf("x:");
		scanf("%d", &x[i]);
		printf("y:");
		scanf("%d", &y[i]);
	}
	if (isTriangle(x, y) == 0) {
		printf("삼각형이 아닙니다!");
		exit(1);
	}
	double r = getTriangleInfo(x, y);
	printf("둘레 : %.2f", r);
}

int isTriangle(int x[3], int y[3]) {
	//벡터의 외적 이용 벡터 AB * 벡터 AC
	long long ab[2] = { x[1] - x[0],y[1] - y[0] };
	long long ac[2] = { x[2] - x[0],y[2] - y[0] };
	if (ab[0] * ac[1] - ab[1] * ac[0] == 0) {
		return 0;
	}
	return 1;
}

double getTriangleInfo(int x[3], int y[3]) {
	long long ab2 = getDistance(x[0], y[0], x[1], y[1]);
	long long bc2 = getDistance(x[1], y[1], x[2], y[2]);
	long long ca2 = getDistance(x[2], y[2], x[0], y[0]);
	long long temp;
	if (ab2 <= bc2) { temp = ab2; ab2 = bc2; bc2 = temp; }
	if (ab2 <= ca2) { temp = ab2; ab2 = ca2; ca2 = temp; }

	if (ab2 == bc2 + ca2) {
		printf("직각삼각형입니다!\n");
	}
	else if (ab2 > bc2 + ca2) {
		printf("둔각삼각형입니다!\n");
	}
	else {
		printf("예각삼각형입니다!\n");
	}
	double r = sqrt(getDistance(x[0], y[0], x[1], y[1]))
		+ sqrt(getDistance(x[1], y[1], x[2], y[2]))
		+ sqrt(getDistance(x[2], y[2], x[0], y[0]));
	return r;
}

long long getDistance(int x1, int y1, int x2, int y2) {
	double dx = x2 - x1;
	double dy = y2 - y1;
	return dx * dx + dy * dy;
}