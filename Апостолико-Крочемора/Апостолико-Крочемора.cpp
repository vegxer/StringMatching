#include <iostream>
#include <string>

using namespace std;

void prefFunc(string, int*);
int AP_CR(string, string);


int main()
{
	setlocale(LC_CTYPE, "rus");
	string text, pattern;
	cout << "Введите текст: ";
	getline(cin, text, '\n');
	cout << "Введите паттерн: ";
	getline(cin, pattern, '\n');
	int res = AP_CR(pattern, text);
	if (res == -1)
		cout << "Вхождений подстроки не найдено\n";
	else
		cout << "Найдено вхождение подстроки в строку с индекса " << res << '\n';
	system("pause");
	return 0;
}

int AP_CR(string pattern, string text)
{
	int textLength = text.length(), patternLength = pattern.length(), L;
	int* pi = new int[patternLength];
	prefFunc(pattern, pi);
	for (L = 1; pattern[L - 1] == pattern[L]; ++L);
	if (L == patternLength)
		L = 0;
	int i = L, j = 0, k = 0;
	while (j <= textLength - patternLength)
	{
		while (i < patternLength && pattern[i] == text[i + j])
			++i;
		if (i >= patternLength)
		{
			while (k < L && pattern[k] == text[j + k])
				++k;
			if (k >= L)
				return j;
		}
		j += (i - pi[i]);
		if (i == L)
			k = max(0, k - 1);
		else
		{
			if (pi[i] <= L)
			{
				k = max(0, pi[i]);
				i = L;
			}
			else
			{
				k = L;
				i = pi[i];
			}
		}
	}
	return -1;
}

void prefFunc(string str, int* pi)
{
	int strLength = str.length();
	int i = 0, j;
	j = pi[0] = -1;
	while (i < strLength)
	{
		while (j > -1 && str[i] != str[j])
			j = pi[j];
		++j, ++i;
		if (str[i] == str[j])
			pi[i] = pi[j];
		else
			pi[i] = j;
	}
}
