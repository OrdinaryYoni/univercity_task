#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

char* changeFilename(char* filename);

int main() {
	char filename[50], filename2[50];
	printf("처리할 파일 이름을 입력하세요. :");
	scanf("%s", filename);
	strcpy(filename2, changeFilename(filename));

	FILE* fr, * fw;
	fr = fopen(filename, "r");
	if (fr == NULL) {
		printf("파일을 불러올 수 없습니다.");
		return -1;
	}
	fw = fopen(filename2, "w");

	char line[255];
	int line_num = 0;
	while (fgets(line, sizeof(line), fr)) {
		line_num++;
		printf("%d	%s", line_num, line);
		fprintf(fw, "%d	%s", line_num, line);
	}
	fclose(fr);
	fclose(fw);
}

char* changeFilename(char* filename) {
	char filename2[50];

	size_t length = strlen(filename);
	for (int i = 0;i < length;i++) {
		if (filename[i] == '.') {
			filename2[i] = '\0';
			break;
		}
		filename2[i] = filename[i];
	}
	strcat(filename2, ".dst");

	return filename2;
}