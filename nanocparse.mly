/* Ocamlyacc parser for NanoC */

%{
open Ast
%}

%token SEMI LPAREN RPAREN LBRACE RBRACE PLUS MINUS ASSIGN
%token EQ NEQ LT AND OR
%token IF ELSE WHILE INT BOOL
%token <int> LITERAL
%token <bool> BLIT
%token <string> ID
%token EOF

%start program
%type <Ast.program> program

%right ASSIGN
%left OR
%left AND
%left EQ NEQ
%left LT
%left PLUS MINUS

%%

program:
  vdecl_list stmt_list EOF { {locals=$1; body=$2} }

vdecl_list:
  /*nothing*/ { [] }
  | vdecl vdecl_list { $1 :: $2 }

vdecl:
  typ ID SEMI { ($1, $2) }

typ:
    INT   { Int   }
  | BOOL  { Bool  }

stmt_list:
  /*nothing*/ { [] }
  | stmt stmt_list { $1 :: $2 }

stmt:
    expr SEMI                               { Expr $1               }
  | LBRACE stmt_list RBRACE                 { Block $2    }
  | IF LPAREN expr RPAREN stmt ELSE stmt    { If ($3, $5, $7)        }
  | WHILE LPAREN expr RPAREN stmt           { While ($3, $5) }

expr:
    LITERAL          { Literal($1)            }
  | BLIT             { BoolLit($1)            }
  | ID               { Id($1)                 }
  | expr PLUS   expr { Binop($1, Add,   $3)   }
  | expr MINUS  expr { Binop($1, Sub,   $3)   }
  | expr EQ     expr { Binop($1, Equal, $3)   }
  | expr NEQ    expr { Binop($1, Neq, $3)     }
  | expr LT     expr { Binop($1, Less,  $3)   }
  | expr AND    expr { Binop($1, And,   $3)   }
  | expr OR     expr { Binop($1, Or,    $3)   }
  | ID ASSIGN expr   { Assign($1, $3)         }
  | LPAREN expr RPAREN { $2                   }
