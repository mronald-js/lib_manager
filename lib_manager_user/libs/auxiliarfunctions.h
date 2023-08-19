#ifndef AUXILIAR_FUNC_H
#define AUXILIAR_FUNC_H

#include <stdio.h>
#include <stdlib.h>

void substitui(char *vetor){
    vetor[strcspn(vetor, "\n")] = '\0'; //troca o último \n por um caracter nulo, dessa forma evitando que o \n fique no buffer
}

int getTarefa() {
    int tarefa;
    do {
        scanf("%d", &tarefa);
    } while (tarefa < 0 || tarefa > 3);
    return tarefa;
}

void menuPrincipal() {
    printf("\nMenu Principal:\n");
    printf("1 - Registrar (Plano A - ASSOCIADO)\n");
    printf("2 - Registrar (Plano B - MEMBRO BASICO)\n");
    printf("3 - Login\n");
    printf("0 - Sair\n");
}


void menuLogado(char *nome, char plano) {
    printf("\nAtualmente logado como \033[32m%s\033[0m | PLANO \033[31m%c\033[0m\n", nome, plano);
    printf("\nOpcoes:\n");
    printf("1 - Buscar livro\n");
    printf("2 - Solicitar Emprestimo\n");
    printf("3 - Limpar terminal\n");
    printf("0 - Logout\n");
}

void salvarDados() {
    FILE *fp;
    fp = fopen("users/dados.txt", "w");
    for(int i = 0; i < numAssociados; i++) {
        fprintf(fp, "%s,%s,%c\n", associados[i].nome, associados[i].senha, associados[i].plano);
    }
    fclose(fp);
}

void limparbuffer(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int getOpcao() {
    int opcao;
    do {
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparbuffer();
    } while (opcao < 0 || opcao > 3);
    return opcao;
}

void registrarUsuario(int opcao) {

    char nome[100], senha[20];
    int usuarioJaExistente, counter = 0;
    
    do {
        usuarioJaExistente = 0;
        printf("Digite seu nome de usuario: ");
        fgets(nome, 100, stdin);
        substitui(nome);
        
        do {
            if(counter > 0)
                printf("Senha invalida!\nDigite novamente!\n");
            else
                printf("\nDigite sua senha (6-20 caracteres): ");
            fgets(senha, 20, stdin);
            substitui(senha);
            counter++;
        } while(strlen(senha) < 6 || strlen(senha) > 20);
        counter = 0;

        autenticarAssociado(nome, senha, 0);

    } while(usuarioJaExistente);

    char plano = opcao == 1 ? 'A' : 'B';
    addAssociado(nome, senha, plano);
    salvarDados();
    printf("\nUsuario \033[032m%s\033[0m registrado com sucesso!\n", nome);
}

void carregarDados() {
    FILE *fp;
    fp = fopen("users/dados.txt", "r");
    if (fp == NULL) {
        return;
    }
    while(!feof(fp)) {
        Associado novoAssociado;
        fscanf(fp, "%[^,],%[^,],%c\n", novoAssociado.nome, novoAssociado.senha, &novoAssociado.plano);
        associados[numAssociados++] = novoAssociado;
    }
    fclose(fp);
}

//mensagem de boas vindas

void bemVindo(){
    printf("\n\nSeja Bem Vindo a [NOME DA BIBLIOTECA]!\n\n");
}


// Interface de usuário
void exibirMenu() {
    printf("Por Gentileza Cadastra-se No Sistema\n");
    printf("(Cadastrar como associado - assinatura mensal) Digite 1\n(Cadastrar conta basica - gratuito) Digite 2   \n");
    printf("\nDigite 3 se ja tiver cadastro; Digite 0 para sair\n");
}

//Apenas uma arte para exibir o nome do programa (pode ignorar essa função);
void libManager() {
    printf("\033[31m*\033[0m    ,--, \n");
    printf("\033[32m*\033[0m ,---.'|\033[33m                                   ____ \033[0m\n");
    printf("\033[34m*\033[0m |   | :\033[35m                                 ,'  , `. \033[0m\n");
    printf("\033[36m*\033[0m :   : |\033[37m      ,--,\033[31m      ,---,\033[32m         ,-+-,.' _ | \033[0m\n");
    printf("\033[33m*\033[0m |   ' :\033[34m    ,--.'|\033[35m    ,---.'|\033[36m      ,-+-. ;   , ||\033[0m\033[37m                     ,---,\033[31m                                         __  ,-. \033[0m\n");
    printf("\033[32m*\033[0m ;   ; '\033[33m    |  |,\033[34m     |   | :\033[35m     ,--.'|'   |  ;|\033[0m\033[36m                 ,-+-. /  |\033[37m                 ,----._,\033[31m.\033[32m            ,' ,'/ /|\033[0m\n");
    printf("\033[33m*\033[0m '   | |\033[31m__\033[32m  `--'_\033[0m\033[33m     :   : :\033[34m    |   |  ,', |  ':\033[35m    ,--.--.\033[0m\033[36m     ,--.'|'   |\033[37m    ,--.--.\033[31m     /   /  ' /\033[32m    ,---.\033[33m   '  | |' |\033[0m\n");
    printf("\033[34m*\033[0m |   | :\033[31m.'|\033[32m ,' ,'|\033[0m\033[33m    :     |,-. |   | /  | |  ||\033[34m   /       \\   \033[0m\033[35m  |   |  ,\"' |\033[36m   /       \\   \033[37m  |   :\033[31m     |\033[32m   /     \\\033[33m  |  |   \033[0m\n");
    printf("\033[35m*\033[0m '   :\033[31m    ;\033[32m '  | |\033[0m\033[33m    |   : '  |\033[34m '   | :  | :  |,\033[35m  .--.  .-. |\033[0m\033[36m  |   | /  | |\033[37m  .--.  .-. |\033[31m  |   | .\\  .\033[32m  /    /  |\033[33m '  :  /\033[0m \n");
    printf("\033[36m*\033[0m |   |\033[31m  ./\033[32m  |  | :\033[0m\033[33m    |   |  / : |   : |  ; |--'\033[34m    \\__\\/:\033[0m\033[35m . .\033[0m\033[36m  |   | |  | |\033[37m   \\__\\/:\033[31m . .\033[32m  .   ; ';  |\033[33m .    ' / |\033[0m\033[34m |  | \033[0m\n");
    printf("\033[37m*\033[0m ;   :\033[31m ;\033[32m    '  : |\033[33m__\033[34m  '   : |: | ;   . |  ; |--'\033[35m       ,\" .--.; |\033[0m\033[36m  |   | |  |/    ,\" .--.; |\033[37m  '   .\033[31m   . |\033[32m '   ;   /|\033[33m ;  : \033[0m\n");
    printf("\033[31m*\033[0m |   ,/\033[32m     |  | '.'| |   | '/ : |   : '  |/\033[33m       /  /  ,.  |\033[0m\033[34m  |   | |--'    /  /  ,.  |\033[35m   `---`-'|\033[0m\033[36m | '   |  / |\033[37m |  , ;\033[0m\n");
    printf("\033[32m*\033[0m '---'\033[33m      ;  :    ; |   :    |\033[34m ;   | |`-'       ;  :   .'   \\|   |/       ;  :   .'   \\\033[35m  .'__/\\_: |\033[36m |   :    |\033[0m\033[37m  ---'\033[0m\n");
    printf("\033[34m*\033[0m            |  ,   /  /\033[35m    \\  /\033[35m  |   ;/           |  ,     .-./ '---'        |  ,     .-./  |\033[0m   :    :  \\   \\  /\n");
    printf("\033[32m*\033[0m             ---`-'\033[32m   `-'----'   '---'\033[0m             `--`---'                   `--`---'       \\   \\  /    `----'\n");
    printf("_._._._._._._._._._._._._._._._._._._._._._._._._.._._._._._._._._._._._._._._._._._._._._._._._._._._._.._._._._._._._._.\n");
}

// limpa terminal
void limparTela() {
    system("cls"); // para Windows
    system("clear"); // para Linux ou macOS
    libManager();
}
#endif // ASSOCIADO_H