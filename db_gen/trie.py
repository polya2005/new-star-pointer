from struct import Struct

class Trie:
    class Node:
        binary_format = Struct("61h h")  # 61 children indices (shorts) and one value (short)

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
            if b == 0xce or b == 0xcf:  # Greek letter prefix
                continue
            if 0xb1 <= b <= 0xbf:  # Greek letters range
                real_key.append(b - 0x8d)  # Adjust to ASCII range
            elif 0x80 <= b <= 0x89:  # Also Greek letters
                real_key.append(b - 0x4d)
            elif 0x61 <= b <= 0x7a:  # Lowercase letters
                real_key.append(b - 0x57)
            elif 0x41 <= b <= 0x5a:  # Uppercase letters
                real_key.append(b - 0x37)
            elif 0x30 <= b <= 0x39:  # Digits
                real_key.append(b - 0x30)
            elif b == 0x20:  # Space character
                real_key.append(0x3c)
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
