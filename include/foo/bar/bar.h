#ifndef FOO_BAR_HPP_
#define FOO_BAR_HPP_

#include <iostream> // std::cout

// this is a generated header. It is needed
// to build dll libraries that work on windows.
// add the BAR_EXPORT definition to each
// function/class you want to export to the dll.
#include <foo/bar/BAR_EXPORT.h>

namespace foo {


BAR_EXPORT void bar();


} // namespace foo

#endif // FOO_BAZ_HPP_
