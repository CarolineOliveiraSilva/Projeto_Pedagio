Análise de Fluxo Semanal de Pedágio

Este projeto é um programa em C desenvolvido para analisar o fluxo de veículos em um pedágio, chamado "Pedágio Siga Bem", durante um período de uma semana. O sistema permite a inserção de dados de forma manual ou a leitura a partir de um arquivo, processa esses dados para encontrar o dia de maior movimento (pico) e, por fim, gera um relatório no console e o salva em um arquivo de texto.

✨ Funcionalidades
Sistema de Login: Um sistema de autenticação simples para garantir que apenas usuários autorizados acessem os dados.

Múltiplas Formas de Entrada de Dados:

Entrada Manual: O usuário pode inserir o número de carros para cada dia da semana diretamente no console.

Leitura de Arquivo: O programa pode ler os dados de um arquivo pré-existente chamado dados_pedagio.txt.

Processamento de Dados: Calcula automaticamente o dia com o maior fluxo de veículos na semana.

Relatório Visual: Exibe um relatório claro no console, destacando o dia de pico com uma cor diferente para fácil identificação.

Salvar Relatório: Salva o relatório final em um arquivo de texto chamado relatorio_pedagio.txt, incluindo um resumo do dia de maior movimento.

Interface Amigável: Utiliza cores no console (para Windows) para melhorar a experiência do usuário, indicando sucesso e erros.

🛠️ Pré-requisitos
Um compilador C (como GCC, MinGW, ou o compilador do Visual Studio).

Sistema Operacional Windows (devido ao uso das bibliotecas <windows.h> para funções como Sleep e SetConsoleOutputCP).

🚀 Como Compilar e Executar
Salve o código: Salve o código-fonte em um arquivo chamado pedagio.c.

Abra um terminal: Navegue até o diretório onde você salvou o arquivo.

Compile o código: Use o seu compilador C. Com o GCC (MinGW), o comando seria:

Execute o programa:

📋 Como Usar
1. Login
Ao iniciar o programa, você será solicitado a fazer login. As credenciais padrão são:

Usuário: Administrador

Senha: 1234

Você tem um número limitado de tentativas para fazer o login corretamente.

2. Escolha do Método de Entrada
Após o login, o programa oferecerá duas opções para a entrada de dados:

Opção 1: Inserir dados manualmente

O programa solicitará que você digite o número de carros para cada dia da semana, de Segunda-Feira a Domingo.

Opção 2: Ler dados do arquivo

Para usar esta opção, você precisa criar um arquivo chamado dados_pedagio.txt no mesmo diretório do executável.

O arquivo deve conter 7 linhas, cada uma com um número inteiro representando a quantidade de carros do dia correspondente (Segunda a Domingo).

Exemplo de formato para dados_pedagio.txt:

Nota: Se o arquivo dados_pedagio.txt não for encontrado ou estiver formatado incorretamente, o programa solicitará que você insira os dados manualmente.

3. Visualização e Salvamento do Relatório
Após a inserção dos dados, o programa irá:

Exibir o relatório completo no console, com o dia de pico destacado em verde.

Salvar automaticamente este mesmo relatório em um novo arquivo chamado relatorio_pedagio.txt.
