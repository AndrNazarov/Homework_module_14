#include "trie.h"
#include <windows.h>
#include "string.h"
#include <conio.h> 
#include <iostream>

const int GREEN = 10;
const int GRAY = 7;

void backspace(int count) {
	for (int i = 0; i < count; i++)
		std::cout << '\b' << " " << '\b';
}

bool symbolAcceptable(char symbol) {
	return (symbol <= 'z' && symbol >= 'a');
}

int main()
{
	
	Trie dictionary;
	TrieNode* root = dictionary.getRoot();
	std::string keys[] = { "As", "final", "task", "you", "need", "to", "implement", "program", "that", "performs", "autocompletion",
		"of", "the", "entered", "word", "according", "initially", "specified", "dictionary"	};

	int n = sizeof(keys) / sizeof(keys[0]);
	for (int i = 0; i < n; i++)
		dictionary.insert(root, keys[i]);

	std::cout << "Enter the text, Spacebar - for autocompletion, ESC - for exit" << std::endl;

	bool typing = true; 
	std::string word; 
	std::string restOfWord; 
	bool autocompletionAccepted = true; 
	char buttonPressed;
	
	while (typing) {

		buttonPressed = _getch(); 
		{
			switch (buttonPressed)
			{
			case 27: 
				typing = false;
				break;
			case 8: 
				if (word.length() > 0)
				{
					backspace(1);
					word.erase(word.end() - 1);
					restOfWord = "";
				}
				break;
			case 32: 
				if (restOfWord.length() > 0) 
				{
					backspace(restOfWord.length());
					std::cout << restOfWord;
				}
				word = "";
				restOfWord = "";
				autocompletionAccepted = true;
				std::cout << " ";
				break;

			default:
				
				if (autocompletionAccepted == false)
				{
					if (restOfWord.length() > 0) 
					{
						backspace(restOfWord.length());
						word.erase(word.length() - restOfWord.length(), restOfWord.length());
					}
				}

				word += buttonPressed;
				std::cout << buttonPressed;
				restOfWord = dictionary.completeWordByPrefix(word);

				if (restOfWord.length() > 0) 
				{
					autocompletionAccepted = false;
					word += restOfWord;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
					std::cout << restOfWord;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
				}
				break;
			}
		}
	}
	return 0;
}