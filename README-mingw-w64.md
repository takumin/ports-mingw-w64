---
# FreeBSD 向け MinGW-w64
作ってみました。

---
# ターゲットアーキテクチャ、スレッドモデルと例外処理形式について
基本的に下記ルールに則った命名になります。

mingw-w64-${ターゲットアーキテクチャ}-${スレッドモデル}-${例外処理形式}

## ターゲットアーキテクチャ
- multilib (i686-w64-mingw32 + x86_64-w64-mingw32)
- i686-w64-mingw32 (Windows 32bit)
- x86_64-w64-mingw32 (Windows 64bit)

## スレッドモデル
- win32
- posix

## 例外処理形式
- Windows 32bit
-- sljl or dwarf2
- Windows 64bit
-- sljl or seh
