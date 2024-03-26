OS = $(shell uname)
TEST_NAME = tests
ifeq ("$(OS)", "Linux")
    BUILD_FILE_TMP = PhotoLab
    BUILD_FILE = PhotoLab
    OPEN = xdg-open
    LEAKS_RUN = valgrind --track-origins=yes ./$(TESTS_DIR)/$(TEST_NAME)
else
    BUILD_FILE_TMP = PhotoLab.app
    BUILD_FILE = PhotoLab.app
    OPEN = open
    LEAKS_RUN = CK_FORK=no leaks -atExit -- ./$(TESTS_DIR)/$(TEST_NAME)
endif

CC = g++

#-------------------------------------------------------
#    Dirs
#-------------------------------------------------------

TESTS_DIR = ../tests_build
BUILD_DIR = ../build
DIST_DIR = "../PhotoLab_v1.0"
DVI_DIR = "../doc_PhotoLab"
REPORT_DIR = ../report

#-------------------------------------------------------
#    Make dirs
#-------------------------------------------------------

BUILD = @mkdir -p $(BUILD_DIR)
TESTS = @mkdir -p $(TESTS_DIR)
DIST = @mkdir -p $(DIST_DIR)
REPORT = @mkdir -p $(REPORT_DIR)

#-------------------------------------------------------
#    Dist name
#-------------------------------------------------------

DIST_NAME = $(DIST_DIR).tar.gz

#-------------------------------------------------------
#    Targets
#-------------------------------------------------------

all: install

install:
	$(BUILD)
	@cd $(BUILD_DIR) && cmake ../src -B . && cmake --build .

uninstall:
	rm -rf $(BUILD_DIR)

dvi:
	makeinfo -o $(DVI_DIR) --html --no-warn --force PhotoLab_v1.0_info.texi
	$(OPEN) $(DVI_DIR)/index.html

dist:
	$(DIST)
	cp -r Makefile main.cc CMakeLists.txt controller model view $(DIST_DIR)
	tar -cvzf $(DIST_NAME) $(DIST_DIR)
	rm -rf $(DIST_DIR)

tests: build_tests
	./$(TESTS_DIR)/$(TEST_NAME)

build_tests: clean_src
	$(TESTS)
	@cd $(TESTS_DIR) && cmake ../src -B . && cmake --build . --target $(TEST_NAME)

gcov_report:
	$(TESTS)
	@cd $(TESTS_DIR) && cmake -DGCOVREPORT=ON ../src -B . && cmake --build . --target $(TEST_NAME)
	./$(TESTS_DIR)/$(TEST_NAME)
	$(REPORT)
	gcovr $(TESTS_DIR) --html --html-details -f model/model.cc -f model/filter.cc -o $(REPORT_DIR)/report.html
	$(OPEN) $(REPORT_DIR)/report.html

google_style:
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -verbose -style=google -i {} +

clang:
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -verbose -style=google -n {} +

cppcheck:
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec cppcheck --enable=all --suppress=missingIncludeSystem {} +

leaks: tests
	$(LEAKS_RUN)

clean_src:
	rm -rf $(BUILD_DIR)
	rm -rf $(DIST_DIR)
	rm -rf $(DIST_NAME)
	rm -rf $(TESTS_DIR)
	rm -rf $(DVI_DIR)

clean: clean_src
	rm -rf $(REPORT_DIR)

.PHONY: all tests clean
