#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include "menu.h"   //Inclui o Arquivo menu ao programa na main
#include <stdio.h>



struct tPizza{  

    int tamanho;
    int num_sabores;
    int codigo_sabor;
    int borda;
    float valor_total;
    float preco_sabor;
    char nomes_sabores[256];

};
float preco_grande[]={3.80, 3.80, 3.80, 3.80, 3.80, 3.80, 4.90, 4.90, 4.90, 4.90, 4.90, 4.10, 4.10, 4.10, 4.10}; //preços dos pedaços da pizza grande
float preco_gigante[]={4.0, 4.0, 4.0, 4.00, 4.00, 4.00, 5.40, 5.40, 5.40, 5.40, 5.40, 4.3, 4.3, 4.3, 4.30};//preços dos pedaços da pizza Gigante
char *cardapio[]={"Calabresa", "Frango","Quatro queijos","Bacon","Atum","Mussarela",
"Calabresa com cebola","Marguerita","Strogonoff", "Frango com catupiry","Fraldinha na mostarda",
"Chocolate preto","Chocolate branco","Sonho de Valsa", "Morango com chocolate"}; //Sabores das Pizzas com seus devidos códigos para facilitar a escolha do Cliente.
																								

void pizzapronta(struct tPizza* pizza);
void imprimecard(); 
struct tPizza incluir();

int main(void)
{
	setlocale(LC_ALL, "Portuguese");//O Dev C++ não aceita acentos, portanto o biblioteca <locale.h> adiciona-os nas programa.
	int i; //Variavel para rodar o for no case '2'.
	float precototal=0.0;//Estabelecer um valor incial para nao salvar lixo de memória.
	char opcao;//Variavel que lê a opção do "Menu.h" do menu principal no void.
	struct tPizza pedido[10];//Considera o máximo de pedidos como 10 loops e mais uma variavel na Struct

	do
	{
		opcao = menu();
		switch(opcao)
		{
		case '1':
			mostrar_cardapio();//Função colocalizada no "menu.h"
			break;
		case '2':
			for(i=0; i<10; ++i)
			{
				system("cls");//limpa tela
				printf("\n\tVocê já pediu %d pizzas (máx de 10)\n",i);//Lê os pedidos e coloca-os visiveis para os clientes
				pedido[i]=incluir();//Salva todo 'incluir()' em pedido[i] para mostrar depois no final do programa
				if (pedido[i].tamanho == 0)//Encerra o pedido  
					break;
				precototal+=pedido[i].valor_total;
			}
			
				system("cls");//Limpa a tela
				printf("  ______________________________________________________\n");
				printf(" |\t 					\t|\n");
				printf(" |      EXTRATO:                                        |\n");
				printf(" |\t 					\t|\n");
			for(i=0; i<10; ++i)
			{
				if (pedido[i].tamanho==0)//Encerra do pedido
					break;
				
				printf(" | %s				\n", pedido[i].nomes_sabores);//Imprime no extrato os sabores de cada pizza pedida
				printf(" |   R$%3.2f 				     		|\n", pedido[i].valor_total);//Imprime o valor de cada pizza
			}
				printf(" |\t 					\t|\n");
				printf(" |     Preço Total: R$%3.2f				|\n", precototal);//Imprime o valor total das Pizzas
				printf(" |\t 					\t|\n");
				printf(" |______________________________________________________|\n");
				system("pause");
				
			exit(0); //Sai do programa
		case '3':
			instrucoes();//Função colocalizada no "menu.h"
			break;
		case '4':
			creditos();//Função colocalizada no "menu.h"
			break;
		}
	}while(opcao != '0');//Faz o loop até o zero ser digitado, ou quando cai no case 2, faz o pedido e sai do programa.
}



struct tPizza incluir(){//Opção 2 do menu inicial, visto que roda toda vez que i do pedido[i] é chamado pelo for 
    int j=0; 
    char s;
    struct tPizza pizza;
    pizza.valor_total=0;//Limpar o lixo de meméria
    pizza.nomes_sabores[0]='\0'; //Para não imprimir lixo virtual no extrato
	do{
		printf("  ______________________________________________________\n");
		printf(" |  Chegou a hora de fazer o pedido, só responder as    |\n");
		printf(" |             perguntas e Bon Appetit!!                |\n");
		printf(" | Tamanho:                                             |\n");
		printf(" |\t 					\t|\n");
		printf(" | Digite 0 para terminar o pedido                      |\n");
		printf(" | Digite 8 para a Pizza Grande (8 de fatias)           |\n");
		printf(" | Digite 12 para a Pizza Gigante (12 de fatias)        |\n");
		printf(" |______________________________________________________|\n");
		scanf("%d", &pizza.tamanho);
        do { s = getchar(); } while (s!='\n' && s!='\0'); // Limpa o Buffer
	}while(pizza.tamanho!=8&&pizza.tamanho!=12&&pizza.tamanho!=0);
		//Roda até que seja escolhido um valor válido
	
	if (pizza.tamanho==0) //Encerra do Pedido
		return pizza;

	
	switch(pizza.tamanho){
		
		case 8:{//Oito pedaços, Pizza Grande
				do{
					strcat(pizza.nomes_sabores, "Grande: ");//Salva "Grande: " na string nomes_sabores.
					printf("  ______________________________________________________\n");
					printf(" |\t 					\t|\n");
					printf(" |  Quantos sabores?                                    |\n");
					printf(" |  Para só um sabor. Digite 1!                         |\n");
					printf(" |  Para dois sabores. Digite 2!                        |\n");
					printf(" |\t 					\t|\n");
					printf(" |______________________________________________________|\n");
							scanf("%d", &pizza.num_sabores);
					do { s = getchar(); } while (s!='\n' && s!='\0');//Limpa Buffer
				}while(pizza.num_sabores!=1&&pizza.num_sabores!=2);//Lê a quantidade de sabores desejados
					//Roda até que seja escolhido um valor válido
	
		switch(pizza.num_sabores)
			{
			case 1: imprimecard(); //Imprime o cardapio
			 		//pizza Grande com um sabor
					do {
						printf(" |\t 					\t|\n");
						printf(" |  Escolha o sabor pelo Código, Digitando-o!           |\n");
						printf(" |\t 					\t|\n");
						printf(" |______________________________________________________|\n");	
							scanf("%d", &pizza.codigo_sabor);
								do { s = getchar(); } while (s!='\n' && s!='\0');//Limpa Buffer
									
					
					}while(pizza.codigo_sabor < 0 || pizza.codigo_sabor >15);
					//Roda até que seja digitado um codigo valido de Sabor
					
					strcat(pizza.nomes_sabores,cardapio[pizza.codigo_sabor]); //Salva o Nome do sabor em nomes_sabores. 
					pizza.valor_total=preco_grande[pizza.codigo_sabor]*8.0; //Multiplica cada pedaço por cada sabor
		
					pizzapronta(&pizza);
			break;
		
			case 2: 
					//pizza Grande com dois sabores
			        for (j=0; j<2; j++)
		            {
		            	do{
		                imprimecard();
						printf(" |\t 					\t|\n");
						printf(" |  Escolha os sabores pelos Códigos, Digitando-os!     |\n");
						printf(" |\t 					\t|\n");
						printf(" |______________________________________________________|\n");
		                scanf("%d", &pizza.codigo_sabor);
									do { s = getchar(); } while (s!='\n' && s!='\0');//Limpa Buffer
									
						}while(pizza.codigo_sabor < 0 || pizza.codigo_sabor >15);
       					//Roda até que seja digitado um codigo valido de Sabor
  
						if (j!=0)//Le o j para adicionar espaço entre sabores no extrato
							strcat(pizza.nomes_sabores, " e ");//Adiciona virgula entre os sabores
			            	strcat(pizza.nomes_sabores,cardapio[pizza.codigo_sabor]);//Salva os sabores na nomes_sabores

		                pizza.preco_sabor=preco_grande[pizza.codigo_sabor]*4;//Multiplica cada pedaço por cada sabor
		                pizza.valor_total=pizza.valor_total+pizza.preco_sabor;
		
		                printf("\n\n");
					}
					pizzapronta(&pizza);//Imprime a função pizzapronta
					}
			break;

	case 12:{ 
	 		//Doze pedaços, pizza Gigante
			strcat(pizza.nomes_sabores, "Gigante:  ");//Salva "Gigante:" em nomes_sabores
				do{
				
						printf("  ______________________________________________________\n");
						printf(" |\t 					\t|\n");
						printf(" |  Quantos sabores?                                    |\n");
						printf(" |  Para só um sabor. Digite 1!                         |\n");
						printf(" |  Para dois sabores. Digite 2!                        |\n");
						printf(" |  Para três sabores. Digite 3!                        |\n");
						printf(" |\t 					\t|\n");
						printf(" |______________________________________________________|\n");
								scanf("%d", &pizza.num_sabores);
						do { s = getchar(); } while (s!='\n' && s!='\0');//Limpa Buffer
				}while(pizza.num_sabores!=1&&pizza.num_sabores!=2&&pizza.num_sabores!=3);
				//Roda ate que seja escolhido um valor válido

            		if (pizza.num_sabores==1){
	                    //pizza Gigante com um sabor
						do {
						imprimecard();
						printf(" |\t 					\t|\n");
						printf(" |  Escolha o sabor pelo Código, Digitando-o!           |\n");
						printf(" |\t 					\t|\n");
						printf(" |______________________________________________________|\n");	
							scanf("%d", &pizza.codigo_sabor);
								do { s = getchar(); } while (s!='\n' && s!='\0');//Limpa Buffer
							}while(pizza.codigo_sabor < 0 || pizza.codigo_sabor >15);
				        //Roda até que seja escolhido um valor válido
						
						strcat(pizza.nomes_sabores,cardapio[pizza.codigo_sabor]);//Salva o sabor em nomes_sabores
	
			     	    pizza.valor_total=preco_gigante[pizza.codigo_sabor]*12.0;//Multiplica cada pedaço por cada sabor
	
			     	    pizzapronta(&pizza);//Imprime a função pizzapronta
						}

					if(pizza.num_sabores==2){

                    	for (j=0; j<2; j++)
                    	{
                        	do {
								imprimecard();//Imprime o carpadio
								printf(" |\t 					\t|\n");
								printf(" |  Escolha os sabores pelos Códigos, Digitando-os!     |\n");
								printf(" |\t 					\t|\n");
								printf(" |______________________________________________________|\n");	
									scanf("%d", &pizza.codigo_sabor);
								do { s = getchar(); } while (s!='\n' && s!='\0');//Limpa Buffer
							}while(pizza.codigo_sabor < 0 || pizza.codigo_sabor >15);
							//Roda até que seja escolhido um valor válido
	
							if (j!=0)//Le o j para adicionar espaço entre sabores no extrato
								strcat(pizza.nomes_sabores, " e ");//Adiciona virgula entre os sabores
				            	strcat(pizza.nomes_sabores,cardapio[pizza.codigo_sabor]);//Salva os sabores na nomes_sabores
	
			        	    pizza.preco_sabor=preco_gigante[pizza.codigo_sabor]*6;//Multiplica cada pedaço por cada sabor
		        	    	pizza.valor_total=pizza.valor_total+pizza.preco_sabor;

		            		printf("\n\n");
						}
						pizzapronta(&pizza);//Imprime a função pizzapronta
					}
				}

					if(pizza.num_sabores==3){

	                    for (j=0; j<3; j++)
	                    {
	                        do {
								imprimecard();
								printf(" |\t 					\t|\n");
								printf(" |  Escolha os sabores pelos Códigos, Digitando-os!     |\n");
								printf(" |\t 					\t|\n");
								printf(" |______________________________________________________|\n");	
									scanf("%d", &pizza.codigo_sabor);
								do { s = getchar(); } while (s!='\n' && s!='\0');//Limpa Buffer
							}while(pizza.codigo_sabor < 0 || pizza.codigo_sabor >15);
							//Roda até que seja escolhido um valor válido
							
							
							if (j==0||j==1){//Le o j para adicionar espaço entre sabores no extrato
	                        	
				            strcat(pizza.nomes_sabores,cardapio[pizza.codigo_sabor]);//Adiciona os sabores em nomes_sabores
							strcat(pizza.nomes_sabores, ", ");//Adiciona espaço entre os sabores
									}
				            else if(j==2){
							
				            strcat(pizza.nomes_sabores, "e ");//Adiciona espaço entre os sabores
				            strcat(pizza.nomes_sabores,cardapio[pizza.codigo_sabor]);//Salva o sabor desejado em nomes_sabores
						        }
	                        pizza.preco_sabor=preco_gigante[pizza.codigo_sabor]*4;//Multiplica cada pedaço por cada sabor
		        	     	pizza.valor_total=pizza.valor_total+pizza.preco_sabor; //preço total de uma pizza
	
			            	printf("\n\n");
	                    }
						pizzapronta(&pizza);//Imprime a função pizzapronta
				}
			}
		}
	return pizza;
}

void pizzapronta(struct tPizza* pizza){
	    int borda;
		char s;
		do{
			printf("  ______________________________________________________\n");
			printf(" |\t 					\t|\n");
			printf(" |   A sua Pizza é de:                                  |\n");	
			printf(" |   %s \n", pizza->nomes_sabores);	//Aponta para nomes_sabores dentro da pizza
		    printf(" |   O preço da Pizza é de:                             |\n");	
			printf(" |   R$%3.2f                                            |\n", pizza->valor_total);//Aponta valor_total dentro da pizza	
			printf(" |   Deseja adicionar borda recheada?                   |\n");
			printf(" |   Se sim. Digite 1!                                  |\n");
			printf(" |   Se não. Digite 0!                                  |\n");
			printf(" |______________________________________________________|\n\n");
			scanf("%d", &borda);
			do { s = getchar(); } while (s!='\n' && s!='\0');//Limpa Buffer
		}while(borda!=0&&borda!=1);
			//Roda até que seja escolhido um valor válido
			
			if (borda==1&&pizza->tamanho==8)
				{
				strcat(pizza->nomes_sabores, " com borda recheada."); //Salva a borda à nomes_sabores
				pizza->valor_total+=2;//Borda escolhida para pizza Grande
				}
			else if (borda==1&&pizza->tamanho==12){
				
				strcat(pizza->nomes_sabores, " com borda recheada.");//Salva a borda à nomes_sabores
				pizza->valor_total+=3.50;//Borda escolhida para pizza Gigante
		
		}
		}


//Imprime o cardápio dentro do programa nas escolhas de pizzas.
void imprimecard(){
	
		printf("  ______________________________________________________\n");
		printf(" |\t 					\t|\n");
		printf(" |        (%d)%s        |       (%d)%s         |\n", 0,cardapio[0],1, cardapio [1]);
		printf(" |      (%d)%s     |          (%d)%s       |\n",2, cardapio[2],3, cardapio [3]);
		printf(" |           (%d)%s          |       (%d)%s      |\n",4, cardapio[4],5, cardapio [5]);
		printf(" |   (%d)%s  |      (%d)%s      |\n",6, cardapio[6],7, cardapio [7]);
		printf(" |      (%d) %s        |  (%d)%s |\n",8, cardapio[8],9, cardapio [9]);
		printf(" |  (%d)%s |   (%d)%s   |\n",10, cardapio[10],11, cardapio [11]);
		printf(" | (%d)%s       |   (%d)%s    |\n", 12,cardapio[12],13, cardapio [13]);
		printf(" | (%d)%s  |                         |\n", 14,cardapio[14]);
		printf(" |\t 					\t|\n");
	//Ficou fora de tabulação devido as configurações de espaçamento e cada palavra também
		
	
}
