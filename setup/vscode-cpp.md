# 🛠 ติดตั้ง C++ + VSCode สำหรับมือใหม่

คู่มือนี้จะพาตั้งแต่ **เครื่องเปล่า** ไปจนถึง **รันโค้ด C++ ได้ใน VSCode** ครับ  
เลือก OS ของคุณแล้วทำตามขั้นตอนได้เลย

---

## สารบัญ

- [Windows (แนะนำ — ใช้ Scoop)](#-windows-แนะนำ--ใช้-scoop)
- [macOS](#-macos)
- [Linux (Ubuntu/Debian)](#-linux-ubuntudebian)
- [ตั้งค่า VSCode](#-ตั้งค่า-vscode)
- [ทดสอบรันโค้ด](#-ทดสอบรันโค้ด)
- [แก้ปัญหาที่พบบ่อย](#-แก้ปัญหาที่พบบ่อย)

---

## 🪟 Windows (แนะนำ — ใช้ Scoop)

ใช้ **Scoop** ซึ่งเป็น package manager สำหรับ Windows — ติดตั้งโปรแกรมได้ง่ายและไม่ต้องการ admin

### ขั้นที่ 1 — ติดตั้ง Scoop

เปิด **PowerShell ธรรมดา (ไม่ใช่ Run as Administrator)** แล้วรัน 2 คำสั่งนี้ตามลำดับ:

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

```powershell
Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
```

### ขั้นที่ 2 — ติดตั้ง Git

```powershell
scoop install git
```

### ขั้นที่ 3 — เพิ่มแหล่งดาวน์โหลดโปรแกรม (extras bucket)

```powershell
scoop bucket add extras
```

### ขั้นที่ 4 — ติดตั้ง MinGW (GCC Compiler)

```powershell
scoop install extras/mingw
```

### ขั้นที่ 5 — ติดตั้ง VSCode

```powershell
scoop install extras/vscode
```

### ขั้นที่ 6 — เพิ่ม Extension ใน VSCode

เปิด VSCode → กด `Ctrl+Shift+X` ค้นหาและติดตั้ง:

- **Code Runner** โดย Jun Han

### ขั้นที่ 7 — ตรวจสอบว่า g++ พร้อมใช้

เปิด Terminal ใน VSCode (เลือก PowerShell) แล้วรัน:

```powershell
get-command g++
```

> ✅ ผลลัพธ์ควรเป็น path ที่ขึ้นต้นด้วย `C:\` เช่น `C:\Users\...\scoop\apps\mingw\...\g++.exe`

---

## 🍎 macOS

เปิด **Terminal** แล้วรัน:

```bash
xcode-select --install
```

กดติดตั้งตามขั้นตอน (~2-5 นาที) แล้วทดสอบ:

```bash
g++ --version
```

> **หมายเหตุ:** macOS ใช้ Clang แทน GCC จริงๆ แต่คำสั่ง `g++` ทำงานได้เหมือนกัน

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

### ตั้งค่า Code Runner ให้รันใน Terminal

1. กด `Ctrl+,` เพื่อเปิด Settings
2. ค้นหา `code-runner.runInTerminal`
3. **เปิดใช้งาน** (ติ๊กถูก) — สำคัญมาก ไม่งั้นรับ input ไม่ได้

---

## ✅ ทดสอบรันโค้ด

### วิธีที่ 1 — ใช้ Code Runner (ง่ายที่สุด)

1. เปิดไฟล์ `.cpp` เช่น `examples/01-tree/01_node_basic.cpp`
2. กด **▶ Run** มุมขวาบน หรือ `Ctrl+Alt+N`
3. ดูผลลัพธ์ใน Terminal ด้านล่าง

### วิธีที่ 2 — ใช้ Terminal โดยตรง (แนะนำ)

```bash
# Compile
g++ -std=c++17 -Wall examples/01-tree/03_bst.cpp -o bst

# รัน
./bst           # macOS / Linux
.\bst.exe       # Windows PowerShell
```

---

## 🔧 แก้ปัญหาที่พบบ่อย

### ❌ `get-command g++` ไม่เจอ หรือ error

รีสตาร์ท VSCode แล้วลองใหม่ — Scoop อัปเดต PATH ต้องเปิด terminal ใหม่ถึงจะเห็น

### ❌ Code Runner รันแล้วไม่แสดงผล

ตรวจสอบว่าเปิด `code-runner.runInTerminal` ใน Settings แล้ว

### ❌ Compile ผ่านแต่รันแล้วหน้าต่างปิดทันที (Windows)

รันผ่าน Terminal แทน Code Runner โดยตรง

---

## 📌 คำสั่งที่ใช้บ่อย

```bash
# Compile พร้อม C++17 + Warning
g++ -std=c++17 -Wall main.cpp -o main

# รัน
./main          # macOS/Linux
.\main.exe      # Windows PowerShell
```

---

*หากติดปัญหาอื่นๆ เปิด Issue ใน repo ได้เลยครับ* 🙌
