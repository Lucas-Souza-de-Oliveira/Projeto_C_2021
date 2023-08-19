#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Adicionar coisas para os voluntarios

struct Produtos {
	int codigo, qtdEstoque, qtdMinEstoque;
	float valor;
	char nomeProd[20];
};

struct Produtos cadProduto[10];

struct Compra {  //struct pro processo de compra
    int BackICompr, QntCar, QntProd, PesqProd, code;
    float Price;
};

struct Compra CarCompra[10];

struct CompraPreco {
    float FullPrice;
    int BackI, BackIVolun, SaidaMain; //Quantia de produtos //Quantia de voluntarios
};

struct CompraPreco CarCompraPreco;

struct Voluntario{
	char nome[70], cidade[50];
	double cpf, telefone;
};

struct Voluntario cadVoluntario[5];

struct Cliente{
	char nome[50], endereco[60], cidade[50];
	double cpf, telefone, cep;
};

struct Cliente cadCliente[5];

int cadastrar();
int consultaEstoque();
int cadastroCliente();
int cadastroVoluntario();
int consultaVoluntario();
int loja();
int OpSn(int OpSn);
int MAdm();
int CompraWay(int i, int i2);
int CompraCar(int I2);
int CompraFinal();

void sair(){
    system("cls || clear");
    printf("\n=--------------------------------------------------------------------=\n\n");
    printf("Obrigado por acessar nossa página.\n");
    printf("Volte sempre.\n");
    printf("\n=--------------------------------------------------------------------=\n\n");
}


int main(){
setlocale(LC_ALL, "");
    int op=1, OpSaida = 1;

    while (OpSaida < 3 && CarCompraPreco.SaidaMain != 3 ){
        system("cls || clear");
    	printf("\n=--------------------------------------------------------------------=\n");
		printf("=------------------------------Ecoplace------------------------------=\n");
		printf("=--------------------------------------------------------------------=\n\n");

		printf("[1] - Cadastro de Voluntário\n");
		printf("[2] - Menu do Admin\n");
		printf("[3] - Loja\n");
		printf("\n=--------------------------------------------------------------------=\n\n");
		printf("Digite o número da opção desejada: ");
			scanf("%d", &op);

        while (op > 3 || op < 1){
        printf("\n!---------------------------Opção Invalida---------------------------!\n\n");
        printf("Digite novamente: ");
        scanf("%d", &op);
        }

		switch(op){
		case 1:
		    system("cls || clear");
			 cadastroVoluntario();
		break;
		case 2:
		    MAdm();
		break;
		case 3:
		    system("cls || clear");
			OpSaida = loja();
		break;
		}
    }
    sair();
    system("pause");
    return 0;
}

int loja(){
	int op, i=0, i2 = 0;
		printf("\n=--------------------------------------------------------------------=\n");
		printf("=----------------------------Loja Ecoplace---------------------------=\n");
		printf("=--------------------------------------------------------------------=\n\n");

		printf("=--------------------------Lista de Produtos-------------------------=\n");

		consultaEstoque();

		printf("\n=--------------------------------------------------------------------=\n\n");
		printf("[1] - Comprar produto\n");
		printf("[2] - Retornar a página inicial\n");
		printf("[3] - Finalizar acesso\n");
		printf("\n=--------------------------------------------------------------------=\n\n");
		printf("Digite o número da opção desejada: ");
        scanf("%d", &op);

        while (op > 3 || op < 1){ //verificação op
        printf("\n!---------------------------Opção Invalida---------------------------!\n\n");
        printf("Digite novamente: ");
        scanf("%d", &op);
        }

		switch(op){
			case 1:
			   CompraWay(i, i2);
		break;
			case 2:
				main();
		break;
		}
    return (op);
}

int CompraWay(int i, int i2){
    int OpSN, BackI;

    BackI = CarCompraPreco.BackI;
    printf("\n=--------------------------------------------------------------------=\n\n");
			    printf("Digite o código do produto que deseja: ");
			    scanf("%d", &CarCompra[i2].PesqProd);

			    while (cadProduto[i].codigo != CarCompra[i2].PesqProd && i < BackI){ //Proceesso de pesquisa
                i++;
                    if (cadProduto[i].codigo != CarCompra[i2].PesqProd && i == BackI){
                       printf("\nSinto muito, mas não temos o produto que deseja.\n");
                       system("pause");
                       system("cls || clear");
                       loja();
                    }
                    if(cadProduto[i].codigo == CarCompra[i2].PesqProd){
                        printf("\n=--------------------------------------------------------------------=\n\n");
                        CarCompra[i2].BackICompr = i; //Backup i
                        printf("Produto é: %s\n", cadProduto[i].nomeProd);
                        printf("Código dele: %d\n", cadProduto[i].codigo);
                        CarCompra[i2].code = cadProduto[i].codigo; //salvando dado
                        printf("O valor base é de: R$%.2f\n", cadProduto[i].valor);
                        printf("Ainda há %d desse produto no estoque\n", cadProduto[i].qtdEstoque - cadProduto[i].qtdMinEstoque);
                        printf("\n=--------------------------------------------------------------------=\n\n");

                        printf("Este é o produto que deseja? Digite 1 para sim ou 2 para não: ");
                        scanf("%d", &OpSN);

                        OpSN = OpSn(OpSN); //validação

                        if(OpSN == 2){
                            system("cls || clear");
                            loja();
                        }else{
                            printf("\n=--------------------------------------------------------------------=\n\n");
                            printf("Digite a quantia que deseja comprar: ");
                            scanf("%d", &CarCompra[i2].QntProd);

                            while(CarCompra[i2].QntProd > (cadProduto[i].qtdEstoque - cadProduto[i].qtdMinEstoque)){
                                printf("\n!---------------------------Quantia Invalida---------------------------!\n\n");
                                printf("Digite novamente: ");
                                scanf("%d", &CarCompra[i2].QntProd);
                            }

                            CarCompra[i2].Price = (cadProduto[i].valor * CarCompra[i2].QntProd);
                            CarCompraPreco.FullPrice = CarCompraPreco.FullPrice + CarCompra[i2].Price;
                            cadProduto[i].qtdEstoque = cadProduto[i].qtdEstoque - CarCompra[i2].QntProd;

                            printf("Deseja adicionar mais produtos ao carrinho? 1 para sim ou 2 para não: ");
                            scanf("%d", &OpSN);

                            OpSN = OpSn(OpSN); //validação

                            if(OpSN == 2){
                                CompraCar(i2);
                                CompraFinal();
                            }else{
                                printf("\n=--------------------------------------------------------------------=\n\n");
                                consultaEstoque();
                                i = 0; //Zerando valor de i para a pesquisa funcionar
                                i2++; //Passando i2 para proximo número
                                CompraWay(i, i2);
                            }
                        }
                    }
                }
    return 0;
}

int CompraCar(int I2){
    int OpSN, i2, i, R = -1, Ip = 0, x;

    i2 = I2;

    system("cls || clear");
    printf("\n=------------------------------Carrinho------------------------------=\n\n");
    printf("Produto \tQuantidade \tValor\n");
    while (I2 != -1){
        printf("%s \t%d         \tR$%.2f\n", cadProduto[CarCompra[I2].BackICompr].nomeProd, CarCompra[I2].QntProd, CarCompra[I2].Price);
        I2--;
    }

    printf("\nValor total a pagar: R$%.2f\n", CarCompraPreco.FullPrice);
    printf("\n=--------------------------------------------------------------------=\n\n");

    printf("Deseja retirar algum produto? 1 para sim ou 2 para não: ");
    scanf("%d", &OpSN);

    OpSN = OpSn(OpSN); //validação

    if(OpSN == 1){
        system("cls || clear");
        printf("\n=------------------------------Carrinho------------------------------=\n\n");
        printf("Produto \tCódigo \tQuantidade \tValor\n");
            while (I2 != i2){
            I2++;
            printf("%s \t%d \t%d         \tR$%.2f\n", cadProduto[CarCompra[I2].BackICompr].nomeProd, CarCompra[I2].code, CarCompra[I2].QntProd, CarCompra[I2].Price);
            }
        printf("\n=--------------------------------------------------------------------=\n\n");
        printf("Digite o código do produto que deseja retirar: ");
        scanf("%d", &CarCompra[Ip].PesqProd);

        i2 = 0; //zerando pra poder usar
        for(x = 0; x < CarCompraPreco.BackI; x++){
            if(CarCompra[Ip].PesqProd == CarCompra[i2].code){
                CarCompraPreco.FullPrice = CarCompraPreco.FullPrice - CarCompra[i2].Price;
                CarCompra[i2].BackICompr = -2;
                CarCompra[i2].Price = 0;
                i = -1;
                while(cadProduto[i].codigo != CarCompra[Ip].PesqProd){
                    i++;
                    if(cadProduto[i].codigo == CarCompra[Ip].PesqProd){
                     cadProduto[i].qtdEstoque = cadProduto[i].qtdEstoque + CarCompra[i2].QntProd;
                    }
                }
                CarCompra[i2].QntProd = 0;

                printf("\n=--------------------------Produto retirado--------------------------=\n\n");
                system("pause");
                system("cls || clear");

                printf("\n=------------------------------Carrinho------------------------------=\n\n");
                printf("Produto \tQuantidade \tValor\n");
                    while (I2 != -1){
                        printf("%s       \t%d         \tR$%.2f\n", cadProduto[CarCompra[I2].BackICompr].nomeProd, CarCompra[I2].QntProd, CarCompra[I2].Price);
                        I2--;
                    }
                printf("\n=--------------------------------------------------------------------=\n\n");
            }
            i2++;
        }
        system("pause");
    }
}

int CompraFinal (){
    int i=0;
    int OpSN;
    double NumCart, CodCart;

    system("cls || clear");
    printf("\n=--------------------------------------------------------------------=\n\n");
    printf("Valor total a pagar: R$%.2f\n", CarCompraPreco.FullPrice);
    printf("\nProsseguir com a compra? 1 para sim ou 2 para não: ");
    scanf("%d", &OpSN);

    OpSN = OpSn(OpSN); //validação

    if(OpSN == 1){
        cadastroCliente();
        printf("\n=--------------------------------------------------------------------=\n\n");
        printf("Digite o número de seu cartão: ");
        scanf("%lf", &NumCart);
        printf("\nDigite o código de segurança: ");
        scanf("%lf", &CodCart);
        printf("\n=--------------------------------------------------------------------=\n\n");

        printf("Compra realizada com sucesso.\n");

        printf("\n=--------------------------------------------------------------------=\n\n");
        printf("Deseja retornar para a página inicial? 1 para sim ou 2 para não: ");
        scanf("%d", &OpSN);

        OpSN = OpSn(OpSN); //validação

        if(OpSN == 1){
            system("cls || clear");
            main();
        }else {
        system("cls || clear");
        CarCompraPreco.SaidaMain = 3;
        }
    }else {
         printf("\n=--------------------------------------------------------------------=\n\n");
        printf("Deseja retornar para a página inicial? 1 para sim ou 2 para não: ");
        scanf("%d", &OpSN);

        OpSN = OpSn(OpSN); //validação

        if(OpSN == 1){
            system("cls || clear");
            main();
        }else {
        CarCompraPreco.SaidaMain = 3;
        }
    }
}

int cadastroCliente(){
	int i = 0, OpSN = 1;

	while(OpSN == 1){
        printf("\n=--------------------------------------------------------------------=\n\n");
		printf("Para prosseguir com a compra, preencha as informações abaixo.\n");
		printf("Digite seu nome completo: ");
            gets(cadCliente[i].nome); //Não funciona direito se não colocar dois
    		gets(cadCliente[i].nome);
        printf("Digite seu endereço: ");
            gets(cadCliente[i].endereco);
        printf("Digite o nome de sua cidade: ");
            gets(cadCliente[i].cidade);
        printf("Digite seu CPF: ");
            scanf("%lf", &cadCliente[i].cpf);
        printf("Digite seu telefone: ");
            scanf("%lf", &cadCliente[i].telefone);
        printf("Digite seu CEP: ");
            scanf("%lf", &cadCliente[i].cep);

        system("cls || clear");
        printf("\n=--------------------------------------------------------------------=\n");

		printf("Nome: %s\n", strupr(cadCliente[i].nome));
		printf("Endereço: %s\n", strupr(cadCliente[i].endereco));
		printf("Cidade: %s\n", strupr(cadCliente[i].cidade));
		printf("CPF: %.0lf\n", cadCliente[i].cpf);
		printf("Telefone: %.0lf\n", cadCliente[i].telefone);
		printf("CEP: %.0lf\n", cadCliente[i].cep);

		printf("\n=--------------------------------------------------------------------=\n");
        printf("\nDeseja corrigir alguma informação? 1-sim 2-não: ");
        scanf("%d", &OpSN);

 		OpSN = OpSn(OpSN); //validação

 		i++;

 		if(OpSN == 1){
            i--;
 		}
	}
	return 0;
}

int cadastroVoluntario(){
	int i = 0, OpSN = 1;
		printf("\n=--------------------------------------------------------------------=\n");
		printf("=-----------------------Cadastro de Voluntário-----------------------=\n");
		printf("=--------------------------------------------------------------------=\n\n");

	while(OpSN == 1){
        i++;
		printf("Por favor, preencha os campos abaixo\n");
		printf("Digite seu nome completo: ");
    		gets(cadVoluntario[i].nome); //buga se so tiver 1 gets
    		gets(cadVoluntario[i].nome);

    	printf("Digite o nome da cidade em que mora: ");
    		gets(cadVoluntario[i].cidade);

		printf("Digite seu telefone: ");
    		scanf("%lf", &cadVoluntario[i].telefone);

  		printf("Digite seu CPF: ");
   			scanf("%lf", &cadVoluntario[i].cpf);
   	system("cls || clear");
   		printf("\n=----------------------Cadastrado bem sucedido-----------------------=\n");

   		printf("Nome: %s\n", strupr(cadVoluntario[i].nome));
 		printf("Cidade: %s\n", strupr(cadVoluntario[i].cidade));
 		printf("telefone: %.0lf\n", cadVoluntario[i].telefone);
 		printf("CPF: %.0lf\n", cadVoluntario[i].cpf);

 		printf("\n=--------------------------------------------------------------------=\n");
        printf("\nContinuar cadastrando? 1-sim 2-não: ");
        scanf("%d", &OpSN);

 		OpSN = OpSn(OpSN); //validação
	}
	CarCompraPreco.BackIVolun = i;
return 0;
}

int consultaVoluntario(){
    int BackINegV;

    BackINegV = CarCompraPreco.BackIVolun;
	while (BackINegV > 0){
        printf("\n=--------------------------------------------------------------------=\n\n");
		printf("Nome: %s\n", strupr(cadVoluntario[BackINegV].nome));
 		printf("Cidade: %s\n", strupr(cadVoluntario[BackINegV].cidade));
 		printf("Telefone: %.0lf\n", cadVoluntario[BackINegV].telefone);
 		printf("CPF: %.0lf\n", cadVoluntario[BackINegV].cpf);

 		BackINegV--;
	}
 return 0;
}

int cadastrar(){
	int i = 0, OpSN = 1;

    while(OpSN == 1){
        i++;
        printf("\n=--------------------------------------------------------------------=\n");
    	printf("=------------------------Cadastrando Produtos------------------------=\n");
    	printf("=--------------------------------------------------------------------=\n\n");

    	printf("Nome do produto: ");
            gets(cadProduto[i].nomeProd); //colocou dois pq não funcionava com um
            gets(cadProduto[i].nomeProd);
		printf("Código do produto: ");
			scanf("%d", &cadProduto[i].codigo);
		printf("Valor: ");
			scanf("%f", &cadProduto[i].valor);
		printf("Quantidade em estoque: ");
			scanf("%d", &cadProduto[i].qtdEstoque);
		printf("Quantidade mínima de estoque: ");
			scanf("%d", &cadProduto[i].qtdMinEstoque);
		printf("\n=----------------------Cadastrado bem sucedido-----------------------=\n");

        printf("\n=--------------------------------------------------------------------=\n");
        printf("\nContinuar cadastrando? 1-sim 2-não: ");
        scanf("%d", &OpSN);

        OpSN = OpSn(OpSN); //validação
	}
	CarCompraPreco.BackI = i;
return 0;
}

int consultaEstoque(){
    int BackINeg;

    BackINeg = CarCompraPreco.BackI;
	printf("\nProduto \t Codigo\t Valor\tEstoque \n");
	while (BackINeg > 0){ //Printa do ultimo ao primeiro cadastrado
		printf("%s \t %d \t %.2f \t %d \n", cadProduto[BackINeg].nomeProd, cadProduto[BackINeg].codigo, cadProduto[BackINeg].valor, cadProduto[BackINeg].qtdEstoque - cadProduto[BackINeg].qtdMinEstoque);
        BackINeg--;
	}
 return 0;
}

int OpSn(int OpSn){ //Função de validação de Sim e Não

    int BackOpSn;

    while (OpSn > 2 || OpSn < 1){ //verificação OpSN
    printf("\n!---------------------------Opção Invalida---------------------------!\n\n");
    printf("Digite novamente: ");
    scanf("%d", &OpSn);
    }
    BackOpSn = OpSn;
    return(BackOpSn);
}

int MAdm(){

int OpSnAdm, op, BackI;

OpSnAdm = 1;
while (OpSnAdm == 1){
    system("cls || clear");
    printf("\n=--------------------------------------------------------------------=\n");
    printf("=----------------------------Menu do Admin---------------------------=\n");
    printf("=--------------------------------------------------------------------=\n\n");
    printf("[1] - Cadastrar Produtos\n");
    printf("[2] - Consultar Estoque de Produtos\n");
    printf("[3] - Consultar Lista de Voluntários\n");
    printf("[4] - Sair\n");
    printf("\n=--------------------------------------------------------------------=\n\n");
    printf("Digite o número da opção desejada: ");
    scanf("%d", &op);
    system("cls || clear");
        switch(op){
            case 1:
            system("cls || clear");
            cadastrar();
            printf("\n=--------------------------------------------------------------------=\n");
            printf("\nContinuar administrando? 1-sim 2-não: ");
            scanf("%d", &OpSnAdm);

            OpSnAdm = OpSn(OpSnAdm); //validação

            break;
            case 2:
            BackI = CarCompraPreco.BackI;
            printf("\nProduto \t Codigo\t Valor\tEstoque\t Minimo de estoque\n");
                while (BackI > 0){ //Printa do ultimo ao primeiro cadastrado
                    printf("%s \t %d \t %.2f \t %d \t %d\n", cadProduto[BackI].nomeProd, cadProduto[BackI].codigo, cadProduto[BackI].valor, cadProduto[BackI].qtdEstoque, cadProduto[BackI].qtdMinEstoque);
                    BackI--;
                }
            printf("\n=--------------------------------------------------------------------=\n");
            printf("\nContinuar administrando? 1-sim 2-não: ");
            scanf("%d", &OpSnAdm);

            OpSnAdm = OpSn(OpSnAdm); //validação

            break;
            case 3:
            consultaVoluntario();
            printf("\n=--------------------------------------------------------------------=\n");
            printf("\nContinuar administrando? 1-sim 2-não: ");
            scanf("%d", &OpSnAdm);

            OpSnAdm = OpSn(OpSnAdm); //validação

            break;
            case 4:
            system("cls || clear");
            OpSnAdm = 2;
            break;
            }
        }
return 0;
}
