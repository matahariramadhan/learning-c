#!/usr/bin/env bash
set -eu

fail() {
    echo "FAIL: $1"
    exit 1
}

pass() {
    echo "PASS: $1"
}

make >/dev/null

tmpdir="$(mktemp -d)"
trap 'rm -rf "$tmpdir"' EXIT

input="$tmpdir/input.txt"
output="$tmpdir/output.bin"
expected="$tmpdir/expected.bin"

printf 'Hello XOR\n' > "$input"

run_output="$(printf "%s\n4\n%s\n" "$input" "$output" | ./main 2>&1)" || fail "valid run should succeed"

[ -f "$output" ] || fail "output file was not created"

python3 - <<'PY' "$input" "$expected"
import sys
src = open(sys.argv[1], "rb").read()
key = ord("4")
enc = bytes([b ^ key for b in src])
open(sys.argv[2], "wb").write(enc)
PY

cmp -s "$output" "$expected" || fail "output content does not match current XOR behavior"
pass "valid run with absolute paths"

if printf "%s\n4\n%s\n" "/does/not/exist.txt" "$output" | ./main >/dev/null 2>&1; then
    fail "nonexistent input should fail"
else
    pass "nonexistent input"
fi

echo "All tests passed"
