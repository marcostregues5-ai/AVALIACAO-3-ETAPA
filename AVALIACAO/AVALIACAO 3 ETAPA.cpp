#include <stdio.h>

struct Conta{
	
	
    int numero;
    char titular[50];
    float saldo;
    
    
};



int senha_admin = 1234;


int LerTexto(char destino[], int tamanho) {
	
	
    int i = 0;
    char c;

    do {
    	
    	
        c = getchar();
        
        
    } while (c == '\n');
    
    

    while (i < tamanho - 1 && c != '\n' && c != EOF) {
        destino[i] = c;
        i++;
        c = getchar();
        
        
    }
    
    

    destino[i] = '\0';
    
    
    return 1;
    
    
}


int Gerar_Numro_da_Conta() {
	
	
    FILE *arq = fopen("contas.dat", "rb");
    
    
    struct Conta c;
    int ultimo = 0;



    if (arq == NULL) {
    	
    	
        return 1;
    }

    while (fread(&c, sizeof(struct Conta), 1, arq)) {
    	
    	
        ultimo = c.numero;
        
        
    }

    fclose(arq);
    
    
    return ultimo + 1;
    
    
}



int buscar_Conta(int numero, struct Conta *destino) {
	
	
    FILE *arq = fopen("contas.dat", "rb");
    
    
    struct Conta temp;
    

    if (arq == NULL)
    
    
        return 0;

    while (fread(&temp, sizeof(struct Conta), 1, arq)) {
    	
    	
        if (temp.numero == numero) {
            *destino = temp;
            fclose(arq);
            
            
            return 1;
            
        }
        
        
    }

    fclose(arq);
    
    
    return 0;
}





int salvar_Conta(struct Conta conta) {
	
	
    FILE *arq = fopen("contas.dat", "rb+");
    
    
    struct Conta temp;

    if (arq == NULL) {
        return 0;
        
        
    }

    while (fread(&temp, sizeof(struct Conta), 1, arq)) {
    	
    	
        if (temp.numero == conta.numero) {

            
            fseek(arq, -sizeof(struct Conta), SEEK_CUR);

            
            fwrite(&conta, sizeof(struct Conta), 1, arq);

            fclose(arq);
            
            
            
            return 1;
        }
}



    fclose(arq);
    
    
    return 0;
}





int criar_Conta() {
	
	
	
    struct Conta nova;

    printf("Nome do Titular: ");
    LerTexto(nova.titular, 50);
    
    

    nova.numero = Gerar_Numro_da_Conta();
    nova.saldo = 0;



    FILE *arq = fopen("contas.dat", "ab");
    fwrite(&nova, sizeof(struct Conta), 1, arq);
    fclose(arq);



    printf("Conta Criada! Numero: %d\n", nova.numero);


    return 1;
}






int extrato() {
	
	
	
    int num;
    struct Conta c;



    printf("Numero da Conta: ");
    scanf("%d", &num);



    if (buscar_Conta(num, &c)) {
    	
    	
        printf("Titular: %s\n", c.titular);
        printf("Numero: %d\n", c.numero);
        printf("Saldo: %.2f\n", c.saldo);
        
        
        
        
        return 1;
    }
    
    
    
    

    printf("Conta nao Encontrada!\n");
    
    
    
    return 0;
}



int deposito() {
	
	
	
	
    int num;
    float valor;
    struct Conta c;




    printf("Numero da Conta: ");
    scanf("%d", &num);




    printf("Valor do Deposito: ");
    scanf("%f", &valor);
    
    
    

    if (!buscar_Conta(num, &c)) {
        printf("Conta nao Encontrada!\n");
        
        
        
        
        return 0;
        
        
    }



    c.saldo += valor;
    salvar_Conta(c);

    printf("Deposito Realizado!\n");
    
    
    
    
    return 1;
}






int saque() {
	
	
	
	
    int num;
    float valor;
    struct Conta c;



    printf("Numero da Conta: ");
    scanf("%d", &num);
    
    

    printf("Valor do Saque: ");
    scanf("%f", &valor);
    
    

    if (!buscar_Conta(num, &c)) {
        printf("Conta nao Encontrada!\n");
        
        
        return 0;
        
        
    }
    
    

    if (c.saldo < valor) {
    	
    	
        printf("Saldo Insuficiente!\n");
        
        
        return 0;
    }
    
    

    c.saldo -= valor;
    salvar_Conta(c);



    printf("Saque Realizado!\n");
    
    
    return 1;
}





int transferencia() {
	
	
	
    int origem, destino;
    float valor;
    struct Conta c1, c2;



    printf("Conta de Origem: ");
    scanf("%d", &origem);



    printf("Conta de Destino: ");
    scanf("%d", &destino);



    printf("Valor da Transferencia: ");
    scanf("%f", &valor);



    if (!buscar_Conta(origem, &c1)) {
    	
    	
        printf("Conta de Origem nao Encontrada!\n");
        
        
        return 0;
    }
    
    

    if (!buscar_Conta(destino, &c2)) {
    	
    	
        printf("Conta de Destino nao Encontrada!\n");
        
        
        
        return 0;
    }



    if (c1.saldo < valor) {
    	
    	
        printf("Saldo Insuficiente!\n");
        
        
        return 0;
    }
    
    

    c1.saldo -= valor;
    c2.saldo += valor;
    
    

    salvar_Conta(c1);
    salvar_Conta(c2);
    
    

    printf("Transferencia Realizada!\n");
    
    
    
    return 1;
}



int listar_Contas() {
	
	
	
	
    int senha;
    struct Conta c;

    printf("Senha do Administrador: ");
    scanf("%d", &senha);
    
    
    

    if (senha != senha_admin) {
    	
    	
        printf("Senha Incorreta!\n");
        
        
        
        return 0;
    }



    FILE *arq = fopen("contas.dat", "rb");


    if (arq == NULL) {
    	
    	
        printf("Nenhuma Conta Encontrada!\n");
        
        
        return 0;
    }
    
    


    printf("Contas:\n");

    while (fread(&c, sizeof(struct Conta), 1, arq)) {
    	
    	
        printf("%d | %s | Saldo: %.2f\n", c.numero, c.titular, c.saldo);
    }

    fclose(arq);
    
    
    
    return 1;
}



int main() {
	
	
    int opcao;

    do {
        printf("\nMENU\n");
        printf("1 - Criar Conta\n");
        printf("2 - Extrato\n");
        printf("3 - Deposito\n");
        printf("4 - Saque\n");
        printf("5 - Transferencia\n");
        printf("6 - Lista de Contas Salvas\n");
        printf("7 - Sair\n");
        printf("Opcao: ");



        scanf("%d", &opcao);
        getchar();



        if (opcao == 1) criar_Conta();
        else if (opcao == 2) extrato();
        else if (opcao == 3) deposito();
        else if (opcao == 4) saque();
        else if (opcao == 5) transferencia();
        else if (opcao == 6) listar_Contas();
        else if (opcao == 7) printf("ENCERRANDO......\n");
        else printf("Opcao Invalida!\n");
        
        
        
    } while (opcao != 7);



    return 0;
}