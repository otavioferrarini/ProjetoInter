#include <stdio.h>
#include <string.h>
#define MAX_US 101
#define MAX_DIA 32
#define MAX_MES 13
#define MAX_ESTAB 4

// structs
typedef struct{
    int id;
    char nome[31];
}Usuario;

// funções
void carregarDados(Usuario usuarios[MAX_US]);
void menu();
void inicializacaoCheckIn(int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB]);
void cadastroUsuarios(Usuario usuarios[MAX_US], int* accUs);
void listagemUsuarios(Usuario usuarios[MAX_US], int accUs);
void listagemEstabelecimentos();
void cadastroCheckIn();
void reportarCaso();
void salvarDados(Usuario usuarios[MAX_US]);

// variáveis globais
int op = 1, accUs = 0, accCh = 0;
Usuario usuarios[MAX_US];
int checkIns[MAX_US][MAX_DIA][MAX_MES][MAX_ESTAB];

int main(){

    carregarDados(usuarios);

    // inicializacaoCheckIn(checkIns);

    do{
        menu();
        printf("Opcao desejada: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                cadastroUsuarios(usuarios, &accUs);
                break;
            case 2:
                listagemUsuarios(usuarios, accUs);
                break;
        }

    }while(op);

    salvarDados(usuarios);

    return 0;
}

void carregarDados(Usuario usuarios[MAX_US]){
    FILE *arq = fopen("usuarios.txt", "r");
    
    if(arq == NULL){
        printf("Erro ao abrir os dados de usarios\n");
        return;
    }

    while(!feof(arq)){
        fscanf(arq, "%d", &usuarios[accUs].id);
        fscanf(arq, "%30[^\n]", usuarios[accUs].nome);
        accUs++;
    }

    fclose(arq);
}

void menu(){
    printf("\n\t\t PLATAFORMA CORONAVIRUS\n");
    printf("\t 1 - Cadastrar usuario\n");
    printf("\t 2 - Listagem de usuarios\n");
    printf("\t 3 - Listagem de estabelecimento\n");
    printf("\t 4 - CheckIn\n");
    printf("\t 5 - Visitas por ID\n");
    printf("\t 0 - Fechar programa\n");
}

/*
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
*/

void cadastroUsuarios(Usuario* usuarios, int* accUs){
    char cont;
    do{
        printf("Nome: ");
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

void salvarDados(Usuario usuarios[MAX_US]){
    FILE *arq = fopen("usuarios.txt", "w");
    
    if(arq == NULL){
        printf("Erro ao salvar o dados de usuarios\n");
        return;
    }

    for(int i = 0; i < accUs; i++){
        fprintf(arq, "%d %s\n", usuarios[i].id, usuarios[i].nome);
    }

    fclose(arq);
}