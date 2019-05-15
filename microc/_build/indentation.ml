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

let check (previous_n, lines_so_far) line n count = 
  let rec indentCount inputString n count = 
    if inputString.[n] = '\t' then indentCount inputString (n+1) (count+1) else count in
  
  let new_tabCount =  indentCount line 0 0 in 
    
  let new_line = 
    if new_tabCount > previous_n then line ^ " \n}\n "
    else if new_tabCount < previous_n  then  " \n{\n " ^ line in

  let new_lines = lines_so_far :: new_line in

  
  List.fold_left check (0,[]) !lines 0 0
