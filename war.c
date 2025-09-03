#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_NOME 30
#define TAMANHO_COR 10

// Definição da struct Territorio
typedef struct
{
  char nome[TAMANHO_NOME]; // Nome do território
  char cor[TAMANHO_COR];   // Cor do exército
  int tropas;              // Quantidade de tropas
} Territorio;

// Função para cadastrar os territórios dinamicamente
Territorio *cadastrarTerritorios(int n)
{
  Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
  if (mapa == NULL)
  {
    printf("Erro na alocacao de memoria.\n");
    exit(1);
  }

  printf("Cadastro de %d territorios para o jogo War\n", n);
  printf("--------------------------------------------\n");

  for (int i = 0; i < n; i++)
  {
    printf("\nTERRITORIO %d:\n", i + 1);

    printf("Digite o nome do territorio (max 29 caracteres): ");
    fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
    mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove '\n'

    printf("Digite a cor do exercito (max 9 caracteres): ");
    fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
    mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

    printf("Digite a quantidade de tropas: ");
    while (scanf("%d", &mapa[i].tropas) != 1 || mapa[i].tropas < 1)
    {
      printf("Entrada invalida. Digite um numero inteiro positivo para tropas: ");
      while (getchar() != '\n')
        ; // limpar buffer
    }
    while (getchar() != '\n')
      ; // limpar buffer após scanf
  }

  return mapa;
}

// Função para exibir os territórios
void exibirTerritorios(Territorio *mapa, int n)
{
  printf("\nTerritorios cadastrados:\n");
  printf("------------------------\n");
  for (int i = 0; i < n; i++)
  {
    printf("TERRITORIO %d:\n", i + 1);
    printf(" - Nome: %s\n", mapa[i].nome);
    printf(" - Cor do exercito: %s\n", mapa[i].cor);
    printf(" - Quantidade de tropas: %d\n", mapa[i].tropas);
    printf("------------------------\n");
  }
}

// Função que simula o ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor)
{
  printf("\nAtaque de %s (%s) com %d tropas contra %s (%s) com %d tropas\n",
         atacante->nome, atacante->cor, atacante->tropas,
         defensor->nome, defensor->cor, defensor->tropas);

  // Simular dados de 1 a 6 para atacante e defensor
  int dadoAtacante = rand() % 6 + 1;
  int dadoDefensor = rand() % 6 + 1;

  printf("Dado do atacante: %d\n", dadoAtacante);
  printf("Dado do defensor: %d\n", dadoDefensor);

  if (dadoAtacante > dadoDefensor)
  {
    printf("Atacante venceu a batalha!\n");

    // Atualizar defensor: muda de dono e recebe metade das tropas do atacante
    strcpy(defensor->cor, atacante->cor);

    int tropasTransferidas = atacante->tropas / 2;
    if (tropasTransferidas < 1)
      tropasTransferidas = 1; // garantir pelo menos 1 tropa transferida

    defensor->tropas = tropasTransferidas;

    // Atacante perde as tropas transferidas
    atacante->tropas -= tropasTransferidas;
    if (atacante->tropas < 1)
      atacante->tropas = 1; // manter pelo menos 1 tropa no atacante

    printf("%d tropas transferidas para o defensor.\n", tropasTransferidas);
  }
  else
  {
    printf("Defensor venceu a batalha!\n");

    // Atacante perde uma tropa
    atacante->tropas -= 1;
    if (atacante->tropas < 1)
      atacante->tropas = 1; // manter pelo menos 1 tropa

    printf("Atacante perdeu 1 tropa.\n");
  }
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio *mapa)
{
  free(mapa);
}

// Função para escolher um território pelo índice, com validação
int escolherTerritorio(Territorio *mapa, int n, const char *prompt)
{
  (void)mapa; // evitar warning de variável não usada
  int escolha;
  while (1)
  {
    printf("%s (1 a %d): ", prompt, n);
    if (scanf("%d", &escolha) != 1)
    {
      printf("Entrada invalida. Digite um numero inteiro.\n");
      while (getchar() != '\n')
        ; // limpar buffer
      continue;
    }
    if (escolha < 1 || escolha > n)
    {
      printf("Numero fora do intervalo. Tente novamente.\n");
      continue;
    }
    while (getchar() != '\n')
      ; // limpar buffer
    break;
  }
  return escolha - 1; // ajustar para índice 0-based
}

int main()
{
  srand(time(NULL)); // Inicializa gerador de números aleatórios

  int nTerritorios;

  printf("Digite o numero total de territorios: ");
  while (scanf("%d", &nTerritorios) != 1 || nTerritorios < 2)
  {
    printf("Entrada invalida. Digite um numero inteiro maior ou igual a 2: ");
    while (getchar() != '\n')
      ; // limpar buffer
  }
  while (getchar() != '\n')
    ; // limpar buffer

  // Cadastro dos territórios
  Territorio *mapa = cadastrarTerritorios(nTerritorios);

  int continuar = 1;
  while (continuar)
  {
    exibirTerritorios(mapa, nTerritorios);

    printf("\nEscolha o territorio atacante:\n");
    int idxAtacante = escolherTerritorio(mapa, nTerritorios, "Numero do territorio atacante");

    printf("Escolha o territorio defensor:\n");
    int idxDefensor = escolherTerritorio(mapa, nTerritorios, "Numero do territorio defensor");

    // Validar que atacante e defensor são diferentes
    if (idxAtacante == idxDefensor)
    {
      printf("Atacante e defensor nao podem ser o mesmo territorio. Tente novamente.\n");
      continue;
    }

    // Validar que não atacará território da mesma cor
    if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0)
    {
      printf("Nao e permitido atacar um territorio da mesma cor. Tente novamente.\n");
      continue;
    }

    // Validar que atacante tem tropas suficientes para atacar (pelo menos 2)
    if (mapa[idxAtacante].tropas < 2)
    {
      printf("Territorio atacante deve ter pelo menos 2 tropas para atacar. Escolha outro territorio.\n");
      continue;
    }

    // Realizar o ataque
    atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

    // Exibir territórios atualizados
    exibirTerritorios(mapa, nTerritorios);

    // Perguntar se deseja continuar atacando
    char resposta;
    printf("Deseja realizar outro ataque? (s/n): ");
    resposta = getchar();
    while (getchar() != '\n')
      ; // limpar buffer

    if (resposta != 's' && resposta != 'S')
      continuar = 0;
  }

  liberarMemoria(mapa);

  printf("Jogo encerrado. Memoria liberada.\n");

  return 0;
}
