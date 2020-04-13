#include <iostream>
#include <Windows.h>
#include "gotoxy.cpp"
using namespace std;

#define INF 999'999'999 // int �������� ū ��
// ��
// ��
// ��

void init_grid();

class Grid
{
private:
    int x_, y_;
    int color_;
    int grid_[30][30];

public:
    Grid()
    {
        x_ = 0;
        y_ = 0;
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 30; j++)
                grid_[i][j] = 9;
        for (int i = 0 + 4; i < 19 + 4; i++)
            for (int j = 0 + 4; j < 19 + 4; j++)
                grid_[i][j] = 0;
    }
    void set_stone(int color, bool isAI, int x, int y);
    int check_winner();
    int eval(int AI);
    int alpha_beta_search(int AI, int color, int depth);
    int max_value(int AI, int a, int b, int depth);
    int min_value(int AI, int a, int b, int depth);
    bool result(int x, int y);
    void remove(int x, int y);
    bool rule33();
    // bool rule6();
    void showGrid();
};

void Grid::set_stone(int color, bool isAI, int x, int y)
{
    if (!isAI)
    {
        color_ = color;
        gotoxy(0, 22);
        cout << "Player " << color_ << " ��ġ�� �Է��Ͻʽÿ�" << endl;
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
    if (grid_[x_ + 4][y_ + 4] == 0 && x_ < 19 + 4 && y_ < 19 + 4 && rule33())
    {
        grid_[x_ + 4][y_ + 4] = color_;
        gotoxy(x_ * 2, y_);
        if (color_ == 1)
        {
            cout << "��";
        }
        else
        {
            cout << "��";
        }
    }
    else
        set_stone(color_, isAI, x, y);
}

int Grid::check_winner()
{
    for (int i = 0 + 4; i < 19 + 4; i++)
    {
        for (int j = 0 + 4; j < 19 + 4; j++)
        {
            int cur = grid_[i][j];
            if (cur != color_)
                continue;
            else if (i < 15 + 4 && grid_[i + 1][j] == cur && grid_[i + 2][j] == cur && grid_[i + 3][j] == cur && grid_[i + 4][j] == cur)
            {
                if (i < 14 + 4 && grid_[i + 5][j] == cur)
                    continue;
                else if (i > 0 + 4 && grid_[i - 1][j] == cur)
                    continue;
                else
                    return cur;
            }

            else if (j < 15 + 4 && grid_[i][j + 1] == cur && grid_[i][j + 2] == cur && grid_[i][j + 3] == cur && grid_[i][j + 4] == cur)
            {
                if (j < 14 + 4 && grid_[i][j + 5] == cur)
                    continue;
                else if (j > 0 + 4 && grid_[i][j - 1] == cur)
                    continue;
                else
                    return cur;
            }
            else if (i < 15 + 4 && j < 15 + 4 && grid_[i + 1][j + 1] == cur && grid_[i + 2][j + 2] == cur && grid_[i + 3][j + 3] == cur && grid_[i + 4][j + 4] == cur)
            {
                if (i < 14 + 4 && j < 14 + 4 && grid_[i + 5][j + 5] == cur)
                    continue;
                else if (i > 0 + 4 && j > 0 + 4 && grid_[i - 1][j - 1] == cur)
                    continue;
                else
                    return cur;
            }
            else if (i > 3 + 4 && j < 15 + 4 && grid_[i - 1][j + 1] == cur && grid_[i - 2][j + 2] == cur && grid_[i - 3][j + 3] == cur && grid_[i - 4][j + 4] == cur)
            {
                if (i > 4 + 4 && j < 14 + 4 && grid_[i - 5][j + 5] == cur)
                    continue;
                else if (i < 18 + 4 && j > 0 + 4 && grid_[i + 1][j - 1] == cur)
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
    // ������ 33�� ����

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (x_ + 4 + mx[i][j] < 0 || x_ + 4 + mx[i][j] > 18) // ������ ������ �ȵ�
                over = 1;
        }
        if (over == 0)
        {
            if (grid_[x_ + 4 + mx[i][0]][y_ + 4 + my[i][0]] == 0 && grid_[x_ + 4 + mx[i][3]][y_ + 4 + my[i][3]] == 0) // �� ���� ����ְ�
            {
                if (grid_[x_ + 4 + mx[i][1]][y_ + 4 + my[i][1]] == color_ && grid_[x_ + 4 + mx[i][2]][y_ + 4 + my[i][2]] == color_) // �߰��� ���� ���� �� �� ���
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

int Grid::alpha_beta_search(int AI, int color, int depth)
{
    color_ = color;
    int v = -INF, a = -INF, b = INF;
    int action_x = -1, action_y = -1;
    int temp_value, save_color;
    bool can_put;
    for (int i = 0 + 4; i < 19 + 4; i++)
    {
        for (int j = 0 + 4; j < 19 + 4; j++)
        {
            save_color = color_;
            can_put = result(i, j); // ���� �� �ִ� �� Ȯ��, ���� �� �ִٸ� ���´�.
            if (!can_put)
                continue;
            temp_value = min_value(AI, a, b, depth - 1);
            grid_[i][j] = 0; // ������� ���� ���� ġ��
            color_ = save_color;
            // gotoxy(90, 0);
            // cout << temp_value;
            if (v < temp_value)
            {
                v = temp_value;
                action_x = i - 4;
                action_y = j - 4;

                gotoxy(70, 0);
                cout << "          ";
                gotoxy(70, 0);
                cout << action_x;
                gotoxy(70, 1);
                cout << "          ";
                gotoxy(70, 1);
                cout << action_y;
                Sleep(1000);
            }

            gotoxy(50, 0);
            cout << "          ";
            gotoxy(50, 0);
            cout << v;
            // Sleep(1000);
        }
    }
    return action_x * 19 + action_y;
}
int Grid::max_value(int AI, int a, int b, int depth)
{
    if (depth == 0)
    {
        return eval(AI);
    }
    int temp_value, v = -INF, save_color;
    bool can_put;
    for (int i = 0 + 4; i < 19 + 4; i++)
    {
        for (int j = 0 + 4; j < 19 + 4; j++)
        {
            save_color = color_;
            can_put = result(i, j); // ���� �� �ִ� �� Ȯ��, ���� �� �ִٸ� ���´�.
            if (!can_put)
                continue;
            v = max(v, min_value(AI, a, b, depth - 1));
            grid_[i][j] = 0; // ������� ���� ���� ġ��
            color_ = save_color;
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
int Grid::min_value(int AI, int a, int b, int depth)
{
    if (depth == 0)
    {
        return eval(AI);
    }
    int temp_value, v = INF, save_color;
    bool can_put;
    for (int i = 0 + 4; i < 19 + 4; i++)
    {
        for (int j = 0 + 4; j < 19 + 4; j++)
        {
            save_color = color_;
            can_put = result(i, j); // ���� �� �ִ� �� Ȯ��, ���� �� �ִٸ� ���´�.
            if (!can_put)
                continue;
            v = min(v, max_value(AI, a, b, depth - 1));
            grid_[i][j] = 0; // ������� ���� ���� ġ��
            color_ = save_color;
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

int Grid::eval(int AI)
{
    int score[10] = {
        1,         // �ֺ��� 1���� ������ (2�� �̻��� 0��)
        20,        // �ֺ��� ������ �ո� �� or ������ ���� ���ӵ� ���� or 6��
        60,        // �� ���� ���� 2���� �پ��ִ� ���
        1'000,     // ������ �ո� 2��
        10'000,    // ������ ���� 3��
        150'000,   // ������ �ո� 3��
        250'000,   // ������ ���� 4��
        1'000'000, // ������ �ո� 4��
        3'000'000, // 5��
    };
    int total_score = 0, cur, conti = 0, adj = 0;
    float sign;
    int mx[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; // ���ʺ��� �ð��������
    int my[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    int adj_x, adj_y;
    for (int j = 0 + 4; j < 19 + 4; j++)
    {
        for (int i = 0 + 4; i < 19 + 4; i++)
        {
            cur = grid_[i][j];
            if (cur == 0) // ���� ������ 0��
                continue;
            if (cur == 1)
                sign = -1;
            if (cur == 2)
                sign = 0.9;
            for (int k = 0; k < 4; k++) // �츮�� ������, �Ʒ�, �����ʾƷ�, �������� �������� ���� �� �鸸 �����ν� �ߺ��� ����
            {
                adj_x = i + mx[k];
                adj_y = j + my[k];
                if (grid_[adj_x][adj_y] == cur)
                {
                    conti = 1;
                    break;
                }
            }
            if (conti == 1)
            {
                conti = 0;
                continue;
            }

            for (int k = 0; k < 8; k++) // ���� 1�� �� �� (�ֺ��� �����ִ� 1���� ���� �з�)
            {
                adj_x = i + mx[k];
                adj_y = j + my[k];
                if (grid_[adj_x][adj_y] == cur)
                {
                    conti = 1;
                    break;
                }
                else if (grid_[adj_x][adj_y] != 0) // ����� ���� �ְų� ���������� adj�� �÷��ش�.
                {
                    adj++;
                }
            }
            if (conti == 0)
            {
                if (adj >= 2)
                {
                    conti = 0;
                    adj = 0;
                    continue;
                }
                else if (adj == 1)
                {
                    conti = 0;
                    adj = 0;
                    total_score += int(score[0] * sign);
                    continue;
                }
                else
                {
                    conti = 0;
                    adj = 0;
                    total_score += int(score[1] * sign);
                    continue;
                }
            }
            conti = 0;
            adj = 0;

            for (int k = 4; k < 8; k++) // ���� 2���� ��
            {
                if (grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] != cur) // �� ���� �پ��ֵ� �� ���� �ȵ�
                {
                    if (grid_[i + 2 * mx[k]][j + 2 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[3] * sign);
                        conti = 1;
                        continue;
                    }
                    else if (grid_[i + 2 * mx[k]][j + 2 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[2] * sign);
                        conti = 1;
                        continue;
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[1] * sign);
                        conti = 1;
                        continue;
                    }
                }
            }
            if (conti == 1)
            {
                conti = 0;
                continue;
            }
            conti = 0;

            for (int k = 4; k < 8; k++) // ���� 3���� ��
            {
                if (grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] != cur)
                {
                    if (grid_[i + 3 * mx[k]][j + 3 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[5] * sign);
                        conti = 1;
                        continue;
                    }
                    else if (grid_[i + 3 * mx[k]][j + 3 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[4] * sign);
                        conti = 1;
                        continue;
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[1] * sign);
                        conti = 1;
                        continue;
                    }
                }
            }
            if (conti == 1)
            {
                conti = 0;
                continue;
            }
            conti = 0;

            for (int k = 4; k < 8; k++) // ���� 4���� ��
            {
                if (grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] == cur && grid_[i + 4 * mx[k]][j + 4 * my[k]] != cur)
                {
                    if (grid_[i + 4 * mx[k]][j + 4 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[7] * sign);
                        conti = 1;
                        continue;
                    }
                    else if (grid_[i + 4 * mx[k]][j + 4 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[6] * sign);
                        conti = 1;
                        continue;
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[1] * sign);
                        conti = 1;
                        continue;
                    }
                }
            }
            if (conti == 1)
            {
                conti = 0;
                continue;
            }
            conti = 0;

            for (int k = 4; k < 8; k++) // ���� 5���� ��
            {
                if (grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] == cur && grid_[i + 4 * mx[k]][j + 4 * my[k]] == cur && grid_[i + 5 * mx[k]][j + 5 * my[k]] != cur)
                {
                    if (grid_[i + 5 * mx[k]][j + 5 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[8] * sign);
                        conti = 1;
                        continue;
                    }
                    else if (grid_[i + 5 * mx[k]][j + 5 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[8] * sign);
                        conti = 1;
                        continue;
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[8] * sign);
                        conti = 1;
                        continue;
                    }
                }
                else if (grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] == cur && grid_[i + 4 * mx[k]][j + 4 * my[k]] == cur && grid_[i + 5 * mx[k]][j + 5 * my[k]] == cur)
                {
                    total_score += int(score[1] * sign);
                    conti = 1;
                    continue;
                }
            }
            if (conti == 1)
            {
                conti = 0;
                continue;
            }
            conti = 0;
            adj = 0;
            gotoxy(90, 5);
            cout << "�帣�°� �ִ�" << endl;
        }
    }

    if (AI == 1)
        total_score = total_score * (-1);
    return total_score;
}

void Grid::showGrid()
{
    for (int i = 0 + 4; i < 19 + 4; i++)
    {
        gotoxy(50, i + 5);
        for (int j = 0 + 4; j < 19 + 4; j++)
        {
            printf("%d ", grid_[i][j]);
        }
    }
}

void init_grid()
{
    int i, j;
    for (i = 0; i < 19; i++)
    {
        cout << "��������������������" << endl;
    }
    for (i = 0; i < 19; i++)
    {
        gotoxy(i * 2, 20);
        cout << i;
        gotoxy(40, i);
        cout << i;
    }
}
int main()
{
    int color = 1, win = 0, AI = 1;
    int action, action_x, action_y, depth = 3;
    Grid Omok;

    init_grid();

    while (1)
    {
        if (color == AI)
        {
            action = Omok.alpha_beta_search(AI, color, depth);
            action_x = action / 19;
            action_y = action % 19;
            Omok.set_stone(color, true, action_x, action_y);
            gotoxy(50, 2);
            cout << Omok.eval(AI);
            Omok.showGrid();
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
            cout << "Player " << win << " �¸�!!!" << endl;
            break;
        }
        color = 3 - color;
    }

    gotoxy(0, 25);
    system("pause");
    return 0;
}