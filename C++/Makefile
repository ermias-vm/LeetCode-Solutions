# Makefile for C++ LeetCode Solutions

CXXFLAGS = -std=c++20 -Wall
VERIFY_SCRIPT = ../verify_output.sh
TEMP_DIR = ../tmp/C++

# Create tmp directory (only once per make invocation)
$(shell mkdir -p $(TEMP_DIR))

all:

compile:
	@echo "Error: No number specified."
	@echo "Please specify a problem number as part of the command."
	@echo "Usage: make compile<problem_number>"
	@echo "Example: make compile1   # This will compile the solution for problem number 1"

compile%:
	@N=$(subst compile,,$@); \
    if [ -z "$$N" ]; then \
        echo "Unexpected error: No number extracted."; \
    else \
        SOURCE_FILE=$$(find . -type f -name "$$N-*.cc" | head -n 1); \
        if [ -z "$$SOURCE_FILE" ]; then \
            echo "No source file found starting with $$N- and ending with .cc"; \
        else \
            OUTPUT_FILE="$${SOURCE_FILE%.cc}.x"; \
            echo "Compiling $$SOURCE_FILE to $$OUTPUT_FILE"; \
            g++ $(CXXFLAGS) "$$SOURCE_FILE" -o "$$OUTPUT_FILE"; \
        fi; \
    fi

run:
	@echo "Error: No number specified."
	@echo "Please specify a problem number as part of the command."
	@echo "Usage: make run<problem_number>"
	@echo "Example: make run1   # This will run the solution for problem number 1"

run%:
	@N=$(subst run,,$@); \
    if [ -z "$$N" ]; then \
        echo "Unexpected error: No number extracted."; \
    else \
        FILE=$$(find . -type f -name "$$N-*.x" | head -n 1); \
        if [ -z "$$FILE" ]; then \
            echo "No file found starting with $$N- and ending with .x"; \
        else \
            DIFFICULTY=$$(dirname "$$FILE" | sed 's|^\\./||'); \
            echo "Running file $$FILE"; \
            TMP_OUTPUT="$(TEMP_DIR)/$$N.txt"; \
            "./$$FILE" | tee "$$TMP_OUTPUT"; \
            "$(VERIFY_SCRIPT)" "$$N" "$$TMP_OUTPUT" "$$DIFFICULTY"; \
            if [ "$(KEEP_TMP)" != "1" ]; then rm -f "$$TMP_OUTPUT"; fi; \
        fi; \
    fi

%:
	@$(MAKE) --no-print-directory compile$@
	@$(MAKE) --no-print-directory run$@
	@$(MAKE) --no-print-directory clean$@
 


find:
	@echo "Error: No number specified."
	@echo "Please specify a problem number as part of the command."
	@echo "Usage: make find<problem_number>"
	@echo "Example: make find1   # This will find the path for the problem number 1"

find%:
	@N=$(subst find,,$@); \
    FILE=$$(find . -type f -name "$$N-*.cc" | head -n 1); \
    if [ -z "$$FILE" ]; then \
        echo "No file found starting with $$N- and ending with .cc"; \
    else \
        echo "Found file: $$FILE"; \
    fi

clean%:
	@N=$(subst clean,,$@); \
    FILE=$$(find . -type f -name "$$N-*.x" | head -n 1); \
    if [ -n "$$FILE" ]; then \
        rm -f "$$FILE"; \
    else \
        echo "No file found starting with $$N- and ending with .x to delete."; \
    fi

clean_all:
	rm -f $(shell find . -type f -name '*.x')