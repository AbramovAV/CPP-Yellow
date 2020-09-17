#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix
class Matrix
{
private:
    vector<vector<int>> mat;
public:
    Matrix(){
        mat.clear();
    };

    Matrix(int num_rows,int num_cols){
        if(num_rows<0 || num_cols<0) throw out_of_range("Out of matrix range");
        for(int i=0;i<num_rows;++i){
            mat.push_back(vector<int>(num_cols,0));
        }
        if(num_cols==0) mat.clear();
    }

    void Reset(int num_rows,int num_cols){
        if(num_rows<0 || num_cols<0) throw out_of_range("");
        mat.clear();
        for(int i=0;i<num_rows;++i){
            mat.push_back(vector<int>(num_cols,0));
        }
    }

    int At(int row,int col) const{
        if(row<0 || col<0 || row>=GetNumRows() || col>=GetNumColumns()) throw out_of_range("Out of matrix range");
        return mat[row][col];
    }
    
    int& At(int row,int col){
        if(row<0 || col<0 || row>=GetNumRows() || col>=GetNumColumns()) throw out_of_range("Out of matrix range");
        return mat[row][col];
    }

    int GetNumRows() const{
        return mat.size();
    }

    int GetNumColumns() const{
        if(mat.size()>0) return mat[0].size();
        else return 0;
    }
};

istream& operator>>(istream& in_stream,Matrix& mat){
    int rows,cols;
    in_stream>>rows>>cols;
    mat = Matrix(rows,cols);
    for(int i=0;i<rows;++i){
        for(int j=0;j<cols;++j){
            in_stream>>mat.At(i,j);
        }
    }
    return in_stream;
}

ostream& operator<<(ostream& out_stream,const Matrix& mat){
    out_stream<<mat.GetNumRows()<<" "<<mat.GetNumColumns()<<endl;
    for(int i=0;i<mat.GetNumRows();++i){
        for(int j=0;j<mat.GetNumColumns();++j){
            out_stream<<mat.At(i,j);
            if(j<mat.GetNumColumns()-1) out_stream<<" ";
        }
        if(i<mat.GetNumRows()-1) out_stream<<endl;
    }
    return out_stream;
}

bool operator==(const Matrix& first,const Matrix& second){
    if(first.GetNumRows()==second.GetNumRows() && first.GetNumColumns()==second.GetNumColumns()){
        for(int i=0;i<first.GetNumRows();++i){
            for(int j=0;j<first.GetNumColumns();++j){
                if(first.At(i,j)!=second.At(i,j)) return false;
            }
        }
        return true;
    }
    return false;
}


Matrix operator+(const Matrix& first, const Matrix& second){
    if(first.GetNumRows()==second.GetNumRows() && first.GetNumColumns()==second.GetNumColumns()){
        int rows = first.GetNumRows();
        int cols = first.GetNumColumns();
        Matrix result(rows,cols);
        for(int i=0;i<first.GetNumRows();++i){
            for(int j=0;j<first.GetNumColumns();++j){
                result.At(i,j) = first.At(i,j)+second.At(i,j);
            }
        }
        return result;
    }else throw invalid_argument("Matrices have different dimensions.");
}