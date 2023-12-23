#include <iostream>
#include <cctype>
#include <Windows.h>
#include<string>

using namespace std;
int N;
void zadania(int N) {
    cout << "1. Отредактировать входной текст." << endl;
    cout << "2. Вывести на экран сначала все слова, содержащие только буквы, затем слова, содержащие только цифры, а потом слова, содержащие и буквы, и цифры. " << endl;
    cout << "3. Вывести на экран ту же последовательность, удалив из всех слов заданный набор букв и (или) цифр." << endl;
    cout << "4. Линейный поиск." << endl;
    cout << "5. Алгоритм Кнута-Мориса-Пратта." << endl;

}
//1
const int MAX_WORDS = 50;
const int MAX_CHARS = 10;

void removePr(string& input) {

    bool spaceFound = false;
    string result;

    for (char c : input) {
        if (c == ' ') {
            if (!spaceFound) {
                result += c;
                spaceFound = true;
            }
        }
        else {
            result += c;
            spaceFound = false;
        }
    }

    input = result;
}

void removeZn(string& input) {
    for (size_t i = 0; i < input.length(); ++i) {
        if (ispunct(input[i])) {
            size_t j = i + 1;
            while (j < input.length() && ispunct(input[j])) {
                input.erase(j, 1);
            }
        }
    }
}

void registr(string& input) {
    for (char& c : input) {
        c = tolower(c);
    }
}
//2
bool isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

void sortWordsByType(string& text) {
    string word;
    string letterWords, digitWords, mixedWords;

    string currentWord;
    for (char c : text) {
        if (c == ' ') {
            bool hasLetter = false;
            bool hasDigit = false;

            for (char w : currentWord) {
                if (isLetter(w)) {
                    hasLetter = true;
                }
                else if (isDigit(w)) {
                    hasDigit = true;
                }
            }

            if (hasLetter && !hasDigit) {
                letterWords += currentWord + " ";
            }
            else if (!hasLetter && hasDigit) {
                digitWords += currentWord + " ";
            }
            else {
                mixedWords += currentWord + " ";
            }

            currentWord = "";
        }
        else {
            currentWord += c;
        }
    }

    // Проверка последнего слова
    bool hasLetter = false;
    bool hasDigit = false;

    for (char w : currentWord) {
        if (isLetter(w)) {
            hasLetter = true;
        }
        else if (isDigit(w)) {
            hasDigit = true;
        }
    }

    if (hasLetter && !hasDigit) {
        letterWords += currentWord + " ";
    }
    else if (!hasLetter && hasDigit) {
        digitWords += currentWord + " ";
    }
    else {
        mixedWords += currentWord + " ";
    }

    cout << "Слова содержащие только буквы:" << endl << letterWords << endl;
    cout << "Слова содержащие только цифры:" << endl << digitWords << endl;
    cout << "Слова содержащие и буквы и цифры:" << endl << mixedWords << endl;
}


//3
void removeCharacters(string& input, const string& charactersToRemove) {

    string result = "";
    for (char c : input) {
        bool removeChar = false;
        for (char remove : charactersToRemove) {
            if (c == remove) {
                removeChar = true;
                break;
            }
        }
        if (!removeChar) {
            result += c;
        }
    }
    input = result;

}

//4
void linearSearch(string& text, string& pattern) {
    int n = text.length();
    int m = pattern.length();
    bool found = false;

    for (int i = 0; i <= n - m; ++i) {
        int j;
        for (j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == m) {
            cout << "Подстрока найдена на позиции: " << i << endl;
        }
    }
    if (!found) {
        cout << "Подстрока не найдена." << endl;
    }
}

//5
void computeLPS(string& pattern, int* lps) {
    int m = pattern.length();
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
void KMP(string& text, string& pattern) {
    int n = text.length();
    int m = pattern.length();
    int* lps = new int[m];
    int* pat = new int[m];

    bool found = false;

    for (int i = 0; i < m; ++i) {
        pat[i] = pattern[i];
    }

    computeLPS(pattern, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (pat[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            cout << "Подстрока найдена на позиции: " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < n && pat[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    if (!found) {
        cout << "Подстрока не найдена." << endl;
    }
    delete[] lps;
    delete[] pat;
}

int main() {
    setlocale(0, "");

    string input;

    int choice;
    bool p = true;
    cout << "Введите последовательность слов: " << endl;
    getline(cin, input);

    Sleep(1000);
    while (p) {
        zadania(N);
        cout << "Выберите номер задания:" << endl;
        cin >> choice;
        system("cls");
        switch (choice) {
        case 1:
        {
            srand(time(NULL));
            removePr(input);
            removeZn(input);
            registr(input);

            cout << "Строка после удаления повторяющихся пробелов и знаков:" << endl;
            cout << input << endl;
        }
        cout << endl;
        break;
        case 2:
        {srand(time(NULL));
        sortWordsByType(input);
        }
        break;
        case 3:
        {srand(time(NULL));
        cin.ignore();
        string charactersToRemove;
        cout << "Введите набор букв или цифр для удаления: " << endl;
        getline(cin, charactersToRemove);
        removeCharacters(input, charactersToRemove);

        cout << "Результат: " << input << endl;

        }
        break;
        case 4:
        {
            srand(time(NULL));
            cin.ignore();
            string pattern;
            cout << "Введите подстроку для поиска: ";
            getline(cin, pattern);

            linearSearch(input, pattern);
        }
        break;
        case 5:
        {
            srand(time(NULL));
            cin.ignore();
            string  pattern;

            cout << "Введите подстроку для поиска: ";
            getline(std::cin, pattern);

            KMP(input, pattern);

        }
        break;
        system("pause");
        system("cls");
        }
    }
}