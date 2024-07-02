#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#pragma warning(disable:4996)

int main();
void Search(int, int);

void askReturn() {
	char answer;
	printf("もう一度ファイルを読み込みますか?(y: はい, n: いいえ) :>");
	(void)scanf(" %c", &answer);
	switch (answer)
	{
	case 'y': {
		main();
	}
	case'n': {
		exit(0);
	}
	default: {
		askReturn();
	}
	}

}

void askSearch(int month, int sumof_salary) {
	char answer;
	printf("もう一度計算しますか?(y: はい, n:いいえ) :>");
	(void)scanf(" %c", &answer);
	switch (answer)
	{
	case 'y': {
		Search(month, sumof_salary);
		break;
	}
	case'n': {
		askReturn();
		break;
	}
	default: {
		askSearch(month, sumof_salary);
		break;
	}
	}
}

void historyPrint(int* salary, int x) {
	int item = 0, sum = 0;
	printf("～給料履歴～\t～給料合計～\n");
	do {
		sum += salary[item];
		printf("[%d] %d円\t%d円\n", item + 1, salary[item], sum);
		item++;
	} while (item < x);
	printf("\n");
}

void salaryCheck(int month, int sumof_salary, int modeNumber) {
	int  max_salary = 1030000, month_huyou, remain_salary,
		remain_month, max_month = 12;

	//扶養の計算//
	remain_month = max_month - month;
	remain_salary = max_salary - sumof_salary;
	if(remain_month != 0)
		month_huyou = remain_salary / remain_month;

	if (modeNumber == 2) {
		printf("年収:\t%d\n");
	}
	else {
		if (remain_salary > 0) {
			printf("残りの月 : %d - %d = %d\n", max_month, month, remain_month);
			printf("残り給料 : %d - %d = %d\n", max_salary, sumof_salary, remain_salary);
			printf("扶養内です.\n\n");
			askSearch(month, sumof_salary);
		}
		else {
			printf("残りの月 : %d - %d = %d\n", max_month, month, remain_month);
			printf("残り給料 : %d - %d = %d\n", max_salary, sumof_salary, remain_salary);
			printf("扶養外です.\n\n");
			askSearch(month, sumof_salary);
		}

		printf("～扶養計算～\n");
		printf("残りの月 : %d - %d = %d\n", max_month, month, remain_month);
		printf("残り給料 : %d - %d = %d\n", max_salary, sumof_salary, remain_salary);
		printf("扶養に入れる月給 : %d / %d = %d\n", remain_salary, remain_month, month_huyou);
		printf("\n");
	}
}

void Search(int month, int sumof_salary) {	//扶養予測の計算//
	int next_salary, max_salary = 1030000, max_month = 12;
	int remain_month, remain_salary;
	char c_salary[10];
	printf("%d月の給料(予定)は? :>", month + 1);
	(void)scanf("%s", c_salary);
	next_salary = atoi(c_salary);

	remain_salary = max_salary - sumof_salary - next_salary;
	remain_month = max_month - month - 1;

	if (remain_month == 0) {
		printf("今月の給料を入れた残りの給料 : %d - (%d + %d) = %d\n", max_salary,
			sumof_salary, next_salary, remain_salary);
		if (remain_salary > 0) {
			printf("扶養内です.\n\n");
			return;
		}
		else {
			printf("扶養外です.\n\n");
			return;
		}
	}
	else {
		printf("\n残りの月 : %d - (%d + 1) = %d\n", max_month, month, remain_month);
		printf("今月の給料を入れた残りの給料 : %d - (%d + %d) = %d\n", max_salary,
			sumof_salary, next_salary, remain_salary);
		printf("扶養に入れる月給 : %d / %d = %d円\n\n", remain_salary, remain_month, remain_salary / remain_month);
	}
	askSearch(month, sumof_salary);
}


void fileread(int modeNumber) { //file読み込み//
	int salary, sumof_salary = 0;
	int tmpsalary[13], i = 0, month;
	char yen[20], c_month[3], FilePath[256], year[5];
	const char* address = "./給料/";
	FILE* fin;

	system("cls");
	printf("給料もらってる年は?:>"); (void)scanf("%s", year);
	if (modeNumber == 2){
		printf("最後に給料もらったのは何月分? :>");	(void)scanf("%s", c_month);
		month = atoi(c_month);
	}
	else {
		month = 12;
	}
	if (month <= 0 || month > 12) 
		fileread(modeNumber);

	//strcpy(FilePath, debugAddress);
	//strcat(FilePath, address);//
	strcpy(FilePath, address);
	strcat(FilePath, year);
	strcat(FilePath, "年/");
	strcat(FilePath, year);
	strcat(FilePath, "年.txt");

	fin = fopen(FilePath, "r");
	//printf("%s\n", FilePath);//forDebug

	//SalaryHistory.txtから給料の読み込み//
	if (fin == NULL) {
		printf("ファイルが見つかりません.\n");
		askReturn();
	}
	else {
		while (fscanf(fin, "%d%s", &salary, yen) != EOF) {
			sumof_salary += salary;
			tmpsalary[i++] = salary;
		}
		fclose(fin);
	}

	system("cls");
	historyPrint(tmpsalary, i);
	salaryCheck(month, sumof_salary, modeNumber);
	Search(month, sumof_salary);
}

void modeSelect(int modeNumber) {
	if (modeNumber == 1 || modeNumber == 2) {
		fileread(modeNumber);
	}
	else {
		main();
	}
}

int main() {
	int modeNumber, debugNumber;

	printf("次の項目から選択してください\n1: 年収を算出\n2: 扶養計算\n");	(void)scanf("%d", &modeNumber);
	//printf("%d", modeNumber); (void)scanf("%d", &debugNumber);
	modeSelect(modeNumber);
	return EXIT_SUCCESS;
}
