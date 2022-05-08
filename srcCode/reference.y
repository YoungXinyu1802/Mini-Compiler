%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
int yylex();
int yyerror(char *s);
%}

%code requires {
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
} value_type;

typedef struct {
    value_type type;
    int integer_val;
    float float_val;
} value;


#define YYLTYPE value
#define YYSTYPE value
}

%token NUMBER

%%
command : exp1 {

}
;
exp1 : exp1 '\n' exp {
    if ($3.type == TYPE_INT) {
        printf("%d\n", $3.integer_val);
    } else {
        printf("%f\n", $3.float_val);
    }
}
| exp {
    if ($1.type == TYPE_INT) {
        printf("%d\n", $1.integer_val);
    } else {
        printf("%f\n", $1.float_val);
    }
};

exp : exp '+' term {
    if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.integer_val = $1.integer_val + $3.integer_val;
    } else if ($1.type == TYPE_FLOAT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val + $3.float_val;
    } else if ($1.type == TYPE_INT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.integer_val + $3.float_val;
    } else {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val + $3.integer_val;
    }
}
| exp '-' term{
    if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.integer_val = $1.integer_val - $3.integer_val;
    } else if ($1.type == TYPE_FLOAT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val - $3.float_val;
    } else if ($1.type == TYPE_INT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.integer_val - $3.float_val;
    } else {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val - $3.integer_val;
    }
}
| term {
    $$ = $1;
};

term : term '*' factor {
    if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.integer_val = $1.integer_val * $3.integer_val;
    } else if ($1.type == TYPE_FLOAT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val * $3.float_val;
    } else if ($1.type == TYPE_INT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.integer_val * $3.float_val;
    } else {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val * $3.integer_val;
    }
}
| term '/' factor{
    if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.integer_val = $1.integer_val / $3.integer_val;
    } else if ($1.type == TYPE_FLOAT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val / $3.float_val;
    } else if ($1.type == TYPE_INT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.integer_val / $3.float_val;
    } else {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val / $3.integer_val;
    }
}
| factor {
    $$ = $1;
};

factor : '-' numfactor {
    if ($2.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.integer_val = -$2.integer_val;
    } else {
        $$.type = TYPE_FLOAT;
        $$.float_val = -$2.float_val;
    }
}
| numfactor '^' numfactor {
    if ($1.type == TYPE_INT && $3.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.integer_val = pow($1.integer_val, $3.integer_val);
    } else if ($1.type == TYPE_FLOAT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = pow($1.float_val, $3.float_val);
    } else if ($1.type == TYPE_INT && $3.type == TYPE_FLOAT) {
        $$.type = TYPE_FLOAT;
        $$.float_val = pow($1.integer_val, $3.float_val);
    } else {
        $$.type = TYPE_FLOAT;
        $$.float_val = pow($1.float_val, $3.integer_val);
    }
}
| numfactor {
    if ($1.type == TYPE_INT) {
        $$.type = TYPE_INT;
        $$.integer_val = $1.integer_val;
    } else {
        $$.type = TYPE_FLOAT;
        $$.float_val = $1.float_val;
    }
};

numfactor : '(' exp ')' {
    $$ = $2;
}
| NUMBER {
    $$ = $1;
}

%%

int main() {
    return yyparse();
}

int yyerror(char *s){
    fprintf(stderr, "%s\n", s);
    return 0;
}