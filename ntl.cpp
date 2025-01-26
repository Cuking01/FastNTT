#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <iostream>
#include <chrono>

using namespace NTL;
using namespace std;

int main() {
    // 设置有限域的模数
    ZZ p = conv<ZZ>("469762049"); // 一个大型素数
    ZZ_p::init(p);

    // 初始化多项式
    ZZ_pX f, g, h;
    random(f, 1 << 15); // 随机生成 2^15 次的多项式
    random(g, 1 << 15);

    // 测量时间
    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++)
        h = f * g; // 多项式乘法
    auto end = chrono::high_resolution_clock::now();

    cout << "Multiplication time: "
         << chrono::duration<double>(end - start).count()
         << " seconds" << endl;

    return 0;
}
