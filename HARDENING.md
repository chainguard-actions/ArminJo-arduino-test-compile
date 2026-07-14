<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.3.0

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `1`

Action **ArminJo--arduino-test-compile/v3.3.0** was hardened automatically. 1 finding(s) were identified and resolved across 2 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Sub-rule (a): A GitHub Actions expression `${{ github.action_path }}` is directly interpolated inside a `run:` shell command string: `run: ${{ github.action_path }}/arduino-test-compile.sh`. Per the check rules, any `${{ ... }}` expression directly inside a `run:` block is a script-injection risk because the value flows through YAML template substitution before the shell ever sees it. The safe alternative is to use the pre-set environment variable `$GITHUB_ACTION_PATH` instead of the expression form.

Locations:

- `action.yml:96`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection

**Notes:**

Replaced `${{ github.action_path }}/arduino-test-compile.sh` in the `run:` field with `"$GITHUB_ACTION_PATH/arduino-test-compile.sh"`. The `$GITHUB_ACTION_PATH` environment variable is automatically set by GitHub Actions for composite actions and is the safe, recommended alternative to the expression form. This eliminates the YAML template substitution path that creates the script-injection risk.

### Iteration 2

**Fixes applied:** script-injection

**Notes:**

Fixed all unquoted variable expansions in arduino-test-compile.sh:
1. Double-quoted `${SKETCH_NAMES_FIND_START}` in `find` and `ls` commands
2. Used `${VAR:+"$VAR"}` pattern for optional `$PLATFORM_URL` and `$PLATFORM_URL_COMMAND` to safely handle empty values
3. Converted `$EXTRA_ARDUINO_LIB_INSTALL_ARGS` to a bash array (`EXTRA_ARDUINO_LIB_INSTALL_ARGS_ARRAY`) via `read -r -a` and expanded with `"${EXTRA_ARDUINO_LIB_INSTALL_ARGS_ARRAY[@]}"`
4. Double-quoted `${ARDUINO_BOARD_FQBN%|*}` in both compile commands
5. Converted `$EXTRA_ARDUINO_CLI_ARGS` to a bash array (`EXTRA_ARDUINO_CLI_ARGS_ARRAY`) via `read -r -a` and expanded with `"${EXTRA_ARDUINO_CLI_ARGS_ARRAY[@]}"` in both compile commands

The array approach preserves multi-argument behavior while preventing shell metacharacter injection from attacker-controlled inputs.

