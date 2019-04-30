type token =
  | SEMI
  | COL
  | SEMICOL
  | LPAREN
  | RPAREN
  | LBRACE
  | RBRACE
  | COMMA
  | PLUS
  | MINUS
  | TIMES
  | DIVIDE
  | ASSIGN
  | DOT
  | NOT
  | EQ
  | NEQ
  | LT
  | LEQ
  | GT
  | GEQ
  | AND
  | OR
  | RETURN
  | IF
  | ELSE
  | FOR
  | WHILE
  | INT
  | BOOL
  | FLOAT
  | VOID
  | STRING
  | IMAGE
  | CAPTION
  | ALBUM
  | ARR
  | PRESET
  | PIXEL
  | RED
  | GREEN
  | BLUE
  | LITERAL of (int)
  | BLIT of (bool)
  | STRLIT of (string)
  | ID of (string)
  | FLIT of (string)
  | EOF

val program :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Ast.program
