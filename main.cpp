#include <iostream>

#include<stdlib.h>
#include<time.h>

#include <sstream>
#include<string>
#include <utility>
#include <string.h>

using namespace std;

void division()
{
    cout<<"--------------------------------------------------" <<endl;
}

void PrintBoard(char arreglo[][6])
{
    for(int x = 0; x<6; x++)
    {
        for(int y = 0; y<6; y++)
        {
            char tmp = arreglo[x][y];
            if(y==5)
                cout<<tmp<<endl;
            else
                cout << tmp;
        }
    }
};

int randomizer()
{
    return 1+rand()%(6-1);
}

bool validar(int x, int y)
{
    if(x>=1 && x<=5 && y>=1 && y<=5)
        return true;
    cout<<"Datos invalidos, por favor ingrese posiciones dentro del rango (1-5)" <<endl;
    return false;
}

int despejarAdjacentes(int x, int y, char arreglo[][6],pair<int,int> minas[])
{
    int cont = 0;

    if(arreglo[x+1][y]!=NULL && (x!=0 || y!=0))
    {
        for(int z = 0; z<5; z++)
        {
            if(x+1==minas[z].first && y==minas[z].second)
            {
                cont++;
            }
        }
    }
    if(arreglo[x-1][y]!=NULL && (x!=0 || y!=0))
    {
        for(int z = 0; z<5; z++)
        {
            if(x-1==minas[z].first && y==minas[z].second)
            {
                cont++;
            }
        }
    }
    if(arreglo[x][y+1]!=NULL && (x!=0 || y!=0))
    {
        for(int z = 0; z<5; z++)
        {
            if(x==minas[z].first && y+1==minas[z].second)
            {
                cont++;
            }
        }
    }
    if(arreglo[x][y-1]!=NULL && (x!=0 || y!=0))
    {
        for(int z = 0; z<5; z++)
        {
            if(x==minas[z].first && y-1==minas[z].second)
            {
                cont++;
            }
        }
    }
    if(arreglo[x+1][y+1]!=NULL && (x!=0 || y!=0))
    {
        for(int z = 0; z<5; z++)
        {
            if(x+1==minas[z].first && y+1==minas[z].second)
            {
                cont++;
            }
        }
    }
    if(arreglo[x-1][y+1]!=NULL && (x!=0 || y!=0))
    {
        for(int z = 0; z<5; z++)
        {
            if(x-1==minas[z].first && y+1==minas[z].second)
            {
                cont++;
            }
        }
    }
    if(arreglo[x+1][y-1]!=NULL && (x!=0 || y!=0))
    {
        for(int z = 0; z<5; z++)
        {
            if(x+1==minas[z].first && y-1==minas[z].second)
            {
                cont++;
            }
        }
    }
    if(arreglo[x-1][y-1]!=NULL && (x!=0 || y!=0))
    {
        for(int z = 0; z<5; z++)
        {
            if(x-1==minas[z].first && y-1==minas[z].second)
            {
                cont++;
            }
        }
    }

    return cont;
}

void llenarAdjecentes(int x, int y, char arreglo[][6],pair<int,int> minas[]);

int Logic(int x, int y, char arreglo[][6],pair<int,int> minas[])
{

    if(arreglo[x][y]==NULL)
        return NULL;

    int cont = 0;

    cont += despejarAdjacentes(x,y,arreglo,minas);

    char dig = (char)(((int)'0')+cont);

    arreglo[x][y]= dig ;

//    if(cont==0)
//    {
//        llenarAdjecentes(x,y,arreglo,minas);
//    }

    return cont;
}

void llenarAdjecentes(int x, int y, char arreglo[][6],pair<int,int> minas[])
{
        if(arreglo[x+1][y]!=NULL && (x+1!=6 && y!=0))
            Logic(x+1,y,arreglo,minas);

        if(arreglo[x-1][y]!=NULL && (x-1!=0 && y!=0))
            Logic(x-1,y,arreglo,minas);

        if(arreglo[x][y+1]!=NULL && (x!=0 && y+1!=6))
            Logic(x,y+1,arreglo,minas);

        if(arreglo[x][y-1]!=NULL && (x!=0 && y-1!=0))
            Logic(x,y-1,arreglo,minas);

        if(arreglo[x+1][y+1]!=NULL && (x+1!=6 && y+1!=6))
            Logic(x+1,y+1,arreglo,minas);

        if(arreglo[x+1][y-1]!=NULL && (x+1!=6 && y-1!=0))
            Logic(x+1,y-1,arreglo,minas);

        if(arreglo[x-1][y+1]!=NULL && (x-1!=0 && y+1!=6))
            Logic(x-1,y+1,arreglo,minas);

        if(arreglo[x-1][y-1]!=NULL && (x-1!=0 && y-1!=0))
            Logic(x-1,y-1,arreglo,minas);
}

bool buscarMina(int x, int y,pair<int,int> minas[])
{
    for(int z = 0; z<5; z++)
    {
        if(x==minas[z].first && y==minas[z].second)
        {
            division();
            cout<<"Diste con una mina, perdiste!" <<endl;
            return true;
        }
    }
    return false;
}

bool minaExiste(int x, int y, pair<int,int> minas[])
{
    for(int z = 0; z<5; z++)
    {
        if(minas[z].first == x && minas[z].second == y)
            return true;
    }
    return false;
}

void revelarMinas(char arreglo[][6],pair<int,int> minas[])
{
    for(int z = 0; z<5; z++)
    {
        int x = minas[z].first;
        int y = minas[z].second;
        arreglo[x][y] = 'X';
    }
}

void imprimirMinas(pair<int,int> minas[])
{
    for(int y = 0; y<5; y++)
    {
        cout<<minas[y].first<< "," << minas[y].second<<endl;
    }
}

bool evaluarGane(char arreglo[][6])
{
    int cont = 0;
    for(int z = 1; z<6; z++)
    {
        for(int b = 1; b<6; b++)
        {
            if(arreglo[z][b] == '_')
                cont++;
        }
    }
    if(cont==5)
        return true;
    return false;
}

void Juego()
{
    srand(time(NULL));
    bool blowUp = false;

    char arreglo[6][6] = {{' ','1','2','3','4','5'},{'1','_','_','_','_','_'},{'2','_','_','_','_','_'},{'3','_','_','_','_','_'},{'4','_','_','_','_','_'},{'5','_','_','_','_','_'}};

    pair<int,int> minas[5];

    int llenar = 0;

    for(int y = 0; y<5; y++)
    {
        int Q = 0;
        int P = 0;
        do
        {
            Q = randomizer();
            P = randomizer();
        }
        while(minaExiste(Q,P,minas));

        minas[y] = make_pair(Q,P);
    }

    imprimirMinas(minas);
    revelarMinas(arreglo,minas);

    int posX=-1;
    int posY=-1;

    PrintBoard(arreglo);

    while(!blowUp)
    {
        do
        {
            division();
            cout<<"Ingrese la posicion x" <<endl;
            //cin>>posX;
            string j;
            getline(cin,j);
            stringstream(j) >> posX;
            cout<<"Ingrese la posicion y" <<endl;
            //cin>>posY;
            string k;
            getline(cin,k);
            stringstream(k) >> posY;
        }
        while(!validar(posX,posY));
        if(buscarMina(posX,posY,minas))
        {
            blowUp=true;
        }
        else
        {
            Logic(posX,posY,arreglo,minas);
            PrintBoard(arreglo);
            division();
            cout<<"0 = Zona segura" <<endl;
        }
        if(evaluarGane(arreglo))
        {
            cout<<"Encontraste todas las minas, ganaste!" <<endl;
            blowUp=true;
        }
        division();
    }
}

void menu()
{
    int num = 0;

    do
    {
        division();
        cout<< "1. Jugar!" <<endl;
        cout<< "2. Salir :(" <<endl;
        cout<<"Ingrese una opcion" <<endl;
//        cin>>num;
        string j;
        getline(cin,j);
        stringstream(j) >> num;
        switch(num)
        {
        case 1:
            division();
            Juego();
            break;
        case 2:
            division();
            cout<<"Muchas gracias por jugar, vuelve pronto!" <<endl;
            break;
        default:
            cout<<"Opcion invalida, porfavor escoja una opcion valida (1-2)" <<endl;
        }
    }
    while(num!=2);
}

int main()
{
    menu();

    return 0;
}
