#include <stdio.h>
#include <string.h>

// Definição da struct Territorio que armazena nome, cor do exército e quantidade de tropas

typedef struct
{
  char nome[30]; // Nome do território
  char cor[15];  // Cor do exército
  int tropas;    // Quantidade de tropas
} Territorio;

int main()
{
  Territorio territorios[5]; // Vetor para armazenar 5 territórios
  int i;

  printf("Cadastro de Territorios para o jogo War\n");
  printf("---------------------------------------\n");
  // Laço para entrada dos dados dos 5 territórios
  for (i = 0; i < 5; i++)
  {
    printf("\nTERRITORIO %d:\n", i + 1);

    // Entrada do nome do território
    printf("Digite o nome do territorio (max 29 caracteres): ");

    // Usando fgets para ler string com espaços e removendo o '\n' final
    fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);

    // Remover o '\n' que fgets captura
    territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

    // Entrada da cor do exército
    printf("Digite a cor do exercito (max 14 caracteres): ");

    fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
    territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

    // Entrada da quantidade de tropas
    printf("Digite a quantidade de tropas: ");

    // Ler número inteiro
    scanf("%d", &territorios[i].tropas);

    // Limpar o buffer do teclado para evitar problemas na próxima leitura de string

    while (getchar() != '\n')
      ;
  }

  // Exibição dos dados cadastrados

  printf("\n\nTerritorios cadastrados:\n");

  printf("------------------------\n");
  for (i = 0; i < 5; i++)
  {
    printf("TERRITORIO %d:\n", i + 1);
    printf(" - Nome: %s\n", territorios[i].nome);
    printf(" - Cor do exercito: %s\n", territorios[i].cor);
    printf(" - Quantidade de tropas: %d\n", territorios[i].tropas);
    printf("------------------------\n");
  }

  return 0;
};
