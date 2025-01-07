/* Explore manually implementing a object vtables and dynamic dispatch 
 * Entries of a vtable for the same object have the same offset.
 *
 * Assuming B inherits from A and overrides virtual_fn_b
 * */

#include <stdio.h>
#include <stdlib.h>

#define VTABLE_SIZE 10

typedef void (*(*vtable_ptr)[VTABLE_SIZE])();

void a();
void b();
void c();

struct A* a_constructor();
void (* a_vtable[VTABLE_SIZE])() = {
    a,
    b
};

struct B* b_constructor();
void (* b_vtable[VTABLE_SIZE])() = {
    a,
    c
};

struct A {
    vtable_ptr vtable;
    void (*virtual_fn_a)(); 
    void (*virtual_fn_b)(); 
};

struct B {
    vtable_ptr vtable;
    void (*virtual_fn_a)(); 
    void (*virtual_fn_b)(); 
};

int main(int argc, char *argv[])
{
    struct A* a = (struct A*) a_constructor();
    struct B* b = (struct B*) b_constructor(); 
    a->virtual_fn_a();
    b->virtual_fn_a();
    a->virtual_fn_b();
    b->virtual_fn_b();
    return EXIT_SUCCESS;
}

/* return a pointer to an struct of type A */
struct A* a_constructor() {
    struct A* p = (struct A*) malloc(sizeof(struct A));
    p->vtable = &a_vtable;
    p->virtual_fn_a = (*(p->vtable))[0];
    p->virtual_fn_b = (*(p->vtable))[1];
    return p;
}

/* return a pointer to an struct of type B */
struct B* b_constructor() {
    struct B* p = (struct B *) a_constructor();
    p->vtable = &b_vtable;
    p->virtual_fn_a = (*(p->vtable))[0];
    p->virtual_fn_b = (*(p->vtable))[1];
    return p;
}

void a() {
    printf("a\n");
}

void b() {
    printf("b\n");
}

void c() {
    printf("c\n");
}
