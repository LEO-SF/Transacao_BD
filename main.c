#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#define MAX 10
#define MAXIMO 50
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
FILE *fptr;

typedef struct {
    int id;
    char nome[50];
    char cpf[50];
    char gasto1[50];
    char gasto2[50];
} tA1; //estrutura de dados da tabela 1 - Clientes

typedef struct{
    tA1 tabela[MAX];
    int nroElem;
} tAbela1; //tabela 1 - Clientes

typedef struct{
	char tabela [20];
	char bvalor[50];
	char valor [50];
	int id;
	int inicio;
	int fim;
}transacao; //estrutura da transação

typedef struct{
    transacao tabela[MAXIMO];
    int nroElem;
    int contador;
} lTransacoes; //Lista de transações

void menu() { //MENU PARA AS OPÇÕES
    printf("\nEscolha uma das opcoes abaixo para navegar\n");
    printf("\nDADOS\n");
	printf("\na - Mostrar dados da memória");
	printf("\nb - Mostrar dados do disco");
	printf("\nc - Mostrar log do disco");
	
    printf("\n\nOPERAÇÕES\n");
    printf("\nd - Transações");
    printf("\ne - Checkpoint");
	printf("\nf - Simular Falha");
} 

void inicializar(tAbela1* t) { //inicia a lista, e passa como parâmetro o endereço da
//estrutura original
      t->nroElem = 0; //”l” parâmetro do tipo lista, que recebe “0” números de elementos;
}

void inicializarT(lTransacoes* l) { //inicia a lista, e passa como parâmetro o endereço da
//estrutura original
      l->nroElem = 0; //”l” parâmetro do tipo lista, que recebe “0” números de elementos;
      l->contador = 0 ;
}

void inserir_transacao(lTransacoes *t, transacao reg, tAbela1 *m, lTransacoes *d, tAbela1 *disco){
	int escolha, i = 0,  j = 0, z = 0, y = 0, w = 0, a = 1, b = 1, c = 1, f, igual,opcaoT, retomar; 
	char valor[50];

	do{ 
	    for (j=0; j < t->nroElem; j++){
	
        if(t->tabela[j].inicio != 0){
	
        printf("<T%d, ", t->tabela[j].inicio);
        printf("%d, ", t->tabela[j].id);
        printf("%s, ", t->tabela[j].tabela);
        printf("%s, ", t->tabela[j].bvalor);
        printf("%s", t->tabela[j].valor);
        printf(">\n");

        	}
        if(strcmp(t->tabela[j].valor, "checkpoint") == 0){
        	printf("CHECKPOINT\n");
           }
           
	    }
	    
	    printf("\nUNDO: "); 
	    
	    a = 1;
	    
	    for(a = 1; a <= t->contador; a++){
	    	c = 0;
	    	for(i = 0; i < t->nroElem; i++){
	    		if(t->tabela[i].inicio == a && t->tabela[i].fim == 0){
	    			c = 1;
				}
	        }
	        if(c == 1){
	        	printf("T%d ", a);
			}
		}
		
		printf("\nREDO: ");
		
		for(i = 0; i < t->nroElem; i++){//FOR PARA PERCORRER A LISTA
		if(t->tabela[i].inicio == 0){ //SE ALGUM INICIO FOR = 0 (CHECKPOINT) IRÁ INICIAR A TRANSFERÊNCIA DAQUI
		    f = i+1;
		   }
	    }
        
	    for(a = 1; a <= t->contador; a++){
	    	c = 0;
	    	for(w = f ; w < t->nroElem; w++){
	    		if(t->tabela[w].inicio == a && t->tabela[w].fim == 1){
	    			c = 1;
				}
	        }
	        if(c == 1){
	        	printf("T%d ", a);
			}
		}
				
		w = 0;
		
		printf("\n");
	    
		printf("\n1 - Iniciar Transação");
		printf("\n2 - Retomar Transação");
		printf("\n3 - Voltar");
		printf("\nOpção:");
		scanf("%d", &escolha);
		
		system("cls");
		if(escolha == 1){
			
			t->contador++;
			
			do{
			printf("\n1 - Inserir");
		    printf("\n2 - Commit");
			printf("\n3 - Voltar");
			printf("\nOpção:");
			scanf("%d", &opcaoT);
			if(opcaoT == 1){ //INSERIR TRANSAÇÃO

			printf("\nupgrade clientes");
			printf("\n(NOME, CPF, CHURRASCO, SUSHI)");
			printf("\nset ");scanf("%s ", &reg.tabela); gets(reg.valor);
			printf("where id = "); scanf("%d", &reg.id);
			t -> tabela[t -> nroElem] = reg;
			t ->tabela[t->nroElem].fim = 0;
			t ->tabela[t->nroElem].inicio = t -> contador; //inicio é igual à transações iniciada
	     	
	     	if(strcmp(reg.tabela, "nome") == 0){ //ESTRUTURA PEGAR VALOR ANTIGO
				strcpy(t->tabela[t->nroElem].bvalor, disco->tabela[reg.id-1].nome);
			}else if(strcmp(reg.tabela, "cpf") == 0){
				strcpy(t->tabela[t->nroElem].bvalor, disco->tabela[reg.id-1].cpf);
			}else if(strcmp(reg.tabela, "churrasco") == 0){
				strcpy(t->tabela[t->nroElem].bvalor, disco->tabela[reg.id-1].gasto1);
				} else{
				if(strcmp(reg.tabela, "sushi") == 0){
				strcpy(t->tabela[t->nroElem].bvalor, disco->tabela[reg.id-1].gasto2);
				}
			}
			
			t->nroElem++;
			//d->nroElem = t->nroElem;
	     	
			if(strcmp(reg.tabela, "nome") == 0){ //ESTRUTURA PRA ALTERAR EM MEMÓRIA
				strcpy(m->tabela[reg.id-1].nome, reg.valor);
			}else if(strcmp(reg.tabela, "cpf") == 0){
				strcpy(m->tabela[reg.id-1].cpf, reg.valor);
			}else if(strcmp(reg.tabela, "churrasco") == 0){
				strcpy(m->tabela[reg.id-1].gasto1, reg.valor);
				} else{
				if(strcmp(reg.tabela, "sushi") == 0){
				strcpy(m->tabela[reg.id-1].gasto2, reg.valor);
				}
			}
						
		    }else{
		    	if(opcaoT == 2){//DAR COMMIT
		    		 
		        for(z = 0; z < t->nroElem; z++){
		            if(t->tabela[z].inicio == t ->contador){
		        		t->tabela[z].fim = 1;
		        		d->tabela[z].id = t->tabela[z].id;
		        		strcpy(d->tabela[z].tabela, t->tabela[z].tabela);
		        		strcpy(d->tabela[z].bvalor, t->tabela[z].bvalor);
		        		strcpy(d->tabela[z].valor, t->tabela[z].valor);
		        		d->tabela[z].inicio = t->tabela[z].inicio;
		        		d->tabela[z].fim = t->tabela[z].fim;
						d->nroElem++;	        			
					}			
				}
		    	//FAZER UM FOR PARA ALTERAR O REG.FIM DE TODAS AS LINHAS DA TRANSAÇÃO = i_escolha E
		    	//ENVIAR PARA O LOG DE DISCO
				}
			}
		    
			}while(opcaoT != 3);
		
		}else{
			if(escolha == 2){//RETOMAR TRANSAÇÃO
			
			//system("cls");
			printf("\nQual transação deseja retomar: T");
			scanf("%d", &retomar);
			for(y = 0; y < t->nroElem; y++){
				if(t->tabela[y].inicio == retomar){
				printf("\nupgrade clientes");
			    printf("\n(NOME, CPF, CHURRASCO, SUSHI)");
		     	printf("\nset ");printf("%s ", t->tabela[y].tabela);printf("%s", t->tabela[y].valor);
			    printf("\nwhere id = "); printf("%d\n", t->tabela[y].id);
			    }
			}
			do{
				
			printf("\n1 - Inserir");
		    printf("\n2 - Commit");
			printf("\n3 - Voltar");
			printf("\nOpção:");
			scanf("%d", &opcaoT);
			
			if(opcaoT == 1){ //INSERIR TRANSAÇÃO
			
			printf("\nupgrade clientes");
			printf("\n(NOME, CPF, CHURRASCO, SUSHI)");
			printf("\nset ");scanf("%s ", &reg.tabela); gets(reg.valor);
			printf("where id = "); scanf("%d", &reg.id);
			t -> tabela[t -> nroElem] = reg;
			t ->tabela[t->nroElem].fim = 0;
			t ->tabela[t->nroElem].inicio = retomar; //inicio é igual à transações iniciada

			
			if(strcmp(reg.tabela, "nome") == 0){ //ESTRUTURA PEGAR VALOR ANTIGO
				strcpy(t->tabela[t->nroElem].bvalor, disco->tabela[reg.id-1].nome);
			}else if(strcmp(reg.tabela, "cpf") == 0){
				strcpy(t->tabela[t->nroElem].bvalor, disco->tabela[reg.id-1].cpf);
			}else if(strcmp(reg.tabela, "churrasco") == 0){
				strcpy(t->tabela[t->nroElem].bvalor, disco->tabela[reg.id-1].gasto1);
				} else{
				if(strcmp(reg.tabela, "sushi") == 0){
				strcpy(t->tabela[t->nroElem].bvalor, disco->tabela[reg.id-1].gasto2);
				}
			}
			
			t->nroElem++;
			//d->nroElem = t->nroElem;
	     	
			if(strcmp(reg.tabela, "nome") == 0){ //ESTRUTURA PRA ALTERAR EM MEMÓRIA
				strcpy(m->tabela[reg.id-1].nome, reg.valor);
			}else if(strcmp(reg.tabela, "cpf") == 0){
				strcpy(m->tabela[reg.id-1].cpf, reg.valor);
			}else if(strcmp(reg.tabela, "churrasco") == 0){
				strcpy(m->tabela[reg.id-1].gasto1, reg.valor);
				} else{
				if(strcmp(reg.tabela, "sushi") == 0){
				strcpy(m->tabela[reg.id-1].gasto2, reg.valor);
				}
			}
			
		    }else{
		    	if(opcaoT == 2){//DAR COMMIT
		    		 
		        for(z = 0; z < t->nroElem; z++){
		            if(t->tabela[z].inicio == retomar){
		        		t->tabela[z].fim = 1;
		        		d->tabela[z].id = t->tabela[z].id;
		        		strcpy(d->tabela[z].tabela, t->tabela[z].tabela);
		        		strcpy(d->tabela[z].bvalor, t->tabela[z].bvalor);
		        		strcpy(d->tabela[z].valor, t->tabela[z].valor);
		        		d->tabela[z].inicio = t->tabela[z].inicio;
		        		d->tabela[z].fim = t->tabela[z].fim;
						d->nroElem++;	        			
					}
				
				}
		    	//FAZER UM FOR PARA ALTERAR O REG.FIM DE TODAS AS LINHAS DA TRANSAÇÃO = i_escolha E
		    	//ENVIAR PARA O LOG DE DISCO
				}
			}
			
			
			}while(opcaoT !=3);
		}
			
			}
				
		system("cls");
		
	}while(escolha != 3);
    system("cls");
}

void inserir(tAbela1 * t, tA1 dado, int i){
	t -> tabela[i].id = dado.id;
	strcpy(t->tabela[i].nome,dado.nome);
	strcpy(t->tabela[i].cpf,dado.cpf);
	strcpy(t->tabela[i].gasto1,dado.gasto1);
	strcpy(t->tabela[i].gasto2,dado.gasto2);
}

void exibirdisco(tAbela1 *t){
	int i;
	printf("|--------------------------------------------------------------------------|\n");
	printf("|TABELA DISCO - CLIENTES                                                   |\n");
	printf("|--------------------------------------------------------------------------|\n");
	printf("|%-10s %-20s %-18s %-10s %10s  |\n", "ID", "NOME", "CPF", "CHURRASCO", "SUSHI");
	printf("|--------------------------------------------------------------------------|\n");
    for (i=0; i < MAX; i++){

    printf("|%-10d %-20s %-18s %s %15s  |\n", t->tabela[i].id, t->tabela[i].nome, t->tabela[i].cpf, t->tabela[i].gasto1, t->tabela[i].gasto2);
	printf("|--------------------------------------------------------------------------|\n");  

}
    printf("\n");
}

void exibirmemoria(tAbela1 *t){
	int i;
	printf("|--------------------------------------------------------------------------|\n");
	printf("|TABELA MEMÓRIA - CLIENTES                                                 |\n");
	printf("|--------------------------------------------------------------------------|\n");
	printf("|%-10s %-20s %-18s %-10s %10s  |\n", "ID", "NOME", "CPF", "CHURRASCO", "SUSHI");
	printf("|--------------------------------------------------------------------------|\n");
    for (i=0; i < MAX; i++){

    printf("|%-10d %-20s %-18s %s %15s  |\n", t->tabela[i].id, t->tabela[i].nome, t->tabela[i].cpf, t->tabela[i].gasto1, t->tabela[i].gasto2);
	printf("|--------------------------------------------------------------------------|\n");  

}
    printf("\n");
}

void log_disco(lTransacoes *d, lTransacoes *t){
	int j = 0, i = 0, w = 0, a = 0, b = 0;
    
    d->contador = t->contador;
    
	for (j=0; j <= MAX; j++){
	
        if(d->tabela[j].inicio != 0){
		
        printf("<T%d, ", d->tabela[j].inicio);
        printf("%d, ", d->tabela[j].id);
        printf("%s, ", d->tabela[j].tabela);
        printf("%s, ", d->tabela[j].bvalor);
        printf("%s", d->tabela[j].valor);
        printf(">");
        printf("\n");

		}
		      
		if(strcmp(d->tabela[j].valor, "checkpoint") == 0){
        	printf("CHECKPOINT\n");
           }
	    }
		
}

void checkpoint(lTransacoes *t, tAbela1 *m, lTransacoes *d, tAbela1 *disco){
    int i = 0, z = 0;
    d->nroElem = t->nroElem;
    d->contador = t->contador;
	for(i = 0; i < t->nroElem; i++){//FOR PARA PERCORRER A LISTA
		if(t->tabela[i].inicio == 0){ //SE ALGUM INICIO FOR = 0 (CHECKPOINT) IRÁ INICIAR A TRANSFERÊNCIA DAQUI
		    z = i+1;
		}
	}
	
	for(z; z < t->nroElem; z++){//PASSARÁ TUDO PARA O LOG E DISCO A PARTIR DO ÚLTIMO CHECKPOINT
		d->tabela[z].id = t->tabela[z].id;
		strcpy(d->tabela[z].tabela, t->tabela[z].tabela);
		strcpy(d->tabela[z].bvalor, t->tabela[z].bvalor);
		strcpy(d->tabela[z].valor, t->tabela[z].valor);
		d->tabela[z].inicio = t->tabela[z].inicio;
		d->tabela[z].fim = t->tabela[z].fim;
		        	
	 	if(strcmp(t->tabela[z].tabela, "nome") == 0){
		    strcpy(disco->tabela[t->tabela[z].id-1].nome, t->tabela[z].valor);
		}else if(strcmp(t->tabela[z].tabela, "cpf") == 0){
			strcpy(disco->tabela[t->tabela[z].id-1].cpf, t->tabela[z].valor);
		}else if(strcmp(t->tabela[z].tabela, "churrasco") == 0){
			strcpy(disco->tabela[t->tabela[z].id-1].gasto1, t->tabela[z].valor);
		}else{
		    	if(strcmp(t->tabela[z].tabela, "sushi") == 0){
				strcpy(disco->tabela[t->tabela[z].id-1].gasto2, t->tabela[z].valor);	
					}
				}
		    }
		    
		t->nroElem++;
		
		strcpy(t->tabela[z].valor, "checkpoint");
		t->tabela[z].inicio = 0;
	    strcpy(d->tabela[z].valor, "checkpoint");
		d->tabela[z].inicio = 0;
		
}

void undo(lTransacoes *d, tAbela1 *disco, lTransacoes *t){
	int i;
	d->nroElem = t->nroElem;
	for(i = d->nroElem; i >= 0; i--){
		if(d->tabela[i].fim == 0){
		        	
	 	if(strcmp(d->tabela[i].tabela, "nome") == 0){
		    strcpy(disco->tabela[d->tabela[i].id-1].nome, d->tabela[i].bvalor);
		}else if(strcmp(d->tabela[i].tabela, "cpf") == 0){
			strcpy(disco->tabela[d->tabela[i].id-1].cpf, d->tabela[i].bvalor);
		}else if(strcmp(d->tabela[i].tabela, "churrasco") == 0){
			strcpy(disco->tabela[d->tabela[i].id-1].gasto1, d->tabela[i].bvalor);
		}else{
		    	if(strcmp(d->tabela[i].tabela, "sushi") == 0){
				strcpy(disco->tabela[d->tabela[i].id-1].gasto2, d->tabela[i].bvalor);	
					}
				}
		    }
			
		}
}

void redo(lTransacoes *d, tAbela1 *disco, lTransacoes *t){
	int i = 0, z = 0, f = 0;
    
    d->nroElem = t->nroElem;
    
	for(i; i < MAX; i++){//FOR PARA PERCORRER A LISTA
		if(d->tabela[i].inicio == 0 && strcmp(t->tabela[i].valor, "checkpoint") == 0){ //SE ALGUM INICIO FOR = 0 (CHECKPOINT) IRÁ INICIAR A TRANSFERÊNCIA DAQUI
		    f = i+1;
		}
	}
	
	for(z = f; z < MAX; z++){
		if(d->tabela[z].fim == 1){
		        	
	 	if(strcmp(d->tabela[z].tabela, "nome") == 0){
		    strcpy(disco->tabela[d->tabela[z].id-1].nome, d->tabela[z].valor);
		}else if(strcmp(d->tabela[z].tabela, "cpf") == 0){
			strcpy(disco->tabela[d->tabela[z].id-1].cpf, d->tabela[z].valor);
		}else if(strcmp(d->tabela[z].tabela, "churrasco") == 0){
			strcpy(disco->tabela[d->tabela[z].id-1].gasto1, d->tabela[z].valor);
		}else{
		    	if(strcmp(d->tabela[z].tabela, "sushi") == 0){
				strcpy(disco->tabela[d->tabela[z].id-1].gasto2, d->tabela[z].valor);	
					}
				}
		    }	
	}
    	
}

int main(int argc, char *argv[]) {
	int i, j, z = 1, y;
	setlocale(LC_ALL, "Portuguese");
	
	tAbela1 clientes[MAX];
	inicializar(&clientes);
	tA1 reg;
	
	tAbela1 memoria[MAX];
	inicializar(&memoria);
	
	lTransacoes transacoes[MAXIMO];
	inicializarT(&transacoes);
	transacao registro;
	
	lTransacoes logdisco[MAXIMO];
	inicializarT(&logdisco);

	FILE *fptr;
	
	char escolha;
	//DISCO
	for(i = 0; i < MAX; i++){
		reg.id = i+1;
		strcpy(reg.nome, "João");
		strcpy(reg.cpf,"999.999.999-99");
		strcpy(reg.gasto1, "50.00"); 
		strcpy(reg.gasto2, "50.00"); 
		inserir(&clientes, reg, i);
	}
	
    //MEMORIA
    	for(i = 0; i < MAX; i++){
        memoria->tabela[i].id = clientes->tabela[i].id;
        strcpy(memoria->tabela[i].nome, clientes->tabela[i].nome);
		strcpy(memoria->tabela[i].cpf, clientes->tabela[i].cpf);
		strcpy(memoria->tabela[i].gasto1, clientes->tabela[i].gasto1); 
		strcpy(memoria->tabela[i].gasto2, clientes->tabela[i].gasto2); 
	}
    
	do{
	menu();
	printf("\n\nOpção: ");
    scanf(" %c", &escolha);
	switch(tolower(escolha)){//Caso de escolha do menu
    	case 'a': //Mostrar dados da memória
         	system("cls");
    	    exibirmemoria(&memoria);
    		break;
    	case 'b': //Exibir dados de disco
            system("cls");
        	exibirdisco(&clientes);
    		break;
    	case 'c': //Exibir Log de Disco
    	    system("cls");
            log_disco(&logdisco, &transacoes);
    		break;
    	case 'd': // Transações
            system("cls");
        	inserir_transacao(&transacoes, registro, &memoria, &logdisco, &clientes);
    		break;
    	case 'e'://Checkpoint
    		system("cls");
            checkpoint(&transacoes, &memoria, &logdisco, &clientes);
            printf("\nCHECKPONINT BEM SUCEDIDO\n");
    		break;
    	default:
    		printf("\nOCORRÊNCIA DE FALHA\n");
	}
} while(escolha != 'f');
    
    undo(&logdisco, &clientes, &transacoes);
    redo(&logdisco, &clientes, &transacoes);
    
    fptr = fopen("C:\\disco.txt","w");
    
        for (i=0; i < logdisco->nroElem; i++){
             if(strcmp(logdisco->tabela[i].valor, "checkpoint") == 0){
        	  z = 0;
        	  y = i;
           }
        }
        
        if(z == 0){
            for (i=0; i < y; i++){
            fprintf(fptr,"<T%d, ", logdisco->tabela[i].inicio);
            fprintf(fptr,"%d, ", logdisco->tabela[i].id);
            fprintf(fptr,"%s, ", logdisco->tabela[i].tabela);
            fprintf(fptr,"%s, ", logdisco->tabela[i].bvalor);
            fprintf(fptr,"%s", logdisco->tabela[i].valor);
            fprintf(fptr,">");
            fprintf(fptr,"\n");
		}
        	
        	
		}
		
		for (i = y; i < logdisco->nroElem; i++){
	
        if(logdisco->tabela[i].fim == 1){
		
        fprintf(fptr,"<T%d, ", logdisco->tabela[i].inicio);
        fprintf(fptr,"%d, ", logdisco->tabela[i].id);
        fprintf(fptr,"%s, ", logdisco->tabela[i].tabela);
        fprintf(fptr,"%s, ", logdisco->tabela[i].bvalor);
        fprintf(fptr,"%s", logdisco->tabela[i].valor);
        fprintf(fptr,">");
        fprintf(fptr,"\n");

		}
		      
		if(strcmp(logdisco->tabela[i].valor, "checkpoint") == 0){
        	fprintf(fptr,"CHECKPOINT\n");
           }    
     	}
		
		
		
        /*for (i=0; i < logdisco->nroElem; i++){
	
        if(logdisco->tabela[i].fim == 1){
		
        fprintf(fptr,"<T%d, ", logdisco->tabela[i].inicio);
        fprintf(fptr,"%d, ", logdisco->tabela[i].id);
        fprintf(fptr,"%s, ", logdisco->tabela[i].tabela);
        fprintf(fptr,"%s, ", logdisco->tabela[i].bvalor);
        fprintf(fptr,"%s", logdisco->tabela[i].valor);
        fprintf(fptr,">");
        fprintf(fptr,"\n");

		}
		      
		if(strcmp(logdisco->tabela[i].valor, "checkpoint") == 0){
        	fprintf(fptr,"CHECKPOINT\n");
           }
           
           
           
	}*/
		fprintf(fptr,"\n");
     	fprintf(fptr,"|--------------------------------------------------------------------------|\n");
	    fprintf(fptr,"|TABELA DISCO - CLIENTES                                                   |\n");
	    fprintf(fptr,"|--------------------------------------------------------------------------|\n");
    	fprintf(fptr,"|%-10s %-20s %-18s %-10s %10s  |\n", "ID", "NOME", "CPF", "CHURRASCO", "SUSHI");
     	fprintf(fptr,"|--------------------------------------------------------------------------|\n");
        for (i=0; i < MAX; i++){

        fprintf(fptr,"|%-10d %-20s %-18s %s %15s  |\n", clientes->tabela[i].id, clientes->tabela[i].nome, clientes->tabela[i].cpf, clientes->tabela[i].gasto1, clientes->tabela[i].gasto2);
     	fprintf(fptr,"|--------------------------------------------------------------------------|\n");  

}
    printf("\n");

    fclose(fptr);
	return 0;
}
