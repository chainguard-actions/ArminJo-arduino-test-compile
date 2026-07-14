<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.2.0

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `1`

Action **ArminJo--arduino-test-compile/v3.2.0** was hardened automatically. 2 finding(s) were identified and resolved across 1 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Sub-rule (a): A ${{ }} expression is interpolated directly inside a run: shell command string. In action.yml, the run: block contains `run: ${{ github.action_path }}/arduino-test-compile.sh`. Even though github.action_path is not attacker-controlled, any ${{ ... }} expression inside a run: block is a script-injection finding per the check rules, as YAML template substitution occurs before the shell ever sees the value.

Locations:

- `action.yml:93`

### script-injection (severity: high)

Sub-rule (b): Multiple unquoted shell variable expansions of user-controlled inputs in arduino-test-compile.sh. Variables sourced from action inputs (via env: block in action.yml) are used unquoted in command invocations, allowing shell metacharacter injection. Examples include: `$EXTRA_ARDUINO_CLI_ARGS` (unquoted in arduino-cli compile calls), `$PLATFORM_URL` (unquoted in arduino-cli core update-index/install calls), `$EXTRA_ARDUINO_LIB_INSTALL_ARGS` (unquoted in arduino-cli lib install calls), and `$SKETCH_PATH` (unquoted in arduino-cli compile calls). An attacker-controlled input containing shell metacharacters (`;`, `|`, `&`, `$(...)`) would be interpreted by the shell.

Locations:

- `arduino-test-compile.sh:161`
- `arduino-test-compile.sh:163`
- `arduino-test-compile.sh:165`
- `arduino-test-compile.sh:167`
- `arduino-test-compile.sh:200`
- `arduino-test-compile.sh:202`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection

**Notes:**

Fixed two script-injection findings:

1. action.yml line 93: Moved `${{ github.action_path }}` out of the `run:` block into the `env:` block as `ACTION_PATH: ${{ github.action_path }}`. The run line now uses `"$ACTION_PATH/arduino-test-compile.sh"` (plain shell variable, no template expression in run block).

2. arduino-test-compile.sh: Fixed unquoted user-controlled variables in command invocations:
   - `$PLATFORM_URL`/`$PLATFORM_URL_COMMAND`: Replaced with a bash array `PLATFORM_URL_ARGS=(--additional-urls "$PLATFORM_URL")` expanded as `"${PLATFORM_URL_ARGS[@]}"` in arduino-cli core calls.
   - `$EXTRA_ARDUINO_LIB_INSTALL_ARGS`: Converted to array via `read -r -a EXTRA_LIB_ARGS_ARRAY <<< "$EXTRA_ARDUINO_LIB_INSTALL_ARGS"`, expanded as `"${EXTRA_LIB_ARGS_ARRAY[@]}"` in arduino-cli lib install calls.
   - `$EXTRA_ARDUINO_CLI_ARGS`: Converted to array via `read -r -a EXTRA_CLI_ARGS_ARRAY <<< "$EXTRA_ARDUINO_CLI_ARGS"`, expanded as `"${EXTRA_CLI_ARGS_ARRAY[@]}"` in arduino-cli compile calls.
   - `$SKETCH_PATH`: Quoted as `"$SKETCH_PATH"` in arduino-cli compile calls.
   - `BUILD_PATH_PARAMETER` string replaced with `BUILD_PATH_ARGS` array `(--build-path "$SKETCH_PATH/build/")` expanded as `"${BUILD_PATH_ARGS[@]}"`.

