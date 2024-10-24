Autor: Leonardo Joji Takii, GRR20153683, UFPR.

Trabalho de Grafos: Número de caminhos a partir de um vértice "v" até sumidouros "s" com rótulos "tn", para 
todos os vértices não-sumidouros de um grafo direcionado acíclico.

Limites do programa:
	É desejado que não haja arcos idênticos.
	Nomes dos vértices podem ter até 20 caracteres.
	Rótulos podem ter até 20 caracteres.
	Um sumidouro deve ter apenas 1 rótulo.
	O número de um caminhos para um determinado rótulo é corretamente representado até "32,767", por
	conta da limitação de tamanho do tipo "int" da linguagem "C".
	O nome do grafo pode ter até 50 caracteres.
	O número máximo de arcos é "10,000".
	O número máximo de vértices não-sumidouros é "10,000".
	O número máximo de vértices sumidouros é "10,000".
	O número máximo de vizinhos de um vértice é "10,000".
	O número máximo de elementos na fila é "10,000".

Funcionamento do algoritmo:

/////////////////	
LEITURA DOS DADOS
/////////////////
	A partir da entrada padrão, é feito um parse relativo a um documento ".dot".

		O nome do grafo é armazenado para uso futuro;
		Enquanto há sumidouros para serem lidos:
			O nome do sumidouro e sua etiqueta são armazenados em um vetor de sumidouros;
			Um contador que indica o número de sumidouros é incrementado em 1;

		Enquanto há arcos para serem lidos:
			A origem e o destino de cada arco são armazenados em um vetor de arcos;
			Um contador que indica o número de arcos é incrementado em 1;

		Enquanto há arcos não lidos no vetor de arcos:
				A origem de cada arco é inserida em um vetor de vértices;
				Um contador que indica o número de vértices é incrementado em 1;

		Enquanto há vértices não lidos no vetor de vértices:
				Enquanto há arcos não lidos no vetor de arcos:
					Se o nome da origem do arco atual é igual ao nome do vértice atual
						Se o nome do destino do arco atual não está no vetor de vizinhos do nó atual
							O nome destino do arco atual é inserido em um vetor de vizinhos do nó atual;
							Um contador que indica o número de vizinhos é incrementado em 1;

//////////////////	
BUSCA DOS CAMINHOS
//////////////////
	Enquanto há nós não processados na lista de nós:
		Enfileira todos os vizinhos do nó raíz atual;
			Enquanto há elementos na fila:
				Se o elemento atual da fila é um sumidouro
					Se o rótulo do sumidouro não existe na lista de rótulos do nó raiz atual
						Insere o rótulo na lista de rótulos do nó raiz atual;
					
					Incrementa em 1 o contador deste rótulo no nó raiz atual;
				Senão
					Enfileira todos os vizinhos do nó atual;

				Desenfileira o nó atual da fila;



/////////////////	
ESCRITA DOS DADOS
/////////////////
	A partir da saída padrão, todos os dados obtidos são escritos no formato ".dot".






/////////////////////////////
DESCRIÇÃO DO PROFESSOR RENATO
/////////////////////////////
O objetivo deste trabalho é contar o número de caminhos em um grafo direcionado acíclico, a partir de cada um de seus vértices, que terminam em vértices sumidouros marcados com rótulos. Por exemplo, no grafo do jogo da velha do trabalho 1, esta contagem representa o número de maneiras que levam à vitória de cada um dos jogadores ou ao empate a partir de cada configuração do jogo.

Dado um grafo direcionado acíclico onde os vértices sumidouros podem ter atributos numéricos, queremos contar, para cada vértice v, quantos caminhos iniciando em v terminam em sumidouros com mesmos atributos, e colocar atributos em v com o resultado.

Por exemplo, o resultado para o seguinte grafo de entrada,

strict digraph exemplo {

  X [FIM=1];
  Y [FIM=1];
  Z [OUTRO=1];

  A -> B;
  A -> C;
  B -> X;
  B -> Y;
  B -> Z;
  C -> Y;
  C -> Z;
}

seria

strict digraph resultado_exemplo {

   X [FIM=1];
   Y [FIM=1];
   Z [OUTRO=1];
   A [FIM=3,OUTRO=2];
   B [FIM=2,OUTRO=1];
   C [FIM=1,OUTRO=1];
   A -> B;
   A -> C;
   B -> X;
   B -> Y;
   B -> Z;
   C -> Y;
   C -> Z;
}

Você deve fazer um programa que receba na entrada padrão um grafo direcionado acíclico descrito na linguagem dot, com os vértices sumidouros com atributos numéricos (sempre iguais a 1). O programa deve escrever na saída padrão outro grafo (também em linguagem dot) onde cada vértice v tem atributos [t1=n1,t2=n2,...] indicando que existem n1 caminhos de v a algum sumidouro com o atributo [t1=1], n2 caminhos de v a algum sumidouro com o atributo [t2=1], e assim por diante, como no exemplo acima.

A implementação pode ser feita em qualquer linguagem de programação menos Java.

Bibliotecas de manipulação de grafos da linguagem escolhida podem ser usadas para entrada e saída de grafos no formato dot. As estruturas de dados para a representação dos grafos oferecidas por tais bibliotecas também podem ser usadas. Demais algoritmos implementados nessas bibliotecas não devem ser usados.

Por exemplo, a biblioteca cgraph (que faz parte do pacote GraphViz) pode ser usada para fazer a leitura dos arquivos na linguagem dot.

A biblioteca cgraph implementa (entre outras coisas) uma estrutura de dados para a manipulação de grafos e um interpretador ("parser") da linguagem dot.

Em trabalho-2.tar.gz está um exemplo de uso da biblioteca cgraph para leitura de um grafo. O exemplo consiste de um programa em C e um makefile para compilá-lo e ligá-lo com a biblioteca cgraph. O programa lê um grafo na entrada padrão e escreve na saída padrão alguns parâmetros do grafo lido, seus vértices e os atributos de seus vértices.

O pacote GraphViz é distribuido livremente para diversas plataformas.

Em particular, nas distribuições de GNU/Linux baseadas na distribuição Debian, basta instalar o pacote libgraphviz-dev. Recomenda-se também instalar os pacotes graphviz (utilitários, especialmente para desenhar grafos) e graphviz-doc (documentação adicional). Estes pacotes estão instalados nos servidores da rede do Departamento de Informática.

O trabalho deve ser entregue sob a forma de um arquivo de nome fulano-sicrano.tar.gz, sendo que fulano e sicrano devem ser substituídos pelos login name dos autores.

O arquivo fulano-sicrano.tar.gz, uma vez expandido, deve criar os seguintes arquivos.
fulano-sicrano/readme.txt:
 	arquivo que deve ser usado para comunicar tudo que seja relevante para a correção do trabalho; em particular, este arquivo deve ter uma descrição "em alto nível" do algoritmo usado pela sua implementação
fulano-sicrano/makefile:
 	um makefile que gera o executável conta-caminhos

Assim, a seguinte sequência de comandos executada a partir do diretório que contém os arquivos fulano-sicrano.tar.gz e grafo.dot deve executar seu programa.

tar --extract --gunzip --file=fulano-sicrano.tar.gz
cd fulano-sicrano
make
./conta-caminhos < ../grafo.dot

O arquivo fulano-sicrano.tar.gz deve ser entregue como anexo de mensagem enviada para renato.carmo.rc@gmail.com (turma A) ou andre@inf.ufpr.br (turma B). O "Subject:" desta mensagem deve ser "Entrega do trabalho 2".

O prazo para a entrega é 07/05/2017, às 23h59min.