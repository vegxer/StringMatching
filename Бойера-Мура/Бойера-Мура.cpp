#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 256;

int BoyerMooreStringSearch(string, string);
void preBmBc(string, int bmBc[ALPHABET_SIZE]);
void preBmGs(string, int*);
bool isPrefix(string, int);
int suffixLength(string, int);
int Max(int, int);

int main()
{
	setlocale(LC_CTYPE, "rus");
	string str, pattern;
	cout << "Введите текст: ";
	getline(cin, str, '\n');
	cout << "Введите подстроку: ";
	getline(cin, pattern, '\n');
	int res = BoyerMooreStringSearch(str, pattern);
	if (res == -1)
		cout << "Вхождений не найдено\n";
	else
		cout << "Найдено вхождение с индекса " << res << '\n';
	system("pause");
	return 0;
}

int BoyerMooreStringSearch(string str, string pattern)
{
	int strLength = str.length(), patternLength = pattern.length(), j;
	int bmBc[ALPHABET_SIZE];
	int* bmGs = new int[patternLength];
	preBmBc(pattern, bmBc);
	preBmGs(pattern, bmGs);
	for (int i = patternLength - 1; i < strLength; i += Max(bmBc[str[j]] - (i - j), bmGs[patternLength - (i - j) - 1]))
	{
		for (j = i; j > i - patternLength && str[j] == pattern[patternLength - (i - j) - 1]; --j);
		if (j == i - patternLength)
			return i - patternLength + 1;
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

void preBmGs(string pattern, int* bmGs)
{
	int patternLength = pattern.length(), lastPrefixIndex = patternLength - 1;
	//заполняем массив сдвигов на основе граней подстроки
	for (int i = patternLength - 1; i >= 0; --i)
	{
		if (isPrefix(pattern, i + 1)) //нахождение грани
			lastPrefixIndex = i + 1;
		bmGs[i] = lastPrefixIndex;
	}
	// корректируем массив сдвигов на основе суффиксов подстроки
	for (int i = 0; i < patternLength - 1; ++i)
	{
		int slen = suffixLength(pattern, i); //длина суффикса
		if (pattern[i - slen] != pattern[patternLength - 1 - slen])
			bmGs[patternLength - 1 - slen] = patternLength - 1 - i;
	}
}

bool isPrefix(string pattern, int pos)
{
	int suffixLength = pattern.length() - pos;
	for (int i = 0; i < suffixLength; i++)
	{
		if (pattern[i] != pattern[pos + i])
			return false;
	}
	return true;
}

int suffixLength(string pattern, int pos)
{
	int i, patternLength = pattern.length();
	for (i = 0; i < pos && pattern[pos - i] == pattern[patternLength - 1 - i]; i++);
	return i;
}
