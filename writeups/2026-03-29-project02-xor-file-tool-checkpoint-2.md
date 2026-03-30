# project02_xor_file_tool checkpoint 2

## Goal

Move the XOR file tool to a cleaner whole-file design and replace the temporary string-character key model with numeric parsing using `strtol`.

This is still a checkpoint, not the final project version.

## High-Value Mistakes

### 1. The key was treated as a short string instead of a numeric byte

An earlier version used:

```c
char key[3];
```

and later XORed with:

```c
key[0]
```

That worked mechanically, but it was the wrong model.

Why:
- `"4"` as text is the ASCII byte value for `'4'`
- that is not the same thing as validating and using numeric key `4`
- longer input like `1234` was silently truncated to `"12"` by the small input buffer

The fix direction was:
- read the key as a normal input line
- parse it as base-10 with `strtol`
- reject malformed or out-of-range values
- store the final key as `unsigned char`

## 2. `read_input` needed a clearer contract

The original input helper mainly wrapped `fgets`, newline trimming, and leftover-input flushing.

That was useful, but it did not clearly tell the caller whether:
- input read failed
- the line was too long and had to be flushed
- the line fit cleanly

The helper was reshaped to return distinct status codes so retry loops could be written correctly.

Important design lesson:
- input acquisition and input validation are separate responsibilities
- `read_input` should keep `stdin` clean and return status
- field-specific checks such as key parsing should happen later

## 3. Retry loops must only retry the retryable case

One intermediate retry loop treated every non-zero status the same.

That caused a control-flow bug:
- status `2` should retry
- statuses like read failure should stop the program

The corrected structure became:
- retry on the “input too long” status
- exit on hard failure statuses

This was an important control-flow cleanup rather than just a cosmetic refactor.

## 4. Whole-file processing required chunked looping, not one `fread`

The earlier 300-byte break test showed:
- original file: 300 bytes
- encrypted file: 256 bytes
- decrypted file: 256 bytes

That proved the program was still doing only one read.

The design then moved to the correct file-processing pattern:
- `fread` into a chunk buffer
- XOR exactly `nread` bytes
- `fwrite` exactly `nread` bytes
- repeat until EOF

After that change:
- `wc -c big.txt big.enc big.dec` showed `300 300 300`
- `cmp big.txt big.dec` succeeded

That was the key milestone of this checkpoint.

## Current State at This Checkpoint

By this point, the project had:
- a cleaner `read_input` helper built around `fgets`, `strchr`, and leftover-input flushing
- retry loops for oversized input
- input and output files opened in binary mode
- whole-file XOR processing using repeated `fread`/`fwrite`
- a numeric-key direction using `strtol`

Still unfinished:
- the key prompt/range handling still needs final polish
- `fwrite` result checking should be added
- some error messages still need cleanup
- `convert_to_home` still has rough edges and should eventually be simplified or constrained

## Lessons Learned

- string input and numeric parsing should not be collapsed into one step
- `strtol` is the right tool when another C programmer should be able to understand and maintain the code
- one `fread` call is one chunk read, not whole-file processing
- chunked processing is simple, efficient, and easier to scale than whole-file heap allocation
- retry loops should be written around explicit status codes, not vague “non-zero means retry” assumptions
