# C to Cybersecurity Journey

This repository tracks my hands-on path from C beginner to cybersecurity practitioner.

## Goal
Build strong low-level foundations in C, then apply them to secure coding, networking, and vulnerability analysis in legal lab environments.

## Learning Approach
I learn by doing and by making mistakes.

Workflow for every exercise:
1. I write the code myself.
2. I run and break it.
3. I document the mistake.
4. I fix it with guidance.
5. I write a short lesson learned.

## Repository Structure
- `notes/` concept notes, commands, debugging insights
- `labs/` small focused exercises and experiments
- `projects/` larger roadmap projects
- `writeups/` postmortems and security lessons from mistakes

Host-specific setup issues are documented in `notes/phase0.md`.

## Current Roadmap
The detailed roadmap is in `journey.md`:
- Phase 0: setup and baseline
- Phase 1: C fundamentals and memory
- Phase 2: Linux internals and secure coding
- Phase 3: networking and packet analysis
- Phase 4: vulnerability fundamentals
- Phase 5: specialization track

## AI Assistance Policy
I use AI as a reviewer and safety guide, not as a code generator.

### What AI does
- Reviews my code for bugs, undefined behavior, and security risks.
- Points out dangerous mistakes (memory issues, unsafe APIs, bad assumptions).
- Suggests debugging steps, test cases, and learning checkpoints.
- Helps me stay aligned with the roadmap in `journey.md`.

### What AI does not do
- Does not write final code for me.
- Does not bypass learning by giving full copy-paste solutions.
- Does not perform unauthorized/offensive actions outside legal lab scope.

### Mistake-First Agreement
I intentionally allow myself to make non-critical mistakes as part of learning.

AI should:
- allow non-critical mistakes to happen first;
- intervene only for critical risks:
  - memory corruption / undefined behavior;
  - unsafe patterns that can become dangerous habits;
  - legal/ethical violations;
  - major deviation from the roadmap.
- guide with minimal hints before full explanation, so I can debug first.

### My learning rule
I write the code first.
AI helps me understand failures, fix root causes, and improve engineering discipline.

## Rules
- Practice only in isolated, self-owned labs.
- Never test systems without permission.
- Treat warnings as errors.
- Fix sanitizer issues before adding features.

## C Build Baseline
Use this default compile setup:

```bash
gcc -std=c17 -Wall -Wextra -Werror -g -fsanitize=address,undefined main.c -o main
```

## Progress Log
I will update this repo weekly with:
- at least 1 completed lab
- at least 1 writeup
- project milestone updates
