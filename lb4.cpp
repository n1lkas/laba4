#include <iostream>
#include <cctype>
#include <Windows.h>
#include<string>

using namespace std;
int N;
void zadania(int N) {
    cout << "1. ��������������� ������� �����." << endl;
    cout << "2. ������� �� ����� ������� ��� �����, ���������� ������ �����, ����� �����, ���������� ������ �����, � ����� �����, ���������� � �����, � �����. " << endl;
    cout << "3. ������� �� ����� �� �� ������������������, ������ �� ���� ���� �������� ����� ���� � (���) ����." << endl;
    cout << "4. �������� �����." << endl;
    cout << "5. �������� �����-������-������." << endl;

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

    // �������� ���������� �����
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

    cout << "����� ���������� ������ �����:" << endl << letterWords << endl;
    cout << "����� ���������� ������ �����:" << endl << digitWords << endl;
    cout << "����� ���������� � ����� � �����:" << endl << mixedWords << endl;
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
            cout << "��������� ������� �� �������: " << i << endl;
        }
    }
    if (!found) {
        cout << "��������� �� �������." << endl;
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
            cout << "��������� ������� �� �������: " << i - j << endl;
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
        cout << "��������� �� �������." << endl;
    }
    delete[] lps;
    delete[] pat;
}

int main() {
    setlocale(0, "");

    string input;

    int choice;
    bool p = true;
    cout << "������� ������������������ ����: " << endl;
    getline(cin, input);

    Sleep(1000);
    while (p) {
        zadania(N);
        cout << "�������� ����� �������:" << endl;
        cin >> choice;
        system("cls");
        switch (choice) {
        case 1:
        {
            srand(time(NULL));
            removePr(input);
            removeZn(input);
            registr(input);

            cout << "������ ����� �������� ������������� �������� � ������:" << endl;
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
        cout << "������� ����� ���� ��� ���� ��� ��������: " << endl;
        getline(cin, charactersToRemove);
        removeCharacters(input, charactersToRemove);

        cout << "���������: " << input << endl;

        }
        break;
        case 4:
        {
            srand(time(NULL));
            cin.ignore();
            string pattern;
            cout << "������� ��������� ��� ������: ";
            getline(cin, pattern);

            linearSearch(input, pattern);
        }
        break;
        case 5:
        {
            srand(time(NULL));
            cin.ignore();
            string  pattern;

            cout << "������� ��������� ��� ������: ";
            getline(std::cin, pattern);

            KMP(input, pattern);

        }
        break;
        system("pause");
        system("cls");
        }
    }
}