/******************************************************/
/*             PROJETO I - IAED 2013/2014             */
/*                                                    */
/*      Jorge  Veiga            N75154                */
/*      Jose   Nogueira         N76218                */
/*      Joao   Figueiredo       N75741                */
/*                                                    */
/******************************************************/

/* ZONA 1: Diretivas pre-compilador, Tipos/Estruturas, Variaveis Globais */
#include <stdio.h>              /* */
#include <stdlib.h>             /* */
#define EXIT_SUCESS     0       /* */
#define EXIT_FAILURE    1       /* */
#define TAMANHO_NOME    10+1    /* Tamanho maximo para o nome dos produtos/materias-primas */
#define QT_P            5       /* Quantidade de produtos a considerar */
#define QT_MP           3       /* Quantidade de Materias Primas a considerar */

/* Estrutura do Tipo Produto */
typedef struct{
        char    nome[TAMANHO_NOME];     /* Nome do Produto */
        double  mp[3];                  /* Constituição do Produto em percentagem */
        double  perdas;                 /* Percentagem de perdas admissiveis */
        double  k_mo;                   /* Coeficiente de mao de obra */
        double  k_en;                   /* Coeficiente de energia */
        double  k_eq;                   /* Coeficiente de equipamentos */
        double  vendas;                 /* Vendas anuais do produto */
        double  preco;                  /* Preco do produto em e/ton */
} Produto;

/* Estrutura do Tipo Materia-Prima */
typedef struct{
        char    nome[TAMANHO_NOME];     /* Nome da Materia Prima */
        double  custo;                  /* Custo da Materia Prima em e/kg */
} MateriaPrima;

Produto         produtos[QT_P];         /* Vetor do tipo Produto que vai conter as informacoes dos 5 produtos */
MateriaPrima    mp[QT_MP];              /* Vetor do tipo MateriaPrima que vai conter as informacoes das 3 MateriasPrimas */
double          orcamento[5];           /* Vetor do tipo Double que contem os orcamentos dos custos A, B, C, D e E */
                                        /* Custo F nao tem orcamento */
                                        
/* ZONA 2: Funcoes Auxiliares (subcomandos) */

        /* COMANDO d i => identificacao dos produtos:
                introduz nome no vetor produtos
                imprime o nome no output */
void executa_d_i(){
        int i;
        for ( i = 0; i < QT_P; i++ ) {
                scanf("%s", produtos[i].nome);
                if( i != 0 ){
                        printf(" ");
                }
                printf("%s",produtos[i].nome);
        }
        printf("\n");
}

        /* COMANDO d j => identificacao das materias primas:
                introduz nome no vetor mp
                imprime o nome no output */
void executa_d_j(){
        int i;
        for ( i = 0; i < QT_MP; i++ ) {
                scanf("%s", mp[i].nome);
                if( i != 0 ){
                        printf(" ");
                }
                printf("%s", mp[i].nome);
        }
        printf("\n");
}

        /* COMANDO d y => custo unitario das materias primas:
                introduz valor no vetor mp */
void executa_d_y(){
        int i;
        for(i=0;i<QT_MP;i++){
                scanf("%lf", &mp[i].custo);
        }
}

        /* COMANDO d v => vendas anuais dos produtos:
                introduz valor no vetor produtos */
void executa_d_v(){
        int i;
        for (i=0; i<QT_P; i++){
                scanf("%lf",&produtos[i].vendas);
        }
}

        /* COMANDO d z => preco de venda unitario e/ton dos produtos:
                introduz valor no vetor produtos */
void executa_d_z(){
        int i;
        for (i=0; i<QT_P;i++){
                scanf("%lf",&produtos[i].preco);
        }
}

        /* COMANDO d p => perdas na producao:
                introduz perdas no vetor produtos */
void executa_d_p(){
        int i;
        for (i=0; i<QT_P;i++){
                scanf("%lf",&produtos[i].perdas);
        }
}

        /* COMANDO d m => coeficiente k_mo:
                introduz no vetor produtos */
void executa_d_m(){
        int i;
        for (i=0; i<QT_P;i++){
                scanf("%lf",&produtos[i].k_mo);
        }
}

        /* COMANDO d n => coeficiente k_en:
                introduz no vetor produtos */
void executa_d_n(){
        int i;
        for (i=0; i<QT_P;i++){
                scanf("%lf",&produtos[i].k_en);
        }
}

        /* COMANDO d q => coeficiente k_eq:
                introduz no vetor produtos */
void executa_d_q(){
        int i;
        for (i=0; i<QT_P;i++){
                scanf("%lf",&produtos[i].k_eq);
        }
}

        /* COMANDO d o => orcamento para os custos a,b,c,d,e:
                introduz num vetor orcamento */
void executa_d_o(){
        int i;
        for (i=0; i<QT_P;i++){
                scanf("%lf",&orcamento[i]);
        }
}

        /* COMANDO d c => composicao percentual dos produtos: 
                introduz valores no vetor produtos*/
void executa_d_c(){
        int i,e;
        for (i = 0; i < QT_P; i++) {
                for (e = 0; e < QT_MP; e++){
                        scanf("%lf", &produtos[i].mp[e]);
                }
        }
}

/* ZONA 3: Calcula Custos */

        /* Calcula e devolve o custo A:
                => Gastos gerais administratrivos, comerciais e financeiros
                relativos a amortizacao de equipamentos nao produtivos;
                Este custo e repartido uniformemente pela producao.
                
                => Custo A: orcamento / producao total anual (e/ton)
                
                orcamento do custo A: orcamento[0]
                producao total anual <= SUM(produtos[i].vendas) */
                
double calcula_custo_a(){
        double producao = 0;
        int i;
        for ( i = 0; i < QT_P; i++){
                producao = producao + produtos[i].vendas;
        }
        return orcamento[0] / producao;
}

        /* Calcula e devolve o custo B:
                => Vencimentos e encargos com pessoal de producao;
                Este custo e repartido de forma ponderada pela producao de cada produto,
                atendendo ao coenficiente de mao de obra (k_mo) e vendas anuais (vendas);
                mo (toneladas ponderadas) = SUM(k_mo[i]*vendas[i]) (0<=i<5)
                
                => Custo B: orcamento * k_mo / mo (e/ton)
                
                orcamento do custo B: orcamento[1]
                k_mo = produtos[i].k_mo */
                
double calcula_custo_b(int id){
        double mo = 0;
        int i;
        for (i=0; i<QT_P; i++) {
                mo = mo + produtos[i].k_mo*produtos[i].vendas;
        }
        return orcamento[1] * produtos[id].k_mo / mo;
}

        /* Calcula e devolve o custo C:
                => Energia eletrica gasta na producao
                Este custo e repartido de forma ponderada pela producao de cada produto,
                atendendo ao coenficiente de mao de obra (k_en) e vendas anuais (vendas);
                en (toneladas ponderadas) = SUM(k_en[i]*vendas[i]) (0<=i<5)
                
                => Custo C: orcamento * k_en / en(e/ton)
                
                orcamento do custo C: orcamento[2]
                k_en = produtos[i].k_en */
double calcula_custo_c(int id){
        double en = 0;
        int i;
        for (i = 0; i < QT_P; i++) {
                en = en + produtos[i].k_en * produtos[i].vendas;
        }
        return orcamento[2] * produtos[id].k_en / en;
}

        /* Calcula e devolve o custo D:
                => Amortizacao de maquinas e equipamentos de producao;
                Este custo e repartido de forma ponderada pela producao de cada produto,
                atendendo ao coenficiente de mao de obra (k_eq) e vendas anuais (vendas);
                eq (toneladas ponderadas) = SUM(k_eq[i]*vendas[i]) (0<=i<5)
                
                => Custo D: orcamento * k_eq / eq (e/ton)
                
                orcamento do custo D: orcamento[3]
                k_eq = produtos[i].k_eq */
double calcula_custo_d(int id){
        double eq = 0;
        int i;
        for (i=0; i < QT_P; i++){
                eq = eq + produtos[i].k_eq*produtos[i].vendas;
        }
        return orcamento[3] * produtos[id].k_eq / eq;;
}

        /* Calcula e devolve o custo E:
                => Embalagem das toneladas produzidas de todos os produtos
                Este custo e repartido uniformemente pela producao.
                
                => Custo E: orcamento / producao total anual (e/ton)
                
                orcamento do custo E: orcamento[4]
                producao total anual <= SUM(produtos[i].vendas) */
double calcula_custo_e(){
        double producao = 0;
        int i;
        for ( i = 0; i < QT_P; i++){
                producao = producao + produtos[i].vendas;
        }
        return orcamento[4] / producao;
}
        /* Calcula e devolve o custo F:
                => Materias primas;
                => Este custo nao tem orcamento, uma vez que depende do preco
                das materias primas e da constituicao dos produtos;
                => Pela mesma razao, o Custo F depende do id do produto
                
                => Custo F: SUM(M[i]*PrecoMP[i]) * 1000 / (100 - perdas) (e/ton)
                
                M[i] => Percentagem da Materia Prima i no produto (produto[i].mp[i])
                PrecoMP[i] => Preco da materia prima i (mp[i].custo)
                perdas => percentagem de perdas admissiveis (produto[i].perdas) */
double calcula_custo_f(int id){
        double f = 0;
        int i;
        for (i = 0; i < QT_MP; i++) {
                f = f + produtos[id].mp[i] * mp[i].custo;
        }
        return f * 1000 / (100 - produtos[id].perdas);
}

/* Funcao que executa o comando D
        Leitura de dados do input em 11 situacoes possiveis:
        => (i) identificacao dos produtos
                comando: d i str1 ... stri
                i = Quantidade de Produtos
        => (j) identificacao das materias primas
                comando: d j str1 ... stri
                i = Quantidade de Materias Primas
        => (y) custo unitario, e/kg, das materias primas
                comando: d y double1 ... doublei
                i = Quantidade de Materias Primas
        => (v) vendas anuais, ton
                comando: d v double1 ... doublei
                i = Quantidade de Produtos
        => (z) preco de venda unitario, e/ton, dos produtos
                comando: d z double1 ... doublei
                i = Quantidade de Produtos
        => (p) perdas na producao, %
                comando: d p double1 ... doublei
                i = Quantidade de Produtos
        => (m) coeficientes de ponderacao da mao de obra, k_mo
                comando: d m double1 ... doublei
                i = Quantidade de Produtos
        => (n) coeficientes de ponderacao do consumo de energia eletrica na producao, k_en
                comando: d n double1 ... doublei
                i = Quantidade de Produtos
        => (q) coeficientes de ponderacao da ocupacao de maquinas e equipamentos de producao, k_eq
                comando: d q double1 ... doublei
                i = Quantidade de Produtos
        => (o) orcamento para os custos A, B, C, D e E, euros
                comando: d o double1 ... doublei
                comando: d o orcamentoA orcamentoB orcamentoC orcamentoD orcamentoE
        => (c) composicao percentual dos produtos
                comando: d q double1 ... doublenr
                i - id produto
                k - id materia prima
                exemplo: nr = (i - 1) * k + k */
void executa_d(){
        char subcomando;
        getchar();                                      /* Le o espaco */
        scanf("%c ",&subcomando);                       /* Le o subcomando */
        switch (subcomando) {
                case 'i':
                        executa_d_i();          /* Executa o comando d i */
                        break;
                case 'j':
                        executa_d_j();                /* Executa o comando d j */
                        break;
                case 'y':
                        executa_d_y();                /* Executa o comando d y */
                        break;
                case 'v':
                        executa_d_v();          /* Executa o comando d v */
                        break;
                case 'z':
                        executa_d_z();          /* Executa o comando d z */
                        break;
                case 'p':
                        executa_d_p();          /* Executa o comando d p */
                        break;
                case 'm':
                        executa_d_m();          /* Executa o comando d m */
                        break;
                case 'n':
                        executa_d_n();          /* Executa o comando d n */
                        break;
                case 'q':
                        executa_d_q();          /* Executa o comando d q */
                        break;
                case 'o':
                        executa_d_o();         /* Executa o comando d o */
                        break;
                case 'c':
                        executa_d_c();          /* Executa o comando d c */
                        break;
                default:
                        printf("ERRO: Comando l %c desconhecido", subcomando); /* caso seja introduzido um comando desconhecido */
        }
}

/* Funcao que executa o comando C
        => Calcula os diferentes preco de custo (e/ton) e margem (%) para cada produto 

        => Formulas de calculo dos custos Total, industrial, e mp, embalagem e energia
        
                Custo Total (TOT)(e/ton): Soma de todos os custos associados a um produto.
                        Custo_TOT = Custo_A + Custo_B + Custo_C + Custo_D + Custo_E + Custo_F
                Custo Industrial (IND)(e/ton): Soma dos custos ligados diretamente a producao
                        Custo_IND = Custo_B + Custo_C + Custo_D + Custo_E + Custo_F
                Custo de materia-prima, embalagem e energia (MPEE)(e/ton): Soma dos custos 
                imediatos de producao; os custos B e D estao presentes, com ou sem producao
                na unidade fabril
                        Custo_MPEE = custo_C + Custo_E + Custo_F
        Input: N/A
        Output: 4 linhas => Formato: id_linha custo1 ... custoi
                        cTOT cTOT1 ... cTOTi
                        M marg1 ... margi
                        cIND cind1 ... cindi
                        cmpee cmpee1 ... cmpeei */
void executa_c(){
        int i;
        double custo;
        double soma[5];
        double producao = 0;
        for ( i = 0; i < QT_P; i++){
                producao = producao + produtos[i].vendas;
        }
        printf("cTOT");
        for (i=0; i < QT_P; i++){
                soma[i] = calcula_custo_a() + calcula_custo_b(i) + calcula_custo_c(i) + calcula_custo_d(i) + calcula_custo_e() + calcula_custo_f(i);
                printf(" %.2f",soma[i]);
        }
        printf("\nM");
        for (i = 0; i < QT_P;i++){
                printf(" %.2f", ( produtos[i].preco - soma[i] ) * 100 / produtos[i].preco );
        }
        printf("\ncIND");
        for (i=0,custo=0; i < QT_P; i++){
                custo = calcula_custo_b(i) + calcula_custo_c(i) + calcula_custo_d(i) + calcula_custo_e() + calcula_custo_f(i);
                printf(" %.2f",custo);
        }
        printf("\ncMPEE");
        for (i=0,custo=0; i < QT_P; i++){
                custo = calcula_custo_c(i) + calcula_custo_e() + calcula_custo_f(i);
                printf(" %.2f",custo);
        }
        printf("\n");
}

/* Funcao que executa o comando W
        => Calcula valores de cada um dos custos (A a F) para um determinado produto.

        Input:  inti => id do produto
                        w inti
                        
        Output: 1 Linha => Formato: W inti Custo_A ... Custo_F i */
void executa_w(int id){
        printf("W %s A:%.2f ",produtos[id].nome, calcula_custo_a());
        printf("B:%.2f ",calcula_custo_b(id));
        printf("C:%.2f ",calcula_custo_c(id));
        printf("D:%.2f ",calcula_custo_d(id));
        printf("E:%.2f ",calcula_custo_e());
        printf("F:%.2f\n",calcula_custo_f(id));

}

/* Funcao que executa o comando T
        => Calcula valores de custos e vendas anuais totais

        Input:  N/A
                        
        Output: 1 Linha => Formato: id custo venda lucro margem
                id: 'T'
                custo: custo total da producao das vendas = SUM(cTOTi * Vendai)
                venda: o valor da venda da producao = SUM(pVendai * Vendai)
                lucro: venda - custo (e)
                margem: (venda - custo) * 100 / venda */
void executa_t(){
        int i;
        double soma[5];
        double custo,preco;
        for ( i=0, custo = 0; i < QT_P; i++){
                soma[i] = calcula_custo_a() + calcula_custo_b(i) + calcula_custo_c(i) + calcula_custo_d(i) + calcula_custo_e() + calcula_custo_f(i);
        }
        for (i = 0; i < QT_P; i++){
                custo = custo + soma[i] * produtos[i].vendas;
        }
        printf("T %.2f ",custo);
        for (i = 0, preco = 0; i < QT_P; i++){
                preco = preco + produtos[i].preco * produtos[i].vendas;
        }
        printf("%.2f ", preco);
        printf("%.2f ", (preco - custo) );
        printf("%.2f\n", ((preco - custo) * 100 / preco));
}

/* Funcao que executa o comando V
        => Avalia o interesse de uma venda com um determinado desconto

        Input:  int1: id do produto
                float1: desconto em %
                
                v int1 float1
                        
        Output: 1 Linha => Formato: id produto margem desconto margem_d decisao
                id: 'VD'
                produto: nome do produto
                margem: margem da venda do produto em causa, relativamente ao preco tabelado
                desconto: o valor float1 do input
                margem_d: margem da venda do produto em causa, apos o desconto sobre o preco tabelado
                decisao: para o produto p em causa, seja pVenda_d o preco de venda unitario com o desconto
                        decisao = 'tot'  se pCusto_TOT  <= pVenda_d
                        decisao = 'ind'  se pCusto_IND  <= pVenda_d    <= pCusto_TOT
                        decisao = 'mpee' se pCusto_MPEE <= pVenda_d    <= pCusto_IND
                        decisao = '0'    se pVenda_d    <= pCusto_MPEE
                */
void executa_v(int id, double desconto){
        double custo, cind, cmpee, pVenda_d, margem_d, margem;
        cmpee = calcula_custo_c(id) + calcula_custo_e() + calcula_custo_f(id);
        cind = cmpee + calcula_custo_b(id) + calcula_custo_d(id);
        custo = cind + calcula_custo_a();
        pVenda_d = (produtos[id].preco * (100 - desconto) / 100);
        margem = ((produtos[id].preco - custo) * 100 / produtos[id].preco);
        margem_d = (pVenda_d - custo) * 100 / pVenda_d;
        printf("VD %s %.2f %.2f %.2f ", produtos[id].nome, margem, desconto, margem_d);
        if(custo <= pVenda_d){
                printf("%s\n","tot");
        }else if ( cind <= pVenda_d && pVenda_d < custo ) {
                printf("%s\n","ind");
        }else if ( cmpee <= pVenda_d && pVenda_d < cind ) {
                printf("%s\n","mpee");
        }else if ( pVenda_d < cmpee ) {
                printf("%s\n","0");
        }
}
/* Ordena os produtos de acordo com os custos
        custos[] => Vetor com os custos a serem ordenados
        ids[]    => Vetor com os ids que vao ser ordenados de acordo com os custos
        tam      => tamanho dos vetores */
void insertionSort(double custos[], int ids[], int tam) {
        int i, j, eleito;
        for (i = 1; i < tam; i++){
                eleito = custos[i];
                j = i - 1;
                while ((j>=0) && (eleito < custos[j])) {
                        custos[j+1] = custos[j];
                        ids[j+1] = ids[j];
                        j--;
                }
                custos[j+1] = eleito;
                ids[j+1] = i;
        }
}
/* Funcao que executa o comando X
        => Fecho do programa: duas situacoes possiveis

        Input:  int: 0 ou 1
                x int
        se int = 0:
                Accao: Nenhuma
                Output: Nenhum
        se int = 1:
                Accao: o programa e terminado
                Output: 5 (Quantidade de Produtos) Linhas
                Formato:
                produtoj pcustoj
                ...
                produtok pcustok
*/
void executa_x(int comando_nr){
        if(comando_nr == 1){
                double custo[QT_P],custo_ord[QT_P];
                int i, ids[QT_P], id;
                for (id=0; id < QT_P; id++){
                        ids[id] = id;
                        custo[id] = calcula_custo_a() + calcula_custo_b(id) + calcula_custo_c(id) + calcula_custo_d(id) + calcula_custo_e() + calcula_custo_f(id);
                        custo_ord[id] = custo[id];
                }
                insertionSort(custo_ord,ids,5);
                for (i=0; i < QT_P; i++){
                        id = ids[i];
                        printf("%s %.2f\n",produtos[id].nome,custo[id]);
                }
        }
}

int main(){
        char            comando;
        int             comando_nr;
        double          desconto;
        while(1) {
                comando = getchar();
                while ( comando == '\n' || comando == ' '){
                        comando = getchar(); /* le o comando a executar */
                }
                switch(comando){
                        case 'd':
                                executa_d();
                                break;
                        case 'c':
                                executa_c();
                                break;
                        case 'w':
                                scanf("%d", &comando_nr);
                                executa_w(comando_nr-1);
                                break;
                        case 't':
                                executa_t();
                                break;
                        case 'v':
                                scanf("%d", &comando_nr);
                                scanf("%lf", &desconto);
                                executa_v(comando_nr-1, desconto);
                                break;
                        case 'x':
                                scanf("%d", &comando_nr);
                                executa_x(comando_nr);
                                return EXIT_SUCESS;
                        case ' ':
                                break;
                        default:
                                printf("ERRO: Comando %c desconhecido\n", comando);
                }
                getchar();
        }
        return EXIT_FAILURE;
}
