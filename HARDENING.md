<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.2.1

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `2`

Action **ArminJo--arduino-test-compile/v3.2.1** was hardened automatically. 5 finding(s) were identified and resolved across 1 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Sub-rule (a): A ${{ ... }} expression is interpolated directly inside a `run:` shell command string in action.yml. The line `run: ${{ github.action_path }}/arduino-test-compile.sh` embeds the `github.action_path` context value directly into the shell command before the shell ever sees it. The safe alternative is to use the pre-set environment variable `$GITHUB_ACTION_PATH` instead.

Locations:

- `action.yml:98`

### unpinned-uses (severity: high)

Multiple `uses:` references in this workflow use mutable tags or branch names instead of immutable 40-character SHA digests, making the workflow vulnerable to supply-chain attacks if those tags or branches are moved or compromised. Failing references: `actions/checkout@v2` (line 91), `actions/checkout@v2` (line 95), `ArminJo/arduino-test-compile@master` (line 102).

Locations:

- `.github/workflows/arduino-test-compile-ActionTest.yml:91`
- `.github/workflows/arduino-test-compile-ActionTest.yml:95`
- `.github/workflows/arduino-test-compile-ActionTest.yml:102`

### unpinned-uses (severity: high)

Multiple `uses:` references in this workflow use mutable tags instead of immutable 40-character SHA digests, making the workflow vulnerable to supply-chain attacks. Failing references: `actions/checkout@v2` (line 88), `actions/checkout@v2` (line 92).

Locations:

- `.github/workflows/arduino-test-compile-ScriptTest.yml:88`
- `.github/workflows/arduino-test-compile-ScriptTest.yml:92`

### missing-permissions (severity: medium)

The workflow has no top-level `permissions:` key and the single `build` job also has no `permissions:` key. Without explicit permissions, the workflow inherits the default repository permissions (which may include write access to contents, packages, etc.), violating the principle of least privilege.

Locations:

- `.github/workflows/arduino-test-compile-ActionTest.yml:1`

### missing-permissions (severity: medium)

The workflow has no top-level `permissions:` key and the single `build` job also has no `permissions:` key. Without explicit permissions, the workflow inherits the default repository permissions, violating the principle of least privilege.

Locations:

- `.github/workflows/arduino-test-compile-ScriptTest.yml:1`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection, unpinned-uses, missing-permissions

**Notes:**

Fixed 5 findings across 3 files: (1) action.yml line 98: replaced `${{ github.action_path }}/arduino-test-compile.sh` with `$GITHUB_ACTION_PATH/arduino-test-compile.sh` to eliminate script injection; (2) arduino-test-compile-ActionTest.yml: added `permissions: contents: read` at top level, pinned `actions/checkout@v2` to SHA `0717577d45739eb3c851188b29f50ed6c0b2194e` (both occurrences), and pinned `ArminJo/arduino-test-compile@master` to SHA `d02d365b1776367122ba4c9bbfe333dbc94b2722`; (3) arduino-test-compile-ScriptTest.yml: added `permissions: contents: read` at top level and pinned both `actions/checkout@v2` references to SHA `0717577d45739eb3c851188b29f50ed6c0b2194e`.

