#include<stdio.h>
#include<stdlib.h>

typedef struct Term{
    int coefficient;
    int degree;
    struct Term *next;
} Term;

Term * CreatePolynomial(int coefficients[], int degrees[], int length){
    // construct a LinkList, based on list
    // length the read length of list
    Term *L, *s; // L the head node, s tmp node
    L = (Term *) malloc(sizeof(Term));
    L->next = NULL;
    

    for (int i = length - 1; i >= 0; i --){
        s = (Term *) malloc(sizeof(Term));
        s->coefficient = coefficients[i];
        s->degree = degrees[i];
        s->next = L->next;
        L->next = s;
    }

    return L;
}

void AddTerm(Term * L, int coefficient, int degree){
    Term * s;
    s = (Term *) malloc(sizeof(Term));
    s->coefficient = coefficient;
    s->degree = degree;
    L->next = s;
}

void chain(Term *L, Term *chained){
    Term *s = chained, *p = L;
    while(s != NULL){
        AddTerm(p, s->coefficient, s->degree);
        p = p->next;
        s = s->next;
    }
}

void Display(Term *L){
    Term *p;
    p = L->next;
    printf("f(x) = ");
    while(p != NULL){
        printf("+ %d x**%d ", p->coefficient, p->degree);
        p = p->next;
    }
    printf("\n");
}

Term * PolynomialAdd(Term * A, Term * B){
    Term *C, *p1, *p2, *p;
    int coefficient, degree;
    C = (Term *) malloc(sizeof(Term));
    p = C;
    p1 = A->next;
    p2 = B->next;
   
    while(p1 !=NULL && p2 != NULL){
        // calculate the next term
        if(p1->degree == p2->degree){
            coefficient = p1->coefficient + p2->coefficient;
            degree = p1->degree;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->degree > p2->degree){
            coefficient = p2->coefficient;
            degree = p2->degree;
            p2 = p2->next;
        }
        else{
            coefficient = p1->coefficient;
            degree = p1->degree;
            p1 = p1->next;
        }
        
        AddTerm(p, coefficient, degree);
        p = p->next;
    }

    if(p1 != NULL){
        chain(p, p1);
    }

    if(p2 != NULL){
        chain(p, p2);
    }
    return C;
}

void main(){
    int a[] = {1, 2, 3}, b[] = {1, 2, 3}, c[] = {5, 6, 7};
    Term * f1, *f2, *result;
    f1 = CreatePolynomial(a, b, 3);
    f2 = CreatePolynomial(a, c, 3);
    Display(f1);
    Display(f2);
    result = PolynomialAdd(f1, f2);
    Display(result);
}