//account_data.h
#pragma once
#pragma warning(disable:4996)
#define MAX_ACCOUNT 10
#define MAX_HISTORY 50
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	char type[20];
	long long money;
	long long total;
}Transaction;

typedef struct {
	char accountNum[20];
	char name[20];
	char password[20];
	long long total;

	Transaction history[MAX_HISTORY];
	int history_count;

}Account;

void made_account(Account users[], int* count);
void made_history(Account* user, long long money, char* type);
int find_account_by_num(Account users[], char* acc_num, int count);
int find_account_by_name(Account users[], char* name, int count);
int isRightPW(Account user);
void deposit(Account users[], int count);
void withdrawal(Account users[], int count);
void checkBalance(Account users[], int count);
void transfer(Account users[], int count);
void checkTransaction(Account users[], int count);