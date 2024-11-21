# Blockchain for File Metadata and Tamper Detection

## Project Overview
This project implements a simple blockchain in C for securing file metadata and intellectual property. It uses the OpenSSL library for hashing and supports features like tamper detection and file metadata extraction.

The blockchain includes:
- A **Genesis Block** as the starting block.
- The ability to add blocks containing file metadata (e.g., file size, creation date, modification date).
- Tamper detection through hash comparison.
- A menu-driven CLI for user interaction.

---

## Features
1. **Blockchain Structure:**
   - Each block contains:
     - Index
     - Timestamp
     - Data (e.g., file metadata)
     - Previous hash
     - Current hash

2. **File Metadata Storage:**
   - Extracts and stores file size, creation date, and modification date in the blockchain.

3. **Tamper Detection:**
   - Validates the blockchain by:
     - Comparing the recalculated hash of each block with the stored hash.
     - Ensuring the `prev_hash` of each block matches the `hash` of its predecessor.

4. **Menu-Driven CLI:**
   - Add blocks with file metadata.
   - Display the blockchain.
   - Modify a block (to simulate tampering).
   - Validate the blockchain for tampering.

---

## Requirements
### Dependencies
- **C Compiler:** GCC or any other C compiler.
- **OpenSSL Library:** For SHA-256 hashing.
- **Standard C Libraries:** `stdio.h`, `stdlib.h`, `string.h`, `time.h`.

### Installation
Install OpenSSL if it's not already installed:
```bash
sudo apt update
sudo apt install libssl-dev
```

---

## Usage Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/FrankOnyemaOrji/alu-llp-assignment4.git
cd alu-llp-assignment4.git
```

### 2. Compile the Code
```bash
gcc -o blockchain main.c blockchain.c -lssl -lcrypto
```

### 3. Run the Application
```bash
./blockchain
```

### 4. Menu Options
The program provides the following options:

#### Option 1: Add Block with File Metadata
- Prompts you to enter the file name.
- Extracts the file's metadata and adds it to a new block in the blockchain.

#### Option 2: Validate Blockchain
- Validates the blockchain for tampering.
- Detects:
  - Data tampering (modifications to block data).
  - Chain breakage (mismatch in `prev_hash` and `hash`).

#### Option 3: Modify Block
- Simulates tampering by modifying the data of a specific block.
- Prompts you to enter the block index and new data.

#### Option 4: Display Blockchain
- Displays all blocks in the blockchain with their:
  - Index
  - Timestamp
  - Data
  - Hash
  - Previous hash

#### Option 5: Exit
- Exits the program.

---

## Demonstration

### Step 1: Add a Block
1. Create a sample file, e.g., `sample.txt`:
   ```bash
   echo "This is a sample file for blockchain testing." > sample.txt
   ```
2. Add the file to the blockchain:
   ```
   Blockchain Menu:
   1. Add Block with File Metadata
   2. Validate Blockchain
   3. Modify Block
   4. Display Blockchain
   5. Exit
   Enter your choice: 1
   Enter file name: sample.txt
   Block added successfully.
   ```

### Step 2: Display Blockchain
```
Blockchain Menu:
1. Add Block with File Metadata
2. Validate Blockchain
3. Modify Block
4. Display Blockchain
5. Exit
Enter your choice: 4
Block 0:
  Timestamp: 2024-11-21 09:31:42
  Data: Genesis Block
  Hash: 74b063fcb098afc3ef9982193e94dbe00674edec1a0811ef9b0eabff3edfe5c6
  Prev Hash: 0
----------------------------
Block 1:
  Timestamp: 2024-11-21 09:32:10
  Data: File: sample.txt, Size: 56 bytes, Created: 2024-11-21 09:31:58, Modified: 2024-11-21 09:31:58
  Hash: 4c22616d0d82ae410105d60d3837abefdc11c2cc1ddf3937f2380c8b8731a054
  Prev Hash: 74b063fcb098afc3ef9982193e94dbe00674edec1a0811ef9b0eabff3edfe5c6
----------------------------
```

### Step 3: Modify a Block
Simulate tampering:
```
Blockchain Menu:
1. Add Block with File Metadata
2. Validate Blockchain
3. Modify Block
4. Display Blockchain
5. Exit
Enter your choice: 3
Enter block index to modify: 1
Enter new data: Tampered data
Block modified successfully.
```

### Step 4: Validate Blockchain
```
Blockchain Menu:
1. Add Block with File Metadata
2. Validate Blockchain
3. Modify Block
4. Display Blockchain
5. Exit
Enter your choice: 2
Tampering detected in block 1. Stored hash does not match recalculated hash.
```

---

## Code Overview

### File Structure
- `blockchain.h`: Header file with structure definitions and function prototypes.
- `blockchain.c`: Contains all blockchain logic (e.g., block creation, hash calculation, validation).
- `main.c`: The main program with a menu-driven interface.

### Blockchain Data Structure
Each block contains:
- `index`: Position in the blockchain.
- `timestamp`: When the block was created.
- `data`: File metadata or custom data.
- `prev_hash`: Hash of the previous block.
- `hash`: Current block's hash.

---

## How It Works
1. **Adding a Block:**
   - Metadata is extracted from the file using `stat()`.
   - A new block is created with this data and linked to the previous block.
   - The block's hash is calculated using SHA-256.

2. **Validating the Blockchain:**
   - For each block:
     - Recalculate the hash and compare it with the stored hash.
     - Ensure the `prev_hash` of the next block matches the current block's hash.

3. **Tamper Detection:**
   - Any mismatch in hashes or chain links is flagged as tampering.

---

## Example Output
After running the program, a tampered blockchain might look like this:

```
Tampering detected in block 1. Stored hash does not match recalculated hash.
```

---

## Contributions
Feel free to contribute to the project by:
- Reporting issues.
- Suggesting improvements.
- Creating pull requests.

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.
