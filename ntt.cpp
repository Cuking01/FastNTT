#include "../CuSDK/basis.h"
#include "../CuSDK/simd.h"


static constexpr u2 mod=998244353;

static constexpr u2 pow_no_mod(u2 a,u2 b)
{
    u2 ans=1;
    while(b)
    {
        if(b&1)ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans;
}

struct ZF
{
    static constexpr u2 pow(u2 a,u2 b)
    {
        u2 ans=1;
        while(b)
        {
            if(b&1)ans=(u3)ans*a%mod;
            a=(u3)a*a%mod;
            b>>=1;
        }
        return ans;
    }
};



struct Mogo_F
{
    static constexpr u2 mod=::mod;
    static constexpr u2 yi=((1ull<<62)+mod-1)/mod-(1ull<<32);
    static constexpr u2 modp=pow_no_mod(mod,(1u<<31)-1);

    static constexpr u2 jmod(u2 x)
    {
        return x>=mod?x-mod:x;
    }

    static constexpr u2 mul(u2 a,u2 b)
    {
        u3 x=(u3)a*b;
        u2 t=x*modp;
        u2 m=(u3)t*mod>>32;
        u2 xh=x>>32;
        return jmod(xh-m+mod);
    }

    static constexpr u2 pow(u2 a,u2 b)
    {
        u2 ans=(1ull<<32)%mod;
        while(b)
        {
            if(b&1)ans=mul(ans,a);
            a=mul(a,a);
            b>>=1;
        }
        return ans;
    }

    static constexpr u2 to_mf(u2 x)
    {
        return ((u3)x<<32)%mod;
    }

    static constexpr u2 to_zf(u2 x)
    {
        return mul(x,1);
    }

    //结果应该为0时可能得到结果为mod。
    template<u2 n>
    ALWAYS_INLINE static void jmod(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> tmp,const VU32x8&vmod)
    {
        tmp=a.template as<VI32x8>() > vmod.template as<VI32x8>();
        tmp=tmp&vmod;
        a=a-tmp;
    }

    template<u2 n,bool j_mod=true>
    ALWAYS_INLINE static void mul_3(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> b,Pack_Ref<VU32x8,n> t,VU32x8& vmod,VU32x8& vmodp)
    {
        using w64=VU64x4;
        auto ap=a.template as<w64>();
        auto bp=b.template as<w64>();
        auto tp=t.template as<w64>();

        tp=a*b; //t0

        ap=ap>>cint<32>;
        bp=bp>>cint<32>;
        bp=a*b; //t1

        ap=t*vmodp;  //t0
        
        tp=tp>>cint<32>;
        t=blend(t,b,cint<0b1010'1010>);
        
        bp=b*vmodp; //t1
        ap=a*vmod;

        t=t+vmod;
        bp=b*vmod;
        
        ap=ap>>cint<32>;
        a=blend(a,b,cint<0b1010'1010>);
        a=t-a;

        if constexpr(j_mod)
            jmod<n>(a,t,vmod);
    }

    template<u2 n,bool j_mod=true>
    ALWAYS_INLINE static void mul_4(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> b,Pack_Ref<VU32x8,n> t0,Pack_Ref<VU32x8,n> t1,const VU32x8& vmod,const VU32x8& vmodp)
    {
        using w64=VU64x4;
        auto ap=a.template as<w64>();
        auto bp=b.template as<w64>();
        auto tp0=t0.template as<w64>();
        auto tp1=t1.template as<w64>();

        tp0=a*b;
        ap=ap>>cint<32>;
        bp=bp>>cint<32>;

        tp1=a*b;

        ap=t0*vmodp;  //t0
        bp=t1*vmodp;  //t1
        
        tp0=tp0>>cint<32>;
        t0=blend(t0,t1,cint<0b1010'1010>);

        ap=a*vmod;
        bp=b*vmod;

        t0=t0+vmod;
        
        ap=ap>>cint<32>;
        a=blend(a,b,cint<0b1010'1010>);
        a=t0-a;

        if constexpr(j_mod)
            jmod<n>(a,t0,vmod);
    }

    template<u2 n>
    ALWAYS_INLINE static void to_mf(Pack_Ref<VU32x8,n> x,Pack_Ref<VU32x8,n> t0,Pack_Ref<VU32x8,n> t1,const VU32x8&vyi,const VU32x8&vmod)
    {
        using w64=VU64x4;

        auto xp=x.template as<w64>();
        auto tp0=t0.template as<w64>();
        auto tp1=t1.template as<w64>();

        x=x<<cint<2>;
        tp1=xp>>cint<32>;
        tp0=x*vyi;
        tp1=t1*vyi;
        tp0=tp0>>cint<32>;
        t1=t1+x;
        t0=t0+x;
        tp1=tp1>>cint<32>;
        tp0=t0*vmod;
        tp1=t1*vmod;
        tp1=tp1<<cint<32>;
        x=blend(t0,t1,cint<0xaa>);
        t0[0]=t0[0]^t0[0];
        x=t0[0]-x;
    }

    template<u2 n>
    ALWAYS_INLINE static void to_zf(Pack_Ref<VU32x8,n> x,Pack_Ref<VU32x8,n> t0,Pack_Ref<VU32x8,n> t1,VU32x8&vmod,VU32x8&vmodp)
    {
        using w64=VU64x4;

        auto xp=x.template as<w64>();
        auto tp0=t0.template as<w64>();
        auto tp1=t1.template as<w64>();

        tp0=x*vmodp;
        xp=xp>>cint<32>;
        tp1=x*vmodp;
        tp0=t0*vmod;
        tp1=t1*vmod;
        tp0=tp0>>cint<32>;
        x=blend(t0,t1,cint<0xaa>);
        x=vmod-x;
        jmod<n>(x,t0,vmod);
    }

    static void arr_to_mf(const u2*arr,u2*to,u3 len)
    {
        u3 i;
        Pack<VU32x8,4> x,t0,t1;
        VU32x8 vmod=set1(mod),vyi=set1(yi);
        for(i=0;i+31<len;i+=32)
        {
            x.loadu(arr+i);
            to_mf<4>(x,t0,t1,vyi,vmod);
            x.storeu(to+i);
        }
        for(;i+7<len;i+=8)
        {
            x[0].loadu(arr+i);
            to_mf<1>(x[0],t0[0],t1[0],vyi,vmod);
            x[0].storeu(to+i);
        }
        for(;i<len;i++)
        {
            to[i]=to_mf(arr[i]);
        }

    }

    static void arr_to_zf(const u2*arr,u2*to,u3 len)
    {
        u3 i;
        Pack<VU32x8,4> x,t0,t1;
        VU32x8 vmod=set1(mod),vmodp=set1(modp);
        for(i=0;i+31<len;i+=32)
        {
            x.loadu(arr+i);
            to_zf<4>(x,t0,t1,vmod,vmodp);
            x.storeu(to+i);
        }
        for(;i+7<len;i+=8)
        {
            x[0].loadu(arr+i);
            to_zf<1>(x[0],t0[0],t1[0],vmod,vmodp);
            x[0].storeu(to+i);
        }
        for(;i<len;i++)
        {
            to[i]=to_zf(arr[i]);
        }
    }


    static ALWAYS_INLINE void get_modp(VU32x8&vmodp)
    {
        vmodp=set1(modp);
    }

    static ALWAYS_INLINE void get_mod(VU32x8&vmod)
    {
        vmod=set1(mod);
    }
};

using MF=Mogo_F;

ALWAYS_INLINE void Transpose(Pack_Ref<VU32x8,8> mat,Pack_Ref<VU32x8,8> tmp)
{
    tmp[0,1,2,3]=permute2x(mat[0,1,2,3],mat[4,5,6,7],cint<0b0010'0000>);
    tmp[4,5,6,7]=permute2x(mat[0,1,2,3],mat[4,5,6,7],cint<0b0011'0001>);
    mat[0,1,4,5].as<VI64x4>()=unpacklo(tmp[0,1,4,5].as<VI64x4>(),tmp[2,3,6,7].as<VI64x4>());
    mat[2,3,6,7].as<VI64x4>()=unpackhi(tmp[0,1,4,5].as<VI64x4>(),tmp[2,3,6,7].as<VI64x4>());
    tmp=shuffle(mat,cint<0b1101'1000>);
    mat[0,2,4,6]=unpacklo(tmp[0,2,4,6],tmp[1,3,5,7]);
    mat[1,3,5,7]=unpackhi(tmp[0,2,4,6],tmp[1,3,5,7]);
}

struct Ntt
{
    static constexpr u2 g=3;
    static constexpr u2 gi=332748118;

    u3 layer;                               //一次正/逆变换的总层数
    static constexpr u3 seg_len=32;         //每个小段的大小
    static constexpr u3 seg_per_group=512;  //每个分组的小段的个数
    u3 group_num;                           //总共分了多少组

    alignas(64) u2 tmp[seg_len*seg_per_group];   //足以装入L2的一个小缓冲区，用来存一个组,且留一些L2的余量给其他地方用
    
    alignas(32) u2 w2[8];
    alignas(32) u2 wi2[8];
    alignas(32) u2 w4[8];
    alignas(32) u2 wi4[8];
    alignas(32) u2 w8[8];
    alignas(32) u2 wi8[8];
    alignas(64) u2 w16[8];
    alignas(64) u2 wi16[8];
    alignas(64) u2 w32[16];
    alignas(64) u2 wi32[16];
    alignas(64) u2 w[1<<21];
    alignas(64) u2 wi[1<<21];

    Ntt()
    {
        u2 W,Wi;
        for(u3 i=0;i<8;i++)
            w2[i]=1,wi2[i]=1;
        W=ZF::pow(g,(mod-1)/4);
        Wi=ZF::pow(gi,(mod-1)/4);
        for(u3 i=0;i<8;i+=2)
        {
            w4[i]=1,wi4[i]=1;
            for(u3 j=1;j<2;j++)
                w4[j]=(u3)w4[j-1]*W%mod,wi4[i]=(u3)wi4[j-1]*Wi%mod;
        }

        W=ZF::pow(g,(mod-1)/8);
        Wi=ZF::pow(gi,(mod-1)/8);
        for(u3 i=0;i<8;i+=4)
        {
            w4[i]=1,wi4[i]=1;
            for(u3 j=1;j<2;j++)
                w4[j]=(u3)w4[j-1]*W%mod,wi4[i]=(u3)wi4[j-1]*Wi%mod;
        }

        W=ZF::pow(g,(mod-1)/32);
        Wi=ZF::pow(g,(mod-1)/32);
        w32[0]=1;
        wi32[0]=1;
        for(u3 i=1;i<16;i++)
        {
            w32[i]=(u3)w32[i-1]*W%mod;
            wi32[i]=(u3)wi32[i-1]*Wi%mod;
        }
    }

    /*
    
    |---------------------------------数据总长=group_num*seg_per_group*seg_len---------------------------------|

    |-----group_num个seg------||-----group_num个seg------||-----group_num个seg------||-----group_num个seg------|

    {|-seg-|-seg-|-seg-|-seg-|}{|-seg-|-seg-|-seg-|-seg-|}{|-seg-|-seg-|-seg-|-seg-|}{|-seg-|-seg-|-seg-|-seg-|} -----data
       32    32    32    32       32    32    32    32       32    32    32    32       32    32    32    32    
       |                          |                          |                          |                          
       |                          |                          |                          |
       |                          |                          |                          |
       ----------------------------------------------------------------------------------------- group_0
    */

    //先转成蒙哥马利域，然后进行正变换的前min(9,layer-5)层，
    //分成group_num组，每组内分别计算完成再计算下一组，保证全在L2内
    void trans_step1(u2*a)
    {

    }

    //继续正变换，此步进行max(0,layer-14)层变换，每次对相邻的group_num个seg一起做变换，
    //此时实际上相当于在每个大段上做变换，每个大段变换完成后进行下一个大段的变换，
    //保证一直在L2内（实际可以保证在L1内，但影响不大）
    void trans_step2(u2*a)
    {
        
    }

    //对每个a和b的对应小段先进行最后5层正变换，然后乘起来，再进行5次逆变换后存入c中
    //除了一开始读a,b,w和wi，以及最后写c，中间全部在寄存器中进行。
    void trans_step3(u2*a,u2*b,u2*c)
    {
        Pack<VU32x8,16> regs;

        Pack_Ref va=regs[0,1,2,3];
        Pack_Ref vb=regs[4,5,6,7];
        Pack_Ref t =regs[8,9,10,11];
        VU32x8&vmod=regs[12];
        VU32x8&vmodp=regs[13];
        VU32x8&vmod2=regs[14];

        //假设len>=64，即layer>=6
        u3 len=1ull<<layer;

        MF::get_mod(vmod);
        MF::get_modp(vmodp);
        vmod2=vmod<<cint<1>;

        alignas(64) u2 tmp[32];

        for(u3 i=0;i<len;i+=64)
        {
            //32正变换
            auto trans32=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(va[0,1],vb[0,1]);
                Pack_Ref py(va[2,3],vb[2,3]);
                
                t=px+py;
                px=px-py;
                py[0,1].load(w32);
                px=px+vmod2;
                MF::jmod(t,py,vmod2);
                t.store(tmp);
                py[2,3]=py[0,1];
                MF::mul_3<4,false>(py,px,t,vmod,vmodp);
                px.load(tmp);
            };

            //16正变换
            auto trans16=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(va[0,2],vb[0,2]);
                Pack_Ref py(va[1,3],vb[1,3]);

                t=px+py;
                px=px-py;
                py[0].load(w16);
                px=px+vmod2;
                MF::jmod(t,py,vmod2);
                t.store(tmp);
                py[1,2,3]=py[0,0,0];
                MF::mul_3<4,false>(py,px,t,vmod,vmodp);
                px.load(tmp);
            };

            //8正变换
            auto trans8=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,1,2,3]);
                Pack_Ref py(regs[4,5,6,7]);
                t=px+py;
                px=px-py;
                py[0].load(w8);
                px=px+vmod2;
                MF::jmod(t,py,vmod2);
                t.store(tmp);
                py[1,2,3]=py[0,0,0];
                MF::mul_3<4,false>(py,px,t,vmod,vmodp);
                px.load(tmp);
            };

            //4正变换
            auto trans4=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,1,4,5]);
                Pack_Ref py(regs[2,3,6,7]);
                t=px+py;
                px=px-py;
                py[0].load(w4);
                px=px+vmod2;
                MF::jmod(t,py,vmod2);
                t.store(tmp);
                py[1,2,3]=py[0,0,0];
                MF::mul_3<4,false>(py,px,t,vmod,vmodp);
                px.load(tmp);
            };

            //2正变换
            auto trans2=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,2,4,6]);
                Pack_Ref py(regs[1,3,5,7]);
                t=px-py;
                px=px+py;
                t=px+vmod2;
                MF::jmod(t,py,vmod2);
                MF::jmod(px,py,vmod2);
                py=t;
            };

            //2逆变换，和正变换一样
            auto trans2i=trans2;

            //4逆变换
            auto trans4i=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,1,4,5]);
                Pack_Ref py(regs[2,3,6,7]);
                
                px.store(tmp);
                t[0].load(wi4);
                t[1,2,3]=t[0];
                MF::mul_3<4,false>(py,px,t,vmod,vmodp);
                px.load(tmp);

                t=px-py;
                px=px+py;
                py=t+vmod2;

                MF::jmod(px,t,vmod2);
                MF::jmod(py,t,vmod2);
            };

            //8逆变换
            auto trans8i=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,1,2,3]);
                Pack_Ref py(regs[4,5,6,7]);
                
                px.store(tmp);
                t[0].load(wi8);
                t[1,2,3]=t[0];
                MF::mul_3<4,false>(py,px,t,vmod,vmodp);
                px.load(tmp);

                t=px-py;
                px=px+py;
                py=t+vmod2;

                MF::jmod(px,t,vmod2);
                MF::jmod(py,t,vmod2);
            };

            //16逆变换
            auto trans16i=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,2,4,6]);
                Pack_Ref py(regs[1,3,5,7]);
                
                px.store(tmp);
                t[0].load(wi16);
                t[1,2,3]=t[0];
                MF::mul_3<4,false>(py,px,t,vmod,vmodp);
                px.load(tmp);

                t=px-py;
                px=px+py;
                py=t+vmod2;

                MF::jmod(px,t,vmod2);
                MF::jmod(py,t,vmod2);
            };

            //32逆变换
            auto trans32i=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,1,4,5]);
                Pack_Ref py(regs[2,3,6,7]);
                
                px.store(tmp);
                t[0,1].load(wi32);
                t[2,3]=t[0,1];
                MF::mul_3<4,false>(py,px,t,vmod,vmodp);
                px.load(tmp);

                t=px-py;
                px=px+py;
                py=t+vmod2;

                MF::jmod(px,t,vmod2);
                MF::jmod(py,t,vmod2);
            };

            va.load(a+i);
            vb.load(b+i);
            trans32();
            trans16();
            Transpose(Pack_Ref(va,vb),regs[8,9,10,11,12,13,14,15]);
            MF::get_mod(vmod);
            MF::get_modp(vmodp);
            vmod2=vmod<<cint<1>;
            trans8();
            trans4();
            trans2();
            va.store(a+i);
            vb.store(b+i);
            va.load(a+i+32);
            vb.load(b+i+32);
            trans32();
            trans16();
            Transpose(Pack_Ref(va,vb),regs[8,9,10,11,12,13,14,15]);
            MF::get_mod(vmod);
            MF::get_modp(vmodp);
            vmod2=vmod<<cint<1>;
            trans8();
            trans4();
            trans2();
            va.store(b+i+32);
            va.load(a+i);
            t=permute2x(va,vb,cint<0x31>);
            va=permute2x(va,vb,cint<0x20>);
            MF::mul_3<4,false>(t,va,vb,vmod,vmodp);
            va.load(b+i);
            vb.load(b+i+32);
            t.store(c+i);
            t=permute2x(va,vb,cint<0x31>);
            va=permute2x(va,vb,cint<0x20>);
            MF::mul_3<4,false>(t,va,vb,vmod,vmodp);
            va.load(c+i);
            vb=t;
            trans2i();
            trans4i();
            trans8i();
            Transpose(Pack_Ref(va,vb),regs[8,9,10,11,12,13,14,15]);
            MF::get_mod(vmod);
            MF::get_modp(vmodp);
            vmod2=vmod<<cint<1>;
            trans16i();
            trans32i();
            va.store(c+i);
            vb.store(c+i+32);
        }
    }

    //与step2类似，但是进行的是逆变换
    void trans_step4(u2*a)
    {

    }

    //与step1类似，但是进行的是逆变换
    void trans_step5(u2*a)
    {

    }

    void mul(u2*a,u2*b,u2*c,u3 len)
    {
        u3 k=5;
        while((1ull<<k)<len)k<<=1;
        len=1ull<<k;

        u3 layer=k;


    }
};



void test()
{
    u2 a[1005];
    for(int i=0;i<1005;i++)
        a[i]=i;
    Mogo_F::arr_to_mf(a,a,1005);
    Mogo_F::arr_to_zf(a,a,1005);
    for(int i=0;i<1005;i++)
    {
        printf("%u ",a[i]);
        if(i%10==9)puts("");
    }
}



void poly_multiply(unsigned *a, int n, unsigned *b, int m, unsigned *c)
{
    Pack<VU32x8,4> x,y,t;
    VU32x8 vmod=set1(mod),vmodp=set1(Mogo_F::modp);
    for(int j=0;j<1024*1024;j++)
    for(int i=0;i<1024;i+=32)
    {
        x.loadu(a+i);
        y.loadu(b+i);
        Mogo_F::mul_3<4,false>(x,y,t,vmod,vmodp);
        x.storeu(a+i);
    }
}

/*
int main()
{
    read();

    int len=n+m+1;
    int k=32;
    while(k<len)k<<=1;

    #ifdef TEST_JUDGE
        int start=clock();
        for(int j=0;j<10;j++){
    #endif

        init(k);
        NTTfa(a,k);
        NTTfa(b,k);
        for(S i=0;i<k;i+=8)
            mul_mod(a+i,b+i).store(a+i);
        NTTifa(a,k);
        
    #ifdef TEST_JUDGE
        }
        int end=clock();
        printf("%d\n",end-start);
    #endif

    write();
}
*/


