::: center
**Time-Travelling File System**\
COL106: Data Structures and Algorithms -- Assignment 1\
:::

# Overview {#overview .unnumbered}

This project implements a **simplified, in-memory version control
system**, inspired by Git, using core data structures such as **Trees**,
**HashMaps**, and **Heaps**. The system manages versioned files with
support for branching and historical inspection.

# Features {#features .unnumbered}

## Core Features {#core-features .unnumbered}

-   **CREATE**: Create a new file with an initial snapshot.

-   **READ**: Display the current content of a file.

-   **INSERT**: Append content to a file version.

-   **UPDATE**: Replace the content of a file version.

-   **SNAPSHOT**: Create an immutable snapshot version with a message
    and timestamp.

-   **ROLLBACK**: Revert to a selected version.

-   **HISTORY**: List past snapshots along the version tree.

-   **EXIT**: Terminates the program.

## System-wide Operations {#system-wide-operations .unnumbered}

-   **RECENT FILES**: Print files sorted by last modification time.

-   **BIGGEST TREES**: Print files with the highest version count.

# How to Run {#how-to-run .unnumbered}

## Requirements {#requirements .unnumbered}

A C++ compiler such as `g++`.

## Compilation and Execution {#compilation-and-execution .unnumbered}

Use the provided `run.sh` script:

    chmod +x run.sh
    ./run.sh

# Command Syntax {#command-syntax .unnumbered}

## Core Operations {#core-operations .unnumbered}

``` {.bash language="bash"}
CREATE <filename>
READ <filename>
INSERT <filename> <content>
UPDATE <filename> <content>
SNAPSHOT <filename> <message>
ROLLBACK <filename> [versionID]
HISTORY <filename>
```

## System Analytics {#system-analytics .unnumbered}

``` {.bash language="bash"}
RECENT_FILES [num]
BIGGEST_TREES [num]
```

# CONSTRAINTS {#constraints .unnumbered}

the following are the constraints that i have to implement to the
problem statement effectively.

-   File name should have only one word.

-   snapshot message must be given while snapshotting(got inspiration
    from git).

-   content or message will not have trailing spaces in start(to make
    sure if someone accidentally gives two spaces. this limits freedom
    but if we had this freedom, then we cant control accidental
    spacings. But we can change this according to our needs).

-   integer cannot have trailing spaces.(checked that seperately to
    inform them whats wrong)

-   num in system analytics function can't be more than the number of
    files which exist.(no reason, just my preference. we can change this
    if we want).

-   Update and Insert must have content(no reason if no content).

-   Added last_modified attribute to files to make it easier for sorting
    it for recent_files. one could not find another elegant method

# ERROR HANDLING {#error-handling .unnumbered}

## CREATE {#create .unnumbered}

-   Made sure the file name contains only one word. as it may create
    confusion while updating.

-   made sure the file name is unique. Displayed a message when it is
    already present.

## READ {#read .unnumbered}

-   Made sure that given file name exist. Displayed a message if it is
    not present

## INSERT {#insert .unnumbered}

-   Made sure the given file name exist. Displayed a message if it is
    not present

-   Made sure they gave a content to add to the file. Displayed a
    message if it is not present

-   Created new version if the active version is snapshotted.

## UPDATE {#update .unnumbered}

-   Made sure the given file name exist. Displayed a message if it is
    not present

-   Made sure they gave a content to add to the file. Displayed a
    message if it is not present

-   Created new version if the active version is snapshotted.

## SNAPSHOT {#snapshot .unnumbered}

-   Made sure the given file name exist. Displayed a message if it is
    not present

-   Made sure they gave a snapshot message. Displayed a message if it is
    not present

-   checked whether the active version is already snapshotted. Displayed
    a message when already snapshotted.

## ROLLBACK {#rollback .unnumbered}

-   Made sure the file name exist.

-   if no version id is given, rollbacked to parent version. Displayed a
    message when it is already at root.

-   Made sure the integer given does not have a trailing space.
    Displayed a message if it had.

-   Made sure they gave a number and the given number is a version.
    Displayed a message if it is not.

## UPDATE {#update-1 .unnumbered}

-   Made sure the given file name exist. Displayed a message if it is
    not present.

## RECENT_FILES {#recent_files .unnumbered}

-   Made sure the given file name exist. Displayed a message if it is
    not present

-   Made sure the given integer is valid. Displayed a message if it is
    not.

-   Made sure they given number of files exist. if the given number is
    more than the number of files exist, displayed an error.

## BIGGEST_TREES {#biggest_trees .unnumbered}

-   Made sure the given file name exist. Displayed a message if it is
    not present

-   Made sure the given integer is valid. Displayed a message if it is
    not.

-   Made sure they given number of files exist. if the given number is
    more than the number of files exist, displayed an error.