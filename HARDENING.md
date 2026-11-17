<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3

> This file was generated automatically by the hardening agent.

**Policy SHA:** `374911c4be584df24e6da57af2d990570ef0f859`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `2`

Action **ArminJo--arduino-test-compile/v3** was hardened automatically. 2 finding(s) were identified and resolved across 1 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Rule (a): a GitHub Actions expression is placed straight into a run: block in the composite step. The offending line is `run: ${{ github.action_path }}/arduino-test-compile.sh`. Use the shell env var instead: `run: "$GITHUB_ACTION_PATH/arduino-test-compile.sh"`.

Locations:

- `action.yml:113`

### prior-fix (severity: high)

Carried forward from this version's previous harden, which fixed it; fix it again unless the code no longer has the problem. The previous harden changed action.yml without recording a finding for it, and this analysis reported nothing there. Re-apply its security changes unless the code no longer needs them. The previous patch:
```diff
diff --git a/action.yml b/action.yml
index 0f2b960..db3327f 100644
--- a/action.yml
+++ b/action.yml
@@ -6,69 +6,57 @@ inputs:
     description: 'Version of arduino-cli to use when building. Current (9/2025) one is 1.3.1.'
     default: 'latest'
     required: false
-
   sketch-names:
     description: 'Comma sepatated list of patterns or filenames (without path, but with extension) of the sketch(es) to test compile. Useful if the sketch is a *.cpp or *.c file or only one sketch in the repository should be compiled.'
     default: '*.ino'
     required: false
-
   sketch-names-find-start:
     description: 'The start directory to look for the sketch-names to test compile. Can be a path like "digistump-avr/libraries/*/examples/C*/".'
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
     description: 'Comma separated list of platform specifiers, if you require a fixed version like "arduino:avr@1.8.2" or do not want the specifier derived from the 2 first elements of the arduino-board-fqbn or need more than one core. The suffix "@latest" is always removed.'
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
     description: 'Comma separated list of arduino library names required for compiling the sketches / examples for this board. Add version number by e.g. @1.2.0.'
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
       For example: build-properties: '{ "WhistleSwitch": "-DDEBUG -DFREQUENCY_RANGE_LOW", "SimpleFrequencyDetector": "-DINFO" }'.
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
     description: |
       Flag to set the build directory (arduino-cli paramer --build-path) to /build subdirectory of compiled sketches.
@@ -76,43 +64,55 @@ inputs:
       They are logged if debug-compile is set to "true".
     default: 'false'
     required: false
-
   debug-compile:
     description: 'If set to "true" the action logs verbose compile output even during successful builds.'
     default: ''
     required: false
-
   debug-install:
     description: 'If set to "true" the action logs verbose arduino-cli output during installation.'
     default: ''
     required: false
-
 runs:
   using: 'composite'
   steps:
     - n
... (truncated)
```

Locations:

- `action.yml`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection, prior-fix

**Notes:**

In action.yml, the run: line no longer has the ${{ github.action_path }} expression in it. It now runs the script as "$GITHUB_ACTION_PATH/arduino-test-compile.sh" (quoted, under bash). That expression was the only one in a run: line, because every input already reaches the script through env: variables.

The prior-fix diff I was given was cut off. The part I could see only deleted blank lines between the inputs, which has no security effect. I assume its hidden part made this same run: change, so this pass re-applies that, but I couldn't confirm it.

I searched arduino-test-compile.sh for curl/wget piped into a shell, eval, and writes to GITHUB_ENV/GITHUB_OUTPUT. The only match is a wget that downloads the arduino-cli tarball to a file, and nothing runs it as a script, so I left it alone. I didn't read the rest of the script line by line.

