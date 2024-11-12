<h1>Programa de Ordenação Paralela com Threads</h1>

<h2>Descrição</h2>
<p>Este programa realiza a ordenação de números inteiros lidos a partir de arquivos de entrada. A ordenação é paralelizada, utilizando múltiplas threads para dividir a tarefa, o que melhora o desempenho em sistemas com múltiplos núcleos de CPU. Cada thread ordena uma parte dos dados, e, no final, a última thread realiza uma ordenação global dos dados combinados.</p>
<p>Este projeto é dividido em múltiplos arquivos (<code>mergesort.c</code>, <code>ordenacao.c</code>, e <code>ordenacao.h</code>) para uma organização clara e modular do código.</p>

<h2>Estrutura dos Arquivos</h2>
<strong>mergesort.c:</strong> Contém a função <code>main</code>, onde ocorre a configuração inicial, leitura dos arquivos, criação das threads, sincronização e exibição dos tempos de execução.</li>
<br>
<strong>ordenacao.c:</strong> Implementa as funções de leitura, ordenação e criação de threads, além de lidar com a ordenação paralela e gravação dos resultados no arquivo de saída.</li>
<br>
<strong>ordenacao.h:</strong> Cabeçalho que declara as estruturas de dados e as funções públicas usadas em <code>mergesort.c</code> e <code>ordenacao.c</code>.</li>


<h2>Compilação</h2>

<h3>Requisitos</h3>
<ul>
	<li>GCC (GNU Compiler Collection)</li>
	<li>Biblioteca pthread (nativa no Linux)</li>
</ul>

<h3>Comandos de Compilação</h3>
<p>Você pode compilar o programa manualmente com:</p>
<pre><code>gcc mergesort.c ordenacao.c -o mergesort -lpthread</code></pre>
<p>ou usando o Makefile com o seguinte comando no terminal:</p>
<pre><code>make</code></pre>
<p>O Makefile simplifica o processo de compilação e é especialmente útil em projetos maiores.</p>

<h3>Limpeza dos Arquivos Compilados</h3>
<p>Para remover o executável, use:</p>
<pre><code>make clean</code></pre>

<h2>Execução</h2>
<p>Após a compilação, execute o programa com o comando:</p>
<pre><code>./mergesort &lt;num_threads&gt; &lt;arquivo1&gt; &lt;arquivo2&gt; ... -o &lt;arquivo_saida&gt;</code></pre>

<ul>
	<li><code>&lt;num_threads&gt;</code>: Número de threads para dividir a tarefa de ordenação.</li>
	<li><code>&lt;arquivo1&gt; &lt;arquivo2&gt; ...</code>: Arquivos de entrada contendo números inteiros (um por linha).</li>
	<li><code>-o &lt;arquivo_saida&gt;</code>: Arquivo de saída para salvar o resultado ordenado.</li>
</ul>

<p><strong>Exemplo de uso:</strong></p>
<pre><code>./mergesort 4 dados1.txt dados2.txt -o resultado.txt</code></pre>

<h2>Estrutura e Explicação do Código</h2>

<h3>1. ordenacao.h</h3>
<p>Este cabeçalho declara as estruturas e funções utilizadas para ordenação paralela.</p>

<strong>Estrutura thread_args:</strong> Define os argumentos que cada thread recebe, como o intervalo de dados que irá ordenar, seu ID, e o número total de threads.
<strong>Variáveis Globais:</strong>
<ul>
	<li><code>int* numeros</code>: Vetor dinâmico que armazena todos os números lidos dos arquivos.</li>
	<li><code>int total_numeros</code>: Total de números armazenados em <code>numeros</code>.</li>
</ul>

<strong>Funções Declaradas:</strong>

<ul>
<li><code>int ler_arquivos(int argc, char* argv[])</code>: Lê os arquivos de entrada e armazena os dados no vetor <code>numeros</code>.</li>
<li><code>void* ordenar_dados(void* args)</code>: Função executada por cada thread para ordenar uma parte do vetor <code>numeros</code>.</li>
<li><code>void criar_threads_para_ordenacao(int num_threads, pthread_t* threads, thread_args* args)</code>: Cria e inicializa as threads para dividir o trabalho de ordenação.</li>
<li><code>int gravar_saida(const char* arquivo_saida)</code>: Grava o vetor ordenado no arquivo de saída.</li>
</ul>

<h3>2. ordenacao.c</h3>
<p>Contém as implementações das funções de leitura, ordenação e criação de threads.</p>

<ul>
<li><code>int ler_arquivos(int argc, char* argv[])</code>: Lê números de inteiros a partir dos arquivos fornecidos e armazena no vetor <code>numeros</code>.</li>
<li><code>void* ordenar_dados(void* args)</code>: Ordena uma porção dos dados e mede o tempo de execução individual de cada thread.</li>
<li><code>void criar_threads_para_ordenacao(int num_threads, pthread_t* threads, thread_args* args)</code>: Divide o trabalho entre as threads.</li>
<li><code>int gravar_saida(const char* arquivo_saida)</code>: Grava os dados ordenados no arquivo de saída.</li>
</ul>


<h3>3. mergesort.c</h3>
<p>Contém a função <code>main</code>, onde ocorre a configuração inicial e a execução do programa.</p>

<h3>Fluxo da Função main</h3>

<ul>
<li><strong>Verificação de Argumentos:</strong> Verifica se os argumentos fornecidos são suficientes.</li>
<li><strong>Leitura dos Arquivos:</strong> Carrega os números dos arquivos de entrada.</li>
<li><strong>Criação das Threads:</strong> Inicia as threads para a ordenação.</li>
<li><strong>Sincronização das Threads:</strong> Garante que todas as threads terminem.</li>
<li><strong>Exibição do Tempo de Execução de Cada Thread:</strong> Exibe o tempo gasto por thread.</li>
<li><strong>Exibição do Tempo Total de Execução:</strong> Calcula e exibe o tempo total.</li>
<li><strong>Gravação dos Dados Ordenados:</strong> Salva o vetor ordenado no arquivo de saída.</li>
<li><strong>Liberação de Memória:</strong> Libera o vetor <code>numeros</code>.</li>
</ul>


<h2>Mensagens de Erro</h2>

<li><strong>Falha ao alocar memória:</strong> Caso <code>malloc</code> ou <code>realloc</code> falhe.</li>
<li><strong>Erro ao abrir arquivo:</strong> Quando um arquivo de entrada ou de saída não pode ser acessado.</li>
