
class CharMatrix {
    int rows, cols;
    public:
    char** matrixptr;
    CharMatrix(int _rows,int _cols);
    int getRows();
    int getCols();
    char& operator() (int r, int c) { return matrixptr[r][c]; };
};