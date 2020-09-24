#include <foo/dog/dog.h>
#include <foo/bar/bar.h>
#include <foo/cat/cat.h>

namespace foo {

dog::dog()
{
    std::cout << "dog constructed" << std::endl;
}

dog::~dog()
{
    #if defined FOO_DOG_DEBUG
    #error DEBUG MODE
    #endif
    std::cout << "dog destroyed" << std::endl;
    bar();
    foo::cat C;
}


} // namespace foo
