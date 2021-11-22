#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <string.h>

//43 '4 'gh

#define MAX_INPUT_SIZE 50
#define DEBUG 1

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);

	unsigned char inputStr[MAX_INPUT_SIZE + 1];
	int lengthStr;

	unsigned char letterList[MAX_INPUT_SIZE][MAX_INPUT_SIZE];
	unsigned char digitList[MAX_INPUT_SIZE][MAX_INPUT_SIZE];
	int letterList_position = 0, digitList_position = 0;

	while(1){
		letterList_position = 0, digitList_position = 0;
		inputStr[0] = '\0';
		for (int i = 0; i < MAX_INPUT_SIZE; i++) {
			for (int b = 0; b < MAX_INPUT_SIZE; b++) {
				letterList[i][b] = '\0';
				digitList[i][b] = '\0';
			}
		}

		printf("Введите что-нибудь(макс %d символов)(Введите 0, чтобы выйти): ", MAX_INPUT_SIZE);
		fgets(inputStr, MAX_INPUT_SIZE + 1, stdin);

		while (strlen(inputStr) == 1) {
			printf("Вы ничего не ввели\nВведите заново(макс %d)(Введите 0, чтобы выйти): ", MAX_INPUT_SIZE);
			fgets(inputStr, MAX_INPUT_SIZE + 1, stdin);
		}
		lengthStr = strlen(inputStr) - 1;

		if (inputStr[0] == '0' && lengthStr == 1) break;

		int _internalPosition = 0;
		char lastChar;
		int lastDefined = 0;
		int finish = 0;

		for (int i = 0; i < lengthStr; i++) {
			unsigned char nowLetter = inputStr[i];
			if (i == lengthStr - 1) finish = 1;
			if (!isalnum(nowLetter)) {
				if (_internalPosition) {
					_internalPosition = 0;
					if (lastDefined) {
						if (lastChar == 'l') letterList_position++;
						else digitList_position++;
					}
				}
				continue;
			}
			if (isdigit(nowLetter)) {
				if (lastDefined) {
					if (lastChar == 'l' && _internalPosition != 0) {
						letterList_position++;
						_internalPosition = 0;
					}
				}
				else {
					lastDefined = 1;
				}
				lastChar = 'd';
				digitList[digitList_position][_internalPosition] = nowLetter;
				_internalPosition++;
				
			}
			if (isalpha(nowLetter)) {
				if (lastDefined) {
					if (lastChar == 'd' && _internalPosition != 0) {
						digitList_position++;
						_internalPosition = 0;
					}
				}
				else {
					lastDefined = 1;
				}
				lastChar = 'l';
				letterList[letterList_position][_internalPosition] = nowLetter;
				_internalPosition++;
			}
			if (finish) {
				if (lastDefined) {
					if (lastChar == 'l') letterList_position++;
					else digitList_position++;
				}
			}
		}

		printf("\n");
		if (letterList_position == 0) printf("Во входной строке нет букв\n");
		else {
			printf("Массив из последовательностей букв: [ ");
			for (int i = 0; i < letterList_position; i++) {
				int sectionLength = strlen(letterList[i]);
				for (int s = 0; s < sectionLength; s++) {
					printf("%c", letterList[i][s]);
				}
				printf(", ");
			}
			printf("]\n");
		}

		if (digitList_position == 0) printf("Во входной строке нет цифр\n");
		else {
			printf("Массив из последовательностей цифр: [ ");
			for (int i = 0; i < digitList_position; i++) {
				int sectionLength = strlen(digitList[i]);
				for (int s = 0; s < sectionLength; s++) {
					printf("%c", digitList[i][s]);
				}
				printf(", ");
			}
			printf("]\n");
		}
		printf("\n");
	}
	return 0;
}