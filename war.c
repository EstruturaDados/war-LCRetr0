#include <stdio.h>
#include <string.h>


struct Territorio{
    char nome[30];
    char cor[10];
    int tropa;
};

int main(){
int contagem = 0;
int i=0;
    printf("====================================\n");
    printf("Bem vindo ao War!\n");
    printf("Vamos cadastrar os territorios do jogo!\n");
    printf("\n");


    //Criei  a estrutura de territorio para receber os dados
    struct Territorio territorio[5];
   
    while(contagem < 5){
         for(i=0; i<5; i++){
        printf("---Cadastro do Territorio [%d] ---\n", i+1);
        printf("Digite o nome do territorio: ");
        scanf("%s", territorio[contagem].nome);
        printf("Digite a cor do territorio: ");
        scanf("%s", territorio[contagem].cor);
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorio[contagem].tropa);
        contagem++;
          printf("\n");
      }

    }

//A estrutura que criei para devolver os dados 
printf("Territorios criados: \n");
printf("\n");

    for(int y=0; y<5; y++){
        printf("Territorio [%d]: \n", y+1);
        printf("-Nome: %s\n", territorio[y].nome);
        printf("-Cor: %s\n", territorio[y].cor);
        printf("-Quantidade de tropas: %d\n", territorio[y].tropa);
        printf("\n");
    }
    
printf("====================================\n");
return 0;
}