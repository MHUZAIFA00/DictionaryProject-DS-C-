#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
class Node 
{
public:
    std::string mean;
    std::vector<Node*> letter;

    Node(std::string mean);
    ~Node();
};
class Tries 
{
private:
    Node* root;
    void Display(Node* curr, int i, std::string extraWord = "");
    void Search(Node* curr, std::string word, std::string& meaning);
    void SuggestWord(Node* curr, std::string word, std::string& meaning);
    bool DeleteVector(std::vector<Node*> letter);
    void Delete(Node*& curr, std::string word, int i, bool& isDeleted, bool& endFound);
    void DeleteAll(Node*& curr, int i);
    bool checkWord(std::string word);

public:
    Tries();
    ~Tries();
    void deleteAll();
    void insert(std::string word, std::string meaning);
    bool search(std::string word);
    void display();
    bool isEmpty();
    bool deleteWord(std::string word);
    void suggestion(std::string word);
    void importDictionary(std::string fileName);
    void show();
};