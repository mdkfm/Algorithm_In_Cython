long lt_cnt = 0;
long ge_cnt = 0;

long absdiff_se(long x, long y){
    // because the lt_cnt and ge_cnt, 
    // this function will be compiled into conditional control branch
    long result;
    if(x < y){
        lt_cnt ++;
        result = y - x;
    }
    else{
        ge_cnt ++;
        result = x - y;
    }
    return result;
}

// goto simulation
long gotodiff_se(long x, long y){
    long result;
    if(x >= y)
        // process else-branch at first
        goto x_ge_y;
    lt_cnt++;
    result = y - x;
    return result;

    x_ge_y:
        ge_cnt++;
        result = x - y;
        return result;
}

// format :
// if (test-expr)
//      then-state
// else
//      else-statement
//
// normal goto simulation format :
// t = test-expr
// if(! t)
//      goto false;
// then-statement
// goto done;
// false:
//      else-statement
// done:


long absdiff(long x, long y){
    // gcc -Ofast -S branch.c
    // this if branch will be optimized with conditional move
    long result;
    if(x < y)
        result = y - x;
    else
        result = x - y;
    return result;
}

// cmov simltaion
long cmovdiff(long x, long y){
    long rval = x - y;
    long eval = y - x;
    long test = x < y;
    if(test) rval = eval; 
	// cmpq	    %rsi, %rdi
	// cmovl	%rdx, %rax
    return rval;
}