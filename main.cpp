#include <iostream>
#include "gotoxy.cpp"
using namespace std;

// ��
// ��
// ��

void init_grid();

class Grid
{
private:
    int x_, y_;
    int color_;
    int grid_[20][20];

public:
    Grid()
    {
        x_ = 0;
        y_ = 0;
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 20; j++)
                grid_[i][j] = 0;
    }
    void set_stone(int color);
    int check_winner();
    int eval();
    int alpha_beta_search(int depth);
    bool rule33();
    bool rule6();
};

void Grid::set_stone(int color)
{
    color_ = color;
    gotoxy(0, 22);
    cout << "Player " << color_ << " ��ġ�� �Է��Ͻʽÿ�" << endl;
    cin >> x_ >> y_;
    gotoxy(0, 23);
    cout << "                 " << endl;
    cout << "                 " << endl;

    if (grid_[x_][y_] == 0 && x_ < 19 && y_ < 19 && rule33()) // rule �߰� �ؾ��� 33
    {
        grid_[x_][y_] = color_;
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
        set_stone(color_);
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
    // ������ 33�� ����

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (x_ + mx[i][j] < 0 || x_ + mx[i][j] > 18) // ������ ������ �ȵ�
                over = 1;
        }
        if (over == 0)
        {
            if (grid_[x_ + mx[i][0]][y_ + my[i][0]] == 0 && grid_[x_ + mx[i][3]][y_ + my[i][3]] == 0) // �� ���� ����ְ�
            {
                if (grid_[x_ + mx[i][1]][y_ + my[i][1]] == color_ && grid_[x_ + mx[i][2]][y_ + my[i][2]] == color_) // �߰��� ���� ���� �� �� ���
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

bool Grid::rule6()
{
}

int main()
{
    int color = 1;
    int win = 0;
    Grid Omok;

    init_grid();

    while (1)
    {
        Omok.set_stone(color);
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