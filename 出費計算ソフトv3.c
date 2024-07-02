#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#pragma warning(disable:4996)

#define adress "./�o��"
#define Jan "January"
#define Feb "February"
#define Mar "March"
#define Apr "April"
#define May "May"
#define Jun "June"
#define Jul "July"
#define Aug "August"
#define Sep "September"
#define Oct "October"
#define Nov "November"
#define Dec "December"

int main(void);
struct String
{
	char str[30];
};

void askReturn(void) {
	char answer;
	printf("������x�ǂݍ��݂܂���?:>"); (void)scanf(" %c", &answer);
	switch (answer)
	{
	case 'y':main(); break;
	case 'n':exit(0);
	default:askReturn(); break;
	}
}

void moneyCheck(FILE* fp, FILE* fp2, char* year, const char* month) {
	system("cls");
	int money[150], i = 0, j = 0, moneySum = 0, copymoney[150];
	struct String item[150], copyitem[150];

	printf("\t�`�o����`\n");
	printf("\t����\t�o��v\n");
	while (fscanf(fp, "%d%s", &money[i], &item[i].str) != EOF) {
		moneySum += money[i];
		printf("[%d]\t%d�~\t%d�~\n", i + 1, money[i], moneySum);
		i++;
	}
	printf("%s�N%s���̏o��̍��v:%d�~(%d��)\n", year, month, moneySum, i);
	for (int j = 0; j < i; j++) {
		for (int t = 0; t < i; t++) {
			if (strcmp(copyitem[t].str, "") == 0) {
				strcpy(copyitem[t].str, item[j].str);
				copymoney[t] = money[j];
				printf("%s\n", copyitem[t].str);
			}
			else if(strcmp(item[j].str, copyitem[t].str) == 0){
				copymoney[t] += money[j];
			}
		}
	}
	int h = 0;
	while (strcmp(copyitem[h].str, "") != 0) {
		fprintf(fp2, "%d%s\n",copymoney[h], item[h].str);
		h++;
	}
	fclose(fp);
	fclose(fp2);
	askReturn();
}

void fileCheck(char monthWord, char* year) {
	const char* monthName = NULL, * monthNum = NULL;
	char filePath[256] = "", sortfile[256] = "";
	FILE *fp1, *fp2;

	switch (monthWord) {
		case'1':monthName = Jan; monthNum = "1"; break;
		case'2':monthName = Feb; monthNum = "2"; break;
		case'3':monthName = Mar; monthNum = "3"; break;
		case'4':monthName = Apr; monthNum = "4"; break;
		case'5':monthName = May; monthNum = "5"; break;
		case'6':monthName = Jun; monthNum = "6"; break;
		case'7':monthName = Jul; monthNum = "7"; break;
		case'8':monthName = Aug; monthNum = "8"; break;
		case'9':monthName = Sep; monthNum = "9"; break;
		case'a':monthName = Oct; monthNum = "10"; break;
		case'b':monthName = Nov; monthNum = "11"; break;
		case'c':monthName = Dec; monthNum = "12"; break;
		default:break;
	}

	if (NULL != monthNum && NULL != monthName) {
		strcpy(filePath, adress);
		strcat(filePath, "/");
		strcat(filePath, year);
		strcat(filePath, "�N/");
		strcat(filePath, monthNum);
		strcat(filePath, ".");
		strcat(filePath, monthName);
		strcpy(sortfile, filePath);
		strcat(sortfile, "_sorted");
		strcat(filePath, ".txt");
		strcat(sortfile, ".txt");
	}


	fp1 = fopen(filePath, "r");
	if (fp1 == NULL) {
		printf("�t�@�C����������܂���.(%s)\n", &filePath);
		askReturn();
	}
	else {		
		fp2 = fopen(sortfile, "w");
		moneyCheck(fp1,fp2 , year, monthNum);
	}
}

void dayCheck(char* year, char* month) {
	char monthWord;

	if (month[0] == '1') {
		switch (month[1]) {
		case'0':monthWord = 'a'; break;
		case'1':monthWord = 'b'; break;
		case'2':monthWord = 'c'; break;
		case NULL:monthWord = month[0];
		default: break;
		}
	}
	else monthWord = month[0];

	fileCheck(monthWord, year);
}

int main(void) {
	char month[3] = "", year[5];
	printf("��������N?:>");	(void)scanf("%s", year);
	printf("�������錎?:>");	(void)scanf("%s", month);
	if (0 >= atoi(month) || atoi(month) > 12) {
		system("cls");
		main();
	}
	else {
		dayCheck(year, month);
	}
	return EXIT_SUCCESS;
}