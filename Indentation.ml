open Printf
open String

let indentatios filename = 
  let lines = ref [] in
  let chan = open_in filename in
  try
    while true; do
      lines := input_line chan :: !lines
    done; !lines
  with End_of_file ->
    close_in chan;
    List.rev !lines
    in 
    
    let level = 0 in
    let tabCount = 0 in
    let n = 0 in 
    if lines.(1).[n] = ['\t'] & then tabCount++
    if level > tabcount:
      append to striong \n } ] \n 
    if level < tabCount 
      append to strin \n { \n 
      
