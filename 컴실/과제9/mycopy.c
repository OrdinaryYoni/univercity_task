#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
#define BUFFERSIZE 1024

int checkArgc(int argc);
size_t readFile(char* filename, char* buffer);
int writeFile(char* filename, char* buffer, size_t data_len);

int main(int argc, char *argv[]) {
	if (checkArgc(argc)) {
		printf("사용법: %s <원본 텍스트 파일> <대상 바이너리 파일>\n", argv[0]);
		return -1;
	}

	char file[50];
	char file2[50];
	strcpy(file, argv[1]);
	strcpy(file2, argv[2]);
	char buffer[BUFFERSIZE];
	size_t data = readFile(file, buffer);
	
	if (data == 0) {
		return -1;
	}
	if (!writeFile(file2, buffer, data)) {
		return -1;
	}
	printf("\n파일이 정상적으로 저장되었습니다.\n");
	return 0;
}

int checkArgc(int argc) {
	return argc != 3;
}

size_t readFile(char* filename, char* buffer) {
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\n읽을 파일을 불러올 수 없습니다.");
		return 0;
	}

	size_t data = fread(buffer, 1, BUFFERSIZE-1, fp);
	buffer[data] = '\0';
	printf("====불러온 파일 내용====\n");
	printf("%s\n", buffer);
	fclose(fp);

	return data;
}

int writeFile(char* filename, char* buffer, size_t data_len) {
	FILE* fp;
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		printf("\n저장할 파일을 생성할 수 없습니다.");
		return 0;
	}

	fwrite(buffer, 1, data_len, fp);
	fclose(fp);

	return 1;
}