<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.1.0

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `1`

Action **ArminJo--arduino-test-compile/v3.1.0** was hardened automatically. 1 finding(s) were identified and resolved across 1 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Sub-rule (a): A ${{ ... }} expression is interpolated directly inside a run: shell command string. The run: step in action.yml uses `run: ${{ github.action_path }}/arduino-test-compile.sh`, which injects the github.action_path context value directly into the shell command before the shell ever sees it. Per the check rules, any ${{ ... }} expression inside a run: block — including github.* contexts — is a script-injection finding. The safe alternative is to use the $GITHUB_ACTION_PATH environment variable instead: `run: "$GITHUB_ACTION_PATH/arduino-test-compile.sh"`.

Locations:

- `action.yml:97`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection

**Notes:**

Replaced `run: ${{ github.action_path }}/arduino-test-compile.sh` with `run: "$GITHUB_ACTION_PATH/arduino-test-compile.sh"` on line 97 of action.yml. The `$GITHUB_ACTION_PATH` environment variable is automatically set by GitHub Actions and is the safe, injection-free way to reference the action's directory path in a run: step.

