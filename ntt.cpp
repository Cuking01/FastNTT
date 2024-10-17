#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<random>
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

struct ymm
{
    __m256i x;
    ymm(){}
    ymm(__m256i x):x(x){}
    ymm(const void*p):x(*(__m256i*)p){}
    ymm(U x):x(_mm256_set1_epi32(x)){}
    operator __m256i(){return x;}
    void store(void*p) const {*(__m256i*)p=x;}
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

inline ymm jmod(ymm a){return a-(a>mod1_vec&mod_vec);}

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

ymm mogo_n;
ymm mogo_np;

// inline ymm mul_mod(ymm a,ymm b)
// {
//     static constexpr U mask=0xaa;

//     ymm a1=rmov(a,32);
//     ymm b1=rmov(b,32);

//     ymm t1=a1*b1;
//     ymm t0=a*b;
    
//     ymm abl=blend<mask>(t1,lmov(t2,32));
//     ymm abh=blend<mask>(rmov(t1,25),lmov(t2,7));

//     ymm ab_p=blend<mask>(rmov(abh*mod_inv_vec,33),rmov(abh,32)*mod_inv_vec>>1);
//     a=abl-mullo(ab_p,mod_vec);
//     return jmod(a);
// }

inline ymm mul_mod(ymm a,ymm b)
{
    ymm a1=rmov(a,32);
    ymm b1=rmov(b,32);
    ymm t0=a*b;
    ymm t1=a1*b1;

    ymm q0=t0*mogo_np;
    ymm q1=t1*mogo_np;

    t0=rmov(t0,32);

    ymm m0=q0*mogo_n;
    ymm m1=q1*mogo_n;
    m0=rmov(m0,32);

    ymm res=blend<0xaa>(t0,t1)-blend<0xaa>(m0,m1);
    return jmod(res+mod_vec);
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
    t0.print64("t0");
    t1=t1*mod_vec;
    t1.print64("t1");
    return a-blend<0xaa>(t0,lmov(t1,32));
}

ymm mogo_to(ymm a)
{
    ymm t0=a;
    ymm t1=rmov(a,32);

    t0.print64("t0");
    t1.print64("t1");

    ymm q0=t0*mogo_np;
    ymm q1=t1*mogo_np;

    q0.print64("q0");
    q1.print64("q1");

    ymm m0=q0*mogo_n;
    ymm m1=q1*mogo_n;

    m0.print64("m0");
    m1.print64("m1");

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
            for(int i=8;i<len;i+=8)
            {
                tr=mul_mod(Wr_vec,tr);tr.store(wr+len+i);
                ti=mul_mod(Wi_vec,ti);ti.store(wi+len+i);
            }
        }
    }
}
void NTTfa(U*a,S len)
{
    for(S i=len>>1;i;i>>=1)
    {
        if(i==1)
        {
            auto trans1=[](U*p)
            {
                ymm x(p);
                jmod(blend<0xaa>(x+rmov(x,32),lmov(x,32)-x+mod_vec)).store(p);
            };
            for(S j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans1(a+j);
                trans1(a+j+8);
            }
        }
        else if(i==2)
        {
            auto trans2=[](U*xp,U*yp,ymm w)
            {
                ymm x(xp),y(yp);
                ymm t1(blend<0xcc>(x,lmov128<8>(y)));
                ymm t2(blend<0x33>(y,rmov128<8>(x)));
                x=jmod(t1+t2);
                y=mul_mod(t1-t2+mod_vec,w);
                blend<0xcc>(x,lmov128<8>(y)).store(xp);
                blend<0x33>(y,rmov128<8>(x)).store(yp);
            };
            ymm w=_mm256_set_epi32(wr[3],wr[2],wr[3],wr[2],wr[3],wr[2],wr[3],wr[2]);
            for(int j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans2(a+j,a+j+8,w);
            }
        }
        else if(i==4)
        {
            auto trans4=[](U*xp,U*yp,ymm w)
            {
                ymm tx(xp),ty(yp);
                ymm x(permute2x128<0x20>(tx,ty));
                ymm y(permute2x128<0x31>(tx,ty));
                tx=jmod(x+y);
                ty=mul_mod(x-y+mod_vec,w);
                x=permute2x128<0x20>(tx,ty);
                y=permute2x128<0x31>(tx,ty);
                x.store(xp);
                y.store(yp);
            };
            ymm w=_mm256_set_epi32(wr[7],wr[6],wr[5],wr[4],wr[7],wr[6],wr[5],wr[4]);
            for(S j=0;j<len;j+=16)
            {
                Prefetch(a+j+16);
                trans4(a+j,a+j+8,w);
            }
        }
        else
        {
            auto trans=[](U*xp,U*yp,const U*wp)
            {
                ymm x(xp),y(yp),w(wp);
                jmod(x+y).store(xp);
                mul_mod(x-y+mod_vec,w).store(yp);
            };
            if(i==8)
            {
                for(S j=0;j<len;j+=16)
                {
                    Prefetch(a+j+16);
                    trans(a+j,a+j+8,wr+8);
                }
            }
            else
            {
                
                for(S j=0;j<len;j+=i<<1)
                {
                    for(S k=0;k<i;k+=16)
                    {
                        Prefetch(a+j+k+16);
                        trans(a+j+k,a+j+k+i,wr+i+k);
                        Prefetch(a+j+k+i+16);
                        trans(a+j+k+8,a+j+k+i+8,wr+i+k+8);
                    }
                }

            }
        }
    }
}
void NTTifa(U*a,S len)
{
    for(S i=1;i<len;i<<=1)
    {
        if(i==1)
        {
            auto trans1=[](U*p)
            {
                ymm x(p);
                jmod(blend<0xaa>(x+rmov(x,32),lmov(x,32)-x+mod_vec)).store(p);
            };
            for(S j=0;j<len;j+=16)
            {
                _mm_prefetch(a+j+16,_MM_HINT_T0);
                trans1(a+j);
                trans1(a+j+8);
            }
        }
        else if(i==2)
        {
            auto trans2=[](U*xp,U*yp,ymm w)
            {
                ymm x(xp),y(yp);
                ymm t1(blend<0xcc>(x,lmov128<8>(y)));
                ymm t2(blend<0x33>(y,rmov128<8>(x)));
                t2=mul_mod(t2,w);
                x=jmod(t1+t2);
                y=jmod(t1-t2+mod_vec);
                blend<0xcc>(x,lmov128<8>(y)).store(xp);
                blend<0x33>(y,rmov128<8>(x)).store(yp);
            };
            ymm w=_mm256_set_epi32(wi[3],wi[2],wi[3],wi[2],wi[3],wi[2],wi[3],wi[2]);
            for(int j=0;j<len;j+=16)
                trans2(a+j,a+j+8,w);
        }
        else if(i==4)
        {
            auto trans4=[](U*xp,U*yp,ymm w)
            {
                ymm tx(xp),ty(yp);
                ymm x(permute2x128<0x20>(tx,ty));
                ymm y(permute2x128<0x31>(tx,ty));
                y=mul_mod(y,w);
                tx=jmod(x+y);
                ty=jmod(x-y+mod_vec);
                x=permute2x128<0x20>(tx,ty);
                y=permute2x128<0x31>(tx,ty);
                x.store(xp);
                y.store(yp);
            };
            ymm w=_mm256_set_epi32(wi[7],wi[6],wi[5],wi[4],wi[7],wi[6],wi[5],wi[4]);
            for(S j=0;j<len;j+=16)
                trans4(a+j,a+j+8,w);
        }
        else
        {
            auto trans=[](U*xp,U*yp,const U*wp)
            {
                ymm y(yp),w(wp);
                y=mul_mod(y,w);
                ymm x(xp);
                jmod(x+y).store(xp);
                jmod(x-y+mod_vec).store(yp);
            };
            if(i==8)
            {
                for(S j=0;j<len;j+=16)
                {
                    Prefetch(a+j+16);
                    trans(a+j,a+j+8,wi+8);
                }
            }
            else
            {
                
                for(S j=0;j<len;j+=i<<1)
                {
                    for(S k=0;k<i;k+=16)
                    {
                        Prefetch(a+j+k+16);
                        trans(a+j+k,a+j+k+i,wi+i+k);
                        Prefetch(a+j+k+i+16);
                        trans(a+j+k+8,a+j+k+i+8,wi+i+k+8);
                    }
                }

            }
        }
    }
    
    ymm inv((UL)pow(len,mod-2)<<32%mod);
    for(S i=0;i<len;i+=8)
        mul_mod(a+i,inv).store(a+i);
    
    /*
    int k=__builtin_ctz(len);
    ymm k1_vec((U)(len-1));
    ymm v1_vec(1u);
    for(S i=0;i<len;i+=8)
    {
        ymm x(a+i);
        ymm t(p0_vec-x&k1_vec);
        jmod((x+t>>k)+mullo(mod_vec>>k,t)).store(a+i);
    }
    */
}

int n,m;
char buf[500000];
char wbuf[2000000];
void read();
void write();
#define TEST_JUDGE 1000000
alignas(64) U a[ml+16],b[ml+16],c[ml+16];



void test()
{
    ymm a=_mm256_set_epi32(1,2,3,4,5,6,7,8);
    ymm b=_mm256_set_epi32(2,3,4,5,6,7,8,9);
    a=to_mogo(a);
    a.print();
    b=to_mogo(b);
    b.print();
    ymm c=mul_mod(a,b);
    c.print("c_mogo_val");
    //c=mogo_to(c);
    c=mul_mod(c,ymm(1));
    c.print("c_val");
}


void poly_multiply(unsigned *a, int n, unsigned *b, int m, unsigned *c)
{
    
    
    LL r=1ll<<32;
    LL ri,np;
    exgcd(r,mod,ri,np);
    np=(np%r+r)%r;

    mogo_np=ymm(np);
    mogo_n=ymm(mod);
    test();
    exit(0);

    memcpy(::a,a,(n+1)*4);
    memcpy(::b,b,(m+1)*4);

    for(int i=0;i<=n;i++)
        ::a[i]=((UL)::a[i]<<32)%mod;
    for(int i=0;i<=m;i++)
        ::b[i]=((UL)::b[i]<<32)%mod;

    int len=n+m+1;
    int k=32;
    while(k<len)k<<=1;
    memset(::a+(n+1),0,(k-n-1)*4);
    memset(::b+(m+1),0,(k-m-1)*4);
    init(k);
    NTTfa(::a,k);
    NTTfa(::b,k);
    for(S i=0;i<k;i+=8)
        mul_mod(::a+i,::b+i).store(::c+i);
    NTTifa(::c,k);
    for(int i=0;i<k;i+=8)
        mogo_to(ymm(::c+i)).store(::c+i);
    memcpy(c,::c,len*4);
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