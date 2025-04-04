#include "ntt.cpp"
#include "../CuSDK/basis.h"
#include<random>
#include<time.h>


void print(u2*a,int n)
{
	printf("n=%d\n",n);
	for(int i=0;i<n;i++)
		printf("%u ",a[i]);
	puts("");
}

double test(int n,int k)
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

	int st=clock();

	for(int i=0;i<k;i++)
	{
		memcpy(a,at,n*2*4);
		memcpy(b,bt,n*2*4);
		poly_multiply(a,n-1,b,n-1,c);
	}

	int ed=clock();
	u3 fa=0;
	u3 fb=0;
	u3 fc=0;

	u3 xp=1;
	u2 x=17;

	constexpr u2 mod=469762049;

	//print(at,n);
	//print(bt,n);
	//print(c,2*n);

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

	//printf("%dx%d %d\n",k,n,ed-st);
	if(fa*fb%mod!=fc)puts("err");

	return ed-st;
}



void test_mt(int len,int times,int times2)
{
    std::vector<double> record(times2);

    for(int i=0;i<1;i++)
    {
        test(len,times);
    }

    for(int i=0;i<times2;i++)
    {
        record[i]=test(len>>1,times)/1000;
        printf("第%d次：%.2lfms\n",i+1,record[i]);
    }
    
    std::sort(record.begin(),record.end());

    printf("\n最小值 %.2lfms\n",record[0]);
    printf("最大值 %.2lfms\n\n",record[times2-1]);

    double sum=0;

    for(int i=0;i<record.size();i++)
        sum+=record[i];
    double avg=sum/times2;
    double s2=0;
    for(int i=0;i<record.size();i++)
        s2+=(avg-record[i])*(avg-record[i]);
    
    s2/=times2-1;

    double s=sqrt(s2);
    double se=s/sqrt(times2);

    printf("长度=%d 次数=%d\n",len,times);

    printf("平均时间：%.2lfms\n",avg);
    printf("标准差：%.2lfms\n",s);
    printf("标准误差：%.2lfms\n\n",se);

    printf("times=%.2lf(%.2lf)ms\n\n\n",avg,se*2);
}


int main()
{
	
	test_mt(1<<10,1<<12,30);
    test_mt(1<<15,1<<7,30);
    test_mt(1<<20,1<<2,30);
}
