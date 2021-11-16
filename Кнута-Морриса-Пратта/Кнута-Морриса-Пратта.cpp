#include <iostream>
#include <string>

using namespace std;

int* effPrefFunc(string);
int KMP(int*, string, string);


int main()
{
	setlocale(LC_CTYPE, "rus");
	string text, pattern;
	cout << "Введите текст: ";
	getline(cin, text, '\n');
	cout << "Введите паттерн: ";
	getline(cin, pattern, '\n');
	int res = KMP(effPrefFunc(pattern), pattern, text + '#');
	if (res == -1)
		cout << "Вхождений подстроки не найдено\n";
	else
		cout << "Найдено вхождение подстроки в строку с индекса " << res << '\n';
	system("pause");
	return 0;
}

int KMP(int* pi, string pattern, string text)
{
	int patternLength = pattern.length(), textLength = text.length(), i = 0;
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
			i = j - pi[j - i - 1];
		}
	}
	return -1;
}

int* effPrefFunc(string str)
{
	int strLength = str.length();
	int* pi = new int[strLength];
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
	return pi;
}
