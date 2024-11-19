#include <bits/stdc++.h>
#include <codecvt>
#include <locale>
#include <time.h>
#include "dicionario.h"
#include "compression.h"

int main(){
    cout << "--------------------------------------" << endl;
    cout << "               PROJETO ZIP            " << endl;
    cout << "--------------------------------------" << endl;
    cout << " Caroline Carvalho e Deborah Yamamoto " << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
    int opt, palavrasAdicionadas = 0, numeroResets = 0, texto_original = 0, texto_com_des = 0, an = -1;
    size_t espacoDic;
    while (true) {
        cout << "Opções de execução: " << endl;
        cout << "0: Parar execução" << endl;
        cout << "1: Compressão de arquivo com tamanho fixo" << endl;
        cout << "2: Compressão de arquivo com tamanho variavel" << endl;
        cout << "3: Descompressão arquivo com tamanho fixo" << endl;
        cout << "4: Descompressão arquivo com tamanho variavel" << endl;
        cout << "--------------------------------------" << endl;
        cin >> opt;
        if (opt == 0) {
            cout << "Encerrando o programa." << endl;
            break;
        }

        cout << "Insira o nome do arquivo:" << endl;
        string filename; cin >> filename;
        cout << "--------------------------------------" << endl;
        cout <<  "Insira o máximo de bits que será utilizado (caso não tenha uma resposta, insira 0): " << endl;
        int bit; cin >> bit;
        cout << "--------------------------------------" << endl;
        cout << "     Aguarde, o algoritmo está sendo executado :)" << endl;
        cout << "--------------------------------------" << endl;
        if(!bit) bit = 12;

        if(opt == 1){
            double start_com_f = (double)clock();
            start_com_f = start_com_f/CLOCKS_PER_SEC;
            compressionFixedOPT(filename,bit,palavrasAdicionadas, numeroResets, espacoDic, texto_original, texto_com_des);
            double timeCompressao = (((double)clock())/CLOCKS_PER_SEC) - start_com_f;
            double taxaDeCompressao = 1.0 - ((double)(texto_com_des)/texto_original);
            cout << "--------------------------------------" << endl;
            cout << "Deseja receber estatísticas e análises da compressão realizada?" << endl;
            cout << "0 - Não, apenas processeguir com a execução" << endl;
            cout << "1 - Sim" << endl;
            cin >> an;
            if(an == 1){
                cout << "--------------------------------------" << endl;
                cout << "Padrões Adicionados: "<<palavrasAdicionadas << endl;
                cout << "Numero de Resets: " << numeroResets << endl;
                cout << "Espaco Ocupado pelo Dicionário: " << espacoDic << endl;
                cout << "Tempo de Compressão: " << timeCompressao << endl; 
                cout << "Tamanho Arquivo de Entrada: " << texto_original << endl;
                cout << "Tamanho Texto Comprimido: " << texto_com_des << endl;
                cout << "Taxa de Compressão: " << taxaDeCompressao * 100 << "%" << endl;
                std::ofstream outFile("dados.csv");
                outFile << "palavras_adicionadas,numero_resets,espaco_dicionario,texto_original,texto_com_des,taxa,tempo\n";
                outFile << palavrasAdicionadas << ","
                        << numeroResets << ","
                        << espacoDic << ","
                        << texto_original << ","
                        << texto_com_des << ","
                        << (taxaDeCompressao * 100) << "," 
                        << timeCompressao << "\n";
                outFile.close();
                cout << endl;
                cout << "Atenção, para ter acesso ao relatório com algumas análises das estatísticas geradas, você precisa:" << endl;
                cout << "1. Acesse o seguinte link e siga o protocolo de instalação do Quarto: https://quarto.org/docs/get-started/" << endl;
                cout << "2. Certifique-se de que possui o ambiente configurado corretamente (RStudio, Visual Studio Code ou terminal)." << endl;
                cout << "3. Abra o arquivo 'analiseDados.qmd' no ambiente de sua preferência." << endl;
                cout << "4. Para renderizar o relatório, execute o comando abaixo no terminal:" << endl;
                cout << "   quarto render analiseDados.qmd" << endl;
                cout << "   (Certifique-se de estar no mesmo diretório do arquivo)." << endl;
                cout << "Após a execução, o relatório estará disponível no formato HTML, PDF ou outro, dependendo de como foi configurado." << endl;

            }
             
             cout << "--------------------------------------" << endl;
        } else if(opt == 2){
            double start_com = (double)clock();
            start_com = start_com/CLOCKS_PER_SEC;
            compressionOPT(filename,bit, palavrasAdicionadas, numeroResets, espacoDic, texto_original, texto_com_des);
            double timeCompressao = (((double)clock())/CLOCKS_PER_SEC) - start_com;
            double taxaDeCompressao = 1.0 - ((double)(texto_com_des)/texto_original);
            cout << "--------------------------------------" << endl;
            cout << "Deseja receber estatísticas e análises da compressão realizada?" << endl;
            cout << "0 - Não, apenas processeguir com a execução" << endl;
            cout << "1 - Sim" << endl;
            cin >> an;
            if(an == 1){
                cout << "--------------------------------------" << endl;
                cout << "Padrões Adicionados: "<<palavrasAdicionadas << endl;
                cout << "Numero de Resets: " << numeroResets << endl;
                cout << "Espaco Ocupado pelo Dicionário: " << espacoDic << endl;
                cout << "Tempo de Compressão: " << timeCompressao << endl; 
                cout << "Tamanho Arquivo de Entrada: " << texto_original << endl;
                cout << "Tamanho Arquivo Comprimido: " << texto_com_des << endl;
                cout << "Taxa de Compressão: " << taxaDeCompressao * 100 << "%" << endl;
                std::ofstream outFile("dados.csv");
                outFile << "palavras_adicionadas,numero_resets,espaco_dicionario,texto_original,texto_com_des,taxa,tempo\n";
                outFile << palavrasAdicionadas << ","
                        << numeroResets << ","
                        << espacoDic << ","
                        << texto_original << ","
                        << texto_com_des << ","
                        << (taxaDeCompressao * 100) << "," 
                        << timeCompressao << "\n";
                outFile.close();
                cout << endl;
                cout << "Atenção, para ter acesso ao relatório com algumas análises das estatísticas geradas, você precisa:" << endl;
                cout << "1. Acesse o seguinte link e siga o protocolo de instalação do Quarto: https://quarto.org/docs/get-started/" << endl;
                cout << "2. Certifique-se de que possui o ambiente configurado corretamente (RStudio, Visual Studio Code ou terminal)." << endl;
                cout << "3. Abra o arquivo 'analiseDados.qmd' no ambiente de sua preferência." << endl;
                cout << "4. Para renderizar o relatório, execute o comando abaixo no terminal:" << endl;
                cout << "   quarto render analiseDados.qmd" << endl;
                cout << "   (Certifique-se de estar no mesmo diretório do arquivo)." << endl;
                cout << "Após a execução, o relatório estará disponível no formato HTML, PDF ou outro, dependendo de como foi configurado." << endl;

            }
             cout << "--------------------------------------" << endl;
        } else if(opt == 3){
            double start_des_f = (double)clock();
            start_des_f = start_des_f/CLOCKS_PER_SEC;
            decompressionFixedOPT(filename,bit, palavrasAdicionadas, numeroResets, espacoDic, texto_original, texto_com_des);
            double timeDescompressao_f = (((double)clock())/CLOCKS_PER_SEC) - start_des_f;
            double taxaDescompressao_f = 1.0 - ((double)(texto_original/8)/texto_com_des);
            cout << "--------------------------------------" << endl;
            cout << "Deseja receber estatísticas e análises da compressão realizada?" << endl;
            cout << "0 - Não, apenas processeguir com a execução" << endl;
            cout << "1 - Sim" << endl;
            cin >> an;
            if(an == 1){
                cout << "--------------------------------------" << endl;
                cout << "Padrões Adicionados: "<<palavrasAdicionadas << endl;
                cout << "Numero de Resets: " << numeroResets << endl;
                cout << "Espaco Ocupado pelo Dicionário: " << espacoDic << endl;
                cout << "Tempo de Descompressão: " << timeDescompressao_f << endl; 
                cout << "Tamanho Texto de Entrada: " << texto_original/8 << endl;
                cout << "Tamanho Texto Descomprimido: " << texto_com_des << endl;
                cout << "Taxa de Descompressão: " << taxaDescompressao_f * 100 << "%" << endl;
                std::ofstream outFile("dados.csv");
                outFile << "palavras_adicionadas,numero_resets,espaco_dicionario,texto_original,texto_com_des,taxa,tempo\n";
                outFile << palavrasAdicionadas << ","
                        << numeroResets << ","
                        << espacoDic << ","
                        << texto_original << ","
                        << texto_com_des << ","
                        << (taxaDescompressao_f * 100) << "," 
                        << timeDescompressao_f << "\n";
                outFile.close();
                cout << endl;
                cout << "Atenção, para ter acesso ao relatório com algumas análises das estatísticas geradas, você precisa:" << endl;
                cout << "1. Acesse o seguinte link e siga o protocolo de instalação do Quarto: https://quarto.org/docs/get-started/" << endl;
                cout << "2. Certifique-se de que possui o ambiente configurado corretamente (RStudio, Visual Studio Code ou terminal)." << endl;
                cout << "3. Abra o arquivo 'analiseDados.qmd' no ambiente de sua preferência." << endl;
                cout << "4. Para renderizar o relatório, execute o comando abaixo no terminal:" << endl;
                cout << "   quarto render analiseDados.qmd" << endl;
                cout << "   (Certifique-se de estar no mesmo diretório do arquivo)." << endl;
                cout << "Após a execução, o relatório estará disponível no formato HTML, PDF ou outro, dependendo de como foi configurado." << endl;

            }
             cout << "--------------------------------------" << endl;
        }else if(opt ==4){
            double start_des = (double)clock();
            start_des = start_des/CLOCKS_PER_SEC;
            decompressionOPT(filename,bit, palavrasAdicionadas, numeroResets, espacoDic, texto_original, texto_com_des);
            double timeDescompressao = (((double)clock())/CLOCKS_PER_SEC) - start_des;
            double taxaDescompressao = 1.0 - ((double)(texto_original/8)/texto_com_des);
            cout << "--------------------------------------" << endl;
            cout << "Deseja receber estatísticas e análises da compressão realizada?" << endl;
            cout << "0 - Não, apenas processeguir com a execução" << endl;
            cout << "1 - Sim" << endl;
            cin >> an;
            if(an == 1){
                cout << "--------------------------------------" << endl;
                cout << "Padrões Adicionados: "<<palavrasAdicionadas << endl;
                cout << "Numero de Resets: " << numeroResets << endl;
                cout << "Espaco Ocupado pelo Dicionário: " << espacoDic << endl;
                cout << "Tempo de Descompressão: " << timeDescompressao << endl; 
                cout << "Tamanho Arquivo de Entrada: " << texto_original/8 << endl;
                cout << "Tamanho Texto Descomprimido: " << texto_com_des << endl;
                cout << "Taxa de Descompressão: " << taxaDescompressao * 100 << "%" << endl;
            }
            std::ofstream outFile("dados.csv");
                outFile << "palavras_adicionadas,numero_resets,espaco_dicionario,texto_original,texto_com_des,taxa,tempo\n";
                outFile << palavrasAdicionadas << ","
                        << numeroResets << ","
                        << espacoDic << ","
                        << texto_original << ","
                        << texto_com_des << ","
                        << (taxaDescompressao * 100) << "," 
                        << timeDescompressao << "\n";
                outFile.close();
                cout << endl;
                cout << "Atenção, para ter acesso ao relatório com algumas análises das estatísticas geradas, você precisa:" << endl;
                cout << "1. Acesse o seguinte link e siga o protocolo de instalação do Quarto: https://quarto.org/docs/get-started/" << endl;
                cout << "2. Certifique-se de que possui o ambiente configurado corretamente (RStudio, Visual Studio Code ou terminal)." << endl;
                cout << "3. Abra o arquivo 'analiseDados.qmd' no ambiente de sua preferência." << endl;
                cout << "4. Para renderizar o relatório, execute o comando abaixo no terminal:" << endl;
                cout << "   quarto render analiseDados.qmd" << endl;
                cout << "   (Certifique-se de estar no mesmo diretório do arquivo)." << endl;
                cout << "Após a execução, o relatório estará disponível no formato HTML, PDF ou outro, dependendo de como foi configurado." << endl;

             cout << "--------------------------------------" << endl;
        }else{
            cout << "Escolha uma opção válida" << endl;
             cout << "--------------------------------------" << endl;
        }
       
 
    }


}