#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <string.h>

#define MAX_INPUT_SIZE 50

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);

	char inputStr[MAX_INPUT_SIZE + 1] = {'\0', };
	int lengthStr;

	char letterList[MAX_INPUT_SIZE][MAX_INPUT_SIZE];
	char digitList[MAX_INPUT_SIZE][MAX_INPUT_SIZE];
	int letterList_position = 0, digitList_position = 0;

	printf("Введите что-нибудь(макс %d символов): ", MAX_INPUT_SIZE);
	fgets(inputStr, MAX_INPUT_SIZE + 1, stdin);
	lengthStr = strlen(inputStr) - 1;

	int _internalPosition = 0;
	int _wasChange = 0;
	char _lastIs;

	for (int i = 0; i < lengthStr; i++) {
		char nowLetter = inputStr[i];
		if (_wasChange) {
			_internalPosition = 0;
			_wasChange = 0;
		}
		if (isdigit(inputStr[i])) {
			_lastIs = 'd';
			digitList[digitList_position][_internalPosition] = nowLetter;
			digitList[digitList_position][_internalPosition + 1] = '\0';
		}
		else {
			_lastIs = 'l';
			letterList[letterList_position][_internalPosition] = nowLetter;
			letterList[letterList_position][_internalPosition + 1] = '\0';
		}
		if (i != lengthStr - 1) {
			if (isdigit(inputStr[i]) != isdigit(inputStr[i + 1])) {
				if (_lastIs == 'd') digitList_position++;
				else letterList_position++;
				_wasChange = 1;
			}
		}
		else {
			if (_lastIs == 'd') digitList_position++;
			else letterList_position++;
		}
		_internalPosition++;
	}

	printf("\n");
	if (letterList_position == 0) printf("Во входной строке нет букв\n");
	else {
		printf("\nМассив из последовательностей букв: [ ");
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
	return 0;
}