// ─────────────────────────────────────────────────────────
//  DSA Thai · บทที่ 1 — Tree Data Structure
//  ไฟล์ 03: Binary Search Tree (BST)
//  อ้างอิง: https://www.geeksforgeeks.org/dsa/binary-search-tree-data-structure/
// ─────────────────────────────────────────────────────────
//
//  Compile:  g++ -std=c++17 -Wall 03_bst.cpp -o bst
//  Run:      ./bst
// ─────────────────────────────────────────────────────────

#include <bits/stdc++.h>
using namespace std;

// ─── Node ─────────────────────────────────────────────────
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

// ─── INSERT ───────────────────────────────────────────────
// O(log n) average, O(n) worst (Skewed)
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->data)
        node->left  = insert(node->left,  key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    // key == node->data: duplicate → ไม่ทำอะไร

    return node;
}

// ─── SEARCH ───────────────────────────────────────────────
// O(log n) average
Node* search(Node* node, int key) {
    // Base case: ไม่เจอ หรือ เจอแล้ว
    if (!node || node->data == key) return node;

    return key < node->data
        ? search(node->left,  key)
        : search(node->right, key);
}

// ─── Helper: หา node ที่มีค่าน้อยที่สุด (Inorder Successor) ──
Node* minNode(Node* node) {
    Node* curr = node;
    while (curr && curr->left)
        curr = curr->left;
    return curr;
}

// ─── DELETE ───────────────────────────────────────────────
// 3 กรณี: ไม่มีลูก / มีลูกข้างเดียว / มีลูก 2 ข้าง
Node* deleteNode(Node* node, int key) {
    if (!node) return nullptr;

    if (key < node->data) {
        node->left  = deleteNode(node->left,  key);
    } else if (key > node->data) {
        node->right = deleteNode(node->right, key);
    } else {
        // พบ node ที่ต้องลบ

        // Case 1: ไม่มี left child
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }

        // Case 2: ไม่มี right child
        if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: มีลูก 2 ข้าง
        // หา inorder successor (smallest ใน right subtree)
        Node* successor   = minNode(node->right);
        node->data        = successor->data;       // copy ค่า
        node->right       = deleteNode(node->right, successor->data);  // ลบ successor
    }
    return node;
}

// ─── Inorder (เพื่อแสดงค่า Sorted) ──────────────────────
void inorder(Node* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

// ─── Print Tree แบบ sideways ─────────────────────────────
void printTree(Node* node, string prefix = "", bool isLeft = true) {
    if (!node) return;
    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");
    cout << node->data << "\n";
    printTree(node->left,  prefix + (isLeft ? "│   " : "    "), true);
    printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
}

// ─── Height ──────────────────────────────────────────────
int height(Node* node) {
    if (!node) return 0;
    return 1 + max(height(node->left), height(node->right));
}

// ─── Cleanup ──────────────────────────────────────────────
void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    cout << "=== Binary Search Tree (BST) Demo ===\n\n";

    // ── INSERT ──
    Node* root = nullptr;
    vector<int> values = {8, 3, 10, 1, 6, 9, 14, 4, 7};

    cout << "Insert: ";
    for (int v : values) {
        cout << v << " ";
        root = insert(root, v);
    }
    cout << "\n\n";

    cout << "BST ที่ได้:\n";
    printTree(root->left,  "", true);
    cout << "└── " << root->data << " (root)\n";
    printTree(root->right, "", false);
    cout << "\n";

    cout << "Inorder (Sorted): ";
    inorder(root);
    cout << "\n\n";

    // ── SEARCH ──
    cout << "--- Search ---\n";
    int targets[] = {6, 13};
    for (int t : targets) {
        Node* found = search(root, t);
        cout << "Search(" << t << "): "
             << (found ? "✓ พบ" : "✗ ไม่พบ") << "\n";
    }
    cout << "\n";

    // ── DELETE ──
    cout << "--- Delete ---\n";

    // ลบ Leaf node (7)
    cout << "Delete(7)  — Leaf node:\n";
    root = deleteNode(root, 7);
    cout << "Inorder: "; inorder(root); cout << "\n\n";

    // ลบ node ที่มีลูกข้างเดียว (6 มีแค่ left = 4)
    cout << "Delete(6)  — มีลูก 1 ข้าง:\n";
    root = deleteNode(root, 6);
    cout << "Inorder: "; inorder(root); cout << "\n\n";

    // ลบ node ที่มีลูก 2 ข้าง (3 มี left=1 และ right=4)
    cout << "Delete(3)  — มีลูก 2 ข้าง:\n";
    root = deleteNode(root, 3);
    cout << "Inorder: "; inorder(root); cout << "\n\n";

    cout << "Height สุดท้าย: " << height(root) - 1 << "\n";

    deleteTree(root);
    return 0;
}
