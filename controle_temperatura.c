#include <stdio.h>

// Função que pede a temp para o usuário
// Em seguida devolve o valor informado

int lerTemperatura() {
    int temperatura;

    printf("Digite a temperatura: ");
    scanf("%d" , &temperatura);

    return temperatura;
}

// Função que analisa a temp informada
// Após a info define qual ação o programa deve realizar

int analisarTemperatura(int temperatura) {
    if (temperatura > 24) {
        return 1;
    } else if (temperatura < 18) {
        return 2;
    } else {
        return 3;
    }
}

// Função que mostra o resultado para o usuário
// da analise realizada pela função anterior

void exibirResultado(int resultado) {
    if (resultado == 1) {
        printf("Resfriando o ambiente!\n");
    }else if (resultado == 2) {
        printf("Aquecendo o ambiente!\n");
    } else {
        printf("A Temperatura do ambiente está estável!\n");
    }
}

int main() {
    // Recebe a temp informada pelo user
    int temperatura = lerTemperatura();

    // Analisa a temp e guarda a escolha
    int resultado = analisarTemperatura(temperatura);

    // Mostra ao user o resultado da analise
    exibirResultado(resultado);

    return 0;
}