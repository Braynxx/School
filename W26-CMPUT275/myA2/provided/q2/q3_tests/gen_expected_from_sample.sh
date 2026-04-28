#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
TEST_DIR="$ROOT_DIR/tests"
PPM_SAMPLE="${1:-/home/braynx/School/School/myA2/provided/q3/ppm_sample}"

if [ ! -x "$PPM_SAMPLE" ]; then
    echo "ppm_sample not found or not executable: $PPM_SAMPLE" >&2
    exit 1
fi

"$PPM_SAMPLE" < "$TEST_DIR/small.ppm" > "$TEST_DIR/small_expected_none.ppm"
"$PPM_SAMPLE" -f < "$TEST_DIR/small.ppm" > "$TEST_DIR/small_expected_flip.ppm"
"$PPM_SAMPLE" -s < "$TEST_DIR/small.ppm" > "$TEST_DIR/small_expected_sepia.ppm"
"$PPM_SAMPLE" -f -s < "$TEST_DIR/small.ppm" > "$TEST_DIR/small_expected_flip_sepia.ppm"
"$PPM_SAMPLE" -s < "$TEST_DIR/clamp.ppm" > "$TEST_DIR/clamp_expected_sepia.ppm"

echo "Generated expected files from: $PPM_SAMPLE"
