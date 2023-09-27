#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <float.h>
#include <math.h>
#include "func.h"

//##########################################################
void range(float x[],float y[],int n)
{
    for(int i=1;i<=n;i++)
    {
        if( x[i] > FLT_MAX || x[i] < (-1*FLT_MAX) || y[i] < (-1*FLT_MAX) || y[i] > FLT_MAX)
        {
            printf("ОШИБКА: выход за диапазон");
            exit(1);
        }
    }
}
//##########################################################
void checkT(float num) // проверка на некорректные символы
{
    if((num/num != 1) || (num == 0)){
    printf("ОШИБКА: Введите число ");
    exit(1);
}
}
//##########################################################
void aoao(float x[],float y[],int n)
{
    for(int i=1;i<=n;i++)
    {
        float q=x[i];
        float w=y[i];
        for(int j=1;j<=n;j++)
        {
            if(q == x[j] && w!= y[j])
            {
                printf("ОШИБКА:Неоднозначность");
                exit(1);
            }
        }
    }
}

void a1(float x[],float y[],int n, float swp)
{
    for (int i=1; i<=n; i+=2)
    {
        if (x[i]>x[i+1])
        {
            swp = x[i];
            x[i]=x[i+1];
            x[i+1]=swp;

            swp = y[i];
            y[i]=y[i+1];
            y[i+1]=swp;
        }
    }
}

void a2(float x[],float y[],int n, int k, float swp)
{
    int p=0;
    for (int i=1; i<=n; i+=k)
    {
        for (int j=1; j<=(k/2); j++)
        {
            if (x[p+j]>x[p+k+1-j])
            {
                swp = x[p+j];
                x[p+j]=x[p+k+1-j];
                x[p+k+1-j]=swp;

                swp = y[p+j];
                y[p+j]=y[p+k+1-j];
                y[p+k+1-j]=swp;
            }

        }
        p+=k;
    }
}

void a3(float x[],float y[],int n, int k, float swp)
{
    int p=0;
    for (int i=1; i<=n; i+=k)
    {
        for (int j=1; j<=k/2; j++)
        {
            if (x[p+j]>x[p+j+k/2])
            {
                swp = x[p+j];
                x[p+j]=x[p+j+k/2];
                x[p+j+k/2]=swp;

                swp = y[p+j];
                y[p+j]=y[p+j+k/2];
                y[p+j+k/2]=swp;
            }
        }
        p+=k;
    }
}



int main()
{
setlocale(LC_ALL, "RUS");
float temp,swp,x[20],y[20];
int sw,n,l;
printf("Введите количество строк в файле: ");
scanf("%d",&n);
if(n<8)
    n=8;
else if(n<16)
    n=16;
FILE *file = fopen("test.txt","r");
FILE *out = fopen("out.txt","w");


while(!feof(file))
    for(int i=1;i<=n;i++)
        {
        temp=(fscanf(file,"%f,%f",&x[i],&y[i]));
        checkT(temp);
        }

range(x,y,n);
aoao(x,y,n);

a1(x, y, n, swp);
a2(x, y, n, 4, swp);
a1(x, y, n, swp);
a2(x, y, n, 8, swp);
a3(x, y, n, 4, swp);
a1(x, y, n, swp);
if (n>8)
{
    a2(x, y, n, 16, swp);
    a3(x, y, n, 8, swp);
    a3(x, y, n, 4, swp);
    a1(x, y, n, swp);
}

l=0;
float h=6666.66;
for (int i=1; i<=n; i++)
    {
        if(x[i]==h && y[i]==h)
            l++;
    }
n=n-l;


printf(" 0. Вывести координаты на экран\n");
printf(" 1. Вывести координаты в файл\n");
printf(" Ввод: ");
scanf("%d", &sw);
switch(sw)
{
case 0:
    printf("\n Координаты (X,Y), отсортированные по Х:");
    for(int i=1;i<=n;i++)
    {
        printf("\n X:%3.2f  Y:%3.2f",x[i],y[i]);
    }
    break;
case 1:
    fprintf(out, "\n Координаты (X,Y), отсортированные по Х:");
    for(int i=1;i<=n;i++)
    {
        fprintf(out, "\n X:%3.2f  Y:%3.2f", x[i],y[i]);
    }
    break;
}



int N=(n-1)*4;
float a[n-1],b[n-1],c[n-1],d[n-1];
double Q[N][N+1];

int i,j,k;
k=2;

for(int i=1;i<=N;i++)
{
    for(int j=1;j<=N+1;j++)
    {
        Q[i][j]=0;
    }
}

Q[1][1]=0;
Q[1][2]=0;
Q[1][3]=2;
Q[1][4]=6*x[1];
Q[1][N+1]=0;

Q[N][N-3]=0;
Q[N][N-2]=0;
Q[N][N-1]=2;
Q[N][N]=6*x[n];
Q[N][N+1]=0;

l=1;

for(i=1;i<=N;i++)
{
    for(j=k;j<k+2;j++)
    {
        Q[j][i]=1;
        Q[j][i+1]=x[l];
        Q[j][i+2]=pow(x[l],2);
        Q[j][i+3]=pow(x[l],3);
        Q[j][N+1]=y[l];

        if(j==k+1)
        {
            if(l<n)
            {
                Q[j+1][i]=0;
                Q[j+1][i+1]=1;
                Q[j+1][i+2]=2*x[l];
                Q[j+1][i+3]=3*pow(x[l],2);
                Q[j+1][N+1]=0;

                Q[j+1][i+4]=0;
                Q[j+1][i+5]=(-1)*Q[j+1][i+1];
                Q[j+1][i+6]=(-1)*Q[j+1][i+2];
                Q[j+1][i+7]=(-1)*Q[j+1][i+3];

                Q[j+2][i]=0;
                Q[j+2][i+1]=0;
                Q[j+2][i+2]=2;
                Q[j+2][i+3]=6*x[l];
                Q[j+2][N+1]=0;

                Q[j+2][i+4]=0;
                Q[j+2][i+5]=0;
                Q[j+2][i+6]=(-1)*Q[j+2][i+2];
                Q[j+2][i+7]=(-1)*Q[j+2][i+3];
            }
        }
        l++;
    }
    l--;
    k+=4;
    i=k-2;
}



for(j=1;j<=3;j++)
{
    for(i=1;i<=N+1;i++)
    {
        swp = Q[j][i];
        Q[j][i]=Q[j+1][i];
        Q[j+1][i]=swp;
    }
}

printf("\n\n 0. Не выводить начальную матрицу по системе уравнений\n");
printf(" 1. Вывести начальную матрицу на экран\n");
printf(" 2. Вывести начальную матрицу в файл\n");
printf(" Ввод: ");
scanf("%d", &sw);
switch(sw)
{
case 0:
    break;
case 1:
    printf("\n\nВид начальной матрицы:");
    for(int i=1;i<=N;i++)
    {
        printf("\n\n%d.",i);
        for(int j=1;j<=N+1;j++)
        {
            printf("  %.2f",Q[i][j]);
        }
    }
    break;
case 2:
    fprintf(out, "\n\nВид начальной матрицы:");
    for(int i=1;i<=N;i++)
    {
        fprintf(out, "\n\n%d.",i);
        for(int j=1;j<=N+1;j++)
        {
            fprintf(out, "  %.2f",Q[i][j]);
        }
    }
    break;
}


for(j=1;j<=N+1;j++)
{
    for(i=j+1;i<=N;i++)
    {
        if(Q[j][j]==0)
        {
            for(int o=j;o<=N+1;o++)
            {
                swp = Q[i][o];
                Q[i][o]=Q[i-1][o];
                Q[i-1][o]=swp;
            }
        }

        if(Q[i][j]!=0)
        {
            float mn=Q[i][j]/Q[j][j];
            for(int o=j;o<=N+1;o++)
                Q[i][o]-=Q[j][o]*mn;
        }
    }
}

printf("\n\n 0. Не выводить решенную матрицу по системе уравнений\n");
printf(" 1. Вывести решенную матрицу на экран\n");
printf(" 2. Вывести решенную матрицу в файл\n");
printf(" Ввод: ");
scanf("%d", &sw);
switch(sw)
{
case 0:
    break;
case 1:
    printf("\n\nВид решенной матрицы:");
    for(int i=1;i<=N;i++)
    {
        printf("\n\n%d.",i);
        for(int j=1;j<=N+1;j++)
        {
            printf("  %.2f",Q[i][j]);
        }
    }
    break;
case 2:
    fprintf(out, "\n\nВид решенной матрицы:");
    for(int i=1;i<=N;i++)
    {
        fprintf(out, "\n\n%d.",i);
        for(int j=1;j<=N+1;j++)
        {
            fprintf(out, "  %.2f",Q[i][j]);
        }
    }
    break;
}

l=n-1;
float mn=0;
d[l]=Q[N][N+1]/Q[N][N];
for(i=N-1;i>=1;i--)
{
    mn=0;
    for(j=i+1;j<=N;j++)
    {
        if(j%4==1)
            mn+=a[(j-j%4+4)/4]*Q[i][j];
        else if(j%4==2)
            mn+=b[(j-j%4+4)/4]*Q[i][j];
        else if(j%4==3)
            mn+=c[(j-j%4+4)/4]*Q[i][j];
        else if(j%4==0)
            mn+=d[(j-j%4)/4]*Q[i][j];
    }

    if(i%4==1)
        a[l]=(Q[i][N+1]-mn)/Q[i][i];
    else if(i%4==2)
        b[l]=(Q[i][N+1]-mn)/Q[i][i];
    else if(i%4==3)
        c[l]=(Q[i][N+1]-mn)/Q[i][i];
    else if(i%4==0)
        d[l]=(Q[i][N+1]-mn)/Q[i][i];
    if(i==4*l-3)
       l-=1;
}

printf("\n\n 0. Не выводить коэффициенты полиномов\n");
printf(" 1. Вывести коэффициенты полиномов на экран\n");
printf(" 2. Вывести коэффициенты полиномов в файл\n");
printf(" Ввод: ");
scanf("%d", &sw);
switch(sw)
{
case 0:
    break;
case 1:
    printf("\n\n Коэффициенты полиномов:");
    for(i=1;i<=n-1;i++)
        printf("\n a%d = %.2f  b%d = %.2f  c%d = %.2f d%d = %.2f", i, a[i], i, b[i], i, c[i], i, d[i]);

    break;
case 2:
    fprintf(out, "\n\n Коэффициенты полиномов:");
    for(i=1;i<=n-1;i++)
        fprintf(out, "\n a%d = %.2f  b%d = %.2f  c%d = %.2f d%d = %.2f", i, a[i], i, b[i], i, c[i], i, d[i]);

    break;
}

printf("\n\n Итоговый вид функции:");
for(i=1;i<=n-1;i++)
{
    int u = i+1;
    printf("\n От x%d до x%d: y = a%d + b%d*x + c%d*x^2 + d%d*x^3", i, u, i, i, i, i);
}
fprintf(out, "\n\n Итоговый вид функции:");
for(i=1;i<=n-1;i++)
{
    int u = i+1;
    fprintf(out, "\n От x%d до x%d: y = a%d + b%d*x + c%d*x^2 + d%d*x^3", i, u, i, i, i, i);
}


printf("\n\n Итоговый вид функции с найденными коэффициентами:");
for(i=1;i<=n-1;i++)
{
    int u = i+1;
    printf("\n От x%d до x%d: y = %.2f + %.2f*x + %.2f*x^2 + %.2f*x^3", i, u, a[i], b[i], c[i], d[i]);
}
fprintf(out, "\n\n Итоговый вид функции с найденными коэффициентами:");
for(i=1;i<=n-1;i++)
{
    int u = i+1;
    fprintf(out, "\n От x%d до x%d: y = %.2f + %.2f*x + %.2f*x^2 + %.2f*x^3", i, u, a[i], b[i], c[i], d[i]);
}
    graphics(a,b,c,d,n,y,x);
    break;


fclose(file);
fclose(out);
}
return 0;
}
