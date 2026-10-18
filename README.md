# 4人用マルチタップの動作テスト for FC
## 概要
ファミコンの周辺機器、4人用マルチタップの動作テストをするプログラムです。
通常はコントローラーをクロックを8bit送って終わりですが、4人用マルチタップの場合はクロックを24bit送ります。

## Files
build.bat：ビルドするバッチファイルです。開発環境は「cc65」を使っています。

rom.nes：ROMイメージファイル。

## 使い方
対応カートリッジはMapper 0。PRG-ROM 32KB(FLASH)、CHR-RAM 8KB(SRAM)。
https://github.com/nicotakuya/diyfccartridge

rom.nesをカートリッジに書き込んでファミコンで動かします。

ファミコンの拡張端子(EXPAND CONNECTOR)に4人用マルチタップを接続します。

起動後、コントローラのボタンを押すと、画面の該当箇所に値が表示されます。

## Screenshot
<img width="514" height="451" alt="Image" src="https://github.com/user-attachments/assets/405ed7c9-f810-4bb7-a896-8f4e3c6af7dd" />
