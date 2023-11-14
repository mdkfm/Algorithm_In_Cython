long scale(long x, long y, long z){
    /* this uses `leaq` but not `addq` and `imulq` */
    long t = x + 4 * y + 12 * z;
    return t;
}

long arith(long x, long y, long z){
    long t1 = x ^ y; 
    /* xorq %rsi, %rdi */
    
    long t2 = z * 48; /* optimized as (3 * z) << 4 */
    /* leaq (%rdx, %rdx, 2) %rax */
    /* salq $4, %rax */

    long t3 = t1 & 0x0F0F0F0F; /* andl $252645135, %edi */
    long t4 = t2 - t3; /* subq %rdi, %rax */
    return t4;
}


double float_cal(double x, double y, double z){
    // float will use XMM register
    // x in %xmm0, y in %xmm1, z in %xmm2,
    double result;
    // mulsd %xmm1, %xmm0
    // divsd %xmm2, %xmm0
    result = x * y / z;

    // return value in %xmm0
    return result;
}