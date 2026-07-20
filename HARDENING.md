<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3

> This file was generated automatically by the hardening agent.

**Policy SHA:** `d636be7e43ef829af6e853da6b3c7566db9f72fe`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `2`

Action **ArminJo--arduino-test-compile/v3** was hardened automatically. 3 finding(s) were identified and resolved across 1 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Sub-rule (a): The `run:` field in action.yml directly interpolates the GitHub Actions expression `${{ github.action_path }}` into the shell command string. Any `${{ ... }}` expression inside a `run:` block is a script-injection risk because the value is substituted by the Actions runner before the shell ever sees it, bypassing shell quoting. The offending line is: `run: ${{ github.action_path }}/arduino-test-compile.sh`. This should be replaced with the environment variable `$GITHUB_ACTION_PATH` which is always available in composite actions.

Locations:

- `action.yml:107`

### unpinned-uses (severity: high)

All `uses:` references in both workflow files use the mutable branch ref `@master` instead of a pinned 40-character commit SHA. This exposes the workflow to supply-chain attacks if the referenced action is compromised or its history is rewritten. Failing references: `actions/checkout@master` (appears twice in each workflow), and `ArminJo/arduino-test-compile@master` (in ActionTest.yml).

Locations:

- `.github/workflows/arduino-test-compile-ActionTest.yml:88`
- `.github/workflows/arduino-test-compile-ActionTest.yml:92`
- `.github/workflows/arduino-test-compile-ActionTest.yml:97`
- `.github/workflows/arduino-test-compile-ScriptTest.yml:88`
- `.github/workflows/arduino-test-compile-ScriptTest.yml:92`

### missing-permissions (severity: medium)

Neither workflow file defines a `permissions:` block at the top level, and no job within either file defines its own `permissions:` block. Without explicit permissions, workflows run with the repository's default token permissions, which may be overly broad (e.g., write access to contents, packages, etc.). A minimal `permissions: read-all` or specific per-scope permissions should be added.

Locations:

- `.github/workflows/arduino-test-compile-ActionTest.yml:1`
- `.github/workflows/arduino-test-compile-ScriptTest.yml:1`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection, unpinned-uses, missing-permissions

**Notes:**

Fixed three security findings: (1) script-injection in action.yml by replacing `${{ github.action_path }}` with `$GITHUB_ACTION_PATH` environment variable; (2) pinned all unpinned @master action references to full commit SHAs - actions/checkout to 61b9e3751b92087fd0b06925ba6dd6314e06f089 and ArminJo/arduino-test-compile to d02d365b1776367122ba4c9bbfe333dbc94b2722; (3) added `permissions: contents: read` block to both workflow files (ActionTest.yml and ScriptTest.yml).

