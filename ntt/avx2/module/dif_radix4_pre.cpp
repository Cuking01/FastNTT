

//执行前若干层变换，必须执行偶数层。总层数为L，总长度为2^L，负责变换前m层。
//变换时，分成2^(L-m)/S组，其中i mod (2^(L-m))属于0~S-1的划分为一组，属于S~2S-1的为一组，以此类推。i是下标。
//限制：2^L>=2^m*S，S是2的幂次，且S>=16，2^m*S*2*sizeof(u2)<=sizeof(L2)，tmp的长度>=2^m
void dif_radix4_pre(u2*a,u2*tmp,u2*w,u3 L,u3 m,u3 S)
{
	Pack<VU32x8,2> vx0,vx1,vx2,vx3,vt0,vt1,vw;
    VU32x8 vmod,vmodp;

    MF::get_mod(vmod);
    MF::get_modp(vmodp);

    u3 len=1ull<<L;

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

    auto butterfly=[&]<bool w_tmp> ALWAYS_INLINE_LAMBDA (
    	u2*px0_in,u2*px1_in,u2*px2_in,u2*px3_in,
    	u2*px0_out,u2*px1_out,u2*px2_out,u2*px3_out,
    	u2*pw1,u2*pw2,u2*pw3)
    {

    };


    for(u3 l=0;l<m;l+=2)
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
                _mm_prefetch(px0+k+32,_MM_HINT_T0);
                _mm_prefetch(px1+k+32,_MM_HINT_T0);
                _mm_prefetch(px2+k+32,_MM_HINT_T0);
                _mm_prefetch(px3+k+32,_MM_HINT_T0);
                _mm_prefetch(pw+k+32,_MM_HINT_T0);
                _mm_prefetch(pw+k*2+32,_MM_HINT_T0);
                _mm_prefetch(pw+k*3+32,_MM_HINT_T0);

                vmod=vmod<<cint<1>;

                

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
