#include <iostream>
// Which type has a theString.
// Which type has the expression “World of C++”
// What print the program (3 lines)
template < class T, size_t N >
size_t sizeof_array( T ( & )[ N ] )
{
    return N;
}

int a[ 10 ];
void test1()
{
    auto theString = "World of C++";
    std::cout << sizeof_array( a ) << std::endl;
    std::cout << sizeof_array( "World of C++" ) << std::endl;
    std::cout << theString << std::endl;
    theString += 9;
    std::cout << theString << 1 [ theString ] << std::endl;
    std::cout << theString << theString + 1 << std::endl;
}

int main()
{
    test1();
    return 0;
}
