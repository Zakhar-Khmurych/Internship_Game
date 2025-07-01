#pragma once
#include <atomic>
#include <conio.h>  // ��� _kbhit() � _getch()

class InputHandler {
public:
    InputHandler(std::atomic<char>& inputChar)
        : inputChar(inputChar) {}

    void CheckInput() {
        if (_kbhit()) {
            inputChar = _getch();  // ��������� �������� �����
        }
    }

private:
    std::atomic<char>& inputChar;
};
