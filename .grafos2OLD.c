#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Sumidouro {
	char nome;
	char rotulo[10];
} Sumidouro;

typedef struct Aresta {
	char origem;
	char destino;
} Aresta;

typedef struct Nodo {


	char nome;
	char vizinhos[100];
	char ** rotulos;
	int valorRotulos[20];
	int numRotulos;
	int numVizinhos;
} Nodo;

int exists(Nodo * nodos, int numNodos ,char no) { //checa se o no já está na lista de nos
    int i;
    for(i = 0; i < numNodos;++i) {
        
        if(nodos[i].nome == no) {
     //   printf("%c %c\n",nodos[i].nome , no);
            return 1;
        }
    }
    
    return 0;
}

int existsRotulo(char **rotulos, int numRotulos, char * rotulo) { //retorna id do rotulo
    int i;
    for(i=0;i<numRotulos;++i) {
        if(!strcmp(rotulos[i],rotulo)) { //se o rotulo já existe
            return i;
        }
    }
    
    return -1;
    
}

int existsVizinhos(char * vizinhos, int numVizinhos, char no) {
    int i;
    for(i = 0; i < numVizinhos;++i) {
        
        if(vizinhos[i] == no) {
     //   printf("%c %c\n",nodos[i].nome , no);
            return 1;
        }
    }
    
    return 0;
}

Sumidouro * existsSumidouros(Sumidouro * sumidouros,int numSumidouros, char no) {
    int i;
    for(i = 0; i < numSumidouros;++i) {
        
        if(sumidouros[i].nome == no) {
     //   printf("%c %c\n",nodos[i].nome , no);
            return &sumidouros[i];
        }
    }
    
    return NULL;
}

Nodo getNodoByName(Nodo * nodos, int numNodos, char nome) {
    int i;
    for (i = 0; i < numNodos; ++i) {
        if(nodos[i].nome == nome) {
            return nodos[i];
        }
    } 

}
void main() {
    char nomeGrafo[50];
	char aux[20];	//recebe um char
	char str[20]; //recebe uma string
	scanf("%s",str); //consome as 4 primeiras strings
	scanf("%s",str); 
	scanf("%s",nomeGrafo); 
	scanf("%s",str); 
	
	Sumidouro sumidouros[100];
	int numSumidouros = 0;
	Aresta arestas[200];
	int i = 0;
	for(;;) {
		
		scanf("%s %s",aux,str); //lê os sumidouros e suas tags
	

		if(str[0] != '[') { //se não for sumidouro
			break;
		}

		strncpy(sumidouros[i].rotulo,&str[1],strlen(str)-2);
		sumidouros[i].rotulo[strlen(sumidouros[i].rotulo)-3] = '\0';
		sumidouros[i].nome = aux[0];
		printf("%c %s\n",sumidouros[i].nome,sumidouros[i].rotulo);	
		++numSumidouros;

		++i;
	}
	int j = 0; //ao sair do loop, lê-se as arestas
	arestas[j].origem = aux[0]; //origem ja foi lida durante o loop;
	scanf("%s",aux); //lendo destino
	arestas[j].destino = aux[0];
	printf("%c -> %c\n",arestas[j].origem,arestas[j].destino);
	++j;
	for(;;) { //enquanto arestas nao acabaram
		scanf("%s",aux); //origem
		if(aux[0] == '}') break;
		arestas[j].origem = aux[0];
		scanf("%s",aux); //seta
		scanf("%s",aux); //destino
		arestas[j].destino = aux[0];

		printf("%c -> %c\n",arestas[j].origem,arestas[j].destino);

		++j;
	}
	
	int sizeArestas = j;
	int sizeSumidouros = i;
    Nodo nodos[100];
    int numNodos = 0;
	j=0;

	
	for(i=0;i<sizeArestas;++i) { //laço que insere nos não-sumidouros em um vetor
        if(!exists(nodos,numNodos,arestas[i].origem)) {//se o nodo não está no vetor
	    
	        nodos[numNodos].nome = arestas[i].origem;   //insere o nodo no vetor
	        nodos[numNodos].numVizinhos = 0;
	        nodos[numNodos].numRotulos = 0;
	        nodos[numNodos].rotulos =(char **) malloc(20*sizeof(char *));
	        
	        for(j=0;j<20;++j) {
	            nodos[numNodos].rotulos[j] = (char *) malloc(10*sizeof(char));
	        }
	        ++numNodos;
	        
	   //     printf("%c\n",nodos[numNodos].nome );
	    }
	}
   //  printf("\n");
    for(i=0;i<numNodos;++i) { //loop para preencher a vizinhança de cada nodo não-sumidouro
        for(j=0; j<sizeArestas;++j) {
            //se a origem da aresta atual é a mesma do nodo atual, e o vizinho não está na lista
            if(!existsVizinhos(nodos[i].vizinhos,nodos[i].numVizinhos
                ,arestas[j].destino)&& nodos[i].nome == arestas[j].origem) {
                    
                nodos[i].vizinhos[ nodos[i].numVizinhos] = arestas[j].destino;
                ++nodos[i].numVizinhos; //incrementa o num de vizinhos do nodo
      //          printf("%c -> %c\n",nodos[i].nome,nodos[i].vizinhos[nodos[i].numVizinhos-1]);
            }
        }
        
 //      printf("%d\n",nodos[i].numVizinhos);
    }
    
    char queue[100];
    memset(queue,0,100);
	int queueCurrent = 0;
	int queueSize = 0;
	int idRotulo;
	Sumidouro * sumiAux;
	//int queueSize = 0;
    for(i = 0; i < numNodos; ++i) { //loop para percorrer o grafo, tomando como raíz todos os nodos não-sumidouros
        printf("%c->",nodos[i].nome);
        for(j = 0; j < nodos[i].numVizinhos; ++j) {
            queue[queueSize] = nodos[i].vizinhos[j];    //enfileira todos os vizinhos do nodo
            ++queueSize;
        }
        
        while(queueCurrent < queueSize) { //enquanto há elementos na fila
            if(sumiAux = existsSumidouros(sumidouros,numSumidouros,queue[queueCurrent])) { //se é um sumidouro, incrementa a tag do nodo atual            
                if(-1 == (idRotulo = existsRotulo(nodos[i].rotulos,nodos[i].numRotulos,sumiAux->rotulo))) { //se o rotulo nao existe no nodo
                    
                    nodos[i].valorRotulos[nodos[i].numRotulos] = 1;
                    strcpy(nodos[i].rotulos[nodos[i].numRotulos],sumiAux->rotulo);
                    ++nodos[i].numRotulos;
                   // puts("novo\n");
               //     printf("\n%c: %s=%d \n",nodos[i].nome,sumiAux->rotulo,nodos[i].valorRotulos[nodos[i].numRotulos-1]);
                }
                
                else { //se o nodo ja existe
                    nodos[i].valorRotulos[idRotulo] +=1;
                  //  printf("%d repetido\n", idRotulo);
             //        printf("\n%c: %s=%d \n",nodos[i].nome,sumiAux->rotulo,nodos[i].valorRotulos[idRotulo]);
                }
                printf("|%c|",queue[queueCurrent]);
            }
            
            else { //se não é um sumidouro
                printf("%c->",queue[queueCurrent]);
                Nodo temp = getNodoByName(nodos,numNodos, queue[queueCurrent]);
                for(j = 0; j < temp.numVizinhos; ++j) {
                    queue[queueSize] = temp.vizinhos[j];    //enfileira todos os vizinhos do nodo
                    ++queueSize;
                }
            }
            
            ++queueCurrent;
            
        }
        printf("\n");
        idRotulo=-1;
        queueSize=0;
        queueCurrent=0;
    }









}
