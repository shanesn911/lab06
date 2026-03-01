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

//function declarations
string findLastWord(string line);
void cleanUp(string &word);
bool compareWords(string word1, string word2);
bool isValidLine(string line);

int main(){
    //get filename from user
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    //open file and check
    ifstream inFile(filename);
    if(!inFile.is_open()){
        cerr << "Cannot open " << filename << endl;
        exit(1);
    }

    //first pass: count valid lines
    int lineCount = 0;
    string line;
    while(getline(inFile, line)){
        if(isValidLine(line)){
            lineCount++;
        }
    }

    //handle empty poem
    if(lineCount == 0){
        cout << "No rhymes found." << endl;
        cout << "There are 0 lines in this poem." << endl;
        inFile.close();
        return 0;
    }

    //rewind and store last word of each valid line
    inFile.clear();
    inFile.seekg(0);

    string* lastWords = new string[lineCount];
    int idx = 0;

    while(getline(inFile, line)){
        if(isValidLine(line)){
            lastWords[idx] = findLastWord(line);
            idx++;
        }
    }
    inFile.close();

    //check adjacent lines for rhymes and print pairs
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
//Post: Returns true if line has at least 2 tokens containing alpha characters
bool isValidLine(string line){
    int alphaWordCount = 0;
    bool inWord = false;
    bool curWordHasAlpha = false;
    for(int i = 0; i < (int)line.size(); i++){
        if(!isspace(line[i])){
            if(isalpha(line[i])){
                curWordHasAlpha = true;
            }
            inWord = true;
        }else{
            if(inWord){
                if(curWordHasAlpha){
                    alphaWordCount++;
                }
                inWord = false;
                curWordHasAlpha = false;
            }
        }
    }
    //catch last word
    if(inWord && curWordHasAlpha){
        alphaWordCount++;
    }
    return alphaWordCount >= 2;
}

//Pre:  line is a valid line with at least 2 words
//Post: Returns the last word of the line, cleaned of non-alpha characters
//      and converted to lower-case
string findLastWord(string line){
    int end = (int)line.size() - 1;
    while(end >= 0 && isspace(line[end])){
        end--;
    }

    int start = end;
    while(start > 0 && !isspace(line[start - 1])){
        start--;
    }

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

//Pre:  word1 and word2 are cleaned strings of at least 2 characters
//Post: Returns true if the last 2 characters of word1 and word2 match
bool compareWords(string word1, string word2){
    int len1 = word1.size();
    int len2 = word2.size();
    return (word1[len1 - 2] == word2[len2 - 2]) &&
           (word1[len1 - 1] == word2[len2 - 1]);
}