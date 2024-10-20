#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<random>
#include<utility>
#include<concepts>
#include<immintrin.h>
#include<emmintrin.h>

#pragma GCC target("avx2")
#pragma GCC optimize("-fno-strict-aliasing")

#define LL long long S
#define UL unsigned LL
#define U unsigned
#define S int
#define fr(i,l) for(S i=0;i<l;i++)

#define Prefetch(p) _mm_prefetch(p,_MM_HINT_T0)

constexpr U mod=998244353u;
constexpr U g=3u;
constexpr U gi=332748118u;

#if defined(_MSC_VER)
    // MSVC Compiler
    #define ALWAYS_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    // GCC or Clang Compiler
    #define ALWAYS_INLINE __attribute__((always_inline)) inline
#else
    // Other compilers
    #error "unknown compiler."
#endif

struct ymm
{
    __m256i x;
    ymm(){}
    ymm(__m256i x):x(x){}
    ymm(const void*p):x(*(__m256i*)p){}
    ymm(U x):x(_mm256_set1_epi32(x)){}
    operator __m256i() const {return x;}
    void load(const void*p){x=_mm256_load_si256((__m256i*)p);}
    void loadu(const void*p){x=_mm256_loadu_si256((__m256i*)p);}
    void store(void*p) const {_mm256_store_si256((__m256i*)p,x);}
    void storeu(void*p) const {_mm256_storeu_si256((__m256i*)p,x);}
    void stream(void*p) const {_mm256_stream_si256((__m256i*)p,x);}
    ymm print(const char*desc_str=0) const
    {
        alignas(64) unsigned tmp[8];
        store(tmp);
        if(desc_str)puts(desc_str);
        for(int i=0;i<8;i++)
            printf("%x ",tmp[i]);
        puts("");
        return *this;
    }
    ymm print64(const char*desc_str=0) const
    {
        alignas(64) UL tmp[4];
        store(tmp);
        if(desc_str)puts(desc_str);
        for(int i=0;i<4;i++)
            printf("%llx ",tmp[i]);
        puts("");
        return *this;
    }
};
ymm p1_vec(0xffffffffu);
ymm p0_vec(0u);
inline ymm operator+(ymm a,ymm b){return _mm256_add_epi32(a,b);}
inline ymm operator-(ymm a,ymm b){return _mm256_sub_epi32(a,b);}
inline ymm operator*(ymm a,ymm b){return _mm256_mul_epu32(a,b);}
inline ymm operator|(ymm a,ymm b){return _mm256_or_si256(a,b);}
inline ymm operator&(ymm a,ymm b){return _mm256_and_si256(a,b);}
inline ymm andnot(ymm a,ymm b){return _mm256_andnot_si256(a,b);}
inline ymm operator~(ymm a){return andnot(a,p1_vec);}
inline ymm operator>(ymm a,ymm b){return _mm256_cmpgt_epi32(a,b);}
inline ymm operator==(ymm a,ymm b){return _mm256_cmpeq_epi32(a,b);}
inline ymm operator>>(ymm a,int w){return _mm256_srli_epi32(a,w);}
inline ymm operator<<(ymm a,int w){return _mm256_slli_epi32(a,w);}
template<U mask>
inline ymm blend(ymm a,ymm b){return _mm256_blend_epi32(a,b,mask);}
inline ymm blendv(ymm a,ymm b,ymm mask){return _mm256_blendv_epi8(a,b,mask);}
template<U mask>
inline ymm permute2x128(ymm a,ymm b){return _mm256_permute2x128_si256(a,b,mask);}

inline ymm rmov(ymm a,int w){return _mm256_srli_epi64(a,w);}
inline ymm lmov(ymm a,int w){return _mm256_slli_epi64(a,w);}
template<int w>
inline ymm rmov128(ymm a){return _mm256_bsrli_epi128(a,w);}
template<int w>
inline ymm lmov128(ymm a){return _mm256_bslli_epi128(a,w);}
inline ymm mullo(ymm a,ymm b){return _mm256_mullo_epi32(a,b);}

ymm mod1_vec(mod-1);
ymm mod_vec(mod);
ymm mod_inv_vec(3524075686u);

U mo(U x){return x>=mod?x-mod:x;}



LL exgcd(LL a,LL b,LL&x,LL&y)
{
    if(b==0)
    {
        x=1;y=0;
        return a;
    }

    LL r=exgcd(b,a%b,y,x);
    y-=(a/b)*x;
    return r;
}

U mogo_np;
ymm mogo_n_vec;
ymm mogo_np_vec;

template<int n>
ALWAYS_INLINE void jmod(ymm_pack<n> a,ymm_pack<n> t,ymm&mod)
{
    execute_simd<_mm256_cmpgt_epi32>(t,a,mod);
    execute_simd<_mm256_and_si256>(t,t,mod);
    execute_simd<_mm256_sub_epi32>(a,a,t);
    
    //return a-(a>mod&mod);
}

//3n+1
template<int n>
ALWAYS_INLINE void mul_mod(ymm_pack<n> a,ymm_pack<n> b,ymm_pack<n> t,ymm&constant)
{
    constant=_mm256_set1_epi32(mogo_np);
    execute_simd<_mm256_mul_epu32>(t,a,b);
    execute_simd<rmov>(a,a,32);
    execute_simd<rmov>(b,b,32);
    execute_simd<_mm256_mul_epu32>(a,a,b);
    execute_simd<rmov>(b,t,32);
    execute_simd<blend<0xaa>>(b,b,a);
    execute_simd<_mm256_mul_epu32>(a,a,constant);
    execute_simd<_mm256_mul_epu32>(t,t,constant);
    constant=_mm256_set1_epi32(mod);
    execute_simd<_mm256_mul_epu32>(a,a,constant);
    execute_simd<_mm256_mul_epu32>(t,t,constant);
    execute_simd<rmov>(t,t,32);
    execute_simd<blend<0xaa>>(a,t,a);
    execute_simd<_mm256_sub_epi32>(a,a,b);
    jmod(a,t,constant);

    // ymm a1=rmov(a,32);
    // ymm b1=rmov(b,32);
    // ymm t0=a*b;
    // ymm t1=a1*b1;
    // ymm q0=t0*mogo_np;
    // ymm q1=t1*mogo_np;
    // t0=rmov(t0,32);
    // ymm m0=q0*mogo_n;
    // ymm m1=q1*mogo_n;
    // m0=rmov(m0,32);
    // ymm res=blend<0xaa>(t0,t1)-blend<0xaa>(m0,m1);
    // return jmod(res+mod_vec);
}

ymm to_mogo(ymm a)
{
    static constexpr U yip=((1ull<<62)+mod-1)/mod-(1ull<<32);
    static ymm yip_v=ymm(yip);

    ymm x=a<<2;
    ymm t0=x*yip_v;
    ymm t1=rmov(x,32)*yip_v;
    t0=rmov(t0,32);
    t0=t0+x;
    t1=t1+x;
    t1=rmov(t1,32);
    t0=t0*mod_vec;
    t1=t1*mod_vec;
    return _mm256_setzero_si256()-blend<0xaa>(t0,lmov(t1,32));
}

ymm mogo_to(ymm a)
{
    ymm t0=a;
    ymm t1=rmov(a,32);

    ymm q0=t0*mogo_np;
    ymm q1=t1*mogo_np;

    ymm m0=q0*mogo_n;
    ymm m1=q1*mogo_n;

    m0=rmov(m0,32);

    ymm res=mod_vec-blend<0xaa>(m0,m1);

    return jmod(res);
}

U pow(U a,U b)
{
    U ans=1;
    for(;b;a=(UL)a*a%mod,b>>=1)
        if(b&1)ans=(UL)ans*a%mod;
    return ans;
}

U& mul(U&a,U b){return a=(UL)a*b%mod;}
S up(S x){S l=1;while(l<x)l<<=1;return l;}

constexpr S ml=1<<24;
alignas(64) U wr[ml+16],wi[ml+16];



int n,m;
char buf[500000];
char wbuf[2000000];
void read();
void write();
#define TEST_JUDGE 1000000
alignas(64) U a[ml+16],b[ml+16],c[ml+16];

template<typename T>
concept Pointer=std::is_pointer_v<T>;

template<typename T>
struct is_const_pointer: std::false_type{};

template<typename T>
struct is_const_pointer<const T*>: std::true_type{};

template<typename T>
constexpr bool is_const_pointer_v=is_const_pointer<T>::value;

template<typename T>
concept CPointer=is_const_pointer_v<T>;

template<int n>
struct ymms
{
    ymm mm[n];

    ymms(){}

    template<std::size_t... ids>
    ALWAYS_INLINE ymms(const ymm*p,std::index_sequence<ids...>):mm{(p+ids)...}{}

    ALWAYS_INLINE ymms(const void*p):ymm((ymm*)p,std::make_index_sequence<n>()){}
    
    template<Pointer... Args>
    ALWAYS_INLINE ymms(Args... p):mm{p...}{}

    template<std::size_t... ids>
    ALWAYS_INLINE void load_impl(void*p,std::index_sequence<ids...>)
    {
        ((mm[ids].load((ymm*)p+ids)),...);
    }

    ALWAYS_INLINE void load(void*p)
    {
        load_impl(p,std::make_index_sequence<n>());
    }

    template<Pointer... Args>
    ALWAYS_INLINE void load(Args... p) requires (sizeof...(Args)==n)
    {
        int cnt=0;
        ((mm[cnt++].load(p)),...);
    }

    template<std::size_t... ids>
    ALWAYS_INLINE void loadu_impl(const void*p,std::index_sequence<ids...>)
    {
        ((mm[ids].loadu((ymm*)p+ids)),...);
    }

    ALWAYS_INLINE void loadu(const void*p)
    {
        loadu_impl(p,std::make_index_sequence<n>());
    }

    template<Pointer... Args>
    ALWAYS_INLINE void loadu(Args... p) requires (sizeof...(Args)==n)
    {
        int cnt=0;
        ((mm[cnt++].loadu(p)),...);
    }

    template<std::size_t... ids>
    ALWAYS_INLINE void store_impl(void*p,std::index_sequence<ids...>)
    {
        ((mm[ids].store((ymm*)p+ids)),...);
    }

    ALWAYS_INLINE void store(void*p)
    {
        store_impl(p,std::make_index_sequence<n>());
    }

    template<Pointer... Args>
    ALWAYS_INLINE void store(Args... p) requires (sizeof...(Args)==n)
    {
        int cnt=0;
        ((mm[cnt++].store(p)),...);
    }

    template<std::size_t... ids>
    ALWAYS_INLINE void storeu_impl(void*p,std::index_sequence<ids...>)
    {
        ((mm[ids].storeu((ymm*)p+ids)),...);
    }

    ALWAYS_INLINE void storeu(void*p)
    {
        storeu_impl(p,std::make_index_sequence<n>());
    }

    template<Pointer... Args>
    ALWAYS_INLINE void storeu(Args... p) requires (sizeof...(Args)==n)
    {
        int cnt=0;
        ((mm[cnt++].storeu(p)),...);
    }

    template<std::size_t... ids>
    ALWAYS_INLINE void stream_impl(void*p,std::index_sequence<ids...>)
    {
        ((mm[ids].stream((ymm*)p+ids)),...);
    }

    ALWAYS_INLINE void stream(void*p)
    {
        stream_impl(p,std::make_index_sequence<n>());
    }

    template<Pointer... Args>
    ALWAYS_INLINE void stream(Args... p) requires (sizeof...(Args)==n)
    {
        int cnt=0;
        ((mm[cnt++].stream(p)),...);
    }
};

struct ymm_ref
{
    ymm&ref;
};

template<typename T>
concept ymm_like=
        std::is_same_v<T,ymm>||
        std::is_same_v<T,__m256i>||
        std::is_same_v<T,ymm_ref>;

template<int n>
struct ymm_pack
{
    ymm_ref ref[n];

    template<typename... Agrs>
    ymm_pack(ymm_like auto&...args):ref{args...}{}

    template<std::size_t... ids>
    ymm_pack(ymms<n>&mms,std::index_sequence<ids...>):ref{mms.mm[ids]...}{}

    ymm_pack(ymms<n>&mms):ymm_pack(mms,std::make_index_sequence<n>()){}

    template<int... id>
    ymm_pack shuffle() const
    {
        return ymm_pack{ref[id]...};
    }
};


template<typename T>
ALWAYS_INLINE const T&extract(const T&a,int i)
{
    return a;
}

template<int n>
ALWAYS_INLINE const ymm& extract(const ymm_pack<n>&a,int i)
{
    return a.ref[i].ref;
}

template<auto fun,int n,typename... Args>
ALWAYS_INLINE void execute_simd(ymm_pack<n> a,const Args&... args)
{
    for(int i=0;i<n;i++)
        a.ref[i].ref=fun(extract(args,i)...);
}

void arr_to_mogo1(unsigned*from,unsigned*to,int n)
{
    static constexpr U yip=((1ull<<62)+mod-1)/mod-(1ull<<32);
    ymm yip_v=ymm(yip);
    ymm zero=_mm256_setzero_si256();
    ymm mod_vec=::mod_vec;
    for(int i=0;i+31<n;i+=32)
    {
        ymm x0=_mm256_loadu_si256((__m256i*)(from+i+0));
        ymm x1=_mm256_loadu_si256((__m256i*)(from+i+8));
        ymm x2=_mm256_loadu_si256((__m256i*)(from+i+16));
        ymm x3=_mm256_loadu_si256((__m256i*)(from+i+24));

        x0=x0<<2;
        x1=x1<<2;
        x2=x2<<2;
        x3=x3<<2;

        ymm t01=rmov(x0,32);
        ymm t11=rmov(x1,32);
        ymm t21=rmov(x2,32);
        ymm t31=rmov(x3,32);

        ymm t00=x0*yip_v;
        ymm t10=x1*yip_v;
        ymm t20=x2*yip_v;
        ymm t30=x3*yip_v;

        t01=t01*yip_v;
        t11=t11*yip_v;
        t21=t21*yip_v;
        t31=t31*yip_v;

        t00=rmov(t00,32);
        t10=rmov(t10,32);
        t20=rmov(t20,32);
        t30=rmov(t30,32);

        t00=t00+x0;
        t10=t10+x1;
        t20=t20+x2;
        t30=t30+x3;

        t01=t01+x0;
        t11=t11+x1;
        t21=t21+x2;
        t31=t31+x3;

        t01=rmov(t01,32);
        t11=rmov(t11,32);
        t21=rmov(t21,32);
        t31=rmov(t31,32);

        t00=t00*mod_vec;
        t10=t10*mod_vec;
        t20=t20*mod_vec;
        t30=t30*mod_vec;

        t01=t01*mod_vec;
        t11=t11*mod_vec;
        t21=t21*mod_vec;
        t31=t31*mod_vec;

        t01=lmov(t01,32);
        t11=lmov(t11,32);
        t21=lmov(t21,32);
        t31=lmov(t31,32);

        x0=blend<0xaa>(t00,t01);
        x1=blend<0xaa>(t10,t11);
        x2=blend<0xaa>(t20,t21);
        x3=blend<0xaa>(t30,t31);

        x0=zero-x0;
        x1=zero-x1;
        x2=zero-x2;
        x3=zero-x3;

        x0.store(to+i+0);
        x1.store(to+i+8);
        x2.store(to+i+16);
        x3.store(to+i+24);
    }
}

void arr_to_mogo2(unsigned*from,unsigned*to,int n)
{
    static constexpr U yip=((1ull<<62)+mod-1)/mod-(1ull<<32);
    ymm yip_v=ymm(yip);
    ymm zero=_mm256_setzero_si256();

    for(int i=0;i+31<n;i+=32)
    {
        ymms<4> x,t0,t1;
        ymm_pack<4> px(x),pt0(t0),pt1(t1);
        x.loadu(from+i);

        execute_simd<_mm256_slli_epi32>(px,px,2);
        execute_simd<rmov>(pt1,px,32);
        execute_simd<_mm256_mul_epu32>(pt0,px,yip_v);
        execute_simd<_mm256_mul_epu32>(pt1,px,yip_v);
        execute_simd<rmov>(pt0,pt0,32);
        execute_simd<_mm256_add_epi32>(pt0,pt0,px);
        execute_simd<_mm256_add_epi32>(pt1,pt1,px);
        execute_simd<rmov>(pt1,pt1,32);
        execute_simd<_mm256_mul_epu32>(pt0,pt0,mod_vec);
        execute_simd<_mm256_mul_epu32>(pt1,pt1,mod_vec);
        execute_simd<lmov>(pt1,pt1,32);
        execute_simd<blend<0xaa>>(px,pt0,pt1);
        execute_simd<_mm256_sub_epi32>(px,zero,px);

        x.store(to+i);
    }
}

void arr_mogo_to0(unsigned*from,unsigned*to,int n)
{
    for(int i=0;i<n;i+=8)
    {
        ymm t(from+i);
        t=mogo_to(t);
        t.storeu(to+i);
    }
}

void arr_mogo_to1(unsigned*from,unsigned*to,int n)
{
    ymm mogo_np=::mogo_np;
    ymm mogo_n=::mogo_n;
    ymm mod1_vec(mod-1);
    int i;
    for(i=0;i+31<n;i+=40)
    {
        ymm t00(from+i+0);
        ymm t01(from+i+8);
        ymm t02(from+i+16);
        ymm t03(from+i+24);
        ymm t04(from+i+32);

        ymm t10,t11,t12,t13,t14;

        ymm_pack<5> pt0(t00,t01,t02,t03,t04);
        ymm_pack<5> pt1(t10,t11,t12,t13,t14);

        execute_simd<rmov>(pt1,pt0,32);
        execute_simd<_mm256_mul_epu32>(pt0,pt0,mogo_np);
        execute_simd<_mm256_mul_epu32>(pt1,pt1,mogo_np);
        execute_simd<_mm256_mul_epu32>(pt0,pt0,mogo_n);
        execute_simd<_mm256_mul_epu32>(pt1,pt1,mogo_n);
        execute_simd<rmov>(pt0,pt0,32);
        execute_simd<blend<0xaa>>(pt0,pt0,pt1);
        execute_simd<_mm256_sub_epi32>(pt0,mogo_n,pt0);
        execute_simd<_mm256_cmpgt_epi32>(pt1,pt0,mod1_vec);
        execute_simd<_mm256_and_si256>(pt1,pt1,mogo_n);
        execute_simd<_mm256_sub_epi32>(pt0,pt0,pt1);

        t00.storeu(to+i+0);
        t01.storeu(to+i+8);
        t02.storeu(to+i+16);
        t03.storeu(to+i+24);
        t04.storeu(to+i+32);
    }

    for(;i<n;i+=8)
    {
        ymm t(from+i);
        t=mogo_to(t);
        t.storeu(to+i);
    }
}


void init(S ml)
{
    for(S len=1;len<ml;len<<=1)
    {
        U Wr=pow(g,(mod-1)/(len<<1));
        U Wi=pow(gi,(mod-1)/(len<<1));
        if(len<8)
        {
            U tr=1,ti=1;
            fr(i,len)
            {
                wr[len+i]=tr;mul(tr,Wr);
                wi[len+i]=ti;mul(ti,Wi);
            }
        }
        else
        {
            {
                U tr=1,ti=1;
                fr(i,8)
                {
                    wr[len+i]=tr;mul(tr,Wr);
                    wi[len+i]=ti;mul(ti,Wi);
                }
            }
            ymm tr(wr+len),ti(wi+len),Wr_vec(pow(Wr,8)),Wi_vec(pow(Wi,8));
            tr=to_mogo(tr);
            ti=to_mogo(ti);
            Wr_vec=to_mogo(Wr_vec);
            Wi_vec=to_mogo(Wi_vec);
            tr.store(wr+len);
            ti.store(wi+len);
            
            for(int i=8;i<len;i+=8)
            {
                tr=mul_mod(Wr_vec,tr);tr.store(wr+len+i);
                ti=mul_mod(Wi_vec,ti);ti.store(wi+len+i);
            }
        }
    }
    to_mogo(ymm(wr)).store(wr);
    to_mogo(ymm(wi)).store(wi);
}
void NTTfa(U*from,U*a,S len)
{
    // for(S i=len>>1;i>=32;i>>=1)
    // {
    //     if(i==1)
    //     {
    //         auto trans1=[](U*p)
    //         {
    //             ymm x(p);
    //             jmod(blend<0xaa>(x+rmov(x,32),lmov(x,32)-x+mod_vec)).store(p);
    //         };
    //         for(S j=0;j<len;j+=16)
    //         {
    //             Prefetch(a+j+16);
    //             trans1(a+j);
    //             trans1(a+j+8);
    //         }
    //     }
    //     else if(i==2)
    //     {
    //         auto trans2=[](U*xp,U*yp,ymm w)
    //         {
    //             ymm x(xp),y(yp);
    //             ymm t1(blend<0xcc>(x,lmov128<8>(y)));
    //             ymm t2(blend<0x33>(y,rmov128<8>(x)));
    //             x=jmod(t1+t2);
    //             y=mul_mod(t1-t2+mod_vec,w);
    //             blend<0xcc>(x,lmov128<8>(y)).store(xp);
    //             blend<0x33>(y,rmov128<8>(x)).store(yp);
    //         };
    //         ymm w=_mm256_set_epi32(wr[3],wr[2],wr[3],wr[2],wr[3],wr[2],wr[3],wr[2]);
    //         for(int j=0;j<len;j+=16)
    //         {
    //             Prefetch(a+j+16);
    //             trans2(a+j,a+j+8,w);
    //         }
    //     }
    //     else if(i==4)
    //     {
    //         auto trans4=[](U*xp,U*yp,ymm w)
    //         {
    //             ymm tx(xp),ty(yp);
    //             ymm x(permute2x128<0x20>(tx,ty));
    //             ymm y(permute2x128<0x31>(tx,ty));
    //             tx=jmod(x+y);
    //             ty=mul_mod(x-y+mod_vec,w);
    //             x=permute2x128<0x20>(tx,ty);
    //             y=permute2x128<0x31>(tx,ty);
    //             x.store(xp);
    //             y.store(yp);
    //         };
    //         ymm w=_mm256_set_epi32(wr[7],wr[6],wr[5],wr[4],wr[7],wr[6],wr[5],wr[4]);
    //         for(S j=0;j<len;j+=16)
    //         {
    //             Prefetch(a+j+16);
    //             trans4(a+j,a+j+8,w);
    //         }
    //     }
    //     else
    //     {
    //         auto trans=[](U*xp,U*yp,const U*wp)
    //         {
    //             ymm x(xp),y(yp),w(wp);
    //             jmod(x+y).store(xp);
    //             mul_mod(x-y+mod_vec,w).store(yp);
    //         };
    //         if(i==8)
    //         {
    //             for(S j=0;j<len;j+=16)
    //             {
    //                 Prefetch(a+j+16);
    //                 trans(a+j,a+j+8,wr+8);
    //             }
    //         }
    //         else
    //         {
                
    //             for(S j=0;j<len;j+=i<<1)
    //             {
    //                 for(S k=0;k<i;k+=16)
    //                 {
    //                     Prefetch(a+j+k+16);
    //                     trans(a+j+k,a+j+k+i,wr+i+k);
    //                     Prefetch(a+j+k+i+16);
    //                     trans(a+j+k+8,a+j+k+i+8,wr+i+k+8);
    //                 }
    //             }

    //         }
    //     }
    // }
}
void NTTifa(U*a,S len)
{
    // for(S i=1;i<len;i<<=1)
    // {
    //     if(i==1)
    //     {
    //         auto trans1=[](U*p)
    //         {
    //             ymm x(p);
    //             jmod(blend<0xaa>(x+rmov(x,32),lmov(x,32)-x+mod_vec)).store(p);
    //         };
    //         for(S j=0;j<len;j+=16)
    //         {
    //             _mm_prefetch(a+j+16,_MM_HINT_T0);
    //             trans1(a+j);
    //             trans1(a+j+8);
    //         }
    //     }
    //     else if(i==2)
    //     {
    //         auto trans2=[](U*xp,U*yp,ymm w)
    //         {
    //             ymm x(xp),y(yp);
    //             ymm t1(blend<0xcc>(x,lmov128<8>(y)));
    //             ymm t2(blend<0x33>(y,rmov128<8>(x)));
    //             t2=mul_mod(t2,w);
    //             x=jmod(t1+t2);
    //             y=jmod(t1-t2+mod_vec);
    //             blend<0xcc>(x,lmov128<8>(y)).store(xp);
    //             blend<0x33>(y,rmov128<8>(x)).store(yp);
    //         };
    //         ymm w=_mm256_set_epi32(wi[3],wi[2],wi[3],wi[2],wi[3],wi[2],wi[3],wi[2]);
    //         for(int j=0;j<len;j+=16)
    //             trans2(a+j,a+j+8,w);
    //     }
    //     else if(i==4)
    //     {
    //         auto trans4=[](U*xp,U*yp,ymm w)
    //         {
    //             ymm tx(xp),ty(yp);
    //             ymm x(permute2x128<0x20>(tx,ty));
    //             ymm y(permute2x128<0x31>(tx,ty));
    //             y=mul_mod(y,w);
    //             tx=jmod(x+y);
    //             ty=jmod(x-y+mod_vec);
    //             x=permute2x128<0x20>(tx,ty);
    //             y=permute2x128<0x31>(tx,ty);
    //             x.store(xp);
    //             y.store(yp);
    //         };
    //         ymm w=_mm256_set_epi32(wi[7],wi[6],wi[5],wi[4],wi[7],wi[6],wi[5],wi[4]);
    //         for(S j=0;j<len;j+=16)
    //             trans4(a+j,a+j+8,w);
    //     }
    //     else
    //     {
    //         auto trans=[](U*xp,U*yp,const U*wp)
    //         {
    //             ymm y(yp),w(wp);
    //             y=mul_mod(y,w);
    //             ymm x(xp);
    //             jmod(x+y).store(xp);
    //             jmod(x-y+mod_vec).store(yp);
    //         };
    //         if(i==8)
    //         {
    //             for(S j=0;j<len;j+=16)
    //             {
    //                 Prefetch(a+j+16);
    //                 trans(a+j,a+j+8,wi+8);
    //             }
    //         }
    //         else
    //         {
                
    //             for(S j=0;j<len;j+=i<<1)
    //             {
    //                 for(S k=0;k<i;k+=16)
    //                 {
    //                     Prefetch(a+j+k+16);
    //                     trans(a+j+k,a+j+k+i,wi+i+k);
    //                     Prefetch(a+j+k+i+16);
    //                     trans(a+j+k+8,a+j+k+i+8,wi+i+k+8);
    //                 }
    //             }

    //         }
    //     }
    // }
    
    // ymm inv((UL)pow(len,mod-2)<<32%mod);
    // for(S i=0;i<len;i+=8)
    //     mul_mod(a+i,inv).store(a+i);
}


void test()
{
    alignas(64) U a[128];
    for(int i=0;i<128;i++)
        a[i]=i;
    arr_to_mogo2(a,::a,128);

    arr_mogo_to1(::a,a,128);

    for(int i=0;i<128;i++)
    {
        printf("%d\n",a[i]);
    }
}

void poly_multiply(unsigned *a, int n, unsigned *b, int m, unsigned *c)
{
    LL r=1ll<<32;
    LL ri,np;
    exgcd(r,mod,ri,np);
    np=(np%r+r)%r;

    mogo_np=np;
    mogo_np_vec=ymm(np);
    mogo_n_vec=ymm(mod);

    // test();
    // exit(0);

    for(int i=0;i<200;i++)
    {
        arr_to_mogo2(a,::a,n+1);
        //arr_to_mogo1(a,::a,n+1);
        //arr_mogo_to1(::a,a,n+1);
    }

    // arr_to_mogo2(a,::a,n+1);
    // arr_to_mogo2(b,::b,n+1);

    // int len=n+m+1;
    // int k=32;
    // while(k<len)k<<=1;

    // memset(::a+(n+1),0,(k-n-1)*4);
    // memset(::b+(m+1),0,(k-m-1)*4);

    // init(k);
    // NTTfa(::a,k);
    // NTTfa(::b,k);
    // for(S i=0;i<k;i+=8)
    //     mul_mod(::a+i,::b+i).store(::c+i);
    // NTTifa(::c,k);
    
    // arr_mogo_to1(::c,c,k);
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

void read()
{
    #ifdef ONLINE_JUDGE
        char*f=buf;
        buf[fread(buf,1,sizeof buf,stdin)]=0;
        int x=0;
        while(*f<'0')f++;
        while(*f>='0')x=x*10+*f++ -'0';
        n=x;
        x=0;
        while(*f<'0')f++;
        while(*f>='0')x=x*10+*f++ -'0';
        m=x;
        f++;
        for(int i=0;i<=n;i++)
            a[i]=*f++ -'0',f++;
        for(int i=0;i<=m;i++)
            b[i]=*f++ -'0',f++;
    #elif TEST_JUDGE
        std::mt19937 rnd(300100);
        n=TEST_JUDGE,m=TEST_JUDGE;
        for(int i=0;i<=n;i++)
            a[i]=rnd()%10;
        for(int j=0;j<=m;j++)
            b[j]=rnd()%10;
    #else
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;i++)
            scanf("%d",a+i);
        for(int j=0;j<=m;j++)
            scanf("%d",b+j);

    #endif
}

void write()
{
    #ifdef TEST_JUDGE
        #if TEST_JUDGE>128
            return;
        #endif
    #endif
    int len=n+m+1;
    char*f=wbuf;
    for(S i=0;i<len;i++)
    {
        U x=a[i];
        if(x)
        {
            char*sf=f;
            do
            {
                *f++=x%10+'0';
                x/=10;
            }while(x);
            char*ef=f-1;
            *f++=' ';
            while(sf<ef)
            {
                char t=*sf;*sf=*ef;*ef=t;
                sf++;ef--;
            }
            
        }
        else
        {
            *f++='0';
            *f++=' ';
        }
    }
    *f=0;
    fwrite(wbuf,1,f-wbuf,stdout);
}