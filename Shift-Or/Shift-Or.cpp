#include <iostream>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 256;

typedef unsigned long long ull;

ull shiftOrSearch(string, string);


int main()
{
    setlocale(LC_CTYPE, "rus");
    string text, pattern;
    cout << "Введите текст: ";
    getline(cin, text, '\n');
    cout << "Введите паттерн: ";
    getline(cin, pattern, '\n');
    int res = shiftOrSearch(text, pattern);
    if (res == -1)
        cout << "Вхождение подстроки в строку не найдено\n";
    else
        cout << "Найдено вхождение подстроки в строку с индекса " << res << '\n';
    system("pause");
    return 0;
}

ull shiftOrSearch(string text, string pattern)
{
    ull patternLength = pattern.length(), max = pow(2, patternLength) - 1, M = max, textLength = text.length();
    ull X[ALPHABET_SIZE];
    for (ull i = 0; i < ALPHABET_SIZE; ++i)
        X[i] = 0;
    for (ull i = 0; i < patternLength; ++i)
        X[pattern[i]] |= (1 << (patternLength - 1 - i));
    for (ull i = 0; i < textLength; ++i)
    {
        ull bitShift = M >> 1;
        M = bitShift | (max - X[text[i]]);
        if (((max - M) & 1) == 1)
            return i - patternLength + 1;
    }
    return -1;
}
