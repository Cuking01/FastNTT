#include "../CuSDK/basis.h"
#include "../CuSDK/simd.h"


static constexpr u2 mod=469762049;

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
    static constexpr u2 yi=((1ull<<61)+mod-1)/mod-(1ull<<32);
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
        tmp=a-vmod;
        a=min(a,tmp);
    }

    template<u2 n>
    ALWAYS_INLINE static void jmodadd(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> b,const VU32x8&vmod)
    {
        a=a+b;
        b=a-vmod;
        a=min(a,b);
    }

    template<u2 n>
    ALWAYS_INLINE static void jmodsub(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> b,const VU32x8&vmod)
    {
        a=a-b;
        b=a+vmod;
        a=min(a,b);
    }

    template<u2 n,bool j_mod=true>
    ALWAYS_INLINE static void mul_3(Pack_Ref<VU32x8,n> a,Pack_Ref<VU32x8,n> b,Pack_Ref<VU32x8,n> t,const VU32x8& vmod,const VU32x8& vmodp)
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

        x=x<<cint<3>;
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
        x=vmod-x;
        jmod<n>(x,t0,vmod);
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

// void debug_print_arr(u2*a,u3 len)
// {
//     for(u3 i=0;i<len;i++)
//     {
//         printf("%10u ",a[i]);
//         if(i%8==7)puts("");
//     }
// }


// void debug_print_arr_raw(u2*a,u3 len)
// {
//     for(u3 i=0;i<len;i++)
//     {
//         printf("%10u ",MF::to_zf(a[i]));
//         if(i%8==7)puts("");
//     }
// }

// template<u2 n>
// void debug_print(Pack_Ref<VU32x8,n> data)
// {
//     alignas(64) u2 tmp[n*8];
//     data.store(tmp);

//     for(u3 i=0;i<n*8;i++)
//     {
//         printf("%10u ",tmp[i]);
//         if(i%8==7)puts("");
//     }
// }

// template<u2 n>
// void debug_print_raw(Pack_Ref<VU32x8,n> data)
// {
//     alignas(64) u2 tmp[n*8];
//     data.store(tmp);

//     for(u3 i=0;i<n*8;i++)
//     {
//         printf("%10u ",MF::to_zf(tmp[i]));
//         if(i%8==7)puts("");
//     }
// }

struct Ntt
{
    static constexpr u2 g=3;
    static constexpr u2 gi=ZF::pow(3,mod-2);

    u3 layer;                               //一次正/逆变换的总层数
    static constexpr u3 seg_len=32;         //每个小段的大小
    static constexpr u3 seg_per_group=512;  //每个分组的小段的个数
    u3 group_num;                           //总共分了多少组
    
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

    static constexpr u3 w_max_len=1ull<<21;

    alignas(64) static inline u2 w[w_max_len];
    alignas(64) static inline u2 wi[w_max_len];

    void re_w_len(u3 len=w_max_len)
    {
        for(u3 i=32;i<len;i<<=1)
        {
            Pack<VU32x8,4> vw,y,t;
            VU32x8 vw32,vmod,vmodp;

            MF::get_mod(vmod);
            MF::get_modp(vmodp);
            alignas(64) u2 wt[32];
            u2 w1=ZF::pow(g,(mod-1)/(i<<1));
            wt[0]=1;
            for(u3 j=1;j<32;j++)
                wt[j]=(u3)wt[j-1]*w1%mod;
            MF::arr_to_mf(wt,wt,32);
            vw.load(wt);
            vw32=set1(MF::to_mf(ZF::pow(w1,32)));


            for(u3 j=0;j<i;j+=32)
            {
                vw.store(w+i+j);
                y=vw32;
                MF::mul_3<4>(vw,y,t,vmod,vmodp);
            }
            

            w1=ZF::pow(gi,(mod-1)/(i<<1));
            wt[0]=1;
            for(u3 j=1;j<32;j++)
                wt[j]=(u3)wt[j-1]*w1%mod;
            MF::arr_to_mf(wt,wt,32);
            vw.load(wt);
            vw32=set1(MF::to_mf(ZF::pow(w1,32)));
            for(u3 j=0;j<i;j+=32)
            {
                vw.store(wi+i+j);
                y=vw32;
                MF::mul_3<4>(vw,y,t,vmod,vmodp);
            }
        }
    }

    Ntt()
    {
        // u2 W,Wi;
        // for(u3 i=0;i<8;i++)
        //     w2[i]=1,wi2[i]=1;
        // W=ZF::pow(g,(mod-1)/4);
        // Wi=ZF::pow(gi,(mod-1)/4);
        // for(u3 i=0;i<8;i+=2)
        // {
        //     w4[i]=1,wi4[i]=1;
        //     for(u3 j=1;j<2;j++)
        //         w4[i+j]=(u3)w4[i+j-1]*W%mod,wi4[i+j]=(u3)wi4[i+j-1]*Wi%mod;
        // }

        // W=ZF::pow(g,(mod-1)/8);
        // Wi=ZF::pow(gi,(mod-1)/8);
        // for(u3 i=0;i<8;i+=4)
        // {
        //     w8[i]=1,wi8[i]=1;
        //     for(u3 j=1;j<4;j++)
        //         w8[i+j]=(u3)w8[i+j-1]*W%mod,wi8[i+j]=(u3)wi8[i+j-1]*Wi%mod;
        // }

        // W=ZF::pow(g,(mod-1)/16);
        // Wi=ZF::pow(gi,(mod-1)/16);
        // for(u3 i=0;i<8;i+=8)
        // {
        //     w16[i]=1,wi16[i]=1;
        //     for(u3 j=1;j<8;j++)
        //         w16[i+j]=(u3)w16[i+j-1]*W%mod,wi16[i+j]=(u3)wi16[i+j-1]*Wi%mod;
        // }

        // W=ZF::pow(g,(mod-1)/32);
        // Wi=ZF::pow(gi,(mod-1)/32);
        // w32[0]=1;
        // wi32[0]=1;
        // for(u3 i=1;i<16;i++)
        // {
        //     w32[i]=(u3)w32[i-1]*W%mod;
        //     wi32[i]=(u3)wi32[i-1]*Wi%mod;
        // }

        // MF::arr_to_mf(w2,w2,8);
        // MF::arr_to_mf(wi2,wi2,8);
        // MF::arr_to_mf(w4,w4,8);
        // MF::arr_to_mf(wi4,wi4,8);
        // MF::arr_to_mf(w8,w8,8);
        // MF::arr_to_mf(wi8,wi8,8);
        // MF::arr_to_mf(w16,w16,8);
        // MF::arr_to_mf(wi16,wi16,8);
        // MF::arr_to_mf(w32,w32,16);
        // MF::arr_to_mf(wi32,wi32,16);

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

    void dif6_raidx4(u2*a)
    {
        Pack<VU32x8,2> vx0,vx1,vx2,vx3,vt0,vt1,vw;
        VU32x8 vmod,vmodp;

        MF::get_mod(vmod);
        MF::get_modp(vmodp);

        u3 len=1ull<<layer;
        for(u3 l=0;l<6;l+=2)
        {
            u3 i=len>>(l+2);

            for(u3 j=0;j<len;j+=i*4)
            {
                u2*px0=a+j;
                u2*px1=a+j+i;
                u2*px2=a+j+i*2;
                u2*px3=a+j+i*3;
                u2*pw=w+i*2;
                for(u3 k=0;k<i;k+=16)
                {
                    vx0.load(px0+k);
                    vx2.load(px2+k);
                    vw.load(pw+2*k);
                    vx1.load(px1+k);
                    vx3.load(px3+k);
                    // _mm_prefetch(px0+k+32,_MM_HINT_T0);
                    // _mm_prefetch(px1+k+32,_MM_HINT_T0);
                    // _mm_prefetch(px2+k+32,_MM_HINT_T0);
                    // _mm_prefetch(px3+k+32,_MM_HINT_T0);
                    // _mm_prefetch(pw+k+32,_MM_HINT_T0);
                    // _mm_prefetch(pw+k*2+32,_MM_HINT_T0);
                    // _mm_prefetch(pw+k*3+32,_MM_HINT_T0);

                    // if(k%64==0)
                    // {
                    //     _mm_prefetch(px0+k+64,_MM_HINT_T0);
                    //     _mm_prefetch(px1+k+64,_MM_HINT_T0);
                    //     _mm_prefetch(px2+k+64,_MM_HINT_T0);
                    //     _mm_prefetch(px3+k+64,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k+64,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k*2+64,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k*3+64,_MM_HINT_T0);

                    //     _mm_prefetch(px0+k+80,_MM_HINT_T0);
                    //     _mm_prefetch(px1+k+80,_MM_HINT_T0);
                    //     _mm_prefetch(px2+k+80,_MM_HINT_T0);
                    //     _mm_prefetch(px3+k+80,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k+80,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k*2+80,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k*3+80,_MM_HINT_T0);

                    //     _mm_prefetch(px0+k+96,_MM_HINT_T0);
                    //     _mm_prefetch(px1+k+96,_MM_HINT_T0);
                    //     _mm_prefetch(px2+k+96,_MM_HINT_T0);
                    //     _mm_prefetch(px3+k+96,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k+96,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k*2+96,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k*3+96,_MM_HINT_T0);

                    //     _mm_prefetch(px0+k+112,_MM_HINT_T0);
                    //     _mm_prefetch(px1+k+112,_MM_HINT_T0);
                    //     _mm_prefetch(px2+k+112,_MM_HINT_T0);
                    //     _mm_prefetch(px3+k+112,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k+112,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k*2+112,_MM_HINT_T0);
                    //     _mm_prefetch(pw+k*3+112,_MM_HINT_T0);
                    // }
                    
                    
                    vmod=vmod<<cint<1>;

                    auto trans=[&vt0,&vt1,&vmod] ALWAYS_INLINE_LAMBDA (auto&va,auto&vb)
                    {
                        vt0=va;
                        vt1=vb;
                        MF::jmodadd<2>(va,vt1,vmod);
                        MF::jmodsub<2>(vt0,vb,vmod);
                        vb=vt0;
                    };

                    auto trans2=[&vt0,&vt1,&vmod] ALWAYS_INLINE_LAMBDA (auto&va,auto&vb)
                    {
                        vt0=va;
                        vt1=vb;
                        MF::jmodsub<2>(va,vt1,vmod);
                        MF::jmodadd<2>(vt0,vb,vmod);
                        vb=vt0;
                    };

                    trans(vx0,vx2);
                    trans(vx1,vx3);
                    trans(vx0,vx1);
                    trans2(vx2,vx3);

                    vmod=vmod<<cint<1>;
                    MF::mul_4<2,false>(vx1,vw,vt0,vt1,vmod,vmodp);
                    vw.load(pw+k);
                    vx0.store(px0+k);
                    vx0.load(pw+k*3);
                    vx1.store(px1+k);

                    MF::mul_3<4,false>(Pack_Ref(vx2,vx3),Pack_Ref(vw,vx0),Pack_Ref(vt0,vt1),vmod,vmodp);
                    vx2.store(px2+k);
                    vx3.store(px3+k);

                    // MF::mul_4<2,false>(vx2,vw,vt0,vt1,vmod,vmodp);
                    // vw.load(pw+k*3);
                    // vx2.store(px2+k);
                    // MF::mul_4<2,false>(vx3,vw,vt0,vt1,vmod,vmodp);
                    // vx3.store(px3+k);
                }
            }
        }
    }


    void dif6(u2*a)
    {
        Pack<VU32x8,2> vx0,vy0,vx1,vy1,vt0,vt1,vw;
        VU32x8 vmod,vmodp;

        MF::get_mod(vmod);
        MF::get_modp(vmodp);

        u3 len=1ull<<layer;
        for(u3 l=0;l<6;l+=2)
        {
            u3 i=len>>(l+2);

            for(u3 j=0;j<len;j+=i*4)
            {
                u2*px0=a+j;
                u2*py0=a+j+i;
                u2*px1=a+j+i*2;
                u2*py1=a+j+i*3;
                u2*pw=w;
                for(u3 k=0;k<i;k+=16)
                {
                    vx0.load(px0+k);
                    vx1.load(px1+k);
                    vw.load(pw+i*2+k);
                    vy0.load(py0+k);
                    vy1.load(py1+k);
                    _mm_prefetch(px0+k+32,_MM_HINT_T0);
                    _mm_prefetch(py0+k+32,_MM_HINT_T0);
                    _mm_prefetch(px1+k+32,_MM_HINT_T0);
                    _mm_prefetch(py1+k+32,_MM_HINT_T0);
                    _mm_prefetch(pw+i+k+32,_MM_HINT_T0);
                    _mm_prefetch(pw+i*2+k+32,_MM_HINT_T0);
                    _mm_prefetch(pw+i*3+k+32,_MM_HINT_T0);
                    
                    vt0=vx0+vx1;
                    vt1=vx0-vx1;
                    MF::mul_4<2,false>(vt1,vw,vx0,vx1,vmod,vmodp);
                    vw.load(pw+i*2+k+i);

                    vmod=vmod<<cint<1>;
                    MF::jmod<2>(vt0,vx0,vmod);
                    vmod=vmod>>cint<1>;
                    vx0=vt0;     //4p
                    vx1=vt1;     //2p

                    vt0=vy0+vy1;
                    vt1=vy0-vy1;
                    MF::mul_4<2,false>(vt1,vw,vy0,vy1,vmod,vmodp);
                    vw.load(pw+i+k);
                    vmod=vmod<<cint<1>;
                    MF::jmod<2>(vt0,vy0,vmod);
                    vmod=vmod>>cint<1>;
                    vy0=vt0;     //4p
                    vy1=vt1;     //2p

                    vt0=vx0+vy0; //8p
                    vt1=vx0-vy0;
                    MF::mul_4<2,false>(vt1,vw,vx0,vy0,vmod,vmodp);
                    vw.load(pw+i+k);
                    vmod=vmod<<cint<1>;
                    MF::jmod<2>(vt0,vx0,vmod);
                    vmod=vmod>>cint<1>;
                    vx0=vt0;
                    vy0=vt1;

                    vt0=vx1+vy1;
                    vt1=vx1-vy1;
                    MF::mul_4<2,false>(vt1,vw,vx1,vy1,vmod,vmodp);
                    vmod=vmod<<cint<1>;
                    MF::jmod<2>(vt0,vx1,vmod);
                    vx1=vt0;
                    vy1=vt1;

                    vx0.store(px0+k);
                    vx1.store(px1+k);
                    vy0.store(py0+k);
                    vy1.store(py1+k);
                }
            }
        }
    }

    //进行正变换的前9层(仅当层数至少14层时执行，否则直接跳过)
    //分成group_num组，每组内分别计算完成再计算下一组，保证全在L2内
    void trans_step1(u2*a)
    {
        if(layer<14)return;
        static constexpr u3 m=6;
        static constexpr u3 S=256;
        static constexpr u3 tlen=S*(1ull<<m);

        alignas(64) u2 tmp[tlen];   //足以装入L2的一个小缓冲区，用来存一个组,且留一些L2的余量给其他地方用
        alignas(64) u2 tmp_w[tlen];

        const u3 group_num=1ull<<(layer-m);
        const u3 len=1ull<<layer;

        Pack<VU32x8,4> vt;
        Pack<VU32x8,4>vx,vy;
        VU32x8 vmod,vmodp,vmod2;
        MF::get_mod(vmod);
        MF::get_modp(vmodp);
        vmod2=vmod<<cint<1>;

        auto butterfly=[&]<bool write_w> ALWAYS_INLINE_LAMBDA (
            const u2*x0_in,const u2*x1_in,
            u2*x0_out,u2*x1_out,
            const u2*w_in,u2*w_out,
            const u2*w1_in,u2*w1_out
            )
        {
            vx.load(x0_in);
            vy.load(x1_in);

            vt=vy;
            vy=vx-vy;
            MF::jmodadd<4>(vx,vt,vmod2);
            vt.load(w_in);
            vx.store(x0_out);
            
            vy=vy+vmod2;
            if constexpr(write_w)
            {
                vt.store(w_out);
            }
            MF::mul_3<4,false>(vy,vt,vx,vmod,vmodp);
            vy.store(x1_out);
            if constexpr(write_w)
            {
                vt.load(w1_in);
                vt.store(w1_out);
            }
        };

        for(u3 r=0;r<group_num;r+=S)
        {
            for(u3 j=0;j<(1ull<<(m-1));j++)
            {
                u2*px0=a+j*group_num;
                u2*px1=a+j*group_num+(len>>1);
                u2*tx0=tmp+j*S;
                u2*tx1=tmp+j*S+(tlen>>1);
                u2*pw=w+(len>>1)+j*group_num;
                u2*tw=tmp_w+(tlen>>1)+j*S;
                u2*pw1=w+j*group_num;
                u2*tw1=tmp_w+j*S;

                for(u3 k=0;k<S;k+=32)
                    butterfly.operator()<true>(px0+k,px1+k,tx0+k,tx1+k,pw,tw,pw1,tw1);
            }

            for(u3 l=1;l<m-1;l++)
            {
                u3 i=1ull<<(layer-l-1);
                u3 ip=i/group_num*S;
                
                for(u3 j=0;j<tlen;j+=ip<<1)
                {
                    auto w=this->w;
                    for(u3 k=0;k<ip;k+=32)
                    {
                        butterfly.operator()<false>(tmp+j+k,tmp+j+k+ip,tmp+j+k,tmp+j+k+ip,tmp_w+ip+k,tmp_w+ip+k,nullptr,nullptr);
                    }
                }
            }

            u3 i=1ull<<(layer-m);
            u3 ip=i/group_num*S;
            
            for(u3 j=0;j<tlen;j+=ip<<1)
            {
                auto w=this->w;
                for(u3 k=0;k<ip;k+=32)
                {
                    butterfly.operator()<false>(tmp+j+k,tmp+j+k+ip,a+j/S*group_num+k,a+j/S*group_num+k+i,tmp_w+ip+k,tmp_w+ip+k,nullptr,nullptr);
                }
            }

        }
    }

    //与step1类似，但是进行的是逆变换
    void trans_step5(u2*a)
    {
        if(layer<14)return;

        alignas(64) u2 tmp[seg_len*seg_per_group];   //足以装入L2的一个小缓冲区，用来存一个组,且留一些L2的余量给其他地方用
        alignas(64) u2 tmp_w[seg_len*seg_per_group];
       
        const u3 L=9;

        u3 log2_group_num=0;
        while((1ull<<log2_group_num)<group_num)
            log2_group_num++;

        for(u3 group_id=0;group_id<group_num;group_id++)
        {
            Pack<VU32x8,4> vt;
            // for(u3 j=0;j<seg_per_group;j++)
            // {
            //     vt.load(a+(j*group_num+group_id)*seg_len);
            //     vt.store(tmp+j*seg_len);
            // }
            // for(u3 j=1;j<seg_per_group;j<<=1)
            // {
            //     for(u3 k=0;k<j;k++)
            //     {
            //         vt.load(wi+((j+k)*group_num+group_id)*seg_len);
            //         vt.store(tmp_w+(j+k)*seg_len);
            //     }
            // }

            Pack<VU32x8,4>vx,vy;
            VU32x8 vmod,vmodp,vmod2;
            MF::get_mod(vmod);
            MF::get_modp(vmodp);
            vmod2=vmod<<cint<1>;

            for(u3 l=L;l--;)
            {
                u3 i=1ull<<(layer-l-1);
                u3 ip=i/group_num;



                for(u3 j=0;j<seg_len*seg_per_group;j+=ip<<1)
                {
                    auto w=this->w;
                    for(u3 k=0;k<ip;k+=32)
                    {
                        vy.load(a+j+k+ip);
                        vt.load(w+ip+k);
                        MF::mul_3<4,false>(vy,vt,vx,vmod,vmodp);
                        vx.load(a+j+k);

                        vt=vx+vy;
                        vy=vx-vy;
                        vy=vy+vmod2;

                        MF::jmod<4>(vt,vx,vmod2);
                        MF::jmod<4>(vy,vx,vmod2);

                        vt.store(a+j+k);
                        vy.store(a+j+k+ip);
                    }
                }
            }

            // for(u3 j=0;j<seg_per_group;j++)
            // {
            //     vt.load(tmp+j*seg_len);
            //     vt.store(a+(j*group_num+group_id)*seg_len);
            // }
        }
    }

    //继续正变换，此步进行max(0,layer-14)层变换，每次对相邻的group_num个seg一起做变换，
    //此时实际上相当于在每个大段上做变换，每个大段变换完成后进行下一个大段的变换，
    //保证一直在L2内（实际可以保证在L1内，但影响不大）
    void trans_step2(u2*a)
    {
        const u3 L_l=5,L_r=layer>=14?layer-6:layer;    //变换的层数范围。
        const u3 seg_per_group=this->group_num>0?this->seg_per_group:1;
        const u3 group_num=this->group_num>0?this->group_num:(1ull<<layer)/seg_len;

        Pack<VU32x8,4>vx,vy,vt;
        VU32x8 vmod,vmodp,vmod2;
        MF::get_mod(vmod);
        MF::get_modp(vmodp);
        vmod2=vmod<<cint<1>;

        for(u3 sid=0;sid<seg_per_group;sid++) //枚举大段
        {
            u2*sp=a+sid*group_num*seg_len;    //大段首地址
            for(u3 j=0;j<group_num*seg_len;j+=64)
            {
                u2*nxt=sp+group_num*seg_len;
                _mm_prefetch(nxt+j+0,_MM_HINT_T0);
                _mm_prefetch(nxt+j+16,_MM_HINT_T0);
                _mm_prefetch(nxt+j+32,_MM_HINT_T0);
                _mm_prefetch(nxt+j+48,_MM_HINT_T0);

            }
            for(u3 l=L_r;l>L_l;l--)
            {
                u3 i=1ull<<(l-1);
                for(u3 j=0;j<group_num*seg_len;j+=i<<1)
                {
                    for(u3 k=0;k<i;k+=32)
                    {
                        vx.load(sp+j+k);
                        vy.load(sp+j+k+i);

                        vt=vx+vy;
                        vy=vx-vy;
                        MF::jmod<4>(vt,vx,vmod2);
                        vt.store(sp+j+k);
                        vt.load(w+i+k);
                        vy=vy+vmod2;
                        MF::mul_3<4,false>(vy,vt,vx,vmod,vmodp);
                        vy.store(sp+j+k+i);
                    }
                }
            }
        }
    }

    //与step2类似，但是进行的是逆变换
    void trans_step4(u2*a)
    {
        const u3 L_l=5,L_r=layer>=14?layer-9:layer;    //变换的层数范围。
        const u3 seg_per_group=this->group_num>0?this->seg_per_group:1;
        const u3 group_num=this->group_num>0?this->group_num:(1ull<<layer)/seg_len;

        Pack<VU32x8,4>vx,vy,vt;
        VU32x8 vmod,vmodp,vmod2;
        MF::get_mod(vmod);
        MF::get_modp(vmodp);
        vmod2=vmod<<cint<1>;

        for(u3 sid=0;sid<seg_per_group;sid++) //枚举大段
        {
            u2*sp=a+sid*group_num*seg_len;    //大段首地址
            
            for(u3 l=L_l+1;l<=L_r;l++)
            {
                u3 i=1ull<<(l-1);
                for(u3 j=0;j<group_num*seg_len;j+=i<<1)
                {
                    for(u3 k=0;k<i;k+=32)
                    {
                        vy.load(sp+j+k+i);
                        vt.load(wi+i+k);
                        MF::mul_3<4,false>(vy,vt,vx,vmod,vmodp);
                        vx.load(sp+j+k);

                        vt=vx+vy;
                        vy=vx-vy;
                        vy=vy+vmod2;

                        MF::jmod<4>(vt,vx,vmod2);
                        MF::jmod<4>(vy,vx,vmod2);

                        vt.store(sp+j+k);
                        vy.store(sp+j+k+i);
                    }
                }
            }
        }
    }

    //对每个a和b的对应小段先进行最后5层正变换，然后乘起来，再进行5次逆变换后存入c中
    //除了一开始读a,b,w和wi，以及最后写c，中间全部在寄存器中进行(但实际上还是出现少量溢出，多了一些内存操作)。
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
        const u2 w41=w4[1];
        const u2 wi41=wi4[1];

        for(u3 i=0;i<len;i+=64)
        {
            //32正变换
            auto trans32=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(va[0,1],vb[0,1]);
                Pack_Ref py(va[2,3],vb[2,3]);
                t=px+py;
                px=px-py;
                px=px+vmod2;
                MF::jmod(t,py,vmod2);
                //MF::jmod(px,py,vmod2);
                t.store(tmp);
                py[0,1].load(w32);
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
                regs[15].load(w16);
                px=px+vmod2;
                MF::jmod(t,py,vmod2);
                //MF::jmod(px,py,vmod2);
                t.store(tmp);
                py=regs[15];
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
                px=px+vmod2;
                MF::jmod(t,py,vmod2);
                //MF::jmod(px,py,vmod2);
                MF::jmod<1>(px[0],py[0],vmod2);
                t.store(tmp);
                py[1,2,3]=set1(Scale_Pack(w8[1],w8[2],w8[3]));
                MF::mul_4<3,false>(py[1,2,3],px[1,2,3],t[1,2,3],Pack_Ref(py[0],t[0],regs[15]),vmod,vmodp);
                py[0]=px[0];
                px.load(tmp);
            };

            auto trans4=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,1,4,5]);
                Pack_Ref py(regs[2,3,6,7]);
                t=px+py;
                px=px-py;
                px=px+vmod2;
                MF::jmod(t,py,vmod2);
                MF::jmod(px[0,2],py[0,2],vmod2);
                t.store(tmp);
                py[1]=set1(w41);
                py[3]=py[1];
                MF::mul_4<2,false>(py[1,3],px[1,3],t[0,1],t[2,3],vmod,vmodp);
                py[0,2]=px[0,2];
                px.load(tmp);
            };

            //2正变换
            auto trans2=[&] ALWAYS_INLINE_LAMBDA ()
            {
                Pack_Ref px(regs[0,2,4,6]);
                Pack_Ref py(regs[1,3,5,7]);
                t=px-py;
                px=px+py;
                t=t+vmod2;
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
                t[1]=set1(wi41);
                t[3]=t[1];
                MF::mul_4<2,false>(py[1,3],t[1,3],px[0,1],px[2,3],vmod,vmodp);
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
                t[1,2,3]=set1(Scale_Pack(wi8[1],wi8[2],wi8[3]));
                MF::mul_4<3,false>(py[1,2,3],t[1,2,3],px[1,2,3],Pack_Ref(t[0],px[0],regs[15]),vmod,vmodp);
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
                MF::mul_3<4,false>(py,t,px,vmod,vmodp);
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
                MF::mul_3<4,false>(py,t,px,vmod,vmodp);
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
            vb.store(b+i+32);
            vb.load(a+i);
            t=permute2x(va,vb,cint<0x13>);
            va=permute2x(va,vb,cint<0x02>);
            MF::mul_3<4,false>(t,va,vb,vmod,vmodp);
            vb.load(b+i);
            va.load(b+i+32);
            t.store(c+i);
            t=permute2x(va,vb,cint<0x13>);
            va=permute2x(va,vb,cint<0x02>);
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

    //除以len并转回普通整数，并清理掉等于模数的值。
    void trans_step6(u2*a)
    {
        u3 len=1ull<<layer;

        u2 inv=ZF::pow(len,mod-2);
        VU32x8 vinv=set1(inv);

        Pack<VU32x8,4> vx,vy,vt;
        VU32x8 vmod,vmodp;

        MF::get_mod(vmod);
        MF::get_modp(vmodp);

        for(u3 i=0;i<len;i+=32)
        {
            vx.load(a+i);
            vy=vinv;
            MF::mul_3<4>(vx,vy,vt,vmod,vmodp);
            vt=vx==vmod;
            vt=vt&vmod;
            vx=vx-vt;
            vx.store(a+i);
        }
    }

    

    void mul(u2*a,u2*b,u2*c,u3 len)
    {
        //cu_assert(len>=64,"ntt length must >=64");

        //re_w_len(len);

        u3 k=5;
        while((1ull<<k)<len)k++;
        len=1ull<<k;

        layer=k;
        group_num=len/(seg_per_group*seg_len);
         //MF::arr_to_mf(a,a,len);
         //MF::arr_to_mf(b,b,len);

        dif6_raidx4(a);
        //dif6(a);
         //trans_step1(a);
         //trans_step2(a);
         //trans_step1(b);
         //trans_step2(b);
        //trans_step3(a,b,c);
         //trans_step4(c);
         //trans_step5(c);

        //trans_step6(c);
     
    }
};


/*

namespace NTT_simple
{
    static constexpr u2 g=3u;
    static constexpr u2 gi=ZF::pow(3,mod-2);

    void NTT(u2*a,u3 len)
    {
        for(u3 i=len>>1;i;i>>=1)
        {
            u2 wi=ZF::pow(g,(mod-1)/(i<<1));
            for(u3 j=0;j<len;j+=i<<1)
            {
                u2 w=1;
                for(u3 k=0;k<i;k++,w=(u3)w*wi%mod)
                {
                    u2 x=a[j+k],y=a[i+j+k];
                    a[j+k]=(x+y)%mod;
                    a[i+j+k]=(u3)(x-y+mod)*w%mod;
                }
            }
            
        }
    }

    void NTTi(u2*a,u3 len)
    {
        for(u3 i=1;i<len;i<<=1)
        {
            u2 wi=ZF::pow(gi,(mod-1)/(i<<1));
            for(u3 j=0;j<len;j+=i<<1)
            {
                u2 w=1;
                for(u3 k=0;k<i;k++,w=(u3)w*wi%mod)
                {
                    u2 x=a[j+k],y=(u3)a[i+j+k]*w%mod;
                    a[j+k]=(x+y)%mod;
                    a[i+j+k]=(x-y+mod)%mod;
                }
            }
        }

        u2 inv=ZF::pow(len,mod-2);
        for(int i=0;i<len;i++)
            a[i]=(u3)a[i]*inv%mod;
    }

    static inline u2 ta[1<<21];
    static inline u2 tb[1<<21];

    void mul(u2*a,u2*b,u3 lena,u3 lenb,u2*c)
    {
        u3 len=lena+lenb-1;
        u3 k=32;
        while(k<len)k<<=1;
        memset(ta,0,sizeof(u2)*k);
        memset(tb,0,sizeof(u2)*k);
        memcpy(ta,a,sizeof(u2)*lena);
        memcpy(tb,b,sizeof(u2)*lenb);

        NTT(ta,k);
        NTT(tb,k);

        for(u3 i=0;i<k;i++)
            ta[i]=(u3)ta[i]*tb[i]%mod;

        NTTi(ta,k);

        memcpy(c,ta,sizeof(u2)*len);
    }
};

void test()
{
    static u2 a[1<<21];
    static u2 b[1<<21];
    static u2 c[1<<21];
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    //for(int i=0;i<10000;i++)a[i]=b[i]=(i&16)==0?(i&~32)+1:0;
    for(int i=0;i<(1ull<<21);i++)a[i]=b[i]=i<(1ull<<20)?i+1:0;
    
    NTT_simple::mul(a,b,1<<20,1<<20,c);
    puts("\nans:\n");
    debug_print_arr(c+(1<<20),32);


    Ntt ntt;
    ntt.mul(a,b,c,1ull<<21);

    puts("\nmul_fast ans:\n");
    debug_print_arr(c+(1<<20),32);
}
*/


void poly_multiply(unsigned *a, int n, unsigned *b, int m, unsigned *c)
{

    //static int i=(test(),0);
    // u3 len=n+m+1;
    // u3 k=1;
    // while(k<len)k<<=1;

    // u2*at=(u2*)aligned_alloc(k*4,64);
    // u2*bt=(u2*)aligned_alloc(k*4,64);
    // u2*ct=(u2*)aligned_alloc(k*4,64);

    // memcpy(at,a,(n+1)*4);
    // memset(at+n+1,0,(k-n-1)*4);
    // memcpy(bt,b,(n+1)*4);
    // memset(bt+m+1,0,(k-m-1)*4);
    // memset(ct,0,k*4);

    Ntt ntt;
    ntt.mul(a,b,c,n+m+1);

    //memcpy(c,ct,(n+m+1)*4);
    // aligned_free(at);
    // aligned_free(bt);
    // aligned_free(ct);

    //aligned_alloc()
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


