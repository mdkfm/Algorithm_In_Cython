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

// format :
// while(test-expr){
//     loop-statement
// }

// goto simulation format:
// goto test;
// loop:
//     loop-statement
// test:
//     if(test-expr) goto loop;

// fast optimization:
// if(! test-expr) goto done;
// loop:
//     loop-statement;
//     if(test-expr) goto loop;
// done:
