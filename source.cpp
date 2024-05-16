#include"TRIES.h"
#include<iostream>
using namespace std;
Node::Node(string mean)
{
	this->mean = mean;
	letter.clear();
	for (int i = 0; i < 26; i++)
	{
		letter.push_back(NULL);
	}
}
Node::~Node()
{
	this->mean = " ";
	letter.clear();         //Clear vector
}
void Tries::Display(Node* curr, int i, string extraWord = "")
{
	if (isEmpty())
	{
		cout << "Empty Dictationary" << endl;
		return;
	}
	if (curr == NULL)
	{
		return;
	}
	extraWord += char(i + 97);
	if (curr->mean != " ")
	{
		extraWord[0] = ' ';
		cout << extraWord << "  " << "" << curr->mean << endl;
	}
	for (int x = 0; x < 26; x++)
	{
		Display(curr->letter[x], x, extraWord);
	}
}
void Tries::Search(Node* curr, string word, string& meaning)
{
	for (int i = 0; i < word.length(); i++)
	{
		int index = int(word[i]) - 97;
		if (index < 0 or index >= 26)
		{
			cout << "Invalid Word" << endl;
			return;
		}
		if (curr == NULL)
		{
			return;
		}
		if (curr->letter[index] == NULL)
		{
			return;
		}
		else
		{
			curr = curr->letter[index];
		}
	}
	meaning = curr->mean;
}
void Tries::SuggestWord(Node* curr, string word, string& meaning)
{
	for (int i = 0; i < word.length(); i++)
	{
		int index = int(word[i]) - 97;
		if (index < 0 or index >= 26)
		{
			cout << "Invalid Word" << endl;
			return;
		}
		if (curr == NULL)
		{
			return;
		}
		if (curr->letter[index] == NULL)
		{
			return;
		}
		else
		{
			curr = curr->letter[index];
		}
	}
	string extraWord = "a" + word;
	for (int i = 0; i < 26; i++)
	{
		if (curr)
		{
			Display(curr->letter[i], i, extraWord);
		}
	}
}
bool Tries::DeleteVector(vector<Node*> letter)
{
	for (int i = 0; i < letter.size(); i++)
	{

		if (letter[i] != NULL)
		{
			return false;
		}
	}
	return true;
}
void Tries::Delete(Node*& curr, string word, int i, bool& isDeleted, bool& endFound)
{
	if (curr == NULL || endFound == true)
	{
		return;
	}
	if (i >= word.length() || word[i] == '\0')
	{
		if (curr->mean != " ")
		{
			cout << " " << " " << curr->mean;
			isDeleted = true;
		}
		curr->mean = "\0";
		if (DeleteVector(curr->letter))
		{
			delete curr;
			curr = NULL;
		}
		endFound = true;
		return;
	}
	int index = int(word[i]) - 97;
	cout << char(index + 97);
	if (index < 0 or index >= 26)
	{
		cout << "Invalid Word" << endl;
		return;
	}
	if (curr->letter[index] == NULL)
	{
		return;
	}
	else
	{
		Delete(curr->letter[index], word, i + 1, isDeleted, endFound);
	}
	if (curr->mean != "\0" && isDeleted == true)
	{
		endFound = true;
		return;
	}
	if (isDeleted == true && DeleteVector(curr->letter))
	{
		delete curr;
		curr = NULL;
	}
}
void Tries::DeleteAll(Node*& curr, int i)               //Delete Complete Dictionary
{
	if (curr == NULL)
	{
		return;
	}
	for (int x = 0; x < 26; x++)
	{
		if (curr)
		{
			DeleteAll(curr->letter[x], x);
			if (DeleteVector(curr->letter))
			{
				delete curr;
				curr = NULL;
			}
		}
	}
}
bool Tries::checkWord(string word)
{
	return true;
}
Tries::Tries()
{
	root = NULL;
}
Tries::~Tries()
{
	deleteAll();
}
void Tries::deleteAll()
{
	DeleteAll(root, 0);
	cout << endl << "Memory free" << endl;
}
void Tries::insert(string word, string meaning)
{
	if (!(checkWord(word)))
	{
		cout << endl << "Invalid Word" << endl;
		return;
	}
	if (root == NULL)
	{
		root = new Node("\0");
	}
	Node* curr = root;
	cout << endl;
	cout << " Insertion : ";
	for (int i = 0; i < word.length(); i++)
	{
		int index = int(word[i]) - 97; // 4 1 9
		cout << char(index + 97); // 101 98 106 |
		if (index < 0 or index >= 26)
		{
			cout << endl << "Invalid Word" << endl;
			return;
		}
		if (curr->letter[index] == NULL)
		{
			curr = curr->letter[index] = new Node("\0");            //Allocate memory
		}
		else
		{
			curr = curr->letter[index];
		}
	}
	curr->mean = meaning;
	cout << "   " << curr->mean << endl;
}
bool Tries::search(string word)
{
	string meaning = "\0";
	Search(root, word, meaning);

	if (meaning != "\0")
	{
		cout << "Word : " << word << endl << "Meaning : " << meaning << endl;
		return true;
	}
	else
	{
		cout << "Not Found!";
		return false;
	}
}
void Tries::display()
{
	cout << endl << "Dictationary :" << endl;

	Display(root, 0);
	cout << endl;
}
bool Tries::isEmpty()
{
	return root == NULL;
}
bool Tries::deleteWord(string word)
{
	bool isDeleted = false, endFound = false;
	cout << "[";
	Delete(root, word, 0, isDeleted, endFound);

	if (isDeleted)
	{
		cout << "\tDeleted]";
	}
	else
	{
		cout << " Not Deleted]\n";
	}
	return isDeleted;
}
void Tries::suggestion(string word)
{
	cout << "Suggestions: " << word << endl;
	string meaning = "\0";
	SuggestWord(root, word, meaning);
	cout << endl;
}
void Tries::importDictionary(string fileName)
{
	ifstream dictionaryFile(fileName);
	if (!(dictionaryFile))
	{
		cout << endl << "File Not Exist ! " << endl;
		return;
	}
	string line;
	while (getline(dictionaryFile, line))
	{
		string word = "", meaning = "";
		bool wordDone = false;
		for (long i = 0; i < line.size(); i++)
		{
			if (wordDone == false)
			{
				if ((int(line[i]) >= 97 && int(line[i]) <= 122) || (int(line[i]) >= 65 && int(line[i] <= 90)))
				{
					word += line[i];
				}
				else
				{
					wordDone = true;
				}
			}
			else if (wordDone == true)
			{
				if ((int(line[i]) >= 97 && int(line[i]) <= 122) || (int(line[i]) >= 65 && int(line[i] <= 90)))
				{
					meaning += line[i];
				}
			}
		}
		this->insert(word, meaning);
	}
	dictionaryFile.close();
}
void Tries::show()
{
	int opt;
	do
	{
		cout << endl;
		cout << "1.Load Dictionary" << endl;
		cout << "2.Add Word" << endl;
		cout << "3.Search Word" << endl;
		cout << "4.Delete Word" << endl;
		cout << "5.Update Word" << endl;
		cout << "6.Word Suggestion" << endl;
		cout << "8.Display Dictionary" << endl;
		cout << "9.exit" << endl;
		cout << "Option : ";
		cin >> opt;
		switch (opt)
		{
		case 1:
		{
			string file;
			cout << "Enter File name like (Dictionary.txt)" << endl;
			cin >> file;
			importDictionary(file);
			break;
		}
		case 2:
		{
			string word, mean;
			cout << "Enter Word : ";
			cin >> word;
			cout << "Enter meaning : ";
			cin >> mean;
			insert(word, mean);            // Stored in	Dictionary
			break;
		}
		case 3:
		{
			string word;
			cout << "Enter Word to search : ";
			cin >> word;
			search(word);
			break;
		}
		case 4:
		{
			string word;
			cout << "Enter word to delete : ";
			cin >> word;
			deleteWord(word);
			break;
		}
		case 5:
		{
			string word, mean;
			cout << "Enter word to Update : ";
			cin >> word;
			cout << "Enter Meaning to Update : ";
			cin >> mean;
			insert(word, mean);
			break;
		}
		case 6:
		{
			string word;
			cout << "Enter Word for Suggestions: ";
			cin >> word;
			suggestion(word);    //Display similar words meaning exist in dictionary
			break;
		}
		case 7:
		{
			deleteAll();
			if (isEmpty())
			{
				cout << "Dictionary is Empty";
			}
			break;
		}
		case 8:
		{
			display();
			break;
		}
		case 9:
		{
			exit(0);
			break;
		}
		}
		cout << endl;
	} while (opt != 9);
	cout << endl;
}