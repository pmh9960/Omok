#include <iostream>
#include <Windows.h>
#include "gotoxy.cpp"
using namespace std;

#define INF 999'999'999 // int 범위에서 큰 수
// □
// ●
// ○

void init_grid();

class Grid
{
private:
    int x_, y_;
    int color_;
    int grid_[19][19];

public:
    Grid()
    {
        x_ = 0;
        y_ = 0;
        for (int i = 0; i < 19; i++)
            for (int j = 0; j < 19; j++)
                grid_[i][j] = 0;
    }
    void set_stone(int color, bool isAI, int x, int y);
    int check_winner();
    int eval();
    int alpha_beta_search(int color, int depth);
    int max_value(int a, int b, int depth);
    int min_value(int a, int b, int depth);
    bool result(int x, int y);
    void remove(int x, int y);
    bool rule33();
    // bool rule6();
};

void Grid::set_stone(int color, bool isAI, int x, int y)
{
    if (!isAI)
    {
        color_ = color;
        gotoxy(0, 22);
        cout << "Player " << color_ << " 위치를 입력하십시오" << endl;
        cin >> x_ >> y_;
        gotoxy(0, 23);
        cout << "                 " << endl;
        cout << "                 " << endl;
    }
    else
    {
        color_ = color;
        x_ = x;
        y_ = y;
    }
    if (grid_[x_][y_] == 0 && x_ < 19 && y_ < 19 && rule33())
    {
        grid_[x_][y_] = color_;
        gotoxy(x_ * 2, y_);
        if (color_ == 1)
        {
            cout << "●";
        }
        else
        {
            cout << "○";
        }
    }
    else
        set_stone(color_, isAI, x, y);
}

int Grid::check_winner()
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            int cur = grid_[i][j];
            if (cur != color_)
                continue;
            else if (i < 15 && grid_[i + 1][j] == cur && grid_[i + 2][j] == cur && grid_[i + 3][j] == cur && grid_[i + 4][j] == cur)
            {
                if (i < 14 && grid_[i + 5][j] == cur)
                    continue;
                else if (i > 0 && grid_[i - 1][j] == cur)
                    continue;
                else
                    return cur;
            }

            else if (j < 15 && grid_[i][j + 1] == cur && grid_[i][j + 2] == cur && grid_[i][j + 3] == cur && grid_[i][j + 4] == cur)
            {
                if (j < 14 && grid_[i][j + 5] == cur)
                    continue;
                else if (j > 0 && grid_[i][j - 1] == cur)
                    continue;
                else
                    return cur;
            }
            else if (i < 15 && j < 15 && grid_[i + 1][j + 1] == cur && grid_[i + 2][j + 2] == cur && grid_[i + 3][j + 3] == cur && grid_[i + 4][j + 4] == cur)
            {
                if (i < 14 && j < 14 && grid_[i + 5][j + 5] == cur)
                    continue;
                else if (i > 0 && j > 0 && grid_[i - 1][j - 1] == cur)
                    continue;
                else
                    return cur;
            }
            else if (i > 3 && j < 15 && grid_[i - 1][j + 1] == cur && grid_[i - 2][j + 2] == cur && grid_[i - 3][j + 3] == cur && grid_[i - 4][j + 4] == cur)
            {
                if (i > 4 && j < 14 && grid_[i - 5][j + 5] == cur)
                    continue;
                else if (i < 18 && j > 0 && grid_[i + 1][j - 1] == cur)
                    continue;
                else
                    return cur;
            }
        }
    }
    return 0;
}

bool Grid::rule33()
{
    int count = 0, over = 0;
    int mx[12][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {-3, -2, -1, 1},
        {-2, -1, 1, 2},
        {-1, 1, 2, 3},
        {-3, -2, -1, 1},
        {-2, -1, 1, 2},
        {-1, 1, 2, 3},
        {-3, -2, -1, 1},
        {-2, -1, 1, 2},
        {-1, 1, 2, 3},
    };
    int my[12][4] = {
        {-3, -2, -1, 1},
        {-2, -1, 1, 2},
        {-1, 1, 2, 3},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {-3, -2, -1, 1},
        {-2, -1, 1, 2},
        {-1, 1, 2, 3},
        {3, 2, 1, -1},
        {2, 1, -1, -2},
        {1, -1, -2, -3}};
    // 가능한 33의 종류

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (x_ + mx[i][j] < 0 || x_ + mx[i][j] > 18) // 밖으로 나가면 안됨
                over = 1;
        }
        if (over == 0)
        {
            if (grid_[x_ + mx[i][0]][y_ + my[i][0]] == 0 && grid_[x_ + mx[i][3]][y_ + my[i][3]] == 0) // 양 끝은 비어있고
            {
                if (grid_[x_ + mx[i][1]][y_ + my[i][1]] == color_ && grid_[x_ + mx[i][2]][y_ + my[i][2]] == color_) // 중간은 같은 색의 돌 일 경우
                {
                    count++;
                }
            }
        }
    }
    if (count < 2)
        return true;
    else
        return false;
}

// bool Grid::rule6()
// {
// }

int Grid::alpha_beta_search(int color, int depth)
{
    color_ = color;
    int v = -INF, a = -INF, b = INF;
    int action_x = -1, action_y = -1;
    int temp_value;
    bool can_put;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            can_put = result(i, j); // 놓을 수 있는 지 확인, 놓을 수 있다면 놓는다.
            if (!can_put)
                continue;
            temp_value = min_value(a, b, depth - 1);
            grid_[i][j] = 0; // 상상으로 놓은 돌을 치움
            gotoxy(90, 0);
            cout << temp_value;
            if (v < temp_value)
            {
                v = temp_value;
                action_x = i;
                action_y = j;

                gotoxy(70, 0);
                cout << action_x;
                gotoxy(70, 1);
                cout << action_y;
                // Sleep(1000);
            }

            gotoxy(50, 0);
            cout << v;
            // Sleep(1000);
        }
    }
    return action_x * 19 + action_y;
}
int Grid::max_value(int a, int b, int depth)
{
    if (depth == 0)
    {
        return eval();
    }
    int temp_value, v = -INF;
    bool can_put;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            can_put = result(i, j); // 놓을 수 있는 지 확인, 놓을 수 있다면 놓는다.
            if (!can_put)
                continue;
            v = max(v, min_value(a, b, depth - 1));
            grid_[i][j] = 0; // 상상으로 놓은 돌을 치움
            if (v >= b)
                return v;
            a = max(a, v);

            // gotoxy(50, 0);
            // cout << v;
            // gotoxy(50, 1);
            // cout << a;
            // gotoxy(50, 2);
            // cout << b;
            // Sleep(1000);
        }
    }
    return v;
}
int Grid::min_value(int a, int b, int depth)
{
    if (depth == 0)
    {
        return eval();
    }
    int temp_value, v = INF;
    bool can_put;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            can_put = result(i, j); // 놓을 수 있는 지 확인, 놓을 수 있다면 놓는다.
            if (!can_put)
                continue;
            v = min(v, max_value(a, b, depth - 1));
            grid_[i][j] = 0; // 상상으로 놓은 돌을 치움
            if (v <= a)
                return v;
            b = min(b, v);

            // gotoxy(50, 0);
            // cout << v;
            // gotoxy(50, 1);
            // cout << a;
            // gotoxy(50, 2);
            // cout << b;
            // Sleep(1000);
        }
    }
    return v;
}
bool Grid::result(int x, int y)
{
    if (grid_[x][y] == 0 && rule33())
    {
        grid_[x][y] = color_;
        color_ = 3 - color_;
        return true;
    }
    return false;
}

int Grid::eval()
{
    return 1;
}

int main()
{
    int color = 1, win = 0, AI = 2;
    int action, action_x, action_y;
    Grid Omok;

    init_grid();

    while (1)
    {
        if (color == AI)
        {
            action = Omok.alpha_beta_search(color, 3);
            action_x = action / 19;
            action_y = action % 19;
            Omok.set_stone(color, true, action_x, action_y);
        }
        else
        {
            Omok.set_stone(color, false, 0, 0);
        }

        win = Omok.check_winner();
        if (win != 0)
        {
            gotoxy(0, 22);
            cout << "                                             " << endl;
            cout << "                                             " << endl;
            cout << "                                             " << endl;
            gotoxy(0, 22);
            cout << "Player " << win << " 승리!!!" << endl;
            break;
        }
        color = 3 - color;
    }

    gotoxy(0, 25);
    system("pause");
    return 0;
}

void init_grid()
{
    int i, j;
    for (i = 0; i < 19; i++)
    {
        cout << "□□□□□□□□□□□□□□□□□□□" << endl;
    }
    for (i = 0; i < 19; i++)
    {
        gotoxy(i * 2, 20);
        cout << i;
        gotoxy(40, i);
        cout << i;
    }
}