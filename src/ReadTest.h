#ifndef READ_TEST_H
#define READ_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Read.h"

class ReadTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ReadTest);
  CPPUNIT_TEST(testRegion);
  CPPUNIT_TEST(testCheckTrust);
  CPPUNIT_TEST_SUITE_END();

 public:
  void setUp();
  void testRegion();
  void testCheckTrust();
 private:
  bool vec_eq(vector<int> v, int a, int b);
  Read *r;
};

#endif
