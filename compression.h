#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <bits/stdc++.h>
#include <codecvt>
#include <locale>
#include "dicionario.h"
using namespace std;

string completa(string bin, int bit);
string toBin(int in);
string byteTobits(char32_t letter);
char binTochar(string bin);
vector<pair<string,int>> compression(string text, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic);
vector<int> bin2str(vector<string> bin);
string decompression(vector<int> codein, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic);
vector<pair<string,int>> compressionFixed(string text, int max, int& palavrasAdicionadas, int&numeroResets, size_t& espacoDic);
vector<int> apart(string entrada, vector<int> pos);
string decompressionFixed(vector<int> codein, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic);
string openFile (string name);
void write(string binStr, string filename);
string binary(string filename);
void savesize(const string& path, const vector<int>& aux);
vector<int> loadsize(const string& path);
void save(const string path, const string content);
void compressionOPT(string filename, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic, int& texto_original, int& texto_comprimido);
void compressionFixedOPT(string filename, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic, int& texto_original, int& texto_comprimido);
void decompressionOPT(string filename, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic, int& texto_original, int& texto_descomprimido);
void decompressionFixedOPT(string filename, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic, int& texto_original, int& texto_descomprimido);
#endif