// ─────────────────────────────────────────────────────────
//  DSA Thai · บทที่ 1 — Tree Data Structure
//  ไฟล์ 01: Node Structure พื้นฐาน และ Generic Tree
//  อ้างอิง: https://www.geeksforgeeks.org/dsa/introduction-to-tree-data-structure/
// ─────────────────────────────────────────────────────────
//
//  Compile:  g++ -std=c++17 -Wall 01_node_basic.cpp -o node_basic
//  Run:      ./node_basic          (macOS/Linux)
//            node_basic.exe        (Windows)
// ─────────────────────────────────────────────────────────

#include <iostream>
#include <vector>
using namespace std;

// ─── Generic Tree Node (N-ary) ───────────────────────────
// แต่ละ Node เก็บ data และ list ของ children
struct Node {
    int data;
    vector<Node*> children;

    Node(int x) : data(x) {}
};

// เพิ่ม child ให้ parent
void addChild(Node* parent, Node* child) {
    parent->children.push_back(child);
}

// ─── Print Tree แบบ indented ─────────────────────────────
void printTree(Node* node, int level = 0) {
    if (!node) return;

    // Indent ตาม level
    for (int i = 0; i < level; i++) cout << "  ";
    cout << "└─ " << node->data << "\n";

    for (Node* child : node->children)
        printTree(child, level + 1);
}

// ─── นับจำนวน Node ทั้งหมด ───────────────────────────────
int countNodes(Node* node) {
    if (!node) return 0;

    int count = 1;  // นับตัวเอง
    for (Node* child : node->children)
        count += countNodes(child);
    return count;
}

// ─── หา Height ของ Tree ──────────────────────────────────
int height(Node* node) {
    if (!node || node->children.empty()) return 0;

    int maxH = 0;
    for (Node* child : node->children)
        maxH = max(maxH, height(child));
    return maxH + 1;
}

// ─── หา Leaf Nodes ───────────────────────────────────────
void printLeaves(Node* node) {
    if (!node) return;

    if (node->children.empty()) {
        cout << node->data << " ";
        return;
    }
    for (Node* child : node->children)
        printLeaves(child);
}

int main() {
    cout << "=== Generic Tree Demo ===\n\n";

    // สร้าง Tree:
    //       1
    //      / | 
    //     2  3  4
    //    /   
    //   5   6
    //       |
    //       7

    Node* root = new Node(1);
    Node* n2   = new Node(2);
    Node* n3   = new Node(3);
    Node* n4   = new Node(4);
    Node* n5   = new Node(5);
    Node* n6   = new Node(6);
    Node* n7   = new Node(7);

    addChild(root, n2);
    addChild(root, n3);
    addChild(root, n4);
    addChild(n2, n5);
    addChild(n2, n6);
    addChild(n6, n7);

    cout << "โครงสร้าง Tree:\n";
    printTree(root);

    cout << "\nจำนวน Nodes ทั้งหมด : " << countNodes(root) << "\n";
    cout << "Height ของ Tree      : " << height(root) << "\n";
    cout << "Leaf Nodes           : ";
    printLeaves(root);
    cout << "\n";

    cout << "\n--- Terminology ---\n";
    cout << "Root       : " << root->data << "\n";
    cout << "Children ของ " << root->data << " : ";
    for (Node* c : root->children) cout << c->data << " ";
    cout << "\n";
    cout << "Parent ของ " << n5->data << " : " << n2->data << "\n";
    cout << "Depth ของ " << n7->data << " (นับจาก root) : 3\n";

    // ── Memory cleanup ──
    delete n7; delete n6; delete n5;
    delete n4; delete n3; delete n2;
    delete root;

    return 0;
}
