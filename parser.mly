%{ open Ast %}

%token QUOTE PRINT
%token <string> LITERAL

%start expr
%type <Ast.expr> expr %%

expr:
QUOTE expr QUOTE { quote }
| LITERAL { Lit ( $1 ) }
