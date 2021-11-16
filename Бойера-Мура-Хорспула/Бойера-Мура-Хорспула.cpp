#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 256;

void preBmBc(string, int bmBc[ALPHABET_SIZE]);

int BMH(string, string);



int main()
{
	setlocale(LC_CTYPE, "rus");
	string pattern, text;
	cout << "Введите текст: ";
	getline(cin, text, '\n');
	cout << "Введите паттерн: ";
	getline(cin, pattern, '\n');
	int res = BMH(pattern, text);
	if (res == -1)
		cout << "Вхождений подстроки в строку не найдено\n";
	else
		cout << "Найдено вхождение подстроки в строку с индекса " << res << '\n';
	system("pause");
	return 0;
}

int BMH(string pattern, string text)
{
	int patternLength = pattern.length(), textLength = text.length();
	int bmBc[ALPHABET_SIZE];
	preBmBc(pattern, bmBc);
	for (int i = patternLength - 1; i < textLength; i += bmBc[text[i]])
	{
		int j = i;
		for (j = i; j >= i - patternLength + 1 && text[j] == pattern[patternLength - (i - j) - 1]; --j);
		if (j == i - patternLength)
			return i - patternLength + 1;
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
