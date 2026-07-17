<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.1.0

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `2`

Action **ArminJo--arduino-test-compile/v3.1.0** was hardened automatically. 5 finding(s) were identified and resolved across 2 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Sub-rule (a): A `${{ github.action_path }}` expression is interpolated directly inside the `run:` shell command string in action.yml. Any `${{ ... }}` expression inside a `run:` block is a script-injection risk because the value is substituted by the YAML template engine before the shell ever sees it. The offending line is: `run: ${{ github.action_path }}/arduino-test-compile.sh`. This should be replaced with the environment variable form, e.g. `run: "$GITHUB_ACTION_PATH/arduino-test-compile.sh"`.

Locations:

- `action.yml:96`

### unpinned-uses (severity: high)

Multiple `uses:` references in this workflow use mutable tags or branch names instead of pinned 40-character commit SHAs, making the workflow vulnerable to supply-chain attacks if the referenced action is compromised or its tag is moved:
- `uses: actions/checkout@v2` (line ~88, Checkout step)
- `uses: actions/checkout@v2` (line ~92, Checkout custom library step)
- `uses: ArminJo/arduino-test-compile@master` (line ~97, Compile step)
All should be pinned to full SHA digests, e.g. `actions/checkout@11bd71901bbe5b1630ceea73d27597364c9af683 # v2`.

Locations:

- `.github/workflows/arduino-test-compile-ActionTest.yml:88`
- `.github/workflows/arduino-test-compile-ActionTest.yml:92`
- `.github/workflows/arduino-test-compile-ActionTest.yml:97`

### unpinned-uses (severity: high)

Multiple `uses:` references in this workflow use mutable tags instead of pinned 40-character commit SHAs:
- `uses: actions/checkout@v2` (line ~88, Checkout step)
- `uses: actions/checkout@v2` (line ~92, Checkout custom library step)
All should be pinned to full SHA digests, e.g. `actions/checkout@11bd71901bbe5b1630ceea73d27597364c9af683 # v2`.

Locations:

- `.github/workflows/arduino-test-compile-ScriptTest.yml:88`
- `.github/workflows/arduino-test-compile-ScriptTest.yml:92`

### missing-permissions (severity: medium)

The workflow file has no top-level `permissions:` key and no job-level `permissions:` key on any job. Without explicit permissions, the workflow inherits the repository's default token permissions, which may be overly broad. A minimal `permissions:` block (e.g. `contents: read`) should be added at the top level or on each job.

Locations:

- `.github/workflows/arduino-test-compile-ActionTest.yml:1`

### missing-permissions (severity: medium)

The workflow file has no top-level `permissions:` key and no job-level `permissions:` key on any job. Without explicit permissions, the workflow inherits the repository's default token permissions, which may be overly broad. A minimal `permissions:` block (e.g. `contents: read`) should be added at the top level or on each job.

Locations:

- `.github/workflows/arduino-test-compile-ScriptTest.yml:1`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection, unpinned-uses, missing-permissions

**Notes:**

Fixed all 5 findings: (1) Replaced `${{ github.action_path }}` template expression in action.yml run: block with `$GITHUB_ACTION_PATH` environment variable to eliminate script-injection risk. (2) Pinned `actions/checkout@v2` to SHA `ee0669bd1cc54295c223e0bb666b733df41de1c5` in both ActionTest.yml and ScriptTest.yml (2 occurrences each). (3) Pinned `ArminJo/arduino-test-compile@master` to SHA `d02d365b1776367122ba4c9bbfe333dbc94b2722` in ActionTest.yml. (4) Added `permissions: contents: read` top-level block to both ActionTest.yml and ScriptTest.yml.

### Iteration 2

**Fixes applied:** script-injection, unsafe-shell

**Notes:**

Fixed script-injection in arduino-test-compile.sh by: (1) replacing the unquoted $PLATFORM_URL_COMMAND/$PLATFORM_URL pair with a bash array PLATFORM_URL_ARGS expanded as "${PLATFORM_URL_ARGS[@]}"; (2) quoting $single_platform in arduino-cli core install calls; (3) replacing the multi-word $BUILD_PATH_PARAMETER string with a bash array BUILD_PATH_ARGS; (4) splitting $EXTRA_ARDUINO_CLI_ARGS into an array EXTRA_ARDUINO_CLI_ARGS_ARRAY via 'read -r -a' and expanding it as "${EXTRA_ARDUINO_CLI_ARGS_ARRAY[@]}"; (5) quoting $SKETCH_PATH and ${ARDUINO_BOARD_FQBN%|*} in all arduino-cli compile invocations. Fixed unsafe-shell in arduino-test-compile-ScriptTest.yml by removing the wget download of the script from the mutable master branch URL — the script is already available locally from the repository checkout, so the workflow now uses it directly.

