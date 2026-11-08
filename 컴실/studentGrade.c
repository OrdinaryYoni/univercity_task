#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct Student {
	char name[20];
	int mid;
	int final;
	int total;
	struct Student* next;
}Student;

Student* createNode(char name[20], int mid, int final);
Student* sortingAscending(Student* head, Student* new);

int main(void) {
	Student* head = NULL;
	int students;
	printf("학생의 수: ");
	scanf("%d", &students);
	if (students <= 0) {
		printf("양수로 다시 입력해주세요.");
		exit(1);
	}

	for (int i = 0;i < students;i++) {
		char name[20];
		int mid, final;
		printf("이름 중간점수 기말점수 입력: ");
		scanf("%s %d %d", name, &mid, &final);
		if (mid < 0 || final < 0) {
			printf("양수로 다시 입력해주세요.");
			exit(1);
		}

		Student* node = createNode(name, mid, final);
		head = sortingAscending(head, node);
	}

	printf("\n====*학생 성적 오름차순 정렬 결과*====\n");
	printf("이름\t중간\t기말\t총점\n");
	while (head != NULL) {
		Student* temp = head;
		printf("%s\t%d\t%d\t%d\n", head->name, head->mid, head->final, head->total);
		head = head->next;
		free(temp);
	}
}

Student* createNode(char name[20], int mid, int final) {
	struct Student* list = (Student*)malloc(sizeof(Student));
	if (list == NULL) {
		printf("동적 메모리 할당 오류!\n");
		exit(1);
	}
	strcpy(list->name, name);
	list->mid = mid;
	list->final = final;
	list->total = final + mid;
	list->next = NULL;
	return list;
}

Student* sortingAscending(Student* head, Student* new) {
	if (head == NULL || head->total > new->total) {
		new->next = head;
		return new;
	}

	Student* p = head;
	while (p->next != NULL && p->next->total <= new->total) {
		p = p->next;
	}

	new->next = p->next;
	p->next = new;

	return head;
}