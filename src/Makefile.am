bin_PROGRAMS = mastermind test

mastermind_CPPFLAGS = $(GTKMM_CFLAGS) -DGTKMM_DISABLE_DEPRECATED=1
mastermind_LDADD = $(GTKMM_LIBS)
mastermind_SOURCES = main.cpp MainWindow.cpp PlayerBoard.cpp MasterMind.cpp Peg.cpp ScorePeg.cpp

test_SOURCES = test.cpp MasterMind.cpp
test_CPPFLAGS = $(GTEST_CFLAGS)
test_LDADD = $(GTEST_LIBS)