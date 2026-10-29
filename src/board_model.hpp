#pragma once
#include <array>

namespace FrogToad {
    /** @brief Owns the board state, enforces movement rules, and calculates game status. */
    class BoardModel {
    public:
        static constexpr int BoardSize = 7;

        /** Frogs move right; toads move left. */
        enum class Cell { Empty, Frog, Toad };

        enum class GameState { Playing, Solved, Lost };

        /** @brief Reset to the starting configuration. */
        void reset();

        bool canPlayerMove() const;

        /** @brief Return whether the board matches the goal. */
        bool isSolved() const;



        /** @brief Returns game state. Unsolved boards report Playing until loss detection is implemented. */
        GameState state() const;

        /**
         * @brief Test the piece at a zero-based index for a legal move without changing the board.
         * @return True if movable; false for invalid, empty, or blocked cells.
         */
        bool canMove(int index) const;

        /** @brief Return the cell at a zero-based index, or Cell::Empty if out of range. */
        Cell cellAt(int index) const;

        /**
         * @brief Attempt a slide or hop in the piece's movement direction.
         * A slide enters an adjacent empty cell; a hop crosses one opposite-species
         * piece and lands in an empty cell. Rejected moves leave the board unchanged.
         * @param index Zero-based index of the piece to move.
         * @return True if moved; false for an invalid index, empty cell, or blocked move.
         */
        bool tryMove(int index);

    private:
        static constexpr std::array<Cell, BoardSize> StartingBoard{ Cell::Frog, Cell::Frog, Cell::Frog, Cell::Empty, Cell::Toad, Cell::Toad, Cell::Toad };
        
        static constexpr std::array<Cell, BoardSize> GoalBoard{ Cell::Toad, Cell::Toad, Cell::Toad, Cell::Empty, Cell::Frog, Cell::Frog, Cell::Frog };

        std::array<Cell, BoardSize> board{ StartingBoard };

        /** @brief Return whether index is in [0, BoardSize). */
        static constexpr bool isIndexValid(int index);

        /** @brief Return +1 for Frog or -1 for Toad; cell must be occupied. */
        static constexpr int moveDirection(Cell cell);

        /** @brief Test for Cell::Empty; index must be valid. */
        bool isCellEmpty(int index) const;

        /** @brief Return a legal destination for a zero-based cell, or -1 if no move is possible. */
        int moveDestination(int index) const;
    };
}
