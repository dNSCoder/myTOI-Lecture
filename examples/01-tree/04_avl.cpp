// ─────────────────────────────────────────────────────────
//  DSA Thai · บทที่ 1 — Tree Data Structure
//  ไฟล์ 04: AVL Tree — Self-Balancing BST
//  อ้างอิง: https://www.geeksforgeeks.org/dsa/introduction-to-avl-tree/
// ─────────────────────────────────────────────────────────
//
//  Compile:  g++ -std=c++17 -Wall 04_avl.cpp -o avl
//  Run:      ./avl
// ─────────────────────────────────────────────────────────

#include <bits/stdc++.h>
using namespace std;

// ─── Node ─────────────────────────────────────────────────
struct Node {
    int data;
    int height;     // ความสูงของ subtree ที่ Node นี้เป็น root
    Node* left;
    Node* right;

    Node(int x) : data(x), height(1), left(nullptr), right(nullptr) {}
};

int rotationCount = 0;  // นับจำนวนครั้งที่ Rotate

// ─── Utility ──────────────────────────────────────────────
int h(Node* n)       { return n ? n->height : 0; }
int bf(Node* n)      { return n ? h(n->left) - h(n->right) : 0; }
void updateH(Node* n){ n->height = 1 + max(h(n->left), h(n->right)); }

// ─── Right Rotation (แก้ LL case) ────────────────────────
//     y                x
//    / |             /   |
//   x   T3  →    T1     y
//  / |                  / |
// T1  T2               T2  T3
Node* rotateRight(Node* y) {
    Node* x  = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left  = T2;

    updateH(y);
    updateH(x);

    rotationCount++;
    cout << "  → Right Rotation บน node " << y->data
         << " (root ใหม่: " << x->data << ")\n";
    return x;
}

// ─── Left Rotation (แก้ RR case) ─────────────────────────
//   x                   y
//    |                /   |
//     y      →     x     T3
//    / |              |
//   T2  T3             T2
Node* rotateLeft(Node* x) {
    Node* y  = x->right;
    Node* T2 = y->left;

    y->left  = x;
    x->right = T2;

    updateH(x);
    updateH(y);

    rotationCount++;
    cout << "  → Left Rotation บน node " << x->data
         << " (root ใหม่: " << y->data << ")\n";
    return y;
}

// ─── Balance ──────────────────────────────────────────────
Node* balance(Node* node) {
    updateH(node);
    int b = bf(node);

    // Left Heavy (BF > 1)
    if (b > 1) {
        if (bf(node->left) < 0) {           // LR case
            cout << "  LR Case: ";
            node->left = rotateLeft(node->left);
        }
        cout << "  LL Case: ";
        return rotateRight(node);
    }

    // Right Heavy (BF < -1)
    if (b < -1) {
        if (bf(node->right) > 0) {          // RL case
            cout << "  RL Case: ";
            node->right = rotateRight(node->right);
        }
        cout << "  RR Case: ";
        return rotateLeft(node);
    }

    return node;
}

// ─── INSERT ───────────────────────────────────────────────
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if      (key < node->data) node->left  = insert(node->left,  key);
    else if (key > node->data) node->right = insert(node->right, key);

    return balance(node);   // auto-balance หลัง insert
}

// ─── Helper: หา Min ───────────────────────────────────────
Node* minNode(Node* n) {
    while (n->left) n = n->left;
    return n;
}

// ─── DELETE ───────────────────────────────────────────────
Node* deleteNode(Node* node, int key) {
    if (!node) return nullptr;

    if      (key < node->data) node->left  = deleteNode(node->left,  key);
    else if (key > node->data) node->right = deleteNode(node->right, key);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        Node* s  = minNode(node->right);
        node->data  = s->data;
        node->right = deleteNode(node->right, s->data);
    }
    return balance(node);   // auto-balance หลัง delete
}

// ─── Print Tree ───────────────────────────────────────────
void printTree(Node* node, string prefix = "", bool isLast = true) {
    if (!node) return;
    cout << prefix << (isLast ? "└── " : "├── ");
    cout << node->data
         << " (h=" << node->height
         << ", bf=" << bf(node) << ")\n";
    if (node->left || node->right) {
        printTree(node->left,  prefix + (isLast ? "    " : "│   "), !node->right);
        printTree(node->right, prefix + (isLast ? "    " : "│   "), true);
    }
}

// ─── Inorder ──────────────────────────────────────────────
void inorder(Node* n) {
    if (!n) return;
    inorder(n->left);
    cout << n->data << " ";
    inorder(n->right);
}

// ─── Cleanup ──────────────────────────────────────────────
void deleteTree(Node* n) {
    if (!n) return;
    deleteTree(n->left);
    deleteTree(n->right);
    delete n;
}

int main() {
    cout << "=== AVL Tree Demo ===\n\n";
    Node* root = nullptr;

    // ── ทดสอบ RR Case: 10 → 20 → 30 ──────────────────────
    cout << "── ทดสอบ RR Case: insert 10, 20, 30 ──\n";
    cout << "Insert 10\n";  root = insert(root, 10);
    cout << "Insert 20\n";  root = insert(root, 20);
    cout << "Insert 30\n";  root = insert(root, 30);

    cout << "\nTree หลัง balance:\n";
    printTree(root);
    cout << "Inorder: "; inorder(root); cout << "\n";
    cout << "Root: " << root->data << " (ควรเป็น 20)\n\n";

    deleteTree(root);
    root = nullptr;
    rotationCount = 0;

    // ── ทดสอบ LR Case: 30 → 10 → 20 ──────────────────────
    cout << "── ทดสอบ LR Case: insert 30, 10, 20 ──\n";
    cout << "Insert 30\n";  root = insert(root, 30);
    cout << "Insert 10\n";  root = insert(root, 10);
    cout << "Insert 20\n";  root = insert(root, 20);

    cout << "\nTree หลัง balance:\n";
    printTree(root);
    cout << "Root: " << root->data << " (ควรเป็น 20)\n\n";

    deleteTree(root);
    root = nullptr;
    rotationCount = 0;

    // ── Insert หลายค่าพร้อมกัน ────────────────────────────
    cout << "── Insert: 50, 30, 70, 20, 40, 60, 80, 10 ──\n";
    int vals[] = {50, 30, 70, 20, 40, 60, 80, 10};
    for (int v : vals) {
        cout << "Insert " << v << "\n";
        root = insert(root, v);
    }

    cout << "\nAVL Tree สุดท้าย:\n";
    printTree(root);
    cout << "\nInorder (Sorted): ";
    inorder(root);
    cout << "\n\n";

    cout << "Height  : " << root->height - 1 << "\n";
    cout << "Root BF : " << bf(root) << " (ต้องอยู่ใน {-1, 0, 1})\n";
    cout << "Rotations ทั้งหมด: " << rotationCount << "\n\n";

    // ── Delete ────────────────────────────────────────────
    cout << "── Delete(70) ──\n";
    root = deleteNode(root, 70);
    cout << "Tree หลัง delete:\n";
    printTree(root);
    cout << "Inorder: "; inorder(root); cout << "\n";

    deleteTree(root);
    return 0;
}
