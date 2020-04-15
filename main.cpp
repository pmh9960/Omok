#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

#define INF 999'999'999 // int �������� ū ��
#define LIMIT_TIME 10
// ��
// ��
// ��

void init_grid();
void gotoxy(short int x, short int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Grid
{
private:
    int x_, y_;
    int color_;
    int attack_;
    int grid_[30][30];

public:
    Grid()
    {
        x_ = 0;
        y_ = 0;
        attack_ = 0;
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 30; j++)
                grid_[i][j] = 9;
        for (int i = 0 + 4; i < 19 + 4; i++)
            for (int j = 0 + 4; j < 19 + 4; j++)
                grid_[i][j] = 0;
    }
    void set_stone(int color, bool isAI, int x, int y, clock_t start_time = 0);
    int check_winner();
    int eval(int AI, bool test = false);
    int alpha_beta_search(int AI, int color, int depth, clock_t start_time);
    int max_value(int AI, int a, int b, int depth, clock_t start_time);
    int min_value(int AI, int a, int b, int depth, clock_t start_time);
    bool result(int x, int y);
    void remove(int x, int y);
    bool rule33();
    // bool rule6();
    void showGrid();
    int cost_, time_over_ = 0;
};

void Grid::set_stone(int color, bool isAI, int x, int y, clock_t start_time)
{
    if (!isAI)
    {
        color_ = color;
        gotoxy(0, 22);
        std::cout << "Player " << color_ << " ��ġ�� �Է��Ͻʽÿ�" << std::endl;
        cin >> x_ >> y_;
        gotoxy(0, 23);
        std::cout << "                 " << std::endl;
        std::cout << "                 " << std::endl;
        if ((float)(clock() - start_time) / CLOCKS_PER_SEC > LIMIT_TIME)
        {
            gotoxy(0, 22);
            cout << "TIME OVER!!! Player " << 3 - color_ << " �¸�!!!                   " << endl;
            time_over_ = 1;
            return;
        }
    }
    else
    {
        color_ = color;
        x_ = x;
        y_ = y;
    }

    if (x_ > 18 || x_ < 0 || y_ > 18 || y_ < 0)
    {
        set_stone(color_, isAI, x_, y_);
    }
    else if (grid_[x_ + 4][y_ + 4] == 0 && rule33())
    {
        grid_[x_ + 4][y_ + 4] = color_;
        gotoxy(x_ * 2, y_);
        if (color_ == 1)
        {
            std::cout << "��";
        }
        else
        {
            std::cout << "��";
        }
    }
    else
    {
        set_stone(color_, isAI, x_, y_, start_time);
    }
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
            if (x_ + 4 + mx[i][j] < 0 + 4 || x_ + 4 + mx[i][j] > 18 + 4) // ������ ������ �ȵ�
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

int Grid::alpha_beta_search(int AI, int color, int depth, clock_t start_time)
{
    color_ = color;
    int v = -INF, a = -INF, b = INF;
    int action_x = -1, action_y = -1;
    int temp_value, save_color;
    bool can_put;
    int i = 9 + 4, j = 9 + 4, dir = 0, len = 0, i_next, j_next;
    int mx[4] = {1, 0, -1, 0}, my[4] = {0, -1, 0, 1};
    int cur_score;
    cur_score = eval(AI);
    if (cur_score < -100'000)
    {
        if (AI == 1)
        {
            attack_ = 2;
        }
        else
        {
            attack_ = 1;
        }
    }
    else if (cur_score > 100'000)
    {
        if (AI == 1)
        {
            attack_ = 1;
        }
        else
        {
            attack_ = 2;
        }
    }
    else
    {
        attack_ = 0;
    }

    while (dir < 38)
    {
        i_next = i + len * mx[dir % 4];
        j_next = j + len * my[dir % 4];
        int cnt = 0;

        while (cnt < len)
        {
            save_color = color_;
            can_put = result(i, j); // ���� �� �ִ� �� Ȯ��, ���� �� �ִٸ� ���´�.
            if (!can_put)
            {
                i += mx[dir % 4];
                j += my[dir % 4];
                cnt++;
                continue;
            }
            temp_value = min_value(AI, a, b, depth - 1, start_time);
            grid_[i][j] = 0; // ������� ���� ���� ġ��
            color_ = save_color;
            // gotoxy(90, 0);
            // std::cout << temp_value;
            if (v < temp_value)
            {
                v = temp_value;
                action_x = i - 4;
                action_y = j - 4;
            }

            gotoxy(50, 20);
            printf("Depth %d ������ ...  %.2f %%         ", depth, (float(dir) / 37) * 100);
            i += mx[dir % 4];
            j += my[dir % 4];
            cnt++;
            if ((float)(clock() - start_time) / CLOCKS_PER_SEC > LIMIT_TIME) // iterative deepening search
            {
                break;
            }
        }
        if ((float)(clock() - start_time) / CLOCKS_PER_SEC > LIMIT_TIME) // iterative deepening search
        {
            break;
        }

        i = i_next;
        j = j_next;
        if (dir % 2 == 0)
        {
            len++;
        }
        dir++;
    }

    cost_ = v;
    return action_x * 19 + action_y;
}
int Grid::max_value(int AI, int a, int b, int depth, clock_t start_time)
{
    int score = eval(AI);
    if (score > 200'000'000 || score < -200'000'000)
    {
        return score;
    }
    if (depth == 0)
    {
        return score;
    }
    int temp_value, v = -INF, save_color;
    bool can_put;
    int i = 9 + 4, j = 9 + 4, dir = 0, len = 0, i_next, j_next;
    int mx[4] = {1, 0, -1, 0}, my[4] = {0, -1, 0, 1};
    while (dir < 38)
    {
        i_next = i + len * mx[dir % 4];
        j_next = j + len * my[dir % 4];
        int cnt = 0;

        while (cnt < len)
        {
            save_color = color_;
            can_put = result(i, j); // ���� �� �ִ� �� Ȯ��, ���� �� �ִٸ� ���´�.
            if (!can_put)
            {
                i += mx[dir % 4];
                j += my[dir % 4];
                cnt++;
                continue;
            }
            v = max(v, min_value(AI, a, b, depth - 1, start_time));
            grid_[i][j] = 0; // ������� ���� ���� ġ��
            color_ = save_color;
            if (v >= b)
                return v;
            a = max(a, v);

            // gotoxy(50, 0);
            // std::cout << v;
            // gotoxy(50, 1);
            // std::cout << a;
            // gotoxy(50, 2);
            // std::cout << b;
            // Sleep(1000);

            i += mx[dir % 4];
            j += my[dir % 4];
            cnt++;
        }
        i = i_next;
        j = j_next;
        if (dir % 2 == 0)
        {
            len++;
        }
        dir++;
        if ((float)(clock() - start_time) / CLOCKS_PER_SEC > LIMIT_TIME) // iterative deepening search
        {
            break;
        }
    }
    return v;
}
int Grid::min_value(int AI, int a, int b, int depth, clock_t start_time)
{
    int score = eval(AI);
    if (score > 200'000'000 || score < -200'000'000)
    {
        return score;
    }
    if (depth == 0)
    {
        return score;
    }
    int temp_value, v = INF, save_color;
    bool can_put;
    int i = 9 + 4, j = 9 + 4, dir = 0, len = 0, i_next, j_next;
    int mx[4] = {1, 0, -1, 0}, my[4] = {0, -1, 0, 1};
    while (dir < 38)
    {
        i_next = i + len * mx[dir % 4];
        j_next = j + len * my[dir % 4];
        int cnt = 0;

        while (cnt < len)
        {
            save_color = color_;
            can_put = result(i, j); // ���� �� �ִ� �� Ȯ��, ���� �� �ִٸ� ���´�.
            if (!can_put)
            {
                i += mx[dir % 4];
                j += my[dir % 4];
                cnt++;
                continue;
            }
            v = min(v, max_value(AI, a, b, depth - 1, start_time));
            grid_[i][j] = 0; // ������� ���� ���� ġ��
            color_ = save_color;
            if (v <= a)
                return v;
            b = min(b, v);

            // gotoxy(50, 0);
            // std::cout << v;
            // gotoxy(50, 1);
            // std::cout << a;
            // gotoxy(50, 2);
            // std::cout << b;
            // Sleep(1000);

            i += mx[dir % 4];
            j += my[dir % 4];
            cnt++;
        }
        i = i_next;
        j = j_next;
        if (dir % 2 == 0)
        {
            len++;
        }
        dir++;
        if ((float)(clock() - start_time) / CLOCKS_PER_SEC > LIMIT_TIME) // iterative deepening search
        {
            break;
        }
    }
    return v;
}

bool Grid::result(int x, int y)
{
    x_ = x - 4;
    y_ = y - 4;
    if (grid_[x][y] == 0 && rule33())
    {
        grid_[x][y] = color_;
        color_ = 3 - color_;
        return true;
    }
    return false;
}

int Grid::eval(int AI, bool test)
{
    int score[11] = {
        1,          // 0 �ֺ��� 1���� ������ (2�� �̻��� 0��)
        10,         // 1 �ֺ��� ������ �ո� ��
        100,        // 2 �� ���� ���� 2���� �پ��ִ� ���
        1'000,      // 3 ������ �ո� 2�� or ������ ���� ���� or 6��
        15'000,     // 4 ������ ���� 3��
        400'000,    // 5 010110 or 011010
        500'000,    // 6 ������ �ո� 3��
        5'000'000,  // 7 0110110
        10'000'000, // 8 ������ ���� 4��
        50'000'000, // 9 ������ �ո� 4��
        INF,        // 10 5��
    };
    int total_score = 0, cur, conti = 0, adj = 0, count = 0;
    float sign;
    int mx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    int my[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; // ���ʺ��� �ð��������
    int adj_x, adj_y;
    for (int j = 0 + 4; j < 19 + 4; j++)
    {
        for (int i = 0 + 4; i < 19 + 4; i++)
        {
            cur = grid_[i][j];
            if (cur == 0) // ���� ������ 0��
                continue;
            else if (attack_ == 0) // ������ ����
                sign = 1;
            else if (cur == attack_)
                sign = 1;
            else
                sign = 0.1;

            if (cur == AI)
                sign *= 1;
            else
                sign *= -1;

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
                    if (test)
                    {
                        count++;
                        gotoxy(50, 2 + count);
                        cout << "�� 1�� �ֺ� �ѷ� ���� : " << i - 4 << ", " << j - 4 << "               ";
                    }
                }
                else if (adj == 1)
                {
                    conti = 0;
                    adj = 0;
                    total_score += int(score[0] * sign);
                    if (test)
                    {
                        count++;
                        gotoxy(50, 2 + count);
                        cout << "�� 1�� �ֺ� �� 1�� : " << i - 4 << ", " << j - 4 << "               ";
                    }
                }
                else
                {
                    conti = 0;
                    adj = 0;
                    total_score += int(score[1] * sign);
                    if (test)
                    {
                        count++;
                        gotoxy(50, 2 + count);
                        cout << "�� 1�� �ֺ� �� ���� : " << i - 4 << ", " << j - 4 << "               ";
                    }
                }
            }
            conti = 0;
            adj = 0;

            for (int k = 4; k < 8; k++) // ���� 2���� ��
            {
                if (grid_[i - mx[k]][j - my[k]] != cur && grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] != cur) // �� ���� �پ��ֵ� �� ���� �ȵ�
                {
                    if (grid_[i + 2 * mx[k]][j + 2 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[3] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 2�� ��� : " << i - 4 << ", " << j - 4 << " => " << mx[k] << ", " << my[k] << "               ";
                        }
                    }
                    else if (grid_[i + 2 * mx[k]][j + 2 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[2] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 2�� �Ѷ� : " << i - 4 << ", " << j - 4 << " => " << mx[k] << ", " << my[k] << "               ";
                        }
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[1] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 2�� �縷 : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                }
            }
            conti = 0;

            for (int k = 4; k < 8; k++) // ���� 3���� ��
            {
                if (grid_[i - mx[k]][j - my[k]] != cur && grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] != cur)
                {
                    if (grid_[i + 3 * mx[k]][j + 3 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[6] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 3�� ��� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else if (grid_[i + 3 * mx[k]][j + 3 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[4] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 3�� �Ѷ� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[3] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 3�� �縷 : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                }
            }
            conti = 0;

            for (int k = 4; k < 8; k++) // ���� 4���� �� or ���� �ϳ�
            {
                if (grid_[i - mx[k]][j - my[k]] != cur && grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] == cur && grid_[i + 4 * mx[k]][j + 4 * my[k]] != cur)
                {
                    if (grid_[i + 4 * mx[k]][j + 4 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[9] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 4�� ��� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else if (grid_[i + 4 * mx[k]][j + 4 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[8] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 4�� �Ѷ� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[3] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 4�� �縷 : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                }
                else if (grid_[i - mx[k]][j - my[k]] != cur && grid_[i + mx[k]][j + my[k]] == 0 && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] == cur && grid_[i + 4 * mx[k]][j + 4 * my[k]] != cur) // 1011
                {
                    if (grid_[i + 4 * mx[k]][j + 4 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[5] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "1011 ��� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else if (grid_[i + 4 * mx[k]][j + 4 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[4] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "1011 �Ѷ� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[3] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "1011 �縷 : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                }
                else if (grid_[i - mx[k]][j - my[k]] != cur && grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == 0 && grid_[i + 3 * mx[k]][j + 3 * my[k]] == cur && grid_[i + 4 * mx[k]][j + 4 * my[k]] != cur)
                {
                    if (grid_[i + 4 * mx[k]][j + 4 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score += int(score[5] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "1101 ��� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else if (grid_[i + 4 * mx[k]][j + 4 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score += int(score[4] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "1101 �Ѷ� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else // ������ ���� ���
                    {
                        total_score += int(score[3] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "1101 �縷 : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                }
            }
            conti = 0;

            for (int k = 4; k < 8; k++) // ���� 5���� ��
            {
                if (grid_[i - mx[k]][j - my[k]] != cur && grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] == cur && grid_[i + 4 * mx[k]][j + 4 * my[k]] == cur && grid_[i + 5 * mx[k]][j + 5 * my[k]] != cur)
                {
                    if (grid_[i + 5 * mx[k]][j + 5 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score = int(score[10] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 5�� ��� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else if (grid_[i + 5 * mx[k]][j + 5 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score = int(score[10] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 5�� �Ѷ� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else // ������ ���� ���
                    {
                        total_score = int(score[10] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "�� 5�� �縷 : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                }
                else if (grid_[i - mx[k]][j - my[k]] != cur && grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] == 0 && grid_[i + 4 * mx[k]][j + 4 * my[k]] == cur && grid_[i + 5 * mx[k]][j + 5 * my[k]] != cur)
                {
                    if (grid_[i + 5 * mx[k]][j + 5 * my[k]] == 0 && grid_[i - mx[k]][j - my[k]] == 0) // ������ �� �շ��ִ� ���
                    {
                        total_score = int(score[7] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "11011 ��� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else if (grid_[i + 5 * mx[k]][j + 5 * my[k]] == 0 || grid_[i - mx[k]][j - my[k]] == 0) // ���� �� �շ��ִ� ���
                    {
                        total_score = int(score[7] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "11011 �Ѷ� : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                    else // ������ ���� ���
                    {
                        total_score = int(score[7] * sign);
                        conti = 1;
                        if (test)
                        {
                            count++;
                            gotoxy(50, 2 + count);
                            cout << "11011 �縷 : " << i - 4 << ", " << j - 4 << "               ";
                        }
                    }
                }
                else if (grid_[i + mx[k]][j + my[k]] == cur && grid_[i + 2 * mx[k]][j + 2 * my[k]] == cur && grid_[i + 3 * mx[k]][j + 3 * my[k]] == cur && grid_[i + 4 * mx[k]][j + 4 * my[k]] == cur && grid_[i + 5 * mx[k]][j + 5 * my[k]] == cur)
                {
                    total_score += int(score[3] * sign);
                    conti = 1;
                    if (test)
                    {
                        count++;
                        gotoxy(50, 2 + count);
                        cout << "�� 6�� �̻� : " << i - 4 << ", " << j - 4 << "               ";
                    }
                    continue;
                }
            }
            conti = 0;
            adj = 0;
            // gotoxy(90, 5);
            // std::cout << "�帣�°� �ִ�" << std::endl;
        }
    }

    return total_score;
}

void Grid::showGrid()
{
    for (int i = 0 + 4; i < 19 + 4; i++)
    {
        gotoxy(50, i + 5);
        for (int j = 0 + 4; j < 19 + 4; j++)
        {
            printf("%d ", grid_[j][i]);
        }
    }
}

void init_grid()
{
    int i, j;
    for (i = 0; i < 19; i++)
    {
        std::cout << "��������������������" << std::endl;
    }
    for (i = 0; i < 19; i++)
    {
        gotoxy(i * 2, 20);
        std::cout << i;
        gotoxy(40, i);
        std::cout << i;
    }
}
int main()
{
    int color = 1, win = 0, AI = 1, cur_cost, cost1 = -INF, cost2 = INF;
    int temp_action, temp_cost, action, action_x, action_y, depth;
    int num_p, re = 1;
    clock_t start = clock();
    Grid Omok = Grid();

    init_grid();
    while (re == 1)
    {
        gotoxy(0, 22);
        cout << "0P or 1P or 2P?" << endl;
        cin >> num_p;

        switch (num_p)
        {
        case 0:
            AI = 1;
            re = 0;
            break;

        case 1:
            gotoxy(0, 23);
            cout << "                                " << endl
                 << "                                " << endl
                 << "                                " << endl;
            gotoxy(0, 22);
            cout << "Do First(0) or not(1)?" << endl;
            cin >> AI;
            AI = 2 - AI;
            re = 0;
            break;

        case 2:
            AI = 0;
            re = 0;
            break;

        default:
            break;
        }

        gotoxy(0, 23);
        cout << "                                " << endl
             << "                                " << endl
             << "                                " << endl;
    }

    while (1)
    {
        switch (num_p)
        {
        case 0:
            // AI vs AI
            depth = 0;
            start = clock();
            cost1 = -INF;
            cost2 = INF;
            while ((float)(clock() - start) / CLOCKS_PER_SEC < LIMIT_TIME)
            {
                depth += 1;
                temp_action = Omok.alpha_beta_search(AI, color, depth, start);
                temp_cost = Omok.cost_;
                if ((float)(clock() - start) / CLOCKS_PER_SEC > LIMIT_TIME)
                    break;
                if (color == 1)
                {
                    if (temp_cost > cost1)
                    {
                        action = temp_action;
                        cost1 = temp_cost;
                    }
                }
                else
                {
                    if (temp_cost < cost2)
                    {
                        action = temp_action;
                        cost2 = temp_cost;
                    }
                }
            }
            action_x = action / 19;
            action_y = action % 19;
            Omok.set_stone(color, true, action_x, action_y);
            AI = 3 - AI;
            break;

        case 1:
            // AI vs Human
            if (color == AI)
            {
                depth = 0;
                start = clock();
                cost1 = -INF;
                cost2 = INF;
                while ((float)(clock() - start) / CLOCKS_PER_SEC < LIMIT_TIME)
                {
                    depth += 1;
                    temp_action = Omok.alpha_beta_search(AI, color, depth, start);
                    temp_cost = Omok.cost_;
                    if ((float)(clock() - start) / CLOCKS_PER_SEC > LIMIT_TIME)
                        break;
                    if (color == 1)
                    {
                        if (temp_cost > cost1)
                        {
                            action = temp_action;
                            cost1 = temp_cost;
                        }
                    }
                    else
                    {
                        if (temp_cost < cost2)
                        {
                            action = temp_action;
                            cost2 = temp_cost;
                        }
                    }
                }
                action_x = action / 19;
                action_y = action % 19;
                Omok.set_stone(color, true, action_x, action_y);
            }
            else
            {
                start = clock();
                Omok.set_stone(color, false, 0, 0, start);
            }
            break;

        case 2:
            // Human vs Human
            start = clock();
            Omok.set_stone(color, false, 0, 0, start);
            break;

        default:
            break;
        }

        if (Omok.time_over_ == 1)
        {
            break;
        }

        win = Omok.check_winner();
        if (win != 0)
        {
            gotoxy(0, 22);
            std::cout << "                                             " << std::endl;
            std::cout << "                                             " << std::endl;
            std::cout << "                                             " << std::endl;
            gotoxy(0, 22);
            std::cout << "Player " << color << " �¸�!!!" << std::endl;
            break;
        }

        color = 3 - color;
    }

    gotoxy(0, 25);
    system("pause");
    return 0;
}