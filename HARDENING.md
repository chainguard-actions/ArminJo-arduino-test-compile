<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.2.1

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `1`

Action **ArminJo--arduino-test-compile/v3.2.1** was hardened automatically. 2 finding(s) were identified and resolved across 2 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Rule (a): A ${{ }} expression is directly interpolated inside a `run:` shell command string in action.yml. The line `run: ${{ github.action_path }}/arduino-test-compile.sh` embeds a GitHub Actions expression directly in the shell command before the shell ever sees it, which is a script-injection risk.

Locations:

- `action.yml:100`

### script-injection (severity: high)

Rule (b): Multiple unquoted shell variable expansions of untrusted inputs (sourced from `inputs.*` via env vars set in action.yml) are used directly in shell commands inside arduino-test-compile.sh, which is the script executed by the composite action's `run:` step. Specific violations include: (1) `wget --quiet https://downloads.arduino.cc/arduino-cli/arduino-cli_${CLI_VERSION}_Linux_64bit.tar.gz` — `${CLI_VERSION}` (from `inputs.cli-version`) is unquoted in a URL; (2) `arduino-cli core update-index $PLATFORM_URL_COMMAND $PLATFORM_URL` and `arduino-cli core install $single_platform $PLATFORM_URL_COMMAND $PLATFORM_URL` — `$PLATFORM_URL` (from `inputs.platform-url`) is unquoted; (3) `arduino-cli compile --verbose --warnings all --fqbn ${ARDUINO_BOARD_FQBN%|*} $BUILD_PATH_PARAMETER $EXTRA_ARDUINO_CLI_ARGS $SKETCH_PATH` — `${ARDUINO_BOARD_FQBN%|*}` (from `inputs.arduino-board-fqbn`), `$EXTRA_ARDUINO_CLI_ARGS` (from `inputs.extra-arduino-cli-args`), and `$SKETCH_PATH` are all unquoted, allowing shell metacharacter injection.

Locations:

- `arduino-test-compile.sh:113`
- `arduino-test-compile.sh:185`
- `arduino-test-compile.sh:188`
- `arduino-test-compile.sh:191`
- `arduino-test-compile.sh:194`
- `arduino-test-compile.sh:380`
- `arduino-test-compile.sh:383`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection

**Notes:**

Fixed two script-injection findings:

1. action.yml line 100: Moved `${{ github.action_path }}` out of the `run:` shell string into the `env:` block as `ACTION_PATH: ${{ github.action_path }}`, then used `"$ACTION_PATH/arduino-test-compile.sh"` in the run command.

2. arduino-test-compile.sh:
   - Line 113: Quoted the wget URL string to prevent CLI_VERSION metacharacter injection.
   - Lines 185/188/191/194: Replaced unquoted `$PLATFORM_URL_COMMAND $PLATFORM_URL` with a bash array `PLATFORM_URL_ARGS=(--additional-urls "$PLATFORM_URL")` expanded as `"${PLATFORM_URL_ARGS[@]}"` in all arduino-cli core commands.
   - Lines 380/383: Converted `BUILD_PATH_PARAMETER` to array `BUILD_PATH_ARGS`, split `EXTRA_ARDUINO_CLI_ARGS` into array `EXTRA_CLI_ARGS_ARRAY` via `read -ra`, and quoted `"${ARDUINO_BOARD_FQBN%|*}"` and `"$SKETCH_PATH"` in all arduino-cli compile invocations.

### Iteration 2

**Fixes applied:** script-injection

**Notes:**

Fixed two script-injection findings: (1) In arduino-test-compile.sh, converted the unquoted $EXTRA_ARDUINO_LIB_INSTALL_ARGS variable to a properly-quoted array using 'read -ra EXTRA_LIB_ARGS_ARRAY <<< "$EXTRA_ARDUINO_LIB_INSTALL_ARGS"' and expanded it as '"${EXTRA_LIB_ARGS_ARRAY[@]}"' in both the debug and non-debug arduino-cli lib install invocations. (2) In action.yml, changed the run: value from a YAML double-quoted string (where double-quotes are YAML delimiters, not shell quotes) to a YAML block scalar so that the shell double-quotes around "$ACTION_PATH/arduino-test-compile.sh" are actual shell quotes that properly protect the variable expansion.

