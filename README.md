# 🌿 DSA Thai — Data Structures & Algorithms สำหรับ Computer Olympiad

บทเรียน DSA ภาษาไทย เน้น **Competitive Programming style** พร้อม Diagram, Code C++ และ Interactive Demo  
อิง Curriculum จาก [GeeksforGeeks](https://www.geeksforgeeks.org/dsa/), [Programiz](https://www.programiz.com/dsa), [cp-algorithms](https://cp-algorithms.com/) และ [USACO Guide](https://usaco.guide/)

🌐 **[เปิดดูบทเรียนออนไลน์ →](https://[your-username].github.io/[your-repo-name]/)**

---

## 📚 บทเรียนที่มี

| บท | หัวข้อ | Part | สถานะ |
|---|---|---|---|
| 🌳 | Tree Data Structure | [Part 1 — ทฤษฎี](docs/tree-dsa-lesson.html) | ✅ พร้อมเรียน |
| 🌳 | Tree Data Structure | [Part 2 — CP Implementation](docs/tree-cp-lesson.html) | ✅ พร้อมเรียน |
| 🕸 | Graph & Shortest Path | — | 🔒 เร็วๆ นี้ |
| 📈 | Complexity Analysis | — | 🔒 เร็วๆ นี้ |

---

## 🗂 โครงสร้างไฟล์

```
dsa-thai/
├── README.md
├── setup/
│   └── vscode-cpp.md           ← วิธีติดตั้ง C++ + VSCode (อ่านก่อน!)
├── examples/
│   └── 01-tree/                ← โค้ด C++ ตัวอย่างบทที่ 1
│       ├── 01_node_basic.cpp
│       ├── 02_traversal.cpp
│       ├── 03_bst.cpp
│       └── 04_avl.cpp
└── docs/                       ← GitHub Pages serve จากโฟลเดอร์นี้
    ├── index.html
    ├── tree-dsa-lesson.html    ← Part 1: ทฤษฎี
    └── tree-cp-lesson.html     ← Part 2: CP Implementation
```

---

## 🚀 เริ่มต้นใช้งาน

### 1. ดูบทเรียน (ไม่ต้องติดตั้งอะไร)

เปิด `docs/index.html` ในเบราว์เซอร์ได้เลย หรือเข้าผ่าน GitHub Pages link ด้านบน

### 2. ตั้งค่า GitHub Pages

1. Push repo ขึ้น GitHub
2. ไปที่ **Settings → Pages**
3. Source: **Deploy from a branch**
4. Branch: **main** / Folder: **docs** → Save

### 3. รันโค้ด C++ ตัวอย่าง

> **ยังไม่มี Compiler?** → อ่าน [setup/vscode-cpp.md](setup/vscode-cpp.md) ก่อนครับ

```bash
# Clone repo
git clone https://github.com/[your-username]/[your-repo-name].git
cd dsa-thai

# Compile และรันตัวอย่าง
g++ -std=c++17 examples/01-tree/03_bst.cpp -o bst && ./bst
```

---

## 🛠 Requirements สำหรับรัน C++

- **Windows:** ติดตั้งผ่าน Scoop → ดู [setup/vscode-cpp.md](setup/vscode-cpp.md)
- **macOS:** `xcode-select --install`
- **Linux:** `sudo apt install build-essential`
- **Standard:** C++17 (`-std=c++17`)

---

## 🤝 Contributing

ยินดีรับ PR และ Issue ครับ! ทั้ง typo, เพิ่มตัวอย่าง, หรือแจ้ง bug

---

*อ้างอิง: [GeeksforGeeks DSA](https://www.geeksforgeeks.org/dsa/) · [Programiz DSA](https://www.programiz.com/dsa) · [cp-algorithms.com](https://cp-algorithms.com/) · [USACO Guide](https://usaco.guide/)*
