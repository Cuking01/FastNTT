#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace NTL;
using namespace std;

double test_one(int len,int times)
{
    // 设置有限域的模数
    ZZ p = conv<ZZ>("998244353"); // 一个大型素数
    ZZ_p::init(p);

    // 初始化多项式
    ZZ_pX f, g, h;
    random(f, len>>1);
    random(g, len>>1);

    // 测量时间
    auto start = chrono::high_resolution_clock::now();

    for(int i=0;i<times;i++)
        h = f * g; // 多项式乘法
    auto end = chrono::high_resolution_clock::now();
    
    return chrono::duration<double>(end - start).count()*1000;
         
}

void test_mt(int len,int times,int times2)
{
    std::vector<double> record(times2);

    for(int i=0;i<1;i++)
    {
        test_one(len,times);
    }

    for(int i=0;i<times2;i++)
    {
        record[i]=test_one(len,times);
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

int main() {
    
    test_mt(1<<10,1<<12,30);
    test_mt(1<<15,1<<7,30);
    test_mt(1<<20,1<<2,30);
    return 0;
}
