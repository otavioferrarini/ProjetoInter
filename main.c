#include <stdio.h>
#include <string.h>
#define MAX_US 20
#define MAX_DIA 32
#define MAX_MES 13
#define MAX_ESTAB 5

// structs
typedef struct{
    int id;
    char nome[31];
}Usuario;

// funções
void carregarDados(Usuario usuarios[MAX_US], int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]);
void menu();
void inicializacaoCheckIn(int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]);
void cadastroUsuarios(Usuario usuarios[MAX_US], int* accUs);
void listagemUsuarios(Usuario usuarios[MAX_US], int accUs);
void listagemEstabelecimentos();
void cadastroCheckIns(int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]);
void listagemCheckIns(int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB], Usuario usuarios[MAX_US]);
void reportarCaso();
void salvarDados(Usuario usuarios[MAX_US], int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]);

// variáveis globais
int op = 1, accUs = 0, accCh = 0;
Usuario usuarios[MAX_US];
int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB];

int main(){
    carregarDados(usuarios, checkIns);

    do{
        menu();
        printf("\nOpcao desejada: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                cadastroUsuarios(usuarios, &accUs);
                break;
            case 2:
                listagemUsuarios(usuarios, accUs);
                break;
            case 3:
                listagemEstabelecimentos();
                break;
            case 4:
                cadastroCheckIns(checkIns);
                break;
            case 5:
                listagemCheckIns(checkIns, usuarios);
        }

    }while(op);

    salvarDados(usuarios, checkIns);
    return 0;
}

void carregarDados(Usuario usuarios[MAX_US], int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]){
    FILE *arq = fopen("usuarios.txt", "r");
    FILE *arqCh = fopen("checkins.txt", "r");
    
    if(arq == NULL){
        printf("Erro ao abrir os dados de usarios\n");
    } else {
        while(!feof(arq)){
            fscanf(arq, "%d", &usuarios[accUs].id);
            fscanf(arq, "%30[^\n]", usuarios[accUs].nome);
            accUs++;
        }
    }
    if(arqCh == NULL){
        printf("Erro ao abrir os dados de checkins\n");
        inicializacaoCheckIn(checkIns);
    }else{
        int i = 0, j = 0, k = 0, l = 0, x = 0;
        while(!feof(arqCh)){
            fscanf(arqCh, "%d %d %d %d %d", &i, &j, &k, &l, &x);
            checkIns[i][j][k][l] = x;
        }
    }
    
    fclose(arqCh);
    fclose(arq);
}

void menu(){
    printf("\n\t\t PLATAFORMA CORONAVIRUS\n");
    printf("\t 1 - Cadastrar usuario\n");
    printf("\t 2 - Listagem de usuarios\n");
    printf("\t 3 - Listagem de estabelecimento\n");
    printf("\t 4 - CheckIn\n");
    printf("\t 5 - Listagem de check-in\n");
    printf("\t 0 - Fechar programa\n");
}


void inicializacaoCheckIn(int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]){
    for(int i = 0; i < MAX_US; i++){
        for(int j = 0; j < MAX_DIA; j++){
            for(int k = 0; k < MAX_MES; k++){
                for(int l = 0; l < MAX_ESTAB; l++){
                    checkIns[i][j][k][l] = 0;
                }
            }
        }
    }
}


void cadastroUsuarios(Usuario* usuarios, int* accUs){
    char cont;
    do{
        printf("\nNome: ");
        setbuf(stdin, NULL);
        scanf("%30[^\n]", usuarios[*accUs].nome);
        usuarios[*accUs].id = *accUs;
        printf("O id de %s e: %d\n\n", usuarios[*accUs].nome, usuarios[*accUs].id);
        printf("Deseja cadastrar novo usuario? (s/n) ");
        setbuf(stdin, NULL);
        scanf(" %c", &cont);
        (*accUs)++;
    }while(cont == 's' || cont == 'S');
}

void listagemUsuarios(Usuario usuarios[MAX_US], int accUs){
    printf("\nID\tNOME\n");
    for(int i = 0; i < accUs; i++){
        printf("%d\t%s\n", usuarios[i].id, usuarios[i].nome);
    }
}

void listagemEstabelecimentos(){
    printf("\nID\tESTABELECIMENTOS\n");
    printf("1\tPraca\n");
    printf("2\tMercado\n");
    printf("3\tFeira\n");
    printf("4\tEscola\n");
}

void cadastroCheckIns(int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]){
    int estabelecimento, dia, mes, id; 
    char cont;
    do{
        printf("\nID do usuario: ");
        scanf("%d", &id);
        printf("Estabelecimento: (1-Praca 2-Mercado 3-Feira 4-Escola)\n");
        scanf("%d", &estabelecimento);
        printf("Dia: ");
        scanf("%d", &dia);
        printf("Mes: ");
        scanf("%d", &mes);
        checkIns[id][dia][mes][estabelecimento] = 1;
        printf("Deseja cadastrar novo usuario? (s/n) ");
        setbuf(stdin, NULL);
        scanf(" %c", &cont);
    }while(cont == 's' || cont == 'S');
}

void listagemCheckIns(int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB], Usuario usuarios[MAX_US]){
    printf("\nDATA\tNOME\t\t\tEstabelecimento\n");
    for(int i = 0; i < MAX_US; i++){
        for(int j = 0; j < MAX_DIA; j++){
            for(int k = 0; k < MAX_MES; k++){
                for(int l = 0; l < MAX_ESTAB; l++){
                    if(checkIns[i][j][k][l]){
                        printf("%d/%d\t%s\t\t\t%d\n", j, k, usuarios[i].nome, l);
                    }
                }
            }
        }
    }
}

void salvarDados(Usuario usuarios[MAX_US], int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]){
    FILE *arq = fopen("usuarios.txt", "w");
    FILE *arqCh = fopen("checkins.txt", "w");
    
    if(arq == NULL){
        printf("Erro ao salvar o dados de usuarios\n");
    }else{
        for(int i = 0; i < accUs; i++){
            if(i == accUs - 1){
                fprintf(arq, "%d %s", usuarios[i].id, usuarios[i].nome);
            }else{
                fprintf(arq, "%d %s\n", usuarios[i].id, usuarios[i].nome);
            }
        }
    }

    if(arqCh == NULL){
        printf("Erro ao salvar o dados de checkins\n");
    }else{
        for(int i = 0; i < MAX_US; i++){
            for(int j = 0; j < MAX_DIA; j++){
                for(int k = 0; k < MAX_MES; k++){
                    for(int l = 0; l < MAX_ESTAB; l++){
                        if(i == MAX_US -1 && j == MAX_DIA - 1 && k == MAX_MES - 1 && l == MAX_ESTAB - 1){
                            fprintf(arqCh, "%d %d %d %d %d", i, j, k, l, checkIns[i][j][k][l]);
                        }else{
                            fprintf(arqCh, "%d %d %d %d %d\n", i, j, k, l, checkIns[i][j][k][l]);
                        }
                    }
                }
            }
        }
    }

    fclose(arqCh);
    fclose(arq);
}