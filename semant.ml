(* Semantic checking for the NanoC compiler *)

open Ast
open Sast

module StringMap = Map.Make(String)

(* Semantic checking of the AST. Returns an SAST if successful,
   throws an exception if something is wrong.

   Check each global variable, then check each function *)

let check program =

  (* Verify a list of bindings has no duplicate names *)
  let check_binds (kind : string) (binds : (typ * string) list) =
    let rec dups = function
        [] -> ()
      |	((_,n1) :: (_,n2) :: _) when n1 = n2 ->
        raise (Failure ("duplicate " ^ kind ^ " " ^ n1))
      | _ :: t -> dups t
    in dups (List.sort (fun (_,a) (_,b) -> compare a b) binds)
  in

  (* Make sure no locals duplicate *)
  check_binds "local" program.locals;

  (* Build local symbol table of variables for this function *)
  let symbols = List.fold_left (fun m (ty, name) -> StringMap.add name ty m)
      StringMap.empty program.locals
  in

  (* Return a variable from our local symbol table *)
  let type_of_identifier s =
    try StringMap.find s symbols
    with Not_found -> raise (Failure ("undeclared identifier " ^ s))
  in

  (* Return a semantically-checked expression, i.e., with a type *)
  let rec check_expr = function
      Literal l -> (Int, SLiteral l)
    | BoolLit l -> (Bool, SBoolLit l)
    | StrLit l -> (Str, SStrLit l)
    | Id var -> (type_of_identifier var, SId var)
    | Assign(var, e) as ex ->
      let lt = type_of_identifier var
      and (rt, e') = check_expr e in
      if lt = rt then (lt, SAssign(var, (rt, e')))
      else raise (Failure ("illegal assignment " ^ string_of_typ lt ^ " = " ^
                           string_of_typ rt ^ " in " ^ string_of_expr ex))

    | Binop(e1, op, e2) as e ->
      let (t1, e1') = check_expr e1
      and (t2, e2') = check_expr e2 in
      let err = "illegal binary operator " ^
                string_of_typ t1 ^ " " ^ string_of_op op ^ " " ^
                string_of_typ t2 ^ " in " ^ string_of_expr e
      in
      if t1 = t2 then
        let ty = match op with
            Add | Sub when t1 = Int -> Int
          | Equal | Neq -> Bool
          | Less when t1 = Int -> Bool
          | And | Or when t1 = Bool -> Bool
          | _ -> raise (Failure err)
        in (ty, SBinop((t1, e1'), op, (t2, e2')))
      else raise (Failure err)
  in

  let check_bool_expr e =
    let (t, e') = check_expr e in
    if t = Bool then (t, e') else raise (Failure ("expected Boolean expression in " ^ string_of_expr e))
  in

  let rec check_stmt_list = function
      [] -> []
    | Block sl :: sl' -> check_stmt_list (sl @ sl')
    | s :: sl -> check_stmt s :: check_stmt_list sl
  and check_stmt = function
    | Expr e -> SExpr(check_expr e)
    | If(e, st1, st2) ->
      SIf(check_bool_expr e, check_stmt st1, check_stmt st2)
    | While(e, st) ->
      SWhile(check_bool_expr e, check_stmt st)
    | Print (s) ->
      SPrint(check_expr s)
    | Block sl ->
      SBlock(check_stmt_list sl)
  in
  {
    slocals = program.locals;
    sbody = check_stmt_list program.body
  }
