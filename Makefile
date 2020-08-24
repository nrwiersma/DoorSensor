# Format the code. Requires clang-format.
fmt:
	@echo "==> Formatting..."
	@clang-format -i src/*
	@echo "==> Formatted"
.PHONY: fmt
