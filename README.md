
# 📂 Time-Travelling File System – COL106 Data Structures and Algorithms Assignment

## 📖 Overview

This project implements a **simplified, in-memory version control system**, inspired by Git, using core data structures such as **Trees**, **HashMaps**, and **Heaps**. The system manages versioned files with support for branching and historical inspection.

The primary learning objective is to apply data structures from scratch (without using built-in C++ libraries like `map`, `vector`, or `priority_queue`) to build a practical, real-world application.

---

## 📂 Features

### ✅ Core Functionalities
- **CREATE**: Create a new file with an initial snapshot.
- **READ**: Display the current content of a file.
- **INSERT**: Append content to a file version.
- **UPDATE**: Replace the content of a file version.
- **SNAPSHOT**: Create an immutable snapshot version with a message and timestamp.
- **ROLLBACK**: Revert to a previous version.
- **HISTORY**: List past snapshots along the version tree.

### ✅ System-wide Operations
- **RECENT FILES**: List files sorted by last modification time.
- **BIGGEST TREES**: List files with the highest version count.

---

## 🏗 System Architecture

### 📦 File Structure
- Version history stored in a **Tree** structure.
- Fast lookup of versions using a custom **HashMap**.
- Metrics such as recent files and largest trees tracked using a **Heap**.

### 📂 Version Node
Each version stores:
- `version_id`
- `content`
- `message`
- `created_timestamp`
- `snapshot_timestamp`
- `parent` and `children` pointers.

---

## ⚙ How to Run

### ✅ Requirements
- C++ compiler (e.g., `g++`)

### ✅ Compilation and Execution

Use the provided `run.sh` script to compile and run the program:

```bash
chmod +x run.sh
./run.sh