#!/bin/sh

TMPDIR=$(mktemp -d)

TEST_SIZE=1000
mkdir "$TMPDIR/$TEST_SIZE"
TMPNAME=$(head -c 10 /dev/urandom | base64 | tr -d "=" | tr "+/" "-_")
head -c $TEST_SIZE /dev/urandom > "$TMPDIR/$TEST_SIZE/input"
./s4s split "$TMPDIR/$TEST_SIZE/output-$TMPNAME" "$TEST_SIZE" < "$TMPDIR/$TEST_SIZE/input"
./s4s join "$TMPDIR/$TEST_SIZE/output-$TMPNAME" > "$TMPDIR/$TEST_SIZE/result"
if ! cmp --silent -- "$TMPDIR/$TEST_SIZE/result" "$TMPDIR/$TEST_SIZE/input"
then
    echo "Failed!" 1>&2
fi
rm -rf "$TMPDIR/$TEST_SIZE"
