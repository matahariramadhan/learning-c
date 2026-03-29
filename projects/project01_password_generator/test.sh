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

if printf "hahah\n" | ./main >/dev/null 2>&1; then
    fail "non-numeric input should fail"
else
    pass "non-numeric input"
fi

if printf "0\n" | ./main >/dev/null 2>&1; then
    fail "zero length should fail"
else
    pass "zero length"
fi

if printf -- "-5\n" | ./main >/dev/null 2>&1; then
    fail "negative length should fail"
else
    pass "negative length"
fi

if printf "100\n" | ./main >/dev/null 2>&1; then
    fail "too-large length should fail"
else
    pass "too-large length"
fi

output="$(printf "8\n" | ./main)" || fail "valid length should succeed"

password="$(printf "%s\n" "$output" | sed -n 's/.*Your password: //p' | tail -n 1)"

[ -n "$password" ] || fail "password line not found"
[ "${#password}" -eq 8 ] || fail "password length should be 8"

printf "%s" "$password" | grep -Eq '^[a-zA-Z0-9]+$' || fail "password contains invalid characters"

pass "valid password generation"
echo "All tests passed"

