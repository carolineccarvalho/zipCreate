<h1 align="center" style="font-weight: bold;">Trabalho Prático de Algoritmos 2</h1>
<p align="center">
 <a href="#tech">Tecnologias</a> • 
 <a href="#intro">Introdução</a> • 
 <a href="#métodos">Métodos e Implementações</a> •
 <a href="#comdes">Funcionamento de Compressão e Descompressão</a> •
 <a href="#testes">Testes e Análise</a> • 
 <a href="#inst">Instruções de Uso</a> • 
 <a href="#colab">Responsáveis</a> •
</p>
<p align="center">
    <b>Este projeto implementa o algoritmo LZW para compressão e descompressão de arquivos, utilizando uma Trie Compacta como estrutura de dados para armazenamento eficiente dos padrões.</b>
</p>

<h2 id="tech"> Tecnologias</h2>

- C++ 
- Python 

<h2 id="intro">Introdução</h2>
    O algoritmo LZW é uma extensão do algoritmo LZ78, com a principal diferença de que o LZW é inicializado com todos os símbolos do alfabeto das cadeias de entrada. Essa modificação permite que o algoritmo seja mais eficiente no processamento de dados, ao eliminar a necessidade de codificar explicitamente os símbolos isolados durante a compressão.

<h2 id="métodos">Métodos e Implementações</h2>
    Este projeto foi desenvolvido em três etapas principais: (1) a implementação do dicionário, (2) a implementação do algoritmo LZW para compressão e descompressão de dados com tamanho fixo, e (3) a implementação do algoritmo LZW para dados de tamanho variável. Todas as funcionalidades implementadas, bem como as escolhas de projeto, serão detalhadas nas seções a seguir.
<h3>Dicionário</h3>
<h4>Estrutura Geral</h4>
    <p>
    O dicionário foi implementado utilizando uma árvore de prefixos compacta. Essa abordagem reduz o consumo de memória ao representar cadeias longas, graças à compactação dos nós, e minimiza operações redundantes. A busca por palavras é realizada percorrendo as arestas da árvore, permitindo um acesso eficiente aos dados armazenados.
    </p>
    <p>
    Foram utilizadas duas classes ao todo. A primeira <code>TrieNode</code>, é responsável por representar os nós da árvore. Cada nó armazena duas informações: os filhos, que indicam se existem possíveis continuações para a cadeia armazenada no nó atual e o código único associado, utilizado para referenciar e diferenciar cada padrão. E a segunda <code>Dicionario</code>, é responsável por gerenciar a árvore de prefixos compacta, além de conectar essa estrutura à funcionalidade de um dicionário ao permitir que seja possível buscar palavras, retornar seus códigos associados, inserir novos padrões e remover entradas existentes.
    </p>
<h4>Funções Principais:</h4>
  <ul>
    <li>Dicionario() e ~Dicionario()</li>
    <p> 
    O construtor <code>Dicionario()</code> é responsável por inicializar a estrutura de dados, criando a raiz da árvore e conectando-a a dois filhos, um com o valor "0" e outro com o valor "1". Essa implementação está relacionada ao algoritmo LZW, que é inicializado com todos os simbolos do alfabeto das cadeias de entrada. Na nossa implementação, apenas esses dois caracteres são adicionados, pois estamos adotando uma implementação que aceitará e retornará cadeias binárias. O destrutor <code>~Dicionario</code> garante a liberação de memória, percorrendo e removendo todos os nós da árvore, evitando vazamentos de memória.
    </p> 
    <li>void insert(const string& chave, const string& codigo)</li>
    <p>
    A função <code>insert()</code> é responsável por inserir novas palavras no dicionário. Para manter a estrutura da Trie Compacta, a inserção é feita da seguinte forma: a partir da raiz, o algoritmo verifica se algum dos filhos começa com o mesmo caractere da chave que queremos adicionar, o que certamente ocorrerá devido à inicialização mencionada anteriormente. Em seguida, o algoritmo verifica se é possível agrupar prefixos em comum com os nós já existentes. Para cada filho, é analisado quanto do prefixo da chave é comum ao valor da aresta do nó. Se nenhum filho correspondente for encontrado, o nó atual é atualizado para incluir a nova chave e o código, criando um novo nó. Caso um filho correspondente seja encontrado, duas situações podem ocorrer: se o tamanho do prefixo comum for igual ao tamanho da aresta, o índice da chave é avançado e o processo continua; se o prefixo comum for menor que o tamanho da aresta, o nó atual é dividido para manter a estrutura compacta.
    </p>
    <li>bool searchTrie(const string& chave)</li>
    <p>
    A função <code>searchTrie()</code> tem como objetivo retornar <code>true</code> caso a string passada como parâmetro esteja presente no dicionário e <code>false</code> caso contrário. A busca segue um processo semelhante ao da função <code>insert()</code>. Começando pela raiz, o algoritmo percorre os filhos dos nós, verificando se existe um prefixo comum com a chave. Se o prefixo comum for igual ao tamanho da aresta, o nó atual é atualizado e o índice da chave é avançado. Se o prefixo comum for menor, a chave não pode ser encontrada e a função retorna <code>false</code>. Se a chave for completamente percorrida e o código do nó final não estiver vazio, a função retorna <code>true</code>, caso contrário, retorna <code>false</code>.
    </p>
    <li>string stringTrie(const string& chave);</li>
    <p>
    A função <code>stringTrie()</code> unciona de maneira semelhante à função <code>searchTrie()</code>, no entanto, em vez de retornar um valor booleano, ela retorna o código associado à chave buscada.
    </p>
    <li>bool deleteTrie(const string& chave);</li>
    <p>
    A função <code>deleteTrie()</code> é responsável por remover uma chave específica do dicionário. Ela utiliza a função auxiliar <code>removeTrie</code>, que realiza a remoção de forma recursiva, garantindo que nenhum nó desnecessário permaneça na estrutura da árvore após a exclusão. Quando a chave é completamente percorrida, seu código é redefinido para "-1", indicando que o nó não representa mais uma chave válida. Se o nó correspondente não possuir filhos, ele é removido. Caso contrário, a função verifica se é possível compactar a estrutura; se sim, realiza a compactação, mantendo a eficiência da árvore. Se a chave não for encontrada, a função retorna <code>false</code>.
    </p>
    </ul>
<h4>Decisões de Projeto</h4>
<h4>Exemplos de Uso</h4>
<ul>
<li>Inserção</li>
<li>Busca</li>
<li>Remoção</li>
</ul>
<h3>LZW de tamanho fixo</h3>
<h3>LZW de tamanho variável</h3>
<h2 id="instrucoes"> Instrucoes de Uso</h2>
<h2 id="testes"> Testes</h2>
<h2 id="colab"> Responsáveis</h2>
    