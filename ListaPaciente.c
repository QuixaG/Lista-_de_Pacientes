#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Paciente{
   int cpf;
   char* nomePaci;
   struct Paciente *prox;
};

/**
 * Estrutura de Fila.
 * Inicio representa o primeiro da fila, por onde se sai dela.
 * Fim representa o final da fila, por onde se entra na estrutura.
 */
struct Fila{
     struct Paciente *inicio;
     struct Paciente *fim;
};

struct Paciente* criarPaciente(int cpf, char* nomePaci){
	struct Paciente *p = malloc(sizeof(struct Paciente));
	p->cpf = cpf;
	p->nomePaci = nomePaci;
    p->prox = NULL;
	return p;
}

struct Fila* novaFila(){
    struct Fila *f = malloc(sizeof (struct Fila));
    f->fim = NULL;
    f->inicio = NULL;
    return f;
}

void imprimirFila(struct Fila *p){
    struct Paciente *ptr = p->fim;
    if(ptr != NULL){
        printf("Lista de espera a partir do ultimo da fila\n");
        while(ptr != NULL){
            printf("%i - %s\n", ptr->cpf, ptr->nomePaci);
            ptr = ptr->prox;
        }
    }else{
        printf("Fila Vazia.\n");
    }
}

void enfileira(struct Paciente *paciente , struct Fila *f){
    if (f->inicio == NULL){
        f->inicio = paciente;
        f->fim = paciente;
    }else{
        struct Paciente *tmp = f->fim;
        f->fim = paciente;
        paciente->prox = tmp;
    }
}

void desenfileira (struct Fila *f){
    if(f->inicio == NULL)	return;
    struct Paciente *tmp = f->fim;
    if(tmp->prox == NULL){ //So um elemento
        f->inicio = NULL;
        f->fim = NULL;
        free(tmp);
    }else{
        while(tmp->prox != f->inicio){
            tmp = tmp->prox;
        }
        tmp->prox = NULL;
        free(f->inicio);
        f->inicio = tmp;
    }
}


int main(int argc, char **argv) {
    struct Fila *p1 = novaFila();

    int opcao;
    while(1) {
        printf("===================================\nMENU:\n1. Retirar Senha\n2. Proximo paciente\n3. Mostrar fila\n4. Sair");
        printf("\nEscolha sua opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int cpf;
            printf("\nFavor informar seu CPF: ");
            scanf("%d", &cpf);
            char* nome = malloc(50*sizeof (char));
            printf("Favor informar seu nome completo: ");
            scanf("%s", nome);
            struct Paciente *paciente = criarPaciente(cpf, nome);
            enfileira(paciente, p1);
            printf("> Obrigado, aguarde sua vez!\n");
        } else if (opcao == 2){
            if(p1->inicio == NULL){
                printf("Nao ha mais pacientes.\n");
            }else{
                printf("%s - Favor se dirigir ao consultorio.\n", p1->inicio->nomePaci);
                desenfileira(p1);
            }
        }else if (opcao == 3){
            imprimirFila(p1);
        }else if (opcao == 4){
            printf("Obrigado, ate mais!!!\n");
            break;
        }else{
            printf("Opcao invalida. Favor tentar novamente.\n");
        }
    }
    return 1;
}