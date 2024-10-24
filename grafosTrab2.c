#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Sumidouro {
	char nome[20];
	char rotulo[20];
} Sumidouro;

typedef struct Arco {
	char origem[20];
	char destino[20];
} Arco;

typedef struct Nodo { 
	char nome[20];
	char ** vizinhos;
	char ** rotulos;
	int valorRotulos[20];
	int numRotulos;
	int numVizinhos;
} Nodo;

int exists(Nodo * nodos, int numNodos ,char * no) { //checa se o no já está na lista de nos
    int i;
    for(i = 0; i < numNodos;++i) {
        
        if(!strcmp(nodos[i].nome,no)) {
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

int existsVizinhos(char ** vizinhos, int numVizinhos, char * no) {
    int i;
    for(i = 0; i < numVizinhos;++i) {
        
        if(!strcmp(vizinhos[i],no)) {
     //   printf("%c %c\n",nodos[i].nome , no);
            return 1;
        }
    }
    
    return 0;
}

Sumidouro * existsSumidouros(Sumidouro * sumidouros,int numSumidouros, char * no) {
    int i;
    for(i = 0; i < numSumidouros;++i) {
        
        if(!strcmp(sumidouros[i].nome, no)) {
     //   printf("%c %c\n",nodos[i].nome , no);
            return &sumidouros[i];
        }
    }
    
    return NULL;
}

Nodo getNodoByName(Nodo * nodos, int numNodos, char * nome) {
    int i;
    for (i = 0; i < numNodos; ++i) {
        if(!strcmp(nodos[i].nome, nome)) {
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
	
	Sumidouro sumidouros[10000];
	int numSumidouros = 0;
	Arco * arcos =(Arco *) malloc(8000000*sizeof(Arco));
	int i = 0;
	for(;;) {
		
		scanf("%s %s",aux,str); //lê os sumidouros e suas tags
	

		if(str[0] != '[') { //se não for sumidouro
			break;
		}

		strncpy(sumidouros[i].rotulo,&str[1],strlen(str)-2);
		sumidouros[i].rotulo[strlen(sumidouros[i].rotulo)-3] = '\0';
		strcpy(sumidouros[i].nome, aux);
		printf("%s %s\n",sumidouros[i].nome,sumidouros[i].rotulo);	
		++numSumidouros;

		++i;
	}
	printf("LI SUMIDOUROS\n");

	unsigned int j = 0; //ao sair do loop, lê-se os arcos
	strcpy(arcos[j].origem , aux); //origem ja foi lida durante o loop;
	scanf("%s",aux); //lendo destino
	strcpy(arcos[j].destino , aux);
	arcos[j].destino[strlen(arcos[j].destino)-1] = '\0';
	printf("%s -> %s\n",arcos[j].origem,arcos[j].destino);
	++j;
	for(;;) { //enquanto arcos nao acabaram
		scanf("%s",aux); //origem
		if(aux[0] == '}') break;
		strcpy(arcos[j].origem , aux);
		scanf("%s",aux); //seta
		scanf("%s",aux); //destino
		strcpy(arcos[j].destino ,aux);
		arcos[j].destino[strlen(arcos[j].destino)-1] = '\0';

		printf("%s -> %s\n",arcos[j].origem,arcos[j].destino);

		++j;
	}
	
	unsigned int sizearcos = j;
	int sizeSumidouros = i;
    Nodo nodos[10000];
    int numNodos = 0;
	j=0;

	
	for(i=0;i<sizearcos;++i) { //laço que insere nos não-sumidouros em um vetor
        if(!exists(nodos,numNodos,arcos[i].origem)) {//se o nodo não está no vetor
	    
	        strcpy(nodos[numNodos].nome,arcos[i].origem);   //insere o nodo no vetor
	        nodos[numNodos].numVizinhos = 0;
	        nodos[numNodos].numRotulos = 0;
	        nodos[numNodos].rotulos =(char **) malloc(20*sizeof(char *));
	        nodos[numNodos].vizinhos = (char **) malloc(10000*sizeof(char *));
	        
	        
	        
	        for(j=0;j<20;++j) {
	            nodos[numNodos].rotulos[j] = (char *) malloc(20*sizeof(char));
	        }
	        
	        for(j=0;j<10000;++j) {
	            nodos[numNodos].vizinhos[j] = (char *) malloc(20*sizeof(char));
	        }
	        
	        
	        ++numNodos;
	        
	      //  printf("%s\n",nodos[numNodos].nome );
	    }
	}
   //  printf("\n");
    for(i=0;i<numNodos;++i) { //loop para preencher a vizinhança de cada nodo não-sumidouro
        for(j=0; j<sizearcos;++j) {
            //se a origem do arco atual é a mesma do nodo atual, e o vizinho não está na lista
            if(!existsVizinhos(nodos[i].vizinhos,nodos[i].numVizinhos
                ,   arcos[j].destino)&& !strcmp(nodos[i].nome,arcos[j].origem)) {
                    
                nodos[i].vizinhos[ nodos[i].numVizinhos] = arcos[j].destino;
                ++nodos[i].numVizinhos; //incrementa o num de vizinhos do nodo
      //          printf("%c -> %c\n",nodos[i].nome,nodos[i].vizinhos[nodos[i].numVizinhos-1]);
            }
        }
        
 //      printf("%d\n",nodos[i].numVizinhos);
    }
    
    printf("strict digraph resultado_%s {\n\n",nomeGrafo);
    for(i=0;i<numSumidouros;++i) {
        printf("    %s [%s=1];\n",sumidouros[i].nome,sumidouros[i].rotulo);
    }
    char queue[200000][20];
    memset(queue,0,200000);
	unsigned int queueCurrent = 0;
	unsigned int queueSize = 0;
	int idRotulo;
	Sumidouro * sumiAux;
	//int queueSize = 0;
    for(i = 0; i < numNodos; ++i) { //loop para percorrer o grafo, tomando como raíz todos os nodos não-sumidouros
      //  printf("%s->",nodos[i].nome);
        for(j = 0; j < nodos[i].numVizinhos; ++j) {
            strcpy(queue[queueSize], nodos[i].vizinhos[j]);    //enfileira todos os vizinhos do nodo
            ++queueSize;
        }
        
        while(queueCurrent != queueSize) { //enquanto há elementos na fila
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
             //   printf("|%s|",queue[queueCurrent]);
            }
            
            else { //se não é um sumidouro
            //    printf("%s->",queue[queueCurrent]);
                Nodo temp = getNodoByName(nodos,numNodos, queue[queueCurrent]);
                for(j = 0; j < temp.numVizinhos; ++j) {
                    strcpy(queue[queueSize],temp.vizinhos[j]);    //enfileira todos os vizinhos do nodo
                    ++queueSize;
                    queueSize%=200000;
                }
            }
            
            ++queueCurrent;
            queueSize%=200000;
            
        }
        
        printf("    %s [",nodos[i].nome);
        for(j=0;j<nodos[i].numRotulos;++j) {
            
            if(j+1 !=nodos[i].numRotulos)  printf("%s=%d,",nodos[i].rotulos[j],nodos[i].valorRotulos[j]);
            else printf("%s=%d];\n",nodos[i].rotulos[j],nodos[i].valorRotulos[j]);
        }
        idRotulo=-1;
        queueSize=0;
        queueCurrent=0;
    }
    
    for(i=0;i<sizearcos;++i) {
        printf("    %s -> %s;\n",arcos[i].origem,arcos[i].destino);
    }
    
    printf("}\n");
    free(arcos); //faltou o free (eu,2024)









}
