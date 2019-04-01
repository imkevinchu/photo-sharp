%{ open Ast %}
%token PRINT
%token <string> LITERAL

%start expr
%type <Ast.expr> expr %%

expr:
expr PLUS expr { Binop ( $1 , Add, $3 ) }
| LITERAL { Lit ( $1 ) }
