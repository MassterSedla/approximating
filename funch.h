#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <graphics.h>


void graphics(float a[],float b[],float c[],float d[],int n,float y[],float x[])
{

int driver, mode;
driver = DETECT;
mode = 0;
initgraph(&driver, &mode, " " );
float X;
float Y;

for(int i=1;i<=n;i++)
{
    line(50+5+x[i]*40,350-y[i]*30,50+x[i]*40-5,350-y[i]*30);
    line(50+x[i]*40,350-y[i]*30+5,50+x[i]*40,350-y[i]*30-5);
}

line(50,0,50,480);
line(50,350,640,350);
Y = a[1]+b[1]*x[1]+c[1]*pow(x[1],2)+d[1]*pow(x[1],3);
moveto(50+x[1]*40,350-Y*30);
X=x[1];
for(int i=1;i<n;i++)
{
    for(float j = x[i];j <= x[i+1]; j+=0.1)
    {
        X=j;
        Y = a[i]+b[i]*X+c[i]*pow(X,2)+d[i]*pow(X,3);
        lineto(50+X*40,350-Y*30);
    }
}
moveto(0,0);
outtext("Аппроксимация кубическим сплайном");
getch();
closegraph();
}