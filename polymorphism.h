#ifndef __POLYMORPHISM_H__
#define __POLYMORPHISM_H__
#define DEFAULT_SYMBOL '\0'
#define DEFAULT_DOLLAR_SYMBOL '$'
#define DEFAULT_HASH_SYMBOL '#'
#define DEFAULT_FLOAT_SYMBOL '@'


///// VIRTUAL TABLE ////////////

typedef struct Virtual_table_tf{
    void (*print)(void*, const char* const);
    void (*dtor)(void* dtf);
}Virtual_table_tf;

//// TextFormatter ////////////

typedef struct TextFormatter
{
    void* vptr;

}TextFormatter;

void dtor_TextFormatter(void* tf);

///// VIRTUAL TABLE ////////////

typedef struct Virtual_table_dtf{
    Virtual_table_tf virtual_table_tf;
} Virtual_table_dtf;


//// DefaultTextFormatter ////////////

static int next_id;

typedef struct DefaultTextFormatter{
     TextFormatter textFormatter;
    int id;
}DefaultTextFormatter;

void DefaultTextFormatter_print(void*, const char* const text);
void ctor_DefaultTextFormatter(DefaultTextFormatter* tf);
void dtor_DefaultTextFormatter(void* dtf);
void assigment_DefaultTextFormatter(DefaultTextFormatter* dtf, const DefaultTextFormatter* other);
DefaultTextFormatter* generateFormatterArray();
DefaultTextFormatter copyctor_DefaultTextFormatter(const DefaultTextFormatter* other);


//// PrePostFixer ////////////

///// VIRTUAL TABLE ////////////

typedef struct Virtual_table_ppf{
    Virtual_table_dtf virtual_table_dtf;
    void (*print_slc)(void*,long, char);
    char (*getDefaultSymbol_s)(void*);
} Virtual_table_ppf;

typedef struct PrePostFixer
{
    DefaultTextFormatter defaultTextFormatter;
    const char* pre;
    const char* post;
}PrePostFixer;

void ctor_PrePostFixer(PrePostFixer * ppf, const char* prefix, const char* postfix);
void dtor_PrePostFixer(void* ppf);
void PrePostFixer_print(void* ppf, const char* text);
void (print_slc)(void*,long, char);
char (getDefaultSymbol_s)(void*);

////// PrePostDollarFixer ////////////


///// VIRTUAL TABLE ////////////

typedef struct Virtual_table_ppdf{
    Virtual_table_ppf virtual_table_ppf;
} Virtual_table_ppdf;

typedef struct PrePostDollarFixer
{
    struct PrePostFixer prePostFixer;
}PrePostDollarFixer;

PrePostDollarFixer copyctor_PrePostDollarFixer(const PrePostDollarFixer* other);
void dtor_PrePostDollarFixer(void* ppdf);
void PrePostDollarFixer_print_sic(void* ppdf, int num, char symbol);
void PrePostDollarFixer_print_slc(void* ppdf,long num, char symbol);
void PrePostDollarFixer_print_sdc(void* ppdf,double num, char symbol);
void ctor_PrePostDollarFixer(struct PrePostDollarFixer* ppdf,const char* prefix, const char* postfix);

/// PrePostHashFixer ////////////

typedef struct Virtual_table_pphf{
    Virtual_table_ppdf virtual_table_ppdf;
} Virtual_table_pphf;


typedef struct PrePostHashFixer{
     PrePostDollarFixer prePostDollarFixer;
     int precision;
}PrePostHashFixer;

void ctor_PrePostHashFixer(PrePostHashFixer*,int prc);
void dtor_PrePostHashFixer(void*);
void PrePostHashFixer_print_sic(PrePostHashFixer*,int num, char symbol);
void PrePostHashFixer_print_slc(void*,long num, char symbol) ;

//// PrePostFloatDollarFixer ////////////


///// VIRTUAL TABLE ////////////

typedef struct Virtual_table_ppfdf{
    Virtual_table_ppdf virtual_table_ppdf;
} Virtual_table_ppfdf;

typedef struct PrePostFloatDollarFixer{
    PrePostDollarFixer prePostDollarFixer;
}PrePostFloatDollarFixer;

//// PrePostFloatDollarFixer Defs ////////////

void ctor_PrePostFloatDollarFixer(PrePostFloatDollarFixer *,const char* prefix, const char* postfix);
void dtor_PrePostFloatDollarFixer(void*);
void print_PrePostFloatDollarFixer_fc(PrePostFloatDollarFixer* this,float num, char symbol);
void print_PrePostFloatDollarFixer_f(PrePostFloatDollarFixer* this,float num);

//// PrePostChecker ////////////


///// VIRTUAL TABLE ////////////

typedef struct Virtual_table_ppc{
    Virtual_table_ppdf virtual_table_ppdf;
} Virtual_table_ppc;


typedef struct PrePostChecker{
    PrePostFloatDollarFixer prePostFloatDollarFixer;
}PrePostChecker;

void ctor_PrePostChecker(PrePostChecker* this);
void dtor_PrePostChecker(void* this);
void PrePostChecker_printThisSymbolUsingFunc();
void PrePostChecker_printThisSymbolDirectly();
void PrePostChecker_printDollarSymbolByCastUsingFunc();
void PrePostChecker_printDollarSymbolByScopeUsingFunc();
void PrePostChecker_printDollarSymbolByCastDirectly();
void PrePostChecker_printDollarSymbolByScopeDirectly();

//// Multiplier ////////////

typedef struct Virtual_table_m{
    Virtual_table_dtf virtual_table_dtf;
} Virtual_table_m;

typedef struct Multiplier {
    DefaultTextFormatter defaultTextFormatter;
    int times;
}Multiplier;

void print_Multiplier(void* this,const char* text);
void dtor_Multiplier(void* this);
#endif