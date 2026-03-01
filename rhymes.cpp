//rhymes.cpp
//Author: [Your Name]
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

//function declarations
string findLastWord(string line);
void cleanUp(string &word);
bool compareWords(string word1, string word2);

//Pre:  line is a non-blank string with at least 2 words
//Post: Returns the last word of the line, cleaned of non-alpha characters,
//      and converted to lower-case
string findLastWord(string line){
    //find the last word by scanning from the end
    int end = line.size() - 1;

    //skip any trailing whitespace
    while(end >= 0 && isspace(line[end])){
        end--;
    }

    //find the start of the last word
    int start = end;
    while(start > 0 && !isspace(line[start - 1])){
        start--;
    }

    string lastWord = line.substr(start, end - start + 1);

    //clean up and lower-case the word
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
    //compare last 2 characters
    return (word1[len1 - 2] == word2[len2 - 2]) &&
           (word1[len1 - 1] == word2[len2 - 1]);
}

int main(){
    string filename;

    //get filename from user
    cout << "Enter filename: ";
    cin >> filename;

    //open the file
    ifstream inFile(filename);
    if(!inFile.is_open()){
        cerr << "Cannot open " << filename << endl;
        exit(1);
    }

    //read all non-blank lines and extract last words
    //first pass: count lines
    int lineCount = 0;
    string line;
    while(getline(inFile, line)){
        if(!line.empty()){
            //check if line has non-whitespace characters
            bool hasContent = false;
            for(int i = 0; i < (int)line.size(); i++){
                if(!isspace(line[i])){ hasContent = true; break; }
            }
            if(hasContent) lineCount++;
        }
    }

    //rewind and collect last words
    inFile.clear();
    inFile.seekg(0);

    string* lastWords = new string[lineCount];
    int idx = 0;

    while(getline(inFile, line) && idx < lineCount){
        //skip blank lines
        bool hasContent = false;
        for(int i = 0; i < (int)line.size(); i++){
            if(!isspace(line[i])){ hasContent = true; break; }
        }
        if(hasContent){
            lastWords[idx] = findLastWord(line);
            idx++;
        }
    }
    inFile.close();

    //find and print rhyming pairs
    int rhymeCount = 0;
    for(int i = 0; i < lineCount - 1; i++){
        if(compareWords(lastWords[i], lastWords[i + 1])){
            cout << lastWords[i] << " and " << lastWords[i + 1] << endl;
            rhymeCount++;
        }
    }

    //print results
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
        cout << "There are " << lineCount << " lines in this poem, so the rhyme-line density is: " << (double)rhymeCount / lineCount << endl;
    }

    delete[] lastWords;

    return 0;
}