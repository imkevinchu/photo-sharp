(* Code generation: translate takes a semantically checked AST and
produces LLVM IR

LLVM tutorial: Make sure to read the OCaml version of the tutorial

http://llvm.org/docs/tutorial/index.html

Detailed documentation on the OCaml LLVM library:

http://llvm.moe/
http://llvm.moe/ocaml/

*)

module L = Llvm
module A = Ast
open Sast

module StringMap = Map.Make(String)

(* translate : Sast.program -> Llvm.module *)
let translate (globals, functions) =
  let context    = L.global_context () in

  (* Create the LLVM compilation module into which
     we will generate code *)
  let the_module = L.create_module context "MicroC" in

  (* Get types from the context *)
  let i32_t      = L.i32_type    context
  and i64_t      = L.i64_type    context
  and i8_t       = L.i8_type     context
  and i1_t       = L.i1_type     context
  and float_t    = L.double_type context
  and void_t     = L.void_type   context
  and pix_t      = L.pointer_type (L.i32_type context)
  and image_t    = L.pointer_type (L.i32_type context)
  and album_t    = L.pointer_type (L.i32_type context)
  and string_t   = L.pointer_type (L.i8_type context) 
  and arr_t    = L.pointer_type (L.i32_type context)
  and grad_t     = L.pointer_type (L.i32_type context)
  in


  (* Return the LLVM type for a MicroC type *)
  let ltype_of_typ = function
      A.Int   -> i32_t
    | A.Bool  -> i1_t
    | A.Float -> float_t
    | A.Void  -> void_t
    | A.String -> string_t
    | A.Image -> image_t
    | A.Album -> album_t
    | A.Array -> arr_t
    | A.Pixel -> pix_t
    | A.Gradient -> grad_t
  in

  (* Create a map of global variables after creating each *)
  let global_vars : L.llvalue StringMap.t =
    let global_var m (t, n) =
      let init = match t with
          A.Float -> L.const_float (ltype_of_typ t) 0.0
        | _ -> L.const_int (ltype_of_typ t) 0
      in StringMap.add n (L.define_global n init the_module) m in
    List.fold_left global_var StringMap.empty ((A.Int, "Marie!") :: globals) in

  let printf_t : L.lltype =
      L.var_arg_function_type i32_t [| L.pointer_type i8_t |] in
  let printf_func : L.llvalue =
      L.declare_function "printf" printf_t the_module in

  let printbig_t : L.lltype =
      L.function_type i32_t [| i32_t |] in
  let printbig_func : L.llvalue =
      L.declare_function "printbig" printbig_t the_module in

  let printPix_t : L.lltype =
      L.function_type i32_t [| pix_t |] in
  let printPix_func : L.llvalue =
      L.declare_function "printPix" printPix_t the_module in

  let setPix_t : L.lltype =
      L.function_type pix_t [|i32_t; i32_t; i32_t; i32_t|] in
  let setPix_func : L.llvalue =
      L.declare_function "setPix" setPix_t the_module in

  (* Link Image editing functions *)

  let open_t : L.lltype =
      L.function_type image_t [| L.pointer_type i8_t |] in
  let open_func : L.llvalue =
      L.declare_function "open" open_t the_module in

  let save_t : L.lltype =
      L.function_type image_t [| L.pointer_type i8_t; image_t |] in
  let save_func : L.llvalue =
      L.declare_function "save" save_t the_module in

  let printImage_t : L.lltype =
      L.function_type i32_t [| image_t |] in
  let printImage_func : L.llvalue =
      L.declare_function "PrintImage" printImage_t the_module in

  let contrast_t : L.lltype =
      L.function_type i32_t [| image_t; i32_t |] in
  let contrast_func : L.llvalue =
      L.declare_function "ImageContrast" contrast_t the_module in

  let saturate_t : L.lltype =
      L.function_type i32_t [| image_t; i32_t |] in
  let saturate_func : L.llvalue =
      L.declare_function "ImageSaturate" saturate_t the_module in

  let rotate90_t : L.lltype =
      L.function_type i32_t [| image_t |] in
  let rotate90_func : L.llvalue =
      L.declare_function "ImageRotate90" rotate90_t the_module in

  let addNoise_t : L.lltype =
      L.function_type i32_t [| image_t; float_t; float_t |] in
  let addNoise_func : L.llvalue =
      L.declare_function "ImageAddNoise" addNoise_t the_module in

  let kelvin_t : L.lltype =
      L.function_type i32_t [| image_t; float_t |] in
  let kelvin_func : L.llvalue =
      L.declare_function "ImageKelvin" kelvin_t the_module in

  let reflectY_t : L.lltype =
      L.function_type i32_t [| image_t |] in
  let reflectY_func : L.llvalue =
      L.declare_function "ImageReflectY" reflectY_t the_module in

  let reflectX_t : L.lltype =
      L.function_type i32_t [| image_t |] in
  let reflectX_func : L.llvalue =
      L.declare_function "ImageReflectX" reflectX_t the_module in

  let crop_t : L.lltype =
      L.function_type i32_t [| image_t; float_t |] in
  let crop_func : L.llvalue =
      L.declare_function "ImageCrop" crop_t the_module in

  let brightness_t : L.lltype =
      L.function_type i32_t [| image_t; i32_t |] in
  let brightness_func : L.llvalue =
      L.declare_function "ImageBrightness" brightness_t the_module in

  let tint_t : L.lltype =
      L.function_type i32_t [| image_t; i32_t |] in
  let tint_func : L.llvalue =
      L.declare_function "ImageTint" tint_t the_module in

  let hsl_t : L.lltype =
      L.function_type i32_t [| image_t; i32_t; i32_t; i32_t|] in
  let hsl_func : L.llvalue =
      L.declare_function "ImageHSL" hsl_t the_module in

  let imageSize_t : L.lltype =
      L.function_type i32_t [| image_t |] in
  let imageSize_func : L.llvalue =
      L.declare_function "ImageSize" imageSize_t the_module in

  let imageRevert_t : L.lltype =
      L.function_type i32_t [| image_t |] in
  let imageRevert_func : L.llvalue =
      L.declare_function "ImageRevert" imageRevert_t the_module in

  let getPix_t : L.lltype =
      L.function_type pix_t [| image_t ; i32_t |] in
  let getPix_func : L.llvalue =
      L.declare_function "getPixel" getPix_t the_module in

  let satPix_t : L.lltype =
      L.function_type i32_t [| pix_t ; i32_t |] in
  let satPix_func : L.llvalue =
      L.declare_function "PixelSaturate" satPix_t the_module in

  let redPixel_t : L.lltype =
      L.function_type i32_t [| pix_t |] in
  let redPixel_func : L.llvalue =
      L.declare_function "RedPixel" redPixel_t the_module in

  let newAlbum_t : L.lltype =
      L.function_type album_t [||] in
  let newAlbum_func : L.llvalue =
      L.declare_function "newAlbum" newAlbum_t the_module in

  let newGradient_t : L.lltype =
        L.function_type grad_t [| image_t ; i32_t|] in
  let newGradient_func : L.llvalue =
        L.declare_function "newImageGradient" newGradient_t the_module in

  let applyGrad_t : L.lltype =
        L.function_type grad_t [| image_t; grad_t |] in
  let applyGradient_func : L.llvalue =
        L.declare_function "GradToLayer" applyGrad_t the_module in

  let gradCon_t : L.lltype =
        L.function_type grad_t [| grad_t; i32_t|] in
  let gradContrast_func : L.llvalue =
        L.declare_function "GradContrast" gradCon_t the_module in
  let gradBright_t : L.lltype =
        L.function_type grad_t [| grad_t; i32_t|] in
  let gradBright_func : L.llvalue =
        L.declare_function "GradBrightness" gradBright_t the_module in
  let gradHSL_t : L.lltype =
        L.function_type grad_t [| grad_t ; i32_t ; i32_t ; i32_t|] in
  let gradHSL_func : L.llvalue =
        L.declare_function "GradHSL" gradHSL_t the_module in

  let addImage_t : L.lltype =
      L.function_type i32_t [| album_t; image_t |] in
  let addImage_func : L.llvalue =
      L.declare_function "addToAlbum" addImage_t the_module in

  let albumSize_t : L.lltype =
      L.function_type i32_t [| album_t |] in
  let albumSize_func : L.llvalue =
      L.declare_function "AlbumSize" albumSize_t the_module in

  let getImage_t : L.lltype =
      L.function_type image_t [| album_t; i32_t |] in
  let getImage_func : L.llvalue =
      L.declare_function "GetImage" getImage_t the_module in

  let freeGradient_t : L.lltype =
      L.function_type grad_t [| grad_t |] in
  let freeGradient_func : L.llvalue =
      L.declare_function "freeGradient" freeGradient_t the_module in
  let freeAlbum_t : L.lltype =
      L.function_type album_t [| album_t |] in
  let freeAlbum_func : L.llvalue =
      L.declare_function "freeAlbum" freeAlbum_t the_module in
  let freeImage_t : L.lltype =
      L.function_type image_t [| image_t |] in
  let freeImage_func : L.llvalue =
      L.declare_function "freeImageStack" freeImage_t the_module in
  let freePixel_t : L.lltype =
      L.function_type pix_t [| pix_t |] in
  let freePixel_func : L.llvalue =
      L.declare_function "freePix" freePixel_t the_module in

  let removeLast_t : L.lltype =
      L.function_type i32_t [| album_t |] in
  let removeLast_func : L.llvalue =
      L.declare_function "removeLast" removeLast_t the_module in

  let newArrayString_t : L.lltype = 
      L.function_type arr_t [| |] in
  let newArrayString_func : L.llvalue = 
      L.declare_function "newArrayString" newArrayString_t the_module in

  let getVal_t : L.lltype = 
      L.function_type string_t [| arr_t; i32_t |] in
  let getVal_func : L.llvalue = 
      L.declare_function "getVal" getVal_t the_module in

  let setVal_t : L.lltype = 
      L.function_type i32_t [| arr_t; string_t; i32_t |] in
  let setVal_func : L.llvalue = 
      L.declare_function "setVal" setVal_t the_module in

  (* Define each function (arguments and return type) so we can 
     call it even before we've created its body *)
  let function_decls : (L.llvalue * sfunc_decl) StringMap.t =
    let function_decl m fdecl =
      let name = fdecl.sfname
      and formal_types =
	Array.of_list (List.map (fun (t,_) -> ltype_of_typ t) fdecl.sformals)
      in let ftype = L.function_type (ltype_of_typ fdecl.styp) formal_types in
      StringMap.add name (L.define_function name ftype the_module, fdecl) m in
    List.fold_left function_decl StringMap.empty functions in

  (* Fill in the body of the given function *)
  let build_function_body fdecl =
    let (the_function, _) = StringMap.find fdecl.sfname function_decls in
    let builder = L.builder_at_end context (L.entry_block the_function) in

    let int_format_str = L.build_global_stringptr "%d\n" "fmt" builder
    and str_str = L.build_global_stringptr "%s\n" "fmt" builder
    and float_format_str = L.build_global_stringptr "%g\n" "fmt" builder in

    (* Construct the function's "locals": formal arguments and locally
       declared variables.  Allocate each on the stack, initialize their
       value, if appropriate, and remember their values in the "locals" map *)
    let local_vars =
      let add_formal m (t, n) p =
        L.set_value_name n p;
	let local = L.build_alloca (ltype_of_typ t) n builder in
        ignore (L.build_store p local builder);
	StringMap.add n local m

      (* Allocate space for any locally declared variables and add the
       * resulting registers to our map *)
      and add_local m (t, n) =
	let local_var = L.build_alloca (ltype_of_typ t) n builder
	in StringMap.add n local_var m
      in

      let formals = List.fold_left2 add_formal StringMap.empty fdecl.sformals
          (Array.to_list (L.params the_function)) in
      List.fold_left add_local formals fdecl.slocals
    in

    (* Return the value for a variable or formal argument.
       Check local names first, then global names *)
    let lookup n = try StringMap.find n local_vars
                   with Not_found -> StringMap.find n global_vars
    in

    (* Construct code for an expression; return its value *)
    let rec expr builder ((_, e) : sexpr) = match e with
	SLiteral i  -> L.const_int i32_t i
      | SBoolLit b  -> L.const_int i1_t (if b then 1 else 0)
      | SFliteral l -> L.const_float_of_string float_t l
      | SStrLit s   -> L.build_global_stringptr s "" builder
      | SPixelLit(r,g,b,a)-> let r' = expr builder r
                           and g' = expr builder g
                           and b' = expr builder b
                           and a' = expr builder a in
                           L.build_call setPix_func [| r'; g'; b'; a' |] "setPix" builder
      | SNoexpr     -> L.const_int i32_t 0
      | SId s       -> L.build_load (lookup s) s builder
      | SAssign (s, e) -> let e' = expr builder e in
                          ignore(L.build_store e' (lookup s) builder); e'
      | SBinop ((A.Float,_ ) as e1, op, e2) ->
	  let e1' = expr builder e1
	  and e2' = expr builder e2 in
	  (match op with
	    A.Add     -> L.build_fadd
	  | A.Sub     -> L.build_fsub
	  | A.Mult    -> L.build_fmul
	  | A.Div     -> L.build_fdiv
	  | A.Equal   -> L.build_fcmp L.Fcmp.Oeq
	  | A.Neq     -> L.build_fcmp L.Fcmp.One
	  | A.Less    -> L.build_fcmp L.Fcmp.Olt
	  | A.Leq     -> L.build_fcmp L.Fcmp.Ole
	  | A.Greater -> L.build_fcmp L.Fcmp.Ogt
	  | A.Geq     -> L.build_fcmp L.Fcmp.Oge
	  | A.And | A.Or ->
	      raise (Failure "internal error: semant should have rejected and/or on float")
	  ) e1' e2' "tmp" builder
      | SBinop (e1, op, e2) ->
	  let e1' = expr builder e1
	  and e2' = expr builder e2 in
	  (match op with
	    A.Add     -> L.build_add
	  | A.Sub     -> L.build_sub
	  | A.Mult    -> L.build_mul
          | A.Div     -> L.build_sdiv
	  | A.And     -> L.build_and
	  | A.Or      -> L.build_or
	  | A.Equal   -> L.build_icmp L.Icmp.Eq
	  | A.Neq     -> L.build_icmp L.Icmp.Ne
	  | A.Less    -> L.build_icmp L.Icmp.Slt
	  | A.Leq     -> L.build_icmp L.Icmp.Sle
	  | A.Greater -> L.build_icmp L.Icmp.Sgt
	  | A.Geq     -> L.build_icmp L.Icmp.Sge
	  ) e1' e2' "tmp" builder
      | SUnop(op, ((t, _) as e)) ->
          let e' = expr builder e in
	  (match op with
	    A.Neg when t = A.Float -> L.build_fneg
	  | A.Neg                  -> L.build_neg
          | A.Not                  -> L.build_not) e' "tmp" builder
      | SCall ("print", [e]) | SCall ("printb", [e]) ->
        let (t, _) = e in
          (match t with
             A.Int -> L.build_call printf_func [| int_format_str ; (expr builder e) |]
	    "printf" builder
           | A.Float -> L.build_call printf_func [| float_format_str ; (expr builder e) |]
	    "printf" builder
           | A.String -> L.build_call printf_func [| str_str; (expr builder e) |]
	    "printf" builder
           | A.Bool -> L.build_call printf_func [| int_format_str ; (expr builder e) |]
	    "printf" builder
           | A.Pixel -> L.build_call printPix_func [| (expr builder e) |]
	    "printPix" builder
           | A.Image -> L.build_call printImage_func [| (expr builder e) |]
	    "PrintImage" builder)
      | SCall ("prints", [e]) ->
          L.build_call printf_func [| str_str; (expr builder e) |]
             "printf" builder
      | SCall ("printbig", [e]) ->
	  L.build_call printbig_func [| (expr builder e) |] "printbig" builder
      | SCall ("printf", [e]) ->
	  L.build_call printf_func [| float_format_str ; (expr builder e) |]
	    "printf" builder
      | SCall ("open", [e]) ->
          L.build_call open_func [| (expr builder e) |] "open" builder
      | SCall ("save", e) ->
          L.build_call save_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "save" builder
      | SCall ("Contrast", e) ->
          L.build_call contrast_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "ImageContrast" builder
      | SCall ("Saturate", e) ->
          L.build_call saturate_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "ImageSaturate" builder
      | SCall ("Rotate90", [e]) ->
          L.build_call rotate90_func [| (expr builder e) |] "ImageRotate90" builder
      | SCall ("AddNoise", e) ->
          L.build_call addNoise_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e))); (expr builder (List.hd (List.tl (List.tl e)))) |] "ImageAddNoise" builder
      | SCall ("Kelvin", e) ->
          L.build_call kelvin_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "ImageKelvin" builder
      | SCall ("ReflectY", [e]) ->
          L.build_call reflectY_func [| (expr builder e) |] "ImageReflectY" builder
      | SCall ("ReflectX", [e]) ->
          L.build_call reflectX_func [| (expr builder e) |] "ImageReflectX" builder
      | SCall ("Tint", e) ->
          L.build_call tint_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "ImageTint" builder
      | SCall ("Crop", e) ->
          L.build_call crop_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "ImageCrop" builder
      | SCall ("Brightness", e) ->
          L.build_call brightness_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "ImageBrightness" builder
      | SCall ("HSL", e) ->
          L.build_call hsl_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e))); (expr builder (List.hd (List.tl (List.tl e)))); (expr builder (List.hd (List.tl (List.tl (List.tl e))))) |] "ImageHSL" builder
      | SCall ("GetPixel", e) ->
          L.build_call getPix_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "getPixel" builder
      | SCall ("ImageSize", [e]) ->
          L.build_call imageSize_func [| (expr builder e)|] "ImageSize" builder
      | SCall ("Revert", [e]) ->
          L.build_call imageRevert_func [| (expr builder e)|] "ImageRevert" builder
      | SCall ("SaturatePixel", e) ->
          L.build_call satPix_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "PixelSaturate" builder
      | SCall ("RedPixel", [e]) ->
          L.build_call redPixel_func [| (expr builder e) |] "RedPixel" builder
      | SCall ("NewAlbum", []) ->
          L.build_call newAlbum_func [| |] "newAlbum" builder
      | SCall ("NewGradient", e) ->
            L.build_call newGradient_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "newImageGradient" builder
      | SCall ("ApplyGradient", e)->
            L.build_call applyGradient_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e))) |] "GradToLayer" builder
      | SCall ("gContrast", e) ->
            L.build_call gradContrast_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "GradContrast" builder
      | SCall ("gBrightness", e) ->
        L.build_call gradBright_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e)))|] "GradBrightness" builder
      | SCall ("gHSL", e) ->
            L.build_call gradHSL_func [| (expr builder (List.hd e)); (expr builder (List.hd (List.tl e))); (expr builder (List.hd (List.tl (List.tl e)))); (expr builder (List.hd (List.tl (List.tl (List.tl e)))))|] "GradHSL" builder
      | SCall ("AddImage", e) ->
          L.build_call addImage_func [|(expr builder (List.hd e)); (expr builder (List.hd (List.tl e))) |] "addToAlbum" builder
      | SCall ("AlbumSize", [e]) ->
          L.build_call albumSize_func [|(expr builder e) |] "AlbumSize" builder
      | SCall ("GetImage", e) ->
          L.build_call getImage_func [|(expr builder (List.hd e)); (expr builder (List.hd (List.tl e))) |] "GetImage" builder
      | SCall ("RemoveLast", [e]) ->
          L.build_call removeLast_func [|(expr builder e) |] "removeLast" builder
      | SCall ("newArray", []) ->
          L.build_call newArrayString_func [| |] "newArrayString" builder
      | SCall ("getVal", e) ->
          L.build_call getVal_func [|(expr builder (List.hd e)); (expr builder (List.hd (List.tl e))) |] "getVal" builder
      | SCall ("setVal", e) ->
          L.build_call setVal_func [|(expr builder (List.hd e)); (expr builder (List.hd (List.tl e))); (expr builder (List.hd (List.tl (List.tl e))))|] "setVal" builder
 

      | SCall ("Free", [e]) ->
            let (t, _) = e in
                (match t with
                    A.Image -> L.build_call freeImage_func [|(expr builder e)|] "freeImageStack" builder
                    | A.Album -> L.build_call freeAlbum_func [|(expr builder e)|] "freeAlbum" builder
                    | A.Pixel -> L.build_call freePixel_func [|(expr builder e)|] "freePix" builder
                    | A.Gradient -> L.build_call freeGradient_func [|(expr builder e)|] "freeGradient" builder)

      | SCall (f, args) ->
         let (fdef, fdecl) = StringMap.find f function_decls in
	 let llargs = List.rev (List.map (expr builder) (List.rev args)) in
	 let result = (match fdecl.styp with
                        A.Void -> ""
                      | _ -> f ^ "_result") in
         L.build_call fdef (Array.of_list llargs) result builder
    in

    (* LLVM insists each basic block end with exactly one "terminator"
       instruction that transfers control.  This function runs "instr builder"
       if the current block does not already have a terminator.  Used,
       e.g., to handle the "fall off the end of the function" case. *)
    let add_terminal builder instr =
      match L.block_terminator (L.insertion_block builder) with
	Some _ -> ()
      | None -> ignore (instr builder) in

    (* Build the code for the given statement; return the builder for
       the statement's successor (i.e., the next instruction will be built
       after the one generated by this call) *)

    let rec stmt builder = function
	SBlock sl -> List.fold_left stmt builder sl
      | SExpr e -> ignore(expr builder e); builder
      | SReturn e -> ignore(match fdecl.styp with
                              (* Special "return nothing" instr *)
                              A.Void -> L.build_ret_void builder
                              (* Build return statement *)
                            | _ -> L.build_ret (expr builder e) builder );
                     builder
      | SIf (predicate, then_stmt, else_stmt) ->
         let bool_val = expr builder predicate in
	 let merge_bb = L.append_block context "merge" the_function in
         let build_br_merge = L.build_br merge_bb in (* partial function *)

	 let then_bb = L.append_block context "then" the_function in
	 add_terminal (stmt (L.builder_at_end context then_bb) then_stmt)
	   build_br_merge;

	 let else_bb = L.append_block context "else" the_function in
	 add_terminal (stmt (L.builder_at_end context else_bb) else_stmt)
	   build_br_merge;

	 ignore(L.build_cond_br bool_val then_bb else_bb builder);
	 L.builder_at_end context merge_bb

      | SWhile (predicate, body) ->
	  let pred_bb = L.append_block context "while" the_function in
	  ignore(L.build_br pred_bb builder);

	  let body_bb = L.append_block context "while_body" the_function in
	  add_terminal (stmt (L.builder_at_end context body_bb) body)
	    (L.build_br pred_bb);

	  let pred_builder = L.builder_at_end context pred_bb in
	  let bool_val = expr pred_builder predicate in

	  let merge_bb = L.append_block context "merge" the_function in
	  ignore(L.build_cond_br bool_val body_bb merge_bb pred_builder);
	  L.builder_at_end context merge_bb

      (* Implement for loops as while loops *)
      | SFor (e1, e2, e3, body) -> stmt builder
	    ( SBlock [SExpr e1 ; SWhile (e2, SBlock [body ; SExpr e3]) ] )

      (* Implement enhanced for loop syntax as while loops *)
      | SEFor (it, obj, body) ->
            (* call start and size functions, parser to traditional For syntax *)

            let (t, _) = obj in
                (match t with
                   A.Image ->
                     let e1 = (A.Int, SAssign("Marie!", (A.Int, SLiteral 0))) and
                         e2 = (A.Int, (SBinop((A.Int, SId("Marie!")), Less, (A.Int, SCall("ImageSize", [obj]))))) and
                         e3 = (A.Int, SAssign("Marie!", (A.Int, SBinop((A.Int, SId("Marie!")), Add, (A.Int, SLiteral 1))))) and
                         e4 = (A.Int, SAssign(it, (A.Int, SCall(("GetPixel", [obj; (A.Int, SId("Marie!"))]))))) in
                         stmt builder ( SBlock [SExpr e1 ; SWhile (e2, SBlock [SExpr e4; body ; SExpr e3]) ] )

                 | A.Album ->
                     let e1 = (A.Int, SAssign("Marie!", (A.Int, SLiteral 0))) and
                         e2 = (A.Int, (SBinop((A.Int, SId("Marie!")), Less, (A.Int, SCall("AlbumSize", [obj]))))) and
                         e3 = (A.Int, SAssign("Marie!", (A.Int, SBinop((A.Int, SId("Marie!")), Add, (A.Int, SLiteral 1))))) and
                         e4 = (A.Int, SAssign(it, (A.Int, SCall(("GetImage", [obj; (A.Int, SId("Marie!"))]))))) in
	                  stmt builder ( SBlock [SExpr e1 ; SWhile (e2, SBlock [SExpr e4; body ; SExpr e3]) ] ))
      | SEEFor (it, s, e, body) ->
            (* call start and size functions, parser to traditional For syntax *)

            let (t, _) = s in
                (match t with
                 | A.Int ->
                     let e1 = (A.Int, SAssign(it, s)) and
                         e2 = (A.Int, (SBinop((A.Int, SId(it)), Less, (e)))) and
                         e3 = (A.Int, SAssign(it, (A.Int, SBinop((A.Int, SId(it)), Add, (A.Int, SLiteral 1))))) in
	                  stmt builder ( SBlock [SExpr e1 ; SWhile (e2, SBlock [body ; SExpr e3]) ] ))



    in

    (* Build the code for each statement in the function *)
    let builder = stmt builder (SBlock fdecl.sbody) in

    (* Add a return if the last block falls off the end *)
    add_terminal builder (match fdecl.styp with
        A.Void -> L.build_ret_void
      | A.Float -> L.build_ret (L.const_float float_t 0.0)
      | t -> L.build_ret (L.const_int (ltype_of_typ t) 0))
  in



  List.iter build_function_body functions;
  the_module
