#include "gtest_igmp.h"
#include <gtest/gtest.h>
#include <iostream>
#include <errno.h>

using namespace std;

int main(int argc, char **argv) {

	::testing::InitGoogleTest(&argc, argv);

    if (RUN_ALL_TESTS() != 0){}
        system("PAUSE");

	return 0;
}
