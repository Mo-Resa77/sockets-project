# 🔤 String Manipulation Client-Server socketsApplication

## 📌 Overview

This project implements a **TCP-based client-server application in C**.  
The server listens for connections on **port 7777** and processes requests from the client to either:

- Check if a string is a **palindrome**
- **Reverse** a string

The client sends a **choice** (`1` for palindrome check, `2` for string reversal) and a **string**, then displays the server's response.

---

## 🌟 Features

### 🖥️ Server:
- Accepts **one client connection**
- Handles two types of requests:
  - **Palindrome Check**: Determines if the input string reads the same forward and backward.
  - **String Reversal**: Returns the reversed string.
- Uses **TCP** over port `7777`.

### 👤 Client:
- Connects to the server at `127.0.0.1:7777`.
- Prompts user for:
  - A choice (`1` or `2`)
  - A string (up to **100 characters**)
- Sends request and displays response:
  - Palindrome: `"Yes"` or `"No"`
  - Reversal: Reversed string

---

## 📁 Files

- `server.c`: The **server program** that listens and processes requests.
- `client.c`: The **client program** that sends requests and displays results.

---

## 🧰 Prerequisites

- A **C compiler** (e.g., `gcc`)
- A **Unix-like environment**:
  - Linux
  - macOS
  - Windows with **WSL**
- Standard C libraries:
  - `<sys/socket.h>`, `<arpa/inet.h>`, etc.
- Server and client run on the **same machine** (`127.0.0.1`)

---

## 🛠️ Troubleshooting

### ❗ "Bind error: Address already in use"
- Make sure port `7777` is free:
  ```bash
  netstat -tuln | grep 7777
