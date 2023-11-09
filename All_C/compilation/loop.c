// all kinds of loops use CMP, TEST and JMP
// we could use if and goto to simulate it in C

// *************************** while loop *************************** //
long fact_do(long n){
    // do once before test
    long result = 1;
    do {
        result *= n;
        n = n - 1;
        // this is only a demo
        // it runs error when n=1
    } while(n > 1);
    return result;
}

// simulation
long fact_do_doto(long n){
    long result = 1;
    loop:
        result += n;
        n = n - 1;
        if(n > 1)
            goto loop;
    return result;
}

// format:
// do{
//     loop-statement
// } while(test-expr);

// goto simiulation format:
// loop:
//     loop-statement
//     if(test-expr) goto loop;


long fact_while(long n){
    // do after test
    long result = 1;
    while (n > 1){
        result *= n;
        n = n - 1;
    }
    return result;
}

// simulaion
long fact_while_jm_goto(long n){
    long result = 1;
    goto test;
    loop:
        result *= n;
        n = n - 1;
    test:
        if(n > 1) goto loop;
    return result;
}

long fact_while_gd_goto(long n){
    long result = 1;
    if(n <= 1) goto done;
    loop:
        result *= n;
        n = n - 1;
        if(n > 1) goto loop;
    done:
    return result;
}

// format :
// while(test-expr){
//     loop-statement
// }

// jump to middle format:
// goto test;
// loop:
//     loop-statement
// test:
//     if(test-expr) goto loop;

// guarded-do format:
// if(! test-expr) goto done;
// loop:
//     loop-statement;
//     if(test-expr) goto loop;
// done:


// *************************** for loop *************************** //
long fact_for(long n){
    long i;
    long result = 1;
    for(i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}

// the for loop is similar to while loop

// for loop :
// for(init-expr; test-expr; update-expr){
//     body-statement
// }
// then transformed into
// while loop:
// init-expr
// while(test-expr){
//     body-statement
//     update-expr;
// }

long fact_for_while(long n){
    long i = 2;
    long result = 1;
    while(i <= n){
        result *= i;
        i ++;
    }
    return result;
}

// then transformed into goto 
// jump-to-middle and guarded-do format

// jump-to-middle :
// init-expr
// goto test;
// loop:
//     body-statement
//     update-expr
// test:
//     if(test-expr) goto loop;

// guarded-do :
// init-expr;
// if(! test-expr) goto done;
// loop:
//     body-statement
//     update-expr;
//     if(test-expr) goto loop;
// done:

long fact_for_jm_goto(long n){
    long i = 2;
    long result = 1;
    goto test;
    loop:
        result *= i;
        i++;
    test:
        if(i < n) goto loop;
    return result;
}

long fact_for_gd_goto(long n){
    long i = 2;
    long result = 1;
    if(i >= n) goto done;
    loop:
        result *= i;
        i++;
        if(i < n) goto loop;
    done:
    return result;
}