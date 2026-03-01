//rhymes.cpp
//Author: Shane Nguyen
//Date: February 2026
//Description: Reads a poem from a file, extracts the last word of each line,
//             and checks adjacent lines for rhymes (matching last 2 letters).
//             Prints rhyming pairs, total line count, and rhyme-line density.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

//FUNCTION DECLARATIONS: YOU MUST DEFINE AND USE THESE (do not remove):
//      You can declare/define other functions if you like as well,
//      but you must use the 3 functions below.
//See lab description for more on these functions.

string findLastWord(string line);
void cleanUp(string &word);
bool compareWords(string word1, string word2);
bool hasTwoWords(string line);
void stripCR(string &line);

int main(){
    //create input stream object and get filename from user
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inFile(filename);
    if(!inFile.is_open()){
        cerr << "Cannot open " << filename << endl;
        exit(1);
    }

    //first pass: count lines that have at least 2 words
    int lineCount = 0;
    string line;
    while(getline(inFile, line)){
        stripCR(line);
        if(hasTwoWords(line)) lineCount++;
    }

    //handle empty poem
    if(lineCount == 0){
        cout << "No rhymes found." << endl;
        cout << "There are 0 lines in this poem." << endl;
        inFile.close();
        return 0;
    }

    //rewind and collect last words into dynamic array
    inFile.clear();
    inFile.seekg(0);

    string* lastWords = new string[lineCount];
    int idx = 0;

    while(getline(inFile, line) && idx < lineCount){
        stripCR(line);
        if(hasTwoWords(line)){
            lastWords[idx] = findLastWord(line);
            idx++;
        }
    }
    inFile.close();

    //find and print rhyming adjacent pairs
    int rhymeCount = 0;
    for(int i = 0; i < lineCount - 1; i++){
        if(compareWords(lastWords[i], lastWords[i + 1])){
            cout << lastWords[i] << " and " << lastWords[i + 1] << endl;
            rhymeCount++;
        }
    }

    //print summary
    if(rhymeCount == 0){
        cout << "No rhymes found." << endl;
        cout << "There are " << lineCount << " lines in this poem." << endl;
    }else{
        if(rhymeCount == 1){
            cout << "There is 1 pair of rhyming words." << endl;
        }else{
            cout << "There are " << rhymeCount << " pairs of rhyming words." << endl;
        }
        cout << fixed << setprecision(2);
        cout << "There are " << lineCount << " lines in this poem, so the rhyme-line density is: "
             << (double)rhymeCount / lineCount << endl;
    }

    delete[] lastWords;

    return 0;
}

//Pre:  line is any string
//Post: Removes trailing carriage return if present (handles Windows line endings)
void stripCR(string &line){
    if(!line.empty() && line[line.size() - 1] == '\r'){
        line.erase(line.size() - 1);
    }
}

//Pre:  line is any string
//Post: Returns true if line contains at least 2 words
bool hasTwoWords(string line){
    int wordCount = 0;
    bool inWord = false;
    for(int i = 0; i < (int)line.size(); i++){
        if(!isspace(line[i]) && !inWord){
            inWord = true;
            wordCount++;
        }else if(isspace(line[i])){
            inWord = false;
        }
    }
    return wordCount >= 2;
}

//Pre:  line is a valid line with at least 2 words
//Post: Returns the last word of the line, cleaned of non-alpha characters,
//      and converted to lower-case
string findLastWord(string line){
    int end = (int)line.size() - 1;
    while(end >= 0 && isspace(line[end])) end--;

    int start = end;
    while(start > 0 && !isspace(line[start - 1])) start--;

    string lastWord = line.substr(start, end - start + 1);
    cleanUp(lastWord);
    return lastWord;
}

//Pre:  word is any string
//Post: word has all non-alphabetical characters removed and is lower-cased
void cleanUp(string &word){
    string result = "";
    for(int i = 0; i < (int)word.size(); i++){
        if(isalpha(word[i])){
            result += tolower(word[i]);
        }
    }
    word = result;
}

//Pre:  word1 and word2 are strings of at least 2 characters (after clean-up)
//Post: Returns true if the last 2 characters of word1 and word2 match,
//      false otherwise
bool compareWords(string word1, string word2){
    int len1 = word1.size();
    int len2 = word2.size();
    return (word1[len1 - 2] == word2[len2 - 2]) &&
           (word1[len1 - 1] == word2[len2 - 1]);
}