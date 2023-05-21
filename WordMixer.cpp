#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

void generateWordList(const string& file1, const string& file2, const string& output_file) {
    vector<string> words1;
    vector<string> words2;

    ifstream f1(file1);
    string word;
    while (getline(f1, word)) {
        words1.push_back(word);
    }
    f1.close();

    ifstream f2(file2);
    while (getline(f2, word)) {
        words2.push_back(word);
    }
    f2.close();

    int totalIterations = words1.size() * words2.size();
    int currentIteration = 0;
    int previousProgress = 0;

    ofstream output(output_file);
    for (const auto& word1 : words1) {
        for (const auto& word2 : words2) {
            output << word1 + word2 << '\n';
            currentIteration++;
            int progress = (currentIteration * 100) / totalIterations;
            if (progress > previousProgress) {
                previousProgress = progress;
                cout << "Progress: " << progress << "%\r";
                cout.flush();
            }
        }
    }
    output.close();
}

int main() {
    SetConsoleTitle(L"WordMixer");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
    string file1 = "wordlist_a.txt";
    string file2 = "wordlist_b.txt";
    string output_file = "wordlist.txt";
    generateWordList(file1, file2, output_file);
    cout << "Done!\n";
    system("pause");
    return 0;
}