<!-- Ad Maiorem Dei Gloriam! -->
# CPaint
A basic paint editor made in C with Raylib!

## Why it was made
I wanted to test my skills in a low level language without AI. This was really hard, but really rewarding when it did well XP. This project was made for [Hack Club Phantom](https://phantom.hackclub.com), and all the troubleshotting is self documented on the commits!

## Features
- Color switching
- Canvas saving
- Draggable viewport
- Zoomable viewport
- Undo-Redo support via command pattern

## How to compile
Requires Cmake, a C compiler, internet connection and raylib globally installed on your system.
1. Clone the repo with `git clone https://github.com/Renan-G-projec/CPaint`
2. Under the clonned repo, run `cmake -B build && cmake --build build`
3. Then, run the code with `./build/CPaint` (backslash on windows)

You can skip the steps 2 and 3 if your IDE does that for you.

## NOTES ABOUT COMPILING
(11/26/2026) As it is right now, nvdialog have a critical memory bug on linux gtk, where it frees a string that was never allocated. I have not forked yet, so it may be a problem to compile. A issue shall be opened soon.

## AI Disclosure
NONE AI was used for generating assets, generating code, debugging or any part of the development of this software, not even google AI overview.