

(* Ocamllex scanner for NanoC *)

{ open Nanocparse }

let digit = ['0'-'9'] (* in *)
let letter = ['a'-'z' 'A'-'Z'] (* in *)


rule token = parse
  [' ' '\t' '\r' '\n'] { token lexbuf } (* Whitespace.. Lexbuf is the rest of the input buffer *)
| "/*"     { comment lexbuf }           (* Comments *)
| '('      { LPAREN }
| ')'      { RPAREN }
| '{'      { LBRACE }
| '}'      { RBRACE }
| ';'      { SEMI }
| '+'      { PLUS }
| '-'      { MINUS }
| '='      { ASSIGN }
| '"'      { QUOTE }
| "=="     { EQ }
| "!="     { NEQ }
| '<'      { LT }
| "&&"     { AND }
| "||"     { OR }
| "if"     { IF }
| "else"   { ELSE }
| "while"  { WHILE }
| "int"    { INT }
| "bool"   { BOOL }
| "true"   { BLIT(true)  }
| "false"  { BLIT(false) }
| "print"  { PRINT }
| digit+ as lxm  { LITERAL(int_of_string lxm)}
| letter  as lxm { ID(lxm) }
| ['\"'] (letter | digit | '_')* ['\"']  as lxm { STRLIT(String.sub (lxm) 1 (String.length (lxm) -2)) }
| eof { EOF }
| _ as char { raise (Failure("illegal character " ^ Char.escaped char)) }

and comment = parse
  "*/" { token lexbuf }
| _    { comment lexbuf }
