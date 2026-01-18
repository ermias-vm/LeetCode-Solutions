# Root Makefile - Redirects commands to language-specific directories
# Usage:
#   make <problem_number>           -> Uses DEFAULT_LANG (C by default)
#   make <problem_number> c         -> Uses C/Makefile
#   make <problem_number> c++       -> Uses C++/Makefile
#   make <problem_number> java      -> Uses Java/Makefile
#   make <number> <lang>            -> Run problem in specified language
#   make verify <lang>              -> Verify all problems (saves to Out/logs/)
#   make summary                    -> Show summary (saves to Out/)
#   make clean out                  -> Delete Out/ folder (with confirmation)
#   make format                     -> Format all source files
#   make format c++                 -> Format only C++ files

# Default language directory (c, c++, java)
DEFAULT_LANG ?= c

# Output directories
OUT_DIR = Out
LOGS_DIR = $(OUT_DIR)/logs
TEMP_DIR = $(OUT_DIR)/tmp

# Map language names to directories
lang_to_dir = $(if $(filter c,$1),C,$(if $(filter c++,$1),C++,$(if $(filter java,$1),Java,$(error Unknown language: $1))))

# Detect if second argument is a language
LANG_ARGS := c c++ java
SECOND_ARG := $(word 2,$(MAKECMDGOALS))
THIRD_ARG := $(word 3,$(MAKECMDGOALS))
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
	@echo "╔═══════════════════════════════════════════════════════════════════════╗"
	@echo "║              LeetCode Solutions - Root Makefile                       ║"
	@echo "╠═══════════════════════════════════════════════════════════════════════╣"
	@echo "║ Usage:                                                                ║"
	@echo "║   make <number>              Run problem with default lang ($(DEFAULT_LANG))        ║"
	@echo "║   make <number> c            Run problem in C                         ║"
	@echo "║   make <number> c++          Run problem in C++                       ║"
	@echo "║   make <number> java         Run problem in Java                      ║"
	@echo "║                                                                       ║"
	@echo "║ Examples:                                                             ║"
	@echo "║   make 153                   Run problem 153 (default: $(DEFAULT_LANG))             ║"
	@echo "║   make 1 java                Run problem 1 in Java                    ║"
	@echo "║   make 42 c++                Run problem 42 in C++                    ║"
	@echo "║                                                                       ║"
	@echo "║ Verification & Summary:                                               ║"
	@echo "║   make verify all            Verify all (C, C++, Java) -> Out/logs/   ║"
	@echo "║   make verify c              Verify C solutions -> Out/logs/          ║"
	@echo "║   make verify c++            Verify C++ solutions -> Out/logs/        ║"
	@echo "║   make verify java           Verify Java solutions -> Out/logs/       ║"
	@echo "║   make summary               Show & save summary -> Out/              ║"
	@echo "║                                                                       ║"
	@echo "║ Other commands:                                                       ║"
	@echo "║   make format                Format all source files                  ║"
	@echo "║   make format c              Format only C files                      ║"
	@echo "║   make format c++            Format only C++ files                    ║"
	@echo "║   make format java           Format only Java files                   ║"
	@echo "║   make clean_all             Clean all in default language            ║"
	@echo "║   make clean_all <lang>      Clean all in specified language          ║"
	@echo "║   make clean out             Delete Out/ folder                       ║"
	@echo "║   make find<N>               Find problem N in default language       ║"
	@echo "║   make find<N> <lang>        Find problem N in specified lang         ║"
	@echo "╚═══════════════════════════════════════════════════════════════════════╝"

# Format target - runs format-all by default
format:
ifeq ($(IS_LANG),)
	@$(MAKE) --no-print-directory format-all
else ifeq ($(IS_LANG),java)
	@$(MAKE) -C Java --no-print-directory format
else
	@echo "Formatting $(IS_LANG) source files..."
	@echo ""
	@$(MAKE) --no-print-directory _do_format_c DIRS="$(TARGET_DIR)"
endif

# Internal format target for C/C++
_do_format_c:
	@modified_files=""; \
	for dir in $(DIRS); do \
		echo "Formatting $$dir/..."; \
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
		echo "Ensuring all $$dir files end with newline..."; \
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
	if [ -n "$$modified_files" ]; then \
		echo "Modified files $$dir:"; \
		printf "$$modified_files" | sed 's/^/  - /'; \
	else \
		echo "No files were modified."; \
	fi

# Format all languages at once
format-all:
	@echo "Formatting all source files..."
	@echo ""
	@$(MAKE) --no-print-directory _do_format_c DIRS="C"
	@echo ""
	@echo ""
	@$(MAKE) --no-print-directory _do_format_c DIRS="C++"
	@echo ""
	@echo ""
	@$(MAKE) -C Java --no-print-directory format
	@echo ""
	@echo "Formatting complete!"

# Format check (dry run)
format-check:
ifeq ($(IS_LANG),)
	@echo "Checking format for all source files..."
	@$(MAKE) --no-print-directory _do_format_check_c DIRS="C C++"
	@$(MAKE) -C Java --no-print-directory format-check
else ifeq ($(IS_LANG),java)
	@$(MAKE) -C Java --no-print-directory format-check
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

# Clean Out folder with confirmation
clean:
ifeq ($(SECOND_ARG),out)
	@if [ -d "$(OUT_DIR)" ]; then \
		rm -rI "$(OUT_DIR)"; \
	else \
		echo "$(OUT_DIR)/ folder does not exist."; \
	fi
else
	@echo "Usage: make clean out"
endif

# Handle 'out' as a target argument
out:
	@true

# Global clean - clean all language directories
global_clean:
	@echo "=== Global Clean ==="
	@for dir in C C++ Java; do \
		if [ -f "$$dir/Makefile" ]; then \
			echo "Cleaning $$dir..."; \
			$(MAKE) -C $$dir clean_all 2>/dev/null || true; \
		fi; \
	done
	@echo "=== Done ==="

# Handle language arguments (prevent "No rule to make target" error)
c c++ java:
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
		$(MAKE) -C $(TARGET_DIR) --no-print-directory KEEP_TMP=0 $@; \
	else \
		echo "Unknown target: $@"; \
		echo "Use 'make help' for usage information."; \
	fi

.PHONY: help format format-all format-check clean_all clean global_clean c c++ java out _do_format_c _do_format_check_c summary _summary_output verify all

# Summary - Show table with problem counts by language and difficulty
# Always saves to Out/Solutions_summary.txt
summary:
	@mkdir -p $(OUT_DIR)
	@$(MAKE) --no-print-directory _summary_output | tee $(OUT_DIR)/Solutions_summary.txt
	@echo ""
	@echo "   Summary saved to: $(OUT_DIR)/Solutions_summary.txt"

_summary_output:
	@echo ""
	@echo "   LeetCode Solutions - Summary:"
	@echo ""
	@# Count files per language and difficulty
	@c_easy=$$(find C/Easy -name "*.c" 2>/dev/null | wc -l); \
	c_medium=$$(find C/Medium -name "*.c" 2>/dev/null | wc -l); \
	c_hard=$$(find C/Hard -name "*.c" 2>/dev/null | wc -l); \
	c_total=$$((c_easy + c_medium + c_hard)); \
	cpp_easy=$$(find C++/Easy -name "*.cc" 2>/dev/null | wc -l); \
	cpp_medium=$$(find C++/Medium -name "*.cc" 2>/dev/null | wc -l); \
	cpp_hard=$$(find C++/Hard -name "*.cc" 2>/dev/null | wc -l); \
	cpp_total=$$((cpp_easy + cpp_medium + cpp_hard)); \
	java_easy=$$(find Java/Easy -name "*.java" 2>/dev/null | wc -l); \
	java_medium=$$(find Java/Medium -name "*.java" 2>/dev/null | wc -l); \
	java_hard=$$(find Java/Hard -name "*.java" 2>/dev/null | wc -l); \
	java_total=$$((java_easy + java_medium + java_hard)); \
	test_easy=$$(find ExpectedOutputs/Easy -name "*.txt" 2>/dev/null | wc -l); \
	test_medium=$$(find ExpectedOutputs/Medium -name "*.txt" 2>/dev/null | wc -l); \
	test_hard=$$(find ExpectedOutputs/Hard -name "*.txt" 2>/dev/null | wc -l); \
	test_total=$$((test_easy + test_medium + test_hard)); \
	total_easy=$$((c_easy + cpp_easy + java_easy)); \
	total_medium=$$((c_medium + cpp_medium + java_medium)); \
	total_hard=$$((c_hard + cpp_hard + java_hard)); \
	grand_total=$$((c_total + cpp_total + java_total)); \
	echo   "  ┌────────────┬────────┬────────┬────────┬────────┐"; \
	printf "  │ %-10s │ %6s │ %6s │ %6s │ %6s │\n" "Language" "Easy" "Medium" "Hard" "Total"; \
	echo   "  ├────────────┼────────┼────────┼────────┼────────┤"; \
	printf "  │ %-10s │ %6d │ %6d │ %6d │ %6d │\n" "C" $$c_easy $$c_medium $$c_hard $$c_total; \
	printf "  │ %-10s │ %6d │ %6d │ %6d │ %6d │\n" "C++" $$cpp_easy $$cpp_medium $$cpp_hard $$cpp_total; \
	printf "  │ %-10s │ %6d │ %6d │ %6d │ %6d │\n" "Java" $$java_easy $$java_medium $$java_hard $$java_total; \
	echo   "  ├────────────┼────────┼────────┼────────┼────────┤"; \
	printf "  │ %-10s │ %6d │ %6d │ %6d │ %6d │\n" "Total" $$total_easy $$total_medium $$total_hard $$grand_total; \
	echo   "  ├────────────┼────────┼────────┼────────┼────────┤"; \
	printf "  │ %-10s │ %6d │ %6d │ %6d │ %6d │\n" "Tests" $$test_easy $$test_medium $$test_hard $$test_total; \
	echo   "  └────────────┴────────┴────────┴────────┴────────┘"; \
	echo ""
	@echo ""
	@echo "   Problems Detail:"
	@echo ""
	@# Get all unique problem numbers and their names
	@all_problems=$$(find C C++ Java -name "*-*.c" -o -name "*-*.cc" -o -name "*-*.java" 2>/dev/null | \
		sed 's|.*/||' | sed 's|\.[^.]*$$||' | sort -t'-' -k1 -n | uniq); \
	problem_count=$$(echo "$$all_problems" | wc -w); \
	echo   "  ┌──────┬──────────────────────────────────────────────┬────────┬──────┬──────┬──────┬──────┐"; \
	printf "  │ %-4s │ %-44s │ %-6s │ %-4s │ %-4s │ %-4s │ %-4s │\n" "#" "Problem" "Level" " C " " C++" "Java" "Test"; \
	echo   "  ├──────┼──────────────────────────────────────────────┼────────┼──────┼──────┼──────┼──────┤"; \
	first=1; \
	for problem in $$all_problems; do \
		num=$$(echo "$$problem" | cut -d'-' -f1); \
		name=$$(echo "$$problem" | cut -d'-' -f2-); \
		level=""; \
		if find C/Easy C++/Easy Java/Easy -name "$$num-*" 2>/dev/null | grep -q .; then level="Easy"; fi; \
		if find C/Medium C++/Medium Java/Medium -name "$$num-*" 2>/dev/null | grep -q .; then level="Medium"; fi; \
		if find C/Hard C++/Hard Java/Hard -name "$$num-*" 2>/dev/null | grep -q .; then level="Hard"; fi; \
		c_exists="  "; cpp_exists="  "; java_exists="  "; test_exists="  "; \
		if find C -name "$$num-*.c" 2>/dev/null | grep -q .; then c_exists="OK"; fi; \
		if find C++ -name "$$num-*.cc" 2>/dev/null | grep -q .; then cpp_exists="OK"; fi; \
		if find Java -name "$$num-*.java" 2>/dev/null | grep -q .; then java_exists="OK"; fi; \
		if find ExpectedOutputs -name "$$num.txt" 2>/dev/null | grep -q .; then test_exists="OK"; fi; \
		if [ $$first -eq 0 ]; then \
			echo   "  ├──────┼──────────────────────────────────────────────┼────────┼──────┼──────┼──────┼──────┤"; \
		fi; \
		first=0; \
		printf "  │ %4s │ %-44s │ %-6s │  %s  │  %s  │  %s  │  %s  │\n" "$$num" "$$name" "$$level" "$$c_exists" "$$cpp_exists" "$$java_exists" "$$test_exists"; \
	done; \
	echo   "  └──────┴──────────────────────────────────────────────┴────────┴──────┴──────┴──────┴──────┘"; \
	echo ""; \
	echo "   Total distinct problems: $$problem_count"; \
	echo "";

# Verify - Run all problems with expected outputs and show results table
# Always saves to Out/logs/ with timestamp
# Usage: make verify all | make verify c | make verify c++ | make verify java
verify:
ifeq ($(SECOND_ARG),all)
	@$(MAKE) --no-print-directory _verify_all LANGS="c c++ java" OUT_PREFIX="All"
else ifeq ($(SECOND_ARG),c)
	@$(MAKE) --no-print-directory _verify_all LANGS="c" OUT_PREFIX="C"
else ifeq ($(SECOND_ARG),c++)
	@$(MAKE) --no-print-directory _verify_all LANGS="c++" OUT_PREFIX="C++"
else ifeq ($(SECOND_ARG),java)
	@$(MAKE) --no-print-directory _verify_all LANGS="java" OUT_PREFIX="Java"
else
	@echo "Usage: make verify <all|c|c++|java>"
	@echo ""
	@echo "Examples:"
	@echo "  make verify all       Verify all problems in C, C++, and Java"
	@echo "  make verify c         Verify only C problems"
	@echo "  make verify c++       Verify only C++ problems"
	@echo "  make verify java      Verify only Java problems"
	@echo ""
	@echo "Results are saved to Out/logs/ with timestamp"
endif

# Handle 'all' as a target argument
all:
	@true

_verify_all:
	@mkdir -p $(LOGS_DIR) $(TEMP_DIR)/C $(TEMP_DIR)/C++ $(TEMP_DIR)/Java
	@timestamp=$$(date +%Y%m%d_%H%M%S); \
	outfile="$(LOGS_DIR)/$(OUT_PREFIX)_TestResults_$$timestamp.txt"; \
	echo "" | tee "$$outfile"; \
	echo "═══════════════════════════════════════════════════════════════════════════════" | tee -a "$$outfile"; \
	echo "   Verification Results - $(OUT_PREFIX)" | tee -a "$$outfile"; \
	echo "   Timestamp: $$timestamp" | tee -a "$$outfile"; \
	echo "═══════════════════════════════════════════════════════════════════════════════" | tee -a "$$outfile"; \
	echo "" | tee -a "$$outfile"; \
	verify_c="no"; verify_cpp="no"; verify_java="no"; \
	for lang in $(LANGS); do \
		if [ "$$lang" = "c" ]; then verify_c="yes"; fi; \
		if [ "$$lang" = "c++" ]; then verify_cpp="yes"; fi; \
		if [ "$$lang" = "java" ]; then verify_java="yes"; fi; \
	done; \
	all_problems=$$(find ExpectedOutputs -name "*.txt" 2>/dev/null | sed 's|.*/||' | sed 's|\.txt$$||' | sort -n | uniq); \
	c_results=""; cpp_results=""; java_results=""; \
	for num in $$all_problems; do \
		for lang in $(LANGS); do \
			if [ "$$lang" = "c" ]; then \
				src=$$(find C -name "$$num-*.c" 2>/dev/null | head -n 1); \
				if [ -n "$$src" ]; then \
					dir=$$(dirname "$$src"); \
					difficulty=$$(basename "$$dir"); \
					name=$$(basename "$$src" .c | cut -d'-' -f2-); \
					echo "Testing [C] Problem $$num - $$name..." | tee -a "$$outfile"; \
					exe="$${src%.c}.x"; \
					gcc -std=c11 -Wall -o "$$exe" "$$src" 2>/dev/null; \
					if [ -f "$$exe" ]; then \
						tmp="$(TEMP_DIR)/C/$$num.txt"; \
						"./$$exe" > "$$tmp" 2>&1; \
						expected_file="ExpectedOutputs/$$difficulty/$$num.txt"; \
						if [ -f "$$expected_file" ]; then \
							num_expected=$$(head -n 1 "$$expected_file"); \
							errors=0; \
							for i in $$(seq 1 $$num_expected); do \
								actual=$$(grep "^Output:" "$$tmp" | sed -n "$${i}p" | sed 's/^Output: //'); \
								expected=$$(sed -n "$$((i+1))p" "$$expected_file"); \
								if [ "$$actual" != "$$expected" ]; then \
									errors=$$((errors + 1)); \
									echo "  Example $$i: FAIL" >> "$$outfile"; \
									echo "    Expected: $$expected" >> "$$outfile"; \
									echo "    Got:      $$actual" >> "$$outfile"; \
								else \
									echo "  Example $$i: PASS" >> "$$outfile"; \
								fi; \
							done; \
							if [ $$errors -eq 0 ]; then \
								echo "  Result: PASS ($$num_expected/$$num_expected)" | tee -a "$$outfile"; \
							else \
								echo "  Result: FAIL ($$errors/$$num_expected failed)" | tee -a "$$outfile"; \
							fi; \
							c_results="$$c_results$$num:$$errors "; \
						fi; \
						rm -f "$$exe"; \
					else \
						echo "  Compilation failed!" | tee -a "$$outfile"; \
					fi; \
					echo "" >> "$$outfile"; \
				fi; \
			elif [ "$$lang" = "c++" ]; then \
				src=$$(find C++ -name "$$num-*.cc" 2>/dev/null | head -n 1); \
				if [ -n "$$src" ]; then \
					dir=$$(dirname "$$src"); \
					difficulty=$$(basename "$$dir"); \
					name=$$(basename "$$src" .cc | cut -d'-' -f2-); \
					echo "Testing [C++] Problem $$num - $$name..." | tee -a "$$outfile"; \
					exe="$${src%.cc}.x"; \
					g++ -std=c++20 -Wall -o "$$exe" "$$src" 2>/dev/null; \
					if [ -f "$$exe" ]; then \
						tmp="$(TEMP_DIR)/C++/$$num.txt"; \
						"./$$exe" > "$$tmp" 2>&1; \
						expected_file="ExpectedOutputs/$$difficulty/$$num.txt"; \
						if [ -f "$$expected_file" ]; then \
							num_expected=$$(head -n 1 "$$expected_file"); \
							errors=0; \
							for i in $$(seq 1 $$num_expected); do \
								actual=$$(grep "^Output:" "$$tmp" | sed -n "$${i}p" | sed 's/^Output: //'); \
								expected=$$(sed -n "$$((i+1))p" "$$expected_file"); \
								if [ "$$actual" != "$$expected" ]; then \
									errors=$$((errors + 1)); \
									echo "  Example $$i: FAIL" >> "$$outfile"; \
									echo "    Expected: $$expected" >> "$$outfile"; \
									echo "    Got:      $$actual" >> "$$outfile"; \
								else \
									echo "  Example $$i: PASS" >> "$$outfile"; \
								fi; \
							done; \
							if [ $$errors -eq 0 ]; then \
								echo "  Result: PASS ($$num_expected/$$num_expected)" | tee -a "$$outfile"; \
							else \
								echo "  Result: FAIL ($$errors/$$num_expected failed)" | tee -a "$$outfile"; \
							fi; \
							cpp_results="$$cpp_results$$num:$$errors "; \
						fi; \
						rm -f "$$exe"; \
					else \
						echo "  Compilation failed!" | tee -a "$$outfile"; \
					fi; \
					echo "" >> "$$outfile"; \
				fi; \
			elif [ "$$lang" = "java" ]; then \
				src=$$(find Java -name "$$num-*.java" 2>/dev/null | head -n 1); \
				if [ -n "$$src" ]; then \
					dir=$$(dirname "$$src"); \
					difficulty=$$(basename "$$dir"); \
					name=$$(basename "$$src" .java | cut -d'-' -f2-); \
					echo "Testing [Java] Problem $$num - $$name..." | tee -a "$$outfile"; \
					javac "$$src" 2>/dev/null; \
					if [ -f "$$dir/Test.class" ]; then \
						tmp="$(TEMP_DIR)/Java/$$num.txt"; \
						java -cp "$$dir" Test > "$$tmp" 2>&1; \
						expected_file="ExpectedOutputs/$$difficulty/$$num.txt"; \
						if [ -f "$$expected_file" ]; then \
							num_expected=$$(head -n 1 "$$expected_file"); \
							errors=0; \
							for i in $$(seq 1 $$num_expected); do \
								actual=$$(grep "^Output:" "$$tmp" | sed -n "$${i}p" | sed 's/^Output: //'); \
								expected=$$(sed -n "$$((i+1))p" "$$expected_file"); \
								if [ "$$actual" != "$$expected" ]; then \
									errors=$$((errors + 1)); \
									echo "  Example $$i: FAIL" >> "$$outfile"; \
									echo "    Expected: $$expected" >> "$$outfile"; \
									echo "    Got:      $$actual" >> "$$outfile"; \
								else \
									echo "  Example $$i: PASS" >> "$$outfile"; \
								fi; \
							done; \
							if [ $$errors -eq 0 ]; then \
								echo "  Result: PASS ($$num_expected/$$num_expected)" | tee -a "$$outfile"; \
							else \
								echo "  Result: FAIL ($$errors/$$num_expected failed)" | tee -a "$$outfile"; \
							fi; \
							java_results="$$java_results$$num:$$errors "; \
						fi; \
						rm -f "$$dir/Test.class" "$$dir/Solution.class"; \
					else \
						echo "  Compilation failed!" | tee -a "$$outfile"; \
					fi; \
					echo "" >> "$$outfile"; \
				fi; \
			fi; \
		done; \
	done; \
	echo "" | tee -a "$$outfile"; \
	echo "═══════════════════════════════════════════════════════════════════════════════" | tee -a "$$outfile"; \
	echo "   Summary Table" | tee -a "$$outfile"; \
	echo "═══════════════════════════════════════════════════════════════════════════════" | tee -a "$$outfile"; \
	echo "" | tee -a "$$outfile"; \
	echo   "  ┌──────┬──────────────────────────────────────────────┬────────┬─────┬─────┬──────┬────────┐" | tee -a "$$outfile"; \
	printf "  │ %-4s │ %-44s │ %-6s │ %-3s │ %-3s │ %-4s │ %-6s │\n" "#" "Problem" "Level" "C" "C++" "Java" "Test" | tee -a "$$outfile"; \
	echo   "  ├──────┼──────────────────────────────────────────────┼────────┼─────┼─────┼──────┼────────┤" | tee -a "$$outfile"; \
	all_src=$$(find C C++ Java -name "*-*.c" -o -name "*-*.cc" -o -name "*-*.java" 2>/dev/null | \
		sed 's|.*/||' | sed 's|\.[^.]*$$||' | sort -t'-' -k1 -n | uniq); \
	first=1; \
	total_pass=0; total_fail=0; \
	for problem in $$all_src; do \
		num=$$(echo "$$problem" | cut -d'-' -f1); \
		name=$$(echo "$$problem" | cut -d'-' -f2-); \
		if ! find ExpectedOutputs -name "$$num.txt" 2>/dev/null | grep -q .; then continue; fi; \
		level=""; \
		if find C/Easy C++/Easy Java/Easy -name "$$num-*" 2>/dev/null | grep -q .; then level="Easy"; fi; \
		if find C/Medium C++/Medium Java/Medium -name "$$num-*" 2>/dev/null | grep -q .; then level="Medium"; fi; \
		if find C/Hard C++/Hard Java/Hard -name "$$num-*" 2>/dev/null | grep -q .; then level="Hard"; fi; \
		c_err=""; cpp_err=""; java_err=""; \
		for r in $$c_results; do \
			rnum=$$(echo "$$r" | cut -d':' -f1); \
			rval=$$(echo "$$r" | cut -d':' -f2); \
			if [ "$$rnum" = "$$num" ]; then c_err="$$rval"; fi; \
		done; \
		for r in $$cpp_results; do \
			rnum=$$(echo "$$r" | cut -d':' -f1); \
			rval=$$(echo "$$r" | cut -d':' -f2); \
			if [ "$$rnum" = "$$num" ]; then cpp_err="$$rval"; fi; \
		done; \
		for r in $$java_results; do \
			rnum=$$(echo "$$r" | cut -d':' -f1); \
			rval=$$(echo "$$r" | cut -d':' -f2); \
			if [ "$$rnum" = "$$num" ]; then java_err="$$rval"; fi; \
		done; \
		if [ $$first -eq 0 ]; then \
			echo   "  ├──────┼──────────────────────────────────────────────┼────────┼─────┼─────┼──────┼────────┤" | tee -a "$$outfile"; \
		fi; \
		first=0; \
		c_display="-"; cpp_display="-"; java_display="-"; \
		test_result="PASS"; has_test="no"; \
		if [ "$$verify_c" = "yes" ]; then \
			if [ -n "$$c_err" ]; then \
				has_test="yes"; \
				c_display="$$c_err"; \
				if [ "$$c_err" != "0" ]; then test_result="FAIL"; fi; \
			elif find C -name "$$num-*.c" 2>/dev/null | grep -q .; then \
				c_display="-"; \
			fi; \
		fi; \
		if [ "$$verify_cpp" = "yes" ]; then \
			if [ -n "$$cpp_err" ]; then \
				has_test="yes"; \
				cpp_display="$$cpp_err"; \
				if [ "$$cpp_err" != "0" ]; then test_result="FAIL"; fi; \
			elif find C++ -name "$$num-*.cc" 2>/dev/null | grep -q .; then \
				cpp_display="-"; \
			fi; \
		fi; \
		if [ "$$verify_java" = "yes" ]; then \
			if [ -n "$$java_err" ]; then \
				has_test="yes"; \
				java_display="$$java_err"; \
				if [ "$$java_err" != "0" ]; then test_result="FAIL"; fi; \
			elif find Java -name "$$num-*.java" 2>/dev/null | grep -q .; then \
				java_display="-"; \
			fi; \
		fi; \
		if [ "$$has_test" = "yes" ]; then \
			if [ "$$test_result" = "PASS" ]; then \
				total_pass=$$((total_pass + 1)); \
			else \
				total_fail=$$((total_fail + 1)); \
			fi; \
		else \
			test_result="-"; \
		fi; \
		printf "  │ %4s │ %-44s │ %-6s │  %s  │  %s  │  %s   │ %-6s │\n" "$$num" "$$name" "$$level" "$$c_display" "$$cpp_display" "$$java_display" "$$test_result" | tee -a "$$outfile"; \
	done; \
	echo   "  └──────┴──────────────────────────────────────────────┴────────┴─────┴─────┴──────┴────────┘" | tee -a "$$outfile"; \
	echo "" | tee -a "$$outfile"; \
	echo "   Summary: $$total_pass passed, $$total_fail failed" | tee -a "$$outfile"; \
	echo "" | tee -a "$$outfile"; \
	if [ $$total_fail -eq 0 ]; then \
		final_file="$(LOGS_DIR)/$(OUT_PREFIX)_TestResults_PASS_$$timestamp.txt"; \
	else \
		final_file="$(LOGS_DIR)/$(OUT_PREFIX)_TestResults_FAIL_$$timestamp.txt"; \
	fi; \
	mv "$$outfile" "$$final_file"; \
	echo "   Output saved to: $$final_file";
