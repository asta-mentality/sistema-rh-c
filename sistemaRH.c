// Projeto de portfólio
// Sistema de RH

#include <stdio.h>
#include <stdlib.h> // Necessário para usar malloc, free e NULL
#include <string.h> // Necessário para usar strcpy
#include <locale.h>

// Estrutura para gerenciar os cargos e pisos salariais da empresa (Normalização de dados)
typedef struct Cargo {
    char Nome_cargo[50];
    float Piso_salarial;
    struct Cargo *prox;
} Cargo;

typedef struct Funcionario {
    char Nome[50];
    char Funcao[50];
    char Celular[25];
    char E_mail[50];
    int Num_registro;

    // Campos limpos para a Folha de Pagamentos
    int Tempo_casa;       // Tempo de empresa contando em meses (inicia em 0)
    float Horas_extras;   // Banco de horas extras realizadas no mês

    struct Funcionario *prox;
} Funcionario;

// Função para inserir um novo funcionário no início da lista (LIFO / Pilha)
void inserirIni(Funcionario **prim, char nome[], char funcao[], char celular[],
        char e_mail[], int num_registro) {
     
    Funcionario *novo = (Funcionario *) malloc(sizeof(Funcionario));            

    if (novo == NULL) {
        printf("============================================\n");
        printf("            REGISTRO DE FUNCIONARIOS        \n");
        printf("============================================\n\n");
        printf("Erro: Memoria insuficiente no sistema!\n");
        printf("Nao foi possivel alocar espaco para o novo funcionario.\n\n");
        printf("Pressione [Enter] para retornar ao Menu Principal...");
        getchar();
        return;
    }

    strcpy(novo->Nome, nome);
    strcpy(novo->Funcao, funcao);
    strcpy(novo->Celular, celular);
    strcpy(novo->E_mail, e_mail);
    novo->Num_registro = num_registro;

    // Inicializando os novos campos da Folha
    novo->Tempo_casa = 0;
    novo->Horas_extras = 0.0f;

    novo->prox = *prim;
    *prim = novo;

    printf("=== Funcionario Cadastrado com Sucesso! ===\n\n");
    printf("Funcionario: %s\n", novo->Nome);
    printf("Funcao: %s\n", novo->Funcao);
    printf("Contato: %s\n", novo->Celular);
    printf("E-mail: %s\n", novo->E_mail);
    printf("ID: %d\n\n", novo->Num_registro);
}

// Função para remover um funcionário pelo ID e liberar a memória RAM com free()
void removerFuncionario(Funcionario **prim, int id_busca) {
    if (*prim == NULL) {
        printf("Erro: A lista esta vazia!\n\n");
        return;
    }

    Funcionario *aux = *prim;
    Funcionario *ant = NULL;

    // Se o funcionário a ser removido é o primeiro da lista (cabeça)
    if (aux->Num_registro == id_busca) {
        *prim = aux->prox;
        free(aux); // Libera a memória RAM do nó isolado
        printf("=== Funcionario removido com sucesso e memoria liberada! ===\n\n");
        return;
    }

    // Percorre a lista mantendo o rastro do elemento anterior
    while (aux != NULL && aux->Num_registro != id_busca) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Erro: Nenhum funcionario encontrado com a ID %d.\n\n", id_busca);
        return;
    }

    // Isola o nó atual e libera a memória
    ant->prox = aux->prox;
    free(aux);
    printf("=== Funcionario removido com sucesso e memoria liberada! ===\n\n");
}

// Função para inserir um novo cargo no início da lista de Configurações
void inserirCargo(Cargo **prim, char nome_cargo[], float piso_salarial) {
    Cargo *novo = (Cargo *) malloc(sizeof(Cargo));

    if (novo == NULL) {
        printf("Erro: Memoria insuficiente no sistema!\n\n");
        return;
    }

    strcpy(novo->Nome_cargo, nome_cargo);
    novo->Piso_salarial = piso_salarial;

    novo->prox = *prim;
    *prim = novo;

    printf("=== Cargo Cadastrado com Sucesso! ===\n\n");
    printf("Cargo: %s\n", novo->Nome_cargo);
    printf("Piso Salarial: R$ %.2f\n\n", novo->Piso_salarial);
}

// Função para remover um cargo pelo nome e liberar a memória RAM com free()
void removerCargo(Cargo **prim, char nome_busca[]) {
    if (*prim == NULL) {
        printf("Erro: A lista de cargos esta vazia!\n\n");
        return;
    }

    Cargo *aux = *prim;
    Cargo *ant = NULL;

    // Se o cargo a ser removido é o primeiro da lista (cabeça)
    if (strcmp(aux->Nome_cargo, nome_busca) == 0) {
        *prim = aux->prox;
        free(aux);
        printf("=== Cargo removido com sucesso e memoria liberada! ===\n\n");
        return;
    }

    // Percorre a lista mantendo o rastro do elemento anterior
    while (aux != NULL && strcmp(aux->Nome_cargo, nome_busca) != 0) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Erro: Nenhum cargo encontrado com o nome '%s'.\n\n", nome_busca);
        return;
    }

    // Isola o nó atual e libera a memória
    ant->prox = aux->prox;
    free(aux);
    printf("=== Cargo removido com sucesso e memoria liberada! ===\n\n");
}

// Função centralizada para calcular e exibir o holerite (Princípio DRY)
void gerarHolerite(Funcionario *func, Cargo *prim_cargo) {
    // 1. Busca o piso salarial na lista de cargos
    Cargo *aux_cargo = prim_cargo;
    float piso_encontrado = 0.0f; 
    int cargo_encontrado = 0;

    while (aux_cargo != NULL) {
        if (strcmp(aux_cargo->Nome_cargo, func->Funcao) == 0) {
            piso_encontrado = aux_cargo->Piso_salarial;
            cargo_encontrado = 1;
            break; // Interrompe o loop assim que encontra o cargo
        }
        aux_cargo = aux_cargo->prox;
    }

    if (!cargo_encontrado) {
        printf("--------------------------------------------------\n");
        printf(" EMPRESA: SISTEMA DE RH PORTFOLIO S/A             \n");
        printf("--------------------------------------------------\n");
        printf(" Matricula/ID : %d\n", func->Num_registro);
        printf(" Funcionario  : %s\n", func->Nome);
        printf(" Funcao       : %s\n", func->Funcao);
        printf(" [Alerta: Cargo '%s' nao cadastrado nas Configuracoes!]\n", func->Funcao);
        printf("==================================================\n\n");
        return;
    }

    // 2. Motor de cálculo (Matemática CLT - Divisor 220 horas)
    float valor_hora = piso_encontrado / 220.0f;
    float valor_horas_extras = (valor_hora * 1.5f) * func->Horas_extras;
    float salario_bruto = piso_encontrado + valor_horas_extras;

    // Simulação de descontos (Ex: INSS aproximado de 11%)
    float inss = salario_bruto * 0.11f;
    float salario_liquido = salario_bruto - inss;

    // 3. Layout visual da Holerite
    printf("--------------------------------------------------\n");
    printf(" EMPRESA: SISTEMA DE RH PORTFOLIO S/A             \n");
    printf("--------------------------------------------------\n");
    printf(" Matricula/ID : %d\n", func->Num_registro);
    printf(" Funcionario  : %s\n", func->Nome);
    printf(" Funcao       : %s\n", func->Funcao);
    printf(" Contatos     : %s | %s\n", func->Celular, func->E_mail);
    printf(" Tempo de Casa: %d meses\n", func->Tempo_casa);
    printf("--------------------------------------------------\n");
    printf(" DEMONSTRATIVO DE PROVENTOS E DESCONTOS           \n");
    printf("--------------------------------------------------\n");
    printf(" [+] Salario Base (Piso): R$ %.2f\n", piso_encontrado);
    printf(" [+] Horas Extras (%.1fh): R$ %.2f\n", func->Horas_extras, valor_horas_extras);
    printf(" [-] INSS (Aprox. 11%):  R$ %.2f\n", inss);
    printf("--------------------------------------------------\n");
    printf(" SALARIO LIQUIDO        : R$ %.2f\n", salario_liquido);
    printf("==================================================\n\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    int c; // Variável auxiliar para limpar o buffer
    int contador_id = 1; // Controla a geração sequencial e perpétua dos IDs

    Funcionario *prim = NULL; // Ponteiro âncora para funcionários
    Cargo *prim_cargo = NULL; // Ponteiro âncora para cargos

    do {
        printf("============================================\n");
        printf("          SISTEMA DE FUNCIONARIOS           \n");
        printf("============================================\n\n");

        printf("[1] - Registro de funcionarios\n");
        printf("[2] - Consulta e Gestao de registros\n");
        printf("[3] - Folha de pagamento\n");
        printf("[4] - Configuracoes do Sistema\n");
        printf("[5] - Encerrar programa\n\n");

        printf("Escolha uma opcao:\n\n");
        
        // Blindagem do menu principal contra letras
        if (scanf("%d", &opcao) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; // Força a cair na validação de opção inválida
        } else {
            while ((c = getchar()) != '\n' && c != EOF);
        }
        printf("\n");

        if(opcao < 1 || opcao > 5) {
            printf("Escolha uma opcao valida\n\n");
        }

        // OPÇÃO 1: Cadastro dinâmico
        if(opcao == 1) {
            int continuar_cadastro;

            do {
                char nome_temp[50];
                char funcao_temp[50];
                char celular_temp[25];
                char e_mail_temp[50];

                printf("============================================\n");
                printf("          REGISTRO DE FUNCIONARIOS          \n");
                printf("============================================\n\n");

                printf("Digite seu nome:\n");
                scanf(" %49[^\n]", nome_temp);
                printf("\n");

                printf("Digite sua funcao:\n");
                scanf(" %49[^\n]", funcao_temp);
                printf("\n");

                printf("Digite seu numero de celular:\n");
                scanf(" %24[^\n]", celular_temp);
                printf("\n");

                printf("Digite seu E-mail:\n");
                scanf(" %49[^\n]", e_mail_temp);
                printf("\n");

                inserirIni(&prim, nome_temp, funcao_temp, celular_temp, e_mail_temp, contador_id);

                contador_id++; // O ID sempre avança, garantindo coerência diária

                printf("Deseja registrar outro funcionario?\n\n");
                printf("[1] - Sim\n");
                printf("[2] - Voltar ao Menu Principal\n\n");

                // Blindagem da sub-opção de continuar
                if (scanf("%d", &continuar_cadastro) != 1) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    continuar_cadastro = -1;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                printf("\n");
                
            } while(continuar_cadastro == 1);
        }

        // OPÇÃO 2: Consulta e Gestão de Registros (CRUD Completo)
        if(opcao == 2) {
            int sub_opcao; 

            do {
                printf("=========================================\n");
                printf("      CONSULTA E GESTAO DE REGISTROS     \n");
                printf("=========================================\n\n");

                printf("[1] - Buscar por registro unico (ID)\n");
                printf("[2] - Ver todos os registros\n");
                printf("[3] - Atualizar um registro\n");
                printf("[4] - Remover um registro\n");
                printf("[0] - Voltar ao Menu Principal\n\n");

                printf("Escolha uma opcao:\n\n");
                
                // Blindagem contra letras no sub-menu
                if (scanf("%d", &sub_opcao) != 1) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    sub_opcao = -1;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                printf("\n");

                // Validação de segurança para o sub-menu (incluindo o 0 para voltar)
                if (sub_opcao == 0) {
                    printf("Retornando ao Menu Principal...\n\n");
                    break;
                } else if(sub_opcao < 1 || sub_opcao > 4) {
                    printf("Escolha uma opcao valida\n\n");
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

                                printf("=== Funcionario Encontrado ===\n\n");
                                printf("Numero de registro: %d\n", aux->Num_registro);
                                printf("Funcionario: %s\n", aux->Nome);
                                printf("Funcao: %s\n", aux->Funcao);
                                printf("Contatos: %s, %s\n\n", aux->Celular, aux->E_mail);

                                break; 
                            }
                            aux = aux->prox;
                        }

                        if(encontrado == 0) {
                            printf("Erro: Nenhum funcionario encontrado com a ID %d.\n\n", buscar_id);
                        }

                        printf("Pressione [Enter] para continuar...");
                        getchar();
                        printf("\n\n");
                    }
                    // Sub-opção 2: Ver todos os registros
                    else if(sub_opcao == 2) {
                        if(prim == NULL) {
                            printf("Nenhum funcionario cadastrado!\n\n");
                        } else {
                            Funcionario *aux = prim;

                            while(aux != NULL) {
                                printf("NNumero de registro: %d\n", aux->Num_registro);
                                printf("Funcionario: %s\n", aux->Nome);
                                printf("Funcao: %s\n", aux->Funcao);    
                                printf("Contatos: %s, %s\n\n", aux->Celular, aux->E_mail);

                                aux = aux->prox;
                            }
                        }

                        printf("Pressione [Enter] para continuar...");
                        getchar();
                        printf("\n\n");
                    }
                    // Sub-opção 3: Atualizar um registro
                    else if(sub_opcao == 3) {
                        if(prim == NULL) {
                            printf("Erro: Nenhum funcionario cadastrado para atualizar!\n\n");
                            printf("Pressione [Enter] para continuar...");
                            getchar();
                            printf("\n\n");
                        } else {
                            int continuar_atualizar;
                            do {
                                int buscar_id;
                                int encontrado = 0;

                                printf("=========================================\n");
                                printf("           ATUALIZAR REGISTRO            \n");
                                printf("=========================================\n\n");

                                printf("Digite a ID do funcionario que deseja atualizar:\n");
                                scanf("%d", &buscar_id);
                                while((c = getchar()) != '\n' && c != EOF);
                                printf("\n");

                                Funcionario *aux = prim;
                                while(aux != NULL) {
                                    if(aux->Num_registro == buscar_id) {
                                        encontrado = 1;

                                        printf("=== Funcionario Encontrado ===\n");
                                        printf("Nome atual: %s\n", aux->Nome);
                                        printf("Funcao atual: %s\n\n", aux->Funcao);

                                        printf("Digite o novo nome:\n");
                                        scanf(" %49[^\n]", aux->Nome);
                                        printf("\n");

                                        printf("Digite a nova funcao:\n");
                                        scanf(" %49[^\n]", aux->Funcao);
                                        printf("\n");

                                        printf("Digite o novo numero de celular:\n");
                                        scanf(" %24[^\n]", aux->Celular);
                                        printf("\n");

                                        printf("Digite o novo E-mail:\n");
                                        scanf(" %49[^\n]", aux->E_mail);
                                        printf("\n");

                                        printf("=== Dados atualizados com sucesso! ===\n\n");
                                        break;
                                    }
                                    aux = aux->prox;
                                }

                                if(encontrado == 0) {
                                    printf("Erro: Nenhum funcionario encontrado com a ID %d.\n\n", buscar_id);
                                }

                                printf("Deseja atualizar outro registro?\n\n");
                                printf("[1] - Sim\n");
                                printf("[2] - Voltar ao Menu de Gestao\n\n");

                                if (scanf("%d", &continuar_atualizar) != 1) {
                                    while ((c = getchar()) != '\n' && c != EOF);
                                    continuar_atualizar = -1;
                                } else {
                                    while ((c = getchar()) != '\n' && c != EOF);
                                }
                                printf("\n");

                            } while(continuar_atualizar == 1);
                        }
                    }
                    // Sub-opção 4: Remover um registro
                    else if(sub_opcao == 4) {
                        if(prim == NULL) {
                            printf("Erro: Nenhum funcionario cadastrado para remover!\n\n");
                            printf("Pressione [Enter] para continuar...");
                            getchar();
                            printf("\n\n");
                        } else {
                            int continuar_remover;
                            do {
                                int buscar_id;

                                printf("=========================================\n");
                                printf("            REMOVER REGISTRO             \n");
                                printf("=========================================\n\n");

                                printf("Digite a ID do funcionario que deseja remover:\n");
                                scanf("%d", &buscar_id);
                                while((c = getchar()) != '\n' && c != EOF);
                                printf("\n");

                                // Chama a função de remoção segura com free()
                                removerFuncionario(&prim, buscar_id);

                                printf("Deseja remover outro registro?\n\n");
                                printf("[1] - Sim\n");
                                printf("[2] - Voltar ao Menu de Gestao\n\n");

                                if (scanf("%d", &continuar_remover) != 1) {
                                    while ((c = getchar()) != '\n' && c != EOF);
                                    continuar_remover = -1;
                                } else {
                                    while ((c = getchar()) != '\n' && c != EOF);
                                }
                                printf("\n");

                            } while(continuar_remover == 1);
                        }
                    }
                }
            } while (sub_opcao != 0);
        }

        // Opção 3: Folha de pagamento
        if(opcao == 3) {
            int sub_opcao;

            do {
                printf("\n==================================================\n");
                printf("                FOLHA DE PAGAMENTO                \n");
                printf("==================================================\n\n");

                printf("  [1] Consultar Holerite Individual (Por ID)\n");
                printf("  [2] Relatorio Geral da Folha de Pagamento (RH)\n");
                printf("  [3] Consultar Multiplos IDs (RH)\n");
                printf("  [0] Voltar ao Menu Principal\n\n");

                if (scanf("%d", &sub_opcao) != 1) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    sub_opcao = -1;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                }

                switch (sub_opcao) {
                    case 1: {
                        printf("\n==================================================\n");
                        printf("         CONSULTA DE HOLERITE INDIVIDUAL          \n");
                        printf("==================================================\n\n");

                        if (prim == NULL) {
                            printf("Erro: Nenhum funcionario cadastrado para consulta!\n\n");
                            printf("Pressione [Enter] para retornar...\n");
                            getchar();
                            break;
                        }

                        int id_busca;
                        printf("Por favor, insira a ID do funcionario:\n");
                        if (scanf("%d", &id_busca) != 1) {
                            while ((c = getchar()) != '\n' && c != EOF);
                            printf("\nID invalida!\n\n");
                            printf("Pressione [Enter] para retornar...\n");
                            getchar();
                            break;
                        }
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("\n");

                        // 1. Busca do Funcionário por ID
                        Funcionario *aux_func = prim;
                        int encontrado = 0;
                        while (aux_func != NULL) {
                            if (aux_func->Num_registro == id_busca) {
                                encontrado = 1;
                                break;
                            }
                            aux_func = aux_func->prox;
                        }

                        // 2. Validação se o funcionário foi encontrado
                        if (encontrado == 0) {
                            printf("Erro: Nenhum funcionario encontrado com a ID %d.\n\n", id_busca);
                            printf("Pressione [Enter] para retornar...\n");
                            getchar();
                            break;
                        }

                        // 3. Chamada limpa da nossa função modularizada de cálculo e exibição do Holerite
                        gerarHolerite(aux_func, prim_cargo);

                        printf("Pressione [Enter] para retornar ao Menu de Folha de Pagamento...\n");
                        getchar();
                        break;
                    }

                    case 2: {
                        // RELATÓRIO GERAL DA FOLHA (Reaproveitando a função DRY)
                        printf("\n==================================================\n");
                        printf("         RELATORIO GERAL DA FOLHA DE PAGAMENTO    \n");
                        printf("==================================================\n\n");

                        if (prim == NULL) {
                            printf("Erro: Nenhum funcionario cadastrado no sistema!\n\n");
                            printf("Pressione [Enter] para retornar...");
                            getchar();
                            break;
                        }    

                        Funcionario *aux = prim;
                        int total_funcionarios = 0;

                        // Varre toda a lista encadeada gerando o holerite de cada um
                        while (aux != NULL) {
                            gerarHolerite(aux, prim_cargo);
                            total_funcionarios++;
                            aux = aux->prox;

                            printf("--------------------------------------------------\n");
                        }

                        printf("Relatorio concluido. Total de holerites gerados: %d\n\n", total_funcionarios);
                        printf("Pressione [Enter] para retornar ao Menu de Folha...");
                        getchar();
                        break;
                    }    
                    
                    case 3: {
                        // CONSULTA DE MÚLTIPLOS IDs (Com limite e tratamento parcial)
                        printf("\n==================================================\n");
                        printf("         CONSULTA DE MULTIPLOS IDs (LOTE)         \n");
                        printf("==================================================\n\n");

                        if (prim == NULL) {
                            printf("Erro: Nenhum funcionario cadastrado no sistema!\n\n");
                            printf("Pressione [Enter] para retornar...");
                            getchar();
                            break;
                        }
                        
                        int qtd;
                        printf("Quantos funcionarios deseja consultar em lote? (Maximo 10):\n");
                        if (scanf("%d", &qtd) != 1 || qtd < 1 || qtd > 10) {
                            while ((c = getchar()) != '\n' && c != EOF);
                            printf("\nQuantidade invalida! Escolha um numero entre 1 e 10.\n\n");
                            printf("Pressione [Enter] para retornar...");
                            getchar();
                            break;
                        } 
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("\n");

                        int ids_busca[10];
                        printf("Digite os %d IDs separados por espaco ou enter:\n", qtd);
                        for (int i = 0; i < qtd; i++) {
                            printf("ID [%d]: ", i + 1);
                            scanf("%d", &ids_busca[i]);
                        }
                        while ((c = getchar()) != '\n' && c != EOF);
                        printf("\n\n==================================================\n");
                        printf("             PROCESSANDO RESULTADOS DO LOTE       \n");
                        printf("==================================================\n\n");

                        // Varre o vetor de IDs solicitadas e busca na lista encadeada
                        for (int i = 0; i < qtd; i++) {
                            Funcionario *aux_func = prim;
                            int encontrado = 0;

                            while (aux_func != NULL) {
                                if (aux_func->Num_registro == ids_busca[i]) {
                                    encontrado = 1;
                                    break;
                                }
                                aux_func = aux_func->prox;
                            }

                            if (encontrado) {
                                // Reaproveita o motor DRY
                                gerarHolerite(aux_func, prim_cargo);
                            } else {
                                printf("[Alerta] ID %d nao encontrada no sistema.\n", ids_busca[i]);
                                printf("--------------------------------------------------\n\n");
                            }
                        }

                        printf("Processamento em lote finalizado.\n");
                        printf("Pressione [Enter] para retornar ao Menu de Folha...");
                        getchar();
                        break;     
                    }
                            
                    case 0:
                        printf("\nRetornando ao Menu Principal...\n");
                        break;

                    default:
                        printf("\nOpcao invalida! Tente novamente.\n");
                        break;   
                }

            } while (sub_opcao != 0);
        }

        // Opção 4: Configurações do Sistema (CRUD de Cargos)
        if(opcao == 4) {
            int sub_opcao_cargo;

            do {
                printf("=========================================\n");
                printf("         CONFIGURACOES DO SISTEMA        \n");
                printf("=========================================\n\n");

                printf("[1] - Cadastrar novo cargo\n");
                printf("[2] - Ver todos os cargos\n");
                printf("[3] - Atualizar piso de um cargo\n");
                printf("[4] - Remover um cargo\n");
                printf("[0] - Voltar ao Menu Principal\n\n");

                printf("Escolha uma opcao:\n\n");
                
                if (scanf("%d", &sub_opcao_cargo) != 1) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    sub_opcao_cargo = -1;
                } else {
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                printf("\n");

                if (sub_opcao_cargo == 0) {
                    printf("Retornando ao Menu Principal...\n\n");
                    break;
                } else if(sub_opcao_cargo < 1 || sub_opcao_cargo > 4) {
                    printf("Escolha uma opcao valida\n\n");
                } else {
                    // Sub-opção 1: Cadastrar novo cargo
                    if(sub_opcao_cargo == 1) {
                        char nome_cargo_temp[50];
                        float piso_cargo_temp;

                        printf("=========================================\n");
                        printf("           CADASTRAR NOVO CARGO          \n");
                        printf("=========================================\n\n");

                        printf("Digite o nome do cargo:\n");
                        scanf(" %49[^\n]", nome_cargo_temp);
                        printf("\n");

                        printf("Digite o piso salarial do cargo:\n");
                        scanf(" %f", &piso_cargo_temp);
                        while((c = getchar()) != '\n' && c != EOF);
                        printf("\n");

                        inserirCargo(&prim_cargo, nome_cargo_temp, piso_cargo_temp);

                        printf("Pressione [Enter] para continuar...");
                        getchar();
                        printf("\n\n");
                    }
                    // Sub-opção 2: Ver todos os cargos
                    else if(sub_opcao_cargo == 2) {
                        if(prim_cargo == NULL) {
                            printf("Nenhum cargo cadastrado!\n\n");
                        } else {
                            Cargo *aux = prim_cargo;

                            while(aux != NULL) {
                                printf("Cargo: %s\n", aux->Nome_cargo);
                                printf("Piso salarial: R$ %.2f\n\n", aux->Piso_salarial);

                                aux = aux->prox;
                            }
                        }

                        printf("Pressione [Enter] para continuar...");
                        getchar();
                        printf("\n\n");
                    }
                    // Sub-opção 3: Atualizar piso de um cargo
                    else if(sub_opcao_cargo == 3) {
                        if(prim_cargo == NULL) {
                            printf("Erro: Nenhum cargo cadastrado para atualizar!\n\n");
                            printf("Pressione [Enter] para continuar...");
                            getchar();
                            printf("\n\n");
                        } else {
                            char nome_busca[50];
                            int encontrado = 0;

                            printf("=========================================\n");
                            printf("          ATUALIZAR PISO DE CARGO        \n");
                            printf("=========================================\n\n");

                            printf("Digite o nome do cargo que deseja atualizar:\n");
                            scanf(" %49[^\n]", nome_busca);
                            while((c = getchar()) != '\n' && c != EOF);
                            printf("\n");

                            Cargo *aux = prim_cargo;
                            while(aux != NULL) {
                                if(strcmp(aux->Nome_cargo, nome_busca) == 0) {
                                    encontrado = 1;

                                    printf("Cargo encontrado: %s\n", aux->Nome_cargo);
                                    printf("Piso atual: R$ %.2f\n\n", aux->Piso_salarial);

                                    printf("Digite o novo piso salarial:\n");
                                    scanf(" %f", &aux->Piso_salarial);
                                    while((c = getchar()) != '\n' && c != EOF);
                                    printf("\n");

                                    printf("=== Piso salarial atualizado com sucesso! ===\n\n");
                                    break;
                                }
                                aux = aux->prox;
                            }

                            if(encontrado == 0) {
                                printf("Erro: Nenhum cargo encontrado com o nome '%s'.\n\n", nome_busca);
                            }

                            printf("Pressione [Enter] para continuar...");
                            getchar();
                            printf("\n\n");
                        }
                    }
                    // Sub-opção 4: Remover um cargo
                    else if(sub_opcao_cargo == 4) {
                        if(prim_cargo == NULL) {
                            printf("Erro: Nenhum cargo cadastrado para remover!\n\n");
                            printf("Pressione [Enter] para continuar...");
                            getchar();
                            printf("\n\n");
                        } else {
                            char nome_busca[50];

                            printf("=========================================\n");
                            printf("              REMOVER CARGO              \n");
                            printf("=========================================\n\n");

                            printf("Digite o nome do cargo que deseja remover:\n");
                            scanf(" %49[^\n]", nome_busca);
                            while((c = getchar()) != '\n' && c != EOF);
                            printf("\n");

                            removerCargo(&prim_cargo, nome_busca);

                            printf("Pressione [Enter] para continuar...");
                            getchar();
                            printf("\n\n");
                        }
                    }
                }
            } while(sub_opcao_cargo != 0);
        }

        // Opção 5: Encerrar programa
        if(opcao == 5) {
            printf("Encerrando o sistema de RH. Ate logo!\n\n");
            break;
        }

    } while(1);

    return 0;
}