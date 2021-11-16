#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 256;

void preBmBc(string, int bmBc[ALPHABET_SIZE]);
int Raita(string, string);


int main()
{
	setlocale(LC_CTYPE, "rus");
	string pattern, text;
	cout << "Введите текст: ";
	getline(cin, text, '\n');
	cout << "Введите паттерн: ";
	getline(cin, pattern, '\n');
	int res = Raita(pattern, text);
	if (res == -1)
		cout << "Вхождений подстроки не найдено\n";
	else
		cout << "Найдено вхождение подстроки в строку с индекса " << res << '\n';
	system("pause");
	return 0;
}

int Raita(string pattern, string text)
{
	int patternLength = pattern.length(), textLength = text.length(), j;
	int bmBc[ALPHABET_SIZE];
	preBmBc(pattern, bmBc);
	int firstSymb = pattern[0];
	int middleSymb = pattern[patternLength - patternLength / 2 - 1];
	int lastSymb = pattern[patternLength - 1];
	for (int i = patternLength - 1; i < textLength; i += bmBc[text[i]])
	{
		if (lastSymb == text[i] && firstSymb == text[i - patternLength + 1] && middleSymb == text[i - patternLength / 2])
		{
			for (j = i - 1; j > i - patternLength + 1 && pattern[patternLength - (i - j) - 1] == text[j]; --j);
			if (j == i - patternLength + 1)
				return j;
		}
	}
	return -1;
}

void preBmBc(string pattern, int bmBc[ALPHABET_SIZE])
{
	int length = pattern.length();
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		bmBc[i] = length;
	for (int i = 0; i < length - 1; ++i)
		bmBc[pattern[i]] = length - i - 1;
}
