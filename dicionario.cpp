#include "dicionario.h"
#include <iostream>

TrieNode::TrieNode() : code("-1") {}

Dicionario::Dicionario() {
    raiz = new TrieNode();
    raiz->filhos["0"] = new TrieNode();
    raiz->filhos["1"] = new TrieNode();
    nextCode = "2";
}

void Dicionario::insert(const std::string& chave, const std::string& codigo) {
    TrieNode* curr = raiz;
    int index = 0;

    while (index < chave.size()) {
        bool found = false;
        for (auto &child : curr->filhos) {
            const std::string &edge = child.first;
            int tamanhoPrefixComum = prefixoEmComum(chave, edge, index);

            if (tamanhoPrefixComum == edge.size()) {
                curr = child.second;
                index += tamanhoPrefixComum;
                found = true;
                break;
            } else if (tamanhoPrefixComum > 0) {
                splitNode(curr, edge, tamanhoPrefixComum);
                curr = curr->filhos[chave.substr(index, tamanhoPrefixComum)];
                index += tamanhoPrefixComum;
                found = true;
                break;
            }
        }
        if (!found) {
            curr->filhos[chave.substr(index)] = new TrieNode();
            curr->filhos[chave.substr(index)]->code = codigo;
            return;
        }
    }
    curr->code = codigo;
}

void Dicionario::printTrie() {
    printTrieRecursive(raiz, "", true);
}

bool Dicionario::searchTrie(const std::string& chave) {
    TrieNode* curr = raiz;
    int index = 0;

    while (index < chave.size()) {
        bool found = false;
        for (auto &child : curr->filhos) {
            const std::string &edge = child.first;
            int tamanhoPrefixComum = prefixoEmComum(chave, edge, index);

            if (tamanhoPrefixComum == edge.size()) {
                curr = child.second;
                index += tamanhoPrefixComum;
                found = true;
                break;
            } else if (tamanhoPrefixComum > 0) {
                return false;
            }
        }
        if (!found) {
            return false;
        }
    }
    return !curr->code.empty();
}
string Dicionario::stringTrie(const string& chave){
    TrieNode* curr = raiz;
    int index = 0;

    while (index < chave.size()) {
        bool found = false;
        for (auto &child : curr->filhos) {
            const std::string &edge = child.first;
            int tamanhoPrefixComum = prefixoEmComum(chave, edge, index);

            if (tamanhoPrefixComum == edge.size()) {
                curr = child.second;
                index += tamanhoPrefixComum;
                found = true;
                break;
            } else if (tamanhoPrefixComum > 0) {
                return "";
            }
        }
        if (!found) {
            return "";
        }
    }
    return curr->code;
}
bool Dicionario::deleteTrie(const std::string& chave) {
    return removeTrie(raiz, chave);
}

int Dicionario::prefixoEmComum(const std::string& chave, const std::string& edge, int start) {
    int i = 0;
    while (i + start < chave.size() && i < edge.size() && chave[i + start] == edge[i]) {
        i++;
    }
    return i;
}

void Dicionario::splitNode(TrieNode* node, const std::string &edge, int matchLength) {
    std::string prefixo = edge.substr(0, matchLength);
    std::string sufixo = edge.substr(matchLength);

    TrieNode* child = node->filhos[edge];
    node->filhos.erase(edge);

    TrieNode* newChild = new TrieNode();
    node->filhos[prefixo] = newChild;
    newChild->filhos[sufixo] = child;
}

void Dicionario::printTrieRecursive(TrieNode* node, const std::string& prefix, bool isLast) {
    if (node->code != "-1") {
        std::cout << prefix << (isLast ? "└── " : "├── ") << "(Code: " << node->code << ")" << std::endl;
    } else {
        std::cout << prefix << (isLast ? "└── " : "├── ") << std::endl;
    }

    auto it = node->filhos.begin();
    while (it != node->filhos.end()) {
        bool lastChild = (std::next(it) == node->filhos.end());
        std::cout << prefix << (isLast ? "    " : "│   ") << it->first << std::endl;
        printTrieRecursive(it->second, prefix + (isLast ? "    " : "│   "), lastChild);
        ++it;
    }
}

bool Dicionario::removeTrie(TrieNode* curr, const std::string& chave, int index) {
    if (index == chave.size()) {
        if (curr->code == "-1") {
            return false;
        }
        curr->code = "-1";
        return curr->filhos.empty();
    }

    for (auto &child : curr->filhos) {
        const std::string &edge = child.first;
        TrieNode* nextNode = child.second;
        int tamanhoPrefixComum = prefixoEmComum(chave, edge, index);

        if (tamanhoPrefixComum == edge.size()) {
            bool devemosDeletarFilho = removeTrie(nextNode, chave, index + tamanhoPrefixComum);
            if (devemosDeletarFilho) {
                delete nextNode;
                curr->filhos.erase(edge);
            }
            return curr->filhos.empty() && curr->code == "-1";
        }
    }
    return false;
}
