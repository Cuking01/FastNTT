#include "ntt.cpp"
#include<random>
#include<time.h>


void print(unsigned*a,int n)
{
	for(int i=0;i<n;i++)
		printf("%u ",a[i]);
	puts("");
}

void test(int n)
{
	static unsigned a[1<<24],b[1<<24],c[1<<24];
	std::mt19937 rnd(10);
	for(int i=0;i<n;i++)
	{
		a[i]=rnd()%10;
		b[i]=rnd()%10;
	}

	int k=(1<<24)/n;

	int st=clock();

	for(int i=0;i<k;i++)
		poly_multiply(a,n-1,b,n-1,c);

	int ed=clock();

	unsigned long long fa=0;
	unsigned long long fb=0;
	unsigned long long fc=0;

	unsigned long long xp=1;
	unsigned x=17;

	constexpr unsigned mod=998244353;

	// print(a,n);
	// print(b,n);
	// print(c,2*n);

	for(int i=0;i<n;i++)
	{
		fa=(fa+(UL)a[i]*xp)%mod;
		fb=(fb+(UL)b[i]*xp)%mod;
		xp=xp*x%mod;
	}
	xp=1;
	for(int i=0;i<2*n;i++)
	{
		fc=(fc+(UL)c[i]*xp)%mod;
		xp=xp*x%mod;
	}

	printf("%dx%d %d\n",k,n,ed-st);
	if(fa*fb%mod!=fc)puts("err");
}

int main()
{
	for(int i=1<<8;i<=(1<<21);i<<=1)
	{
		test(i);
	}
}
