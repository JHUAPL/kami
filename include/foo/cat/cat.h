#ifndef FOO_CAT_HPP_
#define FOO_CAT_HPP_

#include <iostream> // std::cout


// this is a generated header. It is needed
// to build dll libraries that work on windows.
// add the BAR_EXPORT definition to each
// function/class you want to export to the dll.
#include <foo/cat/CAT_EXPORT.h>

namespace foo {



class CAT_EXPORT cat
{
    public:
        cat();
        ~cat();

        void call_bar();

};

} // namespace foo

#endif // FOO_BAZ_HPP_
