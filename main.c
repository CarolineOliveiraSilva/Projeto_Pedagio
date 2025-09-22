#include <stdio.h> //Para funções de entrada e saída de dados
#include <stdlib.h> //Fornece funções de utilidade geral, como system("cls") para limpar a tela.
#include <string.h> //manipular strings, usada aqui para strcpy (copiar string) e strcmp (comparar strings)
#include <windows.h> //Específica para o sistema operacional Windows, usada para Sleep (pausar a execução) e SetConsoleOutputCP (ajustar a codificação de caracteres do console)

// Define códigos de escape ANSI para cores no terminal
#define vermelho "\x1b[31m" // Define a cor vermelha para o texto
#define verde "\x1b[32m" // Define a cor verde para o texto
#define reset "\x1b[0m" // Reseta a cor do texto para o padrão
#define dias 7 // Define o número de dias na semana para a análise

// Define as credenciais de login fixas
#define usuario "Administrador"
#define senha "1234"
#define tentativasdelogin 3

// Estrutura para armazenar os dados de um único dia
typedef struct {
    char nome[20];
    int quantidadedeCarros;
} dadosDoDia;

typedef struct {
    int diaDePico;
    int maiorfluxo;
} resultado;

// Declara as funções que serão usadas no programa para que a 'main' possa encontrá-las
void lerDadosManual(dadosDoDia semana[]);
int lerDadosDoArquivo(dadosDoDia semana[]);
resultado processardados(const dadosDoDia semana[]);
void mostrarResultado(const dadosDoDia semana[], resultado resultadoFinal); 
void salvarArquivo(const dadosDoDia semana[], resultado resultadoFinal);

/* Controla o acesso ao sistema, pedindo usuário e senha.
 * @return Retorna 0 em caso de sucesso e 1 em caso de falha após 3 tentativas.
 */
int login(){
    char nomedousuario[20];
    char senhaDigitada[10];
    int tentativas = 0;

    // Loop que continua enquanto o número de tentativas for menor que o máximo permitido

    while (tentativas < tentativasdelogin)
    {
        printf("=====================================================\n");
        printf("\t\tPEDÁGIO SIGA BEM\n");
        printf("=====================================================\n");
        printf("\n\tMenu de Login\n");
        printf("\nDigite seu nome de usuario: ");
        scanf("%s", nomedousuario);

        printf("\nDigite sua senha: ");
        scanf("%s" , senhaDigitada);

        // Compara o usuário e a senha digitados com as constantes definidas.
        // strcmp retorna 0 se as strings forem iguais

        if(strcmp(nomedousuario, usuario) == 0 && (strcmp(senhaDigitada, senha))== 0){
            printf(verde "Login realizado com sucesso!Acesso liberado\n"reset);
            Sleep(1500);
            return 0;

        }else{
            tentativas ++;// Incrementa o contador de tentativas
            printf(vermelho"\nNome ou senha incorreta\n" reset);

            if(tentativas < tentativasdelogin){
                printf("\nVocê tem mais %d tentativas\n",tentativasdelogin - tentativas);
            }
        }
     }
     // Se o loop terminar, significa que as tentativas se esgotaram
     return 1;
    }

    // --- FUNÇÕES DE ENTRADA DE DADOS ---

void lerDadosManual(dadosDoDia semana[]){
    printf("\nPEDÁGIO SIGA BEM \n");
    printf("FLUXO DE CARROS SEMANAL\n");
    printf("\nDigite a quantidade de carros para cada dia\n");

    // Loop que percorre cada dia da semana
    for(int i = 0; i < dias; i++){
        printf("%s: ", semana[i].nome);
        scanf("%d", &semana[i].quantidadedeCarros);
    }
}
    //Lê os dados de fluxo de carros de um arquivo "dados_pedagio.txt
int lerDadosDoArquivo(dadosDoDia semana[]){
    FILE* arquivo = fopen("dados_pedagio.txt", "r");

    // Se o arquivo não puder ser aberto (não existe), 'arquivo' será NULL
    if(arquivo == NULL){ 
        printf(vermelho "AVISO: Arquivo não encontrado!" reset "\n");
        return 0;
    }

    // Loop para ler um número para cada dia da semana
    for(int i = 0; i < dias; i++){
      
        if(fscanf(arquivo, "%d" , &semana[i].quantidadedeCarros) != 1){
            printf(vermelho "Erro! Arquivo não contém dados suficientes." reset "\n");
            fclose(arquivo); // Fecha o arquivo após a leitura bem-sucedida.
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}
    //FUNÇÃO DE PROCESSAMENTO
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
    return resultadoFinal;// Retorna a estrutura com os resultados da análise.
}


void mostrarResultado(const dadosDoDia semana[], resultado resultadoFinal) {
    
    printf("\t\tRELATORIO SEMANAL\n\n");

    int largura_coluna_dois = 30; 

    // Cabeçalho da tabela ajustado
    printf("------------------------------------------------------\n");
    printf("| %-20s | %-*s |\n", "DIA DA SEMANA", largura_coluna_dois, "FLUXO DE VEICULOS");
    printf("------------------------------------------------------\n");

    // Loop para imprimir os dados de cada dia
    for (int i = 0; i < dias; i++) {
        
        char indicador_pico[30] = ""; 

        if (i == resultadoFinal.diaDePico) {
            // Se for o dia de pico
            sprintf(indicador_pico, "carros DIA DE PICO");
            printf(verde); 
        } else {
            sprintf(indicador_pico, "carros");
        }

        char coluna_carros[50];
        sprintf(coluna_carros, "%5d %s", semana[i].quantidadedeCarros, indicador_pico);
        printf("| %-20s | %-*s |\n", semana[i].nome, largura_coluna_dois, coluna_carros);

        if (i == resultadoFinal.diaDePico) {
            printf(reset); // Reseta a cor
        }
    }
    printf("------------------------------------------------------\n");
    printf("\nRELATORIO FINALIZADO COM SUCESSO!\n");
}

void salvarArquivo(const dadosDoDia semana[], resultado resultadoFinal){
    
    // Tenta abrir/criar o arquivo no modo de escrita ("w")

    FILE* arquivo = fopen("relatorio_pedagio.txt", "w");

    // Verifica se houve erro ao abrir o arquivo.
    if(arquivo == NULL){
        printf(vermelho "\nERRO AO SALVAR ARQUIVO" reset "\n");
        return; 
    }
    // Escreve o cabeçalho no arquivo.
    fprintf(arquivo, "Relatório de fluxo semanal\n");

    // Loop para escrever os dados de cada dia no arquivo
    for (int i = 0; i < dias; i++){
        fprintf(arquivo, "%s: %d carros", semana[i].nome, semana[i].quantidadedeCarros);
        if(i == resultadoFinal.diaDePico){
            fprintf(arquivo, " <--- DIA DE PICO!");
        }
        
        fprintf(arquivo, "\n");
    }

   // Escreve um resumo no final do arquivo
    fprintf(arquivo, "\nRELATÓRIO CONCLUÍDO: O DIA COM MAIS MOVIMENTO FOI %s COM %d CARROS!\n", semana[resultadoFinal.diaDePico].nome, resultadoFinal.maiorfluxo);
    
    
    fclose(arquivo);
    
    printf(verde "\nRELATÓRIO SALVO COM SUCESSO!" reset "\n");
}
    //FUNÇÃO PRINCIPAL
int main(){
    
    // Configura o console do Windows para exibir caracteres UTF-8 (acentos, etc.
    SetConsoleOutputCP(65001);

    int opcao;// Variável para a escolha do usuário no menu.
    
    dadosDoDia semana[dias];// Vetor de estruturas para armazenar os dados dos 7 dias
    
    // Vetor de strings com os nomes dos dias da semana para inicialização
    const char* nomeDosDias[dias] = {"Segunda-Feira","Terça-Feira", "Quarta-Feira", "Quinta-Feira", "Sexta-Feira", "Sábado", "Domingo"};
    
    
    resultado resultadoDaAnalise;// Variável para guardar o resultado do processamento.

    char continuar; //Variável para continuar


// Inicializa o vetor 'semana', copiando os nomes dos dias e zerando a contagem de carros
    for (int i = 0; i < dias; i++){
        strcpy(semana[i].nome, nomeDosDias[i]);
        semana[i].quantidadedeCarros = 0;
    }
    // Chama a função de login e, se falhar (retornar 1), encerra o programa.
    if(login() != 0){
        return 1;
    }
     do {
        system("cls"); // Limpa a tela para cada nova análise

        // Inicializa o vetor 'semana' para cada nova análise
        for (int i = 0; i < dias; i++){
            strcpy(semana[i].nome, nomeDosDias[i]);
            semana[i].quantidadedeCarros = 0;
        }
    
    
    printf("PEDAGIO SIGA BEM\n");
    printf("\nAnálise semanal de fluxo\n");
    

    // Loop para garantir que o usuário escolha uma opção válida (1 ou 2).
    do{

    printf("\n1- Inserir dados\n");
    printf("2- Ler dados do arquivo\n");
    printf("Escolha sua opção: ");
    scanf("%d", &opcao);

    if(opcao != 1 && opcao !=2){
        printf(vermelho "Opção invalida tente novamente\n" reset);
    }

    }while(opcao != 1 && opcao !=2);

    // Estrutura de decisão para chamar a função correta com base na escolha do usuário.

    if(opcao == 1){
            lerDadosManual(semana);
        } else if(opcao == 2){
            if(!lerDadosDoArquivo(semana)){
                printf("\nComo a leitura do arquivo falhou, por favor insira os dados manualmente.\n");
                lerDadosManual(semana);
            } else {
                printf(verde "Dados lidos do arquivo com sucesso!" reset "\n");
            }
        }

    // Executa a sequência principal de operações
    resultadoDaAnalise = processardados(semana);// Processa os dados.
    mostrarResultado(semana, resultadoDaAnalise);// Mostra o resultado na tela.
    salvarArquivo(semana, resultadoDaAnalise);// Salva o resultado em um arquivo.

    printf("\n---------------------------------------\n");
        printf("Deseja realizar uma nova análise? (S/N): ");
        
        // Usa " %c" com um espaço antes para consumir o "Enter" da entrada anterior
        scanf(" %c", &continuar); 

    // NOVO: Condição do loop. Ele continua se o usuário digitar 'S' ou 's'.
    } while (continuar == 'S' || continuar == 's');
     
    
    printf("\nPrograma encerrado. Até logo!\n");

    return 0; // Indica que o programa terminou com sucesso.

}
