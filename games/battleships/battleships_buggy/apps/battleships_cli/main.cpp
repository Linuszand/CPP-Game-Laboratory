#include "core/Game.h"
#include "cli/ConsoleRenderer.h"
#include "cli/Input.h"
#include <iostream>
#include <string>

using namespace bs;

static void PrintHelp()
{
    std::cout <<
        "Commands:\n"
        "  help                - show this help\n"
        "  quit                - quit game\n"
        "  reveal              - toggle reveal ships on your own board (debug)\n"
        "  During play:\n"
        "    shoot A5           - shoot coordinate\n"
        "    or just: A5\n\n";
}

static Orientation AskOrientation()
{
    std::cout << "Orientation (h/v): ";
    std::string s;
    std::getline(std::cin, s);
    if (!s.empty() && (s[0] == 'v' || s[0] == 'V')) return Orientation::Vertical;
    return Orientation::Horizontal;
}

int main()
{
    // Spec defaults: 10x10 grid, ships 2/3/3/4/5 (in Game::ShipLengths()).
    Game game(10, 10);
    game.StartSetup();

    ConsoleRenderer r;
    bool reveal = false;

    while (true)
    {
        r.ClearScreen();

        if (game.State() == GameState::Setup)
        {
            r.PrintTitle("Battleships (BUGGY) - Setup");
            const auto& player = game.CurrentPlayer();
            std::cout << player.name << ", place your ships.\n\n";

            RenderOptions opt;
            opt.revealShips = true;
            r.PrintBoard(player.own, opt);

            int placed = static_cast<int>(player.own.Ships().size());

            if (placed >= static_cast<int>(game.ShipLengths().size()))
            {
                std::cout << "All ships placed for " << player.name << ". Press Enter to continue...\n";
                std::string tmp; std::getline(std::cin, tmp);
                // BUG: may start Playing too early (before both players finished)
                game.NextPlayerDuringSetup();
                // Changed placement for FinishSetupIfReady(); to be under NextPlayerDuringSetup(); If we don't the game will start
                // without Player2 having placed his/her ships.
                game.FinishSetupIfReady();
                continue;
            }

            int length = game.ShipLengths()[static_cast<std::size_t>(placed)];
            std::cout << "Place ship of length " << length << ". Enter start coord (e.g. A1): ";

            std::string line;
            std::getline(std::cin, line);
            Command cmd = ParseCommandLoose(line);
            if (cmd.type == CommandType::Quit) break;
            if (cmd.type == CommandType::Help)
            {
                PrintHelp();
                std::cout << "Press Enter...\n";
                std::getline(std::cin, line);
                continue;
            }

            Coord start = (cmd.type == CommandType::Shoot) ? cmd.shootTarget : ParseCoordLoose(line);
            Orientation o = AskOrientation();

            PlaceResult pr = game.PlaceShipForCurrent(Ship{ length, start, o });
            if (pr != PlaceResult::Ok)
            {
                // BUG: not informative (spec asks to distinguish OutOfBounds vs Overlap).
                std::cout << "Could not place ship. (buggy message, no detail)\n";
                std::cout << "Press Enter...\n";
                std::getline(std::cin, line);
            }
            continue;
        }

        if (game.State() == GameState::Playing)
        {
            r.PrintTitle("Battleships (BUGGY) - Play");
            auto& current = game.CurrentPlayerMut();
            auto& other = game.OtherPlayerMut();

            std::cout << "Turn: " << current.name << "\n\n";
            r.PrintTwoBoards(current, other, RenderOptions{ reveal, true });

            std::cout << "Enter command (A5 / shoot A5 / help / quit / reveal): ";
            std::string line;
            std::getline(std::cin, line);

            Command cmd = ParseCommandLoose(line);
            if (cmd.type == CommandType::Quit) break;
            if (cmd.type == CommandType::Help)
            {
                PrintHelp();
                std::cout << "Press Enter...\n";
                std::getline(std::cin, line);
                continue;
            }
            if (cmd.type == CommandType::RevealToggle)
            {
                reveal = !reveal;
                continue;
            }

            if (cmd.type == CommandType::Shoot)
            {
                ShotResult sr = game.ShootAtOpponent(cmd.shootTarget);
                std::cout << "Result: ";
                switch (sr)
                {
                case ShotResult::Miss:   std::cout << "Miss\n"; break;
                case ShotResult::Hit:    std::cout << "Hit\n"; break;
                case ShotResult::Sunk:   std::cout << "Sunk!\n"; break;
                case ShotResult::Invalid:std::cout << "Invalid\n"; break;
                default:                 std::cout << "?\n"; break;
                }

                std::cout << "Press Enter...\n";
                std::getline(std::cin, line);
            }
            continue;
        }

        if (game.State() == GameState::GameOver)
        {
            r.PrintTitle("Battleships (BUGGY) - Game Over");
            int winner = game.WinnerIndex();

            if (winner >= 0)
                std::cout << "Winner: " << (winner == 0 ? "Player 1" : "Player 2") << "\n";
            else
                std::cout << "Winner: (unknown)\n";

            std::cout << "\nPress Enter to quit...\n";
            std::string tmp; std::getline(std::cin, tmp);
            break;
        }
    }

    std::cout << "Bye!\n";
    return 0;
}