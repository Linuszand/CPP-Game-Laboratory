#pragma once
#include "core/Coord.h"
#include "core/Enums.h"
#include "core/Ship.h"
#include <vector>

namespace bs {

    enum class Cell : std::uint8_t
    {
        Empty,
        Ship,
        Hit,
        Miss,
        Invalid
    };

    class Board
    {
    public:
        Board(int width, int height);

        int Width() const { return m_width; }
        int Height() const { return m_height; }

        // Placement
        PlaceResult PlaceShip(const Ship& ship); // copies ship into internal list
        bool       InBounds(Coord c) const;
        Cell       GetCell(Coord c) const;
        void       SetCell(Coord c, Cell v);

        // Shooting
        ShotResult Shoot(Coord target);

        // Queries
        bool AllShipsSunk() const;

        // Debug/cheat (used by CLI):
        const std::vector<Ship>& Ships() const { return m_ships; }

        // Buggy: exposes internal grid for "convenience"
        const std::vector<Cell>& GridRaw() const { return m_grid; }

        int Index(Coord c) const { return c.y * m_width + c.x; }

    private:
        int m_width;
        int m_height;
        std::vector<Cell> m_grid;
        std::vector<Ship> m_ships;

        PlaceResult CanPlaceShip(const Ship& ship) const;
    };

} // namespace bs