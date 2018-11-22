#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

#define linha 16
#define coluna 80
#define tamSemaf 8

struct Semaforo
{
    int x[5];
    int y[5];
};

char mapa[linha][coluna];
int vetorLogica[3][8] = {{1,1,1,1,0,0,0,1},{0,0,0,0,0,1,1,1},{1,0,1,1,1,0,1,0}};

void clrscr()
{
    system("@cls||clear");
}

void inicializaMapa()
{
    int i, j;
    char ch;
    char url[]="mapa.txt";
    FILE *arq;
    arq = fopen(url,"r");
    if ((arq = fopen(url,"r") )==NULL)
    {
        printf("null\n");
    }
    else{
        for (i=0; i<linha; i++)
        {
            for (j=0; j<coluna; j++)
            {
                ch = fgetc(arq);
                mapa[i][j] = ch;
            }
            ch=fgetc(arq);
        }
    }
        fclose(arq);
}

void definePosicoes(struct Semaforo semaforo[])
{
    FILE *arq;
    int i, j;
    arq = fopen("posicoes.txt", "r");
    for (i=0; i<tamSemaf; i++)
    {
        for (j=0; j<5; j++)
        {
            fscanf(arq, "%d", &semaforo[i].x[j]);
            fscanf(arq, "%d", &semaforo[i].y[j]);
        }
    }
    fclose(arq);
}

void imprimeMapa()
{
    int i, j;
    clrscr();
    for (i=0; i<linha; i++)
    {
        for (j=0; j<coluna; j++)
        {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}

void zeraSemaforos(struct Semaforo semaforo[])
{
    int i, x, y, xp, yp;
    for (i=0; i<tamSemaf; i++)
    {
        x = semaforo[i].x[0];
        y = semaforo[i].y[0];
        xp = semaforo[i].x[3];
        yp = semaforo[i].y[3];
        mapa[x][y] = ' ';
        mapa[x+1][y] = ' ';
        mapa[x+2][y] = ' ';
        mapa[xp][yp] = ' ';
        mapa[xp+1][yp] = ' ';
    }
}

void defineVetor(int logica, int vetor[])
{
    int i;
    for (i=0;i<tamSemaf; i++)
    {
        vetor[i]=vetorLogica[logica][i];
    }
}

void defineSemaforos(struct Semaforo semaforo[], int logica)
{
    int vetor[tamSemaf];
    defineVetor(logica, vetor);
    int i, xc, yc, xp, yp;

    zeraSemaforos(semaforo);
    for (i=0; i<tamSemaf; i++)
    {
        xc = semaforo[i].x[0];
        yc = semaforo[i].y[0];
        xp = semaforo[i].x[3];
        yp = semaforo[i].y[3];
        if (vetor[i] == 1)
        {
            mapa[xc+2][yc] = 'X';
            mapa[xp][yp] = 'X';
        }
        else if (vetor[i] == 0)
        {
            mapa[xc][yc] = 'X';
            mapa[xp+1][yp] ='X';
        }
        else
        {
            mapa[xc+1][yc] = 'X';
        }
    }
}

void alerta(struct Semaforo semaforo[], int logica)
{
    int vetor[tamSemaf];
    defineVetor(logica, vetor);
    int i, xc, yc, xp, yp, logicaAux;
    logicaAux = logica +1;
    if (logicaAux >=3)
        logicaAux = 0;
    zeraSemaforos(semaforo);
    for (i=0; i<tamSemaf; i++)
    {
        xc = semaforo[i].x[0];
        yc = semaforo[i].y[0];
        xp = semaforo[i].x[3];
        yp = semaforo[i].y[3];
        if (vetor[i] == 1 && vetorLogica[logicaAux][i]==0)
        {
            mapa[xc+1][yc] = 'X';
            mapa[xp][yp] = 'X';
        }
        else if (vetor[i] == 1 && vetorLogica[logicaAux][i]==1)
        {
            mapa[xc+2][yc] = 'X';
            mapa[xp][yp] ='X';
        }
        else
        {
            mapa[xc][yc] = 'X';
            mapa[xp+1][yp] = 'X';
        }
    }
}

void alertaSemaforoX(int numSemaforo, struct Semaforo semaforo[])
{
    int xc, yc, xp, yp;
    xc = semaforo[numSemaforo].x[0];
    yc = semaforo[numSemaforo].y[0];
    xp = semaforo[numSemaforo].x[3];
    yp = semaforo[numSemaforo].y[3];
    mapa[xc][yc] = ' ';
    mapa[xc+1][yc] = 'X';
    mapa[xc+2][yc] = ' ';
    mapa[xp][yp] = 'X';
    mapa[xp+1][yp] = ' ';
}

void ligaSemaforoX(int numSemaforo, struct Semaforo semaforo[])
{
    int xc, yc, xp, yp;
    xc = semaforo[numSemaforo].x[0];
    yc = semaforo[numSemaforo].y[0];
    xp = semaforo[numSemaforo].x[3];
    yp = semaforo[numSemaforo].y[3];
    mapa[xc][yc] = ' ';
    mapa[xc+1][yc] = ' ';
    mapa[xc+2][yc] = 'X';
    mapa[xp][yp] = 'X';
    mapa[xp+1][yp] = ' ';
}

void fechaSemaforoX(int numSemaforo, struct Semaforo semaforo[])
{
    int xc, yc, xp, yp;
    xc = semaforo[numSemaforo].x[0];
    yc = semaforo[numSemaforo].y[0];
    xp = semaforo[numSemaforo].x[3];
    yp = semaforo[numSemaforo].y[3];
    mapa[xc][yc] = 'X';
    mapa[xc+1][yc] = ' ';
    mapa[xc+2][yc] = ' ';
    mapa[xp][yp] = ' ';
    mapa[xp+1][yp] = 'X';

}
void abreCarro1(struct Semaforo semaforo[])
{
    alertaSemaforoX(5, semaforo);
    imprimeMapa();
    sleep(2);
    fechaSemaforoX(5, semaforo);
    ligaSemaforoX(0, semaforo);
    imprimeMapa();
    sleep(3);
}

void abreCarro2(struct Semaforo semaforo[])
{
    alertaSemaforoX(5, semaforo);
    imprimeMapa();
    sleep(2);
    fechaSemaforoX(5, semaforo);
    ligaSemaforoX(1, semaforo);
    imprimeMapa();
    sleep(3);
}

void abreCarro3(struct Semaforo semaforo[])
{
    alertaSemaforoX(5, semaforo);
    imprimeMapa();
    sleep(2);
    fechaSemaforoX(5, semaforo);
    ligaSemaforoX(2, semaforo);
    ligaSemaforoX(3, semaforo);
    imprimeMapa();
    sleep(3);
}

void abreCarro4(struct Semaforo semaforo[])
{
    alertaSemaforoX(2, semaforo);
    alertaSemaforoX(5, semaforo);
    imprimeMapa();
    sleep(2);
    fechaSemaforoX(2, semaforo);
    fechaSemaforoX(5, semaforo);
    ligaSemaforoX(4, semaforo);
    ligaSemaforoX(0, semaforo);
    imprimeMapa();
    sleep(3);
}
void abreCarro6(struct Semaforo semaforo[])
{
    int i;
    for (i=0; i<5; i++)
        alertaSemaforoX(i, semaforo);
    imprimeMapa();
    sleep(2);
    for (i=0; i<5; i++)
        fechaSemaforoX(i, semaforo);
    ligaSemaforoX(5, semaforo);
    imprimeMapa();
    sleep(3);
}
void fechaCarro(int numero, struct Semaforo semaforo[])
{
    alertaSemaforoX(numero, semaforo);
    if (numero == 2 || numero == 5)
        alertaSemaforoX(numero+1, semaforo);
    imprimeMapa();
    sleep(2);
    if (numero == 2 || numero == 5)
        fechaSemaforoX(numero+1, semaforo);
    fechaSemaforoX(numero, semaforo);
    imprimeMapa();
    sleep(3);
}
void abrePedestre(int numero, struct Semaforo semaforo[])
{
    alertaSemaforoX(numero, semaforo);
    if (numero == 2 || numero == 5)
        alertaSemaforoX(numero+1, semaforo);
    imprimeMapa();
    sleep(2);
    if (numero == 3 || numero == 6)
        fechaSemaforoX(numero+1, semaforo);
    fechaSemaforoX(numero, semaforo);
    imprimeMapa();
    sleep(3);
}
void fechaPedestre(int numero, struct Semaforo semaforo[])
{
    int xp, yp;
    xp = semaforo[numero].x[3];
    yp = semaforo[numero].y[3];
    mapa[xp][yp] = 'X';
    mapa[xp+1][yp] = ' ';
    if (numero == 2 || numero == 5)
    {
        xp = semaforo[numero+1].x[3];
        yp = semaforo[numero+1].y[3];
        mapa[xp][yp] = 'X';
        mapa[xp+1][yp] = ' ';
    }
}
void abreOnibus(struct Semaforo semaforo[])
{
    alertaSemaforoX(5, semaforo);
    imprimeMapa();
    sleep(2);
    fechaSemaforoX(5, semaforo);
    ligaSemaforoX(2, semaforo);
    ligaSemaforoX(3, semaforo);
    imprimeMapa();
    sleep(3);
}

void alertaPedestre(int numero, struct Semaforo semaforo[])
{
    int xp, yp, i;
    xp = semaforo[numero].x[3];
    yp = semaforo[numero].y[3];
    mapa[xp+1][yp] = ' ';
    for (i=0; i<4; i++)
    {
        mapa[xp][yp] = ' ';
        imprimeMapa();
        sleep(0.7);
        mapa[xp][yp] = 'X';
        imprimeMapa();
        sleep(0.7);
    }
}
void verificaComando(char comando[], struct Semaforo semaforo[])
{
    if (strcmp(comando, "abre carro 1") == 0)
        abreCarro1(semaforo);
    else if (strcmp(comando, "abre carro 2") == 0)
        abreCarro2(semaforo);
    else if (strcmp(comando, "abre carro 3") == 0)
        abreCarro3(semaforo);
    else if (strcmp(comando, "abre carro 4") == 0)
        abreCarro4(semaforo);
    else if (strcmp(comando, "abre carro 6") == 0)
        abreCarro6(semaforo);
    else if (strcmp(comando, "fecha carro 1") == 0)
        fechaCarro(0, semaforo);
    else if (strcmp(comando, "fecha carro 2") == 0)
        fechaCarro(1, semaforo);
    else if (strcmp(comando, "fecha carro 3") == 0)
        fechaCarro(2, semaforo);
    else if (strcmp(comando, "fecha carro 4") == 0)
        fechaCarro(4, semaforo);
    else if (strcmp(comando, "fecha carro 6") == 0)
        fechaCarro(5, semaforo);
    else if (strcmp(comando, "fecha carro 7") == 0)
        fechaCarro(7, semaforo);
    else if (strcmp(comando, "abre pedestre 1") == 0)
        abrePedestre(0, semaforo);
    else if (strcmp(comando, "abre pedestre 2") == 0)
        abrePedestre(1, semaforo);
    else if (strcmp(comando, "abre pedestre 3") == 0)
        abrePedestre(2, semaforo);
    else if (strcmp(comando, "abre pedestre 4") == 0)
        abrePedestre(4, semaforo);
    else if (strcmp(comando, "abre pedestre 6") == 0)
        abrePedestre(5, semaforo);
    else if (strcmp(comando, "abre pedestre 7") == 0)
        abrePedestre(7, semaforo);
    else if (strcmp(comando, "fecha pedestre 1") == 0)
        fechaPedestre(0, semaforo);
    else if (strcmp(comando, "fecha pedestre 2") == 0)
        fechaPedestre(1, semaforo);
    else if (strcmp(comando, "fecha pedestre 3") == 0)
        fechaPedestre(2, semaforo);
    else if (strcmp(comando, "fecha pedestre 4") == 0)
        fechaPedestre(4, semaforo);
    else if (strcmp(comando, "fecha pedestre 6") == 0)
        fechaPedestre(5, semaforo);
    else if (strcmp(comando, "fecha pedestre 7") == 0)
        fechaPedestre(7, semaforo);
    else if (strcmp(comando, "abre onibus") == 0)
        abreOnibus(semaforo);
    else if (strcmp(comando, "alerta pedestre 1") == 0)
        alertaPedestre(0, semaforo);
    else if (strcmp(comando, "alerta pedestre 2") == 0)
        alertaPedestre(1, semaforo);
    else if (strcmp(comando, "alerta pedestre 3") == 0)
        alertaPedestre(2, semaforo);
    else if (strcmp(comando, "alerta pedestre 4") == 0)
        alertaPedestre(4, semaforo);
    else if (strcmp(comando, "alerta pedestre 6") == 0)
        alertaPedestre(5, semaforo);
    else if (strcmp(comando, "alerta pedestre 7") == 0)
        alertaPedestre(7, semaforo);
}
int main()
{
    struct Semaforo semaforo[9];
    int logica=0;
    char comando[30];
    inicializaMapa();
    definePosicoes(semaforo);
    while(1)
    {
        defineSemaforos(semaforo, logica);
        imprimeMapa();
        if(kbhit())
        {
            gets(comando);
            verificaComando(comando, semaforo);
        }
        sleep(4);
        alerta(semaforo, logica);
        imprimeMapa();
        sleep(3);
        logica++;
        if (logica >= 3)
            logica =0;
    }

}



