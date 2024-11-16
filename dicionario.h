#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <unordered_map>
#include <string>
using namespace std;

class TrieNode {
public:
    unordered_map<string, TrieNode*> filhos;
    string code;

    TrieNode();
};

class Dicionario {
private:
    TrieNode* raiz;
    string nextCode;

    int prefixoEmComum(const string& chave, const string& edge, int start);
    void splitNode(TrieNode* node, const string &edge, int matchLength);
    void printTrieRecursive(TrieNode* node, const string& prefix, bool isLast);
    bool removeTrie(TrieNode* curr, const string& chave, int index = 0);
    void apagaTrie(TrieNode* node);
    bool searchTrie(TrieNode* curr, const string& codigo);

public:
    Dicionario();
    ~Dicionario();

    void insert(const string& chave, const string& codigo);
    void printTrie();
    bool countTrie(const std::string& codigo);
    bool deleteTrie(const string& chave);
    string stringTrie(TrieNode* curr, const std::string& codigo, const string& prefixo);
    string getPalavra(const string& codigo);
    void clear();
};

#endif
