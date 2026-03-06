# 🛠 ติดตั้ง C++ + VSCode สำหรับมือใหม่

คู่มือนี้จะพาตั้งแต่ **เครื่องเปล่า** ไปจนถึง **รันโค้ด C++ ได้ใน VSCode** ครับ  
เลือก OS ของคุณแล้วทำตามขั้นตอนได้เลย

---

## สารบัญ

- [Windows](#-windows)
- [macOS](#-macos)
- [Linux (Ubuntu/Debian)](#-linux-ubuntudebian)
- [ตั้งค่า VSCode](#-ตั้งค่า-vscode)
- [ทดสอบรันโค้ด](#-ทดสอบรันโค้ด)
- [แก้ปัญหาที่พบบ่อย](#-แก้ปัญหาที่พบบ่อย)

---

## 🪟 Windows

### ขั้นที่ 1 — ติดตั้ง MinGW-w64 (GCC Compiler สำหรับ Windows)

1. เข้าไปที่ [winlibs.com](https://winlibs.com/) แล้วคลิก **Download** ที่ช่อง  
   `GCC 13.x.x + LLVM/Clang ... Win64 — UCRT — MSVCRT → Zip archive`

2. แตกไฟล์ zip → ได้โฟลเดอร์ `mingw64`

3. **ย้ายโฟลเดอร์** `mingw64` ไปไว้ที่ `C:\mingw64`

4. เพิ่ม Path ให้ระบบรู้จัก compiler:
   - กด **Win + S** → พิมพ์ `environment variables` → คลิก **Edit the system environment variables**
   - คลิก **Environment Variables...**
   - ในช่อง **System variables** → เลือก `Path` → คลิก **Edit**
   - คลิก **New** → พิมพ์ `C:\mingw64\bin` → กด **OK** ทุกหน้าต่าง

5. เปิด **Command Prompt** ใหม่แล้วทดสอบ:
   ```
   g++ --version
   ```
   ถ้าเห็นเวอร์ชัน g++ แสดงว่าสำเร็จ ✅

---

## 🍎 macOS

### ขั้นที่ 1 — ติดตั้ง Command Line Tools (มี g++ ติดมาด้วย)

เปิด **Terminal** แล้วรัน:

```bash
xcode-select --install
```

กดติดตั้งตามขั้นตอน (~2-5 นาที)

ทดสอบ:
```bash
g++ --version
```

> **หมายเหตุ:** macOS จะใช้ Clang แทน GCC จริงๆ แต่คำสั่ง `g++` ทำงานได้เหมือนกันครับ

---

## 🐧 Linux (Ubuntu/Debian)

เปิด **Terminal** แล้วรัน:

```bash
sudo apt update
sudo apt install build-essential -y
```

ทดสอบ:
```bash
g++ --version
```

---

## 💻 ตั้งค่า VSCode

### ขั้นที่ 1 — ดาวน์โหลด VSCode

ไปที่ [code.visualstudio.com](https://code.visualstudio.com/) → Download ตาม OS

### ขั้นที่ 2 — ติดตั้ง Extension ที่จำเป็น

เปิด VSCode → กด `Ctrl+Shift+X` (หรือ `Cmd+Shift+X` บน Mac)  
ค้นหาและติดตั้ง Extension เหล่านี้:

| Extension | ผู้พัฒนา | ใช้ทำอะไร |
|---|---|---|
| **C/C++** | Microsoft | Syntax highlight, IntelliSense |
| **C/C++ Extension Pack** | Microsoft | รวม Tools ที่จำเป็นทั้งหมด |
| **Code Runner** | Jun Han | รันโค้ดด้วยปุ่มเดียว |

### ขั้นที่ 3 — ตั้งค่า Code Runner

1. กด `Ctrl+,` เพื่อเปิด Settings
2. ค้นหา `code-runner.runInTerminal`
3. **เปิดใช้งาน** (ติ๊กถูก) — สำคัญมาก ไม่งั้นรับ input ไม่ได้

### ขั้นที่ 4 — สร้างไฟล์ Config `.vscode/tasks.json`

ใน VSCode เปิดโฟลเดอร์ repo → กด `Ctrl+Shift+P` → พิมพ์ `Tasks: Configure Default Build Task` → เลือก `C/C++: g++ build active file`

VSCode จะสร้างไฟล์ `.vscode/tasks.json` ให้อัตโนมัติ หน้าตาประมาณนี้:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "cppbuild",
      "label": "Build C++ file",
      "command": "/usr/bin/g++",
      "args": [
        "-std=c++17",
        "-Wall",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

> **Windows:** เปลี่ยน `"command"` เป็น `"C:/mingw64/bin/g++.exe"`

---

## ✅ ทดสอบรันโค้ด

### วิธีที่ 1 — ใช้ Code Runner (ง่ายที่สุด)

1. เปิดไฟล์ `.cpp` ใดก็ได้ เช่น `examples/01-tree/01_node_basic.cpp`
2. กด **▶ Run** มุมขวาบน หรือ `Ctrl+Alt+N`
3. ดูผลลัพธ์ใน Terminal ด้านล่าง

### วิธีที่ 2 — ใช้ Terminal โดยตรง (แนะนำ เข้าใจ process ดีกว่า)

```bash
# เข้าโฟลเดอร์ตัวอย่าง
cd examples/01-tree

# Compile
g++ -std=c++17 -Wall 01_node_basic.cpp -o node_basic

# รัน
./node_basic          # macOS / Linux
node_basic.exe        # Windows
```

### วิธีที่ 3 — ใช้ Build Task

เปิดไฟล์ `.cpp` แล้วกด `Ctrl+Shift+B` — VSCode จะ compile ไฟล์ที่เปิดอยู่

---

## 🔧 แก้ปัญหาที่พบบ่อย

### ❌ `g++: command not found` หรือ `'g++' is not recognized`

**Windows:** Path ยังไม่ถูก — ทำซ้ำขั้นตอนเพิ่ม `C:\mingw64\bin` ใน Environment Variables แล้วเปิด Terminal ใหม่

**macOS:** รัน `xcode-select --install` อีกครั้ง

**Linux:** รัน `sudo apt install build-essential -y` อีกครั้ง

---

### ❌ ไม่เห็น IntelliSense / autoComplete

กด `Ctrl+Shift+P` → `C/C++: Select IntelliSense Configuration` → เลือก compiler ที่ติดตั้ง

---

### ❌ Compile ผ่านแต่รันแล้วหน้าต่างปิดทันที (Windows)

เพิ่มบรรทัดนี้ก่อน `return 0;` ในโค้ด:
```cpp
system("pause");  // Windows only
```

หรือรันผ่าน Terminal แทน Code Runner

---

### ❌ ใช้ C++17 features ไม่ได้ (`structured bindings` ฯลฯ)

ตรวจสอบว่า compile flag มี `-std=c++17`:
```bash
g++ -std=c++17 myfile.cpp -o myfile
```

---

## 📌 Summary คำสั่งที่ใช้บ่อย

```bash
# Compile ธรรมดา
g++ main.cpp -o main

# Compile พร้อม C++17 + Warning
g++ -std=c++17 -Wall main.cpp -o main

# Compile + Debug info
g++ -std=c++17 -g main.cpp -o main

# รัน
./main          # macOS/Linux
main.exe        # Windows
```

---

*หากติดปัญหาอื่นๆ เปิด Issue ใน repo ได้เลยครับ* 🙌
