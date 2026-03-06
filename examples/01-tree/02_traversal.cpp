// ─────────────────────────────────────────────────────────
//  DSA Thai · บทที่ 1 — Tree Data Structure
//  ไฟล์ 02: Tree Traversal ทุกรูปแบบ
//  อ้างอิง: https://www.geeksforgeeks.org/dsa/tree-traversals-inorder-preorder-and-postorder/
// ─────────────────────────────────────────────────────────
//
//  Compile:  g++ -std=c++17 -Wall 02_traversal.cpp -o traversal
//  Run:      ./traversal
// ─────────────────────────────────────────────────────────

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ─── Binary Tree Node ────────────────────────────────────
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

// ─── 1. Inorder: Left → Root → Right ────────────────────
// ผลลัพธ์ใน BST จะ Sorted เสมอ
void inorder(Node* node) {
    if (node == nullptr) return;

    inorder(node->left);            // ไป Left ก่อน
    cout << node->data << " ";      // เข้า Root
    inorder(node->right);           // ไป Right
}

// ─── 2. Preorder: Root → Left → Right ───────────────────
// ใช้ copy tree หรือ serialize โครงสร้าง
void preorder(Node* node) {
    if (node == nullptr) return;

    cout << node->data << " ";      // เข้า Root ก่อน
    preorder(node->left);           // ไป Left
    preorder(node->right);          // ไป Right
}

// ─── 3. Postorder: Left → Right → Root ──────────────────
// ใช้ลบ tree หรือคำนวณ expression
void postorder(Node* node) {
    if (node == nullptr) return;

    postorder(node->left);          // ไป Left
    postorder(node->right);         // ไป Right
    cout << node->data << " ";      // เข้า Root สุดท้าย
}

// ─── 4. BFS / Level-Order ────────────────────────────────
// ใช้ Queue เดิน Level ต่อ Level
void levelOrder(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        cout << curr->data << " ";

        if (curr->left)  q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// ─── BFS แบบแสดงทีละ Level ──────────────────────────────
void levelOrderByLevel(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int size = q.size();    // จำนวน node ใน level นี้
        cout << "Level " << level << ": ";

        for (int i = 0; i < size; i++) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";

            if (curr->left)  q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << "\n";
        level++;
    }
}

// ─── Height ──────────────────────────────────────────────
int height(Node* node) {
    if (!node) return 0;
    return 1 + max(height(node->left), height(node->right));
}

int main() {
    // สร้าง BST ตัวอย่าง:
    //         4
    //        /  
    //       2   6
    //      /  /  
    //     1  3 5  7

    Node* root         = new Node(4);
    root->left         = new Node(2);
    root->right        = new Node(6);
    root->left->left   = new Node(1);
    root->left->right  = new Node(3);
    root->right->left  = new Node(5);
    root->right->right = new Node(7);

    cout << "=== Tree Traversal Demo ===\n";
    cout << "Tree (BST):\n";
    cout << "       4\n";
    cout << "      / \\\n";
    cout << "     2   6\n";
    cout << "    / \\ / \\\n";
    cout << "   1  3 5  7\n\n";

    cout << "1. Inorder   (L→Root→R) : ";
    inorder(root);
    cout << "\n   ↑ Sorted เสมอสำหรับ BST!\n\n";

    cout << "2. Preorder  (Root→L→R) : ";
    preorder(root);
    cout << "\n\n";

    cout << "3. Postorder (L→R→Root) : ";
    postorder(root);
    cout << "\n\n";

    cout << "4. BFS Level-Order      : ";
    levelOrder(root);
    cout << "\n\n";

    cout << "5. BFS แบบแสดงทีละ Level:\n";
    levelOrderByLevel(root);

    cout << "\nHeight ของ Tree: " << height(root) - 1 << "\n";

    // Memory cleanup
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
