#include <malloc.h>
#include <stdio.h>
#include "polymorphism.h"

extern Virtual_table_m virtual_table_m;
extern Virtual_table_dtf vptr_dtf;

void doFormatterDynamicArray()
{
    printf("\n--- start doFormatterDynamicArray() ---\n\n");

    DefaultTextFormatter* formatters = generateFormatterArray();

    for (int i = 0; i < 3; ++i)
        ((Virtual_table_tf*)formatters[i].textFormatter.vptr)->print(&formatters[i],"Hello World!");



    printf("\n--- end doFormatterDynamicArray() ---\n\n");
    for (int i = 0; i < 3; ++i)
        ((Virtual_table_tf*)formatters[i].textFormatter.vptr)->dtor(&formatters[i]);
    free(formatters) ;
}

void doPrePostFixer()
{
    printf("\n--- start doPrePostFixer() ---\n\n");

    struct PrePostFixer angleBrackets;
    ctor_PrePostFixer(&angleBrackets,"<<< ", " >>>");
    ((Virtual_table_tf*) angleBrackets.defaultTextFormatter.textFormatter.vptr)->print(&angleBrackets,"Hello World!");
    ((Virtual_table_ppf*) angleBrackets.defaultTextFormatter.textFormatter.vptr)->print_slc(&angleBrackets,-777,'\0');
    ((Virtual_table_ppf*) angleBrackets.defaultTextFormatter.textFormatter.vptr)->print_slc(&angleBrackets,350,'#');
    ((Virtual_table_ppf*) angleBrackets.defaultTextFormatter.textFormatter.vptr)->print_slc(&angleBrackets,3.14,'\0');

    printf("\n--- end doPrePostFixer() ---\n\n");
    dtor_PrePostFixer(&angleBrackets);
}

void doPrePostDollarFixer()
{
    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    PrePostDollarFixer asterisks;
    ctor_PrePostDollarFixer(&asterisks,"***** ", " *****");
    PrePostDollarFixer_print_sic(&asterisks,-777,'$');
    PrePostDollarFixer_print_sic(&asterisks,350, '#');
    PrePostDollarFixer_print_sdc(&asterisks,3.14f,'$');

    printf("\n--- end doPrePostDollarFixer() ---\n\n");
    dtor_PrePostDollarFixer(&asterisks);
}

void runAsPrePostFixerRef(PrePostFixer* pp)
{
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    ((Virtual_table_ppf*)pp->defaultTextFormatter.textFormatter.vptr)->print_slc(pp,123,'\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(PrePostDollarFixer* pp)
{
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");

    ((Virtual_table_ppf*)(pp->prePostFixer.defaultTextFormatter.textFormatter.vptr))->print_slc(pp,123,'$');

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(PrePostDollarFixer pp)
{
    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");

    ((Virtual_table_ppf*)(pp.prePostFixer.defaultTextFormatter.textFormatter.vptr))->print_slc(&pp,123,'$');
    dtor_PrePostDollarFixer(&pp);

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");
}

void runAsPrePostHashFixerRef(PrePostHashFixer* pp)
{
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");
    ((Virtual_table_ppf*)(pp->prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr))->print_slc(pp,123,'#');

printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

void doPrePostFloatDollarFixer()
{
    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostFloatDollarFixer hashes;
    ctor_PrePostFloatDollarFixer(&hashes,"### ", " ###");
    print_PrePostFloatDollarFixer_f(&hashes,-777);
    print_PrePostFloatDollarFixer_fc(&hashes,350, '#');
    print_PrePostFloatDollarFixer_f(&hashes,3.14f);

    PrePostDollarFixer hashes2;
    hashes2 = copyctor_PrePostDollarFixer(&hashes.prePostDollarFixer);
    PrePostDollarFixer_print_sdc(&hashes2,7.5,'$');
    PrePostDollarFixer_print_sic(&hashes2,100,'$');

    printf("\n--- end doPrePostFloatDollarFixer() ---\n\n");
    dtor_PrePostDollarFixer(&hashes);
    dtor_PrePostFixer(&hashes2);

}

void doPrePostChecker()
{
    printf("\n--- start doPrePostChecker() ---\n\n");

    PrePostChecker check;
    ctor_PrePostChecker(&check);
    PrePostChecker_printThisSymbolUsingFunc();
    PrePostChecker_printThisSymbolDirectly();
    PrePostChecker_printDollarSymbolByCastUsingFunc();
    PrePostChecker_printDollarSymbolByScopeUsingFunc();
    PrePostChecker_printDollarSymbolByCastDirectly();
    PrePostChecker_printDollarSymbolByScopeDirectly();

    printf("\n--- end doPrePostChecker() ---\n\n");
    dtor_PrePostChecker(&check);
}

void doMultiplier()
{
    printf("\n--- start doMultiplier() ---\n\n");

    Multiplier m1;
    m1.times = 3;
    printf("--- Multiplier CTOR: times = %d\n", m1.times);
    ctor_DefaultTextFormatter(&m1.defaultTextFormatter);
    m1.defaultTextFormatter.textFormatter.vptr= &virtual_table_m;

    Multiplier m2;
    ctor_DefaultTextFormatter(&m2.defaultTextFormatter);
    m2.times = 5;
    printf("--- Multiplier CTOR: times = %d\n", m2.times);
    m2.defaultTextFormatter.textFormatter.vptr= &virtual_table_m;

    Multiplier m3;
    m3.defaultTextFormatter = copyctor_DefaultTextFormatter(&m1.defaultTextFormatter);
    m3.times= m1.times;
    m3.defaultTextFormatter.textFormatter.vptr= &virtual_table_m;

    Multiplier m4;
    m4.defaultTextFormatter = copyctor_DefaultTextFormatter(&m2.defaultTextFormatter);
    m4.times= m2.times;
    m4.defaultTextFormatter.textFormatter.vptr= &virtual_table_m;

    ((Virtual_table_tf*)(m1.defaultTextFormatter.textFormatter.vptr))->print(&m1,"abc ");
    ((Virtual_table_tf*)(m2.defaultTextFormatter.textFormatter.vptr))->print(&m2,"abc ");
    ((Virtual_table_tf*)(m3.defaultTextFormatter.textFormatter.vptr))->print(&m3,"abc ");
    ((Virtual_table_tf*)(m4.defaultTextFormatter.textFormatter.vptr))->print(&m4,"abc ");

    printf("\n--- end doMultiplier() ---\n\n");
    printf("--- Multiplier DTOR: times = %d\n", m1.times);
    m1.defaultTextFormatter.textFormatter.vptr = &vptr_dtf;
    dtor_DefaultTextFormatter(&m1.defaultTextFormatter);
    printf("--- Multiplier DTOR: times = %d\n", m2.times);
    m2.defaultTextFormatter.textFormatter.vptr = &vptr_dtf;
    dtor_DefaultTextFormatter(&m2.defaultTextFormatter);
    printf("--- Multiplier DTOR: times = %d\n", m3.times);
    m3.defaultTextFormatter.textFormatter.vptr = &vptr_dtf;
    dtor_DefaultTextFormatter(&m3.defaultTextFormatter);
    printf("--- Multiplier DTOR: times = %d\n", m4.times);
    m4.defaultTextFormatter.textFormatter.vptr = &vptr_dtf;
    dtor_DefaultTextFormatter(&m4.defaultTextFormatter);

}
void doFormatterArray()
{
    printf("\n--- start doFormatterArray() ---\n\n");

    DefaultTextFormatter formatters[3];

    PrePostDollarFixer ppdf;
    ctor_PrePostDollarFixer(&ppdf,"!!! ", " !!!");
    formatters[0]= copyctor_DefaultTextFormatter(&ppdf.prePostFixer.defaultTextFormatter);
    dtor_PrePostDollarFixer(&ppdf);

    Multiplier m;;
    m.times = 4;
    printf("--- Multiplier CTOR: times = %d\n", m.times);
    ctor_DefaultTextFormatter(&m.defaultTextFormatter);
    m.defaultTextFormatter.textFormatter.vptr= &virtual_table_m;
    formatters[1]=copyctor_DefaultTextFormatter(&m.defaultTextFormatter);
    dtor_Multiplier(&m);

    PrePostChecker ppc;
    ctor_PrePostChecker(&ppc);
    formatters[2] = copyctor_DefaultTextFormatter(&ppc.prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.defaultTextFormatter);
    dtor_PrePostChecker(&ppc);

    for (int i = 0; i < 3; ++i)
        ((Virtual_table_tf*)formatters[i].textFormatter.vptr)->print(&formatters[i],"Hello World!");

    printf("\n--- end doFormatterArray() ---\n\n");

    for (int i = 0; i < 3; ++i)
        ((Virtual_table_tf*)formatters[i].textFormatter.vptr)->dtor(&formatters[i]);
}
void doFormatterPtrs()
{
    printf("\n--- start doFormatterPtrs() ---\n\n");

    DefaultTextFormatter* pfmt[3];
    PrePostDollarFixer* ptr1= (PrePostDollarFixer*)malloc(sizeof(PrePostDollarFixer));
    PrePostDollarFixer ppdf;
    ctor_PrePostDollarFixer(&ppdf,"!!! ", " !!!");
    ptr1=&ppdf;
//    pfmt[0]=ptr1->prePostFixer.defaultTextFormatter;
//            {
//
//            new Multiplier(4),
//            new PrePostChecker()
//            };
//
//    for (int i = 0; i < 3; ++i)
//        pfmt[i]->print("Hello World!");
//
//    for (int i = 2; i >= 0; --i)
//        delete pfmt[i];

    printf("\n--- end doFormatterPtrs() ---\n\n");
}

int main()
{
    printf("\n--- Start main() ---\n\n");
    doPrePostChecker();
    doFormatterDynamicArray();
    doPrePostFixer();
    doPrePostDollarFixer();
    PrePostHashFixer hfix;
    ctor_PrePostHashFixer(&hfix,4);
    runAsPrePostFixerRef((PrePostFixer *)&hfix);
    runAsPrePostDollarFixerRef((PrePostDollarFixer *) &hfix);
    PrePostDollarFixer p =copyctor_PrePostDollarFixer(&hfix);
    runAsPrePostDollarFixerObj(p);
    runAsPrePostHashFixerRef(&hfix);
    doPrePostFloatDollarFixer();
    doMultiplier();
    doFormatterArray();
    //doFormatterPtrs();
    printf("\n--- End main() ---\n\n");
    dtor_PrePostHashFixer(&hfix);
    return 0;
}