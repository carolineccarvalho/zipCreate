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

public:
    Dicionario();
    void insert(const string& chave, const string& codigo);
    void printTrie();
    bool searchTrie(const string& chave);
    bool deleteTrie(const string& chave);
    string stringTrie(const string& chave);
};

#endif
