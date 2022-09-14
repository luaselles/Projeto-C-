#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

struct Fornecedores
{
	int fornecedor_prod;
	char nome_fornecedor[60], cidade_fornecedor[60];
};
struct Estoque
{
	int cod_prod, qtd_estoque, qtd_min, fornecedor_prod;
	char descricao_prod[50];
	float venda, custo;
};
struct Data
{
	int dia, mes, ano;
};
struct Compras
{
	int cod_compras, fornecedor_prod, cod_prod, qtd;
	float custo;
	Data validade;
};

void CriarArquivos(void);
void ConheceArquivo(void);
void VerificaArquivo(char nome[100]);
char Menu (void);
int BuscaFornecedor(FILE *ptr, int aux);
void LeFornecedores(char nome[100]);
int BuscaCod(FILE *ptr, int aux);
void LeEstoque(char nome[100]);
int BuscaCodCompras(FILE *ptr, int aux);
int BuscaPos(FILE *ptr, int aux);
void LeCompras(char nome[100]);
void ExcluirProdutos(char nome[100]);
void AlterarEstoque(char nome[100]);
void ConsultaProdutos(char nome[100]);
int BuscaPosFornecedores(FILE *ptr, int aux);
void RelatorioProdutos(char nome[100]);
void RelatorioFornecedores(char nome[100]);
void RelatorioCompras(char nome[100]);
void Ordenar(char nome[100]);
void Ordenar2(char nome[100]);
void RelatorioFornecedoresProdutos(char nome[100]);
void RelatorioEstoqueMin(char nome[100]);
void PesquisaNome(char nome[100]);
void PesquisaForn(char nome[100]);
void Estatisticas(char nome[100]);

char Menu (void)
{
	system("cls");
    printf("\n--- CONTROLE DE REGISTRO DE PRODUTOS ---\n\n");
    printf("[X] VERIFICAR ARQUIVO\n");
    printf("[A] REGISTRO DE FORNECEDORES\n");
    printf("[B] REGISTRO DE PRODUTOS\n");
    printf("[C] REGISTRO DE COMPRAS\n");
    printf("[D] EXCLUIR PRODUTOS\n");
    printf("[E] ALTERAR INFORMACOES DE PRODUTOS\n");
    printf("[F] CONSULTAR PRODUTOS\n");
    printf("[G] RELATORIO PRODUTOS\n");
    printf("[H] RELATORIO DE FORNECEDORES\n");
    printf("[I] RELATORIO COMPRAS\n");
    printf("[J] RELATORIO DE PRODUTOS POR FORNECEDORES\n");
    printf("[K] RELATORIO DE PRODUTOS COM ESTOQUE ABAIXO DA QUANTIDADE MINIMA\n");
    printf("[L] PESQUISA POR NOME DO PRODUTO\n");
    printf("[M] PESQUISA POR NOME DO FORNECEDOR\n");
    printf("[N] ESTATISTICAS\n");
    
    printf("[ESC] SAIR");
    return toupper(getche());
}

int BuscaFornecedor(FILE *ptr, int aux)
{
	Fornecedores tab_fornecedores1;
	rewind(ptr);
	fread(&tab_fornecedores1,sizeof(Fornecedores),1,ptr);
	
	while (!feof(ptr) && aux!=tab_fornecedores1.fornecedor_prod)
		fread(&tab_fornecedores1,sizeof(Fornecedores),1,ptr);
	
	if (!feof(ptr))
		return 1;
	else
		return 0;
}

void LeFornecedores(char nome[100])
{
	FILE *ptr = fopen(nome, "ab+");
	Fornecedores tab_fornecedores;
	
	int achou, pos;
	
	system("cls");
	
	printf ("\n--- CADASTRO DE FORNECEDORES ---\n\n");
	printf ("DIGITE O CODIGO DO FORNECEDOR (DIGITE 0 PARA SAIR): \n");
	scanf ("%d", &tab_fornecedores.fornecedor_prod);
	achou = BuscaFornecedor(ptr, tab_fornecedores.fornecedor_prod);
	while (achou == 1)
	{
		printf ("CODIGO REPETIDO, DIGITE NOVAMENTE: \n");
		scanf ("%d", &tab_fornecedores.fornecedor_prod);
		achou = BuscaFornecedor(ptr, tab_fornecedores.fornecedor_prod);
	}
	while (tab_fornecedores.fornecedor_prod > 0)
	{
		fseek (ptr, sizeof(Fornecedores), 1);
		fread (&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
		printf ("DIGITE O NOME DO FORNECEDOR: \n");
		fflush (stdin);
		gets (tab_fornecedores.nome_fornecedor);
		printf ("DIGITE A CIDADE DO FORNECEDOR: \n");
		fflush (stdin);
		gets (tab_fornecedores.cidade_fornecedor);
		fwrite (&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
		
		printf ("\n----------------------------------------------------------\n");
		
		printf ("DIGITE O CODIGO DO FORNECEDOR (DIGITE 0 PARA SAIR): \n");
		scanf ("%d", &tab_fornecedores.fornecedor_prod);
		achou = BuscaFornecedor(ptr, tab_fornecedores.fornecedor_prod);
		while (achou == 1)
		{
			printf ("CODIGO REPETIDO, DIGITE NOVAMENTE: \n");
			scanf ("%d", &tab_fornecedores.fornecedor_prod);
			achou = BuscaFornecedor(ptr, tab_fornecedores.fornecedor_prod);
		}
	}
	fclose(ptr);
}

int BuscaCod(FILE *ptr, int aux)
{
	Estoque tab_estoque1;
	rewind(ptr);
	fread(&tab_estoque1,sizeof(Estoque),1,ptr);
	
	while (!feof(ptr) && aux!=tab_estoque1.cod_prod)
		fread(&tab_estoque1,sizeof(Estoque),1,ptr);
	
	if (!feof(ptr))
		return 1;
	else
		return 0;
}

void LeEstoque(char nome[100])
{
	FILE *ptr = fopen(nome, "ab+");
	int achou1, achou2;
	Fornecedores tab_fornecedores;
	Estoque tab_estoque;
	
	system("cls");
	printf ("\n--- CADASTRO DE PRODUTOS ---\n\n");
	printf("DIGITE O CODIGO DO FORNECEDOR (DIGITE 0 PARA SAIR): \n");
	scanf ("%d", &tab_fornecedores.fornecedor_prod);
	achou1 = BuscaFornecedor(ptr, tab_fornecedores.fornecedor_prod);
	
	while (tab_fornecedores.fornecedor_prod > 0)
	{
		while (achou1 == 0 && tab_fornecedores.fornecedor_prod > 0)
		{
			printf ("FORNECEDOR NAO ENCONTRADO, DIGITE NOVAMENTE: \n");
			scanf ("%d", &tab_fornecedores.fornecedor_prod);
			achou1 = BuscaFornecedor(ptr, tab_fornecedores.fornecedor_prod);
		}
		tab_estoque.fornecedor_prod = tab_fornecedores.fornecedor_prod;
		printf ("DIGITE O CODIGO DO PRODUTO: \n");
		scanf ("%d", &tab_estoque.cod_prod);
		achou2 = BuscaCod(ptr, tab_estoque.cod_prod);
		while (achou2 == 1 || tab_estoque.cod_prod == 0)
		{
			printf ("CODIGO REPETIDO OU NULO, DIGITE OUTRA VEZ: \n");
			scanf ("%d", &tab_estoque.cod_prod);
			achou2 = BuscaCod(ptr, tab_estoque.cod_prod);
		}
		fseek (ptr, sizeof(Estoque), 1);
		fread (&tab_estoque, sizeof(Estoque), 1, ptr);
		fflush(stdin);
		printf ("DIGITE A DESCRICAO DO PRODUTO: \n");
		gets(tab_estoque.descricao_prod);
		printf ("DIGITE A QUANTIDADE EM ESTOQUE: \n");
		scanf ("%d", &tab_estoque.qtd_estoque);
		printf ("DIGITE A QUANTIDADE MINIMA: \n");
		scanf ("%d", &tab_estoque.qtd_min);
		printf ("DIGITE A VENDA: \n");
		scanf ("%f", &tab_estoque.venda);
		printf ("DIGITE O CUSTO: \n");
		scanf ("%f", &tab_estoque.custo);
		fwrite(&tab_estoque, sizeof(Estoque), 1, ptr);
		
		printf ("\n----------------------------------------------------------\n");
	
		printf("DIGITE O CODIGO DO FORNECEDOR (DIGITE 0 PARA SAIR): \n");
		scanf ("%d", &tab_fornecedores.fornecedor_prod);
		
		achou1 = BuscaFornecedor(ptr, tab_fornecedores.fornecedor_prod);
	}
	fclose(ptr);
}

int BuscaCodCompras(FILE *ptr, int aux)
{
	Compras tab_compras1;
	rewind(ptr);
	fread(&tab_compras1,sizeof(Compras),1,ptr);
	
	while (!feof(ptr) && aux!=tab_compras1.cod_compras)
		fread(&tab_compras1,sizeof(Compras),1,ptr);
	
	if (!feof(ptr))
		return 1;
	else
		return 0;
}

int BuscaPos(FILE *ptr, int aux)
{
	Estoque tab_estoque1;
	rewind(ptr);
	fread(&tab_estoque1,sizeof(Estoque),1,ptr);
	
	while (!feof(ptr) && aux!=tab_estoque1.cod_prod)
		fread(&tab_estoque1,sizeof(Estoque),1,ptr);
	
	if (!feof(ptr))
		return ftell(ptr)-sizeof(Estoque);
	else
		return -1;
}

void LeCompras(char nome[100])
{
	FILE *ptr = fopen(nome, "ab+");
	
	Compras tab_compras;
	Estoque tab_estoque;
	int cod, achou, cod2, achou2, cod3, achou3, pos, qtd, valor_soma, pos_a;
	system("cls");
	printf ("\n--- COMPRAS ---\n\n");
	printf ("DIGITE O CODIGO DA COMPRA: \n");
	scanf ("%d", &cod);
	
	achou = BuscaCodCompras(ptr, cod);
	while (achou == 1 || cod == 0)
	{
		printf ("CODIGO REPETIDO OU NULO, DIGITE NOVAMENTE: \n");
		scanf ("%d", &cod);
		achou = BuscaCodCompras(ptr, cod);
	}
	while (cod>0)
	{
		printf ("DIGITE O CODIGO DO FORNECEDOR: \n");
		scanf ("%d", &cod2);
		achou2 = BuscaFornecedor(ptr, cod2);
		while (achou2 == 0)
		{
			printf ("FORNECEDOR NAO ENCONTRADO, DIGITE NOVAMENTE: \n");
			scanf ("%d", &cod2);
			achou2 = BuscaFornecedor(ptr, cod2);
		}
		tab_compras.fornecedor_prod = cod2;
		printf ("DIGITE O CODIGO DO PRODUTO: \n");
		scanf ("%d", &cod3);
		achou3 = BuscaCod(ptr, cod3);
		pos = BuscaPos(ptr, cod3);
		while (achou3 == 0 || pos == -1)
		{
			printf ("CODIGO NAO ENCONTRADO, DIGITE OUTRA VEZ: \n");
			scanf ("%d", &cod3);
			achou3 = BuscaCod(ptr, cod3);
			pos = BuscaPos(ptr, cod3);
		}
		tab_compras.cod_prod = cod3;
		printf ("DIGITE A QUANTIDADE: \n");
		scanf ("%d", &tab_compras.qtd);
		
		pos_a = ftell(ptr);
		fseek(ptr, pos, 0);
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
		qtd = tab_estoque.qtd_estoque;
		
		fseek(ptr, pos_a, 0);
		
		while (tab_compras.qtd > qtd)
		{
			printf ("NAO HA QUANTIDADE SUFICIENTE DO PRODUTO EM ESTOQUE, DIGITE NOVAMENTE: \n");
			scanf ("%d", &tab_compras.qtd);
		}
		
		valor_soma = tab_compras.qtd;
		fseek(ptr, pos, 0);
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
		tab_estoque.qtd_estoque = tab_estoque.qtd_estoque + valor_soma;
		fseek(ptr, pos, 0);
		fwrite(&tab_estoque.qtd_estoque, sizeof(Estoque), 1, ptr);
		
		fseek(ptr, pos_a, 0);
		
		printf ("DIGITE A VALIDADE: \n");
		scanf ("%d %d %d", &tab_compras.validade.dia, &tab_compras.validade.mes, &tab_compras.validade.ano);
		printf ("DIGITE O CUSTO: \n");
		scanf ("%f", &tab_compras.custo);
		
		tab_compras.cod_compras = cod;
		fwrite(&tab_compras, sizeof(Compras), 1, ptr);
		
		printf ("\n----------------------------------------------------------\n");
		
		printf ("DIGITE O CODIGO DA COMPRA: \n");
		scanf ("%d", &cod);
		achou = BuscaCodCompras(ptr, cod);
		while (achou == 1 || cod == 0)
		{
			printf ("CODIGO REPETIDO OU NULO, DIGITE NOVAMENTE: \n");
			scanf ("%d", &cod);
			achou = BuscaCodCompras(ptr, cod);
		}
	}	
	fclose(ptr);
}

void ExcluirProdutos(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Estoque tab_estoque;
	int cod, pos;
	
	system("cls");
	printf("\n --- EXCLUSAO FISICA DE PRODUTOS ---\n\n");
	printf ("DIGITE O CODIGO DO PRODUTO A SER EXCLUIDO: \n");
	scanf("%d",&cod);
	if (cod > 0)
	{
		pos = BuscaPos(ptr, cod);
		if (pos==-1)
			printf("\nCODIGO NAO ENCONTRADO!\n");
		else
			{
				fseek(ptr, pos, 0); 
				fread(&tab_estoque, sizeof(Estoque), 1, ptr);
				printf ("CODIGO DO PRODUTO: %d\n", tab_estoque.cod_prod);
				printf ("DESCRICAO DO PRODUTO: %s\n", tab_estoque.descricao_prod);
				printf ("QUANTIDADE EM ESTOQUE: %d\n", tab_estoque.qtd_estoque);
				printf ("QUANTIDADE MINIMA: %d\n", tab_estoque.qtd_min);
				printf ("VENDA: %.2f\n", tab_estoque.venda);
				printf ("CUSTO: %.2f\n", tab_estoque.custo);
				printf ("FORNECEDOR DO PRODUTO: %d\n", tab_estoque.fornecedor_prod);
				
				printf ("EXCLUIR PRODUTO? (S/N)\n");
				if (toupper(getche())=='S')
				{
					rewind(ptr);
					FILE *ptrT = fopen("Temp.dat","wb");
					fread(&tab_estoque,sizeof(Estoque),1,ptr);
					while(!feof(ptr))
					{
						if (tab_estoque.cod_prod != cod)
							fwrite(&tab_estoque,sizeof(Estoque),1,ptrT);
						
						fread(&tab_estoque,sizeof(Estoque),1,ptr);
					}
					fclose(ptr);
					fclose(ptrT);
					remove(nome);
					rename("Temp.dat",nome);
					printf("\nPRODUTO EXCLUIDO!\n");
				}
				else fclose(ptr);
			}
	}
	else
		printf("\nCODIGO NAO VALIDO!\n");
		
	Sleep(2000);
}

void AlterarEstoque(char nome[100])
{
	FILE *ptr = fopen(nome, "rb+");
	
	int cod, pos, achou1, cod2, pos_a;
	Estoque tab_estoque;
	system("cls");
	printf ("\n --- ALTERAR INFORMACOES DE PRODUTOS ---\n\n");

	printf ("DIGITE O CODIGO DO PRODUTO A SER ALTERADO: \n");
	scanf ("%d", &cod);
	pos = BuscaPos(ptr, cod);
	while (cod > 0)
	{
		while (pos == -1)
		{
			printf ("CODIGO NAO ENCONTRADO, DIGITE NOVAMENTE!\n");
			scanf ("%d", &cod);
			pos = BuscaPos(ptr, cod);
		}
		
		fseek(ptr, pos, 0);
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
		
		printf ("CODIGO DO PRODUTO: %d\n", tab_estoque.cod_prod);
		printf ("DESCRICAO DO PRODUTO: %s\n", tab_estoque.descricao_prod);
		printf ("QUANTIDADE EM ESTOQUE: %d\n", tab_estoque.qtd_estoque);
		printf ("QUANTIDADE MINIMA: %d\n", tab_estoque.qtd_min);
		printf ("VENDA: %.2f\n", tab_estoque.venda);
		printf ("CUSTO: %.2f\n", tab_estoque.custo);
		printf ("FORNECEDOR DO PRODUTO: %d\n", tab_estoque.fornecedor_prod);
		printf ("ALTERAR PRODUTO? (S/N)\n");
		if (toupper(getche())=='S')
		{
			printf("\nDIGITE O CODIGO DO FORNECEDOR: \n");
			scanf ("%d", &cod2);
			achou1 = BuscaFornecedor(ptr, cod2);	
			while (achou1 == 0)
			{
			printf ("FORNECEDOR NAO ENCONTRADO, DIGITE NOVAMENTE: \n");
			scanf ("%d", &cod2);
			achou1 = BuscaFornecedor(ptr, cod2);
			}
			tab_estoque.fornecedor_prod = cod2;
			fflush(stdin);
			printf ("DIGITE A DESCRICAO DO PRODUTO: \n");
			gets(tab_estoque.descricao_prod);
			printf ("DIGITE A QUANTIDADE EM ESTOQUE: \n");
			scanf ("%d", &tab_estoque.qtd_estoque);
			printf ("DIGITE A QUANTIDADE MINIMA: \n");
			scanf ("%d", &tab_estoque.qtd_min);
			printf ("DIGITE A VENDA: \n");
			scanf ("%f", &tab_estoque.venda);
			printf ("DIGITE O CUSTO: \n");
			scanf ("%f", &tab_estoque.custo);
			fseek(ptr, pos, 0);
			fwrite(&tab_estoque, sizeof(Estoque), 1, ptr);
			
			
			printf ("\nPRODUTO ALTERADO! \n");
		}
		
		printf ("\n----------------------------------------------------------\n");
		
		printf ("DIGITE O CODIGO DO PRODUTO A SER ALTERADO: \n");
		scanf ("%d", &cod);
		pos = BuscaPos(ptr, cod);
	}
	
	Sleep(3000);
	fclose(ptr);
}

void ConsultaProdutos(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	int cod, pos;
	Estoque tab_estoque;
	system("cls");
	printf ("\n --- CONSULTAR PRODUTOS ---\n\n");
	
	printf ("DIGITE O CODIGO DO PRODUTO A SER CONSULTADO: \n");
	scanf ("%d", &cod);
	pos = BuscaPos(ptr, cod);
	while (cod > 0)
	{
		while (pos == -1)
		{
			printf ("CODIGO NAO ENCONTRADO, DIGITE NOVAMENTE!\n");
			scanf ("%d", &cod);
			pos = BuscaPos(ptr, cod);
		}
		fseek(ptr, pos, 0);
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
		printf ("CODIGO DO PRODUTO: %d\n", tab_estoque.cod_prod);
		printf ("DESCRICAO DO PRODUTO: %s\n", tab_estoque.descricao_prod);
		printf ("QUANTIDADE EM ESTOQUE: %d\n", tab_estoque.qtd_estoque);
		printf ("QUANTIDADE MINIMA: %d\n", tab_estoque.qtd_min);
		printf ("VENDA: %.2f\n", tab_estoque.venda);
		printf ("CUSTO: %.2f\n", tab_estoque.custo);
		printf ("FORNECEDOR DO PRODUTO: %d\n", tab_estoque.fornecedor_prod);
		
		printf ("\n----------------------------------------------------------\n");
		
		printf ("DIGITE O CODIGO DO PRODUTO A SER CONSULTADO: \n");
		scanf ("%d", &cod);
		pos = BuscaPos(ptr, cod);
	}
		
	Sleep(3000);
	fclose(ptr);
}

int BuscaPosFornecedores(FILE *ptr, int aux)
{
	Fornecedores tab_fornecedores1;
	rewind(ptr);
	fread(&tab_fornecedores1,sizeof(Fornecedores),1,ptr);
	
	while (!feof(ptr) && aux!=tab_fornecedores1.fornecedor_prod)
		fread(&tab_fornecedores1,sizeof(Fornecedores),1,ptr);
	
	if (!feof(ptr))
		return ftell(ptr)-sizeof(Fornecedores);
	else
		return -1;
}

void RelatorioProdutos(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Estoque tab_estoque;
	Fornecedores tab_fornecedores;
	int pos, cod, pos_a;
	system("cls");
	printf ("\n --- RELATORIO DE PRODUTOS ---\n\n");
	fread(&tab_estoque, sizeof(Estoque), 1, ptr);

	while (!feof(ptr))
	{
		printf ("\n----------------------------------------------------------\n");
		printf ("CODIGO DO PRODUTO: %d\n", tab_estoque.cod_prod);
		printf ("DESCRICAO DO PRODUTO: %s\n", tab_estoque.descricao_prod);
		printf ("QUANTIDADE EM ESTOQUE: %d\n", tab_estoque.qtd_estoque);
		printf ("QUANTIDADE MINIMA: %d\n", tab_estoque.qtd_min);
		printf ("VENDA: %.2f\n", tab_estoque.venda);
		printf ("CUSTO: %.2f\n", tab_estoque.custo);
		printf ("CODIGO FORNECEDOR DO PRODUTO: %d\n", tab_estoque.fornecedor_prod);
		cod = tab_estoque.fornecedor_prod;
		pos = BuscaPosFornecedores(ptr, cod);
		
		pos_a = ftell(ptr);
		fseek(ptr, pos, 0);
		fread(&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
		printf ("NOME DO FORNECEDOR: %s\n", tab_fornecedores.nome_fornecedor);
		
		fseek(ptr, pos_a, 0);
		printf ("\n----------------------------------------------------------\n");
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
	}
	printf ("FIM DO RELATORIO\n");
	
	Sleep(3000);
	fclose(ptr);
}

void RelatorioFornecedores(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Fornecedores tab_fornecedores;
	system("cls");
	printf ("\n --- RELATORIO DE FORNECEDORES ---\n\n");

	fread(&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
	while (!feof(ptr))
	{
		printf ("\n----------------------------------------------------------\n");
		printf ("CODIGO DO FORNECEDOR: %d\n", tab_fornecedores.fornecedor_prod);
		printf ("NOME DO FORNECEDOR: %s\n", tab_fornecedores.nome_fornecedor);
		printf ("CIDADE DO FORNECEDOR: %s\n", tab_fornecedores.cidade_fornecedor);
		
		printf ("\n----------------------------------------------------------\n");
		fread(&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
	}
	printf ("FIM DO RELATORIO\n");
	
	Sleep(3000);
	fclose(ptr);
}

void RelatorioCompras(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Compras tab_compras;
	Fornecedores tab_fornecedores;
	Estoque tab_estoque;
	int cod, pos, cod2, pos2, pos_a;
	system("cls");
	printf ("\n --- RELATORIO DE COMPRAS ---\n\n");
	
	fread(&tab_compras, sizeof(Compras), 1, ptr);
	while (!feof(ptr))
	{
		printf ("\n----------------------------------------------------------\n");
		printf ("CODIGO DA COMPRA: %d\n", tab_compras.cod_compras);
		printf ("CODIGO DO FORNECEDOR: %d\n", tab_compras.fornecedor_prod);
		cod = tab_compras.fornecedor_prod;
		
		pos = BuscaPosFornecedores(ptr, cod);
		pos_a = ftell(ptr);
		fseek(ptr, pos, 0);
		fread(&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
		
		printf ("NOME DO FORNECEDOR: %s\n", tab_fornecedores.nome_fornecedor);
		fseek(ptr, pos_a, 0);
		printf ("CODIGO DA PRODUTO: %d\n", tab_compras.cod_prod);
		cod2 = tab_compras.cod_prod;
		
		pos2 = BuscaPos(ptr, cod2);
		pos_a = ftell(ptr);
		fseek(ptr, pos2, 0);
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
	
		printf ("NOME DO PRODUTO: %s\n", tab_estoque.descricao_prod);
		fseek(ptr, pos_a, 0);
		printf ("QUANTIDADE: %d\n", tab_compras.qtd);
		printf ("CUSTO: %.2f\n", tab_compras.custo);
		printf ("VALIDADE: %d / %d / %d\n", tab_compras.validade.dia, tab_compras.validade.mes, tab_compras.validade.ano);
		
		printf ("\n----------------------------------------------------------\n");
		fread(&tab_compras, sizeof(Compras), 1, ptr);
	}
	printf ("FIM DO RELATORIO\n");
	
	Sleep(3000);
	fclose(ptr);
}

void Ordenar(char nome[100])
{
	FILE *ptr = fopen(nome,"rb+");
	int a, b, qtd;
	Fornecedores tab1, tab2;
	
	fseek(ptr,0,2);
	qtd = ftell(ptr)/sizeof(Fornecedores);
	
	for(a=0; a<qtd-1; a++)
		for(b=a+1; b<qtd; b++)
		{
			fseek(ptr,a*sizeof(Fornecedores),0);
			fread(&tab1,sizeof(Fornecedores),1,ptr);
			
			fseek(ptr,b*sizeof(Fornecedores),0);
			fread(&tab2,sizeof(Fornecedores),1,ptr);
			
			if (strcmp(tab1.nome_fornecedor,tab2.nome_fornecedor)>0)
			{
				fseek(ptr,a*sizeof(Fornecedores),0);
				fwrite(&tab2,sizeof(Fornecedores),1,ptr);
				
				fseek(ptr,b*sizeof(Fornecedores),0);
				fwrite(&tab1,sizeof(Fornecedores),1,ptr);
			}
		}
	
	fclose(ptr);
	getch();
}

void Ordenar2(char nome[100])
{
	FILE *ptr = fopen(nome,"rb+");
	int a, b, qtd;
	Estoque tab1, tab2;
	
	fseek(ptr,0,2);
	qtd = ftell(ptr)/sizeof(Fornecedores);
	
	for(a=0; a<qtd-1; a++)
		for(b=a+1; b<qtd; b++)
		{
			fseek(ptr,a*sizeof(Estoque),0);
			fread(&tab1,sizeof(Estoque),1,ptr);
			
			fseek(ptr,b*sizeof(Estoque),0);
			fread(&tab2,sizeof(Estoque),1,ptr);
			
			if (tab1.qtd_estoque > tab2.qtd_estoque)
			{
				fseek(ptr,a*sizeof(Fornecedores),0);
				fwrite(&tab2,sizeof(Fornecedores),1,ptr);
				
				fseek(ptr,b*sizeof(Fornecedores),0);
				fwrite(&tab1,sizeof(Fornecedores),1,ptr);
			}
		}
	
	fclose(ptr);
	getch();
}

void RelatorioFornecedoresProdutos(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Fornecedores tab_fornecedores;
	Estoque tab_estoque;
	int pos_f, pos_e, cod_fornecedor;
	system("cls");
	printf ("\n--- RELATORIO DE PRODUTOS POR FORNECEDORES ---\n\n");

	Ordenar("tudo.dat");
	fread(&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
	while (!feof(ptr))
	{
		printf ("\n----------------------------------------------------------\n");
		printf ("CODIGO DO FORNECEDOR: %d\n", tab_fornecedores.fornecedor_prod);
		printf ("NOME DO FORNECEDOR: %s\n", tab_fornecedores.nome_fornecedor);
		printf ("CIDADE DO FORNECEDOR: %s\n", tab_fornecedores.cidade_fornecedor);
		pos_f = ftell(ptr);
		
		cod_fornecedor = tab_fornecedores.fornecedor_prod;
		rewind(ptr);
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
		while (!feof(ptr))
		{
			if (cod_fornecedor == tab_estoque.fornecedor_prod)
			{
				printf ("\n");
				printf ("        CODIGO DO PRODUTO: %d\n", tab_estoque.cod_prod);
				printf ("        DESCRICAO DO PRODUTO: %s\n", tab_estoque.descricao_prod);
				printf ("        QUANTIDADE EM ESTOQUE: %d\n", tab_estoque.qtd_estoque);
				printf ("        QUANTIDADE MINIMA: %d\n", tab_estoque.qtd_min);
				printf ("        VENDA: %.2f\n", tab_estoque.venda);
				printf ("        CUSTO: %.2f\n", tab_estoque.custo);
			}
			fread(&tab_estoque, sizeof(Estoque), 1, ptr);
		}
		
		printf ("\n----------------------------------------------------------\n");
		
		fseek(ptr, pos_f, 0);
		fread(&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
	}
	printf ("FIM DO RELATORIO\n");
	
	Sleep(3000);
}

void RelatorioEstoqueMin(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Estoque tab_estoque;
	system("cls");
	printf ("\n--- RELATORIO DE PRODUTOS COM ESTOQUE ABAIXO DA QUANTIDADE MINIMA ---\n\n");
	Ordenar2 ("tudo.dat");
	fread(&tab_estoque, sizeof(Estoque), 1, ptr);
	while(!feof(ptr))
	{
		if (tab_estoque.qtd_min > tab_estoque.qtd_estoque)
		{
			printf ("\n----------------------------------------------------------\n");
			printf ("CODIGO DO PRODUTO: %d\n", tab_estoque.cod_prod);
			printf ("DESCRICAO DO PRODUTO: %s\n", tab_estoque.descricao_prod);
			printf ("QUANTIDADE EM ESTOQUE: %d\n", tab_estoque.qtd_estoque);
			printf ("QUANTIDADE MINIMA: %d\n", tab_estoque.qtd_min);
			printf ("VENDA: %.2f\n", tab_estoque.venda);
			printf ("CUSTO: %.2f\n", tab_estoque.custo);
			printf ("\n----------------------------------------------------------\n");
		}
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
	}
	Sleep(3000);
	fclose(ptr);
}

void PesquisaNome(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Estoque tab_estoque;
	char aux[40];
	system("cls");
	printf("\n--- PESQUISA POR NOME DO PRODUTO ---\n\n");
	printf("NOME DO PRODUTO: \n");
	fflush(stdin);
	gets(aux);
	while (strcmp(aux,"\0")!=0)
	{
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
		while(!feof(ptr))
		{
			if (stricmp(aux,tab_estoque.descricao_prod)==0)
			{
				printf ("\n----------------------------------------------------------\n");
				printf ("CODIGO DO PRODUTO: %d\n", tab_estoque.cod_prod);
				printf ("DESCRICAO DO PRODUTO: %s\n", tab_estoque.descricao_prod);
				printf ("QUANTIDADE EM ESTOQUE: %d\n", tab_estoque.qtd_estoque);
				printf ("QUANTIDADE MINIMA: %d\n", tab_estoque.qtd_min);
				printf ("VENDA: %.2f\n", tab_estoque.venda);
				printf ("CUSTO: %.2f\n", tab_estoque.custo);
				printf ("FORNECEDOR DO PRODUTO: %d\n", tab_estoque.fornecedor_prod);
				printf ("\n----------------------------------------------------------\n");
			}
			fread(&tab_estoque, sizeof(Estoque), 1, ptr);
		}

		Sleep(3000);
		
		
		printf("NOME DO PRODUTO: \n");
		fflush(stdin);
		gets(aux);
	}
	fclose(ptr);
}

void PesquisaForn(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Fornecedores tab_fornecedores;
	char aux[40];
	system("cls");
	printf("\n--- PESQUISA POR NOME DO FORNECEDOR ---\n\n");
	printf("NOME DO FORNECEDOR: \n");
	fflush(stdin);
	gets(aux);
	while (strcmp(aux,"\0")!=0)
	{
		fread(&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
		while (!feof(ptr))
		{
			if (stricmp(aux,tab_fornecedores.nome_fornecedor)==0)
			{
				printf ("\n----------------------------------------------------------\n");
				printf ("CODIGO DO FORNECEDOR: %d\n", tab_fornecedores.fornecedor_prod);
				printf ("NOME DO FORNECEDOR: %s\n", tab_fornecedores.nome_fornecedor);
				printf ("CIDADE DO FORNECEDOR: %s\n", tab_fornecedores.cidade_fornecedor);
				
				printf ("\n----------------------------------------------------------\n");
			}
			fread(&tab_fornecedores, sizeof(Fornecedores), 1, ptr);
		}
		
		Sleep(3000);
		
		printf("NOME DO FORNECEDOR: \n");
		fflush(stdin);
		gets(aux);
	}
	fclose(ptr);
}

void Estatisticas(char nome[100])
{
	FILE *ptr = fopen(nome, "rb");
	
	Compras tab_compras;
	Estoque tab_estoque;
	int pos_maior_lucro, maior_qtd, pos_maior_qtd, cod, pos_mais_comprado;
	float lucro, maior_lucro, total_lucro, media_lucro, x;
	maior_qtd = 0;
	maior_lucro = 0;
	total_lucro = 0;
	media_lucro = 0;
	system("cls");
	
	printf("\n--- ESTATISTICAS ---\n\n");
	
	fread(&tab_compras, sizeof(Compras), 1, ptr);
	while (!feof(ptr))
	{
		if (tab_compras.qtd > maior_qtd)
		{
			maior_qtd = tab_compras.qtd;
			pos_maior_qtd = ftell(ptr);
		}
		fread(&tab_compras, sizeof(Compras), 1, ptr);
	}
	
	rewind(ptr);
	fread(&tab_estoque, sizeof(Estoque), 1, ptr);
	while (!feof(ptr))
	{
		lucro = tab_estoque.venda - tab_estoque.custo;
		total_lucro = total_lucro + lucro;
		if (lucro > maior_lucro)
		{
			maior_lucro = lucro;
			pos_maior_lucro = ftell(ptr);
		}
		fread(&tab_estoque, sizeof(Estoque), 1, ptr);
	}
	
	fseek(ptr, 0, 2);
	x = ftell(ptr) / sizeof(Estoque);
	media_lucro = total_lucro / x;
	
	fseek(ptr, pos_maior_qtd, 0);
	fread(&tab_compras, sizeof(Compras), 1, ptr);
	cod = tab_compras.cod_prod;
	
	pos_mais_comprado = BuscaPos(ptr, cod);
	

	printf ("\n----------------------------------------------------------\n");
	fseek(ptr, pos_mais_comprado, 0);
	fread(&tab_estoque, sizeof(Estoque), 1, ptr);
	printf ("PRODUTO MAIS COMPRADO: %s\n", tab_estoque.descricao_prod);
	
	fseek(ptr, pos_maior_lucro, 0);
	fread(&tab_estoque, sizeof(Estoque), 1, ptr);
	printf ("PRODUTO COM MAIOR LUCRO: %s\n", tab_estoque.descricao_prod);
	
	printf ("MEDIA PERCENTUAL DE LUCRO DOS PRODUTOS: %.2f %%\n", media_lucro);
	printf ("\n----------------------------------------------------------\n");
		
	Sleep(3000);
	
	fclose(ptr);
}

void CriarArquivos(void)
{
	FILE *ptr = fopen("tudo.dat","ab");
	fclose(ptr);
}

void ConheceArquivo(void)
{
    char Arquivo[100];
	
	printf("\nIndique o nome ou caminho do arquivo: ");
	fflush(stdin);
	gets(Arquivo);
	while (strcmp(Arquivo,"\0")!=0)
	{
		VerificaArquivo(Arquivo);
		
		printf("\nIndique o nome ou caminho do Arquivo: ");
		fflush(stdin);
		gets(Arquivo);
	}
}

void VerificaArquivo(char nome[100])
{
	FILE *ptr = fopen(nome,"rb");
	if (ptr == NULL)
	{
		printf("\nErro de abertura do arquivo!\n");
		Sleep(300);
		printf("\nDeseja criar o arquivo(S/N)? ");
		if (toupper(getche())=='S')
		{
			ptr = fopen(nome,"wb");
			printf("\nO arquivo foi criado corretamente!!\n");
			fclose(ptr);
			getch();
		}
	}
	else 
		{
			printf("\nArquivo existente!\n");
			getch();
			fclose(ptr);
		}
}

int main(void)
{
	char opcao;
	
	CriarArquivos();
	
	Menu();
	do
	{
		opcao = Menu();
		switch (opcao)
		{
			case 'X': ConheceArquivo();
						break;
			case 'A': LeFornecedores("tudo.dat");
						break;
			case 'B': LeEstoque("tudo.dat");
						break;
			case 'C': LeCompras("tudo.dat");
						break;
			case 'D': ExcluirProdutos("tudo.dat");
						break;
			case 'E': AlterarEstoque("tudo.dat");
						break;
			case 'F': ConsultaProdutos("tudo.dat");
						break;
			case 'G': RelatorioProdutos("tudo.dat");
						break;
			case 'H': RelatorioFornecedores("tudo.dat");
						break;
			case 'I': RelatorioCompras("tudo.dat");
						break;
			case 'J': RelatorioFornecedoresProdutos("tudo.dat");
						break;
			case 'K': RelatorioEstoqueMin("tudo.dat");
						break;
			case 'L': PesquisaNome("tudo.dat");
						break;
			case 'M': PesquisaForn("tudo.dat");
						break;
			case 'N': Estatisticas("tudo.dat");
						break;
		}
	}
	while (opcao != 27);
}

