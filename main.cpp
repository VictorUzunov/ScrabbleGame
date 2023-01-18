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
//Check if the word is in the dictionary
bool wordExistsInDictionary(vector<string> &words, const string &wordToFind) {
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == wordToFind) {
            return true;
        }
    }
    return false;
}

//Check if the word is valid in order to be added in the dictionary
bool validNewWord(const string &newWord) {
    for (int i = 0; i < newWord.size(); i++) {
        if (newWord[i] < 'a' || newWord[i] > 'z') {
            return false;
        }
    }
    return true;
}
//Fill the file with the words from the vector
void saveDictionary(vector<string> &words) {
    //Open the file and delete everything from it
    fstream file(DICTIONARY_NAME, ios::out | ios::trunc);
    for (int i = 0; i < words.size(); i++) {
        file << words[i] << endl;
    }
    file.close();
}

void addWordToDictionary(vector<string> &words, const string &wordToAdd) {
    words.push_back(wordToAdd);
    saveDictionary(words);
}

void settings(int &lettersInEachRound, int &rounds) {

    cout << "Settings:" << endl;
    cout << "Here, you can change the number of the rounds and the number of the letters in each round" << endl;
    cout << "Insert the number of letters in each round: ";
    cin >> lettersInEachRound;

    cout << "Insert the number of rounds in each game: ";
    cin >> rounds;

}
//Change one letter and randomly get a new one
void changeAvailableLetter(string &availableLetters, const char letter) {
    for (int i = 0; i < availableLetters.size(); i++) {
        if (availableLetters[i] == letter) {
            int random = rand() % 26;
            int newLetter = 'a' + random;
            availableLetters[i] = (char) newLetter;
            break;
        }
    }
}

//The Random Letter Generator is forced to give at least two vowels
void randomLettersGenerator(string &availableLetters, int lettersInEachRound) {
    for (int i = 0; i < lettersInEachRound; i++) {
        if ((i + 1) % 4 != 0) {
            int random = rand() % 26;
            int letter = 'a' + random;
            availableLetters += (char) letter;
            cout << (char) letter << " ";
        } else {
            //Random vowel
            availableLetters += getRandomVowel();
            cout << availableLetters[i] << " ";
        }
    }
    cout << endl;
}

//Print the available letters
void letters(string &availableLetters) {
    for (int i = 0; i < availableLetters.size(); i++) {
        cout << availableLetters[i] << " ";
    }
    cout << endl;
}
void startTheGame(int lettersInEachRound, int rounds, int &points, vector<string> &words) {
    int round = 0;
    while (round != rounds) {
        cout << "Available letters in round " << round + 1 << " are:" << endl;
        string availableLetters;
        randomLettersGenerator(availableLetters, lettersInEachRound);
        cout << "1.Change one of the letters(you will lose 1 point)" << endl;
        cout << "2.Skip the round and get new letters" << endl;
        string yourWord;
        bool again = true;
        string option1 = "1";
        string option2 = "2";
        do {
            cin >> yourWord;
            //Check if the word is valid and whether it is in the dictionary
            if (correctWordForTheRound(availableLetters, yourWord) && wordExistsInDictionary(words, yourWord)) {
                points += (int) yourWord.size();
                again = false;
                if (round + 1 != rounds) {
                    cout << "Your points so far are:" << points << endl;
                } else {
                    cout << "Your total points are:" << points << endl;
                }
            }
                //The action if you want to change one letter from the available
            else if (yourWord == option1) {
                points--;
                cout << "Enter the letter from the available ones that you want to change:";
                char letter;
                cin >> letter;
                changeAvailableLetter(availableLetters, letter);
                cout << "Available letters in round " << round + 1 << " are:" << endl;
                letters(availableLetters);
                cout << "1.Change one of the letters(you will lose 1 point)" << endl;
                cout << "2.Skip the round and get new letters" << endl;
            }
                //Skip the round
            else if (yourWord == option2) {
                break;
            }
                //If you have entered invalid word or word that is not in the dictionary
            else {
                cout << "Invalid word. Try again with: ";
                letters(availableLetters);
                cout << "1.Change one of the letters(you will lose 1 point)" << endl;
                cout << "2.Skip the round and get new letters" << endl;
            }
        } while (again);
        round++;
    }
}

int main() {
    //Information about the game
    cout << "Welcome to the Scrabble Game" << endl;
    cout << "Before you start the game read the instructions carefully:" << endl;
    cout << "In each round are generated letters and you should make a word." << endl;
    cout << "For correct word you receive as many points as the number of" << endl;
    cout << "letters int it. If you cannot do it you can change one of the" << endl;
    cout << "letters and get a new one but every time you will lose one point." << endl;
    cout << "You have also the option to skip the whole round and get 10 new letters." << endl;
    cout << "After the last round you will see your total points." << endl;
    cout << "Good luck!" << endl;
    int points = 0;
    int lettersInEachRound = 10;
    int rounds = 10;
    vector<string> words;
    bool success = readDictionary(words);
    if (!success) {
        cerr << "The file could not be opened";
        return 1;
    }
    readDictionary(words);
    bool keepGoing = true;
    //Returning to menu cycle
    while (keepGoing) {
        cout << endl;
        cout << "MENU:" << endl;
        cout << "1.Start the game" << endl;
        cout << "2.Settings" << endl;
        cout << "3.Add new word to the Dictionary" << endl;
        cout << "4.Exit" << endl;
        cout << "Input 1, 2, 3 or 4:";
        string input;
        do {
            cin >> input;
            if (!correctInput(input) || !cin.good()) {
                cout << "Incorrect input, try again:" << endl;
            }
        } while (!correctInput(input));
        switch (input[0]) {
            //Start the game
            case '1': {
                startTheGame(lettersInEachRound, rounds, points, words);
            }
                break;
                //Settings
            case '2': {
                settings(lettersInEachRound, rounds);
            }
                break;
                //Add new word
            case '3': {
                cout << "You can add a new word in the dictionary." << endl;
                cout << "Input your word:";
                string newWord;
                cin >> newWord;
                if (validNewWord(newWord)) {
                    cout << "Your word was added" << endl;
                    addWordToDictionary(words, newWord);
                } else {
                    cout << "This word does not exist!";
                    cout << endl;
                }
            }
                break;
                //Exit
            case '4': {
                keepGoing = false;
            }
                break;
            default:
                break;
        }
    }
    return 0;
}