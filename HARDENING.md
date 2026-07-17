<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.2.0

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `2`

Action **ArminJo--arduino-test-compile/v3.2.0** was hardened automatically. 3 finding(s) were identified and resolved across 2 iteration(s).

## Findings Fixed

### unpinned-uses (severity: high)

Both workflow files reference actions using mutable tags/branches instead of pinned 40-character commit SHAs. In arduino-test-compile-ActionTest.yml: `actions/checkout@v2` (used twice) and `ArminJo/arduino-test-compile@master`. In arduino-test-compile-ScriptTest.yml: `actions/checkout@v2` (used twice). Any of these could be silently updated to deliver malicious code.

Locations:

- `.github/workflows/arduino-test-compile-ActionTest.yml:88`
- `.github/workflows/arduino-test-compile-ActionTest.yml:92`
- `.github/workflows/arduino-test-compile-ActionTest.yml:99`
- `.github/workflows/arduino-test-compile-ScriptTest.yml:84`
- `.github/workflows/arduino-test-compile-ScriptTest.yml:88`

### script-injection (severity: high)

Sub-rule (a): action.yml contains a `run:` block that directly interpolates a `${{ }}` expression into the shell command string: `run: ${{ github.action_path }}/arduino-test-compile.sh`. The `github.action_path` context value is substituted by the Actions runner before the shell sees the command, meaning any special characters in the value are processed by the shell without quoting. This should be replaced with the `$GITHUB_ACTION_PATH` environment variable instead.

Locations:

- `action.yml:100`

### missing-permissions (severity: medium)

Neither workflow file defines a top-level `permissions:` key, and neither job within them defines a job-level `permissions:` key. Without explicit permissions, workflows inherit the default repository token permissions, which may be overly broad (e.g., write access to contents). A minimal `permissions: read-all` or specific scopes should be declared.

Locations:

- `.github/workflows/arduino-test-compile-ActionTest.yml:1`
- `.github/workflows/arduino-test-compile-ScriptTest.yml:1`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection, unpinned-uses, missing-permissions

**Notes:**

1. action.yml: Replaced `${{ github.action_path }}/arduino-test-compile.sh` with `$GITHUB_ACTION_PATH/arduino-test-compile.sh` to eliminate script injection risk. 2. Both workflow files: Pinned `actions/checkout@v2` to `@ee0669bd1cc54295c223e0bb666b733df41de1c5` (4 occurrences) and `ArminJo/arduino-test-compile@master` to `@d02d365b1776367122ba4c9bbfe333dbc94b2722` (1 occurrence), with original tags preserved as inline comments. 3. Both workflow files: Added `permissions: contents: read` top-level block to restrict the GITHUB_TOKEN to the minimum needed for checkout operations.

### Iteration 2

**Fixes applied:** script-injection

**Notes:**

Fixed all unquoted variable expansions in arduino-test-compile.sh that could allow shell injection:

1. PLATFORM_URL/PLATFORM_URL_COMMAND: Built a PLATFORM_URL_ARGS bash array and used "${PLATFORM_URL_ARGS[@]}" in all arduino-cli core update-index and core install commands.

2. EXTRA_ARDUINO_LIB_INSTALL_ARGS: Converted to array via `read -r -a EXTRA_ARDUINO_LIB_INSTALL_ARGS_ARRAY <<< "$EXTRA_ARDUINO_LIB_INSTALL_ARGS"` and used "${EXTRA_ARDUINO_LIB_INSTALL_ARGS_ARRAY[@]}" in lib install commands.

3. EXTRA_ARDUINO_CLI_ARGS: Converted to array via `read -r -a EXTRA_ARDUINO_CLI_ARGS_ARRAY <<< "$EXTRA_ARDUINO_CLI_ARGS"` and used "${EXTRA_ARDUINO_CLI_ARGS_ARRAY[@]}" in compile commands.

4. ARDUINO_BOARD_FQBN: Quoted "${ARDUINO_BOARD_FQBN%|*}" in actual compile command executions.

5. BUILD_PATH_PARAMETER: Converted to BUILD_PATH_ARGS array with "${BUILD_PATH_ARGS[@]}" in compile commands.

The echo/logging lines that display commands for informational purposes retain the old form but are inside double-quoted echo strings and do not execute shell commands. All actual command executions now use properly quoted arrays, preventing shell metacharacter injection.

