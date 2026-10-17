#include <stdio.h>

// Função responsável pelo cálculo do salário
float CalculoDeSalario(int Horas_trabalhadas, float Valor_hora) {
    float Salario_total;
    int Horas_extras;

    // Verifica se o funcionário trabalhou mais de 40 horas
    if (Horas_trabalhadas > 40) {
        Horas_extras = Horas_trabalhadas - 40;

        // Calcula o salário com adicional de 50% nas horas extras
        Salario_total = (40 * Valor_hora) + (Horas_extras * Valor_hora * 1.5);

    } else {
        // Calcula o salário sem horas extras
        Salario_total = Horas_trabalhadas * Valor_hora;
    }

    return Salario_total;
}

int main() {
    char Nome[50];
    int Horas_trabalhadas;
    float Valor_hora;
    float Salario_total;

    // Entrada dos dados do funcionário
    printf("Digite seu nome.: ");
    scanf(" %49s[^\n]", Nome);

    printf("Quantas horas você trabalhou?: ");
    scanf("%d", &Horas_trabalhadas);

    printf("Quanto você recebe por hora?: ");
    scanf("%f", &Valor_hora);

    // Chama a função e armazena o salário calculado
    Salario_total = CalculoDeSalario(Horas_trabalhadas, Valor_hora);

    // Exibe o resultado final
    printf("Funcionário: %s\n", Nome);
    printf("Salário total: R$ %.2f\n", Salario_total);

    return 0;
}