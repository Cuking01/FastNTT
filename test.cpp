#include "ntt.cpp"
#include "../CuSDK/basis.h"
#include<random>
#include<time.h>


void print(u2*a,int n)
{
	for(int i=0;i<n;i++)
		printf("%u ",a[i]);
	puts("");
}

void test(int n)
{
	alignas(64) static u2 a[(1<<24)+16],b[(1<<24)+16],c[1<<24];
	alignas(64) static u2 at[1<<24],bt[1<<24];
	std::mt19937 rnd(10);
	for(int i=0;i<n;i++)
	{
		a[i]=rnd()%10;
		b[i]=rnd()%10;
		a[i+n]=0;
		b[i+n]=0;
		at[i]=a[i];
		bt[i]=b[i];
		at[i+n]=a[i+n];
		bt[i+n]=b[i+n];
	}

	int k=(1<<29)/n;

	int st=clock();

	for(int i=0;i<k;i++)
	{
		//memcpy(a,at,n*2*4);
		//memcpy(b,bt,n*2*4);
		poly_multiply(a,n-1,b,n-1,c);
	}

	int ed=clock();
	u3 fa=0;
	u3 fb=0;
	u3 fc=0;

	u3 xp=1;
	u2 x=17;

	constexpr u2 mod=469762049;

	// print(at,n);
	// print(bt,n);
	// print(c,2*n);

	for(int i=0;i<n;i++)
	{
		fa=(fa+(u3)at[i]*xp)%mod;
		fb=(fb+(u3)bt[i]*xp)%mod;
		xp=xp*x%mod;
	}
	xp=1;
	for(int i=0;i<2*n;i++)
	{
		fc=(fc+(u3)c[i]*xp)%mod;
		xp=xp*x%mod;
	}

	printf("%dx%d %d\n",k,n,ed-st);
	if(fa*fb%mod!=fc)puts("err");
}

int main()
{
	for(int i=1<<10;i<=(1<<20);i<<=1)
	{
		test(i);
	}
}
