/*
 Jezyk programowania: C/C++
 Środowisko programistyczne: Visual Studio
 Algorytm: Kolorowanie Grafu
 Opis: w pliku readme
 Autor: Lukasz Golojuch
 */
#include <iostream>
#include <string>
using namespace std;
int n; // zmienna pomocnicza
int tablica[70][70]; // tablica przechowujaca graf
int tablica_pom[70][70]; // tablica pomocnicza przechowujaca graf
bool t_przej[70]; //bylismy ale nie sprawdzilismy
bool t_odw[70]; // bylismy i sprawdzilismy
int najwiekszy[70]; // przechowuje jeden z grafow o stopniu rownym max_st
int max_st; // przechowuje najwiekszy stopien grafu
int l; // zmienna pomocnicza
int ilosc_najwiekszych; // przechowuje ilosc grafow o stopniu rownym max_st
int poczatek;
int w; // przechowuje ilosc lisci

bool graf_pelny_niespojny()
{
    for(int i=1; i<=w; i++)
    {
        l=0;
        for(int j=1; j<=w; j++)
        {
            if(tablica_pom[i][j]==1)
            {
                l++;
            }
        }
        if(l!=w-1)
        {
            return false;
        }
    }
    return true;
}

/*
 Funkcja cykl_niespojny():
 
 Funkcja sprawdzajaca czy graf posiada cykl, ktory jednoczesnie jest cyklem niespojnym.
 
 Funkcja zwraca wartosc true jesli graf posiada cykl niespojny, a false w przeciwynym wypadku.
*/
bool cykl_niespojny()
{
    if((w&1)==0)
    {
        return false;
    }
    for(int i=1; i<=w; i++)
    {
        l=0;
        for(int j=1; j<=w; j++)
        {
            if(tablica_pom[i][j]==1)
            {
                l++;
            }
        }
        if(l!=2)
        {
            return false;
        }
    }
    return true;
}
/*
 Funkcja generujaca tablice pomocnicza w celu ochrony glownej tablicy przed zmianami i przyszlymi bledami
*/
void generuj_tablice_pomocnicza()
{
    for(int i=0; i<=w; i++)
    {
        for(int j=0; j<=w; j++)
        {
            tablica_pom[i][j]=0;
        }
    }
    int licznik=1;
    for(int i=1;i<=n;i++)
    {
        if(t_przej[i]==1)
        {
            tablica_pom[licznik][0]=i;
            tablica_pom[0][licznik]=i;
            licznik++;
        }
    }
    int x,y;
    for(int i=1; i<=w; i++)
    {
        for(int j=1; j<=w; j++)
        {
            x=tablica_pom[i][0];
            y=tablica_pom[0][j];
            tablica_pom [i][j] = tablica[x][y];
        }
    }
}

/*
 
*/
void ilosc_lisci()
{
    w=0;
    for(int i=1; i<=n; i++)
    {
        if(t_przej[i]==1)
        {
            w++;
        }
    }
}
/*
 Funkcja przeszukujaca w których miejscach tablicy nie zostalo wykonane sprawdzenie
*/
int niesprawdzone()
{
    for(int i=1; i<=n; i++)
    {
        if(t_przej[i]==1 && t_odw[i]==0)
        {
            t_odw[i]=1;
            return i;
        }
    }
    return 0;
}

/*
 Funkcja majaca swoje zastosowanie w momencie kiedy graf nie jest grafem spojnym.
*/
bool kiedy_spojny()
{
    int p;
    for(int i=1; i<=ilosc_najwiekszych; i++)
    {
        poczatek = najwiekszy[i];
        for(int i=0; i<=n; i++)
        {
            t_przej[i]=0;
            t_odw[i]=0;
        }
        p=poczatek;
        while(p!=0)
        {
            for(int j=1; j<=n; j++)
            {
                if(tablica[p][j]==1)
                {
                    t_przej[j]=1;
                }
            }
            p=niesprawdzone();
        }
        ilosc_lisci();
        generuj_tablice_pomocnicza();
        if(cykl_niespojny()||graf_pelny_niespojny())
        {
            return true;
        }
    }
    return false;
}

void najwyzszy_wiersz()
{
    for(int i=0; i<=n; i++)
    {
        najwiekszy[i]=0;
    }
    int pom;
    ilosc_najwiekszych=0;
    int licznik;
    for(int i=1; i<=n; i++)
    {
        licznik=0;
        pom=i;
        for(int j=1; j<=n; j++)
        {
            if(tablica[i][j]==1)
            {
                licznik++;
            }
        }
        if(licznik==max_st)
        {
            ilosc_najwiekszych++;
            najwiekszy[ilosc_najwiekszych]=pom;
        }
    }
}

int pierwszy()
{
    for(int i=1;i<=n; i++)
    {
        if(t_przej[i] == true && t_odw[i]==false)
        {
            t_odw[i]=true;
            return i;
        }
    }
    for(int i=1; i<=n; i++)
    {
        if(t_odw[i]==0)
        {
            return -1;
        }
    }
    return 0;
}
/*
 Funkcja sprawdzajaca czy graf jest grafem spojnym.
*/
bool spojny()
{
    for(int i=2; i<=n; i++)
    {
        t_przej[i]=0;
        t_odw[i]=0;
    }
    t_odw[1]=1;
    t_przej[1]=1;
    int p=1;
    while(p!=0 && p!=-1)
    {
        for(int i=1; i<=n; i++)
        {
            if(tablica[i][p]==1 && t_przej[i]!=1)
            {
                t_przej[i]=1;
            }
        }
        p=pierwszy();
    }
    if(p==0)
    {
        return true;
    }
    return false;
}
/*
 Funkcja sprawdzajaca czy graf jest grafem pelnym
*/
bool graf_pelny()
{
    for(int i=1; i<=n; i++)
    {
        l=0;
        for(int j=1; j<=n; j++)
        {
            if(tablica[i][j]==1)
            {
                l++;
            }
        }
        if(l!=n-1)
        {
            return false;
        }
    }
    return true;
}

/*
 Funkcja sprawdzajaca czy graf posiada cykl
*/
bool cykl()
{
    if((n&1)==0)
    {
        return false;
    }
    for(int i=1; i<=n; i++)
    {
        l=0;
        for(int j=1; j<=n; j++)
        {
            if(tablica[i][j]==1)
            {
                l++;
            }
        }
        if(l!=2)
        {
            return false;
        }
    }
    return true;
}


int main() {
    int ilosc; // przechowuje ilosc grafow ktora bedzie sprawdzana
    
    // pobieramy ilosc grafow do sprawdzenia
    scanf ("%d",&ilosc);
    string graf;
    int p;

    int dl;
    for(int i=0; i<ilosc; i++)
    {
        l=0;
        max_st=0;
        scanf ("%d",&n);
        cin>>graf;
        for(int i=1;i<=n;i++)
        {
            tablica[i][0]=i;
            tablica[0][i]=i;
        }
        for(int i=1; i<=n; i++)
        {
            p=0;
            for(int j=1; j<=n; j++)
            {
                dl =int(graf[l])-48;
                tablica[i][j]=dl;
                if(dl==1)
                {
                    p++;
                }
                l++;
            }
            if(p>max_st)
            {
                max_st=p;
            }
        }
        if(spojny())
        {
            if(graf_pelny() || cykl())
            {
                printf("True \n");
            }else
            {
                printf("False \n");
            }
        }
        else
        {
            najwyzszy_wiersz();
            if(kiedy_spojny())
            {
                printf("True \n");
            }else
            {
                printf("False \n");
            }
        }
    }
    return 0;
}


