# line-editor-c

# Line Editor in C

Activity 7: Coding Competition, Portfolio Building (3rd Semester)

## Team

- Sahana N Angadi (solo, team size 1)

## Description

A command-line line editor written in C. The user types commands to create, view and modify a small text document one line at a time, with no GUI.

## Data structure

A 2D character array `char lines[100][256]` with a counter `count`. Line number n maps to `lines[n-1]`. Insert and delete shift lines by copying. This is simple and has little bug risk, at the cost of slower shifting and a fixed size of 100 lines.

## Features implemented

**Core**

- Insert a line
- Delete a line
- Display the document
- Save / load a file

**Bonus**

- Search (find text)
- Line count and word count

## How to compile

```
gcc -Wall -o editor editor.c
```

## How to run

```
./editor
```

On Windows PowerShell use `.\editor`.

## Usage

See [HELP.md](HELP.md) for every command with examples.

Quick example:

```
> i 1 Hello world
> p
  1: Hello world
> s notes.txt
> q
```

## Repository contents

- `editor.c`: source code
- `HELP.md`: command help
- `design/paper_design.pdf`: paper design
- `README.md`: this file
