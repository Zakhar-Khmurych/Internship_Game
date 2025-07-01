#pragma once
#include <atomic>
#include <conio.h>  // Для _kbhit() і _getch()

class InputHandler {
public:
    InputHandler(std::atomic<char>& inputChar)
        : inputChar(inputChar) {}

    void CheckInput() {
        if (_kbhit()) {
            inputChar = _getch();  // Оновлюємо атомарну змінну
        }
    }

private:
    std::atomic<char>& inputChar;
};
