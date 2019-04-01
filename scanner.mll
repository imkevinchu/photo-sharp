{ open Parser }

rule token = 
  parse [' ' '\t' '\r' '\n'] {token lexbuf}
  | "print "                  { PRINT }
  | ['a'-'z']+ as id         { LITERAL(id) }
  | eof                      { EOF } 
  