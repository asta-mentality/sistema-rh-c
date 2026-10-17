// Projeto de portfólio
// Sistema de RH

#include <stdio.h>

struct Funcionario {
    char Nome[50];
    char Funcao[50];
    char Celular[25];
    char E_mail[50];
    float Piso_salarial;
    int Num_registro;
};

int main()
{
    int opcao;
    int total_funcionarios = 0;
    int c; // Variável auxiliar para limpar o buffer

    struct Funcionario funcionarios[100];

    do {
        // 10 linhas antes de escrever!
        printf("============================================\n");
        printf("          SISTEMA DE FUNCIONÁRIOS           \n");
        printf("============================================\n\n");

        printf("[1] - Registro de funcionários\n");
        printf("[2] - Consulta de registros\n");
        printf("[3] - Folha de pagamento\n");
        printf("[4] - Encerrar programa\n\n");

        printf("Escolha uma opção:\n\n");
        scanf("%d", &opcao);

        // Limpa o '\n' que o scanf deixa no buffer do Menu Principal
        while((c = getchar()) != '\n' && c != EOF);

        printf("\n");

        if(opcao > 4) {
            printf("Escolha uma opção válida\n\n");
        } 

        if(opcao == 1) {
            // 1. Verifica se o limite já foi atingido antes de qualquer coisa
            if (total_funcionarios >= 100) {
                printf("============================================\n");
                printf("         REGISTRO DE FUNCIONÁRIOS           \n");
                printf("============================================\n\n");

                printf("Erro: Capacidade máxima de cadastro atingida (100 funcionarios)\n");
                printf("Não é possível adicionar novos registros no momento!\n\n");
        
                printf("Pressione [Enter] para voltar ao Menu Principal...");
                getchar(); // Pausa para o usuário ler

            } else {
                // 2. Se tiver vaga, o do...while fica PROTEGIDO dentro do else!
                int continuar_cadastro;

                do {
                    // 10 linhas antes de escrever!
                    printf("============================================\n");
                    printf("          REGISTRO DE FUNCIONÁRIOS          \n");
                    printf("============================================\n\n");

                    // Recebe informações do Funcionário
                    printf("Digite seu nome:\n");
                    scanf(" %49[^\n]", funcionarios[total_funcionarios].Nome);
                    printf("\n");

                    printf("Digite sua função:\n");
                    scanf(" %49[^\n]", funcionarios[total_funcionarios].Funcao);
                    printf("\n");

                    printf("Digite seu número de celular:\n");
                    scanf(" %24[^\n]", funcionarios[total_funcionarios].Celular);
                    printf("\n");

                    printf("Digite seu E-mail:\n");
                    scanf(" %49[^\n]", funcionarios[total_funcionarios].E_mail);
                    printf("\n");

                    printf("Digite seu Piso salarial:\n");
                    scanf(" %f", &funcionarios[total_funcionarios].Piso_salarial);

                    // Limpa o buffer após o scanf do float
                    while((c = getchar()) != '\n' && c != EOF);  
                    printf("\n");      

                    // Criação automática do número de registro
                    funcionarios[total_funcionarios].Num_registro = total_funcionarios + 1;

                    // Devolve as informações
                    printf("Funcionário: %s\n", funcionarios[total_funcionarios].Nome);
                    printf("Função: %s\n", funcionarios[total_funcionarios].Funcao);
                    printf("Contato: %s\n", funcionarios[total_funcionarios].Celular);
                    printf("E-mail: %s\n", funcionarios[total_funcionarios].E_mail);
                    printf("Piso salarial: R$ %.2f\n", funcionarios[total_funcionarios].Piso_salarial);
                    printf("ID: %d\n\n", funcionarios[total_funcionarios].Num_registro);    

                    // Avança para próxima posição do array!
                    total_funcionarios += 1;    

                    // ATENÇÃO: Se o usuário atingiu o 100º cadastro agora, 
                    // barramos antes de perguntar se ele quer continuar cadastrando.
                    if (total_funcionarios >= 100) {
                        printf("Limite de 100 funcionários atingido com este último cadastro!\n");
                        printf("Retornando ao Menu Principal...\n\n");
                    
                        printf("Pressione [Enter] para continuar...");
                        getchar();
                        break; // Encerra o do-while imediatamente!
                    }

                    // Pergunta se deseja cadastrar outro funcionário
                    printf("Deseja registrar outro funcionário?\n\n");
                    printf("[1] - Sim\n");
                    printf("[2] - Voltar ao Menu Principal\n\n");

                    scanf("%d", &continuar_cadastro);
                    while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
                    printf("\n");
                    
                } while(continuar_cadastro == 1);
            }
        }

        if(opcao == 2) {
            int sub_opcao; // Variável para o sub-menu

            // 10 linhas antes de escrever!
            printf("=========================================\n");
            printf("           CONSULTA DE REGISTROS         \n");
            printf("=========================================\n\n");

            printf("[1] - Buscar por registro único (ID)\n");
            printf("[2] - Ver todos os registro\n\n");

            printf("Escolha uma opção:\n\n");
            scanf("%d", &sub_opcao);
            while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
            printf("\n");

            // Caminho 1: Busca por ID único
            if(sub_opcao == 1) {
                int i;
                int Buscar_id; // Variável para encontrar a ID específica
                int encontrado = 0; // Flag!

                printf("Digite a ID solicitada:\n");
                scanf("%d", &Buscar_id);
                while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
                printf("\n");

                // O laço varre o array do 0 até o total 
                // de funcionários cadastrados
                for(i = 0; i < total_funcionarios; i++ ) {

                    // Se o ID digitado bater com o ID da posição 'i' do array...
                    if(Buscar_id == funcionarios[i].Num_registro) {
                        // Flag de encontrado!
                        encontrado = 1;

                        printf("=== Funcionário Encontrado ===\n\n");
                        printf("Número de registro: %d\n", funcionarios[i].Num_registro);
                        printf("Funcionário: %s\n", funcionarios[i].Nome);
                        printf("Função: %s\n", funcionarios[i].Funcao);
                        printf("Piso salarial: R$ %.2f\n", funcionarios[i].Piso_salarial);
                        printf("Contatos: %s, %s\n\n", funcionarios[i].Celular, funcionarios[i].E_mail);

                        break; // Para de procurar, ID úico encontrado!
                    } 
                }
                // Se o laço acabou e Flag continuou em 0, o ID não existe
                if(encontrado == 0) {
                    printf("Erro: Nenhum funcionário encontrado com a ID %d.\n\n", Buscar_id);
                }

                printf("Pressione [Enter] para voltar ao Menu Principal...");
                getchar();
                printf("\n\n");

            }
            // Caminho 2: Ver todos os registros
            else if(sub_opcao == 2) {

                if(total_funcionarios == 0) {
                    printf("Nenhum funcionário cadastrado!\n\n");

                } else {
                    int i;
                    for(i = 0; i < total_funcionarios; i++) {
                        printf("Número de registro: %d\n", funcionarios[i].Num_registro);
                        printf("Funcionário: %s\n", funcionarios[i].Nome);
                        printf("Função: %s\n", funcionarios[i].Funcao);    
                        printf("Piso salarial: R$ %.2f\n", funcionarios[i].Piso_salarial);
                        printf("Contatos: %s, %s\n\n", funcionarios[i].Celular, funcionarios[i].E_mail);
                    }
                }

                printf("Pressione [Enter] para voltar ao Menu Principal...");
                getchar();
                printf("\n\n");
            }
        }

    } while(opcao != 4);

    return 0;
}