# project02_xor_file_tool checkpoint 1

## Goal

Start the second Phase 1 project by building the input-handling and file-opening foundation for a simple XOR file tool.

This checkpoint is not the finished project. It records the current milestone and the important bugs uncovered along the way.

## High-Value Mistakes

### 1. Mixing `scanf` and `fgets` caused skipped input

An early version read the path with `fgets`, then the key with `scanf`, then the output path with `fgets`.

Problem:
- `scanf("%d", &key)` parsed the integer
- the trailing newline remained in `stdin`
- the next `fgets` saw that leftover newline immediately
- the output path looked like it was skipped

Important lesson:
- the newline was not stored in `key`
- it was still waiting in the input stream

### 2. Debugger inspection changed the input stream

While investigating the skipped-input bug, `gdb` was used to call:

```gdb
print getchar()
```

That did reveal the leftover newline value, but it also changed the program state.

Why:
- `getchar()` is not a passive inspection
- it consumes a character from `stdin`

This was an important debugging lesson:
- debugger function calls can mutate runtime state

### 3. The first key-handling design was conceptually wrong

There were several wrong attempts:
- trying to run `trim_newline` on an `int`
- trying to read the key with `fgets` into a single `char`

Why those were wrong:
- the leftover newline problem was in `stdin`, not inside the parsed integer
- a single `char` is not a valid line buffer for `fgets`

That led to a temporary learning-stage design where the key was read as a small string buffer instead.

### 4. `convert_to_home` had multiple pointer/string bugs

This helper exposed several real mistakes:

- using `sizeof home` after `char *home = getenv("HOME");`
  - wrong because `home` is a pointer, not an array
- expanding `~` but originally losing the rest of the path suffix
- returning before the transformed buffer had actually been copied back into the original path

These bugs were diagnosed with `gdb` by inspecting the intermediate string state.

### 5. Text-line file reading is not the final XOR design

The checkpoint currently opens the input file and reads with `fgets`.

That revealed two design issues:
- `fgets` only reads one text line, not the whole file
- `%s` printing of the encrypted buffer became unstable because the transformed bytes were not a valid C string

This clarified the next architectural step:
- the final XOR tool should use `fread` and `fwrite` on raw byte buffers

### 6. Embedded null bytes exposed string-thinking in file processing

A file containing:

```text
A\0B\n
```

was used as a break test.

What it exposed:
- the first XOR loop stopped when it saw `'\0'`
- that treated binary file data as if it were a C string
- everything after the embedded null byte was ignored

That bug was then patched so the loop processed all bytes up to `nread`, not up to a string terminator.

This was an important shift:
- file data is not a string
- embedded `'\0'` bytes are normal file content

### 7. Large-file testing exposed the single-chunk limitation

A 300-byte file was used as a break test.

Observed result:
- original file: 300 bytes
- encrypted file: 256 bytes
- decrypted file: 256 bytes

The comparison tools used were:

```bash
wc -c big.txt big.enc big.dec
cmp big.txt big.dec
```

The result made the current limitation obvious:
- the program only performs one `fread(...)`
- so it only processes the first 256-byte chunk
- anything after that is ignored

This is the next structural bug to fix.

## Current State at This Checkpoint

By this point, the project had achieved:
- safer terminal input handling with `fgets`
- newline trimming helper
- leftover-input flushing helper
- a higher-level `read_input` helper
- a first pass at `~` path expansion
- successful file opening for the input path
- a first byte-transformation attempt using XOR
- a fix for the embedded-null-byte truncation bug

But it was still not finished because:
- file reading was still line-based, not byte-based
- the key model was still temporary
- output writing logic still needed refinement
- whole-file streaming was still missing; only one chunk was processed

## Lessons Learned

- input bugs often come from `stdin` state, not just variable values
- `gdb` can help find stream/input bugs, but function calls inside the debugger can also change the bug
- pointer size is not string length
- path expansion and string rewriting require careful attention to `'\0'`
- successful `fopen` is only the start; cleanup and later failure paths still matter
- a binary-safe XOR file tool needs byte-oriented I/O, not string-oriented I/O
- binary data must be processed according to byte count, not string terminators
- large-file tests are valuable because they expose single-read assumptions immediately
