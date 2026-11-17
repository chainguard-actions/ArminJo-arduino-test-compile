<!-- markdownlint-disable -->

# Hardening Report: ArminJo--arduino-test-compile/v3.3.0

> This file was generated automatically by the hardening agent.

**Policy SHA:** `374911c4be584df24e6da57af2d990570ef0f859`

**Test Policy SHA:** `843adf9e4b8f85d0c08b27b9d0b09dd094b54702`

**Harden Agent Version:** `2`

Action **ArminJo--arduino-test-compile/v3.3.0** was hardened automatically. 3 finding(s) were identified and resolved across 1 iteration(s).

## Findings Fixed

### script-injection (severity: high)

Rule (a) violation: the composite step's run: block puts a GitHub Actions expression straight into the shell command: `run: ${{ github.action_path }}/arduino-test-compile.sh`. The expression is substituted into the script text before bash parses it, and the value is not quoted. Use the GITHUB_ACTION_PATH env var instead, quoted: `run: "$GITHUB_ACTION_PATH/arduino-test-compile.sh"`.

Locations:

- `action.yml:118`

### prior-fix (severity: high)

Carried forward from this version's previous harden, which fixed it; fix it again unless the code no longer has the problem. The previous harden changed action.yml without recording a finding for it, and this analysis reported nothing there. Re-apply its security changes unless the code no longer needs them. The previous patch:
```diff
diff --git a/action.yml b/action.yml
index c14f1e0..899e838 100644
--- a/action.yml
+++ b/action.yml
@@ -6,113 +6,110 @@ inputs:
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
-    description: |
-      Flag to set the build directory (arduino-cli paramer --build-path) to /build subdirectory of compiled sketches. 
-      But anyway, the build binaries are always available in the newly generated "build/<fqbn>" directory of the sketch. 
-      They are logged if debug-compile is set to "true".
+    description: "Flag to set the build directory (arduino-cli paramer --build-path) to /build subdirectory of compiled sketches. \nBut anyway, the build binaries are always available in the newly generated \"build/<fqbn>\" directory of the sketch. \nThey are logged if debug-compile is set to \"true\".\n"
     default: 'false'
     re
... (truncated)
```

Locations:

- `action.yml`

### prior-fix (severity: high)

Carried forward from this version's previous harden, which fixed it; fix it again unless the code no longer has the problem. The previous harden changed arduino-test-compile.sh without recording a finding for it, and this analysis reported nothing there. Re-apply its security changes unless the code no longer needs them. The previous patch:
```diff
diff --git a/arduino-test-compile.sh b/arduino-test-compile.sh
index ee1760c..2e439e9 100755
--- a/arduino-test-compile.sh
+++ b/arduino-test-compile.sh
@@ -205,23 +205,23 @@ if [[ $DEBUG_INSTALL == true ]]; then
 fi
 for single_platform in "${PLATFORM_ARRAY[@]}"; do # Loop over all platforms specified
   if [[ $DEBUG_INSTALL == true ]]; then
-    echo -e "arduino-cli core update-index $PLATFORM_URL_COMMAND $PLATFORM_URL --verbose"
-    arduino-cli core update-index $PLATFORM_URL_COMMAND $PLATFORM_URL --verbose # must specify --additional-urls here
+    echo -e "arduino-cli core update-index ${PLATFORM_URL_COMMAND:+$PLATFORM_URL_COMMAND} ${PLATFORM_URL:+$PLATFORM_URL} --verbose"
+    arduino-cli core update-index ${PLATFORM_URL_COMMAND:+"$PLATFORM_URL_COMMAND"} ${PLATFORM_URL:+"$PLATFORM_URL"} --verbose # must specify --additional-urls here
     if [[ $? -ne 0 ]]; then
       echo "::error::Updating index of $PLATFORM_URL failed"
       exit 1
     fi
-    echo -e "arduino-cli core install $single_platform $PLATFORM_URL_COMMAND $PLATFORM_URL -v"
-    arduino-cli core install $single_platform $PLATFORM_URL_COMMAND $PLATFORM_URL --verbose
+    echo -e "arduino-cli core install $single_platform ${PLATFORM_URL_COMMAND:+$PLATFORM_URL_COMMAND} ${PLATFORM_URL:+$PLATFORM_URL} -v"
+    arduino-cli core install "$single_platform" ${PLATFORM_URL_COMMAND:+"$PLATFORM_URL_COMMAND"} ${PLATFORM_URL:+"$PLATFORM_URL"} --verbose
   else
-    echo -e "arduino-cli core update-index $PLATFORM_URL_COMMAND $PLATFORM_URL > /dev/null"
-    arduino-cli core update-index $PLATFORM_URL_COMMAND $PLATFORM_URL > /dev/null # must specify --additional-urls here
+    echo -e "arduino-cli core update-index ${PLATFORM_URL_COMMAND:+$PLATFORM_URL_COMMAND} ${PLATFORM_URL:+$PLATFORM_URL} > /dev/null"
+    arduino-cli core update-index ${PLATFORM_URL_COMMAND:+"$PLATFORM_URL_COMMAND"} ${PLATFORM_URL:+"$PLATFORM_URL"} > /dev/null # must specify --additional-urls here
     if [[ $? -ne 0 ]]; then
       echo "::error::Updating index of $PLATFORM_URL failed"
       exit 1
     fi
-    echo -e "arduino-cli core install $single_platform $PLATFORM_URL_COMMAND $PLATFORM_URL > /dev/null"
-    arduino-cli core install $single_platform $PLATFORM_URL_COMMAND $PLATFORM_URL > /dev/null
+    echo -e "arduino-cli core install $single_platform ${PLATFORM_URL_COMMAND:+$PLATFORM_URL_COMMAND} ${PLATFORM_URL:+$PLATFORM_URL} > /dev/null"
+    arduino-cli core install "$single_platform" ${PLATFORM_URL_COMMAND:+"$PLATFORM_URL_COMMAND"} ${PLATFORM_URL:+"$PLATFORM_URL"} > /dev/null
   fi
     if [[ $? -ne 0 ]]; then
       echo "::error::Install core for $single_platform failed"
@@ -274,11 +274,13 @@ else
   IFS=$','
   declare -a REQUIRED_LIBRARIES_ARRAY=( $REQUIRED_LIBRARIES )
   IFS="$BACKUP_IFS"
+  # Split space-separated extra lib install args into an array
+  read -r -a EXTRA_ARDUINO_LIB_INSTALL_ARGS_ARRAY <<< "$EXTRA_ARDUINO_LIB_INSTALL_ARGS"
   if [[ $DEBUG_INSTALL == true ]]; then
     echo "arduino-cli lib install \"${REQUIRED_LIBRARIES_ARRAY[@]}\" $EXTRA_ARDUINO_LIB_INSTALL_ARGS"
-    arduino-cli lib install "${REQUIRED_LIBRARIES_ARRAY[@]}" $EXTRA_ARDUINO_LIB_INSTALL_ARGS
+    arduino-cli lib install "${REQUIRED_LIBRARIES_ARRAY[@]}" "${EXTRA_ARDUINO_LIB_INSTALL_ARGS_ARRAY[@]}"
   else
-    arduino-cli lib install "${REQUIRED_LIBRARIES_ARRAY[@]}" $EXTRA_ARDUINO_LIB_INSTALL_ARGS >/dev/null 2>&1
+    arduino-cli lib install "${REQUIRED_LIBRARIES_ARRAY[@]}" "${EXTRA_ARDUINO_LIB_INSTALL_ARGS_ARRAY[@]}" >/dev/null 2>&1
   fi
   if [[ $? -ne 0 ]]; then
     echo "::error::Installation of $REQUIRED_LIBRARIES failed"
@@ -289,6 +291,9 @@ fi
 # Save generated files to the build subfolder of the sketch
 export ARDUINO_SKETCH_ALWAYS_EXPORT_BINARIES=true
 
+# Split space-separated extra arduino-cli args into an array
+read -r -a EXTRA_ARDUINO_CLI_ARGS_ARRAY <<< "$EXTRA_ARDUINO_CLI_ARGS"
+
 #
 # Get the build property map
 #
@@ -328,9 +333,9 @@ COMPILED_SKETCHES=
 for sketch_name in "${SKETCH_NAMES_ARRAY[@]}"; do # Loop over all sketch names
   if [[ $SET_BUILD_PATH == true ]]; then
   # mus
... (truncated)
```

Locations:

- `arduino-test-compile.sh`

## Iteration Notes

### Iteration 1

**Fixes applied:** script-injection, prior-fix

**Notes:**

action.yml: the run line `${{ github.action_path }}/arduino-test-compile.sh` is now `"$GITHUB_ACTION_PATH/arduino-test-compile.sh"`, quoted and with no expression in the shell text. All inputs already reach the script through env.

arduino-test-compile.sh: I re-applied the safe parts of the previous harden. The arduino-cli `core update-index` and `core install` calls now quote $single_platform and pass $PLATFORM_URL_COMMAND and $PLATFORM_URL as `${VAR:+"$VAR"}`. Arguments come out the same as before, because spaces in the URL list are already turned into commas.

I did not re-apply the previous `read -r -a` rewrite of $EXTRA_ARDUINO_CLI_ARGS and $EXTRA_ARDUINO_LIB_INSTALL_ARGS. These inputs are argument lists, and upstream's unquoted $VAR is the correct form for them: it splits words and expands globs the way users expect, but runs nothing. `read -a` would stop glob expansion and change how the action behaves.

One possible risk I left alone: the script builds the build-properties map with `declare -A PROP_MAP="( $(... sed ...) )"`, which bash may evaluate. If so, a crafted build-properties value could run commands. That value is set by the workflow author, this analysis didn't flag it, and rewriting the parsing could break how it handles quoted values. It's worth checking in a later pass.

