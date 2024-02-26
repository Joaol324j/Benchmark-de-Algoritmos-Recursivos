#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar arquivo contendo números inteiros aleatórios
void gerarArquivo(int quantidade) {
    FILE *arquivo = fopen("numeros.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < quantidade; i++) {
        int numero = rand() % 1000; 
        fprintf(arquivo, "%d ", numero);
    }

    fclose(arquivo);
}

// Função para busca linear de um número no arquivo
int buscaLinear(int numero) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    int elemento;
    clock_t inicio = clock();

    while (fscanf(arquivo, "%d", &elemento) != EOF) {
        if (elemento == numero) {
            fclose(arquivo);
            clock_t fim = clock();
            return (int)(fim - inicio);
        }
    }

    fclose(arquivo);
    return -1;
}

// Função para busca sentinela de um número no arquivo
int buscaSentinela(int numero) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    int elemento;
    int ultimoElemento;
    clock_t inicio = clock();

    while (fscanf(arquivo, "%d", &elemento) != EOF) {
        if (elemento == numero) {
            fclose(arquivo);
            clock_t fim = clock();
            return (int)(fim - inicio);
        }
        ultimoElemento = elemento;
    }

    if (ultimoElemento == numero) {
        fclose(arquivo);
        clock_t fim = clock();
        return (int)(fim - inicio);
    }

    fclose(arquivo);
    return -1;
}

// Função para particionamento no Quick Sort
int particionar(int *numeros, int esquerda, int direita) {
    int pivo = numeros[direita];
    int i = esquerda - 1;

    for (int j = esquerda; j <= direita - 1; j++) {
        if (numeros[j] < pivo) {
            i++;
            int temp = numeros[i];
            numeros[i] = numeros[j];
            numeros[j] = temp;
        }
    }

    int temp = numeros[i + 1];
    numeros[i + 1] = numeros[direita];
    numeros[direita] = temp;

    return i + 1;
}

// Função de ordenação Quick Sort
void quickSort(int *numeros, int esquerda, int direita) {
    if (esquerda < direita) {
        int pivo = particionar(numeros, esquerda, direita);
        quickSort(numeros, esquerda, pivo - 1);
        quickSort(numeros, pivo + 1, direita);
    }
}

// Função de mesclagem no Merge Sort
void merge(int *numeros, int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = numeros[esquerda + i];
    for (int j = 0; j < n2; j++)
        R[j] = numeros[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            numeros[k] = L[i];
            i++;
        } else {
            numeros[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        numeros[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        numeros[k] = R[j];
        j++;
        k++;
    }
}

// Função de ordenação Merge Sort
void mergeSort(int *numeros, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(numeros, esquerda, meio);
        mergeSort(numeros, meio + 1, direita);

        merge(numeros, esquerda, meio, direita);
    }
}

// Função para busca binária de um número no arquivo
int buscaBinaria(int numero, int quantidade) {
    FILE *arquivo = fopen("numeros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    int *numeros = (int *)malloc(quantidade * sizeof(int));
    if (numeros == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < quantidade; i++) {
        fscanf(arquivo, "%d", &numeros[i]);
    }

    fclose(arquivo);

    quickSort(numeros, 0, quantidade - 1);

    clock_t inicio = clock();
    int esquerda = 0;
    int direita = quantidade - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (numeros[meio] == numero) {
            free(numeros);
            clock_t fim = clock();
            return (int)(fim - inicio);
        }

        if (numeros[meio] < numero) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    free(numeros);
    return -1;
}

// Função de ordenação Bubble Sort
void bubbleSort(int *numeros, int quantidade) {
    clock_t inicio = clock();

    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    printf("Tempo gasto no Bubble Sort: %d ms\n", (int)(fim - inicio));
}

// Função de ordenação Insertion Sort
void insertionSort(int *numeros, int quantidade) {
    clock_t inicio = clock();

    for (int i = 1; i < quantidade; i++) {
        int chave = numeros[i];
        int j = i - 1;

        while (j >= 0 && numeros[j] > chave) {
            numeros[j + 1] = numeros[j];
            j--;
        }

        numeros[j + 1] = chave;
    }

    clock_t fim = clock();
    printf("Tempo gasto no Insertion Sort: %d ms\n", (int)(fim - inicio));
}

// Função para calcular o fatorial de um número de forma recursiva
int fatorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * fatorial(n - 1);
}

// Função para calcular o somatório de 1 até n de forma recursiva
int somatorio(int n) {
    if (n == 1)
        return 1;
    else
        return n + somatorio(n - 1);
}

// Função para calcular o n-ésimo termo da sequência de Fibonacci de forma recursiva
int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

// Função que implementa o menu de operações
void menuOperacoes(int quantidade) {
    int escolha;

    do {
        printf("\nEscolha uma operação:\n");
        printf("1. Busca de elemento (Linear, Sentinela, Binária)\n");
        printf("2. Classificação de elementos (Bubble Sort, Insertion Sort, Quick Sort, Merge Sort)\n");
        printf("3. Operações de comparação entre algoritmos iterativos e recursivos\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            int numero;
            printf("Digite o número que deseja buscar: ");
            scanf("%d", &numero);

            int tempoLinear = buscaLinear(numero);
            int tempoSentinela = buscaSentinela(numero);
            int tempoBinaria = buscaBinaria(numero, quantidade);

            if (tempoLinear != -1) {
                printf("Número encontrado com busca Linear em %d ms.\n", tempoLinear);
            } else {
                printf("Número não encontrado com busca Linear.\n");
            }

            if (tempoSentinela != -1) {
                printf("Número encontrado com busca Sentinela em %d ms.\n", tempoSentinela);
            } else {
                printf("Número não encontrado com busca Sentinela.\n");
            }

            if (tempoBinaria != -1) {
                printf("Número encontrado com busca Binária em %d ms.\n", tempoBinaria);
            } else {
                printf("Número não encontrado com busca Binária.\n");
            }
        } else if (escolha == 2) {
            FILE *arquivo = fopen("numeros.txt", "r");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo para leitura.\n");
                exit(1);
            }

            int *numeros = (int *)malloc(quantidade * sizeof(int));
            if (numeros == NULL) {
                printf("Erro de alocação de memória.\n");
                exit(1);
            }

            for (int i = 0; i < quantidade; i++) {
                fscanf(arquivo, "%d", &numeros[i]);
            }

            fclose(arquivo);

            int *copia = (int *)malloc(quantidade * sizeof(int));
            if (copia == NULL) {
                printf("Erro de alocação de memória.\n");
                exit(1);
            }

            for (int i = 0; i < quantidade; i++) {
                copia[i] = numeros[i];
            }

            clock_t inicioQuickSort = clock();
            quickSort(numeros, 0, quantidade - 1);
            clock_t fimQuickSort = clock();

            clock_t inicioMergeSort = clock();
            mergeSort(copia, 0, quantidade - 1);
            clock_t fimMergeSort = clock();

            bubbleSort(copia, quantidade);
            insertionSort(numeros, quantidade);

            free(numeros);
            free(copia);

            printf("Tempo gasto no Quick Sort: %d ms\n", (int)(fimQuickSort - inicioQuickSort));
            printf("Tempo gasto no Merge Sort: %d ms\n", (int)(fimMergeSort - inicioMergeSort));
        } else if (escolha == 3) {
            int numero;
            printf("Digite um número para calcular seu fatorial, somatório e fibonacci: ");
            scanf("%d", &numero);

            clock_t inicioIterativo, fimIterativo, inicioRecursivo, fimRecursivo;

            // Fatorial
            inicioIterativo = clock();
            int fatorialIterativo = fatorial(numero);
            fimIterativo = clock();

            inicioRecursivo = clock();
            int fatorialRecursivo = fatorial(numero);
            fimRecursivo = clock();

            printf("Fatorial (Iterativo): %d ms\n", (int)(fimIterativo - inicioIterativo));
            printf("Fatorial (Recursivo): %d ms\n", (int)(fimRecursivo - inicioRecursivo));

            // Somatório
            inicioIterativo = clock();
            int somatorioIterativo = somatorio(numero);
            fimIterativo = clock();

            inicioRecursivo = clock();
            int somatorioRecursivo = somatorio(numero);
            fimRecursivo = clock();

            printf("Somatório (Iterativo): %d ms\n", (int)(fimIterativo - inicioIterativo));
            printf("Somatório (Recursivo): %d ms\n", (int)(fimRecursivo - inicioRecursivo));

            // Fibonacci
            inicioIterativo = clock();
            int fibonacciIterativo = fibonacci(numero);
            fimIterativo = clock();

            inicioRecursivo = clock();
            int fibonacciRecursivo = fibonacci(numero);
            fimRecursivo = clock();

            printf("Fibonacci (Iterativo): %d ms\n", (int)(fimIterativo - inicioIterativo));
            printf("Fibonacci (Recursivo): %d ms\n", (int)(fimRecursivo - inicioRecursivo));
        }
    } while (escolha != 0);
}

// Função principal
int main() {
    int quantidade;

    printf("Quantos números inteiros aleatórios você deseja gerar e salvar no arquivo? ");
    scanf("%d", &quantidade);

    gerarArquivo(quantidade);

    menuOperacoes(quantidade);

    return 0;
}