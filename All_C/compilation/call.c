long fibonacci(long n){
    if(n <= 2){
        return 1;
    }
    // before call, push the %rbp and %rbx into stack
    // because fibonacci uses this two to save n and fibonacci(n - 1) 
    return fibonacci(n - 1) + fibonacci(n - 2);

    // after called, restore %rbp and %rbx from stack 
}