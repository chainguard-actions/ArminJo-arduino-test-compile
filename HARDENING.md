<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `1`

Action **ArminJo--arduino-test-compile/v3** was hardened automatically. 1 finding(s) were identified and resolved across 2 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Sub-rule (a): A ${{ ... }} expression is directly interpolated inside a `run:` shell command string in action.yml. The line `run: ${{ github.action_path }}/arduino-test-compile.sh` embeds the GitHub Actions expression `${{ github.action_path }}` directly into the shell command before the shell ever sees it. Although `github.action_path` is not attacker-controlled, any `${{ ... }}` expression inside a `run:` block is a script-injection risk because the value is substituted by the YAML template engine before the shell parses it, bypassing shell quoting. The safe alternative is to use the pre-set environment variable `$GITHUB_ACTION_PATH` instead: `run: "$GITHUB_ACTION_PATH/arduino-test-compile.sh"`

Locations:

- `action.yml:100`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection

**Notes:**

Replaced `${{ github.action_path }}/arduino-test-compile.sh` with `"$GITHUB_ACTION_PATH/arduino-test-compile.sh"` in action.yml at line 100. The pre-set environment variable `$GITHUB_ACTION_PATH` is the safe equivalent that avoids template-engine interpolation before shell parsing.

### Iteration 2

**Fixes applied:** script-injection

**Notes:**

Fixed all 6 categories of shell injection vulnerabilities in arduino-test-compile.sh: (1) Validated CLI_VERSION with a regex allowlist (^[a-zA-Z0-9._-]+$) before using it in the wget URL, and quoted the URL string; (2) Changed $PLATFORM_URL and $PLATFORM_URL_COMMAND to use ${VAR:+"$VAR"} conditional expansion so they are quoted when non-empty and absent when empty; (3) Converted EXTRA_ARDUINO_LIB_INSTALL_ARGS to a bash array (EXTRA_LIB_ARGS_ARRAY) via `read -ra` and expanded with "${EXTRA_LIB_ARGS_ARRAY[@]}"; (4) Converted EXTRA_ARDUINO_CLI_ARGS to a bash array (EXTRA_CLI_ARGS_ARRAY) via `read -ra` and expanded with "${EXTRA_CLI_ARGS_ARRAY[@]}"; (5) Changed BUILD_PATH_PARAMETER from a string to a bash array (BUILD_PATH_PARAM_ARRAY) with properly quoted path, expanded with "${BUILD_PATH_PARAM_ARRAY[@]}"; (6) Quoted $SKETCH_PATH as "$SKETCH_PATH" in all compile commands. The echo/diagnostic lines that display the command for logging purposes retain the original unquoted form for readability, but the actual command executions use safe array expansion.

