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

vector<string> compression(wstring text, int max = 12){
    vector<string> out;
    Dicionario table;
    for(int i=0; i<=255;i++){
        table.insert(completa(toBin(i),12), byteTobits(char(i)));
    }

    string term = byteTobits(text[0]);
    int value = 256;
    int bit = 8;
    int bit2 = 12;

    for(int i=1; i<text.size();i++){
        if(value == (1<<bit)) bit++;
        string symbol = byteTobits(text[i]);

        if(table.countTrie(term + symbol)){
            term = term + symbol;
        }else{
            out.push_back(table.getPalavra(term));
            if(bit<=max) table.getPalavra(term + symbol) = completa(toBin(value++),bit2);
            else{
                table.clear();
                for(int i=0; i<=255;i++){
                    table.insert(completa(toBin(i),bit2), byteTobits(char(i)));
                }
                value = 256;
                bit = 9;
                table.getPalavra(term + symbol) = completa(toBin(value++),bit2);

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

void decompression(vector<int> codein, int max=12){
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
        if(bit<=max) table.getPalavra(toBin(value++)) = term + entry[0];
        else{
            table.clear();
            for(int i=0; i<=255;i++){
                table.insert(string(1, char(i)), toBin(i));
            }
            value = 256;
            table.getPalavra(toBin(value++)) = term + entry[0];
            bit = 9;
        }
        term = entry;
    }
     
    cout << output << endl;
}


int main(){
    wstring aux = L"A tecnologia se tornou uma parte fundamental do mundo contemporâneo, moldando a forma como as pessoas vivem, trabalham e interagem. Desde as primeiras invenções, como a roda e a prensa de Gutemberg, até os avanços mais recentes em inteligência artificial e biotecnologia, a evolução tecnológica tem sido um motor propulsor de mudanças econômicas, sociais e culturais. Em uma era marcada pela digitalização e pela conectividade global, entender o impacto da tecnologia é essencial para se adaptar e prosperar nesse novo paradigma. Uma das áreas mais notáveis de avanço tecnológico é a da comunicação. O surgimento da internet transformou a maneira como as pessoas trocam informações, permitindo a comunicação instantânea e o acesso a um volume vasto de conhecimento. Ferramentas como e-mail, mensagens instantâneas e redes sociais conectam indivíduos em diferentes partes do mundo, criando uma sociedade global interligada. Essa conectividade trouxe benefícios substanciais, como a disseminação de ideias e a promoção de movimentos sociais, mas também levantou desafios significativos, incluindo questões de privacidade e a propagação de desinformação. No campo da saúde, a tecnologia desempenha um papel crucial. Procedimentos médicos que antes eram complexos e arriscados agora são realizados com maior precisão e menos riscos, graças a tecnologias como a robótica cirúrgica e a telemedicina. Dispositivos portáteis de monitoramento permitem que pacientes acompanhem em tempo real seus sinais vitais, melhorando o diagnóstico precoce e a gestão de doenças crônicas. Além disso, avanços na engenharia genética e na biotecnologia abriram portas para tratamentos inovadores, como a edição de genes, que tem o potencial de curar doenças hereditárias. A automação e a inteligência artificial (IA) são outra vertente de destaque. Com algoritmos sofisticados, a IA é capaz de processar grandes volumes de dados, identificar padrões complexos e tomar decisões que antes eram exclusivas do pensamento humano. Isso levou à criação de sistemas que automatizam tarefas repetitivas, aumentando a produtividade em setores como a manufatura, a logística e os serviços financeiros. No entanto, a adoção de tecnologias de automação também suscita debates sobre o futuro do trabalho, uma vez que muitas ocupações tradicionais estão sendo substituídas por máquinas. A educação também tem sido profundamente influenciada pela tecnologia. Plataformas de aprendizado online, cursos virtuais e recursos digitais ampliaram o acesso ao ensino, permitindo que pessoas em locais remotos ou com horários flexíveis adquiram conhecimento. Ferramentas educacionais baseadas em IA podem personalizar a experiência de aprendizado, adaptando o conteúdo e o ritmo conforme as necessidades do aluno. Contudo, a dependência crescente de tecnologias digitais na educação levanta preocupações sobre desigualdade de acesso, uma vez que nem todos os alunos têm os recursos necessários para aproveitar essas inovações. Outro aspecto transformador da tecnologia é o impacto ambiental. Por um lado, o desenvolvimento de tecnologias sustentáveis, como energia solar e eólica, oferece alternativas mais limpas às fontes de energia tradicionais, ajudando a combater as mudanças climáticas. Por outro lado, a produção e o descarte de dispositivos eletrônicos geram grandes quantidades de resíduos e poluentes, exigindo uma gestão mais responsável dos recursos tecnológicos. Inovações em reciclagem e economia circular são fundamentais para minimizar os danos ambientais e promover um uso mais consciente da tecnologia. Finalmente, a ética e a regulamentação tecnológica são questões cada vez mais debatidas. À medida que novas tecnologias emergem, surge a necessidade de estabelecer diretrizes que assegurem um desenvolvimento responsável e equilibrado. Temas como a proteção de dados pessoais, a transparência nos algoritmos e a responsabilidade em casos de falhas tecnológicas exigem a atenção de governos, empresas e da sociedade civil. Somente por meio de um diálogo aberto e de políticas bem-definidas será possível garantir que a tecnologia continue sendo uma força para o bem comum, sem comprometer os direitos individuais e a equidade social. Em suma, a tecnologia está indissociavelmente ligada ao progresso humano, oferecendo tanto oportunidades quanto desafios. O futuro promete avanços ainda mais surpreendentes, com tecnologias emergentes como computação quântica e interfaces cérebro-computador. A capacidade de usar essas ferramentas de forma consciente e ética será um fator determinante para o sucesso e a sustentabilidade da sociedade global.A tecnologia se tornou uma parte fundamental do mundo contemporâneo, moldando a forma como as pessoas vivem, trabalham e interagem. Desde as primeiras invenções, como a roda e a prensa de Gutemberg, até os avanços mais recentes em inteligência artificial e biotecnologia, a evolução tecnológica tem sido um motor propulsor de mudanças econômicas, sociais e culturais. Em uma era marcada pela digitalização e pela conectividade global, entender o impacto da tecnologia é essencial para se adaptar e prosperar nesse novo paradigma. Uma das áreas mais notáveis de avanço tecnológico é a da comunicação. O surgimento da internet transformou a maneira como as pessoas trocam informações, permitindo a comunicação instantânea e o acesso a um volume vasto de conhecimento. Ferramentas como e-mail, mensagens instantâneas e redes sociais conectam indivíduos em diferentes partes do mundo, criando uma sociedade global interligada. Essa conectividade trouxe benefícios substanciais, como a disseminação de ideias e a promoção de movimentos sociais, mas também levantou desafios significativos, incluindo questões de privacidade e a propagação de desinformação. No campo da saúde, a tecnologia desempenha um papel crucial. Procedimentos médicos que antes eram complexos e arriscados agora são realizados com maior precisão e menos riscos, graças a tecnologias como a robótica cirúrgica e a telemedicina. Dispositivos portáteis de monitoramento permitem que pacientes acompanhem em tempo real seus sinais vitais, melhorando o diagnóstico precoce e a gestão de doenças crônicas. Além disso, avanços na engenharia genética e na biotecnologia abriram portas para tratamentos inovadores, como a edição de genes, que tem o potencial de curar doenças hereditárias. A automação e a inteligência artificial (IA) são outra vertente de destaque. Com algoritmos sofisticados, a IA é capaz de processar grandes volumes de dados, identificar padrões complexos e tomar decisões que antes eram exclusivas do pensamento humano. Isso levou à criação de sistemas que automatizam tarefas repetitivas, aumentando a produtividade em setores como a manufatura, a logística e os serviços financeiros. No entanto, a adoção de tecnologias de automação também suscita debates sobre o futuro do trabalho, uma vez que muitas ocupações tradicionais estão sendo substituídas por máquinas. A educação também tem sido profundamente influenciada pela tecnologia. Plataformas de aprendizado online, cursos virtuais e recursos digitais ampliaram o acesso ao ensino, permitindo que pessoas em locais remotos ou com horários flexíveis adquiram conhecimento. Ferramentas educacionais baseadas em IA podem personalizar a experiência de aprendizado, adaptando o conteúdo e o ritmo conforme as necessidades do aluno. Contudo, a dependência crescente de tecnologias digitais na educação levanta preocupações sobre desigualdade de acesso, uma vez que nem todos os alunos têm os recursos necessários para aproveitar essas inovações. Outro aspecto transformador da tecnologia é o impacto ambiental. Por um lado, o desenvolvimento de tecnologias sustentáveis, como energia solar e eólica, oferece alternativas mais limpas às fontes de energia tradicionais, ajudando a combater as mudanças climáticas. Por outro lado, a produção e o descarte de dispositivos eletrônicos geram grandes quantidades de resíduos e poluentes, exigindo uma gestão mais responsável dos recursos tecnológicos. Inovações em reciclagem e economia circular são fundamentais para minimizar os danos ambientais e promover um uso mais consciente da tecnologia. Finalmente, a ética e a regulamentação tecnológica são questões cada vez mais debatidas. À medida que novas tecnologias emergem, surge a necessidade de estabelecer diretrizes que assegurem um desenvolvimento responsável e equilibrado. Temas como a proteção de dados pessoais, a transparência nos algoritmos e a responsabilidade em casos de falhas tecnológicas exigem a atenção de governos, empresas e da sociedade civil. Somente por meio de um diálogo aberto e de políticas bem-definidas será possível garantir que a tecnologia continue sendo uma força para o bem comum, sem comprometer os direitos individuais e a equidade social. Em suma, a tecnologia está indissociavelmente ligada ao progresso humano, oferecendo tanto oportunidades quanto desafios. O futuro promete avanços ainda mais surpreendentes, com tecnologias emergentes como computação quântica e interfaces cérebro-computador. A capacidade de usar essas ferramentas de forma consciente e ética será um fator determinante para o sucesso e a sustentabilidade da sociedade global.A tecnologia se tornou uma parte fundamental do mundo contemporâneo, moldando a forma como as pessoas vivem, trabalham e interagem. Desde as primeiras invenções, como a roda e a prensa de Gutemberg, até os avanços mais recentes em inteligência artificial e biotecnologia, a evolução tecnológica tem sido um motor propulsor de mudanças econômicas, sociais e culturais. Em uma era marcada pela digitalização e pela conectividade global, entender o impacto da tecnologia é essencial para se adaptar e prosperar nesse novo paradigma. Uma das áreas mais notáveis de avanço tecnológico é a da comunicação. O surgimento da internet transformou a maneira como as pessoas trocam informações, permitindo a comunicação instantânea e o acesso a um volume vasto de conhecimento. Ferramentas como e-mail, mensagens instantâneas e redes sociais conectam indivíduos em diferentes partes do mundo, criando uma sociedade global interligada. Essa conectividade trouxe benefícios substanciais, como a disseminação de ideias e a promoção de movimentos sociais, mas também levantou desafios significativos, incluindo questões de privacidade e a propagação de desinformação. No campo da saúde, a tecnologia desempenha um papel crucial. Procedimentos médicos que antes eram complexos e arriscados agora são realizados com maior precisão e menos riscos, graças a tecnologias como a robótica cirúrgica e a telemedicina. Dispositivos portáteis de monitoramento permitem que pacientes acompanhem em tempo real seus sinais vitais, melhorando o diagnóstico precoce e a gestão de doenças crônicas. Além disso, avanços na engenharia genética e na biotecnologia abriram portas para tratamentos inovadores, como a edição de genes, que tem o potencial de curar doenças hereditárias. A automação e a inteligência artificial (IA) são outra vertente de destaque. Com algoritmos sofisticados, a IA é capaz de processar grandes volumes de dados, identificar padrões complexos e tomar decisões que antes eram exclusivas do pensamento humano. Isso levou à criação de sistemas que automatizam tarefas repetitivas, aumentando a produtividade em setores como a manufatura, a logística e os serviços financeiros. No entanto, a adoção de tecnologias de automação também suscita debates sobre o futuro do trabalho, uma vez que muitas ocupações tradicionais estão sendo substituídas por máquinas. A educação também tem sido profundamente influenciada pela tecnologia. Plataformas de aprendizado online, cursos virtuais e recursos digitais ampliaram o acesso ao ensino, permitindo que pessoas em locais remotos ou com horários flexíveis adquiram conhecimento. Ferramentas educacionais baseadas em IA podem personalizar a experiência de aprendizado, adaptando o conteúdo e o ritmo conforme as necessidades do aluno. Contudo, a dependência crescente de tecnologias digitais na educação levanta preocupações sobre desigualdade de acesso, uma vez que nem todos os alunos têm os recursos necessários para aproveitar essas inovações. Outro aspecto transformador da tecnologia é o impacto ambiental. Por um lado, o desenvolvimento de tecnologias sustentáveis, como energia solar e eólica, oferece alternativas mais limpas às fontes de energia tradicionais, ajudando a combater as mudanças climáticas. Por outro lado, a produção e o descarte de dispositivos eletrônicos geram grandes quantidades de resíduos e poluentes, exigindo uma gestão mais responsável dos recursos tecnológicos. Inovações em reciclagem e economia circular são fundamentais para minimizar os danos ambientais e promover um uso mais consciente da tecnologia. Finalmente, a ética e a regulamentação tecnológica são questões cada vez mais debatidas. À medida que novas tecnologias emergem, surge a necessidade de estabelecer diretrizes que assegurem um desenvolvimento responsável e equilibrado. Temas como a proteção de dados pessoais, a transparência nos algoritmos e a responsabilidade em casos de falhas tecnológicas exigem a atenção de governos, empresas e da sociedade civil. Somente por meio de um diálogo aberto e de políticas bem-definidas será possível garantir que a tecnologia continue sendo uma força para o bem comum, sem comprometer os direitos individuais e a equidade social. Em suma, a tecnologia está indissociavelmente ligada ao progresso humano, oferecendo tanto oportunidades quanto desafios. O futuro promete avanços ainda mais surpreendentes, com tecnologias emergentes como computação quântica e interfaces cérebro-computador. A capacidade de usar essas ferramentas de forma consciente e ética será um fator determinante para o sucesso e a sustentabilidade da sociedade global.A tecnologia se tornou uma parte fundamental do mundo contemporâneo, moldando a forma como as pessoas vivem, trabalham e interagem. Desde as primeiras invenções, como a roda e a prensa de Gutemberg, até os avanços mais recentes em inteligência artificial e biotecnologia, a evolução tecnológica tem sido um motor propulsor de mudanças econômicas, sociais e culturais. Em uma era marcada pela digitalização e pela conectividade global, entender o impacto da tecnologia é essencial para se adaptar e prosperar nesse novo paradigma. Uma das áreas mais notáveis de avanço tecnológico é a da comunicação. O surgimento da internet transformou a maneira como as pessoas trocam informações, permitindo a comunicação instantânea e o acesso a um volume vasto de conhecimento. Ferramentas como e-mail, mensagens instantâneas e redes sociais conectam indivíduos em diferentes partes do mundo, criando uma sociedade global interligada. Essa conectividade trouxe benefícios substanciais, como a disseminação de ideias e a promoção de movimentos sociais, mas também levantou desafios significativos, incluindo questões de privacidade e a propagação de desinformação. No campo da saúde, a tecnologia desempenha um papel crucial. Procedimentos médicos que antes eram complexos e arriscados agora são realizados com maior precisão e menos riscos, graças a tecnologias como a robótica cirúrgica e a telemedicina. Dispositivos portáteis de monitoramento permitem que pacientes acompanhem em tempo real seus sinais vitais, melhorando o diagnóstico precoce e a gestão de doenças crônicas. Além disso, avanços na engenharia genética e na biotecnologia abriram portas para tratamentos inovadores, como a edição de genes, que tem o potencial de curar doenças hereditárias. A automação e a inteligência artificial (IA) são outra vertente de destaque. Com algoritmos sofisticados, a IA é capaz de processar grandes volumes de dados, identificar padrões complexos e tomar decisões que antes eram exclusivas do pensamento humano. Isso levou à criação de sistemas que automatizam tarefas repetitivas, aumentando a produtividade em setores como a manufatura, a logística e os serviços financeiros. No entanto, a adoção de tecnologias de automação também suscita debates sobre o futuro do trabalho, uma vez que muitas ocupações tradicionais estão sendo substituídas por máquinas. A educação também tem sido profundamente influenciada pela tecnologia. Plataformas de aprendizado online, cursos virtuais e recursos digitais ampliaram o acesso ao ensino, permitindo que pessoas em locais remotos ou com horários flexíveis adquiram conhecimento. Ferramentas educacionais baseadas em IA podem personalizar a experiência de aprendizado, adaptando o conteúdo e o ritmo conforme as necessidades do aluno. Contudo, a dependência crescente de tecnologias digitais na educação levanta preocupações sobre desigualdade de acesso, uma vez que nem todos os alunos têm os recursos necessários para aproveitar essas inovações. Outro aspecto transformador da tecnologia é o impacto ambiental. Por um lado, o desenvolvimento de tecnologias sustentáveis, como energia solar e eólica, oferece alternativas mais limpas às fontes de energia tradicionais, ajudando a combater as mudanças climáticas. Por outro lado, a produção e o descarte de dispositivos eletrônicos geram grandes quantidades de resíduos e poluentes, exigindo uma gestão mais responsável dos recursos tecnológicos. Inovações em reciclagem e economia circular são fundamentais para minimizar os danos ambientais e promover um uso mais consciente da tecnologia. Finalmente, a ética e a regulamentação tecnológica são questões cada vez mais debatidas. À medida que novas tecnologias emergem, surge a necessidade de estabelecer diretrizes que assegurem um desenvolvimento responsável e equilibrado. Temas como a proteção de dados pessoais, a transparência nos algoritmos e a responsabilidade em casos de falhas tecnológicas exigem a atenção de governos, empresas e da sociedade civil. Somente por meio de um diálogo aberto e de políticas bem-definidas será possível garantir que a tecnologia continue sendo uma força para o bem comum, sem comprometer os direitos individuais e a equidade social. Em suma, a tecnologia está indissociavelmente ligada ao progresso humano, oferecendo tanto oportunidades quanto desafios. O futuro promete avanços ainda mais surpreendentes, com tecnologias emergentes como computação quântica e interfaces cérebro-computador. A capacidade de usar essas ferramentas de forma consciente e ética será um fator determinante para o sucesso e a sustentabilidade da sociedade global.A tecnologia se tornou uma parte fundamental do mundo contemporâneo, moldando a forma como as pessoas vivem, trabalham e interagem. Desde as primeiras invenções, como a roda e a prensa de Gutemberg, até os avanços mais recentes em inteligência artificial e biotecnologia, a evolução tecnológica tem sido um motor propulsor de mudanças econômicas, sociais e culturais. Em uma era marcada pela digitalização e pela conectividade global, entender o impacto da tecnologia é essencial para se adaptar e prosperar nesse novo paradigma. Uma das áreas mais notáveis de avanço tecnológico é a da comunicação. O surgimento da internet transformou a maneira como as pessoas trocam informações, permitindo a comunicação instantânea e o acesso a um volume vasto de conhecimento. Ferramentas como e-mail, mensagens instantâneas e redes sociais conectam indivíduos em diferentes partes do mundo, criando uma sociedade global interligada. Essa conectividade trouxe benefícios substanciais, como a disseminação de ideias e a promoção de movimentos sociais, mas também levantou desafios significativos, incluindo questões de privacidade e a propagação de desinformação. No campo da saúde, a tecnologia desempenha um papel crucial. Procedimentos médicos que antes eram complexos e arriscados agora são realizados com maior precisão e menos riscos, graças a tecnologias como a robótica cirúrgica e a telemedicina. Dispositivos portáteis de monitoramento permitem que pacientes acompanhem em tempo real seus sinais vitais, melhorando o diagnóstico precoce e a gestão de doenças crônicas. Além disso, avanços na engenharia genética e na biotecnologia abriram portas para tratamentos inovadores, como a edição de genes, que tem o potencial de curar doenças hereditárias. A automação e a inteligência artificial (IA) são outra vertente de destaque. Com algoritmos sofisticados, a IA é capaz de processar grandes volumes de dados, identificar padrões complexos e tomar decisões que antes eram exclusivas do pensamento humano. Isso levou à criação de sistemas que automatizam tarefas repetitivas, aumentando a produtividade em setores como a manufatura, a logística e os serviços financeiros. No entanto, a adoção de tecnologias de automação também suscita debates sobre o futuro do trabalho, uma vez que muitas ocupações tradicionais estão sendo substituídas por máquinas. A educação também tem sido profundamente influenciada pela tecnologia. Plataformas de aprendizado online, cursos virtuais e recursos digitais ampliaram o acesso ao ensino, permitindo que pessoas em locais remotos ou com horários flexíveis adquiram conhecimento. Ferramentas educacionais baseadas em IA podem personalizar a experiência de aprendizado, adaptando o conteúdo e o ritmo conforme as necessidades do aluno. Contudo, a dependência crescente de tecnologias digitais na educação levanta preocupações sobre desigualdade de acesso, uma vez que nem todos os alunos têm os recursos necessários para aproveitar essas inovações. Outro aspecto transformador da tecnologia é o impacto ambiental. Por um lado, o desenvolvimento de tecnologias sustentáveis, como energia solar e eólica, oferece alternativas mais limpas às fontes de energia tradicionais, ajudando a combater as mudanças climáticas. Por outro lado, a produção e o descarte de dispositivos eletrônicos geram grandes quantidades de resíduos e poluentes, exigindo uma gestão mais responsável dos recursos tecnológicos. Inovações em reciclagem e economia circular são fundamentais para minimizar os danos ambientais e promover um uso mais consciente da tecnologia. Finalmente, a ética e a regulamentação tecnológica são questões cada vez mais debatidas. À medida que novas tecnologias emergem, surge a necessidade de estabelecer diretrizes que assegurem um desenvolvimento responsável e equilibrado. Temas como a proteção de dados pessoais, a transparência nos algoritmos e a responsabilidade em casos de falhas tecnológicas exigem a atenção de governos, empresas e da sociedade civil. Somente por meio de um diálogo aberto e de políticas bem-definidas será possível garantir que a tecnologia continue sendo uma força para o bem comum, sem comprometer os direitos individuais e a equidade social. Em suma, a tecnologia está indissociavelmente ligada ao progresso humano, oferecendo tanto oportunidades quanto desafios. O futuro promete avanços ainda mais surpreendentes, com tecnologias emergentes como computação quântica e interfaces cérebro-computador. A capacidade de usar essas ferramentas de forma consciente e ética será um fator determinante para o sucesso e a sustentabilidade da sociedade global.A tecnologia se tornou uma parte fundamental do mundo contemporâneo, moldando a forma como as pessoas vivem, trabalham e interagem. Desde as primeiras invenções, como a roda e a prensa de Gutemberg, até os avanços mais recentes em inteligência artificial e biotecnologia, a evolução tecnológica tem sido um motor propulsor de mudanças econômicas, sociais e culturais. Em uma era marcada pela digitalização e pela conectividade global, entender o impacto da tecnologia é essencial para se adaptar e prosperar nesse novo paradigma. Uma das áreas mais notáveis de avanço tecnológico é a da comunicação. O surgimento da internet transformou a maneira como as pessoas trocam informações, permitindo a comunicação instantânea e o acesso a um volume vasto de conhecimento. Ferramentas como e-mail, mensagens instantâneas e redes sociais conectam indivíduos em diferentes partes do mundo, criando uma sociedade global interligada. Essa conectividade trouxe benefícios substanciais, como a disseminação de ideias e a promoção de movimentos sociais, mas também levantou desafios significativos, incluindo questões de privacidade e a propagação de desinformação. No campo da saúde, a tecnologia desempenha um papel crucial. Procedimentos médicos que antes eram complexos e arriscados agora são realizados com maior precisão e menos riscos, graças a tecnologias como a robótica cirúrgica e a telemedicina. Dispositivos portáteis de monitoramento permitem que pacientes acompanhem em tempo real seus sinais vitais, melhorando o diagnóstico precoce e a gestão de doenças crônicas. Além disso, avanços na engenharia genética e na biotecnologia abriram portas para tratamentos inovadores, como a edição de genes, que tem o potencial de curar doenças hereditárias. A automação e a inteligência artificial (IA) são outra vertente de destaque. Com algoritmos sofisticados, a IA é capaz de processar grandes volumes de dados, identificar padrões complexos e tomar decisões que antes eram exclusivas do pensamento humano. Isso levou à criação de sistemas que automatizam tarefas repetitivas, aumentando a produtividade em setores como a manufatura, a logística e os serviços financeiros. No entanto, a adoção de tecnologias de automação também suscita debates sobre o futuro do trabalho, uma vez que muitas ocupações tradicionais estão sendo substituídas por máquinas.";
    vector<string> cod = compression(aux);
    vector<string> ans;
    for(auto it: cod){
        cout << it << endl;
    }
    vector<int> codin = bin2str(cod);
    decompression(codin);
    
}