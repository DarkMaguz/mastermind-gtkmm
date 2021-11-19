bin_PROGRAMS = mastermind test

mastermind_SOURCES = main.cpp MainWindow.cpp PlayerBoard.cpp MasterMind.cpp Peg.cpp ScorePeg.cpp
mastermind_CPPFLAGS = $(GTKMM_CFLAGS) -DGTKMM_DISABLE_DEPRECATED=1 $(SICPP_CFLAGS)
mastermind_LDADD = $(GTKMM_LIBS) $(SICPP_LIBS)

test_SOURCES = test.cpp MasterMind.cpp
test_CPPFLAGS = $(GTEST_CFLAGS) $(SICPP_CFLAGS)
test_LDADD = $(GTEST_LIBS) $(SICPP_LIBS)
