# Makefile for Python Solutions

# Default Python interpreter
PYTHON = python3

# Default target
all:
	@echo "Usage: make <problem_number>"
	@echo "Example: make 20  (finds e.g. 20-my_solution.py in Easy/, Medium/, or Hard/)"
	@echo "This will run the script and clean up __pycache__ and .pyc files."

# Compile target (Python is interpreted, but we keep it for consistency)
compile%:
	@N=$*; \
	SCRIPT_FILE=$$(find . -path ./venv -prune -o -type f -name "$$N-*.py" -print -quit); \
	if [ -z "$$SCRIPT_FILE" ]; then \
		echo "No Python script file found for problem $$N"; \
		exit 1; \
	fi; \
	echo "Compiling $$SCRIPT_FILE (syntax check)"; \
	$(PYTHON) -m py_compile "$$SCRIPT_FILE"

# Run a specific Python problem
run%:
	@N=$*; \
	SCRIPT_FILE=$$(find . -path ./venv -prune -o -type f -name "$$N-*.py" -print -quit); \
	if [ -z "$$SCRIPT_FILE" ]; then \
		echo "No Python script file found for problem $$N"; \
		exit 1; \
	fi; \
	echo "Running file $$SCRIPT_FILE"; \
	$(PYTHON) "$$SCRIPT_FILE"

# Clean Python cache for a specific problem
clean%:
	@N=$*; \
	SCRIPT_FILE=$$(find . -path ./venv -prune -o -type f -name "$$N-*.py" -print -quit); \
	if [ -n "$$SCRIPT_FILE" ]; then \
		SCRIPT_DIR=$$(dirname "$$SCRIPT_FILE"); \
		PYC_FILE="$${SCRIPT_FILE%.py}.pyc"; \
		if [ -d "$$SCRIPT_DIR/__pycache__" ]; then \
			echo "Deleting $$SCRIPT_DIR/__pycache__"; \
			rm -rf "$$SCRIPT_DIR/__pycache__"; \
		fi; \
		find "$$SCRIPT_DIR" -maxdepth 1 -name "*.pyc" -type f -delete 2>/dev/null || true; \
	fi

# Main target to run a Python problem and clean up
# Example: make 20
%:
	@PROBLEM_NUM=$@; \
	if echo $$PROBLEM_NUM | grep -Eq '^[0-9]+$$'; then \
		$(MAKE) --no-print-directory compile$$PROBLEM_NUM; \
		$(MAKE) --no-print-directory run$$PROBLEM_NUM; \
		$(MAKE) --no-print-directory clean$$PROBLEM_NUM; \
	else \
		case "$$PROBLEM_NUM" in \
			all|find|clean_all|format|format-check) \
				$(MAKE) $$PROBLEM_NUM; \
				;; \
			*) \
				echo "Error: '$$PROBLEM_NUM' is not a valid problem number"; \
				echo "Use 'make <number>', e.g., 'make 20'"; \
				exit 1; \
				;; \
		esac; \
	fi

# Find the source file for a specific problem
find:
	@echo "Error: No problem number specified"
	@echo "Usage: make find<problem_number>"
	@echo "Example: make find1"

find%:
	@N=$*; \
	FILE=$$(find . -path ./venv -prune -o -type f -name "$$N-*.py" -print -quit); \
	if [ -z "$$FILE" ]; then \
		echo "No file found for problem $$N"; \
	else \
		echo "Found file: $$FILE"; \
	fi

# Clean all Python cache files
clean_all:
	@echo "Cleaning all Python cache files..."
	@find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true
	@find . -type f -name "*.pyc" -delete
	@echo "All Python cache files cleaned"

# Ensure all Python files end with newline
format:
	@echo "Checking Python source files..."
	@modified_files=""; \
	for file in $$(find . -path ./venv -prune -o -name "*.py" -type f -print); do \
		if [ -s "$$file" ] && [ "$$(tail -c1 "$$file" | wc -l)" -eq 0 ]; then \
			modified_files="$$modified_files$$file (added final newline)\n"; \
			echo >> "$$file"; \
		fi; \
	done; \
	echo ""; \
	echo "Complete!"; \
	echo ""; \
	echo "Modified files:"; \
	if [ -n "$$modified_files" ]; then \
		printf "$$modified_files" | sed 's/^/  - /'; \
	else \
		echo "  No files were modified."; \
	fi

.PHONY: all find clean_all compile% run% clean% format
