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
  | LITERAL of (int)
  | BLIT of (bool)
  | STRLIT of (string)
  | ID of (string)
  | FLIT of (string)
  | EOF

open Parsing;;
let _ = parse_error;;
# 4 "microcparse.mly"
open Ast
# 46 "microcparse.ml"
let yytransl_const = [|
  257 (* SEMI *);
  258 (* COL *);
  259 (* SEMICOL *);
  260 (* LPAREN *);
  261 (* RPAREN *);
  262 (* LBRACE *);
  263 (* RBRACE *);
  264 (* COMMA *);
  265 (* PLUS *);
  266 (* MINUS *);
  267 (* TIMES *);
  268 (* DIVIDE *);
  269 (* ASSIGN *);
  270 (* NOT *);
  271 (* EQ *);
  272 (* NEQ *);
  273 (* LT *);
  274 (* LEQ *);
  275 (* GT *);
  276 (* GEQ *);
  277 (* AND *);
  278 (* OR *);
  279 (* RETURN *);
  280 (* IF *);
  281 (* ELSE *);
  282 (* FOR *);
  283 (* WHILE *);
  284 (* INT *);
  285 (* BOOL *);
  286 (* FLOAT *);
  287 (* VOID *);
  288 (* STRING *);
    0 (* EOF *);
    0|]

let yytransl_block = [|
  289 (* LITERAL *);
  290 (* BLIT *);
  291 (* STRLIT *);
  292 (* ID *);
  293 (* FLIT *);
    0|]

let yylhs = "\255\255\
\001\000\002\000\002\000\002\000\004\000\006\000\006\000\009\000\
\009\000\005\000\005\000\005\000\005\000\005\000\007\000\007\000\
\003\000\008\000\008\000\010\000\010\000\010\000\010\000\010\000\
\010\000\010\000\010\000\012\000\012\000\011\000\011\000\011\000\
\011\000\011\000\011\000\011\000\011\000\011\000\011\000\011\000\
\011\000\011\000\011\000\011\000\011\000\011\000\011\000\011\000\
\011\000\011\000\011\000\011\000\013\000\013\000\014\000\014\000\
\000\000"

let yylen = "\002\000\
\002\000\000\000\002\000\002\000\013\000\000\000\001\000\002\000\
\004\000\001\000\001\000\001\000\001\000\001\000\000\000\002\000\
\003\000\000\000\002\000\002\000\003\000\002\000\005\000\007\000\
\011\000\011\000\007\000\000\000\001\000\001\000\001\000\001\000\
\001\000\001\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\003\000\003\000\003\000\003\000\002\000\002\000\
\003\000\004\000\003\000\004\000\000\000\001\000\001\000\003\000\
\002\000"

let yydefred = "\000\000\
\002\000\000\000\057\000\000\000\010\000\011\000\012\000\013\000\
\014\000\001\000\003\000\004\000\000\000\000\000\017\000\000\000\
\000\000\000\000\000\000\008\000\000\000\000\000\000\000\000\000\
\000\000\009\000\000\000\015\000\000\000\016\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\030\000\032\000\034\000\000\000\031\000\019\000\
\000\000\000\000\018\000\005\000\047\000\048\000\022\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\020\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\021\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\037\000\
\038\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\052\000\000\000\000\000\000\000\000\000\050\000\000\000\
\023\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\027\000\000\000\000\000\000\000\000\000\000\000\
\000\000\025\000\026\000"

let yydgoto = "\002\000\
\003\000\004\000\011\000\012\000\013\000\018\000\029\000\032\000\
\019\000\048\000\049\000\057\000\083\000\084\000"

let yysindex = "\015\000\
\000\000\000\000\000\000\001\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\240\254\046\255\000\000\212\255\
\242\254\024\255\040\255\000\000\051\255\212\255\056\255\025\255\
\059\255\000\000\083\255\000\000\212\255\000\000\065\255\045\255\
\086\255\157\255\096\255\099\255\157\255\157\255\009\255\100\255\
\105\255\119\255\000\000\000\000\000\000\002\255\000\000\000\000\
\238\255\176\000\000\000\000\000\000\000\000\000\000\000\226\000\
\125\255\157\255\157\255\157\255\157\255\157\255\000\000\157\255\
\157\255\157\255\157\255\157\255\157\255\157\255\157\255\157\255\
\157\255\157\255\157\255\129\255\079\255\000\000\194\000\128\255\
\212\000\226\000\130\255\126\255\226\000\000\255\000\255\000\000\
\000\000\009\001\009\001\064\255\064\255\064\255\064\255\253\000\
\240\000\000\000\135\255\136\255\157\255\137\255\000\000\157\255\
\000\000\139\255\158\000\142\255\226\000\123\255\157\255\123\255\
\138\255\143\255\000\000\160\255\162\255\164\255\168\255\123\255\
\123\255\000\000\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\167\255\
\000\000\000\000\173\255\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\084\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\165\255\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\061\255\
\000\000\000\000\176\255\000\000\183\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\138\000\000\000\000\000\000\000\000\000\
\000\000\087\255\000\000\184\255\055\255\194\255\216\255\000\000\
\000\000\099\000\108\000\004\000\033\000\055\000\077\000\130\000\
\005\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\091\255\000\000\191\255\000\000\
\118\255\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000"

let yygindex = "\000\000\
\000\000\000\000\169\000\000\000\248\255\000\000\000\000\149\000\
\000\000\153\255\222\255\199\255\000\000\000\000"

let yytablesize = 541
let yytable = "\050\000\
\010\000\080\000\053\000\054\000\056\000\061\000\113\000\017\000\
\115\000\055\000\066\000\067\000\034\000\024\000\062\000\001\000\
\122\000\123\000\037\000\014\000\031\000\020\000\038\000\079\000\
\056\000\081\000\082\000\085\000\021\000\086\000\087\000\088\000\
\089\000\090\000\091\000\092\000\093\000\094\000\095\000\096\000\
\097\000\043\000\044\000\045\000\046\000\047\000\015\000\022\000\
\034\000\016\000\035\000\036\000\023\000\114\000\037\000\049\000\
\025\000\049\000\038\000\049\000\026\000\029\000\049\000\029\000\
\027\000\029\000\107\000\039\000\040\000\109\000\041\000\042\000\
\064\000\065\000\066\000\067\000\056\000\043\000\044\000\045\000\
\046\000\047\000\034\000\028\000\035\000\099\000\015\000\018\000\
\037\000\018\000\018\000\055\000\038\000\018\000\055\000\056\000\
\051\000\018\000\056\000\052\000\033\000\039\000\040\000\058\000\
\041\000\042\000\018\000\018\000\059\000\018\000\018\000\043\000\
\044\000\045\000\046\000\047\000\018\000\018\000\018\000\018\000\
\018\000\024\000\060\000\024\000\024\000\078\000\034\000\024\000\
\035\000\098\000\101\000\024\000\037\000\104\000\103\000\105\000\
\038\000\106\000\108\000\110\000\024\000\024\000\112\000\024\000\
\024\000\039\000\040\000\117\000\041\000\042\000\024\000\024\000\
\024\000\024\000\024\000\043\000\044\000\045\000\046\000\047\000\
\034\000\118\000\116\000\119\000\120\000\033\000\037\000\033\000\
\121\000\033\000\038\000\006\000\033\000\033\000\033\000\033\000\
\033\000\007\000\028\000\033\000\033\000\033\000\033\000\033\000\
\033\000\033\000\033\000\053\000\054\000\043\000\044\000\045\000\
\046\000\047\000\035\000\028\000\035\000\030\000\035\000\077\000\
\000\000\035\000\035\000\035\000\000\000\000\000\000\000\000\000\
\035\000\035\000\035\000\035\000\035\000\035\000\035\000\035\000\
\036\000\000\000\036\000\000\000\036\000\000\000\000\000\036\000\
\036\000\036\000\000\000\000\000\000\000\000\000\036\000\036\000\
\036\000\036\000\036\000\036\000\036\000\036\000\063\000\005\000\
\006\000\007\000\008\000\009\000\000\000\000\000\064\000\065\000\
\066\000\067\000\000\000\000\000\068\000\069\000\070\000\071\000\
\072\000\073\000\074\000\075\000\041\000\046\000\041\000\046\000\
\041\000\046\000\000\000\041\000\046\000\000\000\000\000\000\000\
\000\000\000\000\041\000\041\000\041\000\041\000\041\000\041\000\
\041\000\041\000\046\000\000\000\005\000\006\000\007\000\008\000\
\009\000\042\000\000\000\042\000\000\000\042\000\000\000\000\000\
\042\000\000\000\000\000\000\000\000\000\000\000\000\000\042\000\
\042\000\042\000\042\000\042\000\042\000\042\000\042\000\043\000\
\000\000\043\000\000\000\043\000\000\000\000\000\043\000\000\000\
\000\000\000\000\000\000\000\000\000\000\043\000\043\000\043\000\
\043\000\043\000\043\000\043\000\043\000\044\000\000\000\044\000\
\000\000\044\000\000\000\000\000\044\000\000\000\000\000\000\000\
\000\000\000\000\000\000\044\000\044\000\044\000\044\000\044\000\
\044\000\044\000\044\000\039\000\000\000\039\000\000\000\039\000\
\000\000\000\000\039\000\000\000\040\000\000\000\040\000\000\000\
\040\000\039\000\039\000\040\000\000\000\000\000\000\000\039\000\
\039\000\000\000\040\000\040\000\000\000\000\000\000\000\000\000\
\040\000\040\000\045\000\000\000\045\000\000\000\045\000\000\000\
\000\000\045\000\000\000\000\000\051\000\000\000\051\000\000\000\
\000\000\051\000\051\000\051\000\051\000\051\000\045\000\045\000\
\051\000\051\000\051\000\051\000\051\000\051\000\051\000\051\000\
\111\000\000\000\000\000\000\000\000\000\000\000\064\000\065\000\
\066\000\067\000\000\000\000\000\068\000\069\000\070\000\071\000\
\072\000\073\000\074\000\075\000\076\000\000\000\000\000\000\000\
\064\000\065\000\066\000\067\000\000\000\000\000\068\000\069\000\
\070\000\071\000\072\000\073\000\074\000\075\000\100\000\000\000\
\000\000\000\000\064\000\065\000\066\000\067\000\000\000\000\000\
\068\000\069\000\070\000\071\000\072\000\073\000\074\000\075\000\
\102\000\000\000\000\000\000\000\064\000\065\000\066\000\067\000\
\000\000\000\000\068\000\069\000\070\000\071\000\072\000\073\000\
\074\000\075\000\064\000\065\000\066\000\067\000\000\000\000\000\
\068\000\069\000\070\000\071\000\072\000\073\000\074\000\075\000\
\064\000\065\000\066\000\067\000\000\000\000\000\068\000\069\000\
\070\000\071\000\072\000\073\000\074\000\064\000\065\000\066\000\
\067\000\000\000\000\000\068\000\069\000\070\000\071\000\072\000\
\073\000\064\000\065\000\066\000\067\000\000\000\000\000\000\000\
\000\000\070\000\071\000\072\000\073\000"

let yycheck = "\034\000\
\000\000\059\000\037\000\038\000\039\000\004\001\110\000\016\000\
\112\000\001\001\011\001\012\001\004\001\022\000\013\001\001\000\
\120\000\121\000\010\001\036\001\029\000\036\001\014\001\058\000\
\059\000\060\000\061\000\062\000\005\001\064\000\065\000\066\000\
\067\000\068\000\069\000\070\000\071\000\072\000\073\000\074\000\
\075\000\033\001\034\001\035\001\036\001\037\001\001\001\008\001\
\004\001\004\001\006\001\007\001\002\001\111\000\010\001\001\001\
\001\001\003\001\014\001\005\001\036\001\001\001\008\001\003\001\
\006\001\005\001\101\000\023\001\024\001\104\000\026\001\027\001\
\009\001\010\001\011\001\012\001\111\000\033\001\034\001\035\001\
\036\001\037\001\004\001\001\001\006\001\007\001\001\001\004\001\
\010\001\006\001\007\001\005\001\014\001\010\001\008\001\005\001\
\001\001\014\001\008\001\001\001\036\001\023\001\024\001\004\001\
\026\001\027\001\023\001\024\001\004\001\026\001\027\001\033\001\
\034\001\035\001\036\001\037\001\033\001\034\001\035\001\036\001\
\037\001\004\001\004\001\006\001\007\001\001\001\004\001\010\001\
\006\001\001\001\003\001\014\001\010\001\008\001\005\001\001\001\
\014\001\002\001\002\001\001\001\023\001\024\001\001\001\026\001\
\027\001\023\001\024\001\005\001\026\001\027\001\033\001\034\001\
\035\001\036\001\037\001\033\001\034\001\035\001\036\001\037\001\
\004\001\002\001\025\001\002\001\001\001\001\001\010\001\003\001\
\001\001\005\001\014\001\005\001\008\001\009\001\010\001\011\001\
\012\001\005\001\003\001\015\001\016\001\017\001\018\001\019\001\
\020\001\021\001\022\001\005\001\005\001\033\001\034\001\035\001\
\036\001\037\001\001\001\005\001\003\001\029\000\005\001\051\000\
\255\255\008\001\009\001\010\001\255\255\255\255\255\255\255\255\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\022\001\
\001\001\255\255\003\001\255\255\005\001\255\255\255\255\008\001\
\009\001\010\001\255\255\255\255\255\255\255\255\015\001\016\001\
\017\001\018\001\019\001\020\001\021\001\022\001\001\001\028\001\
\029\001\030\001\031\001\032\001\255\255\255\255\009\001\010\001\
\011\001\012\001\255\255\255\255\015\001\016\001\017\001\018\001\
\019\001\020\001\021\001\022\001\001\001\001\001\003\001\003\001\
\005\001\005\001\255\255\008\001\008\001\255\255\255\255\255\255\
\255\255\255\255\015\001\016\001\017\001\018\001\019\001\020\001\
\021\001\022\001\022\001\255\255\028\001\029\001\030\001\031\001\
\032\001\001\001\255\255\003\001\255\255\005\001\255\255\255\255\
\008\001\255\255\255\255\255\255\255\255\255\255\255\255\015\001\
\016\001\017\001\018\001\019\001\020\001\021\001\022\001\001\001\
\255\255\003\001\255\255\005\001\255\255\255\255\008\001\255\255\
\255\255\255\255\255\255\255\255\255\255\015\001\016\001\017\001\
\018\001\019\001\020\001\021\001\022\001\001\001\255\255\003\001\
\255\255\005\001\255\255\255\255\008\001\255\255\255\255\255\255\
\255\255\255\255\255\255\015\001\016\001\017\001\018\001\019\001\
\020\001\021\001\022\001\001\001\255\255\003\001\255\255\005\001\
\255\255\255\255\008\001\255\255\001\001\255\255\003\001\255\255\
\005\001\015\001\016\001\008\001\255\255\255\255\255\255\021\001\
\022\001\255\255\015\001\016\001\255\255\255\255\255\255\255\255\
\021\001\022\001\001\001\255\255\003\001\255\255\005\001\255\255\
\255\255\008\001\255\255\255\255\003\001\255\255\005\001\255\255\
\255\255\008\001\009\001\010\001\011\001\012\001\021\001\022\001\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\022\001\
\003\001\255\255\255\255\255\255\255\255\255\255\009\001\010\001\
\011\001\012\001\255\255\255\255\015\001\016\001\017\001\018\001\
\019\001\020\001\021\001\022\001\005\001\255\255\255\255\255\255\
\009\001\010\001\011\001\012\001\255\255\255\255\015\001\016\001\
\017\001\018\001\019\001\020\001\021\001\022\001\005\001\255\255\
\255\255\255\255\009\001\010\001\011\001\012\001\255\255\255\255\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\022\001\
\005\001\255\255\255\255\255\255\009\001\010\001\011\001\012\001\
\255\255\255\255\015\001\016\001\017\001\018\001\019\001\020\001\
\021\001\022\001\009\001\010\001\011\001\012\001\255\255\255\255\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\022\001\
\009\001\010\001\011\001\012\001\255\255\255\255\015\001\016\001\
\017\001\018\001\019\001\020\001\021\001\009\001\010\001\011\001\
\012\001\255\255\255\255\015\001\016\001\017\001\018\001\019\001\
\020\001\009\001\010\001\011\001\012\001\255\255\255\255\255\255\
\255\255\017\001\018\001\019\001\020\001"

let yynames_const = "\
  SEMI\000\
  COL\000\
  SEMICOL\000\
  LPAREN\000\
  RPAREN\000\
  LBRACE\000\
  RBRACE\000\
  COMMA\000\
  PLUS\000\
  MINUS\000\
  TIMES\000\
  DIVIDE\000\
  ASSIGN\000\
  NOT\000\
  EQ\000\
  NEQ\000\
  LT\000\
  LEQ\000\
  GT\000\
  GEQ\000\
  AND\000\
  OR\000\
  RETURN\000\
  IF\000\
  ELSE\000\
  FOR\000\
  WHILE\000\
  INT\000\
  BOOL\000\
  FLOAT\000\
  VOID\000\
  STRING\000\
  EOF\000\
  "

let yynames_block = "\
  LITERAL\000\
  BLIT\000\
  STRLIT\000\
  ID\000\
  FLIT\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decls) in
    Obj.repr(
# 33 "microcparse.mly"
            ( _1 )
# 365 "microcparse.ml"
               : Ast.program))
; (fun __caml_parser_env ->
    Obj.repr(
# 36 "microcparse.mly"
                 ( ([], [])               )
# 371 "microcparse.ml"
               : 'decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decls) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'vdecl) in
    Obj.repr(
# 37 "microcparse.mly"
               ( ((_2 :: fst _1), snd _1) )
# 379 "microcparse.ml"
               : 'decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decls) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'fdecl) in
    Obj.repr(
# 38 "microcparse.mly"
               ( (fst _1, (_2 :: snd _1)) )
# 387 "microcparse.ml"
               : 'decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 12 : 'typ) in
    let _2 = (Parsing.peek_val __caml_parser_env 11 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 9 : 'formals_opt) in
    let _10 = (Parsing.peek_val __caml_parser_env 3 : 'vdecl_list) in
    let _11 = (Parsing.peek_val __caml_parser_env 2 : 'stmt_list) in
    Obj.repr(
# 42 "microcparse.mly"
     ( { typ = _1;
	 fname = _2;
	 formals = List.rev _4;
	 locals = List.rev _10;
	 body = List.rev _11 } )
# 402 "microcparse.ml"
               : 'fdecl))
; (fun __caml_parser_env ->
    Obj.repr(
# 49 "microcparse.mly"
                  ( [] )
# 408 "microcparse.ml"
               : 'formals_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'formal_list) in
    Obj.repr(
# 50 "microcparse.mly"
                  ( _1 )
# 415 "microcparse.ml"
               : 'formals_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'typ) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 53 "microcparse.mly"
                             ( [(_1,_2)]     )
# 423 "microcparse.ml"
               : 'formal_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'formal_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'typ) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 54 "microcparse.mly"
                             ( (_3,_4) :: _1 )
# 432 "microcparse.ml"
               : 'formal_list))
; (fun __caml_parser_env ->
    Obj.repr(
# 57 "microcparse.mly"
          ( Int   )
# 438 "microcparse.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 58 "microcparse.mly"
          ( Bool  )
# 444 "microcparse.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 59 "microcparse.mly"
          ( Float )
# 450 "microcparse.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 60 "microcparse.mly"
          ( Void  )
# 456 "microcparse.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 61 "microcparse.mly"
           ( String )
# 462 "microcparse.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 64 "microcparse.mly"
                     ( [] )
# 468 "microcparse.ml"
               : 'vdecl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'vdecl_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'vdecl) in
    Obj.repr(
# 65 "microcparse.mly"
                     ( _2 :: _1 )
# 476 "microcparse.ml"
               : 'vdecl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'typ) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string) in
    Obj.repr(
# 68 "microcparse.mly"
               ( (_1, _2) )
# 484 "microcparse.ml"
               : 'vdecl))
; (fun __caml_parser_env ->
    Obj.repr(
# 71 "microcparse.mly"
                   ( [] )
# 490 "microcparse.ml"
               : 'stmt_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'stmt_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 72 "microcparse.mly"
                   ( _2 :: _1 )
# 498 "microcparse.ml"
               : 'stmt_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 75 "microcparse.mly"
                                            ( Expr _1               )
# 505 "microcparse.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr_opt) in
    Obj.repr(
# 76 "microcparse.mly"
                                            ( Return _2             )
# 512 "microcparse.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    Obj.repr(
# 77 "microcparse.mly"
                                            ( Return Noexpr         )
# 518 "microcparse.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'stmt_list) in
    Obj.repr(
# 78 "microcparse.mly"
                                            ( Block(List.rev _3)    )
# 525 "microcparse.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 79 "microcparse.mly"
                                                     ( If(_3, _7, Block([])) )
# 533 "microcparse.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 8 : 'expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 4 : 'stmt) in
    let _11 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 80 "microcparse.mly"
                                                             ( If(_3, _7, _11)        )
# 542 "microcparse.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 8 : 'expr_opt) in
    let _5 = (Parsing.peek_val __caml_parser_env 6 : 'expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 4 : 'expr_opt) in
    let _11 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 82 "microcparse.mly"
                                            ( For(_3, _5, _7, _11)   )
# 552 "microcparse.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 83 "microcparse.mly"
                                                     ( While(_3, _7)         )
# 560 "microcparse.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    Obj.repr(
# 87 "microcparse.mly"
                  ( Noexpr )
# 566 "microcparse.ml"
               : 'expr_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 88 "microcparse.mly"
                  ( _1 )
# 573 "microcparse.ml"
               : 'expr_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 91 "microcparse.mly"
                     ( Literal(_1)            )
# 580 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 92 "microcparse.mly"
              ( Fliteral(_1)           )
# 587 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : bool) in
    Obj.repr(
# 93 "microcparse.mly"
                     ( BoolLit(_1)            )
# 594 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 94 "microcparse.mly"
                     ( Id(_1)                 )
# 601 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 95 "microcparse.mly"
                     ( StrLit(_1)             )
# 608 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 96 "microcparse.mly"
                     ( Binop(_1, Add,   _3)   )
# 616 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 97 "microcparse.mly"
                     ( Binop(_1, Sub,   _3)   )
# 624 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 98 "microcparse.mly"
                     ( Binop(_1, Mult,  _3)   )
# 632 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 99 "microcparse.mly"
                     ( Binop(_1, Div,   _3)   )
# 640 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 100 "microcparse.mly"
                     ( Binop(_1, Equal, _3)   )
# 648 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 101 "microcparse.mly"
                     ( Binop(_1, Neq,   _3)   )
# 656 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 102 "microcparse.mly"
                     ( Binop(_1, Less,  _3)   )
# 664 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 103 "microcparse.mly"
                     ( Binop(_1, Leq,   _3)   )
# 672 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 104 "microcparse.mly"
                     ( Binop(_1, Greater, _3) )
# 680 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 105 "microcparse.mly"
                     ( Binop(_1, Geq,   _3)   )
# 688 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 106 "microcparse.mly"
                     ( Binop(_1, And,   _3)   )
# 696 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 107 "microcparse.mly"
                     ( Binop(_1, Or,    _3)   )
# 704 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 108 "microcparse.mly"
                         ( Unop(Neg, _2)      )
# 711 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 109 "microcparse.mly"
                     ( Unop(Not, _2)          )
# 718 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 110 "microcparse.mly"
                     ( Assign(_1, _3)         )
# 726 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'args_opt) in
    Obj.repr(
# 111 "microcparse.mly"
                              ( Call(_1, _3)  )
# 734 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 112 "microcparse.mly"
                       ( _2                   )
# 741 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    Obj.repr(
# 113 "microcparse.mly"
                            ( _2                   )
# 748 "microcparse.ml"
               : 'expr))
; (fun __caml_parser_env ->
    Obj.repr(
# 116 "microcparse.mly"
                  ( [] )
# 754 "microcparse.ml"
               : 'args_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'args_list) in
    Obj.repr(
# 117 "microcparse.mly"
               ( List.rev _1 )
# 761 "microcparse.ml"
               : 'args_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 120 "microcparse.mly"
                            ( [_1] )
# 768 "microcparse.ml"
               : 'args_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'args_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 121 "microcparse.mly"
                         ( _3 :: _1 )
# 776 "microcparse.ml"
               : 'args_list))
(* Entry program *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let program (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Ast.program)
