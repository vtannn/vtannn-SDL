#ifndef LOGIC_H
#define LOGIC_H
#define BOARDSIZE 3
#define EMPTY_CELL 'T'
#define O_CELL 'o'
#define X_CELL 'x'
struct Tictactoe
{
    char board[BOARDSIZE][BOARDSIZE];
    char nextmove=O_CELL;
    void init()
    {
        for(int i=0;i<BOARDSIZE;i++)
        for(int j=0;j<BOARDSIZE;j++)
        board[i][j]=EMPTY_CELL;
    }
    void move(int row,int col)
    {
        if(row>=0&&col>=0&&row<BOARDSIZE&&col<BOARDSIZE)
        {
            if(board[col][row]==EMPTY_CELL)
            {
                board[col][row]=nextmove;
                nextmove=(nextmove==O_CELL) ? X_CELL : O_CELL;
            }
        }
    }
    int check()
    {
        char x;int d=0;
        for(int i=0;i<BOARDSIZE;i++)
        {
            d=1;
            for(int j=1;j<BOARDSIZE;j++)
            {
                if(board[i][j]==board[i][j-1]&&board[i][j]!=EMPTY_CELL) d++;
                else d=1;
                if(d==3)
                {
                    if(board[i][j]==O_CELL) return 1;
                    else return 2;
                }
            }
        }

        for(int j=0;j<BOARDSIZE;j++)
        {
            d=1;
            for(int i=1;i<BOARDSIZE;i++)
            {
                if(board[i-1][j]==board[i][j]&&board[i][j]!=EMPTY_CELL) d++;
                else d=1;
                if(d==3)
                {
                    if(board[i][j]==O_CELL) return 1;
                    else return 2;
                }
            }
        }
        return 0;
    }
};
#endif // LOGIC_H
