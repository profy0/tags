#include "tag.h"
#include <QRandomGenerator>
#include <QDebug>

tag::tag() {
    startGame();
}

int tag::getItem(int x, int y) const {
    return table[x][y];
}

void tag::startGame() {
    QRandomGenerator *rnd = QRandomGenerator::global();

    std::pair <int, int> step[4] = { {0,1},{1,0},{0,-1},{-1,0} };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            table[i][j] = i*4+j;
        }
    }

    this->step = 0;

    do {
        int val = rnd->bounded(100, 300);
        int x = 3, y = 3;

        std::vector <std::pair<int, int> > possible;

        while (val--) {
            int random = rnd->bounded(0, 3);
            for (int i = 0; i < 8; i++) {
                if (i < random) continue;
                int new_x = x + step[i % 4].first;
                int new_y = y + step[i % 4].second;
                if (new_x >= 0 && new_x <= 3 && new_y >= 0 && new_y <= 3) {
                    std::swap(table[x][y], table[new_x][new_y]);
                    x += step[i % 4].first;
                    y += step[i % 4].second;
                    break;
                }
            }
        }

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                cpyTable[i][j] = table[i][j];
            }
        }

    } while(isFinished());


}

int tag::getStep() const {
    return step;
}

bool tag::isFinished() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(table[i][j]!=i*4+j) return 0;
        }
    }
    return 1;
}

void tag::restartGame() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            table[i][j] = cpyTable[i][j];
        }
    }
}

void tag::reCalc(int x, int y) {
    if(table[x][y]==15) return;
    std::pair <int, int> step[4] = { {0,1},{1,0},{0,-1},{-1,0} };
    for(int i=0;i<4;i++) {
        int new_x = x + step[i].first;
        int new_y = y + step[i].second;
        if (new_x >= 0 && new_x <= 3 && new_y >= 0 && new_y <= 3) {
            if(table[new_x][new_y]==15) {
                this->step++;
                std::swap(table[x][y], table[new_x][new_y]);
                break;
            }
        }
    }
}
