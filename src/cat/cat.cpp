#include <foo/cat/cat.h>
#include <foo/bar/bar.h>

namespace foo {

cat::cat()
{
    std::cout << "Cat constructed" << std::endl;
}

cat::~cat()
{
    std::cout << "Cat destroyed" << std::endl;
}

void cat::call_bar()
{
    std::cout << "Cat calling bar()" << std::endl;
    bar();
}

} // namespace foo
