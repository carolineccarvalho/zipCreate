#include <bits/stdc++.h>
#include <codecvt>
#include <locale>
#include "dicionario.h"
#include "compression.h"

using namespace std;

string completa(string bin, int bit){
    string aux = bin; 
    while(aux.size() != bit){
        aux = '0'+aux;
    }
    return aux;
}

string toBin(int in){
    string aux = "";
    int resto;
    int div = in;
    while(div > 0){
        resto = div%2;
        div = div/2;
        aux = char('0'+ resto)+aux;
    }

    return aux;
}

string byteTobits(char32_t letter){
    bitset<8> bits(letter);
    return bits.to_string();
}

char binTochar(string bin){
    string auxiliar = bin;
    bitset<8> bits(auxiliar);
    return static_cast<char>(bits.to_ulong());
}

vector<pair<string,int>> compression(string text, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic){
    vector<pair<string,int>> out;
    Dicionario table;
    for(int i=0; i<=255;i++){
        table.insert(completa(toBin(i),8), byteTobits(char(i)));
    }

    string term = byteTobits(text[0]);
    int value = 256;
    int bit = 8;

    for(int j=1; j<text.size();j++){
        if(value == (1<<bit)) bit++;
        string symbol = byteTobits(text[j]);

        if(table.countTrie(term + symbol)){
            term = term + symbol;
        }else{
            out.push_back({table.getPalavra(term),table.getPalavra(term).size()});
            if(bit<=max){
                table.insert(completa(toBin(value++),bit), (term + symbol));
                palavrasAdicionadas++;
            }else{
                numeroResets++;
                table.clear();
                for(int i=0; i<=255;i++){
                    table.insert(completa(toBin(i),8), byteTobits(char(i)));
                }
                value = 256;
                bit = 9;
                table.insert(completa(toBin(value++),bit), (term + symbol));

            }
            term = symbol;
        }
    }

    espacoDic = table.calcularTamanhoDicionario();
    out.push_back({table.getPalavra(term),table.getPalavra(term).size()});
    return out;
}

vector<int> bin2str(vector<string> bin){
    vector<int> aux;
    for(auto it: bin){
        aux.push_back(stoi(it, nullptr,2));
    }
    return aux;
}

string decompression(vector<int> codein, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic){
    Dicionario table;
    for(int i=0; i<=255;i++){
        table.insert(string(1, char(i)), toBin(i));
    }
    int value = 256;
    int code = codein[0];
    int bit = 8;
    string term = table.getPalavra(toBin(code));
    string output = term;
    string entry;

    for(int i=1; i<codein.size(); i++){
        if(value == (1<<bit)) bit++;
        code = codein[i];
        if(!table.countTrie(toBin(code))){
            entry = term + term[0];
        }else{
            entry = table.getPalavra(toBin(code));
        }      
        output += entry;
        if(bit<=max) {
            palavrasAdicionadas++;
            table.insert(term + entry[0], toBin(value++));
        }else{
            numeroResets++;
            table.clear();
            for(int i=0; i<=255;i++){
                table.insert(string(1, char(i)), toBin(i));
            }
            value = 256;
            table.insert(term + entry[0], toBin(value++));
            bit=9;
        }
        term = entry;
    }
    espacoDic = table.calcularTamanhoDicionario(); 
    return output;
}


vector<pair<string,int>> compressionFixed(string text, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic){
    vector<pair<string,int>> out;
    Dicionario table;
    for(int i=0; i<=255;i++){
        table.insert(completa(toBin(i),max), byteTobits(char(i)));
    }

    string term = byteTobits(text[0]);
    int value = 256;
    int bit = 8;
    int bit2 = max;

    for(int i=1; i<text.size();i++){
        if(value == (1<<bit)) bit++;
        string symbol = byteTobits(text[i]);

        if(table.countTrie(term + symbol)){
            term = term + symbol;
        }else{
            out.push_back({table.getPalavra(term),table.getPalavra(term).size()});
            if(bit<=max){
                 table.insert(completa(toBin(value++),bit2), term + symbol);
                 palavrasAdicionadas++;
            }else{
                numeroResets++;
                table.clear();
                for(int i=0; i<=255;i++){
                    table.insert(completa(toBin(i),bit2), byteTobits(char(i)));
                }
                value = 256;
                bit = 9;
                table.insert(completa(toBin(value++),bit2), term + symbol);

            }
            term = symbol;
        }
    }
    espacoDic = table.calcularTamanhoDicionario();
    out.push_back({table.getPalavra(term),table.getPalavra(term).size()});
    return out;
}

vector<int> apart(string entrada, vector<int> pos){
    vector<int> aux;
    int help = 0;
    for(int i=0; i<pos.size(); i+=1){
        string it = entrada.substr(help,pos[i]);
        help+=pos[i];
        aux.push_back(stoi(it,nullptr,2));
    }
    return aux;
}

string decompressionFixed(vector<int> codein, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic){
    Dicionario table;
    for(int i=0; i<=255;i++){
        table.insert(string(1, char(i)), toBin(i));
    }
    int value = 256;
    int code = codein[0];
    int bit = 8;
    string term = table.getPalavra(toBin(code));
    string output = term;
    string entry;

    for(int i=1; i<codein.size(); i++){
        if(value == (1<<bit)) bit++;
        code = codein[i];
        if(!table.countTrie(toBin(code))){
            entry = term + term[0];
        }else{
            entry = table.getPalavra(toBin(code));
        }      
        output += entry;
        if(bit<=max) {
            table.insert(term + entry[0], toBin(value++));
            palavrasAdicionadas++;
        }else{
            numeroResets++;
            table.clear();
            for(int i=0; i<=255;i++){
                table.insert(string(1, char(i)), toBin(i));
            }
            value = 256;
            table.insert(term + entry[0], toBin(value++));
            bit = 9;
        }
        term = entry;
    }
    espacoDic = table.calcularTamanhoDicionario();
    return output;
}

string openFile (string name){
        ifstream file(name);
        stringstream buffer;
        buffer << file.rdbuf();
        string conteudo = buffer.str();
        return conteudo;
}


void write(string binStr, string filename) {
    ofstream outputFile(filename, ios::binary);
    if (!outputFile) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    string aux = binStr;

    for (size_t i = 0; i < aux.size(); i += 8) {
       
        string byteStr = aux.substr(i, 8);
        
        unsigned char byte = bitset<8>(byteStr).to_ulong();

        outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }

    outputFile.close();
}


string binary(string filename){
    ifstream arquivo(filename, ios::binary);
    stringstream buffer;
    buffer << arquivo.rdbuf();
    string conteudo = buffer.str();
    int pos = filename[0] - '0';

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo! Adicione o mesmo nome" << endl;
        return "";
    }

    string aux =  "";

    for(int i=0; i<conteudo.size();i++){
        aux += byteTobits(conteudo[i]);
    }
    

    return aux;
}

void savesize(const string& path, const vector<int>& aux) {
    ofstream outputFile("cache/" + path, ios::binary);
    if (!outputFile) {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    for (size_t i = 0; i < aux.size(); ++i) {
        string numStr = to_string(aux[i]);
        outputFile.write(numStr.c_str(), numStr.size()); 

        if (i < aux.size() - 1) {
            outputFile.write(",", 1);  
        }
    }

    outputFile.close();
}

vector<int> loadsize(const string& path) {
    ifstream inputFile("cache/" + path, ios::binary);
    vector<int> numbers;

    if (!inputFile) {
        cerr << "Erro ao abrir o arquivo para leitura. Verifique se o nome do arquivo é o mesmo de compressão." << endl;
        return numbers;
    }

    string fileContent;
    getline(inputFile, fileContent);  

    stringstream ss(fileContent);
    string token;
    while (getline(ss, token, ',')) {  
        if (!token.empty()) {  
            numbers.push_back(stoi(token));  
        }
    }

    inputFile.close();
    return numbers;
}

void save(const string path, const string content) {
    ofstream outputFile(path, ios::binary);
    if (!outputFile) {
        cerr << "Erro ao abrir o arquivo para escrita: " << path << endl;
        return;
    }

    outputFile.write(content.c_str(), content.size());  
    outputFile.close();
}

void compressionOPT(string filename, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic, int& texto_original, int& texto_comprimido){
    string conteudo = openFile(filename);
    texto_original = conteudo.size();
    vector<pair<string,int>> compressed = compression(conteudo, max, palavrasAdicionadas, numeroResets, espacoDic);
    vector<int> value;
    string aux = "";

    for(auto it: compressed) {
        aux += it.first;
        value.push_back(it.second);
    }
    texto_comprimido = (aux.size())/8;
    savesize(filename,value);
    write(aux, filename + ".lzw");
    cout << "Compressão concluída!" << endl;
}


void compressionFixedOPT(string filename, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic, int& texto_original, int& texto_comprimido){
    string conteudo = openFile(filename);
    texto_original = conteudo.size();
    vector<pair<string,int>> compressed = compressionFixed(conteudo, max, palavrasAdicionadas, numeroResets, espacoDic);
    vector<int> value;
    string aux = "";

    for(auto it: compressed) {
        aux += it.first;
        value.push_back(it.second);
    }
    texto_comprimido = (aux.size())/8;
    savesize(filename,value);
    write(aux, filename + ".lzw");
     cout << "Compressão concluída!" << endl;
}

void decompressionOPT(string filename, int max, int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic, int& texto_original, int& texto_descomprimido){
    vector<int> division = loadsize(filename);
    texto_original = division.size();
    vector<int> code = apart(binary(filename + ".lzw"),division);
    string dec = decompression(code, max, palavrasAdicionadas, numeroResets, espacoDic);
    save("Descompressed" + filename,dec);
    texto_descomprimido = dec.size();
    cout << "Descompressão concluída!" << endl;

}

void decompressionFixedOPT(string filename, int max,  int& palavrasAdicionadas, int& numeroResets, size_t& espacoDic, int& texto_original, int& texto_descomprimido){
    vector<int> division = loadsize(filename);
    texto_original = division.size();
    vector<int> code = apart(binary(filename + ".lzw"),division);
    string dec = decompressionFixed(code, max, palavrasAdicionadas, numeroResets, espacoDic);
    save("DescompressedFixed" + filename,dec);
    texto_descomprimido = dec.size();
    cout << "Descompressão concluída!" << endl;
}
