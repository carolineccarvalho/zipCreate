#include <bits/stdc++.h>
#include <codecvt>
#include <locale>

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

vector<string> compression(wstring text, int max = 12){
    vector<string> out;
    unordered_map<string, string> table;
    for(int i=0; i<=255;i++){
        table[byteTobits(char(i))] = completa(toBin(i),8);
    }

    string term = byteTobits(text[0]);
    int value = 256;
    int bit = 8;

    for(int i=1; i<text.size();i++){
        if(value == pow(2,bit)) bit++;
        string symbol = byteTobits(text[i]);
        if(table.count(term + symbol)){
            term = term + symbol;
        }else{
            out.push_back(table[term]);
            table[term + symbol] = completa(toBin(value++),bit);
            term = symbol;
        }
    }

    out.push_back(table[term]);
    return out;
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
    wstring aux = L"Este capítulo inicia com uma introdução ao projeto de software, na qual procuramos definir e motivar a importância desse tipo de atividade (Seção 5.1). Em seguida, discutimos diversas considerações relevantes em projetos de software. Especificamente, tratamos de Integridade Conceitual (Seção 5.2), Ocultamento de Informação (Seção 5.3), Coesão (Seção 5.4) e Acoplamento (Seção 5.5). Na Seção 5.6 discutimos um conjunto de princípios de projeto, incluindo: Responsabilidade Única, Segregação de Interfaces, Inversão de Dependências, Prefira Composição a Herança, Demeter, Aberto/Fechado e Substituição de Liskov. Por fim, tratamos de métricas para avaliar a qualidade de projetos de software (Seção 5.7). 5.1 Introdução A afirmação de John Ousterhout que abre este capítulo é uma excelente definição para projeto de software. Apesar de não afirmar explicitamente, a citação assume que quando falamos de projeto estamos procurando uma solução para um determinado problema. No contexto de Engenharia de Software, esse problema consiste na implementação de um sistema que atenda aos requisitos funcionais e não-funcionais definidos por um cliente — ou Dono do Produto, para usar um termo mais moderno. Prosseguindo, Ousterhout sugere como devemos proceder para chegar a essa solução: devemos decompor, isto é, quebrar o problema inicial, que pode ser bastante complexo, em partes menores. Por fim, a frase impõe uma restrição a essa decomposição: ela deve permitir que cada uma das partes do projeto possa ser resolvida (ou implementada) de forma independente.Essa explicação pode passar a impressão de que projeto é uma atividade simples. No entanto, no projeto de software temos que combater um grande inimigo: a complexidade que caracteriza sistemas modernos de software. Talvez, por isso, Ousterhout mencione que a decomposição de um problema em partes independentes é uma questão fundamental, não apenas em Engenharia de Software, mas em toda Ciência da Computação! Uma estratégia importante para combater a complexidade de sistemas de software passa pela criação de abstrações. Uma abstração — pelo menos em Computação — é uma representação simplificada de uma entidade. Apesar de simplificada, ela nos permite interagir e tirar proveito da entidade abstraída, sem que tenhamos que dominar todos os detalhes envolvidos na sua implementação. Dentre outros, funções, classes, interfaces, pacotes e bibliotecas são os instrumentos clássicos oferecidos por linguagens de programação para criação de abstrações.Em resumo, o primeiro objetivo de projeto de software é decompor um problema em partes menores. Além disso, deve ser possível implementar tais partes de forma independente. Por fim, mas não menos importante, essas partes devem ser abstratas. Em outras palavras, a implementação delas pode ser desafiadora e complexa, mas apenas para os desenvolvedores envolvidos em tal tarefa. Para os demais desenvolvedores, deve ser simples usar a abstração que foi criada.5.1.1 Exemplo Para ilustrar essa introdução a projetos de software, vamos usar o exemplo de um compilador. Os requisitos no caso são claros: dado um programa em uma linguagem X devemos convertê-lo em um programa em uma linguagem Y, que costuma ser a linguagem de uma máquina. No entanto, o projeto de um compilador não é trivial. Então, após anos de pesquisa, descobriu-se uma solução — ou projeto — para esse tipo de sistema, a qual é ilustrada na figura da próxima página.";
    vector<string> cod = compression(aux);
    vector<string> ans;
    for(auto it: cod){
        cout << it << endl;
    }
    
}