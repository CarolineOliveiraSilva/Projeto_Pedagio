#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
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


void lerDadosManual(dadosDoDia semana[]);
int lerDadosDoArquivo(dadosDoDia semana[]);
resultado processardados(const dadosDoDia semana[]);
void mostrarResultado(const dadosDoDia semana[], resultado resultadoFinal); 
void salvarArquivo(const dadosDoDia semana[], resultado resultadoFinal);


int login(){
    char nomedousuario[20];
    char senhaDigitada[10];
    int tentativas = 0;

    while (tentativas < tentativasdelogin)
    {
        printf("PEDÁGIO SIGA BEM\n");
        printf("Login\n");
        printf("Digite seu nome de usuario: ");
        scanf("%s", nomedousuario);

        printf("\nDigite sua senha: ");
        scanf("%s" , senhaDigitada);

        if(strcmp(nomedousuario, usuario) == 0 && (strcmp(senhaDigitada, senha))== 0){
            printf(verde "Login realizado com sucesso!Acesso liberado\n"reset);
            Sleep(1500);
            return 0;

        }else{
            tentativas ++;
            printf(vermelho"Nome ou senha incorreta\n" reset);

            if(tentativas < tentativasdelogin){
                printf("Você tem mais %d tentativas",tentativasdelogin - tentativas);
            }
        }
     }
     return 1;
    }

void lerDadosManual(dadosDoDia semana[]){
    printf("\nPEDÁGIO SIGA BEM \n");
    printf("FLUXO DE CARROS SEMANAL\n");
    printf("\nDigite a quantidade de carros para cada dia\n");

    for(int i = 0; i < dias; i++){
        printf("%s: ", semana[i].nome);
        scanf("%d", &semana[i].quantidadedeCarros);
    }
}

int lerDadosDoArquivo(dadosDoDia semana[]){
    FILE* arquivo = fopen("dados_pedagio.txt", "r");

    if(arquivo == NULL){
        printf(vermelho "AVISO: Arquivo não encontrado!" reset "\n");
        return 0;
    }

    for(int i = 0; i < dias; i++){
      
        if(fscanf(arquivo, "%d" , &semana[i].quantidadedeCarros) != 1){
            printf(vermelho "Erro! Arquivo não contém dados suficientes." reset "\n");
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

resultado processardados(const dadosDoDia semana[]){
    resultado resultadoFinal;
    resultadoFinal.maiorfluxo = semana[0].quantidadedeCarros;
    resultadoFinal.diaDePico = 0;

    for(int i = 1; i < dias; i++){
        if(semana[i].quantidadedeCarros > resultadoFinal.maiorfluxo){
            resultadoFinal.maiorfluxo = semana[i].quantidadedeCarros;
            resultadoFinal.diaDePico = i;
        }
    }
    return resultadoFinal;
}


void mostrarResultado(const dadosDoDia semana[], resultado resultadoFinal){
    printf("\nRELATÓRIO SEMANAL\n");

   
    for (int i = 0; i < dias; i++){
        if(i == resultadoFinal.diaDePico){
            printf(verde);
            printf("%s: %d carros <---- DIA DE PICO\n", semana[i].nome, semana[i].quantidadedeCarros);
            printf(reset);
        } else {
            printf("%s: %d carros\n", semana[i].nome, semana[i].quantidadedeCarros);
        }
    }
    printf("\nRELATÓRIO FINALIZADO COM SUCESSO!\n");
}

void salvarArquivo(const dadosDoDia semana[], resultado resultadoFinal){
    FILE* arquivo = fopen("relatorio_pedagio.txt", "w");

    if(arquivo == NULL){
        printf(vermelho "\nERRO AO SALVAR ARQUIVO" reset "\n");
        return; 
    }

    fprintf(arquivo, "Relatório de fluxo semanal\n");

    
    for (int i = 0; i < dias; i++){
        fprintf(arquivo, "%s: %d carros", semana[i].nome, semana[i].quantidadedeCarros);
        if(i == resultadoFinal.diaDePico){
            fprintf(arquivo, " <--- DIA DE PICO!");
        }
        
        fprintf(arquivo, "\n");
    }

   
    fprintf(arquivo, "\nRELATÓRIO CONCLUÍDO: O DIA COM MAIS MOVIMENTO FOI %s COM %d CARROS!\n", semana[resultadoFinal.diaDePico].nome, resultadoFinal.maiorfluxo);
    
    
    fclose(arquivo);
    
    printf(verde "\nRELATÓRIO SALVO COM SUCESSO!" reset "\n");
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    SetConsoleOutputCP(65001);

    int opcao;
    dadosDoDia semana[dias];
    
    const char* nomeDosDias[dias] = {"Segunda-Feira","Terça-Feira", "Quarta-Feira", "Quinta-Feira", "Sexta-Feira", "Sábado", "Domingo"};
    
    
    resultado resultadoDaAnalise;

    for (int i = 0; i < dias; i++){
        strcpy(semana[i].nome, nomeDosDias[i]);
        semana[i].quantidadedeCarros = 0;
    }

    if(login() != 0){
        return 1;
    }
    system("cls");

    printf("PEDAGIO SIGA BEM\n");
    printf("\nAnálise semanal de fluxo\n");

    do{

    printf("\n1- Inserir dados\n");
    printf("2- Ler dados do arquivo\n");
    printf("Escolha sua opção: ");
    scanf("%d", &opcao);

    if(opcao != 1 && opcao !=2){
        printf(vermelho "Opção invalida tente novamente\n" reset);
    }

    }while(opcao != 1 && opcao !=2);

    if(opcao == 1){
        lerDadosManual(semana);
    } else if(opcao == 2){
        if(!lerDadosDoArquivo(semana)){
            printf("\nComo a leitura do arquivo falhou, por favor insira os dados manualmente.\n");
            lerDadosManual(semana);
        } else {
            
            printf(verde "Dados lidos do arquivo com sucesso!" reset "\n");
        }
    } else {
        printf(vermelho "Opção inválida!" reset "\n");
        return 1;
    }

    
    resultadoDaAnalise = processardados(semana);
    mostrarResultado(semana, resultadoDaAnalise);
    salvarArquivo(semana, resultadoDaAnalise);

    return 0;
}