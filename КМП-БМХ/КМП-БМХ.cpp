#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 256;

void preBmBc(string, int bmBc[ALPHABET_SIZE]);
void effPrefFunc(string, int*);
int BM_KMP(string, string);
int Max(int, int);


int main()
{
	setlocale(LC_CTYPE, "rus");
	string pattern, text;
	cout << "Введите текст: ";
	getline(cin, text, '\n');
	cout << "Введите паттерн: ";
	getline(cin, pattern, '\n');
	int res = BM_KMP(pattern, text + '#');
	if (res == -1)
		cout << "Вхождений подстроки не найдено\n";
	else
		cout << "Найдено вхождение подстроки в строку с индекса " << res << '\n';
	system("pause");
	return 0;
}

int BM_KMP(string pattern, string text)
{
	int patternLength = pattern.length(), textLength = text.length(), i = 0;
	int* pi = new int[patternLength];
	int bmBc[ALPHABET_SIZE];
	effPrefFunc(pattern, pi);
	preBmBc(pattern, bmBc);
	while (i <= textLength - patternLength)
	{
		int j = i;
		while (text[j] == pattern[j - i])
			++j;
		if (j - i == patternLength)
			return j - patternLength;
		else
		{
			j += (i == j);
			i += Max(j - i - pi[j - i - 1], bmBc[text[i + patternLength - 1]]);
		}
	}
	return -1;
}

int Max(int x, int y)
{
	return x > y ? x : y;
}

void preBmBc(string pattern, int bmBc[ALPHABET_SIZE])
{
	int length = pattern.length();
	for (int i = 0; i < ALPHABET_SIZE; ++i)
		bmBc[i] = length;
	for (int i = 0; i < length - 1; ++i)
		bmBc[pattern[i]] = length - i - 1;
}


void effPrefFunc(string str, int* pi)
{
	int strLength = str.length();
	pi[0] = 0;
	for (int i = 1; i < strLength; ++i)
	{
		int j = pi[i - 1];
		while (j > 0 && str[i] != str[j])
			j = pi[j - 1];
		if (str[i] == str[j])
			++j;
		pi[i] = j;
	}
}
