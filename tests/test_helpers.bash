#!/usr/bin/env bash

# Determine the absolute path to this script's directory
TEST_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Paths to bats-support, bats-assert and bats-file (some tests require bats-file helpers)
SUPPORT_DIR="${TEST_DIR}/bats-support"
ASSERT_DIR="${TEST_DIR}/bats-assert"
FILE_DIR="${TEST_DIR}/bats-file"

# Verify that required dependencies exist
if [ ! -d "$SUPPORT_DIR" ] || [ ! -d "$ASSERT_DIR" ]; then
  echo "ERROR: Could not find bats-support or bats-assert directories in ${TEST_DIR}" >&2
  exit 1
fi

# Load bats-support and bats-assert
load "${SUPPORT_DIR}/load.bash"
load "${ASSERT_DIR}/load.bash"

# Optionally load bats-file helpers if present (provides assert_file_exist and related functions)
if [ -d "$FILE_DIR" ]; then
  load "${FILE_DIR}/load.bash" || true
fi

# Add both build/ and project root to PATH
PATH="${PROJECT_ROOT}/build:${PROJECT_ROOT}:$PATH"
export PATH

# Optional global test timeout
export BATS_TEST_TIMEOUT=10