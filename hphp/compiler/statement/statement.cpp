/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-present Facebook, Inc. (http://www.facebook.com)  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "hphp/compiler/statement/statement.h"
#include "hphp/compiler/analysis/function_scope.h"

using namespace HPHP;

///////////////////////////////////////////////////////////////////////////////

#define DEC_STMT_NAMES(x) #x,
const char *Statement::Names[] = {
  DECLARE_STATEMENT_TYPES(DEC_STMT_NAMES)
};
#undef DEC_STMT_NAMES

const char* Statement::nameOfKind(Construct::KindOf kind) {
  assert(kind > Construct::KindOfStatement);
  assert(kind < Construct::KindOfExpression);
  auto const idx = static_cast<int32_t>(kind) -
    static_cast<int32_t>(Construct::KindOfStatement);
  assert(idx > 0);
  return Names[idx];
}

Statement::Statement(STATEMENT_CONSTRUCTOR_BASE_PARAMETERS)
  : Construct(scope, r, kindOf),
    m_labelScope(labelScope) {
  assert(m_labelScope != nullptr);
}

///////////////////////////////////////////////////////////////////////////////
// parser functions

void Statement::addElement(StatementPtr stmt) {
  assert(false);
}

void Statement::insertElement(StatementPtr stmt, int index /* = 0 */) {
  assert(false);
}

bool Statement::hasReachableLabel() const {
  if (skipRecurse()) return false;
  switch (getKindOf()) {
    case KindOfForStatement:
    case KindOfForEachStatement:
    case KindOfWhileStatement:
    case KindOfDoStatement: {
      // a label inside a loop cant be reached from outside the loop
      FunctionScopeRawPtr f = getFunctionScope();
      if (f && f->isGenerator()) break;
      return false;
    }
    case KindOfLabelStatement:
      return true;
    default:
      break;
  }
  for (int i = getKidCount(); i--; ) {
    StatementPtr child(getNthStmt(i));
    if (child && child->hasReachableLabel()) return true;
  }
  return false;
}
