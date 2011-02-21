#include "gtest_NetHeaderAttr.h"

TEST_F(NetHeaderAttrTest, Initialization)
{
    EXPECT_EQ(0, _attr->getPointer());
    EXPECT_EQ(4, _attr->getSize());
}

TEST_F(NetHeaderAttrTest, SettersAndGetters)
{
    _attr->setPointer(5);
    EXPECT_EQ(5, _attr->getPointer());

    _attr->setSize(6);
    EXPECT_EQ(6, _attr->getSize());

    /// \todo testar as operações bitwise
}
