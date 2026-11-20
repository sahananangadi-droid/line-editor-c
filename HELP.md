# Line Editor Help

A command-line line editor written in C. Type a command at the `>` prompt and press Enter. Line numbers start at 1.

## Commands

### i - Insert a line

Adds a new line at the given position. Lines below it shift down.

**Syntax:** `i <line number> <text>`
**Example:**

```
> i 1 Hello world
> i 2 Second line
```

You can insert at any position from 1 up to (number of lines + 1). Inserting at the end adds a new last line.

### d - Delete a line

Removes the given line. Lines below it shift up.

**Syntax:** `d <line number>`
**Example:**

```
> d 2
```

### p - Display the document

Prints every line with its line number.

**Syntax:** `p`
**Example:**

```
> p
  1: Hello world
  2: Second line
```

### s - Save to a file

Writes the document to a text file.

**Syntax:** `s <filename>`
**Example:**

```
> s notes.txt
Saved 2 lines.
```

### l - Load from a file

Replaces the current document with the contents of a file.

**Syntax:** `l <filename>`
**Example:**

```
> l notes.txt
Loaded 2 lines.
```

### f - Find text (bonus)

Prints every line that contains the given text.

**Syntax:** `f <text>`
**Example:**

```
> f world
  1: Hello world
```

### c - Count (bonus)

Shows the number of lines and words in the document.

**Syntax:** `c`
**Example:**

```
> c
Lines: 2, Words: 4
```

### q - Quit

Exits the editor. Unsaved changes are lost, so save first with `s`.

**Syntax:** `q`

## Error messages

| Message                                        | Meaning                                                        |
| ---------------------------------------------- | -------------------------------------------------------------- |
| `Usage: ...`                                   | The command was missing or had wrong arguments                 |
| `Error: invalid line number or document full.` | Insert position is out of range, or 100 lines are already used |
| `Error: no such line.`                         | Delete was given a line that does not exist                    |
| `Error: could not open file.`                  | The file to load does not exist                                |
| `Error: could not save file.`                  | The file could not be written                                  |
| `Unknown command.`                             | The first letter is not a valid command                        |

## Limits

- Up to 100 lines, each up to 255 characters.
