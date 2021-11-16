#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long ull;

const int ALPHABET_SIZE = 256;

ull shiftAndSearch(string, string);


int main()
{
    setlocale(LC_CTYPE, "rus");
    string text, pattern;
    cout << "Введите текст: ";
    getline(cin, text, '\n');
    cout << "Введите паттерн: ";
    getline(cin, pattern, '\n');
    int res = shiftAndSearch(text, pattern);
    if (res == -1)
        cout << "Вхождение подстроки в строку не найдено\n";
    else
        cout << "Найдено вхождение подстроки в строку с индекса " << res << '\n';
    system("pause");
    return 0;
}

ull shiftAndSearch(string text, string pattern)
{
    ull M = 0, patternLength = pattern.length(), textLength = text.length();
    ull X[ALPHABET_SIZE];
    for (ull i = 0; i < ALPHABET_SIZE; ++i)
        X[i] = 0;
    for (ull i = 0; i < patternLength; ++i)
        X[pattern[i]] |= (1 << patternLength - 1 - i);
    ull one = 1 << (patternLength - 1);
    for (ull i = 0; i < textLength; ++i)
    {
        ull bitShift = (M >> 1) | one;
        M = bitShift & X[text[i]];
        if ((M & 1) == 1)
            return i - patternLength + 1;
    }
    return -1;
}
