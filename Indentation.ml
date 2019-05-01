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
    
    
    let rec indentCount inputString n count = 
      if inputString.[n] = '\t' then indentCount inputString (n+1) (count+1)
      else count       
    in

    let f (previous_n, lines_so_far) line =
      let new_tabCount =  indentCount line 0 0 in
      let new_line = 
        if tabCount > previous_n then append to string dedent \n } ] \n to the far
        inputstring :: '\n}\n'
        if tabCount < previous  then append to string indent \n { \n to the beginning of the line 
        in
      let new_lines = lines_so_far :: new_line in
      (new_n, new_lines)
    
    in
    
    let (tabcount,revNewList) = List.fold_left f (0,[]) !lines

    in 

    String.concat "\n" (List.rev revNewList)