from struct import Struct

"""
A Trie (prefix tree) implementation for storing byte sequences with integer values.
Supports insertion of byte sequences and handles specific character mappings.

Encoding is done by mapping input byte values to a smaller range suitable for the trie structure.
Encoding    Character
0-9         0-9
a-z         10-35
α-ω         36-59
(space)     60
"""


class Trie:
    class Node:
        binary_format = Struct(
            "61h h"
        )  # 61 children indices (shorts) and one value (short)

        def __init__(self) -> None:
            self.children = [-1 for _ in range(61)]  # stores children's indices
            self.value: int = -1

        def __repr__(self) -> str:
            return f"Node(children={self.children}, value={self.value})"

        def pack(self) -> bytes:
            return self.binary_format.pack(*self.children, self.value)

    def __init__(self) -> None:
        self.nodes: list["Trie.Node"] = [Trie.Node()]

    def __setitem__(self, key: bytes, value: int) -> None:
        real_key = []
        for b in key:
            # Handle Greek letters
            if b == 0xCE or b == 0xCF:  # Greek letter prefix
                continue
            if 0xB1 <= b <= 0xBF:  # Greek letters range
                real_key.append(b - 0x8D)  # Adjust to ASCII range
            elif 0x80 <= b <= 0x89:  # Also Greek letters
                real_key.append(b - 0x4D)
            elif 0x61 <= b <= 0x7A:  # Lowercase letters
                real_key.append(b - 0x57)
            elif 0x41 <= b <= 0x5A:  # Uppercase letters
                real_key.append(b - 0x37)
            elif 0x30 <= b <= 0x39:  # Digits
                real_key.append(b - 0x30)
            elif b == 0x20:  # Space character
                real_key.append(0x3C)
            else:
                raise ValueError(f"Unsupported character in key: {b}")

        def setitem_helper(node_index: int, key: list[int], value: int) -> None:
            if not key:
                self.nodes[node_index].value = value
                return

            char, *rest = key
            if self.nodes[node_index].children[char] == -1:  # child does not exist
                new_node_index = len(self.nodes)
                self.nodes.append(Trie.Node())
                self.nodes[node_index].children[char] = new_node_index

            child_index = self.nodes[node_index].children[char]
            setitem_helper(child_index, rest, value)

        setitem_helper(0, real_key, value)


if __name__ == "__main__":
    trie = Trie()
    trie[b"hello"] = 1
    trie[b"world"] = 2
    trie[b"hi"] = 3

    print(trie.nodes)  # Print the internal structure of the trie
