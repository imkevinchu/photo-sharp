open Printf
open String
open List
 
let indentations filename = 
  let lines = ref [] in
  let channel = open_in filename in
  try
    while true; do
      lines := input_line channel :: !lines
    done; !lines
  with End_of_file ->
    close_in channel;
    List.rev !lines
    in 
    
    let level = 0 in
    let tabCount = 0 in
    let n = 0 in
    let previous = ref 0 in 

    let f inputString =
      if inputString.[n] = ['\t'] & tabCount != 0 then incr tabCount
      if tabCount > previous then append to string dedent \n } ] \n to the far
      if tabCount < previous  then append to string indent \n { \n to the beginning of the line  
        
      incr n in 

      List.iter f lines ;;
