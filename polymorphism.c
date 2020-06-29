#include <stdio.h>
#include <malloc.h>
#include "polymorphism.h"

struct Virtual_table_tf vptr_tf= { NULL,dtor_TextFormatter };

void dtor_TextFormatter(void* tf)
{
}

void printFunc(const char* fname)
{
    printf("%-60s | ", fname);
}
//// DefaultTextFormatter Defs ////////////

Virtual_table_dtf vptr_dtf = {DefaultTextFormatter_print,dtor_DefaultTextFormatter};

void ctor_DefaultTextFormatter(DefaultTextFormatter* this)
{
    this->textFormatter.vptr = &vptr_dtf;
    this->id = next_id++;
    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->id);
}

void dtor_DefaultTextFormatter(void* this)
{
    ((DefaultTextFormatter*)this)->textFormatter.vptr = &vptr_tf;
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", ((DefaultTextFormatter*)this)->id);
    dtor_TextFormatter((DefaultTextFormatter*)this);
}

DefaultTextFormatter copyctor_DefaultTextFormatter(const DefaultTextFormatter* other)
{
    DefaultTextFormatter dtf;
    dtf.textFormatter.vptr = &vptr_dtf;
    dtf.id = next_id++;
    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->id, dtf.id);
    return dtf;
}

void assigment_DefaultTextFormatter(DefaultTextFormatter* dtf, const DefaultTextFormatter* other)
{
    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->id, dtf->id);
}

void DefaultTextFormatter_print(void* this,const char* const text)
{
    printf("%-60s | ","[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text );
}

DefaultTextFormatter* generateFormatterArray()
{
    DefaultTextFormatter* ptr = malloc(sizeof(DefaultTextFormatter[3]));
    for(int i=0;i<3; i++)
    {
        ctor_DefaultTextFormatter(&ptr[i]);
    }
    return ptr;
}

//// PrePostFixer Defs ////////////

Virtual_table_ppf vptr_ppf = {{PrePostFixer_print,dtor_PrePostFixer},print_slc};

void ctor_PrePostFixer(PrePostFixer * ppf, const char* prefix, const char* postfix)
{
    ctor_DefaultTextFormatter(&ppf->defaultTextFormatter);
    ppf->defaultTextFormatter.textFormatter.vptr = &vptr_ppf;
    ppf->pre = prefix;
    ppf->post = postfix;
    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", ppf->pre, ppf->post);
}

void dtor_PrePostFixer(void* this)
{
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostFixer*)this)->pre, ((PrePostFixer*)this)->post);
    dtor_DefaultTextFormatter(&((PrePostFixer*)this)->defaultTextFormatter);
}

void PrePostFixer_print(void* this, const char* text)
{
    printf("%-60s | ","[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", ((PrePostFixer*)this)->pre, text, ((PrePostFixer*)this)->post);
}
void (print_slc)(void* this,long num , char symbol)
{
        printFunc("[PrePostFixer::print(long, char)]");
        printf("-->\n");

        if (symbol)
            {
                printFunc("[PrePostFixer::print_num(long, char)]");
                printf("%s%c%ld%s\n", ((PrePostFixer*)this)->pre, symbol, num, ((PrePostFixer*)this)->post);
            }
        else
            {
                printFunc("[PrePostFixer::print_num(long)]");
                printf("%s%ld%s\n", ((PrePostFixer*)this)->pre,num,((PrePostFixer*)this)->post);
            }
}


// PrePostDollarFixer Defs ////////////

Virtual_table_ppdf vptr_ppdf = {{{PrePostFixer_print,dtor_PrePostDollarFixer},
                                        PrePostDollarFixer_print_slc}
                                };

void ctor_PrePostDollarFixer( PrePostDollarFixer* this,const char* prefix, const char* postfix)
{
    ctor_PrePostFixer(&this->prePostFixer,prefix, postfix);
    this->prePostFixer.defaultTextFormatter.textFormatter.vptr = &vptr_ppdf;
    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", this->prePostFixer.pre, this->prePostFixer.post);
}

struct PrePostDollarFixer copyctor_PrePostDollarFixer(const  PrePostDollarFixer* other)
{
    struct PrePostDollarFixer ppdf;
    ppdf.prePostFixer= other->prePostFixer;
    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", ppdf.prePostFixer.pre, ppdf.prePostFixer.post);
    return ppdf;
}

void dtor_PrePostDollarFixer(void* this)
{
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostDollarFixer*)this)->prePostFixer.pre,
            ((PrePostDollarFixer*)this)->prePostFixer.post);
    ((PrePostDollarFixer*)this)->prePostFixer.defaultTextFormatter.textFormatter.vptr = &vptr_ppf;
    dtor_PrePostFixer(&((PrePostDollarFixer*)this)->prePostFixer);
}

void PrePostDollarFixer_print_sic(void* this, int num, char symbol)
{
    printFunc("[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");
    ((Virtual_table_ppf*)(((PrePostDollarFixer*)this)->prePostFixer.defaultTextFormatter.
    textFormatter.vptr))->print_slc(this,(long)num, symbol);
}

void PrePostDollarFixer_print_slc(void* this,long num, char symbol)
{
    printFunc("[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");
    printFunc("[PrePostFixer::print(const char*)]");
    printFunc("[PrePostFixer::print_num(long, char)]");
    printf("%s%c%ld%s\n", ((PrePostDollarFixer*)this)->prePostFixer.pre,
            symbol, num, ((PrePostDollarFixer*)this)->prePostFixer.post);
}

void PrePostDollarFixer_print_sdc(void * this,double num, char symbol)
{
    printFunc("[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", ((PrePostDollarFixer*)this)->prePostFixer.pre,
            symbol, num, ((PrePostDollarFixer*)this)->prePostFixer.post);
}

//// PrePostHashFixer Defs ////////////

Virtual_table_pphf vptr_pphf = {{{{PrePostFixer_print,dtor_PrePostHashFixer},
                                        PrePostHashFixer_print_slc}}};


void ctor_PrePostHashFixer(PrePostHashFixer* this,int prc)
{
     ctor_PrePostDollarFixer(&this->prePostDollarFixer,"===> ", " <===");
     this->precision=prc;
     printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", this->prePostDollarFixer.prePostFixer.pre,this->prePostDollarFixer.prePostFixer.post, this->precision);
     this->prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = &vptr_pphf;
     printFunc("[PrePostHashFixer::print(double, char)]");
     printf("%s[%c%.*f]%s\n", this->prePostDollarFixer.prePostFixer.pre, DEFAULT_HASH_SYMBOL, this->precision, 9999.9999, this->prePostDollarFixer.prePostFixer.post);

}
void dtor_PrePostHashFixer(void* this)
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", ((PrePostHashFixer*)this)->prePostDollarFixer.prePostFixer.pre,((PrePostHashFixer*)this)->prePostDollarFixer.prePostFixer.post);
    ((PrePostHashFixer*)this)->prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = &vptr_ppdf;
    dtor_PrePostDollarFixer(&((PrePostHashFixer*)this)->prePostDollarFixer);
}
void PrePostHashFixer_print_sic(PrePostHashFixer* this,int num, char symbol)
{
    printFunc("[PrePostHashFixer::print(int, char)]");
    printf("-->\n");
    printFunc("[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", this->prePostDollarFixer.prePostFixer.pre, symbol, this->precision, (double)num, this->prePostDollarFixer.prePostFixer.post);

}
void PrePostHashFixer_print_slc(void* this,long num, char symbol)
{
    printFunc("[PrePostHashFixer::print(long, char)]");
    printf("-->\n");
    printFunc("[PrePostHashFixer::print(double, char)]");
    printf("%s[%c%.*f]%s\n", ((PrePostHashFixer*)this)->prePostDollarFixer.prePostFixer.pre, symbol, ((PrePostHashFixer*)this)->precision, (double)num, ((PrePostHashFixer*)this)->prePostDollarFixer.prePostFixer.post);
}

Virtual_table_ppfdf virtual_table_ppfdf = {{{{PrePostFixer_print,dtor_PrePostFloatDollarFixer},
                                                    PrePostDollarFixer_print_slc}}};

//// PrePostFloatDollarFixer Defs ////////////

void ctor_PrePostFloatDollarFixer(PrePostFloatDollarFixer * this,const char* prefix, const char* postfix)
{
    ctor_PrePostDollarFixer(&this->prePostDollarFixer,prefix, postfix);
    this->prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = &virtual_table_ppfdf;
    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", this->prePostDollarFixer.prePostFixer.pre, this->prePostDollarFixer.prePostFixer.post);

}
void dtor_PrePostFloatDollarFixer(void* this )
{
    ((PrePostFloatDollarFixer*)this)->prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr= &vptr_ppdf;
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n",((PrePostFloatDollarFixer*)this)->prePostDollarFixer.prePostFixer.pre, ((PrePostFloatDollarFixer*)this)->prePostDollarFixer.prePostFixer.post);
}
void print_PrePostFloatDollarFixer_fc(PrePostFloatDollarFixer* this,float num, char symbol)
{
    printFunc("[PrePostFloatDollarFixer::print(float, char)]");
    printf("%s%c%.2f%s\n", this->prePostDollarFixer.prePostFixer.pre, symbol, num, this->prePostDollarFixer.prePostFixer.post);
}
void print_PrePostFloatDollarFixer_f(PrePostFloatDollarFixer* this,float num)
{
    printFunc("[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");
    print_PrePostFloatDollarFixer_fc(this,num, '@');
}

//// PrePostChecker Defs ////////////

Virtual_table_ppc virtual_table_ppc = {{{{PrePostFixer_print,dtor_PrePostChecker},
                                                PrePostDollarFixer_print_slc}}};

void ctor_PrePostChecker(PrePostChecker* this)
{
    ctor_PrePostFloatDollarFixer(&this->prePostFloatDollarFixer,"[[[[ ", " ]]]]");
    this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = &virtual_table_ppc;
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.pre, this->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.post);
}

void dtor_PrePostChecker(void * this)
{
    ((PrePostChecker*)this)->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.defaultTextFormatter.textFormatter.vptr = &virtual_table_ppfdf;
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", ((PrePostChecker*)this)->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.pre, ((PrePostChecker*)this)->prePostFloatDollarFixer.prePostDollarFixer.prePostFixer.post);
    dtor_PrePostFloatDollarFixer(&((PrePostChecker*)this)->prePostFloatDollarFixer);
}

void PrePostChecker_printThisSymbolUsingFunc()
{
    printFunc("[PrePostChecker::printThisSymbolUsingFunc()]");
    printf("Default symbol is %c\n", DEFAULT_FLOAT_SYMBOL);
}

void PrePostChecker_printThisSymbolDirectly()
{
    printFunc("[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", DEFAULT_FLOAT_SYMBOL);
}

void PrePostChecker_printDollarSymbolByCastUsingFunc()
{
    printFunc("[PrePostChecker::printDollarSymbolByCastUsingFunc()]");

    printf("Default symbol is %c\n", DEFAULT_DOLLAR_SYMBOL);
}

void PrePostChecker_printDollarSymbolByScopeUsingFunc()
{
    printFunc("[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", DEFAULT_DOLLAR_SYMBOL);
}

void PrePostChecker_printDollarSymbolByCastDirectly()
{
    printFunc("[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", DEFAULT_FLOAT_SYMBOL);
}

void PrePostChecker_printDollarSymbolByScopeDirectly()
{
    printFunc("[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", DEFAULT_DOLLAR_SYMBOL);
}

//// Multiplier Defs ////////////

Virtual_table_m  virtual_table_m ={print_Multiplier,dtor_Multiplier};

void print_Multiplier(void* this,const char* text)
{
    printFunc("[Multiplier::print(const char*)]");

    for (int i = 0; i < ((Multiplier*)this)->times; ++i)
        printf("%s", text);
    printf("\n");
}
void dtor_Multiplier(void* this)
{
    printf("--- Multiplier DTOR: times = %d\n", ((Multiplier*)this)->times);
}