# Makefile for Java LeetCode Solutions (main class always Solution, test runner is Test)

JC = javac
JVM = java
JFLAGS =
VERIFY_SCRIPT = ../verify_output.sh
TEMP_DIR = ../tmp/Java

# Create tmp directory (only once per make invocation)
$(shell mkdir -p $(TEMP_DIR))

all:
	@echo "Usage: make <problem_number>"
	@echo "Example: make 1 (finds e.g. 1-TwoSum.java in Easy/, Medium/, or Hard/)"

# Compile the Java file for the given problem number
compile%:
	@N=$*; \
	SOURCE_FILE=$$(find . -type f -name "$$N-*.java" -print -quit); \
	if [ -z "$$SOURCE_FILE" ]; then \
		echo "No source file found for problem $$N (e.g., $$N-*.java)."; exit 1; \
	fi; \
	CLASS_DIR=$$(dirname "$$SOURCE_FILE"); \
	echo "Compiling $$SOURCE_FILE to $$CLASS_DIR/Test.class"; \
	$(JC) $(JFLAGS) "$$SOURCE_FILE"

# Run the Test class for the given problem number
run%:
	@N=$*; \
	SOURCE_FILE=$$(find . -type f -name "$$N-*.java" -print -quit); \
	DIFFICULTY=$$(dirname "$$SOURCE_FILE" | sed 's|^\\./||'); \
	CLASS_FILE=$$(find . -type f -name "Test.class" -print -quit); \
	if [ -z "$$CLASS_FILE" ]; then \
		$(MAKE) --no-print-directory compile$$N; \
		CLASS_FILE=$$(find . -type f -name "Test.class" -print -quit); \
		if [ -z "$$CLASS_FILE" ]; then \
			echo "Compilation failed or Test.class not found."; exit 1; \
		fi; \
	fi; \
	CLASS_DIR=$$(dirname "$$CLASS_FILE"); \
	echo "Running file $$CLASS_DIR/Test.class"; \
	TMP_OUTPUT="$(TEMP_DIR)/$$N.txt"; \
	$(JVM) -cp "$$CLASS_DIR" Test | tee "$$TMP_OUTPUT"; \
	"$(VERIFY_SCRIPT)" "$$N" "$$TMP_OUTPUT" "$$DIFFICULTY"; \
	if [ "$(KEEP_TMP)" != "1" ]; then rm -f "$$TMP_OUTPUT"; fi

# Clean the Solution.class and Test.class files for the given problem number
clean%:
	@N=$*; \
	SOURCE_FILE=$$(find . -type f -name "$$N-*.java" -print -quit); \
	if [ -n "$$SOURCE_FILE" ]; then \
		CLASS_DIR=$$(dirname "$$SOURCE_FILE"); \
		for CLASS in Solution Test; do \
			CLASS_FILE="$$CLASS_DIR/$$CLASS.class"; \
			if [ -f "$$CLASS_FILE" ]; then \
				echo "Deleting $$CLASS_FILE"; \
				rm -f "$$CLASS_FILE"; \
			fi; \
		done; \
	fi

clean_all:
	@echo "Deleting all Solution.class and Test.class files..."; \
	find . -name "Solution.class" -type f -delete; \
	find . -name "Test.class" -type f -delete; \
	echo "All class files deleted."

# Main target: make <problem_number>
%:
	@PROBLEM_NUM=$@; \
	if echo "$$PROBLEM_NUM" | grep -Eq '^[0-9]+$$'; then \
		$(MAKE) --no-print-directory compile$$PROBLEM_NUM; \
		$(MAKE) --no-print-directory run$$PROBLEM_NUM; \
		$(MAKE) --no-print-directory clean$$PROBLEM_NUM; \
	else \
		$(MAKE) $$PROBLEM_NUM; \
	fi

find:
	@echo "Error: No number specified."
	@echo "Please specify a problem number as part of the command."
	@echo "Usage: make find<problem_number>"
	@echo "Example: make find1   # This will find the path for the problem number 1"

find%:
	@N=$*; \
	FILE=$$(find . -type f -name "$$N-*.java" | head -n 1); \
	if [ -z "$$FILE" ]; then \
		echo "No file found starting with $$N- and ending with .java"; \
	else \
		echo "Found file: $$FILE"; \
	fi

# Format all Java files using clang-format (uses ../.clang-format config)
format:
	@echo "Formatting Java/..."
	@modified_files=""; \
	for file in $$(find . -name "*.java" -type f); do \
		if [ -f "$$file" ]; then \
			cp "$$file" "$$file.bak"; \
			clang-format -i "$$file" 2>/dev/null || true; \
			if ! cmp -s "$$file" "$$file.bak"; then \
				modified_files="$$modified_files$$file (clang-format)\n"; \
			fi; \
			rm -f "$$file.bak"; \
		fi; \
	done; \
	echo "Ensuring all Java files end with newline..."; \
	for file in $$(find . -name "*.java" -type f); do \
		if [ -s "$$file" ] && [ "$$(tail -c1 "$$file" | wc -l)" -eq 0 ]; then \
			modified_files="$$modified_files$$file (added final newline)\n"; \
			echo >> "$$file"; \
		fi; \
	done; \
	echo ""; \
	echo "Formatting complete!"; \
	echo ""; \
	if [ -n "$$modified_files" ]; then \
		echo "Modified files Java:"; \
		printf "$$modified_files" | sed 's/^/  - /'; \
	else \
		echo "No files were modified."; \
	fi

format-check:
	@echo "Checking format for all Java source files..."
	@unformatted=""; \
	for file in $$(find . -name "*.java" -type f); do \
		if [ -f "$$file" ]; then \
			if ! clang-format --dry-run --Werror "$$file" 2>/dev/null; then \
				unformatted="$$unformatted$$file\n"; \
			fi; \
		fi; \
	done; \
	if [ -n "$$unformatted" ]; then \
		echo "The following files need formatting:"; \
		printf "$$unformatted" | sed 's/^/  - /'; \
		exit 1; \
	else \
		echo "All files are properly formatted!"; \
	fi

.PHONY: all compile run clean clean_all compile% run% clean% format format-check
