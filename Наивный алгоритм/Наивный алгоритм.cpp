#include <iostream>
#include <string>

using namespace std;

int naiveSearch(string, string);

int main()
{
    setlocale(LC_CTYPE, "rus");
    string text, pattern;
    cout << "Введите текст: ";
    getline(cin, text, '\n');
    cout << "Введите паттерн: ";
    getline(cin, pattern, '\n');
    int res = naiveSearch(text, pattern);
    if (res == -1)
        cout << "Вхождений подстроки в строке не найдено\n";
    else
        cout << "Найдено вхождение подстроки в строку с индекса " << res << '\n';
    system("pause");
    return 0;
}

int naiveSearch(string text, string pattern)
{
    int textLength = text.length(), patternLength = pattern.length(), j;
    for (int i = 0; i <= textLength - patternLength; ++i)
    {
        for (j = 0; j < patternLength && pattern[j] == text[j + i]; ++j);
        if (j == patternLength)
            return i;
    }
    return -1;
}
