#include "../Assets/Grid.h"
#include "../Assets/GridGenerator.h"
#include "../Assets/Player.h"
#include "../Assets/Unit.h"
#include <memory>
#include "ConsoleGameStateDrawer.h"
#include "CommandInvoker.h"
#include "../Assets/Command.h"
#include <conio.h>
#include <thread>
#include <chrono>
#include "../GraphicEngine/InputKey.h" //тут же у мене і черга



class GameHandler {
public:
    GameHandler() : gameGrid(10, 10) {}
    ~GameHandler() {}

    Grid gameGrid;

    Grid* GetGrid() {
        return &gameGrid;
    }


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


    bool HasUnitsOnGrid(std::shared_ptr<Player> player) {
        for (int x = 0; x < gameGrid.Width; ++x) {
            for (int y = 0; y < gameGrid.Height; ++y) {
                const Cell& cell = gameGrid.Cells[x][y];

                for (const auto& unit : cell.CellTakers) {
                    if (unit->GetOwner() == player.get())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void Run(CommandInvoker& invoker, InputQueue& inputQueue) {
        ConsoleGameStateDrawer drawer;
        drawer.Draw(gameGrid);

        bool isPlayerOneTurn = true;
        player1->IsYourTurn = true;
        player2->IsYourTurn = false;

        while (true) {
            std::shared_ptr<Player> currentPlayer = isPlayerOneTurn ? player1 : player2;
            std::string currentPlayerName = currentPlayer->Name;

           


            if (!HasUnitsOnGrid(currentPlayer)) {
                std::cout << currentPlayerName << " has no units left on the grid. Skipping turn.\n";
                invoker.executeCommand(std::make_shared<SkipTurnCommand>(currentPlayerName));
                isPlayerOneTurn = !isPlayerOneTurn;
                player1->IsYourTurn = isPlayerOneTurn;
                player2->IsYourTurn = !isPlayerOneTurn;
                drawer.Draw(gameGrid);
                continue;
            }

            auto key = inputQueue.Pop();
            if (!key.has_value()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            std::shared_ptr<Unit> currentUnit = isPlayerOneTurn ? unit1 : unit2;
            int dx = 0, dy = 0;
            bool isMove = false;

            switch (key.value()) {
            case InputKey::Up:    dy = -1; isMove = true; break;
            case InputKey::Down:  dy = 1;  isMove = true; break;
            case InputKey::Left:  dx = -1; isMove = true; break;
            case InputKey::Right: dx = 1;  isMove = true; break;
            case InputKey::EndTurn: {
                invoker.executeCommand(std::make_shared<SkipTurnCommand>(currentPlayerName));
                isPlayerOneTurn = !isPlayerOneTurn;
                player1->IsYourTurn = isPlayerOneTurn;
                player2->IsYourTurn = !isPlayerOneTurn;
                drawer.Draw(gameGrid);
                continue;
            }
            default: continue;
            }

            if (isMove) {
                int newX = currentUnit->GetCurrentX() + dx;
                int newY = currentUnit->GetCurrentY() + dy;

                if (!gameGrid.IsValidPosition(newX, newY)) {
                    std::cout << "Invalid move.\n";
                    continue;
                }

                invoker.executeCommand(std::make_shared<MoveCommand>(gameGrid, currentUnit, newX, newY));
                drawer.Draw(gameGrid);

                isPlayerOneTurn = !isPlayerOneTurn;
                player1->IsYourTurn = isPlayerOneTurn;
                player2->IsYourTurn = !isPlayerOneTurn;
            }
            gameGrid.Cells[currentUnit->GetCurrentX()][currentUnit->GetCurrentY()].UseSupplies();

        }
    }


   void _Run(CommandInvoker& invoker, InputQueue& inputQueue) {
       ConsoleGameStateDrawer drawer;
       drawer.Draw(gameGrid);

       bool isPlayerOneTurn = true;
       player1->IsYourTurn = true;
       player2->IsYourTurn = false;

       while (true) {
           std::shared_ptr<Unit> currentUnit = isPlayerOneTurn ? unit1 : unit2;
           std::string currentPlayerName = isPlayerOneTurn ? player1->Name : player2->Name;

           auto key = inputQueue.Pop();
           if (!key.has_value()) {
               std::this_thread::sleep_for(std::chrono::milliseconds(10));
               continue;
           }

           int dx = 0, dy = 0;
           bool isMove = false;

           switch (key.value()) {
           case InputKey::Up: dy = -1; isMove = true; break;
           case InputKey::Down: dy = 1; isMove = true; break;
           case InputKey::Left: dx = -1; isMove = true; break;
           case InputKey::Right: dx = 1; isMove = true; break;
           case InputKey::EndTurn: {
               invoker.executeCommand(std::make_shared<SkipTurnCommand>(currentPlayerName));
               isPlayerOneTurn = !isPlayerOneTurn;
               player1->IsYourTurn = isPlayerOneTurn;
               player2->IsYourTurn = !isPlayerOneTurn;
               continue;
           }
           default: continue;
           }

           if (isMove) {
               int newX = currentUnit->GetCurrentX() + dx;
               int newY = currentUnit->GetCurrentY() + dy;

               if (!gameGrid.IsValidPosition(newX, newY)) {
                   std::cout << "Invalid move.\n";
                   continue;
               }

               invoker.executeCommand(std::make_shared<MoveCommand>(gameGrid, currentUnit, newX, newY));
               drawer.Draw(gameGrid);
               isPlayerOneTurn = !isPlayerOneTurn;
               player1->IsYourTurn = isPlayerOneTurn;
               player2->IsYourTurn = !isPlayerOneTurn;
           }
       }
   }

   std::shared_ptr<Player> GetPlayer1() const {
       return player1;
   }

   std::shared_ptr<Player> GetPlayer2() const {
       return player2;
   }



private:
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    std::shared_ptr<Unit> unit1;
    std::shared_ptr<Unit> unit2;
};
