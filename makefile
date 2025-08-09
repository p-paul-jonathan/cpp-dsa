# Makefile

CXX      := g++
CXXFLAGS := -Wall -Wextra -O2 -Ilib
SRCDIR   := src
LIBDIR   := lib
OUTDIR   := output

# Find all .cpp files in src/
SRCS     := $(shell find $(SRCDIR) -type f -name "*.cpp")
# Map them to executables files in output/
OBJS     := $(SRCS:$(SRCDIR)/%.cpp=$(OUTDIR)/%.out)

# Default target: build all
all: $(OBJS)

# Compile each .cpp into matching .out, preserving directory structure
$(OUTDIR)/%.out: $(SRCDIR)/%.cpp $(shell find $(LIBDIR) -type f -name "*.h")
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Done."

# Run all output files
run: all
	@echo "Running all programs..."
	@for bin in $(OBJS); do \
		echo "=== Running $$bin ==="; \
		$$bin; \
		echo ""; \
	done
	@echo "Done."

# Clean everything except .gitkeep and output directory
clean:
	@echo "Cleaning output directory (keeping .gitkeep)..."
	@find $(OUTDIR) -mindepth 1 ! -name '.gitkeep' -delete
	@find $(OUTDIR) -type d -empty -delete
	@echo "Cleaned."

.PHONY: all run clean
