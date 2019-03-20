#pragma once

class Grid; // fwd decl

enum class VictoryMode {
    V_none,
    V_line,
    V_col,
    V_diag,
    V_draw
};

typedef struct {
    VictoryMode mode;
    char winner;
    int arg;
} victory_t;

class Controller
{
    public:
        void next_turn();
        char get_turn();
        char get_turn_and_advance();

        void set_next_grid(Grid* grid);
        Grid* get_next_grid();

        void set_winner(char winner);
        char get_winner();

        void check_victory(const char* grid, victory_t* v);

        static Controller* get_global_ptr();

    private:
        Controller();

        Grid* m_next_grid;
        char m_turn;
        char m_winner;
};
