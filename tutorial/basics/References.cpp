#include "luanics/testing/Tutorial.hpp"

#include <cassert>

BEGIN_CHAPTER(References)

// * References must bind to an object exactly once, at initialization.
// * After binding, reference variables are no different than object variables --- both provide names which can be used to \emph{view} the object.
// * Different views of an object may have different types.
// * lvalue references are introduced with \&, rvalue references are introduced with \&\&.
// * Rules for binding:
//   * lvalue references bind to objects, rvalue references to unobjects.
//   * references to non-const bind only to non-const objects, references to const bind to both const and non-const objects.
//   * As a special case, lvalue reference to const binds to everything.
// * Rules for reference collapsing:
//   * If either reference is lvalue, the result is lvalue.
//   * Only if both references are rvalue is the result rvalue.

SECTION(Basics) {


}

SECTION(Binding) {

}




END_CHAPTER(References)
