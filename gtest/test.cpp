#include "verify.h"
#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
const std::string licfile_path = "../testlic.lic";
const std::string pubkey_path = "../testpub.pub";

checkLicense c(pubkey_path, licfile_path);
Verify v("12345678");
TEST(InitTest, DecodingValue)
{
    EXPECT_NO_THROW(c.init());
}

TEST(NoThrow, HostId)
{
    EXPECT_NO_THROW(c.validateHostId("12345678"));
    EXPECT_NO_THROW(c.validateHostId("23456789"));
    EXPECT_NO_THROW(c.validateHostId("34567890"));
}


TEST(Throw, HostId)
{
    EXPECT_THROW(c.validateHostId("11223344"), std::runtime_error);
}


TEST(ReturnValue, HostId)
{
    EXPECT_TRUE(c.validateHostId("12345678"));
    EXPECT_TRUE(c.validateHostId("23456789"));
    EXPECT_TRUE(c.validateHostId("34567890"));
}

int main()
{

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();

    return 0;
}

