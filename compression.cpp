#include <bits/stdc++.h>
#include <codecvt>
#include <locale>
#include "dicionario.h"

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

string textTobin(string text){
    string out = "";
    for(auto i: text) out += byteTobits(i);
    return out;
}


char binTochar(string bin){
    string auxiliar = bin;
    bitset<8> bits(auxiliar);
    return static_cast<char>(bits.to_ulong());
}

string byteTostr(string bin){
    string out = "";
    for(int i=0; i<bin.size(); i+=8){
        string aux = bin.substr(i,8);
        out += binTochar(aux);
    }
    return out;
}

vector<string> compression(string text, int max = 12){
    vector<string> out;
    Dicionario table;
    for(int i=0; i<=255;i++){
        table.insert(completa(toBin(i),8), byteTobits(char(i)));
    }

    string term = byteTobits(text[0]);
    int value = 256;
    int bit = 8;

    for(int i=1; i<text.size();i++){
        if(value == (1<<bit)) bit++;
        string symbol = byteTobits(text[i]);

        if(table.countTrie(term + symbol)){
            term = term + symbol;
        }else{
            out.push_back(table.getPalavra(term));
            if(bit<=max) table.insert(completa(toBin(value++),bit), (term + symbol));
            else{
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

    out.push_back(table.getPalavra(term));
    return out;
}

vector<int> bin2str(vector<string> bin){
    vector<int> aux;
    for(auto it: bin){
        aux.push_back(stoi(it, nullptr,2));
    }
    return aux;
}

string decompression(vector<int> codein, int max=12){
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
        if(bit<=max) table.insert(term + entry[0], toBin(value++));
        else{
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
     
    return output;
}


vector<string> compressionFixed(string text, int max = 12){
    vector<string> out;
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
            out.push_back(table.getPalavra(term));
            if(bit<=max) table.insert(completa(toBin(value++),bit2), term + symbol);
            else{
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

    out.push_back(table.getPalavra(term));
    return out;
}


string decompressionFixed(vector<int> codein, int max=12){
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
        if(bit<=max) table.insert(term + entry[0], toBin(value++));
        else{
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
     
    return output;
}

void writeBinaryStringToFile(const std::string& binStr, const std::string& filename) {
    std::ofstream outputFile(filename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return;
    }

    for (size_t i = 0; i < binStr.size(); i += 8) {
       
        std::string byteStr = binStr.substr(i, 8);
        
        unsigned char byte = std::bitset<8>(byteStr).to_ulong();

        outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    }

    outputFile.close();
    std::cout << "Arquivo binário escrito com sucesso!" << std::endl;
}


int main(){
    cout << "--------------------------------------" << endl;
    cout << "               PROJETO ZIP            " << endl;
    cout << "--------------------------------------" << endl;
    cout << " Caroline Carvalho e Deborah Yamamoto " << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
    int opt;
    while (true) {
        cout << "Opções de execução: " << endl;
        cout << "0: Parar execução" << endl;
        cout << "1: Compressão de arquivo com tamanho fixo" << endl;
        cout << "2: Compressão de arquivo com tamanho variavel" << endl;
        cout << "3: Descompressão arquivo com tamanho fixo" << endl;
        cout << "4: Descompressão arquivo com tamanho variavel" << endl;
        cin >> opt;

        if (opt == 0) {
            cout << "Encerrando o programa." << endl;
            break;
        }

        //string ascii = bmpToAscii("convert_to_image.bmp");
        std::ifstream file("Teste1.txt");
        stringstream buffer;
        buffer << file.rdbuf();
        string conteudo = buffer.str();
        cout << conteudo << endl;
        vector<string> compressed = compression(conteudo);

        string aux = "";

        for(auto it: compressed) aux += it;

        writeBinaryStringToFile(aux, "Teste1.txt.lzw");
 
    }


}