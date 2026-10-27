// Projeto de portfólio
// Sistema de RH

#include <stdio.h>
#include <stdlib.h> // Necessário para usar malloc e NULL
#include <string.h> // Necessário para usar strcpy

typedef struct Funcionario {
    char Nome[50];
    char Funcao[50];
    char Celular[25];
    char E_mail[50];
    float Piso_salarial;
    int Num_registro;

    struct Funcionario *prox;
} Funcionario;

// Função para inserir um novo funcionário no início da lista (LIFO / Pilha)
void inserirIni(Funcionario **prim, char nome[], char funcao[], char celular[],
        char e_mail[], float piso_salarial, int num_registro) {
     
    // Aloca dinamicamente memória para um novo nó do tipo Funcionario
    Funcionario *novo = (Funcionario *) malloc(sizeof(Funcionario));              

    if (novo == NULL) {
        printf("============================================\n");
        printf("          REGISTRO DE FUNCIONÁRIOS          \n");
        printf("============================================\n\n");
        
        printf("Erro: Memória insuficiente no sistema!\n");
        printf("Não foi possível alocar espaço para o novo funcionário.\n\n");
        printf("Pressione [Enter] para retornar ao Menu Principal...");
        getchar();
        return;
    }

    // Preenche os campos do novo funcionário com os valores recebidos
    strcpy(novo->Nome, nome);
    strcpy(novo->Funcao, funcao);
    strcpy(novo->Celular, celular);
    strcpy(novo->E_mail, e_mail);
    novo->Piso_salarial = piso_salarial;
    novo->Num_registro = num_registro;

    // O novo nó aponta para quem era o primeiro anteriormente
    novo->prox = *prim;

    // O ponteiro principal (prim) passa a apontar para o novo nó
    *prim = novo;

    // Exibe as informações cadastradas com sucesso
    printf("=== Funcionário Cadastrado com Sucesso! ===\n\n");
    printf("Funcionário: %s\n", novo->Nome);
    printf("Função: %s\n", novo->Funcao);
    printf("Contato: %s\n", novo->Celular);
    printf("E-mail: %s\n", novo->E_mail);
    printf("Piso salarial: R$ %.2f\n", novo->Piso_salarial);
    printf("ID: %d\n\n", novo->Num_registro);
}

int main()
{
    int opcao;
    int c; // Variável auxiliar para limpar o buffer
    int contador_id = 1; // Controla a geração sequencial dos IDs

    Funcionario *prim = NULL; // Ponteiro âncora que aponta para o primeiro funcionário (começa vazio)

    do {
        printf("============================================\n");
        printf("           SISTEMA DE FUNCIONÁRIOS          \n");
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

        // OPÇÃO 1: Cadastro dinâmico de funcionários
        if(opcao == 1) {
            int continuar_cadastro;

            do {
                char nome_temp[50];
                char funcao_temp[50];
                char celular_temp[25];
                char e_mail_temp[50];
                float piso_temp;

                printf("============================================\n");
                printf("          REGISTRO DE FUNCIONÁRIOS          \n");
                printf("============================================\n\n");

                // Recebe informações temporárias do Funcionário
                printf("Digite seu nome:\n");
                scanf(" %49[^\n]", nome_temp);
                printf("\n");

                printf("Digite sua função:\n");
                scanf(" %49[^\n]", funcao_temp);
                printf("\n");

                printf("Digite seu número de celular:\n");
                scanf(" %24[^\n]", celular_temp);
                printf("\n");

                printf("Digite seu E-mail:\n");
                scanf(" %49[^\n]", e_mail_temp);
                printf("\n");

                printf("Digite seu Piso salarial:\n");
                scanf(" %f", &piso_temp);

                // Limpa o buffer após o scanf do float
                while((c = getchar()) != '\n' && c != EOF);  
                printf("\n");      

                // Chama a função que aloca dinamicamente e insere no início da lista
                inserirIni(&prim, nome_temp, funcao_temp, celular_temp, e_mail_temp, piso_temp, contador_id);

                // Incrementa o ID para o próximo cadastro
                contador_id++;

                // Pergunta se deseja cadastrar outro funcionário
                printf("Deseja registrar outro funcionário?\n\n");
                printf("[1] - Sim\n");
                printf("[2] - Voltar ao Menu Principal\n\n");

                scanf("%d", &continuar_cadastro);
                while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
                printf("\n");
                
            } while(continuar_cadastro == 1);
        }

        // OPÇÃO 2: Consulta de registros utilizando a lista encadeada e ponteiro aux
        if(opcao == 2) {
            int sub_opcao; // Variável para o sub-menu

            printf("=========================================\n");
            printf("           CONSULTA DE REGISTROS         \n");
            printf("=========================================\n\n");

            printf("[1] - Buscar por registro único (ID)\n");
            printf("[2] - Ver todos os registros\n\n");

            printf("Escolha uma opção:\n\n");
            scanf("%d", &sub_opcao);
            while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
            printf("\n");

            // Caminho 1: Busca por ID único
            if(sub_opcao == 1) {
                int buscar_id; 
                int encontrado = 0; // Flag

                printf("Digite a ID solicitada:\n");
                scanf("%d", &buscar_id);
                while((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
                printf("\n");

                // Ponteiro auxiliar para percorrer a lista sem perder a âncora 'prim'
                Funcionario *aux = prim;

                while(aux != NULL) {
                    if(buscar_id == aux->Num_registro) {
                        encontrado = 1;

                        printf("=== Funcionário Encontrado ===\n\n");
                        printf("Número de registro: %d\n", aux->Num_registro);
                        printf("Funcionário: %s\n", aux->Nome);
                        printf("Função: %s\n", aux->Funcao);
                        printf("Piso salarial: R$ %.2f\n", aux->Piso_salarial);
                        printf("Contatos: %s, %s\n\n", aux->Celular, aux->E_mail);

                        break; // ID único encontrado, encerra a busca
                    }
                    aux = aux->prox; // Avança para o próximo nó da lista
                }

                if(encontrado == 0) {
                    printf("Erro: Nenhum funcionário encontrado com a ID %d.\n\n", buscar_id);
                }

                printf("Pressione [Enter] para voltar ao Menu Principal...");
                getchar();
                printf("\n\n");
            }
            // Caminho 2: Ver todos os registros
            else if(sub_opcao == 2) {
                if(prim == NULL) {
                    printf("Nenhum funcionário cadastrado!\n\n");
                } else {
                    // Ponteiro auxiliar para percorrer a lista do início ao fim
                    Funcionario *aux = prim;

                    while(aux != NULL) {
                        printf("Número de registro: %d\n", aux->Num_registro);
                        printf("Funcionário: %s\n", aux->Nome);
                        printf("Função: %s\n", aux->Funcao);    
                        printf("Piso salarial: R$ %.2f\n", aux->Piso_salarial);
                        printf("Contatos: %s, %s\n\n", aux->Celular, aux->E_mail);

                        aux = aux->prox; // Salta para o próximo nó
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