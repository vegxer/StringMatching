#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long ull;

ull Hash(string, const ull, const ull);
ull pow(ull, int, const ull, const ull);
int RabinKarpStringSearch(string, string);


int main()
{
	setlocale(LC_CTYPE, "rus");
	string text, pattern;
	cout << "Введите текст: ";
	getline(cin, text, '\n');
	cout << "Введите паттерн: ";
	getline(cin, pattern, '\n');
	int res = RabinKarpStringSearch(text, pattern);
	if (res == -1)
		cout << "Вхождений шаблона в текст не найдено\n";
	else
		cout << "Найдено вхождение шаблона в текст с индекса " << res << '\n';
	system("pause");
	return 0;
}

ull pow(ull num, int deg, const ull x, const ull q)
{
	for (int i = 0; i < deg; ++i)
		num = (num * x) % q;
	return num;
}

ull Hash(string str, const ull x, const ull q)
{
	ull hash = str[0];
	int length = str.length();
	for (int i = 1; i < length; ++i)
		hash = (hash * x + str[i]) % q;
	return hash;
}

int RabinKarpStringSearch(string str, string pattern)
{
	const ull q = 2362156885718849, x = 31;
	int strLength = str.length(), patternLength = pattern.length();
	ull Xm = 1;
	Xm = pow(Xm, patternLength - 1, x, q);
	ull patternHash = Hash(pattern, x, q);
	ull strHash = Hash(str.substr(0, patternLength), x, q);
	for (int i = 0; i <= strLength - patternLength; ++i)
	{
		if (patternHash == strHash && pattern == str.substr(i, patternLength))
			return i;
		else
			strHash = ((strHash - str[i] * Xm) * x + str[i + patternLength]) % q;
	}
	return -1;
}
