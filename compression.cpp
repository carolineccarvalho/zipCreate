#include <bits/stdc++.h>
#include <codecvt>
#include <locale>

using namespace std;
 
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

vector<int> compression(wstring text){
    vector<int> out;
    unordered_map<string, string> table;
    for(int i=0; i<=255;i++){
        table[byteTobits(char(i))] = to_string(i);
    }

    string term = byteTobits(text[0]);
    int value = 256;

    for(int i=1; i<text.size();i++){
        string symbol = byteTobits(text[i]);
        if(table.count(term + symbol)){
            term = term + symbol;
        }else{
            out.push_back(stoi(table[term]));
            table[term + symbol] = to_string(value++);
            term = symbol;
        }
    }

    out.push_back(stoi(table[term]));
    return out;
}

vector<int> convertToIntVector(const vector<string>& strVector) {
    vector<int> intVector;
    for (const string& str : strVector) {
        if (str.length() == 1) {
            // Converte o caractere para seu valor ASCII
            int num = static_cast<int>(str[0]);
            intVector.push_back(num);
        } else {
            // Tenta converter strings numéricas
            try {
                int num = stoi(str);
                intVector.push_back(num);
            } catch (const invalid_argument& e) {
                cerr << "Erro: argumento inválido durante a conversão de string para int: " << str << endl;
            } catch (const out_of_range& e) {
                cerr << "Erro: número fora do intervalo permitido para int: " << str << endl;
            }
        }
    }
    return intVector;
}

void decompression(vector<int> codein){
    unordered_map<string, string> table;
    for(int i=0; i<=255;i++){
        table[toBin(i)] = string(1, char(i));
    }
    int value = 256;
    int code = codein[0];
    cout << code << endl;
    string term = table[toBin(code)];
    string output = term;
    string entry;

    cout << output << endl;

    for(int i=1; i<codein.size(); i++){
        code = codein[i];
        if(!table.count(toBin(code))){
            entry = term + term[0];
        }else{
            entry = table[toBin(code)];
        }      
        output += entry;
        table[toBin(value++)] = term + entry[0];
        term = entry;
    }
     
    cout << output << endl;
}

int main(){
    cout << "ç" << endl;
    wstring aux = L"Era uma vez um mundo complexo onde as linguagens de programação não apenas existiam em suas formas básicas, mas eram compostas por variantes, dialetos, compilações e subestruturas. C++ é apenas uma das estrelas que brilham em um firmamento cheio de JavaScript, Python, Rust, Haskell, Go, Kotlin, Ruby e incontáveis outras. Imagine, por exemplo, um projeto onde os desenvolvedores trabalham simultaneamente em múltiplas plataformas, usando diferentes IDEs como Visual Studio Code, Eclipse, IntelliJ IDEA e até editores minimalistas como Vim e Emacs. Além disso, consideremos o seguinte: var123 + func$456 * [calc_789]{expressão_alfa} ÷ 98% & concatenado com texto Dentro desse emaranhado, scripts de automação se entrelaçam com APIs RESTful, JSON, XML e chamadas assíncronas para lidar com dados de grandes volumes, escalando de terabytes para petabytes de informação. Assim, surgem novos desafios de escalabilidade, segurança cibernética, otimização de algoritmos, computação paralela e aprendizado de máquina~.";
    vector<int> cod = compression(aux);
    vector<string> ans;
    for(auto it: cod){
        if(it<=255) ans.push_back(string(1, char(it)));
        else ans.push_back(to_string(it));
    }
    cout << endl;

    for(auto it: ans){
        cout << it << " ";
    }
    cout << endl;
    vector<int> codin = convertToIntVector(ans);
    decompression(cod);
}