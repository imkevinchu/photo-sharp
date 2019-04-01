open Ast
let rec print exp str= 
  match exp with
  Lit ( x ) -> x
let _ =
let lexbuf = Lexing.from_channel stdin in
let expr = Parser.expr Scanner.token lexbuf in
print_endline( expr )