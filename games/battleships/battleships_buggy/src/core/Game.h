#pragma once
#include "core/Board.h"
#include "core/Enums.h"
#include <string>
#include <vector>

namespace bs {

    enum class GameState : std::uint8_t
    {
        Setup,
        Playing,
        GameOver
    };

    struct Player
    {
        std::string name{ "Player" };
        Board own;
        Board tracking; // what this player knows about opponent

        explicit Player(std::string n, int w, int h)
            : name(std::move(n)), own(w, h), tracking(w, h) {
        }
    };

    class Game
    {
    public:
        Game(int width, int height);

        GameState State() const { return m_state; }
        int CurrentPlayerIndex() const { return m_current; }

        const Player& CurrentPlayer() const { return m_players[static_cast<std::size_t>(m_current)]; }
        const Player& OtherPlayer() const { return m_players[static_cast<std::size_t>(1 - m_current)]; }

        Player& CurrentPlayerMut() { return m_players[static_cast<std::size_t>(m_current)]; }
        Player& OtherPlayerMut() { return m_players[static_cast<std::size_t>(1 - m_current)]; }

        void StartSetup();
        void FinishSetupIfReady(); // BUG: too permissive (starts too early)

        // Setup actions
        PlaceResult PlaceShipForCurrent(const Ship& ship);
        void NextPlayerDuringSetup();
        // Play actions
        ShotResult ShootAtOpponent(Coord c);

        bool IsOver() const { return m_state == GameState::GameOver; }
        int WinnerIndex() const { return m_winner; }

        const std::vector<int>& ShipLengths() const { return m_shipLengths; }

    private:
        GameState m_state{ GameState::Setup };
        int m_current{ 0 };
        int m_winner{ -1 };

        int m_width;
        int m_height;

        std::vector<Player> m_players;

        // As required by spec: 2,3,3,4,5
        std::vector<int> m_shipLengths{ 2,3,3,4,5 };

        int m_setupPlacedCount[2]{ 0,0 };

        void AdvanceTurn();
    };

} // namespace bs