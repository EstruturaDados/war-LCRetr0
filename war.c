#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Territorio{
    char nome[30];
    char cor[10];
    int tropa;
};

//cadastre os territorios do jogo
void cadastrarterritorios(struct Territorio *territorio){
int contagem = 0;
int i=0;
    printf("====================================\n");
    printf("Bem vindo ao War!\n");
    printf("Vamos cadastrar os territorios do jogo!\n");
    printf("\n");
    
   
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
}


//ai exibe o mapa
void exibirterritorio(struct Territorio *territorio){

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
    
 }

 //mapa do jogo
 void exibirMapa(struct Territorio *territorio, int *ptr) {
    for (int j = 0; j < 5; j++) {
        printf("Territorio [%d]: %s - Tropas: %d\n", j + 1, territorio[j].nome, ptr[j]);
    }
}

//exibição da mecanica de ataque


 void ataque(struct Territorio *territorio, int *ptr, int atacante, int defensor){
    if(atacante >= 0 && atacante < 5 && defensor >= 0 && defensor < 5){
    if (ptr[atacante] > 1) {
            printf("\n--- INICIANDO BATALHA: %s vs %s ---\n", territorio[atacante].nome, territorio[defensor].nome);
            
            // Rola um dado de 6 lados para cada jogador
            int dadoAtacante = (rand() % 6) + 1;
            int dadoDefensor = (rand() % 6) + 1;

            printf("Dado do Atacante (%s): %d\n", territorio[atacante].nome, dadoAtacante);
            printf("Dado do Defensor (%s): %d\n", territorio[defensor].nome, dadoDefensor);

            // O Atacante precisa tirar maior que o defensor para vencer
            if (dadoAtacante > dadoDefensor) {
                ptr[defensor]--; // Defensor perde 1 tropa
                printf(">>> AVALIACAO: Ataque de Sucesso! %s perdeu 1 tropa. <<<\n", territorio[defensor].nome);
            } else {
                ptr[atacante]--; // Atacante perde 1 tropa (empate ou vitória do defensor)
                printf(">>> AVALIACAO: Ataque FALHOU! %s perdeu 1 tropa. <<<\n", territorio[atacante].nome);
            }
        } else {
            printf("\nAtaque falhou! O territorio atacante nao possui tropas suficientes (precisa de pelo menos 2).\n");
        }
    } else {
        printf("\nAtaque invalido! Verifique os indices dos territorios.\n");
    }
}

 
int main(){
 struct Territorio territorio[5];
    cadastrarterritorios(territorio);
    exibirterritorio(territorio);

    
  printf("====================================\n");
    printf("MAPA ATUAL DO JOGO\n");
 printf("====================================\n");

 int *ptr = (int*)calloc(5, sizeof(int));
 for(int j=0; j<5; j++){
    ptr[j] = territorio[j].tropa;
 }

exibirMapa(territorio, ptr);

int opcaoAtacante, opcaoDefensor;
    int atacante = -1, defensor = -1;

    // --- ESCOLHA DO ATACANTE ---
    printf("\nEscolha o numero do territorio ATACANTE (1 a 5): ");
    scanf(" %d", &opcaoAtacante);

    switch (opcaoAtacante) {
        case 1: atacante = 0; break;
        case 2: atacante = 1; break;
        case 3: atacante = 2; break;
        case 4: atacante = 3; break;
        case 5: atacante = 4; break;
        default:
            printf("Opcao de atacante invalida!\n");
            free(ptr);
            return 0;
    }

    // --- ESCOLHA DO DEFENSOR ---
    printf("Escolha o numero do territorio DEFENSOR (1 a 5): ");
    scanf("%d", &opcaoDefensor);

    switch (opcaoDefensor) {
        case 1: defensor = 0; break;
        case 2: defensor = 1; break;
        case 3: defensor = 2; break;
        case 4: defensor = 3; break;
        case 5: defensor = 4; break;
        default:
            printf("Opcao de defensor invalida!\n");
            free(ptr);
            return 0;
    }

    // Validação para que um territorio não ataque a si mesmo
    if (atacante == defensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
    } else {
        ataque(territorio, ptr, atacante, defensor);
    }


    printf("\nMAPA Atualizado:\n");
    exibirMapa(territorio, ptr);

    free(ptr);
    printf("====================================\n");
    return 0;
}