#include <gtest/gtest.h>
#include "utIterator.h"
#include "struct.h"
#include "struct.cpp"
#include "list.h"
#include "atom.h"
#include "list.cpp"
#include "atom.cpp"

int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}
