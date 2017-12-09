#include "struct.h"
#include "iterator.h"

Iterator<Term*> * Struct::createIterator()
{
  return new StructIterator(this);
}

Iterator<Term*> * Struct::createBFSIterator()
{
  return new StructIterator(this);
}
