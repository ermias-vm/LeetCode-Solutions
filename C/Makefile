# Makefile for C LeetCode Solutions

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

all:
	@echo "Usage: make <problem_number>"
	@echo "Example: make 271  (finds e.g. 271-*.c in Easy/, Medium/, or Hard/)"
	@echo "This will compile, run, and clean up the executable."

compile:
	@echo "Error: No number specified."
	@echo "Please specify a problem number as part of the command."
	@echo "Usage: make compile<problem_number>"
	@echo "Example: make compile271   # This will compile the solution for problem number 271"

compile%:
	@N=$(subst compile,,$@); \
    if [ -z "$$N" ]; then \
        echo "Unexpected error: No number extracted."; \
    else \
        SOURCE_FILE=$$(find . -type f -name "$$N-*.c" | head -n 1); \
        if [ -z "$$SOURCE_FILE" ]; then \
            echo "No source file found starting with $$N- and ending with .c"; \
        else \
            OUTPUT_FILE="$${SOURCE_FILE%.c}.x"; \
            echo "Compiling $$SOURCE_FILE to $$OUTPUT_FILE"; \
            $(CC) $(CFLAGS) "$$SOURCE_FILE" -o "$$OUTPUT_FILE"; \
        fi; \
    fi

run:
	@echo "Error: No number specified."
	@echo "Please specify a problem number as part of the command."
	@echo "Usage: make run<problem_number>"
	@echo "Example: make run271   # This will run the solution for problem number 271"

run%:
	@N=$(subst run,,$@); \
    if [ -z "$$N" ]; then \
        echo "Unexpected error: No number extracted."; \
    else \
        FILE=$$(find . -type f -name "$$N-*.x" | head -n 1); \
        if [ -z "$$FILE" ]; then \
            echo "No executable found starting with $$N- and ending with .x"; \
        else \
            echo "Running file $$FILE"; \
            "./$$FILE"; \
        fi; \
    fi

# Main target: make <problem_number>
%:
	@$(MAKE) --no-print-directory compile$@
	@$(MAKE) --no-print-directory run$@
	@$(MAKE) --no-print-directory clean$@

find:
	@echo "Error: No number specified."
	@echo "Please specify a problem number as part of the command."
	@echo "Usage: make find<problem_number>"
	@echo "Example: make find271   # This will find the path for the problem number 271"

find%:
	@N=$(subst find,,$@); \
    FILE=$$(find . -type f -name "$$N-*.c" | head -n 1); \
    if [ -z "$$FILE" ]; then \
        echo "No file found starting with $$N- and ending with .c"; \
    else \
        echo "Found file: $$FILE"; \
    fi

clean%:
	@N=$(subst clean,,$@); \
    FILE=$$(find . -type f -name "$$N-*.x" | head -n 1); \
    if [ -n "$$FILE" ]; then \
        echo "Deleting $$FILE"; \
        rm -f "$$FILE"; \
    else \
        echo "No executable found starting with $$N- and ending with .x to delete."; \
    fi

clean_all:
	@echo "Deleting all executable files (.x)..."
	@find . -name "*.x" -type f -delete
	@echo "All executable files deleted."

.PHONY: all compile run find clean_all compile% run% clean% find%
