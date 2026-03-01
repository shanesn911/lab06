#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

string findLastWord(string line);
void cleanUp(string &word);
bool compareWords(string word1, string word2);

int main(){
	string filename;
	cout << "Enter filename: ";
	cin >> filename;

	ifstream inFile(filename);
	if(!inFile.is_open()){
		cerr << "Cannot open " << filename << endl;
		exit(1);
	}

	// Count total lines including blanks
	int totalLines = 0;
	string line;
	while(getline(inFile, line)){
		totalLines++;
	}
	inFile.close();

	if(totalLines == 0){
		cout << "No rhymes found." << endl;
		cout << "There are 0 lines in this poem." << endl;
		return 0;
	}

	// Re-open to fill array with last words
	inFile.open(filename);
	string* lastWords = new string[totalLines];
	int idx = 0;
	while(getline(inFile, line)){
		bool hasContent = false;
		for(int i = 0; i < (int)line.length(); i++){
			if(!isspace(line[i])){
				hasContent = true;
				break;
			}
		}
		// Store last word if line isn't empty
		if(hasContent){
			lastWords[idx] = findLastWord(line);
		}else{
			lastWords[idx] = "";
		}
		idx++;
	}
	inFile.close();

	// Check adjacent pairs for rhymes
	int rhymeCount = 0;
	for(int i = 0; i < totalLines - 1; i++){
		if(lastWords[i] != "" && lastWords[i + 1] != ""){
			if(compareWords(lastWords[i], lastWords[i + 1])){
				cout << lastWords[i] << " and " << lastWords[i + 1] << endl;
				rhymeCount++;
			}
		}
	}

	// Final stats output
	if(rhymeCount == 0){
		cout << "No rhymes found." << endl;
		cout << "There are " << totalLines << " lines in this poem." << endl;
	}else{
		if(rhymeCount == 1){
			cout << "There is 1 pair of rhyming words." << endl;
		}else{
			cout << "There are " << rhymeCount << " pairs of rhyming words." << endl;
		}
		cout << fixed << setprecision(2);
		cout << "There are " << totalLines << " lines in this poem, so the rhyme-line density is: "
			 << (double)rhymeCount / totalLines << endl;
	}

	delete[] lastWords;
	return 0;
}

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

void cleanUp(string &word){
	string result = "";
	for(int i = 0; i < (int)word.size(); i++){
		char c = word[i];
		// Keep only letters and lowercase them
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
			result += (char)tolower(c);
		}
	}
	word = result;
}

bool compareWords(string word1, string word2){
	if(word1.length() < 2 || word2.length() < 2) return false;
	int len1 = word1.size();
	int len2 = word2.size();
	// Check if last two characters match
	return (word1[len1 - 2] == word2[len2 - 2]) && (word1[len1 - 1] == word2[len2 - 1]);
}