#pragma once
class Cell
{
private:
	int row, col;
	int target_row, target_col;
	Cell* parent;
	double f, g, h;
//	double 
public:
	Cell();
	Cell(int r, int c, Cell* p) : row(r), col(c), target_row(0), target_col(0), parent(p), f(0.0), g(0.0), h(0.0) { }
	Cell(int r, int c,int tr,int tc, double newg,Cell* p);
	int getRow() { return row; }
	int getCol() { return col; }
	Cell* getParent() { return parent; }
	void ComputeH();

	double distance();
	double getF() { return f; }
	double getH() { return h; }
	double getG() { return g; }
	int getTargetRow() { return target_row; }
	int getTargetCol() { return target_col; }

	bool operator == (const Cell& other) { return row == other.row && col == other.col; }

};

