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

