#ifndef TAG_H
#define TAG_H


class tag {
public:
    tag();
    int getItem(int x, int y) const;
    int getStep() const;
    void startGame();
    bool isFinished();
    void restartGame();
    void reCalc(int x, int y);

private:
    int table[4][4];
    int cpyTable[4][4];
    int step;
};

#endif // TAG_H
