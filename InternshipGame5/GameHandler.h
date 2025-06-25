#include "../Assets/Grid.h"
#include "../Assets/GridGenerator.h"
#include "../Assets/Player.h"
#include "../Assets/Unit.h"
#include <memory>
#include "ConsoleGameStateDrawer.h"
#include "CommandInvoker.h"
#include "../Assets/Command.h"
#include <conio.h>


class GameHandler {
public:
    GameHandler() : gameGrid(10, 10) {}
    ~GameHandler() {}

    Grid gameGrid;

    void Initiate() {
        GridGenerator generator;
        generator.GenerateTerrain(gameGrid);

        player1 = std::make_shared<Player>("1player");
        player2 = std::make_shared<Player>("2player");

        unit1 = std::make_shared<Unit>(3, player1.get());
        unit2 = std::make_shared<Unit>(3, player2.get());

        unit1->SetCoordinates(2, 7);
        unit2->SetCoordinates(7, 2);

        gameGrid.Cells[2][7].AddUnit(unit1);
        gameGrid.Cells[7][2].AddUnit(unit2);
    }


   void Run(CommandInvoker& invoker) {
    ConsoleGameStateDrawer drawer;
    drawer.Draw(gameGrid);

    bool isPlayerOneTurn = true;
    while (true) {
        std::shared_ptr<Unit> currentUnit = isPlayerOneTurn ? unit1 : unit2;
        std::string currentPlayerName = isPlayerOneTurn ? player1->Name : player2->Name;

        std::cout << "\n" << currentPlayerName << "'s turn\n";

        char input = _getch();  // <-- читання без Enter
        std::cout << input << "\n";  // Ехо-вивід символу (щоб гравець бачив, що натиснув)

        int dx = 0, dy = 0;
        switch (tolower(input)) {
        case 'w': dy = -1; break;
        case 's': dy = 1; break;
        case 'a': dx = -1; break;
        case 'd': dx = 1; break;
        case 'q': {
            std::shared_ptr<Command> skipCmd = std::make_shared<SkipTurnCommand>(currentPlayerName);
            invoker.executeCommand(skipCmd);
            isPlayerOneTurn = !isPlayerOneTurn;
            continue;
        }
        default:
            std::cout << "Invalid input. Use W, A, S, D, or Q.\n";
            continue;
        }

        int newX = currentUnit->GetCurrentX() + dx;
        int newY = currentUnit->GetCurrentY() + dy;

        if (!gameGrid.IsValidPosition(newX, newY)) {
            std::cout << "Can't move outside the grid.\n";
            continue;
        }

        std::shared_ptr<Command> moveCmd = std::make_shared<MoveCommand>(gameGrid, currentUnit, newX, newY);
        invoker.executeCommand(moveCmd);

        drawer.Draw(gameGrid);
        isPlayerOneTurn = !isPlayerOneTurn;
    }

    /* while (true) {
        std::shared_ptr<Unit> currentUnit = isPlayerOneTurn ? unit1 : unit2;
        std::string currentPlayerName = isPlayerOneTurn ? player1->Name : player2->Name;

        std::cout << "\n" << currentPlayerName << "'s turn (WASD to move, Q to skip): ";
        char input;
        std::cin >> input;

        // Визначаємо напрям руху
        int dx = 0, dy = 0;
            switch (tolower(input)) {
            case 'w': dy = -1; break;
            case 's': dy = 1; break;
            case 'a': dx = -1; break;
            case 'd': dx = 1; break;
            case 'q': {
                std::shared_ptr<Command> skipCmd = std::make_shared<SkipTurnCommand>(currentPlayerName);
                invoker.executeCommand(skipCmd);
                isPlayerOneTurn = !isPlayerOneTurn;  // Зміна гравця навіть при пропуску
                continue;
            }
            default:
                std::cout << "Invalid input. Use W, A, S, D, or Q.\n";
                continue;
        }

        int newX = currentUnit->GetCurrentX() + dx;
        int newY = currentUnit->GetCurrentY() + dy;

        // Перевірка на валідність координат
        if (!gameGrid.IsValidPosition(newX, newY)) {
            std::cout << "Can't move outside the grid.\n";
            continue;
        }

        std::shared_ptr<Command> moveCmd = std::make_shared<MoveCommand>(gameGrid, currentUnit, newX, newY);
        invoker.executeCommand(moveCmd);

        drawer.Draw(gameGrid);
        isPlayerOneTurn = !isPlayerOneTurn;  // Зміна гравця
    } */
}


private:
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    std::shared_ptr<Unit> unit1;
    std::shared_ptr<Unit> unit2;
};
