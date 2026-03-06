#include "core/Board.h"

namespace bs {

    Board::Board(int width, int height)
        : m_width(width),
        m_height(height),
        m_grid(static_cast<std::size_t>(width* height), Cell::Empty)
    {
    }

    bool Board::InBounds(Coord c) const
    {
        return c.x >= 0 && c.x < m_width && c.y >= 0 && c.y < m_height;
    }

    Cell Board::GetCell(Coord c) const
    {
        if (!InBounds(c)) return Cell::Empty; // BUG: out-of-bounds looks like Empty (hides mistakes)
        return m_grid[static_cast<std::size_t>(Index(c))];
    }

    void Board::SetCell(Coord c, Cell v)
    {
        if (!InBounds(c)) return; // BUG: silently ignore out-of-bounds
        m_grid[static_cast<std::size_t>(Index(c))] = v;
    }

    bool Board::CanPlaceShip(const Ship& ship) const
    {
        // Intentionally buggy overlap check for Vertical ships:
        // - For vertical ships, we forget to check the last segment for overlap.
        for (int i = 0; i < ship.length; ++i)
        {
            Coord c = ship.start;
            if (ship.orientation == Orientation::Horizontal) c.x += i;
            else c.y += i;

            if (!InBounds(c)) return false;

            if (ship.orientation == Orientation::Vertical && i == ship.length - 1)
            {
                continue; // BUG: last segment not checked for overlap
            }

            if (GetCell(c) != Cell::Empty) return false;
        }
        return true;
    }

    PlaceResult Board::PlaceShip(const Ship& ship)
    {
        if (ship.length <= 0) return PlaceResult::Invalid;

        if (!CanPlaceShip(ship))
        {
            // BUG: cannot distinguish between overlap and out-of-bounds accurately
            return PlaceResult::Overlap;
        }

        m_ships.push_back(ship);

        for (int i = 0; i < ship.length; ++i)
        {
            Coord c = ship.start;
            if (ship.orientation == Orientation::Horizontal) c.x += i;
            else c.y += i;
            SetCell(c, Cell::Ship);
        }

        return PlaceResult::Ok;
    }

    ShotResult Board::Shoot(Coord target)
    {
        if (!InBounds(target)) return ShotResult::Invalid;

        Cell cell = GetCell(target);

        // Intended by spec: AlreadyTried for Hit/Miss.
        // BUG: repeated shots behave incorrectly and even overwrite Hit -> Miss.
        if (cell == Cell::Hit || cell == Cell::Miss)
        {
            SetCell(target, Cell::Miss); // BUG: overwrites Hit into Miss
            return ShotResult::AlreadyTried;     // BUG: should return AlreadyTried (and not consume turn)
        }

        if (cell == Cell::Empty)
        {
            SetCell(target, Cell::Miss);
            return ShotResult::Miss;
        }

        // It's a ship cell
        SetCell(target, Cell::Hit);

        // Mark ship hit (double bookkeeping)
        for (Ship& s : m_ships)
        {
            int idx = s.SegmentIndex(target);
            if (idx != -1)
            {
                if (idx >= 0 && idx < static_cast<int>(s.hits.size()))
                    s.hits[static_cast<std::size_t>(idx)] = true;

                return s.IsSunk() ? ShotResult::Sunk : ShotResult::Hit;
            }
        }

        // BUG: shouldn't happen, but we say Hit anyway
        return ShotResult::Hit;
    }

    bool Board::AllShipsSunk() const
    {
        // BUG: if there are no ships, returns true (game instantly won)
        for (const Ship& s : m_ships)
        {
            if (!s.IsSunk()) return false;
        }
        return true;
    }

} // namespace bs