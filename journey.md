# Cybersecurity Learning Journey (C-First)

## Objective
Build strong cybersecurity fundamentals by mastering C, Linux, networking, and secure coding, then applying them in legal lab environments.

## Ground Rules
- [ ] Practice only in isolated, self-owned labs (VMs/CTFs).
- [ ] Never scan or test systems without explicit permission.
- [ ] Keep a learning log: what you built, what broke, what you fixed.

## Weekly Cadence (6-10 hours/week)
- [ ] 3 hours theory (read/watch/docs)
- [ ] 4 hours coding/labs
- [ ] 1 hour write-up and review
- [ ] 1-2 hours challenge practice (CTF or wargame)

## Phase 0 (Week 1): Setup and Baseline
Focus: Build your lab and toolchain.

- [ ] Install Linux VM (Ubuntu is fine).
- [ ] Install `build-essential`, `gdb`, `valgrind`, `tcpdump`, `wireshark`, `nmap`.
- [ ] Learn shell basics (`cd`, `ls`, `cat`, `grep`, `find`, pipes, redirection).
- [ ] Create this repo structure:
  - [ ] `notes/`
  - [ ] `labs/`
  - [ ] `projects/`
  - [ ] `writeups/`

## Phase 1 (Weeks 2-5): C Fundamentals for Security
Focus: Memory, pointers, and bug patterns.

- [ ] Variables, control flow, functions, and scope.
- [ ] Arrays, strings, `struct`, and file I/O.
- [ ] Pointers and pointer arithmetic.
- [ ] Dynamic memory (`malloc`, `calloc`, `realloc`, `free`).
- [ ] Debugging with `gdb` and memory checks with `valgrind`.

Projects:
- [ ] Build a CLI password generator (length, charset flags, entropy estimate).
- [ ] Build a binary-safe XOR file tool (encrypt/decrypt with key input).

Milestone:
- [ ] Explain stack vs heap clearly and debug a memory bug end-to-end.

## Phase 2 (Weeks 6-8): Computer Systems and Linux Internals
Focus: How programs execute and interact with OS.

- [ ] Process model, system calls, files, permissions.
- [ ] ELF basics and program loading (high-level).
- [ ] Signals, environment variables, and PATH risk awareness.
- [ ] Safe/unsafe C APIs (`strncpy` vs `strcpy`, bounds checks).

Projects:
- [ ] Build a mini `strings`-like utility for binary/text files.
- [ ] Build a secure log parser with strict input validation.

Milestone:
- [ ] Identify and fix at least 5 unsafe code patterns in your own code.

## Phase 3 (Weeks 9-12): Networking and Traffic Analysis
Focus: Protocols, sockets, and packet visibility.

- [ ] TCP/IP model, ports, handshake, DNS, HTTP basics.
- [ ] Client/server sockets in C (`<sys/socket.h>`).
- [ ] Packet capture fundamentals with `tcpdump`/Wireshark.

Projects:
- [ ] Build a TCP port scanner for localhost/lab subnet only.
- [ ] Build a basic packet header parser (IP/TCP fields) from captured data.

Milestone:
- [ ] Capture traffic from your own app and explain each packet step.

## Phase 4 (Weeks 13-16): Vulnerability Fundamentals (Defensive Lens)
Focus: Understand exploitation concepts so you can prevent them.

- [ ] Buffer overflows, integer overflows, format-string issues (conceptual + lab).
- [ ] Mitigations: ASLR, NX, stack canaries, RELRO (what each does).
- [ ] Input validation, least privilege, secure defaults.

Projects:
- [ ] Write intentionally vulnerable lab code, then patch and harden it.
- [ ] Produce before/after report with root cause and mitigation.

Milestone:
- [ ] Demonstrate one vulnerability and one mitigation in your lab only.

## Phase 5 (Weeks 17-24): Applied Cybersecurity Track
Focus: Pick one specialization while keeping fundamentals active.

Choose one primary track:
- [ ] Reverse engineering and malware analysis (safe samples, static analysis).
- [ ] Web security and bug bounty fundamentals (OWASP Top 10).
- [ ] Blue team and detection engineering (logs, alerts, triage).

Core outcomes (for any track):
- [ ] 3 complete write-ups in `writeups/`.
- [ ] 1 polished portfolio project in `projects/`.
- [ ] 20+ challenge solves with notes.

## Tools to Master
- [ ] C toolchain: `gcc`, `make`, `gdb`, `valgrind`
- [ ] Networking: `tcpdump`, Wireshark, `nmap`, `netcat`
- [ ] Linux basics: `ps`, `top`, `ss`, `lsof`, `strace`
- [ ] Workflow: `git`, Markdown documentation, issue checklist

## Progress Dashboard
- [ ] Daily: at least 30 minutes focused practice
- [ ] Weekly: 1 lab completed + 1 short write-up
- [ ] Monthly: 1 project milestone demo
- [ ] Quarterly: update CV/portfolio with concrete artifacts

## Optional Certifications (Later, Not First)
- [ ] Security+ (broad foundation)
- [ ] eJPT or PNPT (hands-on entry penetration testing)
- [ ] OSCP (advanced, after strong fundamentals)

## Definition of Success (6 Months)
- [ ] You can read and write non-trivial C safely.
- [ ] You can debug memory and logic bugs independently.
- [ ] You can analyze basic network traffic and explain findings.
- [ ] You have a public portfolio of labs, projects, and security write-ups.
