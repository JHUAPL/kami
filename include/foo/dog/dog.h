#ifndef FOO_DOG_HPP_
#define FOO_DOG_HPP_

#include <iostream> // std::cout


// this is a generated header. It is needed
// to build dll libraries that work on windows.
// add the BAR_EXPORT definition to each
// function/class you want to export to the dll.
#include <foo/dog/DOG_EXPORT.h>

namespace foo {

class DOG_EXPORT dog
{
    public:
        dog();
        ~dog();

};

} // namespace foo

#endif // FOO_BAZ_HPP_
