# PolyBuild NLink Orchestration Makefile
# Component-based build system

PROJECT_NAME = polybuild_nlink_poc
VERSION = 1.0.0

# Component directories in build order
COMPONENTS = component-core component-resolver component-orchestrator component-cli

# Artifacts directory
ARTIFACTS_DIR = artifacts
LOG_DIR = logs

.PHONY: all clean components test nlink-validate help

all: components
	@echo "[NLINK] PolyBuild POC build completed successfully"

components: $(ARTIFACTS_DIR)
	@echo "[NLINK] Building all components in dependency order"
	@for component in $(COMPONENTS); do \
		echo "[NLINK] Building component: $$component"; \
		$(MAKE) -C $$component all || exit 1; \
	done

$(ARTIFACTS_DIR):
	mkdir -p $(ARTIFACTS_DIR) $(LOG_DIR)

clean:
	@echo "[NLINK] Cleaning all components"
	@for component in $(COMPONENTS); do \
		$(MAKE) -C $$component clean; \
	done
	rm -rf $(ARTIFACTS_DIR) $(LOG_DIR)

test: all
	@echo "[NLINK] Running PolyBuild integration tests"
	./artifacts/polybuild --version
	./artifacts/polybuild --help
	./artifacts/polybuild -lpolybuild --dry-run

nlink-validate:
	@echo "[NLINK] Validating project configuration"
	@test -f pkg.nlink && echo "[NLINK] Project configuration found" || echo "[NLINK] Missing pkg.nlink"
	@for component in $(COMPONENTS); do \
		echo "[NLINK] Validating $$component"; \
		$(MAKE) -C $$component nlink-validate; \
	done

install: all
	@echo "[NLINK] Installing PolyBuild"
	cp artifacts/polybuild /usr/local/bin/
	mkdir -p /usr/local/lib/polybuild
	cp artifacts/*.a /usr/local/lib/polybuild/

help:
	@echo "PolyBuild NLink Orchestration Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all              Build all components"
	@echo "  components       Build components in dependency order"
	@echo "  clean            Clean all build artifacts"
	@echo "  test             Run integration tests"
	@echo "  nlink-validate   Validate NLink configurations"
	@echo "  install          Install PolyBuild system-wide"
	@echo "  help             Show this help message"
	@echo ""
	@echo "Usage Examples:"
	@echo "  make all                    # Build complete project"
	@echo "  make test                   # Test PolyBuild CLI"
	@echo "  make clean && make all      # Clean rebuild"
