(* Ocamllex scanner for MicroC *)

{ open Microcparse }

let digit = ['0' - '9']
let digits = digit+

rule token = parse
  [' ' '\t' '\r'] { token lexbuf } (* Whitespace *)
| "/*"     { comment lexbuf }           (* Comments *)
| '('      { LPAREN }
| ')'      { RPAREN }
| '{'      { LBRACE }
| '}'      { RBRACE }
| ['\n']+      { SEMI }
| ','      { COMMA }
| ':'      { COL }
| ';'      { SEMICOL }
| '+'      { PLUS }
| '-'      { MINUS }
| '*'      { TIMES }
| '/'      { DIVIDE }
| '='      { ASSIGN }
| "=="     { EQ }
| "!="     { NEQ }
| '<'      { LT }
| "<="     { LEQ }
| ">"      { GT }
| ">="     { GEQ }
| "&&"     { AND }
| "||"     { OR }
| "!"      { NOT }
| "if"     { IF }
| "else"   { ELSE }
| "for"    { FOR }
| "while"  { WHILE }
| "return" { RETURN }
| "int"    { INT }
| "bool"   { BOOL }
| "float"  { FLOAT }
| "void"   { VOID }
| "string" { STRING }
| "true"   { BLIT(true)  }
| "false"  { BLIT(false) }
| "null"   { NULL }
| "import" { IMPORT }
| "save"   { SAVE }
| "in"     { IN }
| "arr"    { ARRAY }
| "Pixel"  { PIX }
| "Pixel.green" { PXGREEN }
| "Pixel.blue" { PXBLUE }
| "Pixel.red" { PXRED }
| "red"    { RED }
| "green"  { GREEN }
| "blue"   { BLUE }
| "Image"  { IMAGE }
| "Album"  { ALBUM }
| "Caption" { CAPT }
| "Gradient" { GRAD }
| digits as lxm { LITERAL(int_of_string lxm) }
| digits '.'  digit* ( ['e' 'E'] ['+' '-']? digits )? as lxm { FLIT(lxm) }
| ['a'-'z' 'A'-'Z']['a'-'z' 'A'-'Z' '0'-'9' '_']*     as lxm { ID(lxm) }
| ['"'](['a'-'z' 'A'-'Z' '0'-'9' '_' ' ']* as lxm)['"']  {STRLIT(lxm)}
| eof { EOF }
| _ as char { raise (Failure("illegal character " ^ Char.escaped char)) }

and comment = parse
  ['*']['/']['\n']* { token lexbuf }
| _    { comment lexbuf }