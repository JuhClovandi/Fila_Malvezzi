#include <stdio.h>
#include <stdlib.h>

// Estrutura de um processo
typedef struct processo {
    int id; // Identificador do processo (PID)
    struct processo* prox; // Ponteiro para o próximo processo na lista
} Processo;


// Função para adicionar um processo à fila (enfileirar)
void enqueue(Processo** frente, Processo** atras, int id) {
    Processo* novoProcesso = (Processo*)malloc(sizeof(Processo)); // Aloca memória para um novo processo

    // Verifica se a alocação de memória foi bem-sucedida
    if (!novoProcesso) {
        printf("Erro ao alocar memória!!\n");
        return;
    }

    // Inicializa o novo processo
    novoProcesso->id = id; // Define o PID do novo processo
    novoProcesso->prox = NULL; // Define o próximo como NULL

    // Se a fila estiver vazia, o novo processo se torna o primeiro e o último
    if (*atras == NULL) {
        *frente = *atras = novoProcesso;
    } else {
        // senão, Adiciona o novo processo ao final da fila
        (*atras)->prox = novoProcesso; // O último processo aponta para o novo
        *atras = novoProcesso; // Atualiza o ponteiro 'atras' para o novo processo
    }

    printf("Processo com Identificador de Processo (PID) %d enfileirado com sucesso!\n", id);
}


// Função para remover um processo da fila (Desenfileirar)
Processo* dequeue(Processo** frente, Processo** atras) {
    // Verifica se a fila está vazia
    if (*frente == NULL) {
        printf("\nA fila se encontra vazia!\n");
        return NULL;
    }

    Processo* processoRemovido = *frente; // Guarda o processo que será removido
    *frente = (*frente)->prox; // Atualiza o ponteiro 'frente' para o próximo processo da fila

    //Se a fila ficar vazia após a remoção, atualiza o ponteiro 'atras'
    if (*frente == NULL) {
        *atras = NULL;
    }

    printf("Processo desenfileirado com Identificador de Processo (PID): %d\n", processoRemovido->id);
    
    return processoRemovido; // Retorna o processo que foi removido
}


// Função para empilhar um processo na pilha
void push(Processo** topo, Processo* processo) {
    processo->prox = *topo; // O novo processo aponta para o topo atual da pilha
    *topo = processo; // O ponteiro 'topo' é atualizado para apontar para o novo processo
    printf("Processo com Identificador de Processo (PID) %d empilhado com sucesso!\n", processo->id);
}


// Função para desempilhar um processo da pilha
Processo* pop(Processo** topo) {
    // Verifica se a pilha está vazia
    if (*topo == NULL) {
        printf("A pilha está vazia!\n");
        return NULL;
    }

    Processo* processoDesempilhado = *topo; // Guarda o processo que será desempilhado (o topo atual da pilha)
    *topo = (*topo)->prox; // Atualiza o ponteiro 'topo' para o próximo processo na pilha
    printf("Processo desempilhado com Identificador de Processo (PID): %d\n", processoDesempilhado->id);
    return processoDesempilhado; // Retorna o processo desempilhado para possível liberação de memória
}


// Função para imprimir o conteúdo da fila
void imprimirQueue(Processo* frente) {
    // Verifica se a fila está vazia
    if (frente == NULL) {
        printf("A fila (Queue) de processos se encontra vazia!\n");
        return;
    }

    printf("\n");
    printf("Conteudo da fila (Queue) de processos: ");
    Processo* atual = frente; // Inicia do primeiro processo da fila
    
    // Percorre a fila e imprime os IDs dos processos
    while (atual != NULL) {
        printf("%d ", atual->id);
        atual = atual->prox; // Move para o próximo processo
    }
    
    printf("\n");
}

// Função para imprimir o conteúdo da pilha de processos
void imprimirStack(Processo* stack) {
    // Verifica se a pilha está vazia
    if (stack == NULL) {
        printf("A pilha (Stack) de processos se encontra vazia!\n");
        return;
    }

    printf("Conteudo da pilha (Stack) de processos: ");
    Processo* atual = stack; // Inicia do topo da pilha
    
     // Percorre a pilha e imprime os IDs dos processos
    while (atual != NULL) {
        printf("%d ", atual->id);
        atual = atual->prox; // Move para o próximo processo
    }
    
    printf("\n");
}


// Função principal
int main() {
    Processo* topo = NULL; // Inicializa o topo da pilha
    Processo* frente = NULL; // Inicializa a frente da fila
    Processo* atras = NULL; // Inicializa o fim da fila

    printf("\n=== Criacao e Enfileiramento de Processos na Queue ===\n");
    enqueue(&frente, &atras, 1);
    enqueue(&frente, &atras, 2);
    enqueue(&frente, &atras, 3);
    
    imprimirQueue(frente);

    printf("\n=== Despacho de Processos da Queue para a Stack ===\n");
    Processo* processo;
    while ((processo = dequeue(&frente, &atras)) != NULL) {
        push(&topo, processo);
    }

    printf("\n=== Historico de Processos da Stack finalizados ===\n");

    imprimirStack(topo);

    while (topo != NULL) {
        Processo* temp = pop(&topo);
        free(temp);
    }

    printf("\n");
    imprimirStack(topo);
    printf("\n");

    return 0;
}
