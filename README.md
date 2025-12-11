# Gateway Protocol (C++17 Networking)

A custom lightweight network protocol simulation demonstrating message framing, serialization, and routing between nodes.

## 🎯 Purpose
Simulate message exchange between gateway nodes using a custom protocol structure.

## 🚀 Features
- Custom packet structure (header + payload)
- Serialization / deserialization using C++17
- Basic routing table logic
- Error-checking & validation
- Logging module for debugging

## 🛠️ Technical Highlights
- **Binary serialization** using `std::byte`
- **Memory-safe parsing** (no raw buffer overflows)
- **Enums, structs, RAII file/network wrappers**
- Designed for extensibility (opcodes, message types)

## 📦 Build Instructions

mkdir build && cd build
cmake ..
make
./gateway_protocol


## 🧪 What This Demonstrates
- Understanding of **network protocols**
- Ability to design **serialization formats**
- Low-level bitwise & byte-level reasoning
- Architecture thinking for distributed systems

## 📈 Future Improvements
- Add multi-threaded message handling
- Extend routing logic
- Replace simulated I/O with real sockets

