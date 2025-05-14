# Makefile for Java LeetCode Solutions (main class always Solution, test runner is Test)

JC = javac
JVM = java
JFLAGS =

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
	echo "Compiling $$SOURCE_FILE"; \
	$(JC) $(JFLAGS) "$$SOURCE_FILE"

# Run the Test class for the given problem number
run%:
	@N=$*; \
	CLASS_FILE=$$(find . -type f -name "Test.class" -print -quit); \
	if [ -z "$$CLASS_FILE" ]; then \
		$(MAKE) --no-print-directory compile$$N; \
		CLASS_FILE=$$(find . -type f -name "Test.class" -print -quit); \
		if [ -z "$$CLASS_FILE" ]; then \
			echo "Compilation failed or Test.class not found."; exit 1; \
		fi; \
	fi; \
	CLASS_DIR=$$(dirname "$$CLASS_FILE"); \
	echo "Running Test (from $$CLASS_DIR)"; \
	$(JVM) -cp "$$CLASS_DIR" Test

# Clean the Solution.class and Test.class files for the given problem number
clean%:
	@N=$*; \
	for CLASS in Solution Test; do \
		CLASS_FILE=$$(find . -type f -name "$$CLASS.class" -print -quit); \
		if [ -n "$$CLASS_FILE" ]; then \
			echo "Deleting $$CLASS_FILE"; \
			rm -f "$$CLASS_FILE"; \
		fi; \
	done

clean_all:
	@echo "Deleting all Solution.class and Test.class files..."; \
	find . -name "Solution.class" -type f -delete; \
	find . -name "Test.class" -type f -delete; \
	echo "All class files deleted."

# Main target: make <problem_number>
%:
	@PROBLEM_NUM=$@; \
	if echo "$$PROBLEM_NUM" | grep -Eq '^[0-9]+$$'; then \
		echo "Processing problem #$$PROBLEM_NUM"; \
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

.PHONY: all compile run clean clean_all compile% run% clean%
