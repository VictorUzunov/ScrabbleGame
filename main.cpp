/**
*
* Solution to course project 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Victor Uzunov
* @idnumber 0MI0600213
* @compiler GCC
*
* <file with helper functions>
*
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const char *const DICTIONARY_NAME = "dictionary.txt";

bool correctInput(string input) {
    if (input.size() > 1) {
        return false;
    }
    if (input[0] > '0' && input[0] < '5') {
        return true;
    } else {
        return false;
    }
}

//Read the file and put the words in the vector.
bool readDictionary(vector<string> &words) {
    fstream file(DICTIONARY_NAME, ios::in);
    if (!file.is_open()) {
        return false;
    }

    while (!file.eof()) {
        string line;
        getline(file, line);
        if (!line.empty()) {
            words.push_back(line);
        }
    }
    file.close();
    return true;
}
char getRandomVowel() {
    int randomNumber = rand() % 5;
    char vowel;
    switch (randomNumber) {
        case 0: {
            vowel = 'a';
            break;
        }
        case 1: {
            vowel = 'e';
            break;
        }
        case 2: {
            vowel = 'o';
            break;
        }
        case 3: {
            vowel = 'i';
            break;
        }
        case 4: {
            vowel = 'u';
            break;
        }
    }
    return vowel;
}

//Check if the word is with available letters for the round
bool correctWordForTheRound(string availableLetters, const string yourWord) {
    for (int i = 0; i < yourWord.size(); i++) {
        bool correctWord = false;
        for (int j = 0; j < availableLetters.size(); j++) {
            if (availableLetters[j] == yourWord[i]) {
                availableLetters[j] = '0';
                correctWord = true;
                break;
            }
        }
        if (!correctWord) {
            return false;
        }
    }
    return true;
}

