#include<bits/stdc++.h>
#include <graphics.h>
#include <string>
#include<sstream>
#include<math.h>
#include <stdlib.h>
#include <windows.h.>
#include <conio.h>

using namespace std;

//ifstream f("date.in");
using namespace std;
//ofstream g("date.out");


struct punct//structura pentru definirea pixelilor
{
    int x,y;
};

punct coord(int x, int y) //Andrei
{
    punct a;
    a.x = x;
    a.y = y;
    return a;
}

punct operator+(punct a, punct b) //Andrei
{
    punct c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

struct Mouse //Andrei
{
    int x, y;
    bool LMBClick, RMBClick;
    bool incaApasat, released;
} mouse;

struct Window //Andrei
{
    int w,h;
} window;

void mouseUpdate(Mouse *mouse) //Andrei
{
    mouse -> x = mousex();
    mouse -> y = mousey();

    mouse -> LMBClick = mouse -> RMBClick = mouse -> released = false;

    if(ismouseclick(WM_LBUTTONDOWN))
        {
            mouse -> LMBClick = true;
            mouse -> incaApasat = true;
            clearmouseclick(WM_LBUTTONDOWN);
        }

    if(ismouseclick(WM_LBUTTONUP))
        {
            mouse -> incaApasat = false;
            mouse -> released = true;
            clearmouseclick(WM_LBUTTONUP);
        }

    if(ismouseclick(WM_RBUTTONDOWN))
        {
            mouse -> RMBClick = true;
            clearmouseclick(WM_RBUTTONDOWN);
        }
}

int buttonNumber;

char sep[] = " `!@#$%^&*()_-=+,<>/?;:\'\"[]{}~"; //Andrei
char s[1000]; //Andrei
vector<int> values; //Andrei
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Andrei

///VECTORI

int latura_celula_vector( int nr_elemente, int v[101]) //Alex
{
    //functie care determina lungimea laturei unei celule(patrat)
    int latura=0;
    for(int i=1; i<=nr_elemente; i++)
        {
            char cuv[256];//vom transforma numarul din int in char
            std::sprintf(cuv, "%d",v[i]);

            if(textwidth(cuv)>latura)//latura va fi reprezentata de lungimea maxima (in pixeli) a continuturilor celulelor
                latura=textwidth(cuv);
        }
    if(latura<=10)
        return latura+30;
    return latura+20;// returnam o latura putin mai mare pentru a afisa numarul din celula corespunzator
}

// functie cu care desenam in fereastra grafica un vector.
// plecam de la punctle coltului din stanga ale primului patratel
//lungimea laturii va putea fi aleasa de utilizator
void desenare_vector(punct punct_plecare,int latura, int nr_elemente, int v[101]) //Alex
{
    settextstyle(BOLD_FONT,HORIZ_DIR,1);

    int x,y;
    x=punct_plecare.x;
    y=punct_plecare.y;

    for(int i=1; i<=nr_elemente; i++,x+=latura)
        {
            rectangle(x,y,x+latura,y+latura);//vom desena celule(patrate) consecutive
            char cuv[256];//vom transforma numarul din int in char
            std::sprintf(cuv, "%d",v[i]);
            // setcolor(GREEN);
            outtextxy(x+5,y+latura/2+5,cuv);//afisam continutul celulei
            delay(250);
            //setcolor(WHITE);
        }

}


//reprezentarea grafica a functiei ce aduna doi vectori
// plecam de la premisa ca cei doi vectori au aceeasi dimensiune
//vom creea un nou vector rezultat
///urmeaza sa salvez vectoru asta intr un fisier(maybe)
void adunare_vectori(int vector1[],int vector2[],int vector3[],int n) //Alex
{
    for(int i=1; i<=n; i++)
        vector3[i]=vector1[i]+vector2[i];

    punct x;
    int latura;

    latura=max(max(latura_celula_vector(n,vector1),latura_celula_vector(n,vector2)),latura_celula_vector(n,vector3));//gasesc latura maxima a celor trei vectori pentru a nu avea dimensiuni diferite ale celulelor

    x.x=50;
    x.y=200;
    desenare_vector(x,latura,n,vector1);//desenez primul vector
    delay(750);
    x.x=x.x+latura*n+20;
    readimagefile("plus1.jpg", x.x, x.y, x.x+latura,x.y+latura);//inserez semnul plus
    delay(1000);
    x.x+=latura+20;
    desenare_vector(x,latura,n,vector2);//desenes al doilea vector
    delay(750);
    x.x=x.x+latura*n+20;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);//inserez semnul egal
    delay(1000);
    x.x+=latura+20;
    desenare_vector(x,latura,n,vector3);
    //desenez vectorul rezultat
}

void inmultire_vector_scalar(int v[], int vrez[], int n, int scalar) //Andrei
{
    for(int i=1; i <= n; i++)
        vrez[i] = v[i] * scalar;

    punct x = coord(50, 200);
    int latura = max(latura_celula_vector(n, v), latura_celula_vector(n, vrez));
    desenare_vector(x, latura, n, v);
    delay(750);
    x.x = x.x + latura * n + 20;
    readimagefile("star.jpg", x.x, x.y, x.x + latura, x.y + latura);
    delay(1000);
    x.x += latura + 20;
    x.y += latura / 2 + 5;
    char cuv[256];
    sprintf(cuv, "%d", scalar);
    outtextxy(x.x, x.y, cuv);
    delay(1000);
    x.x+=latura;
    x.y = x.y - 5 - latura / 2;
    readimagefile("equal.jpg", x.x, x.y, x.x + latura, x.y + latura);
    delay(1000);
    x.x += latura + 20;
    desenare_vector(x, latura, n, vrez);
}

//reprezentarea grafica a functiei ce scade doi vectori
void scadere_vectori(int vector1[],int vector2[],int vector3[],int n) //Alex
{
    for(int i=1; i<=n; i++)
        vector3[i]=vector1[i]-vector2[i];

    punct x;
    int latura;

    latura=max((latura_celula_vector(n,vector1),latura_celula_vector(n,vector2)),latura_celula_vector(n,vector3));

    x.x=50;
    x.y=200;
    desenare_vector(x,latura,n,vector1);
    delay(750);
    x.x=x.x+latura*n+20;
    readimagefile("minus.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=latura+20;
    desenare_vector(x,latura,n,vector2);
    delay(750);
    x.x=x.x+latura*n+20;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=latura+20;
    desenare_vector(x,latura,n,vector3);
}

//reprezentarea grafica a functiei ce aduna doi vectori
void inmultire_vectori(int vector1[],int vector2[],int vector3[],int n) //Alex
{
    for(int i=1; i<=n; i++)
        vector3[i]=vector1[i]*vector2[i];

    punct x;
    int latura;

    latura=max((latura_celula_vector(n,vector1),latura_celula_vector(n,vector2)),latura_celula_vector(n,vector3));

    x.x=50;
    x.y=200;
    desenare_vector(x,latura,n,vector1);
    delay(750);
    x.x=x.x+latura*n+20;
    readimagefile("star.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=latura+20;
    desenare_vector(x,latura,n,vector2);
    delay(750);
    x.x=x.x+latura*n+20;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=latura+20;
    desenare_vector(x,latura,n,vector3);
}

//reprezentarea grafica a functiei ce aduna doi vectori
void impartire_vectori(int vector1[],int vector2[],int vector3[],int n) //Alex
{
    for(int i=1; i<=n; i++)
        vector3[i]=vector1[i]/vector2[i];

    punct x;
    int latura;

    latura=max((latura_celula_vector(n,vector1),latura_celula_vector(n,vector2)),latura_celula_vector(n,vector3));

    x.x=50;
    x.y=200;
    desenare_vector(x,latura,n,vector1);
    delay(750);
    x.x=x.x+latura*n+20;
    readimagefile("divide.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=latura+20;
    desenare_vector(x,latura,n,vector2);
    delay(750);
    x.x=x.x+latura*n+20;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=latura+20;
    desenare_vector(x,latura,n,vector3);


}


//functie care reprezinta grafic suma elementelor unui vector
void suma_elemente_vector(int v[101], int n) //Alex
{
    //calculez suma
    int s=0;
    for(int i=1; i<=n; i++)
        s+=v[i];

    punct x;
    int latura;

    latura=latura_celula_vector(n,v);

    x.x=50;
    x.y=200;
    desenare_vector(x,latura,n,v);
    delay(750);
    x.x+=latura*7/8;//calcule matematice
    x.y+=latura+10;
    for(int i=1; i<n; i++,x.x+=latura)
        {
            readimagefile("plus1.jpg",x.x,x.y,x.x+latura/4,x.y+latura/4);
            delay(250);
        }

    x.x+=latura;
    x.y-=latura+10;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura/2,x.y+latura/2);
    delay(1000);
    x.x+=latura;
    x.y+=latura/2;
    char cuv[256];
    std::sprintf(cuv, "%d",s);
    outtextxy(x.x,x.y,cuv);
}


//functie asemanatoare pentru produsul elementelor unui vector
void produs_elemente_vector(int v[101], int n) //Alex
{
    int p=1;
    for(int i=1; i<=n; i++)
        p*=v[i];

    punct x;
    int latura;

    latura=latura_celula_vector(n,v);

    x.x=50;
    x.y=200;
    desenare_vector(x,latura,n,v);
    delay(750);
    x.x+=latura*7/8;
    x.y+=latura+10;
    for(int i=1; i<n; i++,x.x+=latura)
        {
            readimagefile("star.jpg",x.x,x.y,x.x+latura/4,x.y+latura/4);
            delay(250);
        }

    x.x+=latura;
    x.y-=latura;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura/2,x.y+latura/2);
    delay(1000);
    x.y+=latura/2;
    x.x+=latura;
    char cuv[256];
    std::sprintf(cuv, "%d",p);
    outtextxy(x.x,x.y,cuv);
}

///urmeaza trei functii pentru sortarea unui vector si reprezentarea acesteia in fereastra grafica


void sortare_selectie_directa(int v[101], int n, int tip) //Alex
// cresc:tip=1; desc:tip=-1
{
    punct x;
    x.x=50;
    x.y=200;
    int latura,i;
    latura=latura_celula_vector(n,v);

    x.y+=latura+10;//vectorul de la care am plecat

    int v1[101];
    for(int i=1; i<=n; i++)
        v1[i]=v[i];

    for(int i=1; i<n; i++)
        for(int j=i+1; j<=n; j++)
            if(v[i]*tip>v[j]*tip)
                {
                    swap(v[i],v[j]);

                    punct y;
                    y.x=50;
                    y.y=200;
                    desenare_vector(y,latura,n,v1);

                    x.x=50;
                    for(int k=1; k<=n; k++,x.x+=latura)
                        {
                            if(k==i||k==j)
                                setcolor(YELLOW);//evidentiez elementele interschimbarii
                            rectangle(x.x,x.y,x.x+latura,x.y+latura);
                            char cuv[256];//vom transforma numarul din int in char
                            std::sprintf(cuv, "%d",v[k]);
                            outtextxy(x.x+5,x.y+latura/2-5,cuv);
                            setcolor(WHITE);
                        }

                    delay(500);
                    cleardevice();
                }

    punct y;
    y.x=50;
    y.y=200;
    desenare_vector(y,latura,n,v1);

    x.x=50;
    setcolor(RED);
    desenare_vector(x,latura,n,v);//afisez vectorul obtinut, cu rosu
    setcolor(WHITE);


}

void sortare_bubble(int v[101], int n, int tip) //Alex
{
    punct x;
    x.x=50;
    x.y=250;
    int latura,i;
    latura=latura_celula_vector(n,v);


    int v1[101];
    for(int i=1; i<=n; i++)
        v1[i]=v[i];

    int terminat=0;
    while(!terminat)
        {
            terminat=1;
            for(int i=1; i<n; i++)
                if(v[i]*tip>v[i+1]*tip)
                    {
                        int aux=v[i];
                        v[i]=v[i+1];
                        v[i+1]=aux;
                        terminat=0;


                        punct y;
                        y.x=50;
                        y.y=200;
                        desenare_vector(y,latura,n,v1);


                        x.x=50;
                        for(int k=1; k<=n; k++,x.x+=latura)
                            {
                                if(k==i||k==i+1)
                                    setcolor(YELLOW);
                                rectangle(x.x,x.y,x.x+latura,x.y+latura);
                                char cuv[256];//vom transforma numarul din int in char
                                std::sprintf(cuv, "%d",v[k]);
                                outtextxy(x.x+5,x.y+latura/2-5,cuv);
                                setcolor(WHITE);
                            }

                        delay(500);
                        cleardevice();
                    }
        }

    punct y;
    y.x=50;
    y.y=200;
    desenare_vector(y,latura,n,v1);

    x.x=50;
    setcolor(RED);
    desenare_vector(x,latura,n,v);
    setcolor(WHITE);

}

void sortare_insertie(int v[101], int n, int tip) //Alex

{
    punct x;
    x.x=50;
    x.y=200;
    int latura,i;
    latura=latura_celula_vector(n,v);


    x.y+=latura+10;

    int v1[101];
    for(int i=1; i<=n; i++)
        v1[i]=v[i];


    for(int j=2; j<=n; j++)
        {
            int aux=v[j];
            int i=j-1;
            while (aux*tip < v[i]*tip && i>0)
                {
                    v[i+1]=v[i];
                    i=i-1;

                    x.x=50;
                    punct y;
                    y.x=50;
                    y.y=200;
                    desenare_vector(y,latura,n,v1);

                    for(int k=1; k<=n; k++,x.x+=latura)
                        {
                            if(k==i)
                                setcolor(YELLOW);
                            rectangle(x.x,x.y,x.x+latura,x.y+latura);
                            char cuv[256];//vom transforma numarul din int in char
                            std::sprintf(cuv, "%d",v[k]);
                            outtextxy(x.x+5,x.y+latura/2-5,cuv);
                            setcolor(WHITE);
                        }

                    delay(500);
                    cleardevice();

                }
            v[i+1]=aux;

            x.x=50;
            punct y;
            y.x=50;
            y.y=200;
            desenare_vector(y,latura,n,v1);
            for(int k=1; k<=n; k++,x.x+=latura)
                {
                    if(k==j)
                        setcolor(YELLOW);
                    rectangle(x.x,x.y,x.x+latura,x.y+latura);
                    char cuv[256];//vom transforma numarul din int in char
                    std::sprintf(cuv, "%d",v[k]);
                    outtextxy(x.x+5,x.y+latura/2-5,cuv);
                    setcolor(WHITE);
                }

            delay(1000);
            cleardevice();
        }

    punct y;
    y.x=50;
    y.y=200;
    desenare_vector(y,latura,n,v1);

    x.x=50;
    setcolor(RED);
    desenare_vector(x,latura,n,v);
    setcolor(WHITE);
}

//functie ce shifteaza spre stanga sau dreapta, cu un anumit numar de pozitii un vector
//reprezinta in fereastra grafica aceste operatie
//nr_shift reprezinta numarul de pozitii shiftate
//directia poate avea valoarea 1 sau alta valoare. 1 pentru shiftare la stanga si alta valoare (0, de exemplu) in caz contrar

void shiftare_vector(int v[101], int n, int nr_shift,int directie) //Alex
{
    punct x;
    x.x=50;
    x.y=200;
    int latura,i;
    latura=latura_celula_vector(n,v);

    x.y+=latura+10;

    int v1[101];
    for(int i=1; i<=n; i++)
        v1[i]=v[i];

    int aux;
    while(nr_shift)//numarul de shiftari pe care le vom face
        {
            if(directie==1)//daca trebuie sa shiftam spre stanga
                {
                    aux=v[1];
                    for(i=1; i<n; i++)
                        {
                            v[i]=v[i+1];
                            x.x=50;

                            punct y;
                            y.x=50;
                            y.y=200;
                            desenare_vector(y,latura,n,v1);
                            for(int k=1; k<=n; k++,x.x+=latura)
                                {
                                    if(k==i)
                                        setcolor(YELLOW);
                                    rectangle(x.x,x.y,x.x+latura,x.y+latura);
                                    char cuv[256];//vom transforma numarul din int in char
                                    std::sprintf(cuv, "%d",v[k]);
                                    outtextxy(x.x+5,x.y+latura/2-5,cuv);
                                    setcolor(WHITE);
                                }

                            delay(500);
                            cleardevice();
                        }
                    v[n]=aux;
                }

            else//daca trebuie sa shiftam spre dreapta

                {
                    aux=v[n];
                    for(i=n; i>1; i--)
                        {
                            v[i]=v[i-1];
                            x.x=50;

                            punct y;
                            y.x=50;
                            y.y=200;
                            desenare_vector(y,latura,n,v1);

                            for(int k=1; k<=n; k++,x.x+=latura)
                                {
                                    if(k==i)
                                        setcolor(YELLOW);
                                    rectangle(x.x,x.y,x.x+latura,x.y+latura);
                                    char cuv[256];//vom transforma numarul din int in char
                                    std::sprintf(cuv, "%d",v[k]);
                                    outtextxy(x.x+5,x.y+latura/2-5,cuv);
                                    setcolor(WHITE);
                                }
                            delay(500);
                            cleardevice();
                        }
                    v[1]=aux;
                }
            nr_shift--;
        }

    punct y;
    y.x=50;
    y.y=200;
    desenare_vector(y,latura,n,v1);

    x.x=50;
    setcolor(RED);
    desenare_vector(x,latura,n,v);
    setcolor(WHITE);
}


///MATRICI

bool validLength(char s[]) //Andrei
{

    unsigned int lg = strlen(s);

    for(unsigned int i=0; i < lg; i++)
        {
            if(strchr(sep, s[i]))
                return false;
            if(isalpha(s[i]))
                return false;
        }
    //if(s[0] == NULL) return false;
    return true;
}

int charToInt(char s[]) //Andrei
{
    int x = 0;
    unsigned int lg = strlen(s);
    for(unsigned int i=0; i < lg; i++)
        x = x * 10 + (int)(s[i] - '0');
    return x;
}

bool valueTooBig(char s[]) //Andrei
{
    int n;
    n = charToInt(s);
    if(n > 100) return true;
    return false;
}

bool validValues(char s[]) //Andrei
///verifica daca valorile introduse sunt valide (numere si spatii)
{
    unsigned int lg = strlen(s);

    for(unsigned int i=0; i < lg; i++)
        {
            if(s[i] == ' ')
                continue;
            if(isalpha(s[i]) || strchr(sep+1, s[i]))
                return false;
        }
    return true;
}

void citire_matrice(int a[101][101], int &n, int &m) //Andrei
{
    n = m = 0;
    int value = 0;
    values.clear();
    system("CLS");

    cout<<"Introduceti numarul de linii ale matricei: ";
    cin.getline(s, 1000);
    while(s[0] == NULL)
        {
            cin.getline(s, 1000);
        }
    while(!validLength(s) || valueTooBig(s))
        {
            SetConsoleTextAttribute(hConsole, 12);

            if(!validLength(s))
                cout<<"Eroare, valoare invalida.\n";
            else if(valueTooBig(s))
                cout<<"Eroare, valoare prea mare.\n";

            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Introduceti numarul de linii ale matricei: ";
            cin.getline(s, 1000);
        }
    n = charToInt(s);

    cout<<"Introduceti numarul de coloane ale matricei: ";
    cin.getline(s, 1000);

    while(!validLength(s) || valueTooBig(s))
        {
            SetConsoleTextAttribute(hConsole, 12);

            if(!validLength(s))
                cout<<"Eroare, valoare invalida.\n";
            else if(valueTooBig(s))
                cout<<"Eroare, valoare prea mare.\n";

            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Introduceti numarul de coloane ale matricei: ";
            cin.getline(s, 1000);
        }
    m = charToInt(s);

    for(int i=1; i <= n; i++)
        {
            do
                {
                    cout<<"Introduceti valorile pentru linia "<<i<<" a matricei: ";
                    cin.getline(s, 1000);

                    while(!validValues(s))
                        {
                            SetConsoleTextAttribute(hConsole, 12);
                            cout<<"Eroare, valoare invalida.\n";

                            SetConsoleTextAttribute(hConsole, 7);
                            cout<<"Introduceti valorile pentru linia "<<i<<" a matricei: ";
                            cin.getline(s, 1000);
                        }
                    char *p = strtok(s, sep);

                    while(p)
                        {
                            int k;

                            bool ok = true;
                            value = 0;
                            for(k=0; p[k] && ok; k++)
                                {
                                    /*if(p[k] == '.') //pt numere double
                                        {
                                            ok = false;
                                            continue;
                                        }*/
                                    value = value * 10 + (int)(p[k] - '0');
                                }
                            /*if(!ok)
                                {
                                    float putere = 0.1f;
                                    for(; p[k]; k++)
                                        {
                                            value = value + putere * (int)(p[k]-'0');
                                            putere /= 10;
                                        }
                                }*/
                            values.push_back(value);
                            //valueNumber++;
                            p = strtok(NULL, sep);
                        }
                }
            while(values.size() < m);
            for(int j=0; j < m; j++)
                a[i][j+1] = values[j];
            values.clear();
        }
}

int latura_celula_matrice( int a[101][101], int n, int m) //Alex
{
    int latura=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            {
                char cuv[256];//vom transforma numarul din int in char
                std::sprintf(cuv, "%d",a[i][j]);

                if(textwidth(cuv)>latura)//latura va fi reprezentata de lungimea maxima (in pixeli) a continuturilor celulelor
                    latura=textwidth(cuv);
            }
// returnam o latura putin mai mare pentru a afisa numarul din celula corespunzator
    return latura+=20;
}

//asemenea vom face si in cazul desenarii unei matrice in fereastra grafica
void desenare_matrice(punct punct_plecare,int nr_linii, int nr_coloane,int latura, int matrice[101][101]) //Alex
{
    settextstyle(BOLD_FONT,HORIZ_DIR,1);

    int x,y;
    x=punct_plecare.x;
    y=punct_plecare.y;

    for(int i=1; i<=nr_linii; i++,y+=latura)
        {
            for(int j=1; j<=nr_coloane; j++,x+=latura)
                {
                    setcolor(GREEN);
                    rectangle(x,y,x+latura,y+latura);
                    setcolor(MAGENTA);
                    char cuv[256];//vom transforma numarul din int in char
                    std::sprintf(cuv, "%d",matrice[i][j]);
                    outtextxy(x+5,y+latura/2-5,cuv);
                    setcolor(WHITE);
                    delay(150);
                }

            x=punct_plecare.x;
        }
    delay(850);
}

void adunare_matrici(int matrice1[101][101], int matrice2[101][101], int n, int m, int matrice3[101][101]) //Alex
{


    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            matrice3[i][j]=matrice1[i][j]+matrice2[i][j];

    punct x;
    x.x=50;
    x.y=50;

    int latura=max((latura_celula_matrice(matrice1,n,m),latura_celula_matrice(matrice2,n,m)),latura_celula_matrice(matrice3,n,m));

    desenare_matrice(x,n,m,latura,matrice1);//desenez prima matrice

    delay(1000);

    x.x=x.x+latura*m+20;
    x.y+=n/2*latura;
    readimagefile("plus1.jpg",x.x,x.y,x.x+latura,x.y+latura);//inserez semnul plus
    x.y-=n/2*latura;

    delay(1000);

    x.x+=latura+20;
    desenare_matrice(x,n,m,latura,matrice2);//desenez a doua matrice

    x.y+=n/2*latura;
    x.x=x.x+latura*m+20;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);//inserez semnul egal
    x.y-=n/2*latura;

    delay(1000);

    x.x+=latura+20;
    setcolor(YELLOW);
    desenare_matrice(x,n,m,latura,matrice3);//desenez matricea rezultat
    setcolor(WHITE);

}

void scadere_matrici(int matrice1[101][101], int matrice2[101][101], int n, int m, int matrice3[101][101]) //Alex
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            matrice3[i][j]=matrice1[i][j]-matrice2[i][j];

    punct x;
    x.x=50;
    x.y=50;

    int latura=max((latura_celula_matrice(matrice1,n,m),latura_celula_matrice(matrice2,n,m)),latura_celula_matrice(matrice3,n,m));

    desenare_matrice(x,n,m,latura,matrice1);//desenez prima matrice

    delay(1000);

    x.x=x.x+latura*m+20;
    x.y+=n/2*latura;
    readimagefile("minus.jpg",x.x,x.y,x.x+latura,x.y+latura);//inserez semnul minus
    x.y-=n/2*latura;
    delay(1000);
    x.x+=latura+20;
    desenare_matrice(x,n,m,latura,matrice2);//desenez a doua matrice
    delay(1000);


    x.y+=n/2*latura;
    x.x=x.x+latura*m+20;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);//inserez semnul egal
    x.y-=n/2*latura;
    delay(1000);
    x.x+=latura+20;
    setcolor(YELLOW);
    desenare_matrice(x,n,m,latura,matrice3);//desenez matricea rezultat
    setcolor(WHITE);

}

void inmultire_matrici(int matrice1[101][101],int matrice2[101][101],int n1,int m1,int n2,int m2, int matrice3[101][101],int &n3,int &m3) //Alex
{

    //if(m1!=n2)
    //  cout<<"nu se poate efectua inmultirea";
    for(int i=1; i<=n1; i++)
        for(int j=1; j<=m2; j++)
            for(int k=1; k<=m1; k++)
                matrice3[i][j]+=matrice1[i][k]*matrice2[k][j];
    n3=n1;
    m3=m2;


    punct x;
    x.x=50;
    x.y=50;

    int latura=max((latura_celula_matrice(matrice1,n1,m1),latura_celula_matrice(matrice2,n2,m2)),latura_celula_matrice(matrice3,n3,m3));

    desenare_matrice(x,n1,m1,latura,matrice1);//desenez prima matrice
    delay(1000);
    x.x=x.x+latura*m1+20;
    x.y+=n1/2*latura;
    readimagefile("star.jpg",x.x,x.y,x.x+latura,x.y+latura);//inserez semnul minus
    x.y-=n1/2*latura;
    delay(1000);
    x.x+=latura+20;

    if(n1>n2)
        {
            x.y+=(n1-n2)*latura/2;
            desenare_matrice(x,n2,m2,latura,matrice2);//desenez a doua matrice
            x.y-=(n1-n2)*latura/2;
        }

    else
        {
            x.y-=(n2-n1)*latura/2;
            desenare_matrice(x,n2,m2,latura,matrice2);//desenez a doua matrice
            x.y+=(n2-n1)*latura/2;
        }
    delay(1000);
    x.y+=n2/2*latura;
    x.x=x.x+latura*m2+20;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);//inserez semnul egal
    x.y-=n2/2*latura;
    delay(1000);
    x.x+=latura+20;
    setcolor(YELLOW);
    desenare_matrice(x,n3,m3,latura,matrice3);//desenez matricea rezultat
    setcolor(WHITE);


}


int matrice_la_putere(int matrice1[101][101],int matrice2[101][101],int n,int putere, int matrice3[101][101]) //Alex
{
    int display_putere=putere;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            matrice2[i][j]=matrice1[i][j];

    while(putere>1)
        {
            inmultire_matrici(matrice1,matrice2,n,n,n,n,matrice3,n,n);
            putere--;

            delay(3000);
            cleardevice();

            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    matrice2[i][j]=matrice3[i][j];

            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    matrice3[i][j]=0;
        }

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            matrice3[i][j]=matrice2[i][j];

    punct x;
    x.x=50;
    x.y=50;

    int latura=latura_celula_matrice(matrice3,n,n);

    desenare_matrice(x,n,n,latura,matrice1);
    delay(1000);
    x.x+=n*latura+20;
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    outtextxy(x.x,x.y,"^");
    delay(1000);
    x.x+=textwidth("^")+10;
    char cuv[256];//vom transforma numarul din int in char
    std::sprintf(cuv, "%d",display_putere);
    outtextxy(x.x,x.y,cuv);
    delay(1000);
    settextstyle(BOLD_FONT,HORIZ_DIR,1);
    x.x+=10;
    x.y+=n/2*latura;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=10+latura;
    x.y-=n/2*latura;
    desenare_matrice(x,n,n,latura,matrice3);


}

void transpusa_matrice(int matrice[101][101],int n,int m, int matrice_rezultat[101][101]) //Alex
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            matrice_rezultat[j][i]=matrice[i][j];

    punct x;
    x.x=50;
    x.y=50;

    int latura=latura_celula_matrice(matrice,n,m);

    desenare_matrice(x,n,m,latura,matrice);
    delay(1000);
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    outtextxy(x.x,x.y,"T");
    delay(1000);
    x.x+=textwidth("^")+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,1);
    x.y+=n/2*latura;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=10+latura;
    x.y-=n/2*latura;
    desenare_matrice(x,n,m,latura,matrice_rezultat);
    delay(1000);
}

void desenare_determinant(punct punct_plecare,int nr_linii, int nr_coloane,int latura, int matrice[101][101]) //Alex
{
    settextstyle(BOLD_FONT,HORIZ_DIR,1);

    int x,y;
    x=punct_plecare.x;
    y=punct_plecare.y;

    setcolor(RED);
    line(x,y,x,y+latura*nr_linii);
    line(x+latura*nr_coloane,y,x+latura*nr_coloane,y+latura*nr_linii);
    delay(1000);
    setcolor(WHITE);

    for(int i=1; i<=nr_linii; i++,y+=latura)
        {
            for(int j=1; j<=nr_coloane; j++,x+=latura)
                {
                    char cuv[256];//vom transforma numarul din int in char
                    std::sprintf(cuv, "%d",matrice[i][j]);
                    outtextxy(x+5,y+latura/2-5,cuv);
                    delay(750);
                }

            x=punct_plecare.x;
        }
}

int d=0;
int determinant(int a[101][101],int n) //Alex
{

    if(n==2)
        return a[1][1]*a[2][2]-a[1][2]*a[2][1];
    else if(n==3)
        return a[1][1]*a[2][2]*a[3][3]+a[1][2]*a[2][3]*a[3][1]+a[1][3]*a[2][1]*a[3][2]-a[3][1]*a[2][2]*a[1][3]-a[3][2]*a[2][3]*a[1][1]-a[3][3]*a[2][1]*a[1][2];
    else
        {
            for(int k=1; k<=n; k++)
                {

                    int aux[101][101];
                    for(int i=1; i<n; i++)
                        for(int j=1; j<n; j++)
                            aux[i][j]=0;

                    int ii=2;
                    for(int i=1; i<n; i++,ii++)
                        for(int j=1,jj=1; j<n; j++,jj++)
                            {

                                if(jj==k)
                                    jj++;
                                aux[i][j]=a[ii][jj];
                            }

                    d+=determinant(aux,n-1)*a[1][k]*pow(-1,k+1);

                }
        }

    return d;
}

int determinant_4(int a[101][101],int n,punct &x,int latura,int color) //Alex
{

    if(n==2)
        return a[1][1]*a[2][2]-a[1][2]*a[2][1];
    else if(n==3)
        return a[1][1]*a[2][2]*a[3][3]+a[1][2]*a[2][3]*a[3][1]+a[1][3]*a[2][1]*a[3][2]-a[3][1]*a[2][2]*a[1][3]-a[3][2]*a[2][3]*a[1][1]-a[3][3]*a[2][1]*a[1][2];
    else
        {


            for(int k=1; k<=n; k++)
                {
                    int aux[101][101];
                    for(int i=1; i<n; i++)
                        for(int j=1; j<n; j++)
                            aux[i][j]=0;

                    int ii=2;
                    for(int i=1; i<n; i++,ii++)
                        for(int j=1,jj=1; j<n; j++,jj++)
                            {

                                if(jj==k)
                                    jj++;
                                aux[i][j]=a[ii][jj];
                            }

                    settextstyle(BOLD_FONT,HORIZ_DIR,1);
                    setcolor(color);
                    color++;
                    x.y+=latura*n/2;
                    outtextxy(x.x,x.y,"(-1)^(1+");
                    x.x+=textwidth("(-1)^(1+");
                    char cuv[256];
                    std::sprintf(cuv, "%d",k);
                    outtextxy(x.x,x.y,cuv);
                    x.x+=textwidth(cuv);
                    outtextxy(x.x,x.y,")*");
                    x.x+=textwidth(")*");
                    std::sprintf(cuv, "%d",a[1][k]);
                    outtextxy(x.x,x.y,cuv);
                    x.x+=textwidth(cuv);
                    outtextxy(x.x,x.y,"* ");
                    x.x+=textwidth("* ");
                    x.y-=latura*n/2;

                    desenare_determinant(x,n,n,latura,a);
                    x.x+=latura/4;
                    x.y+=latura/2;
                    line(x.x,x.y,x.x+latura*(n-1),x.y);
                    x.x+=latura/16+latura*(k-1);
                    line(x.x,x.y,x.x,x.y+latura*(n-1));

                    x.x-=latura/16+latura*(k-1);
                    x.y-=latura/2;
                    x.x-=latura/4;

                    if(k<n)
                        {
                            x.y+=n/2 *latura;
                            x.x=x.x+latura*n+10;
                            readimagefile("plus1.jpg",x.x,x.y,x.x+latura,x.y+latura);
                            x.x+=10+latura;
                            x.y-=n/2*latura;
                        }
                    else
                        {
                            x.y+=n/2 *latura;
                            x.x=x.x+latura*n+10;
                            readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
                            x.x+=10+latura;
                            x.y-=n/2*latura;
                        }


                    d+=determinant(aux,n-1)*a[1][k]*pow(-1,k+1);

                }
        }

    return d;
}


void determinant_grafic(int n,int a[101][101]) //Alex
{
    punct x;
    x.x=10;
    x.y=10;
    int latura=latura_celula_matrice(a,n,n);

    desenare_determinant(x,n,n,latura,a);
    delay(1000);
    x.y+=n/2 *latura-10;
    x.x=x.x+latura*n+10;
    readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
    delay(1000);
    x.x+=latura+10;
    x.y+=10;

    char cuv[256];
    std::sprintf(cuv, "%d",determinant(a,n));
    setcolor(YELLOW);
    outtextxy(x.x,x.y,cuv);
    delay(1000);
    setcolor(WHITE);

    x.x=10;
    x.y=10;
    x.y+=latura*n+50;

    if(n==4)
        {
            determinant_4(a,n,x,latura,2);
            x.x=0;
            x.y+=3*n/2 *latura;
            readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
            delay(1000);
            x.x+=latura+10;
            settextstyle(BOLD_FONT,HORIZ_DIR,3);
            setcolor(YELLOW);
            outtextxy(x.x,x.y+10,cuv);
            setcolor(WHITE);
            settextstyle(BOLD_FONT,HORIZ_DIR,1);
        }
    else if(n==3)
        {
            desenare_determinant(x,n,n,latura,a);
            delay(1000);
            x.y+=latura*n;
            for(int i=1; i<=2; i++,x.y+=latura)
                {
                    for(int j=1; j<=3; j++,x.x+=latura)
                        {
                            char cuv[256];//vom transforma numarul din int in char
                            std::sprintf(cuv, "%d",a[i][j]);
                            outtextxy(x.x+5,x.y+latura/2-5,cuv);
                            delay(150);
                        }

                    x.x=10;
                }

            x.x=10;
            x.y=10;
            x.x+=latura/4;
            x.y+=latura/2;
            x.y+=latura*n+50;
            setcolor(MAGENTA);
            for(int i=1; i<=3; i++,x.y+=latura)
                {
                    line(x.x,x.y,x.x+latura*(n-1),x.y+latura*(n-1));
                    delay(150);
                }

            x.x=10;
            x.y=10;
            x.x+=latura/4;
            x.y+=latura/2;
            x.y+=latura*n+50;
            setcolor(GREEN);
            for(int i=1; i<=3; i++,x.y+=latura)
                {
                    line(x.x+latura*(n-1),x.y,x.x,x.y+latura*(n-1));
                    delay(150);
                }

            x.x=10;
            x.y=10;
            x.y+=latura*n+50;
            x.y+=n/2 *latura;
            x.x=x.x+latura*n+10;
            readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
            delay(1000);
            x.x+=10+latura;

            int sum=a[1][1]*a[2][2]*a[3][3]+a[1][2]*a[2][3]*a[3][1]+a[1][3]*a[2][1]*a[3][2];
            char cuv[256];
            std::sprintf(cuv, "%d",sum);
            setcolor(MAGENTA);
            x.y+=10;
            outtextxy(x.x,x.y,cuv);
            x.x+=textwidth(cuv);

            setcolor(WHITE);
            outtextxy(x.x,x.y,"+");
            x.x+=textwidth("+");

            sum=-a[3][1]*a[2][2]*a[1][3]-a[3][2]*a[2][3]*a[1][1]-a[3][3]*a[2][1]*a[1][2];
            setcolor(GREEN);
            if(sum<0)
                {
                    outtextxy(x.x,x.y,"(");
                    x.x+=textwidth("(");
                    std::sprintf(cuv, "%d",sum);
                    outtextxy(x.x,x.y,cuv);
                    x.x+=textwidth(cuv);
                    outtextxy(x.x,x.y,")");
                    x.x+=textwidth(")");
                }
            else
                {
                    std::sprintf(cuv, "%d",sum);
                    outtextxy(x.x,x.y,cuv);
                    x.x+=textwidth(cuv);
                }

            x.y-=10;
            readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
            delay(1000);
            x.x+=latura+10;
            x.y+=10;
            std::sprintf(cuv, "%d",determinant(a,n));
            setcolor(RED);
            outtextxy(x.x,x.y,cuv);
        }
}

void afisare_matrice(int a[101][101],int n) //Alex
{
    for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
    cout<<endl;
}

void inversa_matrice(int a[101][101],int n) //Alex
{
    if(determinant(a,n)!=0)
        {
            int stelat[101][101],transpusa[101][101];

            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    transpusa[j][i]=a[i][j];

            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    {
                        int aux[101][101];
                        for(int k=1; k<=n; k++)
                            for(int kk=1; kk<=n; kk++)
                                aux[k][kk]=0;

                        for(int p=1,ii=1; p<n; p++,ii++)
                            for(int pp=1,jj=1; pp<n; pp++,jj++)
                                {
                                    if(ii==i)
                                        ii++;
                                    if(jj==j)
                                        jj++;
                                    aux[p][pp]=a[ii][jj];
                                }

                        stelat[i][j]=determinant(aux,n-1)*pow(-1,i+j);

                    }

            punct x;
            x.x=50;
            x.y=50;

            int latura=max(latura_celula_matrice(a,n,n),latura_celula_matrice(stelat,n,n));
            desenare_matrice(x,n,n,latura,a);
            delay(1000);
            x.x+=n*latura+20;
            settextstyle(BOLD_FONT,HORIZ_DIR,3);
            outtextxy(x.x,x.y,"^-1");
            delay(1000);
            x.x+=textwidth("^-1")+10;
            settextstyle(BOLD_FONT,HORIZ_DIR,1);
            x.x+=10;
            x.y+=n/2*latura;
            readimagefile("equal.jpg",x.x,x.y,x.x+latura,x.y+latura);
            delay(1000);
            x.x+=10+latura;
            x.y-=n/2*latura;

            settextstyle(BOLD_FONT,HORIZ_DIR,3);
            x.x+=latura;
            setcolor(YELLOW);
            outtextxy(x.x,x.y,"1");
            delay(1000);
            x.y+=n/2*latura;
            x.x-=latura;
            line(x.x,x.y,x.x+2*latura+20,x.y);
            delay(1000);
            setcolor(WHITE);
            outtextxy(x.x+2*latura+50,x.y,"*");
            setcolor(YELLOW);
            x.y+=10;
            x.x+=latura;
            char cuv[256];

            std::sprintf(cuv, "%d",determinant(a,n));
            outtextxy(x.x,x.y,cuv);
            delay(1000);
            setcolor(WHITE);

            x.x+=2*latura+50;
            x.y=50;
            desenare_matrice(x,n,n,latura,stelat);
            delay(1000);

            settextstyle(BOLD_FONT,HORIZ_DIR,1);
        }
    else
        {
            int i=1;
            while(1)
                {
                    setcolor(i);
                    i++;
                    if(i>6)
                        i=1;
                    settextstyle(BOLD_FONT,HORIZ_DIR,5);
                    char cuv[256];
                    strcpy(cuv,"MATRICEA ARE DETERMINANTUL 0, INVERSA EI NU EXISTA");
                    outtextxy(textwidth(cuv)-1130,800/2,cuv);
                    delay(200);
                }
        }

}


void desenare_matrice_custom1(punct punct_plecare,int n,int latura, int matrice[101][101]) //Alex
{
    settextstyle(BOLD_FONT,HORIZ_DIR,1);

    int x,y;
    x=punct_plecare.x;
    y=punct_plecare.y;

    for(int i=1; i<=n; i++,y+=latura)
        {
            for(int j=1; j<=n; j++,x+=latura)
                {

                    rectangle(x,y,x+latura,y+latura);

                    int c=0;
                    if(i==j)
                        c=2;
                    for(int k=x+1; k<x+latura; k++)
                        for(int kk=y+1; kk<y+latura; kk++)
                            putpixel(k,kk,c);
                    //setfillstyle(SOLID_FILL,WHITE);
                    //floodfill(x+1,y+1,c);
                    char cuv[256];//vom transforma numarul din int in char
                    std::sprintf(cuv, "%d",matrice[i][j]);
                    outtextxy(x+5,y+latura/2-5,cuv);
                    setcolor(WHITE);
                }

            x=punct_plecare.x;
        }
}

void desenare_matrice_custom2(punct punct_plecare,int n,int latura, int matrice[101][101]) //Alex
{
    settextstyle(BOLD_FONT,HORIZ_DIR,1);

    int x,y;
    x=punct_plecare.x;
    y=punct_plecare.y;

    for(int i=1; i<=n; i++,y+=latura)
        {
            for(int j=1; j<=n; j++,x+=latura)
                {

                    rectangle(x,y,x+latura,y+latura);

                    int c=0;
                    if(i+j==n+1)
                        c=3;
                    for(int k=x+1; k<x+latura; k++)
                        for(int kk=y+1; kk<y+latura; kk++)
                            putpixel(k,kk,c);
                    //setfillstyle(SOLID_FILL,WHITE);
                    //floodfill(x+1,y+1,c);
                    char cuv[256];//vom transforma numarul din int in char
                    std::sprintf(cuv, "%d",matrice[i][j]);
                    outtextxy(x+5,y+latura/2-5,cuv);
                    setcolor(WHITE);
                }

            x=punct_plecare.x;
        }
}


void desenare_matrice_custom3(punct punct_plecare,int n,int latura, int matrice[101][101]) //Alex
{
    settextstyle(BOLD_FONT,HORIZ_DIR,1);

    int x,y;
    x=punct_plecare.x;
    y=punct_plecare.y;

    for(int i=1; i<=n; i++,y+=latura)
        {
            for(int j=1; j<=n; j++,x+=latura)
                {

                    rectangle(x,y,x+latura,y+latura);

                    int c=0;
                    if(i<j&&i+j<n+1)
                        c=4;
                    if(i<j&&i+j>n+1)
                        c=5;
                    if(i>j&&i+j>n+1)
                        c=6;
                    if(i>j&&i+j<n+1)
                        c=8;
                    for(int k=x+1; k<x+latura; k++)
                        for(int kk=y+1; kk<y+latura; kk++)
                            putpixel(k,kk,c);
                    char cuv[256];//vom transforma numarul din int in char
                    std::sprintf(cuv, "%d",matrice[i][j]);
                    outtextxy(x+5,y+latura/2-5,cuv);
                    setcolor(WHITE);
                }

            x=punct_plecare.x;
        }
}



void operatii_matrice(int a[101][101], int n,
                      int &ds, int &dp, int &nord, int &sud, int &est, int &vest, int &subdp, int &subds, int &deasupradp, int &deasuprads) //Alex
{
    int i,j;
    subdp=0;
    for(i=1; i<=n; i++)
        dp+=a[i][i],ds+=a[i][n-i+1];

    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            {
                if(i>j)
                    subdp+=a[i][j];
                if(i<j)
                    deasupradp+=a[i][j];
                if(i+j>n+1)
                    subds+=a[i][j];
                if(i+j<n+1)
                    deasuprads+=a[i][j];
                if(i<j&&i+j<n+1)
                    nord+=a[i][j];
                if(i<j&&i+j>n+1)
                    est+=a[i][j];
                if(i>j&&i+j>n+1)
                    sud+=a[i][j];
                if(i>j&&i+j<n+1)
                    vest+=a[i][j];
            }
    cout<<subdp;

    punct x;
    x.x=50;
    x.y=50;
    int latura=latura_celula_matrice(a,n,n);
    desenare_matrice_custom1(x,n,latura,a);

    ///dp
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(2);
    char cuv[256];

    x.y+=10;
    outtextxy(x.x,x.y,"SUMA DP: ");
    x.x+=textwidth("SUMA DP: ");
    std::sprintf(cuv, "%d",dp);
    outtextxy(x.x,x.y,cuv);

    x.x=50;
    x.y+=latura+10;
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(RED);
    outtextxy(x.x,x.y,"SUMA SUB DP: ");
    x.x+=textwidth("SUMA SUB DP: ");
    std::sprintf(cuv, "%d",subdp);
    outtextxy(x.x,x.y,cuv);
    setcolor(WHITE);

    x.x=50;
    x.y+=latura+10;
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(YELLOW);
    outtextxy(x.x,x.y,"SUMA DEASUPRA DP: ");
    x.x+=textwidth("SUMA DEASUPRA DP: ");
    std::sprintf(cuv, "%d",deasupradp);
    outtextxy(x.x,x.y,cuv);
    setcolor(WHITE);

    ///ds
    x.x=50;
    x.y=50;
    x.y+=latura*n+40;
    x.y+=10;
    desenare_matrice_custom2(x,n,latura,a);

    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(3);
    outtextxy(x.x,x.y,"SUMA DS: ");
    x.x+=textwidth("SUMA DS: ");
    std::sprintf(cuv, "%d",ds);
    outtextxy(x.x,x.y,cuv);

    x.x=50;
    x.y+=latura+10;
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(RED);
    outtextxy(x.x,x.y,"SUMA SUB DS: ");
    x.x+=textwidth("SUMA SUB DS: ");
    std::sprintf(cuv, "%d",subds);
    outtextxy(x.x,x.y,cuv);
    setcolor(WHITE);

    x.x=50;
    x.y+=latura+10;
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(YELLOW);
    outtextxy(x.x,x.y,"SUMA DEASUPRA DS: ");
    x.x+=textwidth("SUMA DEASUPRA DS: ");
    std::sprintf(cuv, "%d",deasuprads);
    outtextxy(x.x,x.y,cuv);
    setcolor(WHITE);

    ///cardinale

    x.x=50;
    x.y+=latura*n+40;
    desenare_matrice_custom3(x,n,latura,a);

    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(4);
    outtextxy(x.x,x.y,"SUMA NORD: ");
    x.x+=textwidth("SUMA NORD: ");
    std::sprintf(cuv, "%d",nord);
    outtextxy(x.x,x.y,cuv);

    x.x=50;
    x.y+=latura+10;
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(5);
    outtextxy(x.x,x.y,"SUMA EST: ");
    x.x+=textwidth("SUMA EST: ");
    std::sprintf(cuv, "%d",est);
    outtextxy(x.x,x.y,cuv);
    setcolor(WHITE);

    x.x=50;
    x.y+=latura+10;
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(6);
    outtextxy(x.x,x.y,"SUMA SUD: ");
    x.x+=textwidth("SUMA SUD: ");
    std::sprintf(cuv, "%d",sud);
    outtextxy(x.x,x.y,cuv);
    setcolor(WHITE);

    x.x=50;
    x.y+=latura+10;
    x.x+=latura*n+10;
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(7);
    outtextxy(x.x,x.y,"SUMA VEST: ");
    x.x+=textwidth("SUMA VEST: ");
    std::sprintf(cuv, "%d",vest);
    outtextxy(x.x,x.y,cuv);
    setcolor(WHITE);


}

class Button //Andrei
{
private:
    char label[100];
    punct topL, botR, topR, botL;
    int width, height;
    bool selected = false;

public:

    Button(char *label, punct stgS, int w, int h) //Andrei
    {
        setWidth(w);
        setHeight(h);
        setTopL(stgS);
        setTopR();
        setBotR();
        setBotL();
        setLabel(label);
    }

    ~Button() //Andrei
    {

    }

    void setWidth(int w) //Andrei
    {
        width = w;
    }

    void setHeight(int h) //Andrei
    {
        height = h;
    }
    void setTopL(punct stgS) //Andrei
    {
        topL = stgS;
    }

    void setTopR() //Andrei
    {
        topR.x = topL.x + width;
        topR.y = topL.y;
    }
    void setBotL() //Andrei
    {
        botL.y = topL.y + height;
        botL.x = topL.x;
    }
    void setBotR() //Andrei
    {
        botR.x = topL.x + width;
        botR.y = topR.y + height;
    }

    void setLabel(char sir[]) //Andrei
    {
        strcpy(label, sir);
    }

    int setCellColor() //Andrei
    {
        if(pointInCell(mousex(), mousey()))
            if(mousey()>400)
                return MAGENTA;
            else
                return GREEN;
        return WHITE;
    }

    void setSelected(bool a) //Andrei
    {
        selected = a;
    }

    bool getSelected() //Andrei
    {
        return selected;
    }

    char *getLabel() //Andrei
    {
        return label;
    }

    int getHeight() //Andrei
    {
        return height;
    }

    int getWidth() //Andrei
    {
        return width;
    }

    punct getTopL() //Andrei
    {
        return topL;
    }

    punct getTopR() //Andrei
    {
        return topR;
    }

    punct getBotL() //Andrei
    {
        return botL;
    }

    punct getBotR() //Andrei
    {
        return botR;
    }

    bool pointInCell(int mouseX, int mouseY) //Andrei
    {
        if(mouseX > topL.x && mouseX < topR.x && mouseY < botL.y && mouseY > topR.y)
            return true;
        return false;
    }

    void draw() //Andrei
    {
        setcolor(setCellColor());
        outtextxy(topL.x + 5, topL.y + height / 2 + 5, label);
        rectangle(topL.x, topL.y, botR.x, botR.y);
    }
};

vector<Button> buttons;

void createButtons() //Andrei + Alex
{


    buttons.push_back(Button("Adunare Vectori",                         coord(140, 200),                     textwidth("Adunare Vectori") + 10,                         textheight("Adunare Vectori") + 10));
    buttons.push_back(Button("Scadere Vectori",                         buttons[0].getTopR() + coord(20, 0), textwidth("Scadere Vectori") + 10,                         textheight("Scadere Vectori") + 10));
    buttons.push_back(Button("Inmultire Vectori",                       buttons[1].getTopR() + coord(20, 0), textwidth("Inmultire Vectori") + 10,                       textheight("Inmultire Vectori") + 10));
    buttons.push_back(Button("Impartire Vectori",                       buttons[2].getTopR() + coord(20, 0), textwidth("Impartire Vectori") + 10,                       textheight("Impartire Vectori") + 10));
    buttons.push_back(Button("Suma Elementelor Unui Vector",            buttons[3].getTopR() + coord(20, 0), textwidth("Suma Elementelor Unui Vector") + 10,            textheight("Suma Elementelor Unui Vector") + 10));
    buttons.push_back(Button("Produsul Elementelor Unui Vector",        buttons[4].getTopR() + coord(20, 0), textwidth("Produsul Elementelor Unui Vector") + 10,        textheight("Produsul Elementelor Unui Vector") + 10));
    buttons.push_back(Button("Inmultirea cu un Scalar",                 buttons[5].getTopR() + coord(20, 0), textwidth("Inmultirea cu un Scalar") + 10,               textheight("Inmultirea cu un Scalar") + 10));
    buttons.push_back(Button("Select Sort Vector",                      buttons[0].getBotL() + coord(450, 20), textwidth("Select Sort Vector") + 10,                    textheight("Select Sort Vector") + 10));
    buttons.push_back(Button("Bubble Sort Vector",                      buttons[7].getTopR() + coord(20, 0), textwidth("Bubble Sort Vector") + 10,                      textheight("Bubble Sort Vector") + 10));
    buttons.push_back(Button("Insert Sort Vector",                      buttons[8].getTopR() + coord(20, 0), textwidth("Insert Sort Vector") + 10,                      textheight("Insert Sort Vector") + 10));
    buttons.push_back(Button("Shift",                                   buttons[9].getTopR() + coord(20, 0), textwidth("Shift") + 10,                                   textheight("Shift") + 10));

    buttons.push_back(Button("Adunare Matrici",                         coord(500, 500),                     textwidth("Adunare Matrici") + 10,                         textheight("Adunare Matrici") + 10));
    buttons.push_back(Button("Scadere Matrici",                         buttons[11].getTopR() + coord(20, 0), textwidth("Scadere Matrici") + 10,                        textheight("Scadere Matrici") + 10));
    buttons.push_back(Button("Inmultire Matrici",                       buttons[12].getTopR() + coord(20, 0), textwidth("Inmultire Matrici") + 10,                      textheight("Inmultire Matrici") + 10));
    buttons.push_back(Button("Matrice la putere",                       buttons[13].getTopR() + coord(20, 0), textwidth("Matrice la Putere") + 10,                      textheight("Matrice la Putere") + 10));
    buttons.push_back(Button("Transpusa Matricei",                      buttons[14].getTopR() + coord(20, 0), textwidth("Transpusa Matricei") + 10,                     textheight("Transpusa Matricei") + 10));
    buttons.push_back(Button("Determinantul Matricei",                  coord(625, 550),                      textwidth("Determinantul Matricei") + 10,                 textheight("Determinantul Matricei") + 10));
    buttons.push_back(Button("Inversa Matricei",                        buttons[16].getTopR() + coord(20, 0), textwidth("Inversa Matricei") + 10,                       textheight("Inversa Matricei") + 10));
    buttons.push_back(Button("Sumele zonelor",                          buttons[17].getTopR() + coord(20, 0), textwidth("Sumele zonelor") + 10,                          textheight("Sumele zonelor") + 10));

    buttonNumber = buttons.size();
    /** 0 - Adunare Vectori
     *  1 - Scadere Vectori
     *  2 - Inmultire Vectori
     *  3 - Impartire Vectori
     *  4 - Suma Elemente Vector
     *  5 - Produsul Elementelor unui Vector
     *  6 - Inmultirea cu un Scalar
     *  7 - Select Sort Vector
     *  8 - Bubble Sort Vector
     *  9 - Insert Sort Vector
     *  10 - Shift
     *  11- Adunare Matrice
     *  12- Scadere Matrice
     *  13- Inmultire Matrice
     *  14- Matrice La Putere
     *  15- Transpusa Matricei
     *  16- Determinantul Matricei
     *  17- Inversa Matricei
     *  18- Sumele zonelor
     */
}


void loadTextSettings() //Andrei
{
    settextjustify(0,1);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
}

void drawButtons() //Andrei
{
    for(int i=0; i < buttonNumber; i++)
        buttons[i].draw();
}

bool buttonSelected() //Andrei
///verifica daca a fost selectata o operatie
{
    for(int i=0; i < buttonNumber; i++)
        if(buttons[i].pointInCell(mouse.x, mouse.y) && (mouse.LMBClick || mouse.RMBClick))
            {
                buttons[i].setSelected(true);
                return true;
            }
    return false;
}

int getIndex() //Andrei
///returneaza pozitia butonului selectat din vectorul de butoane
{
    for(int i=0; i < buttonNumber; i++)
        if(buttons[i].getSelected())
            {
                buttons[i].setSelected(false);
                return i;
            }
    return -1;
}

int selectedIndex;

void menu(int width, int height) //Andrei
{
    bool selected = false;

    initwindow(width, height, "BibMat");

    settextstyle(10,HORIZ_DIR,5);
    outtextxy(window.w / 2 - textwidth("BibMat") - 17,50,"BibMat");

    settextstyle(8,HORIZ_DIR,5);
    setcolor(GREEN);
    outtextxy(window.w / 2 - textwidth("VECTORI"),100,"VECTORI");

    setcolor(MAGENTA);
    outtextxy(window.w / 2 - textwidth("MATRICI"),400,"MATRICI");

    loadTextSettings();
    setlinestyle(0, 0xFFFF, 3);

    createButtons();

    while(!GetAsyncKeyState(VK_ESCAPE) && !selected)
        {
            mouseUpdate(&mouse);
            drawButtons();
            selected = buttonSelected();
            outtextxy(20, window.h - 5 * textheight("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "Proiect realizat de:");
            outtextxy(20, window.h - 4 * textheight("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "Loghin Andrei-Ioan");
            outtextxy(20, window.h -3 * textheight("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "Tanase Alexandru");
        }

    selectedIndex = getIndex();
    closegraph();
}

///


/*void citire_vector(int v[101],int &n)//functie pentru citirea unui vector
{
    f>>n;
    for(int i=1; i<=n; i++)
        f>>v[i];
}*/

void citire_vector(int v[101],int &n) //Andrei
{
    n = 0;
    int value;
    values.clear();
    system("CLS");
    cout<<"Introduceti numarul de valori din vector: ";
    cin.getline(s, 1000);
    while(s[0] == NULL)
        {
            cin.getline(s, 1000);
        }
    while(!validLength(s) || valueTooBig(s))
        {
            SetConsoleTextAttribute(hConsole, 12);

            if(!validLength(s))
                cout<<"Eroare, valoare invalida.\n";
            else if(valueTooBig(s))
                cout<<"Eroare, valoare prea mare.\n";

            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Introduceti numarul de valori din vector: ";
            cin.getline(s, 1000);
        }

    n = charToInt(s);

    do
        {
            cout<<"Introduceti valorile pentru vector: ";
            cin.getline(s, 1000);

            while(!validValues(s))
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    cout<<"Eroare, valoare invalida.\n";

                    SetConsoleTextAttribute(hConsole, 7);
                    cout<<"Introduceti valorile pentru vector: ";
                    cin.getline(s, 1000);
                }
            char *p = strtok(s, sep);

            while(p)
                {
                    int i;

                    bool ok = true;
                    value = 0;
                    for(i=0; p[i] && ok; i++)
                        {
                            /*if(p[i] == '.') //pt numere double
                                {
                                    ok = false;
                                    continue;
                                }*/
                            value = value * 10 + (int)(p[i] - '0');
                        }
                    /*if(!ok)
                        {
                            float putere = 0.1f;
                            for(; p[i]; i++)
                                {
                                    value = value + putere * (int)(p[i]-'0');
                                    putere /= 10;
                                }
                        }*/
                    values.push_back(value);
                    //valueNumber++;
                    p = strtok(NULL, sep);
                }
        }
    while(values.size() < n);
    for(int i=0; i < n; i++)
        v[i+1] = values[i];
}

///
int v1[101],v2[101],v3[101],n,m;
int tip;
int nr_shift,directie;
int mat1[101][101],mat2[101][101],mat3[101][101];
int n1,m1,n2,m2,n3,m3;
int putere;
int ds,dp,nord,sud,est,vest,subdp,subds,deasupradp,deasuprads;
int scalar;

bool citireValoriNoi = true;

void application() //Andrei
{
    window.w = GetSystemMetrics(SM_CXSCREEN);
    window.h = GetSystemMetrics(SM_CYSCREEN);


    menu(window.w, window.h);
    if(citireValoriNoi)
        switch(selectedIndex)
            {
            case 0:
                citire_vector(v1,n);
                citire_vector(v2,n);
                break;

            case 1:
                citire_vector(v1,n);
                citire_vector(v2,n);
                break;

            case 2:
                citire_vector(v1,n);
                citire_vector(v2,n);
                break;
            case 3:
                citire_vector(v1,n);
                citire_vector(v2,n);
                break;

            case 4:
                citire_vector(v1,n);
                break;

            case 5:
                citire_vector(v1,n);
                break;

            case 6:
                citire_vector(v1, n);
                cout<<"Introduceti valoarea scalarului: ";
                cin.getline(s, 1000);

                while(!validValues(s))
                    {
                        SetConsoleTextAttribute(hConsole, 12);
                        cout<<"Eroare, valoare invalida.\n";

                        SetConsoleTextAttribute(hConsole, 7);
                        cout<<"Introduceti valoarea scalarului: ";
                        cin.getline(s, 1000);
                    }
                SetConsoleTextAttribute(hConsole, 7);
                scalar = charToInt(s);
                break;

            case 7:
                citire_vector(v1,n);
                SetConsoleTextAttribute(hConsole, 2);
                cout<<"Sortare in ordine crescatoare = 1\nSortare in ordine descrescatoare = -1 \n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"Alegeti tipul sortarii: ";
                cin>>tip;
                while(tip != 1 && tip != -1)
                    {
                        SetConsoleTextAttribute(hConsole, 12);
                        cout<<"Valoare invalida pentru tipul operatiei\n";
                        SetConsoleTextAttribute(hConsole, 2);
                        cout<<"Sortare in ordine crescatoare = 1\nSortare in ordine descrescatoare = -1 \n ";
                        SetConsoleTextAttribute(hConsole, 7);
                        cout<<"Alegeti tipul sortarii: ";
                        cin>>tip;
                    }
                break;

            case 8:
                citire_vector(v1,n);
                SetConsoleTextAttribute(hConsole, 2);
                cout<<"Sortare in ordine crescatoare = 1\nSortare in ordine descrescatoare = -1 \n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"Alegeti tipul sortarii: ";
                cin>>tip;
                while(tip != 1 && tip != -1)
                    {
                        SetConsoleTextAttribute(hConsole, 12);
                        cout<<"Valoare invalida pentru tipul operatiei\n";
                        SetConsoleTextAttribute(hConsole, 2);
                        cout<<"Sortare in ordine crescatoare = 1\nSortare in ordine descrescatoare = -1 \n";
                        SetConsoleTextAttribute(hConsole, 7);
                        cout<<"Alegeti tipul sortarii: ";
                        cin>>tip;
                    }
                break;

            case 9:
                citire_vector(v1,n);

                SetConsoleTextAttribute(hConsole, 2);
                cout<<"Sortare in ordine crescatoare = 1\nSortare in ordine descrescatoare = -1\n";

                SetConsoleTextAttribute(hConsole, 7);
                cout<<"Alegeti tipul sortarii: ";
                cin>>tip;

                while(tip != 1 && tip != -1)
                    {
                        SetConsoleTextAttribute(hConsole, 12);
                        cout<<"Valoare invalida pentru tipul operatiei\n";

                        SetConsoleTextAttribute(hConsole, 2);
                        cout<<"Sortare in ordine crescatoare = 1\nSortare in ordine descrescatoare = -1\n";

                        SetConsoleTextAttribute(hConsole, 7);
                        cout<<"Alegeti tipul sortarii: ";
                        cin>>tip;
                    }
                break;

            case 10:
                citire_vector(v1,n);
                cout<<"Cu cate pozitii sa se shifteze vectorul? ";
                cin.getline(s, 1000);
                while(!validLength(s) || valueTooBig(s))
                    {
                        if(!validLength(s))
                            {
                                SetConsoleTextAttribute(hConsole, 12);
                                cout<<"Valoare invalida\n";
                            }
                        else
                            {
                                SetConsoleTextAttribute(hConsole, 12);
                                cout<<"Valoare prea mare!\n";
                            }
                        SetConsoleTextAttribute(hConsole, 7);
                        cout<<"Cu cate pozitii sa se shifteze vectorul? ";
                        cin.getline(s, 1000);
                    }
                nr_shift = charToInt(s);

                SetConsoleTextAttribute(hConsole, 2);
                cout<<"Shift la stanga = 1\nShift la dreapta = Orice alta valoare\n";

                SetConsoleTextAttribute(hConsole, 7);
                cout<<"In ce directie sa se shifteze vectorul? ";
                cin>>directie;
                break;

            case 11:
                citire_matrice(mat1,n,m);
                citire_matrice(mat2,n,m);
                break;

            case 12:
                citire_matrice(mat1,n,m);
                citire_matrice(mat2,n,m);
                break;

            case 13:
                citire_matrice(mat1,n1,m1);
                citire_matrice(mat2,n2,m2);
                break;

            case 14:
                citire_matrice(mat1,n,m);
                cin>>putere;
                break;

            case 15:
                citire_matrice(mat1,n,m);
                break;

            case 16:
                citire_matrice(mat1,n,m);
                break;

            case 17:
                citire_matrice(mat1,n,m);
                break;

            case 18:
                citire_matrice(mat1,n,m);
                break;
            }

    initwindow(window.w, window.h, "BibMat");

    loadTextSettings();
    setlinestyle(0, 0xFFFF, 3);

    switch(selectedIndex)
        {
        case 0:
            adunare_vectori(v1,v2,v3,n);
            break;

        case 1:
            scadere_vectori(v1,v2,v3,n);
            break;

        case 2:
            inmultire_vectori(v1,v2,v3,n);
            break;

        case 3:
            impartire_vectori(v1,v2,v3,n);
            break;

        case 4:
            suma_elemente_vector(v1,n);
            break;

        case 5:
            produs_elemente_vector(v1,n);
            break;

        case 6:
            inmultire_vector_scalar(v1, v2, n, scalar);
            break;

        case 7:
            sortare_selectie_directa(v1,n,tip);
            break;

        case 8:
            sortare_bubble(v1,n,tip);
            break;

        case 9:
            sortare_insertie(v1,n,tip);
            break;

        case 10:
            shiftare_vector(v1,n,nr_shift,directie);
            break;

        case 11:
            adunare_matrici(mat1,mat2,n,m,mat3);
            break;

        case 12:
            scadere_matrici(mat1,mat2,n,m,mat3);
            break;

        case 13:
            inmultire_matrici(mat1,mat2,n1,m1,n1,m2,mat3,n3,m3);
            break;

        case 14:
            matrice_la_putere(mat1,mat2,n,putere,mat3);
            break;

        case 15:
            transpusa_matrice(mat1,n,m,mat3);
            break;

        case 16:
            determinant_grafic(n,mat1);
            break;

        case 17:
            inversa_matrice(mat1,n);
            break;

        case 18:
            operatii_matrice(mat1,n,ds,dp,nord,sud,est,vest,subdp,subds,deasupradp,deasuprads);
            break;

            //default:
            //createVector(vect1, coord(100, 100));
        }

    Button back = Button("Inapoi la meniu", coord(window.w - textwidth("Inapoi la meniu") - 230, window.h - textheight("Inapoi la meniu") - 120), textwidth("Inapoi la meniu") + 10, textheight("Inapoi la meniu") + 10);
    Button operatieNouaAlteVal = Button("Operatie noua cu alte valori", back.getTopL() + coord(0, -textheight("Operatie noua cu alte valori") - 20), textwidth("Operatie noua cu alte valori") + 10, textheight("Operatie noua cu alte valori") + 10);
    Button operatieNouaAceleasiVal = Button("Operatie noua cu aceleasi valori", operatieNouaAlteVal.getTopL() + coord(0, -textheight("Operatie noua cu aceleasi valori") - 20), textwidth("Operatie noua cu aceleasi valori") + 10, textheight("Operatie noua cu aceleasi valori") + 10);
    Button iesire = Button("Iesire din program", coord(30, back.getTopL().y), textwidth("Iesire din program") + 10, textheight("Iesire din program") + 10);

    while(!GetAsyncKeyState(VK_ESCAPE)
            && !back.getSelected()
            && !operatieNouaAlteVal.getSelected()
            && !operatieNouaAceleasiVal.getSelected()
            && !iesire.getSelected())
        {
            //swapbuffers();
            mouseUpdate(&mouse);

            back.draw();
            operatieNouaAlteVal.draw();
            operatieNouaAceleasiVal.draw();
            iesire.draw();

            if(back.pointInCell(mouse.x, mouse.y) && (mouse.LMBClick || mouse.RMBClick))
                back.setSelected(true);

            if(operatieNouaAlteVal.pointInCell(mouse.x, mouse.y) && (mouse.LMBClick || mouse.RMBClick))
                operatieNouaAlteVal.setSelected(true);

            if(operatieNouaAceleasiVal.pointInCell(mouse.x, mouse.y) && (mouse.LMBClick || mouse.RMBClick))
                operatieNouaAceleasiVal.setSelected(true);

            if(iesire.pointInCell(mouse.x, mouse.y) && (mouse.LMBClick || mouse.RMBClick))
                iesire.setSelected(true);
        }

    if(back.getSelected())
        {
            closegraph();
            back.setSelected(false);
            citireValoriNoi = true;
            application();
        }

    if(operatieNouaAlteVal.getSelected())
        {
            closegraph();
            operatieNouaAlteVal.setSelected(false);
            citireValoriNoi = true;
            application();
        }

    if(operatieNouaAceleasiVal.getSelected())
        {
            closegraph();
            operatieNouaAceleasiVal.setSelected(false);
            citireValoriNoi = false;
            application();
        }

    if(iesire.getSelected())
        {
            closegraph();
            iesire.setSelected(false);
            return;
        }
    closegraph();
}

int main()
{
    application();
    return 0;
}
