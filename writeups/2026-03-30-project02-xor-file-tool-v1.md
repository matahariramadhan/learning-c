# project02_xor_file_tool v1

## Goal

Finish a usable Phase 1 XOR file tool that:
- asks for an input file path
- validates and opens the input file early
- reads a numeric XOR key from the user
- asks for an output path
- processes the entire file in chunks
- writes the transformed file out safely

## High-Value Mistakes

### 1. Trying to compress too much logic into one `while` condition made the code worse

One attempted refactor tried to combine:
- `read_input(...)`
- `convert_to_home(...)`
- `fopen(...)`

inside one large `while (...)` condition.

That looked compact, but it was a bad design:
- hard to read
- hard to debug
- easy to get precedence wrong
- mixed retryable and fatal cases in one boolean expression

The fix was to go back to explicit control flow:
- loop
- inspect `read_input` status
- retry only the retryable case
- run `convert_to_home`
- try `fopen`
- continue or break

This was an important lesson in maintainable C:
- shorter syntax is not automatically clearer code

### 2. The input file should be opened before asking for later inputs

Earlier versions asked for:
- input file path
- key
- output path

and only then tried to open the input file.

That created a bad user experience:
- the user could type everything correctly after the path
- and only then be told that the first path was bad

The flow was corrected to:
1. read input file path
2. expand `~` if needed
3. open input file immediately
4. only then ask for key and output path

This was a simple but important usability improvement.

### 3. The key model needed to be numeric, not string-shaped

An earlier version treated the key like a short string and used `key[0]`.

That was mechanically workable, but it was the wrong abstraction.

The corrected v1 direction was:
- read key input as text
- parse with `strtol`
- validate allowed range
- store as `unsigned char`

For this v1, the user chose to keep the key range as:
- `0` through `9`

So the tool now validates the key as a decimal number in that range.

### 4. Whole-file processing needed both write checking and read-error checking

The earlier chunked version fixed truncation, but it still needed the standard file-I/O checks:
- verify `fwrite(...) == nread`
- check `ferror(file)` after the read loop

Those checks completed the core I/O discipline for v1:
- read chunk
- XOR chunk
- write chunk
- verify write succeeded
- after loop, verify the read did not stop because of stream error

## Current State in v1

The tool now has:
- `read_input` as a line-input helper with explicit status codes
- retry loops that distinguish retryable and fatal cases
- early input-file opening
- `~` expansion helper for simple home-path input
- numeric key parsing with `strtol`
- binary input/output file modes
- chunked `fread`/`fwrite` processing across the whole file
- write checking and read-error checking

Known rough edges still left for later polish:
- some prompts/messages are inconsistent in wording
- `convert_to_home` still expands `~` more broadly than ideal and is the roughest helper in the file
- some cosmetic cleanup remains, but the core behavior is coherent

## Lessons Learned

- input acquisition and semantic validation should be separate steps
- retry loops should only retry the retryable case
- opening important resources earlier improves both logic and UX
- chunked processing is the right default for file tools
- `strtol` is a better long-term choice than ad hoc string-digit handling when maintainability matters
- a v1 is done when the core behavior is correct and testable, not when every small cosmetic issue is gone
