# Makefile

# Compiler and flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -O2 -Ilib -MMD -MP

# Directories
SRCDIR   := src
LIBDIR   := lib
OUTDIR   := output

# Source files
SRCS := $(shell find $(SRCDIR) -type f -name "*.cpp")
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OUTDIR)/%.out)
DEPS := $(OBJS:.out=.d)

# Colors
GREEN := \033[0;32m
BLUE  := \033[0;34m
YELLOW:= \033[1;33m
RESET := \033[0m

# Counters
NEW_BUILDS := 0
SKIPPED    := 0

# Detect single-file build if target ends with .cpp
ifeq ($(suffix $(MAKECMDGOALS)),.cpp)
    REL_FILE := $(patsubst $(SRCDIR)/%,%,$(MAKECMDGOALS))
    TARGETS  := $(OUTDIR)/$(basename $(REL_FILE)).out
else ifneq ($(file),)
    REL_FILE := $(patsubst $(SRCDIR)/%,%,$(file))
    TARGETS  := $(OUTDIR)/$(basename $(REL_FILE)).out
else
    TARGETS := $(OBJS)
endif

# Default target
all: $(TARGETS)
	@printf "\n$(YELLOW)Build Summary:$(RESET)\n"
	@printf "  $(GREEN)%d new$(RESET), $(BLUE)%d unchanged$(RESET), total: %d\n" $(NEW_BUILDS) $(SKIPPED) $(words $(TARGETS))

# Compile rule with build summary counters
$(OUTDIR)/%.out: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@if [ ! -f "$@" ] || [ "$<" -nt "$@" ]; then \
		printf "$(BLUE)Compiling$(RESET) %s...\n" "$<"; \
		$(CXX) $(CXXFLAGS) $< -o $@; \
		printf "$(GREEN)Built$(RESET) %s\n" "$@"; \
		NEW_BUILDS=$$((NEW_BUILDS+1)); \
	else \
		printf "$(YELLOW)Skipping$(RESET) %s (up to date)\n" "$<"; \
		SKIPPED=$$((SKIPPED+1)); \
	fi

# Run all or single target
run: all
	@printf "$(BLUE)Running executables...$(RESET)\n"
	@for bin in $(TARGETS); do \
		printf "\n=== $(GREEN)Running %s$(RESET) ===\n" "$$bin"; \
		"$$bin"; \
	done

# Clean outputs except .gitkeep
clean:
	@printf "$(BLUE)Cleaning$(RESET) output directory (keeping .gitkeep)...\n"
	@$(RM) -r $(OUTDIR)/* 2>/dev/null || true
	@touch $(OUTDIR)/.gitkeep
	@printf "$(GREEN)Cleaned.$(RESET)\n"

# Show usage
help:
	@echo "Usage:"
	@echo "  make               - Build all executables"
	@echo "  make run           - Run all executables"
	@echo "  make file=src/foo.cpp     - Build a single file"
	@echo "  make file=src/foo.cpp run - Build & run single file"
	@echo "  make clean         - Remove build outputs"

.PHONY: all run clean help

# Include dependencies
-include $(DEPS)
