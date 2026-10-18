#include <stdio.h>

int plus(int a, int b);

int main() {
	int a, b;
	printf("test.cpp\n");

	printf("두 수를 입력(공백으로 구분): ");
	scanf_s("%d %d", &a, &b);

	printf("a+b=%d", plus(a, b));
}

int plus(int a, int b) { return a + b; }
