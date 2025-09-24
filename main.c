#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define vermelho "\x1b[31m"
#define verde "\x1b[32m"
#define reset "\x1b[0m"
#define dias 7

#define usuario "Administrador"
#define senha "1234"
#define tentativasdelogin 3

typedef struct {
    char nome[20];
    int quantidadedeCarros;
} dadosDoDia;

typedef struct {
    int diaDePico;
    int maiorfluxo;
} resultado;

// Declaração das funções
void lerDadosManual(dadosDoDia semana[]);
int lerDadosDoArquivo(dadosDoDia semana[]);
resultado processardados(const dadosDoDia semana[]);
void mostrarResultado(const dadosDoDia semana[], resultado resultadoFinal);
void salvarRelatorio(const dadosDoDia semana[], resultado resultadoFinal);
void salvarDadosParaArquivo(const dadosDoDia semana[]); // NOVO: Função para salvar apenas os dados numéricos

int login() {
    char nomedousuario[20];
    char senhaDigitada[10];
    int tentativas = 0;

    while (tentativas < tentativasdelogin) {
        printf("=====================================================\n");
        printf("\t\tPEDÁGIO SIGA BEM\n");
        printf("=====================================================\n");
        printf("\n\tMenu de Login\n");
        printf("\nDigite seu nome de usuario (Administrador): ");
        scanf("%s", nomedousuario);

        printf("\nDigite sua senha (1234): ");
        scanf("%s", senhaDigitada);

        if (strcmp(nomedousuario, usuario) == 0 && (strcmp(senhaDigitada, senha)) == 0) {
            printf(verde "Login realizado com sucesso! Acesso liberado\n" reset);
            Sleep(1500);
            return 0;
        } else {
            tentativas++;
            printf(vermelho "\nNome ou senha incorreta\n" reset);
            if (tentativas < tentativasdelogin) {
                printf("\nVocê tem mais %d tentativas\n", tentativasdelogin - tentativas);
            }
        }
    }
    return 1;
}

void lerDadosManual(dadosDoDia semana[]) {
    printf("\nPEDÁGIO SIGA BEM \n");
    printf("FLUXO DE CARROS SEMANAL\n");
    printf("\nDigite a quantidade de carros para cada dia\n");

    for (int i = 0; i < dias; i++) {
        printf("%s: ", semana[i].nome);
        // Loop para garantir que a entrada seja um número válido
        while (scanf("%d", &semana[i].quantidadedeCarros) != 1) {
            printf(vermelho "Entrada invalida. Digite um numero: " reset);
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
    }
}

// ALTERADO: Agora lê de "dados_pedagio.txt" que contém apenas números
int lerDadosDoArquivo(dadosDoDia semana[]) {
    FILE* arquivo = fopen("dados_pedagio.txt", "r"); // Abre o arquivo de DADOS

    if (arquivo == NULL) {
        printf(vermelho "AVISO: Arquivo de dados 'dados_pedagio.txt' não encontrado!" reset "\n");
        return 0;
    }

    for (int i = 0; i < dias; i++) {
        if (fscanf(arquivo, "%d", &semana[i].quantidadedeCarros) != 1) {
            printf(vermelho "Erro! Arquivo de dados corrompido ou incompleto." reset "\n");
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

resultado processardados(const dadosDoDia semana[]) {
    resultado resultadoFinal;
    resultadoFinal.maiorfluxo = semana[0].quantidadedeCarros;
    resultadoFinal.diaDePico = 0;

    for (int i = 1; i < dias; i++) {
        if (semana[i].quantidadedeCarros > resultadoFinal.maiorfluxo) {
            resultadoFinal.maiorfluxo = semana[i].quantidadedeCarros;
            resultadoFinal.diaDePico = i;
        }
    }
    return resultadoFinal;
}

void mostrarResultado(const dadosDoDia semana[], resultado resultadoFinal) {
    printf("\n\n\t\tRELATORIO SEMANAL\n\n");

    int largura_coluna_dois = 30;

    printf("------------------------------------------------------\n");
    printf("| %-20s | %-*s |\n", "DIA DA SEMANA", largura_coluna_dois, "FLUXO DE VEICULOS");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < dias; i++) {
        char indicador_pico[30] = "";

        if (i == resultadoFinal.diaDePico) {
            sprintf(indicador_pico, "carros <--- DIA DE PICO");
            printf(verde);
        } else {
            sprintf(indicador_pico, "carros");
        }

        char coluna_carros[50];
        sprintf(coluna_carros, "%5d %s", semana[i].quantidadedeCarros, indicador_pico);
        printf("| %-20s | %-*s |\n", semana[i].nome, largura_coluna_dois, coluna_carros);

        if (i == resultadoFinal.diaDePico) {
            printf(reset);
        }
    }
    printf("------------------------------------------------------\n");
    printf("\nRELATORIO FINALIZADO COM SUCESSO!\n");
}

// ALTERADO: Renomeada para salvarRelatorio, salva o arquivo para humanos lerem.
void salvarRelatorio(const dadosDoDia semana[], resultado resultadoFinal) {
    FILE* arquivo = fopen("relatorio_pedagio.txt", "w");

    if (arquivo == NULL) {
        printf(vermelho "\nERRO AO SALVAR RELATORIO" reset "\n");
        return;
    }
    fprintf(arquivo, "Relatório de fluxo semanal\n");
    fprintf(arquivo, "-----------------------------------\n");
    for (int i = 0; i < dias; i++) {
        fprintf(arquivo, "%s: %d carros", semana[i].nome, semana[i].quantidadedeCarros);
        if (i == resultadoFinal.diaDePico) {
            fprintf(arquivo, " <--- DIA DE PICO!");
        }
        fprintf(arquivo, "\n");
    }
    fprintf(arquivo, "-----------------------------------\n");
    fprintf(arquivo, "\nRELATÓRIO CONCLUÍDO: O DIA COM MAIS MOVIMENTO FOI %s COM %d CARROS!\n", semana[resultadoFinal.diaDePico].nome, resultadoFinal.maiorfluxo);
    fclose(arquivo);
    printf(verde "\nRELATORIO SALVO COM SUCESSO EM 'relatorio_pedagio.txt'!" reset "\n");
}

// NOVO: Função que salva apenas os números em um arquivo de dados.
void salvarDadosParaArquivo(const dadosDoDia semana[]) {
    FILE* arquivo = fopen("dados_pedagio.txt", "w");
    if (arquivo == NULL) {
        printf(vermelho "\nERRO AO SALVAR ARQUIVO DE DADOS" reset "\n");
        return;
    }
    // Escreve apenas a quantidade de carros, um por linha.
    for (int i = 0; i < dias; i++) {
        fprintf(arquivo, "%d\n", semana[i].quantidadedeCarros);
    }
    fclose(arquivo);
    printf(verde "\nDados salvos com sucesso em 'dados_pedagio.txt'!" reset "\n");
}


int main() {
    // Configura o console do Windows para exibir caracteres UTF-8
    SetConsoleOutputCP(65001);

    int opcao;
    dadosDoDia semana[dias];
    const char* nomeDosDias[dias] = {"Segunda-Feira", "Terca-Feira", "Quarta-Feira", "Quinta-Feira", "Sexta-Feira", "Sabado", "Domingo"};
    resultado resultadoDaAnalise;
    char continuar, carregar_ultimos_dados;

    // Chama a função de login
    if (login() != 0) {
        return 1;
    }

    // Loop principal para permitir múltiplas análises
    do {
        system("cls"); // Limpa a tela para a nova análise

        // Inicializa a estrutura 'semana' com nomes e zera os carros
        for (int i = 0; i < dias; i++) {
            strcpy(semana[i].nome, nomeDosDias[i]);
            semana[i].quantidadedeCarros = 0;
        }

        printf("PEDAGIO SIGA BEM\n");
        printf("\nAnálise semanal de fluxo\n");

        int dados_carregados = 0; // Flag para controlar se os dados já foram inseridos

        // ---- NOVA LÓGICA ----
        // 1. Verifica se o arquivo de dados da última análise existe.
        FILE* arquivo_teste = fopen("dados_pedagio.txt", "r");
        if (arquivo_teste != NULL) {
            fclose(arquivo_teste); // Fecha o arquivo, só queríamos saber se ele existe.

            // 2. Pergunta ao usuário se ele quer carregar os dados existentes.
            printf("\nQuer ler os dados da ultima semana? (S/N): ");
            scanf(" %c", &carregar_ultimos_dados);

            if (carregar_ultimos_dados == 'S' || carregar_ultimos_dados == 's') {
                if (lerDadosDoArquivo(semana)) { // Tenta ler o arquivo
                    printf(verde "Dados da ultima semana carregados com sucesso!\n" reset);
                    dados_carregados = 1; // Marca que os dados foram carregados com sucesso
                } else {
                    printf(vermelho "Falha ao carregar os dados. Por favor, insira manualmente.\n" reset);
                }
            }
        }
        // ---- FIM DA NOVA LÓGICA ----


        // Se os dados NÃO foram carregados na etapa anterior, mostra o menu padrão.
        if (!dados_carregados) {
            do {
                printf("\n1- Inserir dados manualmente\n");
                printf("2- Tentar ler do arquivo novamente\n");
                printf("Escolha sua opcao: ");
                scanf("%d", &opcao);
                if (opcao != 1 && opcao != 2) {
                    printf(vermelho "Opcao invalida, tente novamente\n" reset);
                }
            } while (opcao != 1 && opcao != 2);

            if (opcao == 1) {
                lerDadosManual(semana);
                // Pergunta se o usuário quer salvar os novos dados digitados.
                char salvar_dados;
                printf("\nDeseja salvar estes dados para uso futuro? (S/N): ");
                scanf(" %c", &salvar_dados);
                if (salvar_dados == 'S' || salvar_dados == 's') {
                    salvarDadosParaArquivo(semana);
                }
            } else if (opcao == 2) {
                if (!lerDadosDoArquivo(semana)) {
                    printf("\nLeitura do arquivo falhou. Por favor, insira os dados manualmente.\n");
                    lerDadosManual(semana);
                } else {
                    printf(verde "Dados lidos do arquivo com sucesso!\n" reset);
                }
            }
        }

        // Executa a sequência principal de operações
        resultadoDaAnalise = processardados(semana);   // Processa os dados.
        mostrarResultado(semana, resultadoDaAnalise); // Mostra o resultado na tela.
        salvarRelatorio(semana, resultadoDaAnalise);  // Salva o relatório formatado.

        printf("\n---------------------------------------\n");
        printf("Deseja realizar uma nova analise? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's');

    printf("\nPrograma encerrado. Ate logo!\n");
    return 0;
}
