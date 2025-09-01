//
// Created by Ahmed Mustafa on 8/16/2025.
//

#include <gtest/gtest.h>
#include <utils/Time.h>

TEST(TimeTest, GetCurrentTime) {

    auto currentTime = Split::Time::getCurrentTime();
    ASSERT_FALSE(currentTime.empty());
    ASSERT_EQ(currentTime.size(), 19); // Format: YYYY-MM-DD HH:MM:SS
    ASSERT_EQ(currentTime[4], '-'); // Check for date separator
    ASSERT_EQ(currentTime[7], '-'); // Check for date separator
    ASSERT_EQ(currentTime[10], ' '); // Check for time separator
    ASSERT_EQ(currentTime[13], ':'); // Check for time separator
    ASSERT_EQ(currentTime[16], ':'); // Check for time separator

    std::cout << "Current Time: " << currentTime << std::endl;

}