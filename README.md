# Projeto-C++

<h3>ESTRUTURAS DE DADOS UTILIZADAS</h3>

STRUCTS: Fornecedores, Estoque, Data, Compras.


FUNÇÕES void: CriarArquivos, ConheceArquivos, VerificaArquivo, LeFornecedores, LeEstoque, LeCompras, ExcluirProdutos, AlterarEstoque, ConsultaProdutos, RelatorioProdutos, RelatorioFornecedores, RelatorioCompras, Ordenar, Ordenar2, RelatorioFornecedoresProdutos, RelatorioEstoqueMin, PesquisaNome, PesquisaForn, Estatisticas.


FUNÇÕES int: BuscaFornecedor, BuscaCod, BuscaCodCompras, BuscaPos, BuscaPosFornecedores, main.


FUNÇÃO char: Menu.

<h3>DESCRIÇÃO DAS FUNCIONALIDADES</h3>

    STRUCTS

Fornecedores: essa struct grava informações relacionadas aos fornecedores cadastrados, sendo elas o código, o nome e a cidade do fornecedor.

Estoque: essa struct grava informações relacionadas aos produtos, como o código, a quantidade, a quantidade mínima, o fornecedor do produto, a descrição (ou nome), o preço de venda e o preço de custo.

Data: essa struct guarda dados da data de validade (dia/mês/ano). É utilizada na struct de Compras.

Compras: essa struct guarda dados de compras registradas, incluindo o código da compra, o fornecedor do produto, o código do produto, a quantidade, o custo e a data de validade.

    FUNÇÕES void

CriarArquivos: essa função abre o arquivo, ou cria ele se não existe (nesse caso, “tudo.dat”).

ConheceArquivo: nessa função, o usuário digita o nome de um arquivo até que o nome seja nulo, usando outra função (VerificaArquivo) para verificar se ele existe.

VerificaArquivo: essa função verifica se o arquivo digitado na função ConheceArquivo existe. Se não existe, ela cria o arquivo. Se existe, simplesmente avisa sobre isso.

LeFornecedores: essa função registra fornecedores, pedindo o código até que ele seja 0. Se o código não existe, a função prossegue para o nome e a cidade.

LeEstoque: essa função registra o estoque, pedindo o código do fornecedor até que ele seja 0. Se o código existe, pede o código do produto, e se o código do produto não existe, prossegue para a descrição, a quantidade, a quantidade mínima, o preço de venda e o custo.

LeCompras: essa função registra as compras, pedindo o código da compra. Se não existe, pede os códigos do fornecedor e do produto. Se existem, a função pede a quantidade do produto (desde que seja suficiente a quantidade dele no estoque), a data de validade e o custo.

ExcluirProdutos: essa função exclui produtos do estoque, pedindo o código do produto a ser excluído. Se existe, mostra os detalhes do produto e pede a confirmação da exclusão, com opções de digitar S (Sim) ou N (Não).

AlterarEstoque: essa função pede o código do produto para ser alterado. Se existe, mostra os detalhes do produto, e pede confirmação com opções de pressionar S (Sim) ou N (Não). Se S é pressionado, a função pede para o usuário digitar as novas informações do produto.

ConsultaProdutos: essa função pede o código do produto, e se o código digitado pelo usuário existe, mostra os detalhes do produto.

RelatorioProdutos: essa função mostra os detalhes de todos os produtos cadastrados no programa.

RelatorioFornecedores: essa função mostra os detalhes de todos os fornecedores.

RelatorioCompras: essa função mostra os detalhes de todas as compras.

Ordenar: essa função ordena os produtos por nome.

Ordenar2: essa função ordena os produtos pela quantidade em estoque.

RelatorioFornecedoresProdutos: essa função mostra os detalhes de todos os produtos por fornecedor.

RelatorioEstoqueMin: essa função mostra os detalhes de todos os produtos com estoque abaixo da quantidade mínima.

PesquisaNome: essa função mostra os detalhes de um produto pelo nome digitado.

PesquisaForn: essa função mostra os detalhes de um fornecedor pelo nome digitado.

Estatisticas: essa função mostra estatísticas,  sendo elas o produto mais comprado, o produto com maior lucro e a média percentual de lucro dos produtos.


    FUNÇÕES int

  
BuscaFornecedor: essa função busca um fornecedor, retornando 1 se ele existe, ou 0 se não existe. É usada em: LeFornecedores, LeEstoque e LeCompras.

BuscaCod: essa função busca um código de um produto, retornando 1 se existe, ou 0 se não existe. É usada em: LeEstoque e LeCompras.

BuscaCodCompras: essa função busca um código de compras, retornando 1 se existe, ou 0 se não existe. É usada em: LeCompras.

BuscaPos: essa função busca a posição de um produto, retornando o valor da posição se existe, ou –1 se não existe. É usada em: LeCompras.

BuscaPosFornecedores: essa função busca a posição de um fornecedor, retornando o valor da posição se existe, ou –1 se não existe. É usada em: RelatorioProdutos.

main: essa função conecta as outras funções, sendo a principal, e primeira tela.


    FUNÇÃO char


Menu: essa função mostra as opções do programa na função main.

