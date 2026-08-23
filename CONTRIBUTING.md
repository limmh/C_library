# Contributing

Thank you for your interest in contributing to this project.
This document explains how to report issues, propose changes, and submit code in a way that makes review and maintenance efficient.
It assumes the project goals described in README.md: portability, correctness, testability, explicit allocator and error handling policies for C and C++ usage.

## Table of contents

- [Before you start](#before-you-start)
- [Report a bug or request a feature](#report-a-bug-or-request-a-feature)
- [Working on code](#working-on-code)
  - [Repository setup](#repository-setup)
  - [Branching and commits](#branching-and-commits)
  - [Code style and language constraints](#code-style-and-language-constraints)
  - [Allocators, errors, and object lifetimes](#allocators-errors-and-object-lifetimes)
  - [Tests and CI](#tests-and-ci)
  - [Documentation and examples](#documentation-and-examples)
- [Pull request process](#pull-request-process)
- [Review and acceptance](#review-and-acceptance)
- [Small PR checklist](#small-pr-checklist)
- [Contributor License Agreement (CLA)](#contributor-license-agreement-cla)
- [Code of Conduct](#code-of-conduct)
- [Contact](#contact)

## Before you start

- Read README.md and the API contract (API documentation in repository) to understand design choices: C89 and C++03 target standards, allocator usage, and emphasis on safety and testability.
- Search existing issues and pull requests to avoid duplicate work.
- If your change is a non-trivial feature or design change (API shape, semantics, or error model), open an issue first describing the proposal and rationale and invite for discussion.

## Report a bug or request a feature

Create a clear issue:
- Title: short and descriptive.
- Body: environment (OS, compiler + version, CMake version), steps to reproduce, expected vs actual behavior, minimal test code to reproduce the issue, relevant log or output, and Git commit if applicable.
- Label: bug/feature/enhancement (maintainers will help tag).

##  Working on code

### Repository setup

1. Clone the repo:
   ```
   git clone https://github.com/limmh/C_library.git
   ```
2. Create a build directory:
   ```
   mkdir build && cd build
   ```
3. Configure with CMake (additional parameters may be required depending on your compiler):
   ```
   cmake -S .. -B .
   ```
4. Build:
   ```
   cmake --build . -j 10
   ```
   Note: The integer value after -j is the number of parallel jobs during build. It can be specified based on your system.
5. Run all unit tests:
   ```
   ctest --output-on-failure
   ```

### Branching and commits

- Work on a feature branch named descriptively:
  - feature/<short-description> (new functionality)
  - fix/<short-description> (bug fixes)
  - docs/<short-description> (docs only)
- Keep commits small and focused. Each commit should be a single logical change.
- Write clear commit messages:
  - Subject line: one short sentence.
  - Optional info:
    - Blank line.
    - Body: what, why, and any notes about backwards compatibility or required followups.
- Rebase rather than merge when updating branches before opening a PR (maintainers may squash/merge when appropriate).

### Code style and language constraints

- Target language standards:
  - C: C89 for library code, C89 or C99 for test code or test applications
  - C++: C++03 (avoid C++11+ features).
- Forbidden/limited features:
  - Avoid reliance on implementation-specific or undefined behavior.
  - Identifier names shall not start with any underscores (single, double or more).
- Prefer:
  - Small, well-documented functions and modules.
  - Pure functions for non-container APIs.
  - Value semantics where practical, for large buffers use allocator-aware handles with explicit ownership.
  - Const correctness in both C and C++ interfaces.
  - Descriptive identifiers and concise comments for non-obvious decisions.
  - Snake case for variable names, function names and type names.
- Headers and visibility:
  - Public APIs must be callable from C code (extern "C" when compiled as C++) with opaque types where appropriate.
  - Keep implementation details in .c or.cpp source files, expose only what callers need.
- Macros:
  - Macros are allowed where necessary (e.g., for type-generic convenience), but prefer inline functions that avoid double evaluation and improve diagnostics.
- Warnings:
  - Fix compiler warnings related to undefined behavior in library code.

## Allocators, errors, and object lifetimes

- All dynamic allocation in public APIs must be allocator-aware:
  - Use the repository’s allocator_type API for dynamic memory.
  - Allocators must return NULL on allocation failure and must never throw any C++ exceptions.
- Code must follow two-phase initialization or factories when allocation or initialization can fail:
  - Factory functions should return NULL (or error results) on allocation failure and perform explicit cleanup.
- Error handling:
  - Use explicit error codes or enums (documented in headers) for public functions. Do not use C++ exceptions for C APIs.
  - Document what failure means and what state callers can expect after a failed call (no partial modifications, rollback semantics, etc.).
- Lifetime and ownership:
  - Document ownership for every API (who owns the buffer, who must free it).
  - Prefer returning pointers to internal data only when lifetime is clearly documented and safe.

### Tests and CI

- Tests are required for behavioral changes and bug fixes. Add unit tests for the functional core principally using provided unit testing harness.
- Tests should be deterministic where possible. For non-deterministic tests, document seed control and reproducibility.
- Run the test suite locally before opening a PR:
  - Build with sanitizers locally: set CFLAGS/CXXFLAGS to include -fsanitize=address,undefined -g -O1 and run tests to detect UB and memory errors.
- Add regression tests for previously found bugs (include the failing case if practical).
- CI:
  - Keep PRs small so CI completes quickly. CI will include builds and sanitizer runs.
  - Maintainers will configure additional CI (sanitizers, Windows builds, fuzz jobs) as needed.

### Documentation and examples

- Update README.md, module-level READMEs, and header comments for any API changes.
- Provide usage examples and update sample programs when you change public APIs.
- If you add a new module, include a brief README describing purpose, constraints, key functions, and allocator or error semantics.

## Pull request process

- Ensure tests pass locally.
- Open a pull request against the default branch (usually main or master). PR description should include:
  - Summary of changes.
  - Motivation and design decisions.
  - Backward compatibility notes and migration steps (if any).
  - Link to the related issue (if any).
  - How to build and run the new tests.
- Keep PRs small and focused. For large refactors, open an RFC issue first to get design buy-in.
- Be responsive to review feedback. Iteration on PRs is expected and welcomed.

## Review and acceptance

- Review focuses on correctness, safety, portability and test coverage where applicable.
- Maintainers may request changes, tests, or documentation updates before merging.
- Maintain backward compatibility unless a breaking change is explicitly discussed and approved in an issue.
- Maintain the project’s intent: correctness and testability take precedence over micro-optimizations unless clearly justified with benchmarks.

## Small PR checklist

- [ ] The test suite is run locally and all tests pass.
- [ ] New public APIs include clear docs: ownership, allocator usage, error returns, thread-safety.
- [ ] Added or updated unit tests that exercise the change (and regression tests for bugs).
- [ ] Changes are limited in scope and well documented in the commit messages or PR description.
- [ ] No compiler warnings related to undefined behavior.

## Contributor License Agreement (CLA)

- Contributions are licensed under the project’s MIT License by submitting a PR.
- If your contribution includes code from another source, include the source and license and ensure compatibility with MIT.
- Ask maintainers if you are unsure.

## Code of Conduct

This repository follows the Code of Conduct (CODE_OF_CONDUCT.md). Be respectful and collaborative. Report violations as described in the Code of Conduct.

## Contact

Repository owner / maintainer: limmh (@limmh).

For contribution questions that are not appropriate for a public issue, indicate in the issue that you prefer private follow-up and the maintainer will contact you.

Thank you for contributing. Your help improves portability, safety, and the quality of the library.
