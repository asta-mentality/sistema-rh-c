// Projeto de portfólio
// Sistema de RH

#include <stdio.h>
#include <stdlib.h> // Necessário para usar malloc, free e NULL
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

    strcpy(novo->Nome, nome);
    strcpy(novo->Funcao, funcao);
    strcpy(novo->Celular, celular);
    strcpy(novo->E_mail, e_mail);
    novo->Piso_salarial = piso_salarial;
    novo->Num_registro = num_registro;

    novo->prox = *prim;
    *prim = novo;

    printf("=== Funcionário Cadastrado com Sucesso! ===\n\n");
    printf("Funcionário: %s\n", novo->Nome);
    printf("Função: %s\n", novo->Funcao);
    printf("Contato: %s\n", novo->Celular);
    printf("E-mail: %s\n", novo->E_mail);
    printf("Piso salarial: R$ %.2f\n", novo->Piso_salarial);
    printf("ID: %d\n\n", novo->Num_registro);
}

// Função para remover um funcionário pelo ID e liberar a memória RAM com free()
void removerFuncionario(Funcionario **prim, int id_busca) {
    if (*prim == NULL) {
        printf("Erro: A lista está vazia!\n\n");
        return;
    }

    Funcionario *aux = *prim;
    Funcionario *ant = NULL;

    // Se o funcionário a ser removido é o primeiro da lista (cabeça)
    if (aux->Num_registro == id_busca) {
        *prim = aux->prox;
        free(aux); // Libera a memória RAM do nó isolado
        printf("=== Funcionário removido com sucesso e memória liberada! ===\n\n");
        return;
    }

    // Percorre a lista mantendo o rastro do elemento anterior
    while (aux != NULL && aux->Num_registro != id_busca) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Erro: Nenhum funcionário encontrado com a ID %d.\n\n", id_busca);
        return;
    }

    // Isola o nó atual e libera a memória
    ant->prox = aux->prox;
    free(aux);
    printf("=== Funcionário removido com sucesso e memória liberada! ===\n\n");
}

int main()
{
    int opcao;
    int c; // Variável auxiliar para limpar o buffer
    int contador_id = 1; // Controla a geração sequencial e perpétua dos IDs

    Funcionario *prim = NULL; // Ponteiro âncora

    do {
        printf("============================================\n");
        printf("           SISTEMA DE FUNCIONÁRIOS          \n");
        printf("============================================\n\n");

        printf("[1] - Registro de funcionários\n");
        printf("[2] - Consulta e Gestão de registros\n");
        printf("[3] - Folha de pagamento\n");
        printf("[4] - Encerrar programa\n\n");

        printf("Escolha uma opção:\n\n");
        scanf("%d", &opcao);

        while((c = getchar()) != '\n' && c != EOF);
        printf("\n");

        if(opcao < 1 || opcao > 4) {
            printf("Escolha uma opção válida\n\n");
        }

        // OPÇÃO 1: Cadastro dinâmico
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

                while((c = getchar()) != '\n' && c != EOF);  
                printf("\n");      

                inserirIni(&prim, nome_temp, funcao_temp, celular_temp, e_mail_temp, piso_temp, contador_id);

                contador_id++; // O ID sempre avança, garantindo coerência diária

                printf("Deseja registrar outro funcionário?\n\n");
                printf("[1] - Sim\n");
                printf("[2] - Voltar ao Menu Principal\n\n");

                scanf("%d", &continuar_cadastro);
                while((c = getchar()) != '\n' && c != EOF);
                printf("\n");
                
            } while(continuar_cadastro == 1);
        }

        // OPÇÃO 2: Consulta e Gestão de Registros (CRUD Completo)
        if(opcao == 2) {
            int sub_opcao; 

            printf("=========================================\n");
            printf("       CONSULTA E GESTÃO DE REGISTROS    \n");
            printf("=========================================\n\n");

            printf("[1] - Buscar por registro único (ID)\n");
            printf("[2] - Ver todos os registros\n");
            printf("[3] - Atualizar um registro\n");
            printf("[4] - Remover um registro\n\n");

            printf("Escolha uma opção:\n\n");
            scanf("%d", &sub_opcao);
            while((c = getchar()) != '\n' && c != EOF);
            printf("\n");

            // Validação de segurança para o sub-menu
            if(sub_opcao < 1 || sub_opcao > 4) {
                printf("Escolha uma opção válida\n\n");
            } else {
                // Sub-opção 1: Busca por ID único
                if(sub_opcao == 1) {
                    int buscar_id; 
                    int encontrado = 0;

                    printf("Digite a ID solicitada:\n");
                    scanf("%d", &buscar_id);
                    while((c = getchar()) != '\n' && c != EOF);
                    printf("\n");

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

                            break; 
                        }
                        aux = aux->prox;
                    }

                    if(encontrado == 0) {
                        printf("Erro: Nenhum funcionário encontrado com a ID %d.\n\n", buscar_id);
                    }

                    printf("Pressione [Enter] para voltar ao Menu Principal...");
                    getchar();
                    printf("\n\n");
                }
                // Sub-opção 2: Ver todos os registros
                else if(sub_opcao == 2) {
                    if(prim == NULL) {
                        printf("Nenhum funcionário cadastrado!\n\n");
                    } else {
                        Funcionario *aux = prim;

                        while(aux != NULL) {
                            printf("Número de registro: %d\n", aux->Num_registro);
                            printf("Funcionário: %s\n", aux->Nome);
                            printf("Função: %s\n", aux->Funcao);    
                            printf("Piso salarial: R$ %.2f\n", aux->Piso_salarial);
                            printf("Contatos: %s, %s\n\n", aux->Celular, aux->E_mail);

                            aux = aux->prox;
                        }
                    }

                    printf("Pressione [Enter] para voltar ao Menu Principal...");
                    getchar();
                    printf("\n\n");
                }
                // Sub-opção 3: Atualizar um registro
                else if(sub_opcao == 3) {
                    if(prim == NULL) {
                        printf("Erro: Nenhum funcionário cadastrado para atualizar!\n\n");
                        printf("Pressione [Enter] para voltar ao Menu Principal...");
                        getchar();
                        printf("\n\n");
                    } else {
                        int continuar_atualizar;
                        do {
                            int buscar_id;
                            int encontrado = 0;

                            printf("=========================================\n");
                            printf("          ATUALIZAR REGISTRO             \n");
                            printf("=========================================\n\n");

                            printf("Digite a ID do funcionário que deseja atualizar:\n");
                            scanf("%d", &buscar_id);
                            while((c = getchar()) != '\n' && c != EOF);
                            printf("\n");

                            Funcionario *aux = prim;
                            while(aux != NULL) {
                                if(aux->Num_registro == buscar_id) {
                                    encontrado = 1;

                                    printf("=== Funcionário Encontrado ===\n");
                                    printf("Nome atual: %s\n", aux->Nome);
                                    printf("Função atual: %s\n\n", aux->Funcao);

                                    printf("Digite o novo nome:\n");
                                    scanf(" %49[^\n]", aux->Nome);
                                    printf("\n");

                                    printf("Digite a nova função:\n");
                                    scanf(" %49[^\n]", aux->Funcao);
                                    printf("\n");

                                    printf("Digite o novo número de celular:\n");
                                    scanf(" %24[^\n]", aux->Celular);
                                    printf("\n");

                                    printf("Digite o novo E-mail:\n");
                                    scanf(" %49[^\n]", aux->E_mail);
                                    printf("\n");

                                    printf("Digite o novo Piso salarial:\n");
                                    scanf(" %f", &aux->Piso_salarial);
                                    while((c = getchar()) != '\n' && c != EOF);
                                    printf("\n");

                                    printf("=== Dados atualizados com sucesso! ===\n\n");
                                    break;
                                }
                                aux = aux->prox;
                            }

                            if(encontrado == 0) {
                                printf("Erro: Nenhum funcionário encontrado com a ID %d.\n\n", buscar_id);
                            }

                            printf("Deseja atualizar outro registro?\n\n");
                            printf("[1] - Sim\n");
                            printf("[2] - Voltar ao Menu Principal\n\n");

                            scanf("%d", &continuar_atualizar);
                            while((c = getchar()) != '\n' && c != EOF);
                            printf("\n");

                        } while(continuar_atualizar == 1);
                    }
                }
                // Sub-opção 4: Remover um registro
                else if(sub_opcao == 4) {
                    if(prim == NULL) {
                        printf("Erro: Nenhum funcionário cadastrado para remover!\n\n");
                        printf("Pressione [Enter] para voltar ao Menu Principal...");
                        getchar();
                        printf("\n\n");
                    } else {
                        int continuar_remover;
                        do {
                            int buscar_id;

                            printf("=========================================\n");
                            printf("          REMOVER REGISTRO               \n");
                            printf("=========================================\n\n");

                            printf("Digite a ID do funcionário que deseja remover:\n");
                            scanf("%d", &buscar_id);
                            while((c = getchar()) != '\n' && c != EOF);
                            printf("\n");

                            // Chama a função de remoção segura com free()
                            removerFuncionario(&prim, buscar_id);

                            printf("Deseja remover outro registro?\n\n");
                            printf("[1] - Sim\n");
                            printf("[2] - Voltar ao Menu Principal\n\n");

                            scanf("%d", &continuar_remover);
                            while((c = getchar()) != '\n' && c != EOF);
                            printf("\n");

                        } while(continuar_remover == 1);
                    }
                }
            }
        }

    } while(opcao != 4);

    return 0;
}