#include <hexl/hexl.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include<time.h>
int main() {
    using namespace intel::hexl;

    // 模数 q，通常选择满足 (q - 1) 是 2 的幂的素数
    uint64_t modulus = 998244353; // 示例模数，满足 (q-1) = 2^p

    // 多项式的长度（必须是 2 的幂）
    size_t poly_degree = 1<<21;

    // 定义两个多项式（填充为 2 的幂长度）
    std::vector<uint64_t> poly1(poly_degree);// = {1, 2, 3, 4, 0, 0, 0, 0};
    std::vector<uint64_t> poly2(poly_degree);// = {5, 6, 7, 8, 0, 0, 0, 0};

    

    // 输出结果多项式
    std::vector<uint64_t> result(poly_degree);

    // 定义 NTT 对象
    // 根数 = 3，modulus 是一个满足要求的素数
    NTT ntt(poly_degree, modulus);

    int start=clock();

    // 对 poly1 和 poly2 执行前向 NTT

    for(size_t i=0;i<poly_degree;i++)
        {
            poly1[i]=i<poly_degree/2?i:0;
            poly2[i]=i<poly_degree/2?i:0;
        }

    for(int j=0;j<10;j++)
    {
        

        ntt.ComputeForward(poly1.data(), poly1.data(), modulus, 1); // inplace 计算
        ntt.ComputeForward(poly2.data(), poly2.data(), modulus, 1); // inplace 计算


        EltwiseMultMod(result.data(),poly1.data(),poly2.data(),poly_degree,modulus,1);
        // // 在 NTT 空间执行逐点乘法
        // for (size_t i = 0; i < poly_degree; ++i) {
        //     result[i] = MultiplyMod(poly1[i], poly2[i], modulus);
        // }

        // 对结果执行逆向 NTT
        ntt.ComputeInverse(result.data(), result.data(), modulus, 1); // inplace 逆 NTT
    }

    
    int end=clock();
    // 打印最终结果
    std::cout << "Resultant polynomial: ";
    for (size_t i = 0; i < poly_degree&&i<20; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
    printf("\n time=%d\n",end-start);
    return 0;
}
