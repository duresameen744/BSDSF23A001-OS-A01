# REPORT.md — Feature 2 (Multi-file Project using Make Utility)

**Name:** Dure Sameen
**Roll No:** BSDSF23A001
**Project:** Programming Assignment 1 — BSDSF23A001-OS-A01
**Feature:** 2 — Multi-file Project using Make Utility
**Date started:** 21-09-2025

---

## 1. Short summary

Feature-2 demonstrates how to build a C project composed of multiple `.c` files using a recursive `Makefile` approach. The project compiles source files in `src/`, places object files in `obj/`, and the final executable in `bin/client`. This feature also includes versioning via a git branch, an annotated tag, and a GitHub release with the compiled binary.

---

## 2. What I implemented (files & structure)

```
BSDSF23A001-OS-A01/
├── src/
│   ├── main.c
│   ├── mystrfunctions.c
│   └── myfilefunctions.c
├── include/
│   ├── mystrfunctions.h
│   └── myfilefunctions.h
├── bin/
│   └── client        # compiled executable (uploaded to GitHub release)
├── obj/
│   └── *.o           # compiled object files
├── Makefile          # top-level (recursive) Makefile
├── src/Makefile      # src Makefile that builds objects and links
├── test.txt
└── REPORT.md
```

---

## 3. How to build and run (reproducible steps)

From project root:

```bash
# Build everything (top-level Makefile delegates to src/)
make

# or build only in src
make -C src

# Run the program
./bin/client
# or make -C src run
```

If you need debug symbols instead of optimization:

```bash
make -C src DEBUG=1
```

---

## 4. Makefile notes (what I used and why)

* **Top-level Makefile:** simply calls `make` inside `src/` so the build can be separated by directory. This is the recursive approach and keeps the root Makefile short and clear.
* **src/Makefile (key parts)**:

  * `CC := gcc` — compiler variable so it can be easily changed.
  * `CFLAGS := -Wall -Wextra -I../include` — enable warnings and tell compiler where headers are.
  * Debug switch: build with `DEBUG=1` to enable `-g -O0`.
  * `SOURCES := $(wildcard $(SRCDIR)/*.c)` — auto-collects .c files.
  * `OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))` — maps sources to object files.
  * Pattern rule `$(OBJDIR)/%.o: $(SRCDIR)/%.c` compiles each `.c` into an `.o`.
  * **Link rule**: `$(TARGET): $(OBJECTS)` links object files into the final binary.

**Why this layout?** It keeps intermediate files in `obj/`, keeps the binary in `bin/`, and ensures `make` only rebuilds what changed.

---

## 5. Report questions — answered plainly

### Q1: Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from linking against a library?

**Answer (plain):** This rule says: "to make the final program (TARGET), first make sure every object file in \$(OBJECTS) is present; then call the linker to combine those object files into an executable." When linking against a library, instead of feeding many object files directly to the linker, you give the linker a pre-built archive (a `.a` file) or shared library (`.so`) via flags like `-L` (where to look) and `-l` (which library). The linker then extracts only the needed pieces from the library. With `$(OBJECTS)` you are linking raw object files you built just now; with a library the objects are packaged and potentially reused across multiple programs.

### Q2: What is a git tag and why is it useful? Difference between simple and annotated tags?

**Answer (plain):** A git tag is a named pointer to a particular commit used to mark a release point (like "v0.1.1"). A **lightweight tag** is just a name pointing to a commit (quick and simple). An **annotated tag** stores extra information (tagger, date, message) and is preferred for releases because it carries metadata and a message describing the release.

### Q3: What is the purpose of creating a GitHub "Release" and what is the significance of attaching binaries?

**Answer (plain):** A GitHub Release is a nice public page that ties a tag to human-readable release notes and optional downloadable files. Attaching binaries (like `bin/client`) makes it easy for people (or graders) to download a ready-to-run program without compiling the source code themselves.

---

## 6. Commands I ran (important log entries)

Examples you can paste into a terminal to verify your state:

```bash
# Check current branch
git branch --show-current

# Show recent commits
git log --oneline --decorate -n 10

# Check tags
git tag -l

# Show tag details
git show v0.1.1-multifile

# Ensure local main is up to date after merging on GitHub
git checkout main
git pull origin main

# Push any outstanding tags
git push origin --tags

# Commit and push REPORT.md (if not yet pushed):
git add REPORT.md
git commit -m "Add REPORT for Feature-2: Makefile, build, release"
git push origin main
```

---

## 7. Verification checklist (what I completed)

* [x] Created `multifile-build` branch and worked there.
* [x] Implemented `mystrfunctions.h` / `myfilefunctions.h`.
* [x] Implemented `mystrfunctions.c`, `myfilefunctions.c`, `main.c`.
* [x] Created `test.txt` for file function tests.
* [x] Created recursive Makefiles (top-level + `src/Makefile`).
* [x] Built and tested the binary `bin/client` using `make`.
* [x] Created annotated tag `v0.1.1-multifile` and pushed it.
* [x] Drafted and published GitHub Release and attached `bin/client`.
* [x] Merged `multifile-build` into `main`.

If all of the above are true on your GitHub repository, Feature-2 is complete.

---

## 8. Next steps and notes

* If you merged on GitHub using the web UI, run `git checkout main && git pull origin main` locally so your local main matches remote.
* Ensure `REPORT.md` is added, committed, and pushed to the `main` branch (or leave it in `multifile-build` until you are ready to merge).
* Push any remaining tags: `git push origin --tags`.

---

## 9. Sample GitHub release description (copy/paste)

**Title:** Version 0.1.1: Multi-file Build

**Description:** Basic multi-file compilation for libmyutils. This release contains:

* Sources in `src/` (string and file utilities)
* Recursive Makefiles (top-level and `src/`)
* Compiled binary `bin/client` (Linux x86\_64)

---

---

*End of REPORT.md — Feature-2*
