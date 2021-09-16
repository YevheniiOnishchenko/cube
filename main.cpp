#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <cmath>


using namespace std;

struct dot{
    float x;
    float y;
    float z;
};

struct coordinates{
    int x;
    int y;
};
struct line{
    dot d1;
    dot d2;
};



coordinates dot_to_coord(dot d){
    coordinates c;
    c.x=round(d.x);
    c.y=round(d.y);
    return c;
}

class Field{
private:
    int height=30;
    int width=100;
    char display[30][100];

public:
    Field(){
        for(int i=0; i<height; i++){
            memset(display[i],' ', width);
        }
    }

    void show(){
        for(int i=0; i<height; i++){
             for(int j=0; j<width; j++){
                 cout << display[i][j];
                 if(j==width-1)cout << endl;
             }
        }
    }

    void draw_point(coordinates c){
        display[c.y+12][c.x+32]=219;
    }
    void del_point(coordinates c){
         display[c.y+12][c.x+12]=' ';
    }
    void draw_line(coordinates c1, coordinates c2){
        coordinates vec;
        float constant=0;
        dot dot_of_line;
        int numb_of_points;
        vec.x=c2.x-c1.x;
        vec.y=c2.y-c1.y;

        if(abs(vec.x)>=abs(vec.y)){
            numb_of_points=abs(vec.x)+10;
        }
        if(abs(vec.y)>abs(vec.x)){
            numb_of_points=abs(vec.y)+10;
        }

        constant=1./(numb_of_points);

        draw_point(c1);
        for(int k=1; k<(numb_of_points); k++){
            dot_of_line.x=(vec.x*constant+c1.x);
            dot_of_line.y=(vec.y*constant+c1.y);
            draw_point(dot_to_coord(dot_of_line));
            constant+=1./(numb_of_points);
        }
        draw_point(c2);
    }

    void del_line(coordinates c1, coordinates c2){
        coordinates vec;
        float constant;
        dot dot_of_line;
        int numb_of_points;
        vec.x=c2.x-c1.x;
        vec.y=c2.y-c1.y;

        if(abs(vec.x)>=abs(vec.y)){
            numb_of_points=abs(vec.x);
        }
        if(abs(vec.y)>abs(vec.x)){
            numb_of_points=abs(vec.y);
        }

        constant=1./(numb_of_points);

        del_point(c1);
        for(int k=1; k<abs(numb_of_points); k++){
            dot_of_line.x=round(vec.x*constant+c1.x);
            dot_of_line.y=round(vec.y*constant+c1.y);
            del_point(dot_to_coord(dot_of_line));
            constant+=1./(numb_of_points);
        }
        del_point(c2);
    }

    void field_clear(){
        for(int i=0; i<height; i++){
             for(int j=0; j<width; j++){
                 display[i][j]=' ';
             }
        }
    }
};

class Matrix{
private:
    float** matr;
    int col;
    int row;
    struct matr_size{
        int col;
        int row;
    };
public:
    Matrix(int c, int r):col(c), row(r){
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(i==j){
                    matr[row][col]=1.f;
                }else{
                    matr[row][col]=0;
                }
            }
        }
    }

    matr_size get_matr_size(float** m){
        matr_size res;
        res.col=sizeof (m[0])/sizeof (m[0][0]);
    }



    void multiplication(float** m1, int m1_row, int m1_col, float** m2, int m2_row, int m2_col, float** res){
        float buff=0;
        int numb_of_row=0;
        int numb_of_col=0;
        if(m1_col==m2_row){
            for(int i=0; i<m1_row; i++){
                for(int j=0; j<m1_col; j++){
                    buff+=m1[i][j]*m2[j][i];

                }

                if(numb_of_col!=m1_col-1){
                    res[numb_of_row][numb_of_col]=buff;
                    numb_of_col++;
                }else{
                    numb_of_col=0;
                    numb_of_row++;
                }
                buff=0;
            }
        }
    }
};


class Cube{
private:
    Field *f;
    int line_size;
    dot vertices[8];
    dot center;
    line lines[12];
public:
    Cube(Field *f, int x, int y, int z, int line_size){
        center.x=x;
        center.y=y;
        center.z=z;
        this->line_size=line_size;
        this->f=f;
    }

    void find_vertices(){
        vertices[0]={center.x+line_size/2, center.y+line_size/2, center.z+line_size/2};
        vertices[1]={center.x+line_size/2, center.y-line_size/2, center.z+line_size/2};
        vertices[2]={center.x-line_size/2, center.y-line_size/2, center.z+line_size/2};
        vertices[3]={center.x-line_size/2, center.y+line_size/2, center.z+line_size/2};
        vertices[4]={center.x-line_size/2+8, center.y+line_size/2-4, center.z-line_size/2};
        vertices[5]={center.x+line_size/2+8, center.y+line_size/2-4, center.z-line_size/2};
        vertices[6]={center.x+line_size/2+8, center.y-line_size/2-4, center.z-line_size/2};
        vertices[7]={center.x-line_size/2+8, center.y-line_size/2-4, center.z-line_size/2};

    }

    void find_lines(){
        lines[0]={vertices[0], vertices[1]};
        lines[1]={vertices[0], vertices[3]};
        lines[2]={vertices[0], vertices[5]};
        lines[3]={vertices[1], vertices[2]};
        lines[4]={vertices[1], vertices[6]};
        lines[5]={vertices[2], vertices[3]};
        lines[6]={vertices[2], vertices[7]};
        lines[7]={vertices[3], vertices[4]};
        lines[8]={vertices[4], vertices[5]};
        lines[9]={vertices[4], vertices[7]};
        lines[10]={vertices[5], vertices[6]};
        lines[11]={vertices[6], vertices[7]};
    }

    line get_line(int i){
        return lines[i];
    }
    dot get_vertices(int i){
        return vertices[i];
    }
    void set_vertices(dot v, int i){
        vertices[i]=v;
    }

    void shift(char symbol){
        float matr_shift[3][3]={1., 0, 0,
                                0, 1., 0,
                                0, 0, 1.};

        switch (symbol)
        {
        case 'w': matr_shift[1][2]=-1.; break;
        case 's': matr_shift[1][2]=1.; break;
        case 'a': matr_shift[0][2]=-1.; break;
        case 'd': matr_shift[0][2]=1.; break;
        }

        float coord[3];
        float buff=0;



        for (int i=0; i<8; i++){
            coord[0]=vertices[i].x;
            coord[1]=vertices[i].y;
            coord[2]=1;

            for(int j=0; j<3; j++){
                buff+=matr_shift[0][j]*coord[j];
            }
            vertices[i].x=buff;
            buff=0;

            for(int j=0; j<3; j++){
                buff+=matr_shift[1][j]*coord[j];
            }
            vertices[i].y=buff;
            buff=0;
        }
    }

    void rotate(float angle, char symbol)
    {


        float matr_rotate[4][4]={1., 0, 0, 0,
                                 0, 1., 0, 0,
                                 0, 0, 1., 0,
                                 0, 0, 0, 1.};

        angle = angle * 2 * 3.14 / 360;

        switch (symbol) {
        case 'r':
            matr_rotate[1][1]=cos(angle);
            matr_rotate[1][2]=-sin(angle);
            matr_rotate[2][1]=sin(angle);
            matr_rotate[2][2]=cos(angle);
            break;
        case 'f':
            matr_rotate[0][0]=cos(angle);
            matr_rotate[0][2]=sin(angle);
            matr_rotate[2][0]=-sin(angle);
            matr_rotate[2][2]=cos(angle);
        default:
            break;
        }


        float coord[4];
        float buff=0;

        for (int i=0; i<8; i++){
            coord[0]=vertices[i].x;
            coord[1]=vertices[i].y;
            coord[2]=vertices[i].z;

            for(int j=0; j<3; j++){
                buff+=matr_rotate[0][j]*coord[j];
            }
            vertices[i].x=buff;
            buff=0;

            for(int j=0; j<3; j++){
                buff+=matr_rotate[1][j]*coord[j];
            }
            vertices[i].y=buff;
            buff=0;

            for(int j=0; j<3; j++){
                buff+=matr_rotate[2][j]*coord[j];
            }
            vertices[i].z=buff;
            buff=0;
        }
    }
};



int main()
{
    Field field;
    Cube cube(&field, 0, 0, 0, 14);
    cube.find_vertices();
    cube.find_lines();
    bool game=1;
    COORD position;

    for(int i=0; i<12; i++){
        field.draw_line(dot_to_coord(cube.get_line(i).d1), dot_to_coord(cube.get_line(i).d2));
    }

    while(game){

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        position.X = 0;
        position.Y = 0;
        SetConsoleCursorPosition(hConsole, position);


        if(GetKeyState('Q') & 0x8000){
            game=0;
        }

        if(GetKeyState('W') & 0x8000){
            field.field_clear();
            cube.shift('w');
            cube.find_lines();
            for(int i=0; i<12; i++){
                field.draw_line(dot_to_coord(cube.get_line(i).d1), dot_to_coord(cube.get_line(i).d2));
            }
        }
        if(GetKeyState('S') & 0x8000){
            field.field_clear();
            cube.shift('s');
            cube.find_lines();
            for(int i=0; i<12; i++){
                field.draw_line(dot_to_coord(cube.get_line(i).d1), dot_to_coord(cube.get_line(i).d2));
            }
        }
        if(GetKeyState('A') & 0x8000){
            field.field_clear();
            cube.shift('a');
            cube.find_lines();
            for(int i=0; i<12; i++){
                field.draw_line(dot_to_coord(cube.get_line(i).d1), dot_to_coord(cube.get_line(i).d2));
            }
        }
        if(GetKeyState('D') & 0x8000){
            field.field_clear();
            cube.shift('d');
            cube.find_lines();
            for(int i=0; i<12; i++){
                field.draw_line(dot_to_coord(cube.get_line(i).d1), dot_to_coord(cube.get_line(i).d2));
            }
        }
        if(GetKeyState('R') & 0x8000){
            field.field_clear();
            cube.rotate(10, 'r');
            cube.find_lines();
            for(int i=0; i<12; i++){
                field.draw_line(dot_to_coord(cube.get_line(i).d1), dot_to_coord(cube.get_line(i).d2));
            }
        }
        if(GetKeyState('F') & 0x8000){
            field.field_clear();
            cube.rotate(10, 'f');
            cube.find_lines();
            for(int i=0; i<12; i++){
                field.draw_line(dot_to_coord(cube.get_line(i).d1), dot_to_coord(cube.get_line(i).d2));
            }
        }



        field.show();
    }


    return 0;
}
