# Makefile for Python Solutions

# Default Python interpreter
PYTHON = python3

# Default target
all:
	@echo "Usage: make <problem_number>"
	@echo "Example: make 20  (finds e.g. 20-my_solution.py in Easy/, Medium/, or Hard/)"
	@echo "This will run the script and clean up __pycache__ and .pyc files."

# Main target to run a Python problem and clean up
# Example: make 20
%:
	@PROBLEM_NUM=$@; \
	if echo $$PROBLEM_NUM | grep -Eq '^[0-9]+$$'; then \
		echo "Processing Python problem #$$PROBLEM_NUM"; \
		SCRIPT_FILE=`find . -path ./venv -prune -o -type f -name "$$PROBLEM_NUM-*.py" -print -quit`; \
		if [ -z "$$SCRIPT_FILE" ]; then \
			echo "No Python script file found for problem $$PROBLEM_NUM"; \
			exit 1; \
		fi; \
		echo "Running $$SCRIPT_FILE"; \
		$(PYTHON) $$SCRIPT_FILE; \
		SCRIPT_DIR=`dirname $$SCRIPT_FILE`; \
		echo "Cleaning up Python artifacts"; \
		if [ -d "$$SCRIPT_DIR/__pycache__" ]; then \
			rm -rf "$$SCRIPT_DIR/__pycache__"; \
		fi; \
		find "$$SCRIPT_DIR" -maxdepth 1 -name "*.pyc" -type f -delete; \
	else \
		case "$$PROBLEM_NUM" in \
			all|find|clean_all) \
				$(MAKE) $$PROBLEM_NUM; \
				;; \
			*) \
				echo "Error: '$$PROBLEM_NUM' is not a valid problem number"; \
				echo "Use 'make <number>', e.g., 'make 20'"; \
				exit 1; \
				;; \
		esac; \
	fi

# Run a specific Python problem
run:
	@echo "Error: No problem number specified"
	@echo "Usage: make run<problem_number>"
	@echo "Example: make run1"

# Equivalent to just 'make <problem_number>'
run%:
	@N=$*; \
	$(MAKE) $$N

# Find the source file for a specific problem
find:
	@echo "Error: No problem number specified"
	@echo "Usage: make find<problem_number>"
	@echo "Example: make find1"

find%:
	@N=$*; \
	FILE=`find . -type f -name "$$N-*.py" | head -n 1`; \
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

.PHONY: all find clean_all run run%
