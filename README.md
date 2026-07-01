# C++ Text Compression Engine

 Uses the Huffman Coding algorithm to compress text data by up to 45% without losing any information.

# Tech Stack
--Language: C++
--Core Data Structures: Min-Heap (Priority Queue), Binary Trees, Hash Maps
--Key Concepts: Greedy Algorithms, Bitwise Operations, Raw Memory Management

# Features
--Custom Tree Building: Uses a priority queue with a custom comparator to build an optimal binary prefix tree based on exact character frequencies.
--Variable-Length Encoding: Standard characters take a full 8-bit byte. This engine generates shorter bit codes for frequent characters to reduce size.
--Strict Memory Management: Wrote custom destructors to handle raw memory pointers, ensuring zero memory leaks.
