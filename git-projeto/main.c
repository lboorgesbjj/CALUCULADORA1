#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

#define MAX 512

int main() {
    char expressao[MAX];

    printf("Digite a expressao em notacao pos-fixada (ou '0' para encerrar):\n");

    while (1) {
        printf("Expressão: ");
        fgets(expressao, sizeof(expressao), stdin);

        expressao[strcspn(expressao, "\n")] = '\0';

        if (strcmp(expressao, "0") == 0) {
            break;
        }

        char *inFixa = getFormaInFixa(expressao);

        float valor = getValor(expressao);

        if (valor == -1) {
            printf("Erro: Expressão inválida ou impossível de calcular.\n\n");
        } else {
            printf("Expressao Pos Fixada: %s\n", expressao);
            printf("Expressao Infixa: %s\n", inFixa);
            printf("Valor: %.5f\n\n", valor);
        }
    }

    return 0;
}
