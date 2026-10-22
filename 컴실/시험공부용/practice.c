#include <stdio.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct {
	int line_num;
	char text[256];
}Record;

int main() {
	char filename[50] = "..\\컴실\\data.txt", filename2[50] = "..\\컴실\\result.bin";
	FILE* fr, * fw, * fp;
	fr = fopen(filename, "r");
	fw = fopen(filename2, "wb");
	if (fr == NULL || fw == NULL) {
		printf("파일을 불러올 수 없습니다.");
		return -1;
	}
	char line[255];
	int line_num = 0;
	while (fgets(line, sizeof(line), fr) != 0) {
		Record record = { 0 };

		line_num++;
		line[strcspn(line, "\r\n")] = '\0';

		record.line_num = line_num;
		strncpy(record.text, line, sizeof(record.text) - 1);

		printf("%d\t%s\n", record.line_num, record.text);

		fwrite(&record, sizeof(Record), 1, fw);
	}
	fclose(fr);
	fclose(fw);

	fp = fopen(filename2, "rb");
	if (fp == NULL) {
		printf("파일 불러오기 실패");
		return -1;
	}
	Record record;
	while (fread(&record, sizeof(Record), 1, fp) != 0) {
		printf("%d\t%s\n", record.line_num, record.text);
	}
	fclose(fp);
}