/*
 * main.cpp
 *
 *  Created on: Nov 18, 2021
 *      Author: magnus
 */

#include <limits.h>
#include <gtest/gtest.h>

#include "MasterMind.h"

TEST(MasterMind, guess)
{
	t_colorSequnence masterSequence = {
			color::BLACK,
			color::BLACK,
			color::BLUE,
			color::WHITE,
			color::GREEN
	};
	MasterMind mm(masterSequence);
	EXPECT_EQ(score::HIT, mm.guess(0, color::BLACK));
	EXPECT_EQ(score::MISS, mm.guess(0, color::GREEN));
	EXPECT_EQ(score::NONE, mm.guess(0, color::RED));
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
