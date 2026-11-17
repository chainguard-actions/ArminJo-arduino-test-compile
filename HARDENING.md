<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.2.1

> This file was generated automatically by the hardening agent.

**Policy SHA:** `374911c4be584df24e6da57af2d990570ef0f859`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `2`

Action **ArminJo--arduino-test-compile/v3.2.1** was hardened automatically. 2 finding(s) were identified and resolved across 1 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Rule (a): the composite step's run: block puts a GitHub Actions expression directly into the shell command: `run: ${{ github.action_path }}/arduino-test-compile.sh`. The value is substituted into the script text before bash parses it, and it is not quoted. Fix: use the runner-provided env var with quotes, e.g. `run: "$GITHUB_ACTION_PATH/arduino-test-compile.sh"`.

Locations:

- `action.yml:118`

### prior-fix (severity: high)

Carried forward from this version's previous harden, which fixed it; fix it again unless the code no longer has the problem. The previous harden changed action.yml without recording a finding for it, and this analysis reported nothing there. Re-apply its security changes unless the code no longer needs them. The previous patch:
```diff
diff --git a/action.yml b/action.yml
index 1565216..2cf21ee 100644
--- a/action.yml
+++ b/action.yml
@@ -6,110 +6,110 @@ inputs:
     description: 'Version of arduino-cli to use when building. Current (8/2022) one is 0.26.0.'
     default: 'latest'
     required: false
-
   sketch-names:
     description: 'Comma sepatated list of patterns or filenames (without path) of the sketch(es) to test compile. Useful if the sketch is a *.cpp or *.c file or only one sketch in the repository should be compiled.'
     default: '*.ino'
     required: false
-
   sketch-names-find-start:
     description: 'The start directory to look for the sketch-names to test compile. Can be a path like "digistump-avr/libraries/*/examples/C*/" .'
     default: '.'
     required: false
-
   arduino-board-fqbn:
     #In the Arduino IDE, the fqbn is printed in the first line of the verbose output for compilation as parameter -fqbn=... for the "arduino-builder -dump-prefs" command
     description: 'Fully Qualified Board Name of the Arduino board. You may add a suffix behind the fqbn with "|" to specify one board for e.g. different compile options like arduino:avr:uno|trace.'
     default: 'arduino:avr:uno'
     required: false
-
   arduino-platform:
     description: 'Comma separated list of platform specifiers, if you require a fixed version like arduino:avr@1.8.2 or do not want the specifier derived from the 2 first elements of the arduino-board-fqbn or need more than one core.'
     default: ''
     required: false
-
   platform-default-url:
     description: 'The platform URL for the required board description if arduino-board-fqbn does not start with "arduino:" and not explicitly specified by platform-url.'
     default: ''
     required: false
-
   platform-url:
     description: 'The platform URL for the required board description if arduino-board-fqbn does not start with "arduino:".'
     default: ''
     required: false
-
   required-libraries:
     description: 'Comma separated list of arduino library names required for compiling the sketches / examples for this board.'
     default: ''
     required: false
-
   sketches-exclude:
     description: 'Comma or space separated list of complete names of all sketches / examples to be excluded in the build for this board.'
     default: ''
     required: false
-
   build-properties:
     description: |
       Build parameter like -DDEBUG for each example specified or for all examples, if example name is "All". In json format.
       For example: build-properties: '{ "WhistleSwitch": "-DDEBUG -DFREQUENCY_RANGE_LOW", "SimpleFrequencyDetector": "-DINFO" }'
     default: ''
     required: false
-
   extra-arduino-cli-args:
     description: |
       This string is passed verbatim without double quotes to the arduino-cli compile commandline as last argument before the filename.
       See https://arduino.github.io/arduino-cli/commands/arduino-cli_compile/ for compile parameters.
     default: ''
     required: false
-
   extra-arduino-lib-install-args:
     description: |
       This string is passed verbatim without double quotes to the arduino-cli lib install commandline as last argument before the library names.
       It can be used e.g. to suppress dependency resolving for libraries by using --no-deps as argument string.
     default: ''
     required: false
-
   set-build-path:
     description: 'Flag to set the build directory (arduino-cli paramer --build-path) to /build subdirectory of compiled sketches.'
     default: 'false'
     required: false
-
   debug-compile:
     description: 'If set to "true" the action logs verbose compile output even during successful builds'
     default: ''
     required: false
-
   debug-install:
     description: 'If set to "true" the action logs verbose arduino-cli output during installation'
     default: ''
     required: false
-
 runs:
   using: 'composite'
   steps:
     - name: Compile all sketches / examples using the bash script arduino-test-compile.sh
       env:
-          # Passing parameters to the script by setting the appropriate ENV_* variables.
-   
... (truncated)
```

Locations:

- `action.yml`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection, prior-fix

**Notes:**

Replaced the inline `run: ${{ github.action_path }}/arduino-test-compile.sh` with the quoted runner env var `run: '"$GITHUB_ACTION_PATH/arduino-test-compile.sh"'` (shell: bash). This re-applies the previous harden's security change; it also removed blank lines, which was only cosmetic. All other expressions are already in the env: block.

