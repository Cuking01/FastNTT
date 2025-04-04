#include <hexl/hexl.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include<time.h>

double test_one(int len,int times)
{
    using namespace intel::hexl;

    // 模数 q，通常选择满足 (q - 1) 是 2 的幂的素数
    uint64_t modulus = 998244353; // 示例模数，满足 (q-1) = 2^p

    // 多项式的长度（必须是 2 的幂）
    size_t poly_degree = len;

    // 定义两个多项式（填充为 2 的幂长度）
    std::vector<uint64_t> poly1(poly_degree);// = {1, 2, 3, 4, 0, 0, 0, 0};
    std::vector<uint64_t> poly2(poly_degree);// = {5, 6, 7, 8, 0, 0, 0, 0};

    

    // 输出结果多项式
    std::vector<uint64_t> result(poly_degree);

    // 定义 NTT 对象
    // 根数 = 3，modulus 是一个满足要求的素数
    NTT ntt(poly_degree, modulus);

    

    // 对 poly1 和 poly2 执行前向 NTT

    for(size_t i=0;i<poly_degree;i++)
        {
            poly1[i]=i<poly_degree/2?i:0;
            poly2[i]=i<poly_degree/2?i:0;
        }

    int start=clock();

    for(int j=0;j<times;j++)
    {
        

        ntt.ComputeForward(poly1.data(), poly1.data(), modulus, 1); // inplace 计算
        ntt.ComputeForward(poly2.data(), poly2.data(), modulus, 1); // inplace 计算


        EltwiseMultMod(result.data(),poly1.data(),poly2.data(),poly_degree,modulus,1);
        
        ntt.ComputeInverse(result.data(), result.data(), modulus, 1); // inplace 逆 NTT
    }

    
    int end=clock();
    return (end-start)/1000.0;
    
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
