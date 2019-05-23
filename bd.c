//gcc bd.c -lmysqlclient -o bd

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <stdio_ext.h>
#include <string.h>

#define TAM 100

int menu();
int inserirContato(char *nome); 
void inserirTelefone(int codigo, char *telefone);
void inserirEmail(int codigo, char *email);
void atualizarContato(int codigo, char *nome);
void atualizarTelefone(int codigo, char *telefone, char *novoTelefone);
void atualizarEmail(int codigo, char *email, char *novoEmail);
void removerContato(int codigo);
void removerTelefone(int codigo, char *telefone);
void removerEmail(int codigo, char *email);
MYSQL_RES *buscarContatoPorCodigo(int codigo);
MYSQL_RES *buscarContatoPorNome(char *nome);
MYSQL_RES *buscarContatoPorEmail(char *email);
MYSQL_RES *buscarContatoPorTelefone(char *telefone);
MYSQL_RES *buscarTelefonesPorCodigo(int codigo);
MYSQL_RES *buscarEmailsPorCodigo(int codigo);

MYSQL conexao;

int main()
{
    MYSQL_RES *resp, *resp2;
   	MYSQL_ROW linhas, linhas2;
    MYSQL_FIELD *campos;
    char query[300], nome[TAM], telefone[TAM], telefoneNovo[TAM], email[TAM], emailNovo[TAM];
    int codigo, continuar, continuar2, opcao, i, j, atualizar, remover, opcaoRemover, operacao, buscarNovamente, conta;

    mysql_init(&conexao);
    if ( mysql_real_connect(&conexao, "localhost", "root", "", "agenda", 3006, NULL, 0) ) {

        do {
            continuar = 0;

            opcao = menu();

            switch (opcao) {

                //Inserir
                case 1:
                    
                    printf("\n-> Informe o nome do Contato: ");
                    __fpurge(stdin);
                    fgets(nome, TAM, stdin);

                    codigo = inserirContato(nome);

                    do {
                        printf("\n-> Informe o Email: ");
                        __fpurge(stdin);
                        fgets(email, TAM, stdin);

                        inserirEmail(codigo, email);

                        printf("\n\n-> Deseja inserir um novo email? (1) Sim (2) Não\n");
                        scanf("%i", &continuar);

                    } while (continuar == 1);

                    do {
                        printf("\n-> Informe o Telefone: ");
                        __fpurge(stdin);
                        fgets(telefone, TAM, stdin);

                        inserirTelefone(codigo, telefone);

                        printf("\n\n-> Deseja inserir um novo telefone? (1) Sim (2) Não\n");
                        scanf("%i", &continuar);

                    } while (continuar == 1);

                break;

                //Atualizar
                case 2:
                    do {
                        printf("\n-> Informe o código do contato: ");
                        scanf("%i", &codigo);

                        resp = buscarContatoPorCodigo(codigo);

                        if (resp != NULL) { 
                            while ((linhas=mysql_fetch_row(resp)) != NULL) {
                                for (i=0; i<mysql_num_fields(resp);i++) {
                                    printf("\nNome atual: %s\n",linhas[i]);

                                    printf("-> Deseja atualizar o nome? (1) Sim (2) Não\n");
                                    scanf("%i", &atualizar);

                                    if (atualizar == 1) {
                                        printf("\n-> Informe o novo nome para o Contato: ");
                                        __fpurge(stdin);
                                        fgets(nome, TAM, stdin);
                                        
                                        atualizarContato(codigo, nome);
                                    }
                                    

                                    //Telefones

                                    printf("\nTelefones Cadastrados\n");
                                    resp2 = buscarTelefonesPorCodigo(codigo);

                                    while ((linhas2=mysql_fetch_row(resp2)) != NULL) {
                                        for (i=0; i<mysql_num_fields(resp2);i++) {
                                            printf("\n%s", linhas2[i]); 
                                        }
                                    }
                                    mysql_free_result(resp2);

                                    do {
                                        printf("\n-> Deseja atualizar um telefone? (1) Sim (2) Não\n");
                                        scanf("%i", &atualizar);

                                        if (atualizar == 1) {
                                            printf("\n-> Informe o numero que deseja atualizar: ");
                                            __fpurge(stdin);
                                            fgets(telefone, TAM, stdin);

                                            printf("\n-> Informe o novo numero: ");
                                            __fpurge(stdin);
                                            fgets(telefoneNovo, TAM, stdin);
                                            
                                            atualizarTelefone(codigo, telefone, telefoneNovo);
                                        }
                                    }
                                    while (atualizar == 1);

                                    do {
                                        printf("\n\n-> Deseja inserir um novo telefone? (1) Sim (2) Não\n");
                                        scanf("%i", &continuar2);

                                        if (continuar2 == 1) {
                                            printf("\n-> Informe o Telefone: ");
                                            __fpurge(stdin);
                                            fgets(telefone, TAM, stdin);

                                            inserirTelefone(codigo, telefone);
                                        }
                                    } while (continuar2 == 1);

                                    //Emails
                                    printf("\nEmails Cadastrados\n");
                                    resp2 = buscarEmailsPorCodigo(codigo);

                                    while ((linhas2=mysql_fetch_row(resp2)) != NULL) {
                                        for (i=0; i<mysql_num_fields(resp2);i++) {
                                            printf("\n%s", linhas2[i]); 
                                        }
                                    }
                                    mysql_free_result(resp2);

                                    do {
                                        printf("\n-> Deseja atualizar um email? (1) Sim (2) Não\n");
                                        scanf("%i", &atualizar);

                                        if (atualizar == 1) {
                                            printf("\n-> Informe o email que deseja atualizar: ");
                                            __fpurge(stdin);
                                            fgets(email, TAM, stdin);

                                            printf("\n-> Informe o novo email: ");
                                            __fpurge(stdin);
                                            fgets(emailNovo, TAM, stdin);
                                            
                                            atualizarEmail(codigo, email, emailNovo);
                                        }
                                    }
                                    while (atualizar == 1);

                                    do {
                                        printf("\n\n-> Deseja inserir um novo email? (1) Sim (2) Não\n");
                                        scanf("%i", &continuar2);

                                        if (continuar2 == 1) {
                                            printf("\n-> Informe o Email: ");
                                            __fpurge(stdin);
                                            fgets(email, TAM, stdin);

                                            inserirEmail(codigo, email);
                                        }
                                    } while (continuar2 == 1);
                                }
                                
                                printf("\n");
                            }
                            
                            mysql_free_result(resp);
                        }
                            
                        printf("\n-> Deseja atualizar um novo contato? (1) Sim (2) Não\n");
                        scanf("%i", &continuar);

                    } while (continuar == 1);
                break;

                //Remover
                case 3:
                    do {

                        printf("\n1. Remover Contato");
                        printf("\n2. Remover Apenas Telefone");
                        printf("\n3. Remover Apenas Email");
                        printf("\n4. Voltar ao menu principal");

                        printf("\n\n-> Digite a operação: ");
                        scanf("%i", &opcaoRemover);

                        if (opcaoRemover != 4) {

                            printf("\n-> Informe o código do contato: ");
                            scanf("%i", &codigo);

                            resp = buscarContatoPorCodigo(codigo);

                            if (resp != NULL) { 

                                switch (opcaoRemover) {
                                    
                                    case 1:
                                        removerContato(codigo);
                                    break;

                                    case 2:
                                        resp = buscarTelefonesPorCodigo(codigo);

                                        while ((linhas=mysql_fetch_row(resp)) != NULL) {
                                            for (i=0; i<mysql_num_fields(resp);i++) {
                                                printf("\n%s", linhas[i]); 
                                            }
                                        }
                                        mysql_free_result(resp);

                                        printf("\n-> Informe o telefone que deseja remover: \n");
                                        __fpurge(stdin);
                                        fgets(telefone, TAM, stdin);

                                        removerTelefone(codigo, telefone);
                                    break;

                                    case 3:
                                        resp = buscarEmailsPorCodigo(codigo);

                                        while ((linhas=mysql_fetch_row(resp)) != NULL) {
                                            for (i=0; i<mysql_num_fields(resp);i++) {
                                                printf("\n%s", linhas[i]); 
                                            }
                                        }
                                        mysql_free_result(resp);

                                        printf("\n-> Informe o email que deseja remover: \n");
                                        __fpurge(stdin);
                                        fgets(email, TAM, stdin);

                                        removerEmail(codigo, email);
                                    break;
                                }
                            }
                        }
                                                       
                    } while (opcaoRemover != 4);

                break;

                //Buscar
                case 4:

                    do {
                    
                    printf("\n1. Por nome");
                    printf("\n2. Por telefone");
                    printf("\n3. Por email");
                    printf("\n4. Voltar");

                    printf("\n\n-> Digite a operacao: ");
                    scanf("%i", &operacao);

                    switch (operacao) {

                            case 1:
                                do {
                                    printf("\nInforme o nome: ");
                                    __fpurge(stdin);
                                    fgets(nome, TAM, stdin);

                                    resp = buscarContatoPorNome(nome);
                                    if (resp) 
                                    {
                                        campos = mysql_fetch_fields(resp);
                                        for (conta=0;conta<mysql_num_fields(resp);conta++) 
                                        {
                                            printf("%s",(campos[conta]).name);
                                            if (mysql_num_fields(resp)>1)
                                                printf("\t");
                                        }
                                        printf("\n");  
                                        while ((linhas=mysql_fetch_row(resp)) != NULL)
                                        {
                                            for (conta=0;conta<mysql_num_fields(resp);conta++)
                                                printf("%s\t",linhas[conta]);
                                            printf("\n");
                                        }
                                    }
                                    mysql_free_result(resp);

                                    printf("\n\nDeseja buscar novamente? (1) Sim (2) Não");
                                    scanf("%i", &buscarNovamente);

                                } while(buscarNovamente == 1);
                            break;

                            case 2:
                                do {
                                    printf("\nInforme o telefone: ");
                                    __fpurge(stdin);
                                    fgets(telefone, TAM, stdin);
                                
                                    resp = buscarContatoPorTelefone(telefone);
                                    if (resp) 
                                    {
                                        campos = mysql_fetch_fields(resp);
                                        for (conta=0;conta<mysql_num_fields(resp);conta++) 
                                        {
                                            printf("%s",(campos[conta]).name);
                                            if (mysql_num_fields(resp)>1)
                                                printf("\t");
                                        }
                                        printf("\n");  
                                        while ((linhas=mysql_fetch_row(resp)) != NULL)
                                        {
                                            for (conta=0;conta<mysql_num_fields(resp);conta++)
                                                printf("%s\t",linhas[conta]);
                                            printf("\n");
                                        }
                                    }
                                    mysql_free_result(resp);

                                    printf("\n\nDeseja buscar novamente? (1) Sim (2) Não");
                                    scanf("%i", &buscarNovamente);

                                } while(buscarNovamente == 1);
                            break;

                            case 3:
                                do {
                                    printf("\nInforme o email: ");
                                    __fpurge(stdin);
                                    fgets(email, TAM, stdin);

                                    resp = buscarContatoPorEmail(email);
                                    if (resp) 
                                    {
                                        campos = mysql_fetch_fields(resp);
                                        for (conta=0;conta<mysql_num_fields(resp);conta++) 
                                        {
                                            printf("%s",(campos[conta]).name);
                                            if (mysql_num_fields(resp)>1)
                                                printf("\t");
                                        }
                                        printf("\n");  
                                        while ((linhas=mysql_fetch_row(resp)) != NULL)
                                        {
                                            for (conta=0;conta<mysql_num_fields(resp);conta++)
                                                printf("%s\t",linhas[conta]);
                                            printf("\n");
                                        }
                                    }
                                    mysql_free_result(resp);

                                    printf("\n\nDeseja buscar novamente? (1) Sim (2) Não");
                                    scanf("%i", &buscarNovamente);

                                } while(buscarNovamente == 1);

                            break;
                        }

                    } while (operacao != 4);

                break;
            }

        } while (opcao != 5);
    }
    else {
        printf("Falha de conexao\n");
        printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
    }

    return 0;
}

int menu() 
{
    int opcao;

    system("clear");
    printf("\n1. Cadastrar");
    printf("\n2. Atualizar");
    printf("\n3. Remover");
    printf("\n4. Buscar");
    printf("\n5. Sair");

    printf("\n\n-> Digite a opção: ");
    scanf("%i", &opcao);

    return opcao;
}

int inserirContato(char *nome)
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "insert into agenda(nome) values('%s');", nome);

  	res=mysql_query(&conexao, query);

    if (!res) {
        return mysql_insert_id(&conexao);
    }
    else printf("Erro na inserção %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
} 

void inserirTelefone(int codigo, char *telefone)
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "insert into telefone(codigo, telefone) values(%i, '%s');", codigo, telefone);

  	res=mysql_query(&conexao, query);

    if (!res) {
    }
    else printf("Erro na inserção %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
}

void inserirEmail(int codigo, char *email)
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "insert into email(codigo, email) values(%i, '%s');", codigo, email);

  	res=mysql_query(&conexao, query);

    if (!res) {
    }
    else printf("Erro na inserção %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
}

MYSQL_RES *buscarContatoPorCodigo(int codigo) 
{
    char query[300]; 
    int n;
    MYSQL_RES *resp;

    n = sprintf(query, "select nome from agenda where codigo = %i;", codigo);

	if (mysql_query(&conexao, query)){
        printf("Erro: %s\n",mysql_error(&conexao));
        mysql_free_result(resp);
        return NULL;
 	} 		
    
    resp = mysql_store_result(&conexao);
    return resp;
}


MYSQL_RES *buscarContatoPorNome(char *nome) 
{
    char query[300]; 
    int n;
    MYSQL_RES *resp;

    n = sprintf(query, "select * from agenda where agenda.nome like '%%%s%%';", nome);

	if (mysql_query(&conexao, query)){
        printf("Erro: %s\n",mysql_error(&conexao));
        mysql_free_result(resp);
        return NULL;
 	} 		
    
    resp = mysql_store_result(&conexao);
    return resp;
}



MYSQL_RES *buscarContatoPorEmail(char *email) 
{
    char query[300]; 
    int n;
    MYSQL_RES *resp;

    n = sprintf(query, "select * from email, agenda where email.email like '%%%s%%' and email.codigo = agenda.codigo;", email);

	if (mysql_query(&conexao, query)){
        printf("Erro: %s\n",mysql_error(&conexao));
        mysql_free_result(resp);
        return NULL;
 	} 		
    
    resp = mysql_store_result(&conexao);
    return resp;
}

MYSQL_RES *buscarContatoPorTelefone(char *telefone)
{
    char query[300]; 
    int n;
    MYSQL_RES *resp;

    n = sprintf(query, "select * from agenda, telefone where telefone.telefone like '%%%s%%' and telefone.codigo = agenda.codigo;", telefone);

	if (mysql_query(&conexao, query)){
        printf("Erro: %s\n",mysql_error(&conexao));
        mysql_free_result(resp);
        return NULL;
 	} 		
    
    resp = mysql_store_result(&conexao);
    return resp;
}

MYSQL_RES *buscarTelefonesPorCodigo(int codigo) 
{
    char query[300]; 
    int n;
    MYSQL_RES *resp;

    n = sprintf(query, "select telefone from telefone where codigo = %i;", codigo);

	if (mysql_query(&conexao, query)){
        printf("Erro: %s\n",mysql_error(&conexao));
        mysql_free_result(resp);
        return NULL;
 	} 		
    
    resp = mysql_store_result(&conexao);
    return resp; 
}

MYSQL_RES *buscarEmailsPorCodigo(int codigo) 
{
    char query[300]; 
    int n;
    MYSQL_RES *resp;

    n = sprintf(query, "select email from email where codigo = %i;", codigo);

	if (mysql_query(&conexao, query)){
        printf("Erro: %s\n",mysql_error(&conexao));
        mysql_free_result(resp);
        return NULL;
 	} 		
    
    resp = mysql_store_result(&conexao);
    return resp; 
}

void removerContato(int codigo)
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "delete from telefone where codigo = %i;", codigo);
  	res=mysql_query(&conexao, query);

    n = sprintf(query, "delete from email where codigo = %i;", codigo);
  	res=mysql_query(&conexao, query);

    n = sprintf(query, "delete from agenda where codigo = %i;", codigo);
  	res=mysql_query(&conexao, query);

    if (!res) {
    }
    else printf("Erro na remoção %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
}

void removerTelefone(int codigo, char *telefone)
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "delete from telefone where telefone = '%s' and codigo = %i;", telefone, codigo);

  	res=mysql_query(&conexao, query);

    if (!res) {
    }
    else printf("Erro na remoção %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
}

void removerEmail(int codigo, char *email)
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "delete from email where email = '%s' and codigo = %i;", email, codigo);

  	res=mysql_query(&conexao, query);

    if (!res) {
    }
    else printf("Erro na remoção %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
}


void atualizarContato(int codigo, char *nome) 
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "update agenda set nome = '%s' where codigo = %i;", nome, codigo);

  	res=mysql_query(&conexao, query);

    if (!res) {
    }
    else printf("Erro na atualização %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
}

void atualizarTelefone(int codigo, char *telefone, char *novoTelefone) 
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "update telefone set telefone = '%s' where codigo = %i and telefone = '%s';", novoTelefone, codigo, telefone);

  	res=mysql_query(&conexao, query);

    if (!res) {
    }
    else printf("Erro na atualização %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
}

void atualizarEmail(int codigo, char *email, char *novoEmail)
{
    char query[300]; 
    int res, n;

    n = sprintf(query, "update email set email = '%s' where codigo = %i and email = '%s';", novoEmail, codigo, email);

  	res=mysql_query(&conexao, query);

    if (!res) {
    }
    else printf("Erro na atualização %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
}