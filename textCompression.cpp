// Huffman Text Compression Implementation

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Node {
    char data;
    unsigned freq;
    Node *left, *right;

    Node(char d, unsigned f) {
        data = d;
        freq = f;
        left = right = nullptr;
    }

    // prevent memory leaks when deleting root
    ~Node() {
        delete left;
        delete right;
    }
};

struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

class Huffman {
private:
    unordered_map<char, string> codeMap;
    unordered_map<string, char> decodeMap;
    Node* root;

    // dfs to get the binary codes
    void getCodes(Node* curr, string str) {
        if (!curr) return;

        // hit a leaf node
        if (!curr->left && !curr->right) {
            codeMap[curr->data] = str;
            decodeMap[str] = curr->data;
        }

        getCodes(curr->left, str + "0");
        getCodes(curr->right, str + "1");
    }

public:
    Huffman() { root = nullptr; }

    ~Huffman() {
        delete root; 
    }

    void build(const string& text) {
        if (text.empty()) return;

        unordered_map<char, unsigned> freqMap;
        for (char c : text) {
            freqMap[c]++;
        }

        priority_queue<Node*, vector<Node*>, compare> pq;
        for (auto it : freqMap) {
            pq.push(new Node(it.first, it.second));
        }

        // edge case: only one type of character in file
        if (pq.size() == 1) {
            Node* leftNode = pq.top();
            pq.pop();
            root = new Node('\0', leftNode->freq);
            root->left = leftNode;
            getCodes(root, "0");
            return;
        }

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();

            // create dummy parent node
            Node* parent = new Node('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            pq.push(parent);
        }

        root = pq.top();
        getCodes(root, "");
    }

    string encode(const string& text) {
        string ans = "";
        for (char c : text) {
            ans += codeMap[c];
        }
        return ans;
    }

    string decode(const string& bits) {
        string res = "";
        string temp = "";

        for (char b : bits) {
            temp += b;
            if (decodeMap.count(temp)) {
                res += decodeMap[temp];
                temp = "";
            }
        }
        return res;
    }

    void debugPrint() {
        cout << "\n[Code Table]\n";
        for (auto it : codeMap) {
            if (it.first == '\n') cout << "\\n";
            else if (it.first == ' ') cout << "spc";
            else cout << it.first;
            
            cout << " -> " << it.second << "\n";
        }
    }
};

int main() {
    string text = "malav;iya na-tio;nal \% instit!ute # of #tech!no!logy";
    
    cout << "Original (" << text.length() << " chars): " << text << "\n";

    Huffman h;
    h.build(text);
    h.debugPrint();

    string encoded = h.encode(text);
    cout << "\nEncoded bits: \n" << encoded << "\n";
    
    int oldSize = text.length() * 8; 
    int newSize = encoded.length();
    
    cout << "\nStats....\n";
    cout << "Old size: " << oldSize << " bits\n";
    cout << "New size: " << newSize << " bits\n";
    cout << "Compression: " << (100.0 - ((double)newSize / oldSize * 100)) << "%\n";

    string decoded = h.decode(encoded);
    cout << "\nDecoded: " << decoded << "\n";

    return 0;
}