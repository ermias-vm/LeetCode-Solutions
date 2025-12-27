# Root Makefile - Redirects commands to language-specific directories
# Usage:
#   make <problem_number>           -> Uses DEFAULT_LANG (C by default)
#   make <problem_number> c         -> Uses C/Makefile
#   make <problem_number> c++       -> Uses C++/Makefile
#   make <problem_number> java      -> Uses Java/Makefile
#   make <problem_number> python    -> Uses Python/Makefile
#   make format                     -> Format all source files
#   make format c++                 -> Format only C++ files
#   make format java                -> Format only Java files
#   make format python              -> Format only Python files

# Default language directory (c, c++, java, python)
DEFAULT_LANG ?= c

# Map language names to directories
lang_to_dir = $(if $(filter c,$1),C,$(if $(filter c++,$1),C++,$(if $(filter java,$1),Java,$(if $(filter python,$1),Python,$(error Unknown language: $1)))))

# Detect if second argument is a language
LANG_ARGS := c c++ java python
SECOND_ARG := $(word 2,$(MAKECMDGOALS))
IS_LANG := $(filter $(SECOND_ARG),$(LANG_ARGS))

# Determine target directory
ifeq ($(IS_LANG),)
    TARGET_DIR := $(call lang_to_dir,$(DEFAULT_LANG))
else
    TARGET_DIR := $(call lang_to_dir,$(IS_LANG))
endif

# Default target - show help
.DEFAULT_GOAL := help

help:
	@echo "╔══════════════════════════════════════════════════════════════════╗"
	@echo "║           LeetCode Solutions - Root Makefile                     ║"
	@echo "╠══════════════════════════════════════════════════════════════════╣"
	@echo "║ Usage:                                                           ║"
	@echo "║   make <number>              Run problem with default lang ($(DEFAULT_LANG))   ║"
	@echo "║   make <number> c            Run problem in C                    ║"
	@echo "║   make <number> c++          Run problem in C++                  ║"
	@echo "║   make <number> java         Run problem in Java                 ║"
	@echo "║   make <number> python       Run problem in Python               ║"
	@echo "║                                                                  ║"
	@echo "║ Examples:                                                        ║"
	@echo "║   make 153                   Run problem 153 (default: $(DEFAULT_LANG))        ║"
	@echo "║   make 1 java                Run problem 1 in Java               ║"
	@echo "║   make 42 c++                Run problem 42 in C++               ║"
	@echo "║                                                                  ║"
	@echo "║ Other commands:                                                  ║"
	@echo "║   make format                Format all source files             ║"
	@echo "║   make format-all            Format all languages (detailed)     ║"
	@echo "║   make format c              Format only C files                 ║"
	@echo "║   make format c++            Format only C++ files               ║"
	@echo "║   make format java           Format only Java files              ║"
	@echo "║   make format python         Format only Python files            ║"
	@echo "║   make clean_all             Clean all in default language       ║"
	@echo "║   make clean_all <lang>      Clean all in specified language     ║"
	@echo "║   make find<N>               Find problem N in default language  ║"
	@echo "║   make find<N> <lang>        Find problem N in specified lang    ║"
	@echo "╚══════════════════════════════════════════════════════════════════╝"

# Format target
format:
ifeq ($(IS_LANG),)
	@echo "Formatting all source files..."
	@$(MAKE) --no-print-directory _do_format_c DIRS="C C++"
	@$(MAKE) -C Java --no-print-directory format
	@$(MAKE) -C Python --no-print-directory format
else ifeq ($(IS_LANG),java)
	@$(MAKE) -C Java --no-print-directory format
else ifeq ($(IS_LANG),python)
	@$(MAKE) -C Python --no-print-directory format
else
	@echo "Formatting $(IS_LANG) source files..."
	@$(MAKE) --no-print-directory _do_format_c DIRS="$(TARGET_DIR)"
endif

# Internal format target for C/C++
_do_format_c:
	@modified_files=""; \
	for dir in $(DIRS); do \
		echo "  Processing $$dir/..."; \
		if [ "$$dir" = "C" ]; then \
			EXT="c"; \
		elif [ "$$dir" = "C++" ]; then \
			EXT="cc"; \
		else \
			continue; \
		fi; \
		for file in $$(find $$dir -name "*.$$EXT" -type f); do \
			if [ -f "$$file" ]; then \
				cp "$$file" "$$file.bak"; \
				clang-format -i "$$file" 2>/dev/null || true; \
				if ! cmp -s "$$file" "$$file.bak"; then \
					modified_files="$$modified_files$$file (clang-format)\n"; \
				fi; \
				rm -f "$$file.bak"; \
			fi; \
		done; \
		for file in $$(find $$dir -name "*.h" -type f); do \
			if [ -f "$$file" ]; then \
				cp "$$file" "$$file.bak"; \
				clang-format -i "$$file" 2>/dev/null || true; \
				if ! cmp -s "$$file" "$$file.bak"; then \
					modified_files="$$modified_files$$file (clang-format)\n"; \
				fi; \
				rm -f "$$file.bak"; \
			fi; \
		done; \
		echo "  Ensuring all source files end with newline..."; \
		for file in $$(find $$dir \( -name "*.$$EXT" -o -name "*.h" \) -type f); do \
			if [ -s "$$file" ] && [ "$$(tail -c1 "$$file" | wc -l)" -eq 0 ]; then \
				modified_files="$$modified_files$$file (added final newline)\n"; \
				echo >> "$$file"; \
			fi; \
		done; \
	done; \
	echo ""; \
	echo "Formatting complete!"; \
	echo ""; \
	echo "Modified files:"; \
	if [ -n "$$modified_files" ]; then \
		printf "$$modified_files" | sed 's/^/  - /'; \
	else \
		echo "  No files were modified."; \
	fi

# Format all languages at once
format-all:
	@echo "=== Formatting all source files ==="
	@echo ""
	@echo "--- C files ---"
	@$(MAKE) --no-print-directory _do_format_c DIRS="C"
	@echo ""
	@echo "--- C++ files ---"
	@$(MAKE) --no-print-directory _do_format_c DIRS="C++"
	@echo ""
	@echo "--- Java files ---"
	@$(MAKE) -C Java --no-print-directory format
	@echo ""
	@echo "--- Python files ---"
	@$(MAKE) -C Python --no-print-directory format
	@echo ""
	@echo "=== All formatting complete ==="

# Format check (dry run)
format-check:
ifeq ($(IS_LANG),)
	@echo "Checking format for all source files..."
	@$(MAKE) --no-print-directory _do_format_check_c DIRS="C C++"
	@$(MAKE) -C Java --no-print-directory format-check
	@$(MAKE) -C Python --no-print-directory format-check
else ifeq ($(IS_LANG),java)
	@$(MAKE) -C Java --no-print-directory format-check
else ifeq ($(IS_LANG),python)
	@$(MAKE) -C Python --no-print-directory format-check
else
	@echo "Checking format for $(IS_LANG) source files..."
	@$(MAKE) --no-print-directory _do_format_check_c DIRS="$(TARGET_DIR)"
endif

_do_format_check_c:
	@unformatted=""; \
	for dir in $(DIRS); do \
		if [ "$$dir" = "C" ]; then \
			EXT="c"; \
		elif [ "$$dir" = "C++" ]; then \
			EXT="cc"; \
		else \
			continue; \
		fi; \
		for file in $$(find $$dir -name "*.$$EXT" -o -name "*.h" -type f); do \
			if [ -f "$$file" ]; then \
				if ! clang-format --dry-run --Werror "$$file" 2>/dev/null; then \
					unformatted="$$unformatted$$file\n"; \
				fi; \
			fi; \
		done; \
	done; \
	if [ -n "$$unformatted" ]; then \
		echo "The following files need formatting:"; \
		printf "$$unformatted" | sed 's/^/  - /'; \
		exit 1; \
	else \
		echo "All files are properly formatted!"; \
	fi

# Clean all in target directory
clean_all:
	@echo "Cleaning all in $(TARGET_DIR)..."
	$(MAKE) -C $(TARGET_DIR) clean_all

# Global clean - clean all language directories
global_clean:
	@echo "=== Global Clean ==="
	@for dir in C C++ Java Python; do \
		if [ -f "$$dir/Makefile" ]; then \
			echo "Cleaning $$dir..."; \
			$(MAKE) -C $$dir clean_all 2>/dev/null || true; \
		fi; \
	done
	@echo "=== Done ==="

# Handle language arguments (prevent "No rule to make target" error)
c c++ java python:
	@true

# Find target with optional language
find%:
	@N=$(subst find,,$@); \
	echo "Searching for problem $$N in $(TARGET_DIR)..."; \
	$(MAKE) -C $(TARGET_DIR) --no-print-directory find$$N

# Compile target with optional language
compile%:
	@N=$(subst compile,,$@); \
	echo "Compiling problem $$N in $(TARGET_DIR)..."; \
	$(MAKE) -C $(TARGET_DIR) --no-print-directory compile$$N

# Run target with optional language
run%:
	@N=$(subst run,,$@); \
	echo "Running problem $$N in $(TARGET_DIR)..."; \
	$(MAKE) -C $(TARGET_DIR) --no-print-directory run$$N

# Clean specific problem with optional language
clean%:
	@N=$(subst clean,,$@); \
	if [ "$$N" != "_all" ]; then \
		echo "Cleaning problem $$N in $(TARGET_DIR)..."; \
		$(MAKE) -C $(TARGET_DIR) --no-print-directory clean$$N; \
	fi

# Catch-all for problem numbers - redirect to appropriate Makefile
%:
	@if echo "$@" | grep -Eq '^[0-9]+$$'; then \
		echo "Running problem $@ in $(TARGET_DIR) ($(if $(IS_LANG),$(IS_LANG),$(DEFAULT_LANG)))..."; \
		echo ""; \
		$(MAKE) -C $(TARGET_DIR) --no-print-directory $@; \
	else \
		echo "Unknown target: $@"; \
		echo "Use 'make help' for usage information."; \
		exit 1; \
	fi

.PHONY: help format format-all format-check clean_all global_clean c c++ java python _do_format_c _do_format_check_c

