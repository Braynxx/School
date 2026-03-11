#!/usr/bin/env bash
set -u -o pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
TEST_DIR="$ROOT_DIR/tests"
SRC="${1:-/home/braynx/School/School/myA2/provided/q3/transformer.c}"
SAMPLE_BIN="${2:-/home/braynx/School/School/myA2/provided/q3/ppm_sample}"
BIN="/tmp/transformer_q3_tests"

pass=0
fail=0

compile() {
    if gcc -Wall -Wextra -Werror "$SRC" -o "$BIN"; then
        echo "[PASS] compile"
        pass=$((pass + 1))
    else
        echo "[FAIL] compile"
        fail=$((fail + 1))
        exit 1
    fi
}

check_output() {
    local label="$1"
    local input_file="$2"
    local expected_file="$3"
    shift 3

    local out_file
    local out_norm
    local expected_norm
    out_file="$(mktemp)"
    out_norm="$(mktemp)"
    expected_norm="$(mktemp)"

    if "$BIN" "$@" < "$input_file" > "$out_file"; then
        sed 's/[[:space:]]*$//' "$expected_file" > "$expected_norm"
        sed 's/[[:space:]]*$//' "$out_file" > "$out_norm"
        if diff -u "$expected_norm" "$out_norm" > /dev/null; then
            echo "[PASS] $label"
            pass=$((pass + 1))
        else
            echo "[FAIL] $label"
            diff -u "$expected_norm" "$out_norm" || true
            fail=$((fail + 1))
        fi
    else
        echo "[FAIL] $label (program exited non-zero)"
        fail=$((fail + 1))
    fi

    rm -f "$out_file" "$out_norm" "$expected_norm"
}

check_should_fail() {
    local label="$1"
    local input_file="$2"
    shift 2

    if "$BIN" "$@" < "$input_file" > /dev/null 2>&1; then
        echo "[FAIL] $label (expected failure but got success)"
        fail=$((fail + 1))
    else
        echo "[PASS] $label"
        pass=$((pass + 1))
    fi
}

compile

if "$ROOT_DIR/gen_expected_from_sample.sh" "$SAMPLE_BIN"; then
    echo "[PASS] generated expected outputs from ppm_sample"
    pass=$((pass + 1))
else
    echo "[FAIL] could not generate expected outputs from ppm_sample"
    fail=$((fail + 1))
    exit 1
fi

check_output "no flags" \
    "$TEST_DIR/small.ppm" \
    "$TEST_DIR/small_expected_none.ppm"

check_output "flip only (-f)" \
    "$TEST_DIR/small.ppm" \
    "$TEST_DIR/small_expected_flip.ppm" \
    -f

check_output "sepia only (-s)" \
    "$TEST_DIR/small.ppm" \
    "$TEST_DIR/small_expected_sepia.ppm" \
    -s

check_output "flip + sepia (-f -s)" \
    "$TEST_DIR/small.ppm" \
    "$TEST_DIR/small_expected_flip_sepia.ppm" \
    -f -s

check_output "sepia clamp" \
    "$TEST_DIR/clamp.ppm" \
    "$TEST_DIR/clamp_expected_sepia.ppm" \
    -s

check_should_fail "invalid magic should fail" \
    "$TEST_DIR/invalid_magic.ppm"

check_should_fail "invalid flag should fail" \
    "$TEST_DIR/small.ppm" \
    -x

echo
echo "Passed: $pass"
echo "Failed: $fail"

if [ "$fail" -ne 0 ]; then
    exit 1
fi
