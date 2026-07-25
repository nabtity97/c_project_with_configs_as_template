# ============================================================
# Toolchain
# ============================================================

# Uses GCC from the system PATH.
# Can be overridden:
#   mingw32-make CC=clang
CC := gcc


# ============================================================
# Project directories
# ============================================================

SRC_DIR          := src
INCLUDE_DIR      := include

TEST_SRC_DIR     := tests/unit_tests/src
TEST_INCLUDE_DIR := tests/unit_tests/include
UNITY_DIR        := tests/unity_framework

BUILD_DIR        := build
PROGRAM_DIR      := $(BUILD_DIR)/program
TEST_BUILD_DIR   := $(BUILD_DIR)/tests

PROGRAM_OBJ_DIR  := $(BUILD_DIR)/objects/program
TEST_OBJ_DIR     := $(BUILD_DIR)/objects/tests


# ============================================================
# Output executables
# ============================================================

PROGRAM_TARGET := $(PROGRAM_DIR)/output.exe
TEST_TARGET    := $(TEST_BUILD_DIR)/unit_tests.exe


# ============================================================
# Source discovery
# ============================================================

# Automatically finds every production .c file.
PROGRAM_SRCS := $(wildcard $(SRC_DIR)/*.c)

# Unit tests have their own main() in test_runner.c,
# so the application's main.c must not be included.
TEST_PRODUCTION_SRCS := \
	$(filter-out $(SRC_DIR)/main.c,$(PROGRAM_SRCS))

# Automatically finds every unit-test .c file.
TEST_SRCS := $(wildcard $(TEST_SRC_DIR)/*.c)

UNITY_SRC := $(UNITY_DIR)/unity.c


# ============================================================
# Object files
# ============================================================

PROGRAM_OBJS := \
	$(patsubst $(SRC_DIR)/%.c,$(PROGRAM_OBJ_DIR)/%.o,$(PROGRAM_SRCS))

TEST_PRODUCTION_OBJS := \
	$(patsubst $(SRC_DIR)/%.c,$(TEST_OBJ_DIR)/production/%.o,$(TEST_PRODUCTION_SRCS))

TEST_OBJS := \
	$(patsubst $(TEST_SRC_DIR)/%.c,$(TEST_OBJ_DIR)/unit_tests/%.o,$(TEST_SRCS))

UNITY_OBJ := $(TEST_OBJ_DIR)/unity/unity.o

ALL_TEST_OBJS := \
	$(TEST_PRODUCTION_OBJS) \
	$(TEST_OBJS) \
	$(UNITY_OBJ)


# ============================================================
# Dependency files
# ============================================================

PROGRAM_DEPS := $(PROGRAM_OBJS:.o=.d)
TEST_DEPS    := $(ALL_TEST_OBJS:.o=.d)


# ============================================================
# Compiler and linker flags
# ============================================================

CFLAGS ?= -g -Wall -Wextra

PROGRAM_CPPFLAGS := \
	-I$(INCLUDE_DIR) \
	-MMD \
	-MP

TEST_CPPFLAGS := \
	-DUNIT_TEST \
	-I$(INCLUDE_DIR) \
	-I$(TEST_INCLUDE_DIR) \
	-I$(UNITY_DIR) \
	-MMD \
	-MP

LDFLAGS ?=
LDLIBS  ?=


# ============================================================
# Operating-system commands
# ============================================================

ifeq ($(OS),Windows_NT)

define create_directory
	@if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
endef

define remove_build_directory
	@if exist "$(subst /,\,$(BUILD_DIR))" rmdir /S /Q "$(subst /,\,$(BUILD_DIR))"
endef

else

define create_directory
	@mkdir -p "$1"
endef

define remove_build_directory
	@rm -rf "$(BUILD_DIR)"
endef

endif


# ============================================================
# Public targets
# ============================================================

.PHONY: all program tests run-tests clean rebuild help

all: program tests

build-program: $(PROGRAM_TARGET)

build-tests: $(TEST_TARGET)

run-program: $(PROGRAM_TARGET)
	@echo Running application...
	@"$(PROGRAM_TARGET)"

run-tests: $(TEST_TARGET)
	@echo Running unit tests...
	@"$(TEST_TARGET)"

clean:
	$(call remove_build_directory)

rebuild: clean all

help:
	@echo Available targets:
	@echo   program     Build the application
	@echo   tests       Build the unit-test executable
	@echo   run-tests   Build and run the unit tests
	@echo   all         Build application and unit tests
	@echo   clean       Delete generated build files
	@echo   rebuild     Clean and build everything


# ============================================================
# Application linking
# ============================================================

$(PROGRAM_TARGET): $(PROGRAM_OBJS)
	$(call create_directory,$(@D))
	$(CC) $(LDFLAGS) $(PROGRAM_OBJS) $(LDLIBS) -o $@


# ============================================================
# Unit-test linking
# ============================================================

$(TEST_TARGET): $(ALL_TEST_OBJS)
	$(call create_directory,$(@D))
	$(CC) $(LDFLAGS) $(ALL_TEST_OBJS) $(LDLIBS) -o $@


# ============================================================
# Compile application source files
# ============================================================

$(PROGRAM_OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(call create_directory,$(@D))
	$(CC) $(PROGRAM_CPPFLAGS) $(CFLAGS) -c $< -o $@


# ============================================================
# Compile production files for unit tests
# ============================================================

$(TEST_OBJ_DIR)/production/%.o: $(SRC_DIR)/%.c
	$(call create_directory,$(@D))
	$(CC) $(TEST_CPPFLAGS) $(CFLAGS) -c $< -o $@


# ============================================================
# Compile unit-test source files
# ============================================================

$(TEST_OBJ_DIR)/unit_tests/%.o: $(TEST_SRC_DIR)/%.c
	$(call create_directory,$(@D))
	$(CC) $(TEST_CPPFLAGS) $(CFLAGS) -c $< -o $@


# ============================================================
# Compile Unity
# ============================================================

$(UNITY_OBJ): $(UNITY_SRC)
	$(call create_directory,$(@D))
	$(CC) $(TEST_CPPFLAGS) $(CFLAGS) -c $< -o $@


# ============================================================
# Generated header dependencies
# ============================================================

-include $(PROGRAM_DEPS)
-include $(TEST_DEPS)