
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 500

typedef struct {
    char nome[100];
    int idade;
    char genero;
    int gestante;
    int lactante;
    int necessidadeEspecial;
    int obeso;
    char senha[10];
    int atendido;
} Paciente;

Paciente urgentes[MAX];
Paciente preferenciais[MAX];
Paciente normais[MAX];

int qtdU = 0, qtdP = 0, qtdN = 0;
int inicioU = 0, inicioP = 0, inicioN = 0;

int contadorU = 1;
int contadorP = 1;
int contadorN = 1;

Paciente atual;
int existeAtendimento = 0;

// Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Leitura de números com validação
int lerInteiro(char mensagem[], int minimo, int maximo) {
    int valor;
    int resultado;

    while (1) {
        printf("%s", mensagem);
        resultado = scanf("%d", &valor);

        if (resultado == 1 && valor >= minimo && valor <= maximo) {
            limparBuffer();
            return valor;
        }

        printf("Entrada invalida! Digite um valor entre %d e %d.\n",
               minimo, maximo);

        limparBuffer();
    }
}

// Leitura de respostas SIM ou NAO
int lerSimNao(char mensagem[]) {
    char resposta;

    while (1) {
        printf("%s (S/N): ", mensagem);
        scanf(" %c", &resposta);
        limparBuffer();

        resposta = toupper((unsigned char)resposta);

        if (resposta == 'S') return 1;
        if (resposta == 'N') return 0;

        printf("Resposta invalida! Digite S ou N.\n");
    }
}

// Classifica o paciente
int classificarPaciente(Paciente p) {

    if (p.idade > 80) {
        return 3; // Urgente
    }

    if (p.gestante || p.lactante ||
        p.necessidadeEspecial || p.obeso) {
        return 2;
    }

    if ((p.genero == 'F' && p.idade >= 60) ||
        (p.genero == 'M' && p.idade >= 65)) {
        return 2;
    }

    return 1; // Normal
}

// Gera senha e adiciona paciente na fila
void gerarSenha(Paciente *p, int categoria) {

    if (categoria == 3) {
        sprintf(p->senha, "U%03d", contadorU++);
        urgentes[qtdU++] = *p;
    }
    else if (categoria == 2) {
        sprintf(p->senha, "P%03d", contadorP++);
        preferenciais[qtdP++] = *p;
    }
    else {
        sprintf(p->senha, "N%03d", contadorN++);
        normais[qtdN++] = *p;
    }
}

// Cadastro de paciente
void cadastrarPaciente() {

    Paciente p;

    if (qtdU - inicioU + qtdP - inicioP +
        qtdN - inicioN >= MAX) {
        printf("\nLimite de pacientes atingido!\n");
        return;
    }

    printf("\n===== CADASTRO DE PACIENTE =====\n");

    printf("Nome: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    if (strlen(p.nome) == 0) {
        printf("Nome invalido!\n");
        return;
    }

    p.idade = lerInteiro("Idade: ", 0, 120);

    do {
        printf("Genero (M/F): ");
        scanf(" %c", &p.genero);
        limparBuffer();

        p.genero = toupper((unsigned char)p.genero);

        if (p.genero != 'M' && p.genero != 'F') {
            printf("Genero invalido!\n");
        }

    } while (p.genero != 'M' && p.genero != 'F');

    p.gestante = 0;

    if (p.genero == 'F') {
        p.gestante = lerSimNao("Esta gestante?");
    }

    p.lactante = lerSimNao("E lactante?");
    p.necessidadeEspecial =
        lerSimNao("Possui necessidade especial?");
    p.obeso = lerSimNao("Possui condicao de obesidade?");

    p.atendido = 0;

    int categoria = classificarPaciente(p);

    gerarSenha(&p, categoria);

    printf("\nPaciente cadastrado com sucesso!\n");
    printf("Nome: %s\n", p.nome);
    printf("Senha: %s\n", p.senha);

    if (categoria == 3)
        printf("Categoria: URGENTE\n");
    else if (categoria == 2)
        printf("Categoria: PREFERENCIAL\n");
    else
        printf("Categoria: NORMAL\n");
}

// Consulta a quantidade de pacientes aguardando
int totalEmEspera() {
    return (qtdU - inicioU) +
           (qtdP - inicioP) +
           (qtdN - inicioN);
}

// Consulta próxima senha
void consultarProxima() {

    printf("\n===== PROXIMA SENHA =====\n");

    if (inicioU < qtdU)
        printf("Proxima senha: %s\n", urgentes[inicioU].senha);

    else if (inicioP < qtdP)
        printf("Proxima senha: %s\n", preferenciais[inicioP].senha);

    else if (inicioN < qtdN)
        printf("Proxima senha: %s\n", normais[inicioN].senha);

    else
        printf("Nao existem pacientes aguardando.\n");
}

// Chama o próximo paciente
void chamarPaciente() {

    if (existeAtendimento) {
        printf("\nFinalize o atendimento atual antes de chamar outro.\n");
        return;
    }

    if (inicioU < qtdU) {
        atual = urgentes[inicioU++];
    }
    else if (inicioP < qtdP) {
        atual = preferenciais[inicioP++];
    }
    else if (inicioN < qtdN) {
        atual = normais[inicioN++];
    }
    else {
        printf("\nNao existem pacientes na fila!\n");
        return;
    }

    existeAtendimento = 1;

    printf("\n===== PACIENTE CHAMADO =====\n");
    printf("Nome: %s\n", atual.nome);
    printf("Senha: %s\n", atual.senha);
}

// Finaliza atendimento
void finalizarAtendimento() {

    if (!existeAtendimento) {
        printf("\nNao existe atendimento em andamento!\n");
        return;
    }

    printf("\nAtendimento da senha %s finalizado!\n",
           atual.senha);

    existeAtendimento = 0;
}

// Mostra o painel de atendimento
void painel() {

    printf("\n========== PAINEL DE ATENDIMENTO ==========\n");

    if (existeAtendimento) {
        printf("SENHA EM ATENDIMENTO: %s\n", atual.senha);
        printf("PACIENTE: %s\n", atual.nome);
    }
    else {
        printf("SENHA EM ATENDIMENTO: Nenhuma\n");
    }

    printf("\n--- PROXIMAS SENHAS ---\n");

    int limite = 5;
    int exibidos = 0;

    for (int i = inicioU; i < qtdU && exibidos < limite; i++) {
        printf("%s - URGENTE\n", urgentes[i].senha);
        exibidos++;
    }

    for (int i = inicioP; i < qtdP && exibidos < limite; i++) {
        printf("%s - PREFERENCIAL\n", preferenciais[i].senha);
        exibidos++;
    }

    for (int i = inicioN; i < qtdN && exibidos < limite; i++) {
        printf("%s - NORMAL\n", normais[i].senha);
        exibidos++;
    }

    if (exibidos == 0)
        printf("Nenhuma senha aguardando.\n");

    printf("\n--- QUANTIDADE EM ESPERA ---\n");
    printf("Urgentes: %d\n", qtdU - inicioU);
    printf("Preferenciais: %d\n", qtdP - inicioP);
    printf("Normais: %d\n", qtdN - inicioN);
    printf("Total: %d\n", totalEmEspera());

    printf("===========================================\n");
}

// Menu principal
void menu() {

    int opcao;

    do {
        printf("\n========== SISTEMA DE CLINICA ==========\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Consultar proxima senha\n");
        printf("3 - Chamar paciente\n");
        printf("4 - Finalizar atendimento\n");
        printf("5 - Exibir painel\n");
        printf("0 - Sair\n");
        printf("========================================\n");

        opcao = lerInteiro("Escolha uma opcao: ", 0, 5);

        switch (opcao) {

            case 1:
                cadastrarPaciente();
                break;

            case 2:
                consultarProxima();
                break;

            case 3:
                chamarPaciente();
                break;

            case 4:
                finalizarAtendimento();
                break;

            case 5:
                painel();
                break;

            case 0:
                printf("\nSistema encerrado!\n");
                break;
        }

    } while (opcao != 0);
}

// Função principal
int main() {

    menu();

    return 0;
}
