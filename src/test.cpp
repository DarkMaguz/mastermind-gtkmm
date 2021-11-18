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
	MasterMind::t_colorSequnence masterSequence = {
			MasterMind::BLACK,
			MasterMind::BLACK,
			MasterMind::BLUE,
			MasterMind::WHITE,
			MasterMind::GREEN
	};
	MasterMind mm(masterSequence);
	EXPECT_EQ(MasterMind::HIT, mm.guess(0, MasterMind::BLACK));
	EXPECT_EQ(MasterMind::MISS, mm.guess(0, MasterMind::GREEN));
	EXPECT_EQ(MasterMind::NONE, mm.guess(0, MasterMind::RED));
}

TEST(MasterMind, cssColorMap)
{
	EXPECT_EQ(MasterMind::cssColorMap[MasterMind::RED], "red");
	EXPECT_EQ(MasterMind::cssColorMap[MasterMind::GREEN], "green");
	EXPECT_EQ(MasterMind::cssColorMap[MasterMind::BLUE], "blue");
	EXPECT_EQ(MasterMind::cssColorMap[MasterMind::YELLOW], "yellow");
	EXPECT_EQ(MasterMind::cssColorMap[MasterMind::BLACK], "black");
	EXPECT_EQ(MasterMind::cssColorMap[MasterMind::WHITE], "white");
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
