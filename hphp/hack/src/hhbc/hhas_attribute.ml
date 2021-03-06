(**
 * Copyright (c) 2017, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the "hack" directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
*)

type t = {
  attribute_name          : Litstr.id;
  attribute_arguments     : Hhbc_ast.instruct_lit_const list
}

let make attribute_name attribute_arguments =
  { attribute_name; attribute_arguments }

let name a = a.attribute_name
let arguments a = a.attribute_arguments
