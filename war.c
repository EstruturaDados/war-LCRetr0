#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio{
    char nome[30];
    char cor[10];
    int tropa;
};

// declarando as funções aqui pro compilador reconhecer elas depois de serem chamadas
void cadastrarterritorios(struct Territorio *territorio);
void exibirterritorio(struct Territorio *territorio);
void exibirMapa(struct Territorio *territorio, int *ptr);
void atribuirMissao(char *destino, struct Territorio *territorio, int tamanho);
void exibirMissao(char *missao, int jogador);
void mapaatualizado(struct Territorio *territorio, int *ptr);
void escolherjogadores(struct Territorio *territorio, int *ptr, int *atacante, int *defensor);
void ataque(struct Territorio *territorio, int *ptr, int atacante, int defensor);
int verificarMissao(char *missao, struct Territorio *territorio, int tamanho);
void liberarMemoria(int *ptr, char *missao1, char *missao2, char *missao3, char *missao4, char *missao5);
 
int main() {
    int opcaoMenu = 0; 
    int numJogador = 0;

    // Missões disponíveis
    char *missoes[] = {
        "Conquistar 3 territorios da cor azul",
        "Conquistar 3 territorios da cor vermelho",
        "Conquistar 3 territorios da cor verde",
        "Conquistar 3 territorios da cor amarelo",
        "Alcancar 20 tropas no mapa"
    };

    int totalMissoes = 5;

    // Missões dos jogadores
    char *missaoJogador1 = NULL;
    char *missaoJogador2 = NULL;
    char *missaoJogador3 = NULL;
    char *missaoJogador4 = NULL;
    char *missaoJogador5 = NULL;
    // Inicializa os dados aleatórios
    srand(time(NULL));

    struct Territorio territorio[5];
    int atacante = -1, defensor = -1;

    // Cadastra os dados base dos territórios
    cadastrarterritorios(territorio);
    exibirterritorio(territorio);

    int *ptr = (int*)calloc(5, sizeof(int));
    if (ptr == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Alocação dinâmica para as missões dos jogadores
    missaoJogador1 = (char *) malloc(100 * sizeof(char));
    missaoJogador2 = (char *) malloc(100 * sizeof(char));
    missaoJogador3 = (char *) malloc(100 * sizeof(char));
    missaoJogador4 = (char *) malloc(100 * sizeof(char));
    missaoJogador5 = (char *) malloc(100 * sizeof(char));

    if (missaoJogador1 == NULL || missaoJogador2 == NULL || missaoJogador3 == NULL || missaoJogador4 == NULL || missaoJogador5 == NULL) {
        printf("Erro ao alocar memoria para as missoes.\n");
        free(ptr);
        return 1;
    }

    // Sorteio das missões
    atribuirMissao(missaoJogador1, territorio, 5);
    atribuirMissao(missaoJogador2, territorio, 5);
    atribuirMissao(missaoJogador3, territorio, 5);
    atribuirMissao(missaoJogador4, territorio, 5);
    atribuirMissao(missaoJogador5, territorio, 5);
    
    // Exibe as missões sorteadas
    exibirMissao(missaoJogador1, 1);
    exibirMissao(missaoJogador2, 2);
    exibirMissao(missaoJogador3, 3);
    exibirMissao(missaoJogador4, 4);
    exibirMissao(missaoJogador5, 5);

    // Sincroniza o vetor de tropas dinâmico com a struct
    mapaatualizado(territorio, ptr);

    // Laço principal de turnos/batalhas
    do {
        printf("\n====================================\n");
        printf("1. Realizar um Ataque\n");
        printf("2. Ver Mapa Atual\n");
        printf("3. Ver Missões\n");
        printf("0. Sair do Jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoMenu);

        if (opcaoMenu == 1) {
            exibirMapa(territorio, ptr);
            escolherjogadores(territorio, ptr, &atacante, &defensor);

            printf("\nMAPA ATUALIZADO APOS O ATAQUE:\n");
            exibirMapa(territorio, ptr);

            // Checagem de vitória após o ataque
            if (verificarMissao(missaoJogador1, territorio, 5)) {
                printf("\n PARABENS! O Jogador 1 cumpriu sua missao (%s) e VENCEU O JOGO!\n", missaoJogador1);
                break;
            }

            if (verificarMissao(missaoJogador2, territorio, 5)) {
                printf("\n PARABENS! O Jogador 2 cumpriu sua missao (%s) e VENCEU O JOGO!\n", missaoJogador2);
                break;
            }
           
            if (verificarMissao(missaoJogador3, territorio, 5)) {
                printf("\n PARABENS! O Jogador 3 cumpriu sua missao (%s) e VENCEU O JOGO!\n", missaoJogador3);
                break;
            }

            if (verificarMissao(missaoJogador4, territorio, 5)) {
                printf("\n PARABENS! O Jogador 4 cumpriu sua missao (%s) e VENCEU O JOGO!\n", missaoJogador4);
                break;
            }

             if (verificarMissao(missaoJogador5, territorio, 5)) {
                printf("\n PARABENS! O Jogador 5 cumpriu sua missao (%s) e VENCEU O JOGO!\n", missaoJogador5);
                break;
            }

        
        } else if (opcaoMenu == 2) {
            exibirMapa(territorio, ptr);
        } else if (opcaoMenu == 3) {
            printf("\nQual jogador deseja ver a missao? (1 a 5): ");
            scanf("%d", &numJogador);

            if (numJogador == 1) {
                exibirMissao(missaoJogador1, 1);
            } else if (numJogador == 2) {
                exibirMissao(missaoJogador2, 2);
            } else if (numJogador == 3) {
                exibirMissao(missaoJogador3, 3);
            } else if (numJogador == 4) {
                exibirMissao(missaoJogador4, 4);
            } else if (numJogador == 5) {
                exibirMissao(missaoJogador5, 5);
            } else {
                printf("Jogador invalido!\n");
            }
        }
        else if (opcaoMenu != 0) {
            printf("Opcao invalida!\n");
        }

    } while (opcaoMenu != 0);

    printf("\nSaindo do jogo...\n");
    liberarMemoria(ptr, missaoJogador1, missaoJogador2, missaoJogador3, missaoJogador4, missaoJogador5);
    printf("====================================\n");
    return 0;
}




// Funções:

void cadastrarterritorios(struct Territorio *territorio) {
    printf("====================================\n");
    printf("Bem vindo ao War!\n");
    printf("Vamos cadastrar os 5 territorios do jogo!\n\n");
    
    for (int i = 0; i < 5; i++) {
        printf("--- Cadastro do Territorio [%d] ---\n", i + 1);
        printf("Digite o nome do territorio: ");
        scanf("%s", territorio[i].nome);
        printf("Digite a cor do territorio: ");
        scanf("%s", territorio[i].cor);
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorio[i].tropa);
        printf("\n");
    }
}

void exibirterritorio(struct Territorio *territorio) {
    printf("Territorios criados: \n\n");
    for (int y = 0; y < 5; y++) {
        printf("Territorio [%d]: \n", y + 1);
        printf("- Nome: %s\n", territorio[y].nome);
        printf("- Cor: %s\n", territorio[y].cor);
        printf("- Quantidade de tropas: %d\n\n", territorio[y].tropa);
    }
}

void exibirMapa(struct Territorio *territorio, int *ptr) {
    for (int j = 0; j < 5; j++) {
        printf("Territorio [%d]: %s (%s) - Tropas: %d\n", j + 1, territorio[j].nome, territorio[j].cor, ptr[j]);
    }
}
void atribuirMissao(char *destino, struct Territorio *territorio, int tamanho) {
    int tipoMissao = rand() % 2;

    if (tipoMissao == 0) {
        // Sorteia um dos territórios já cadastrados pelo usuário para pegar sua cor
        int indiceSorteado = rand() % tamanho;
        sprintf(destino, "Conquistar 3 territorios da cor %s", territorio[indiceSorteado].cor);
    } else {
        sprintf(destino, "Alcancar 20 tropas no mapa");
    }
}
    
void exibirMissao(char *missao, int jogador) {
    printf("-> Missao do Jogador %d: %s\n", jogador, missao);
}

void escolherjogadores(struct Territorio *territorio, int *ptr, int *atacante, int *defensor) {
    int opcaoAtacante, opcaoDefensor;
    *atacante = -1;
    *defensor = -1;

    printf("\nEscolha o numero do territorio ATACANTE (1 a 5): ");
    scanf("%d", &opcaoAtacante);

    if (opcaoAtacante < 1 || opcaoAtacante > 5) {
        printf("Opcao de atacante invalida!\n");
        return;
    }
    *atacante = opcaoAtacante - 1;

    printf("Escolha o numero do territorio DEFENSOR (1 a 5): ");
    scanf("%d", &opcaoDefensor);

    if (opcaoDefensor < 1 || opcaoDefensor > 5) {
        printf("Opcao de defensor invalida!\n");
        return;
    }
    *defensor = opcaoDefensor - 1;

    if (*atacante == *defensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
        return;
    }

    // Executa a batalha
    ataque(territorio, ptr, *atacante, *defensor);
}

void ataque(struct Territorio *territorio, int *ptr, int atacante, int defensor) {
    if (atacante >= 0 && atacante < 5 && defensor >= 0 && defensor < 5) {
        if (ptr[atacante] > 1) {
            printf("\n--- INICIANDO BATALHA: %s vs %s ---\n", territorio[atacante].nome, territorio[defensor].nome);
            
            int dadoAtacante = (rand() % 6) + 1;
            int dadoDefensor = (rand() % 6) + 1;

            printf("Dado do Atacante (%s): %d\n", territorio[atacante].nome, dadoAtacante);
            printf("Dado do Defensor (%s): %d\n", territorio[defensor].nome, dadoDefensor);

            if (dadoAtacante > dadoDefensor) {
                ptr[defensor]--;
                territorio[defensor].tropa--; // Mantém a struct sincronizada
                printf(">>> AVALIACAO: Ataque BEM-SUCEDIDO! %s perdeu 1 tropa. <<<\n", territorio[defensor].nome);
            } else {
                ptr[atacante]--;
                territorio[atacante].tropa--; // Mantém a struct sincronizada
                printf(">>> AVALIACAO: Ataque FALHOU! %s perdeu 1 tropa. <<<\n", territorio[atacante].nome);
            }
        } else {
            printf("\nAtaque falhou! O territorio atacante nao possui tropas suficientes (precisa de pelo menos 2).\n");
        }
    } else {
        printf("\nAtaque invalido!\n");
    }
}

void mapaatualizado(struct Territorio *territorio, int *ptr) {
    for (int j = 0; j < 5; j++) {
        ptr[j] = territorio[j].tropa;
    }
}

int verificarMissao(char *missao, struct Territorio *territorio, int tamanho) {
    int contadorAzul = 0, contadorVermelho = 0, contadorVerde = 0, contadorAmarelo = 0;
    int totalTropas = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(territorio[i].cor, "azul") == 0) contadorAzul++;
        if (strcmp(territorio[i].cor, "vermelho") == 0) contadorVermelho++;
        if (strcmp(territorio[i].cor, "verde") == 0) contadorVerde++;
        if (strcmp(territorio[i].cor, "amarelo") == 0) contadorAmarelo++;

        totalTropas += territorio[i].tropa;
    }

    if (strcmp(missao, "Conquistar 3 territorios da cor azul") == 0 && contadorAzul >= 3) return 1;
    if (strcmp(missao, "Conquistar 3 territorios da cor vermelho") == 0 && contadorVermelho >= 3) return 1;
    if (strcmp(missao, "Conquistar 3 territorios da cor verde") == 0 && contadorVerde >= 3) return 1;
    if (strcmp(missao, "Conquistar 3 territorios da cor amarelo") == 0 && contadorAmarelo >= 3) return 1;
    if (strcmp(missao, "Alcancar 20 tropas no mapa") == 0 && totalTropas >= 20) return 1;

    return 0;
}

void liberarMemoria(int *ptr, char *missao1, char *missao2, char *missao3, char *missao4, char *missao5) {
    free(ptr);
    free(missao1);
    free(missao2);
    free(missao3);
    free(missao4);
    free(missao5);
}