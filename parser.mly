/* Ocamlyacc parser for MicroC */

%{
open Ast
%}

%token DOT SEMI COL SEMICOL LPAREN RPAREN LBRACE RBRACE COMMA PLUS MINUS TIMES DIVIDE ASSIGN PIXKEY IN 
%token NOT EQ NEQ LT LEQ GT GEQ AND OR
%token RETURN IF ELSE FOR WHILE INT BOOL FLOAT VOID STRING IMAGE CAPTION ALBUM ARR PRESET PIXEL 
%token <int> LITERAL
%token <bool> BLIT
%token <string> STRLIT
%token <string> ID FLIT
%token EOF

%start program
%type <Ast.program> program

%nonassoc NOELSE
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left EQ NEQ
%left LT GT LEQ GEQ
%left PLUS MINUS
%left TIMES DIVIDE
%right NOT

%%

program:
  decls EOF { $1 }

decls:
   /* nothing */ { ([], [])               }
 | decls vdecl { (($2 :: fst $1), snd $1) }
 | decls fdecl { (fst $1, ($2 :: snd $1)) }

fdecl:
  PRESET typ ID LPAREN formals_opt RPAREN COL SEMI LBRACE SEMI vdecl_list stmt_list RBRACE SEMI
     { { typ = $2;
	 fname = $3;
	 formals = List.rev $5;
	 locals = List.rev $11;
	 body = List.rev $12 } }

formals_opt:
    /* nothing */ { [] }
  | formal_list   { $1 }

formal_list:
    typ ID                   { [($1,$2)]     }
  | formal_list COMMA typ ID { ($3,$4) :: $1 }

typ:
    INT   { Int   }
  | BOOL  { Bool  }
  | FLOAT { Float }
  | VOID  { Void  }
  | STRING { String }
  | IMAGE  { Image }
  | CAPTION { Caption }
  | ALBUM { Album }
  | ARR { Array }
  | PIXEL { Pixel }

vdecl_list:
    /* nothing */    { [] }
  | vdecl_list vdecl { $2 :: $1 }

vdecl:
   typ ID SEMI { ($1, $2) }

stmt_list:
    /* nothing */  { [] }
  | stmt_list stmt { $2 :: $1 }

stmt:
    expr SEMI                               { Expr $1               }
  | RETURN expr_opt SEMI                    { Return $2             }
  | RETURN SEMI                             { Return Noexpr         }
  | LBRACE SEMI stmt_list RBRACE SEMI       { Block(List.rev $3)    }
  | IF LPAREN expr RPAREN COL SEMI stmt %prec NOELSE { If($3, $7, Block([])) }
  | IF LPAREN expr RPAREN COL SEMI stmt ELSE COL SEMI stmt   { If($3, $7, $11)        }
  | FOR LPAREN expr_opt SEMICOL expr SEMICOL expr_opt RPAREN COL SEMI stmt
                                            { For($3, $5, $7, $11)   }
  | WHILE LPAREN expr RPAREN COL SEMI stmt           { While($3, $7)         }
  | FOR ID IN expr COL SEMI stmt           { EFor($2, $4, $7)          }


expr_opt:
    /* nothing */ { Noexpr }
  | expr          { $1 }

expr:
    LITERAL          { Literal($1)            }
  | FLIT	     { Fliteral($1)           }
  | BLIT             { BoolLit($1)            }
  | ID               { Id($1)                 }
  | STRLIT           { StrLit($1)             }
  | LPAREN expr COMMA expr COMMA expr COMMA expr RPAREN { PixelLit($2, $4, $6, $8) }
  | expr PLUS   expr { Binop($1, Add,   $3)   }
  | expr MINUS  expr { Binop($1, Sub,   $3)   }
  | expr TIMES  expr { Binop($1, Mult,  $3)   }
  | expr DIVIDE expr { Binop($1, Div,   $3)   }
  | expr EQ     expr { Binop($1, Equal, $3)   }
  | expr NEQ    expr { Binop($1, Neq,   $3)   }
  | expr LT     expr { Binop($1, Less,  $3)   }
  | expr LEQ    expr { Binop($1, Leq,   $3)   }
  | expr GT     expr { Binop($1, Greater, $3) }
  | expr GEQ    expr { Binop($1, Geq,   $3)   }
  | expr AND    expr { Binop($1, And,   $3)   }
  | expr OR     expr { Binop($1, Or,    $3)   }
  | MINUS expr %prec NOT { Unop(Neg, $2)      }
  | NOT expr         { Unop(Not, $2)          }
  | ID ASSIGN expr   { Assign($1, $3)         }
  | expr DOT ID LPAREN args_opt RPAREN { Call($3, $1 :: $5) }
  | ID LPAREN args_opt RPAREN { Call($1, $3)  }
  | LPAREN expr RPAREN { $2                   }
  | LPAREN expr RPAREN SEMI { $2                   }

args_opt:
    /* nothing */ { [] }
  | args_list  { List.rev $1 }

args_list:
    expr                    { [$1] }
  | args_list COMMA expr { $3 :: $1 }
