// ********************** if branch ********************** //

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


// ********************** switch branch ********************** //

void switch_eg(long x, long n, long *dest){
    long val = x;
    switch (n){
    case 100:
        val *= 13;
        break;
    case 102:
        val += 10;
        // Fall through
    case 103:
        val += 11;
    case 104:
    case 106:
        val *= val;
        break;
    default:
        val = 0;
    }
    *dest = val;
}

// switch uses jump table
// simultaio
void switch_eg_impl(long x, long n, long *dest){
    static void * jt[7] = {
        &&loc_A, &&loc_def, &&loc_B,
        &&loc_C, &&loc_D, &&loc_def,
        &&loc_D
    };
    unsigned long index = n - 100;
    long val;
    if (index > 6) goto loc_def;
    goto *jt[index];

loc_A: // case 100
    val = x * 13;
    goto done;
loc_B: // case 102
    x = x + 10;
    // Fall through
loc_C: // case 103
    val = x + 11;
    goto done;
loc_D: // case 104, 106
    val = x * x;
    goto done;
loc_def: // default case
    val = 0;
done:
    *dest = val;
}