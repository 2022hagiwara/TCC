#include <iostream> // Visual Studio & MacOS用
//#include <GLUT/GLUT.h> // MacOS用 (Visual Studio利用の場合この行を削徐

#include <Windows.h> // Visual Studio用
#include <GL\glew.h> // Visual Studio用
#include <GL\freeglut.h> // Visual Studio用
//#include<iostream>
//#include<string.h>
//using namespace std;



void* font = GLUT_BITMAP_HELVETICA_18;
int WindowWidth = 1024;    //生成するウィンドウの幅
int WindowHeight = 800;    //生成するウィンドウの高さ
int WindowWidth_h = WindowWidth / 2;    //生成するウィンドウの幅
int k = 3, n = 2;  //kはアリティ nは次元
float moveX = 0, moveY = 0, moveZ = 0;
float angle = 0;
float xRotation = 0, yRotation = 0, zRotation = 0;
float a = 2;//サイクル間の距離ー自
float di = 0.5;//サイクルの距離ー自
float my_x = 1, my_y = 1, my_z = 1;//サイクルの座標ー自自
bool xyn_disp = true;
bool cd_disp = true;
bool x_disp = true;
bool y_disp = true;
bool z_disp = true;

//マウスの座標を保存する配列
int mpos_down[] = { 0,0 };
int mpos_up[] = { 0,0 };

/*
ここからボタン用の座標を保存する二次元配列

子配列の，左側の値には画面を何分割するか，右側の値には分割したものから何番目か？が入る
例
Xの{10,3}であれば，画面を１０個に分けたとき，左から３番目の位置の座標になる．
Yの{20,16}であれば，画面を2０個に分けたとき，上から16番目の位置の座標になる．

・___XYの配列

一つ目の配列にXの座標，二つ目の配列にYの座標が入っている


・___Xの配列

一つ目の配列に左側のXの座標，二つ目の配列に右側のXの座標が入っている


・___Yの配列

一つ目の配列に上側のYの座標，二つ目の配列に下側のYの座標が入っている


___Xと___Yの配列を組み合わせることで，相対的な座標に四角を描画できる


この配列を使うことで，画面サイズが変わった場合でも，適切な位置にボタンが表示される．
また，マウスの座標の位置を判断する処理にも使える．

*/

float nsXY[2][2] = { {10, 1},{50, 4} };
float nc2X[2][2] = { {10, 5},{10, 6} }
    , nc2Y[2][2] = { {50, 3},{50, 5} };
float nc3X[2][2] = { {10, 7},{10, 8} }
    , nc3Y[2][2] = { {50, 3},{50, 5} };

float ksXY[2][2] = { {10, 1},{50, 9} };
float kMX[2][2] = { {10, 5},{10, 6} }
    , kMY[2][2] = { {50, 8},{50, 10} };
float kPX[2][2] = { {10, 7},{10, 8} }
    , kPY[2][2] = { {50, 8},{50, 10} };


float asXY[2][2] = { {10, 1},{50, 14} };
float aMX[2][2] = { {10, 5},{10, 6} }
    , aMY[2][2] = { {50, 13},{50, 15} };
float aPX[2][2] = { {10, 7},{10, 8} }
    , aPY[2][2] = { {50, 13},{50, 15} };

float disXY[2][2] = { {10, 1},{50, 18} };
float diMX[2][2] = { {10, 5},{10, 6} }
    , diMY[2][2] = { {50, 17},{50, 19} };
float diPX[2][2] = { {10, 7},{10, 8} }
    , diPY[2][2] = { {50, 17},{50, 19} };


float nd_strXY[2][2] = { {10, 1},{50, 23} };
float nd_btnX[2][2] = { {10, 2.5}, {10, 3.5} }
    , nd_btnY[2][2] = { {50, 22}, {50, 24} };

float cd_strXY[2][2] = { {10, 5},{50, 23} };
float cd_btnX[2][2] = { {10, 8}, {10, 9} }
    , cd_btnY[2][2] = { {50, 22}, {50, 24} };

float x_disp_strXY[2][2] = { {10, 1},{50, 27} };
float x_disp_btnX[2][2] = { {10, 2}, {10, 3} }
    , x_disp_btnY[2][2] = { {50, 26}, {50, 28} };

float y_disp_strXY[2][2] = { {10, 4},{50, 27} };
float y_disp_btnX[2][2] = { {10, 5}, {10, 6} }
    , y_disp_btnY[2][2] = { {50, 26}, {50, 28} };

float z_disp_strXY[2][2] = { {10, 7},{50, 27} };
float z_disp_btnX[2][2] = { {10, 8}, {10, 9} }
    , z_disp_btnY[2][2] = { {50, 26}, {50, 28} };
    

float reset_strXY[2][2] = { {10,1},{50, 45} };
float reset_btnX[2][2] = { {10, 6}, {10,7} }
    , reset_btnY[2][2] = { {50,44},{50,47} };



int winid[2];//自　複数ウィンドウ

//色々な値を初期値に戻す関数
void reset(void) {
    k = 3, n = 2;  //kはアリティ nは次元
    moveX = 0, moveY = 0, moveZ = 0;
    angle = 0;
    xRotation = 0, yRotation = 0, zRotation = 0;
    a = 2;//サイクル間の距離ー自
    di = 0.5;//サイクルの距離ー自
    my_x = 1, my_y = 1, my_z = 1;//サイクルの座標ー自自
    xyn_disp = true;
    cd_disp = true;
    x_disp = true;
    y_disp = true;
    z_disp = true;
}

//intの値を描画する関数
void int_char_disp(int s) {
    if (s / 10 == 0) {
        char kazu = s + '0';
        glutBitmapCharacter(font, kazu);
        return;
    }
    else {
        char ni[] = {(s / 10) + '0', (s % 10) + '0'};
        glutBitmapCharacter(font, ni[0]);
        glutBitmapCharacter(font, ni[1]);
        return;
    }
}

//floatの値を小数点第一位まで描画する関数
void float_char_disp(float s) {
    int_char_disp((int)s);
    glutBitmapCharacter(font, '.');
    int_char_disp((int)((s - (int)s) * 10));
}

//座標から四角を描画する関数
void createQuad(float x1, float y1, float z1, float x2, float y2, float z2) {
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
    glEnd();
}

//相対的な座標から四角を描画する関数
void createQuadH(float x[2][2], float y[2][2]) {
    float tempX1 = ((WindowWidth_h / x[0][0]) * x[0][1]) - (WindowWidth_h / 2);
    float tempX2 = ((WindowWidth_h / x[1][0]) * x[1][1]) - (WindowWidth_h / 2);
    float tempY1 = ((WindowHeight / y[0][0]) * y[0][1]) - (WindowHeight / 2);
    float tempY2 = ((WindowHeight / y[1][0]) * y[1][1]) - (WindowHeight / 2);

    createQuad(tempX1, -tempY1, 0, tempX2, -tempY2, 0);
    
}

//ボタンの上に文字を描画する関数
void createQuadString(char c, float x[2][2], float y[2][2]) {
    float tempX1 = ((WindowWidth_h / x[0][0]) * x[0][1]) - (WindowWidth_h / 2);
    float tempX2 = ((WindowWidth_h / x[1][0]) * x[1][1]) - (WindowWidth_h / 2);
    float tempY1 = ((WindowHeight / y[0][0]) * y[0][1]) - (WindowHeight / 2);
    float tempY2 = ((WindowHeight / y[1][0]) * y[1][1]) - (WindowHeight / 2);
    
    float tempX = tempX1 + ((tempX2 - tempX1) / 2.5);
    float tempY = tempY1 + ((tempY2 - tempY1) / 1.5);
    glColor3f(0.2, 0.2, 0.2);
    glRasterPos3d(tempX, -tempY, 1);
    glutBitmapCharacter(font, c);
    
    glColor3f(1, 1, 1);
}

//引数の座標に文章を描画する関数
void createString(char c[], float xy[2][2]) {
    float tempX = ((WindowWidth_h / xy[0][0]) * xy[0][1]) - (WindowWidth_h / 2);
    float tempY = ((WindowHeight / xy[1][0]) * xy[1][1]) - (WindowHeight / 2);
    glRasterPos3f(tempX, -tempY, 0);
    for (int i = 0; i < sizeof(c) * 4; i++) {
        glutBitmapCharacter(font, c[i]);
    }
}

//引数の座標に一文字だけ文字を描画する関数
void createString_single(char c, float xy[2][2]) {
    float tempX = ((WindowWidth_h / xy[0][0]) * xy[0][1]) - (WindowWidth_h / 2);
    float tempY = ((WindowHeight / xy[1][0]) * xy[1][1]) - (WindowHeight / 2);
    glRasterPos3f(tempX, -tempY, 0);
    glutBitmapCharacter(font, c);
}

//球体を作成する関数
void createSphere(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); //座標
    glutSolidSphere(0.05 /*半径*/, 20.0, 20.0);
    glPopMatrix();
}

//線を作成する関数
void createLine(float startX, float startY, float startZ, float endX, float endY, float endZ) {
    glBegin(GL_LINES);
    glVertex3f(startX, startY, startZ); //スタート座標
    glVertex3f(endX, endY, endZ); //終了座標
    glEnd();
}

//軸を作成する関数
void createAxis() {
    glColor3f(1, 0, 0); //色を赤に変更
    createLine(-1000.0, 0, 0, 1000.0, 0, 0); //x軸

    glColor3f(0, 0, 1); //色を青に変更
    createLine(0, -1000.0, 0, 0, 1000.0, 0); //y軸

    glColor3f(0, 1, 0);
    createLine(0, 0, -1000.0, 0, 0, 1000.0);

    glColor3f(1, 1, 1); //色を白に変更
}

//2次元のサイクルを作成する関数
void create2dCycle(float x, float y, float z) {
    createSphere(x, y, z);
    createSphere(x + di, y + di, z);
    createSphere(x + di + di, y, z);
    createSphere(x + di, y - di, z);

    //glColor3f(0, 1, 0);
    createLine(x, y, z, x + di, y + di, z);
    //glColor3f(0, 0.75, 0);
    createLine(x + di, y + di, z, x + di + di, y, z);
    //glColor3f(0, 0.5, 0);
    createLine(x + di + di, y, z, x + di, y - di, z);
    //glColor3f(0, 0.25, 0);
    createLine(x + di, y - di, z, x, y, z);
}

void bezier2dConnectionX(float x1, float y1, float z1, float x2, float y2, float z2) {
    float xs = x1 + ((x2 - x1) / 2), ys = y2 + ((y1 - y2) / 2), zs = z1 + di;

    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 1.0; t += 0.01) {
        float xk = ((1 - t) * (1 - t) * x1) + (2 * t * (1 - t) * xs) + (t * t * x2);
        float yk = ((1 - t) * (1 - t) * y1) + (2 * t * (1 - t) * ys) + (t * t * y2);
        float zk = ((1 - t) * (1 - t) * z1) + (2 * t * (1 - t) * zs) + (t * t * z2);

        glVertex3d(xk, yk, zk);
    }
    glEnd();
}

void bezier2dConnectionY(float x1, float y1, float z1, float x2, float y2, float z2) {
    float xs = x1 + ((x2 - x1) / 2), ys = y2 + ((y1 - y2) / 2), zs = z1 - di;
    
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 1.0; t += 0.01) {
        float xk = ((1 - t) * (1 - t) * x1) + (2 * t * (1 - t) * xs) + (t * t * x2);
        float yk = ((1 - t) * (1 - t) * y1) + (2 * t * (1 - t) * ys) + (t * t * y2);
        float zk = ((1 - t) * (1 - t) * z1) + (2 * t * (1 - t) * zs) + (t * t * z2);

        glVertex3d(xk, yk, zk);
    }
    glEnd();
}

//2次元のサイクルとサイクルのつながりを作成する関数
void create2dConnection(float x, float y, float z) {
    //横
    glColor3f(0.8, 0.6, 0.7);
    if (x_disp)bezier2dConnectionX(x - a, y, z, x + di, y - di, z);

    //縦
    glColor3f(0.6, 0.7, 0.8);
    if (y_disp)bezier2dConnectionY(y + di + di, x - a, z, y + di, x + di, z);
    glColor3f(1, 1, 1);
}

//2dのアドレスの文字を描画する処理
void createXYNstring2d(float x, float y, float z, int i, int j, int node) {
    char xyn[] = "(,,)";

    glRasterPos3d(x, y, z);
    for (int t = 0; t < strlen(xyn); t++) {
        glutBitmapCharacter(font, xyn[t]);
        switch (t) {
        case 0:
            int_char_disp(i);
            break;
        case 1:
            int_char_disp(j);
            break;
        case 2:
            glutBitmapCharacter(font, node + '0');
            break;
        }
    }
}

//2dのアドレスの文字を全て描画する処理
void create2dXYN(float x, float y, float z, int i, int j) {

    createXYNstring2d(x, y, z, i, j, 0);
    createXYNstring2d(x + di, y + di, z, i, j, 1);
    createXYNstring2d(x + di + di, y, z, i, j, 2);
    createXYNstring2d(x + di, y - di, z, i, j, 3);


}

//2次元のTCCを作成する関数
void create2dTCC(float x, float y, float z) {
    for (int i = 0; i < k + 1; i++) {
        for (int j = 0; j < k; j++) {
            float kyori_x = a * i, kyori_y = a * j;
            if (i < k) {
                create2dCycle(x + kyori_x, y + kyori_y, z);
                if (xyn_disp)create2dXYN(x + kyori_x, y + kyori_y, z, i, j);
            }
            create2dConnection(x + kyori_x, y + kyori_y, z);
        }
    }
}

void bezier2dX(float x1, float y1, float z1, float x2, float y2, float z2) {
    float xs = x1 + ((x2 - x1) / 2), ys = y2 + ((y1 - y2) / 2), zs = z1 - a;

    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 1.0; t += 0.01) {
        float xk = ((1 - t) * (1 - t) * x1) + (2 * t * (1 - t) * xs) + (t * t * x2);
        float yk = ((1 - t) * (1 - t) * y1) + (2 * t * (1 - t) * ys) + (t * t * y2);
        float zk = ((1 - t) * (1 - t) * z1) + (2 * t * (1 - t) * zs) + (t * t * z2);

        glVertex3d(xk, yk, zk);
    }
    glEnd();
}

void bezier2dY(float x1, float y1, float z1, float x2, float y2, float z2) {
    float xs = x1 + ((x2 - x1) / 2), ys = y2 + ((y1 - y2) / 2), zs = z1 + a;

    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 1.0; t += 0.01) {
        float xk = ((1 - t) * (1 - t) * x1) + (2 * t * (1 - t) * xs) + (t * t * x2);
        float yk = ((1 - t) * (1 - t) * y1) + (2 * t * (1 - t) * ys) + (t * t * y2);
        float zk = ((1 - t) * (1 - t) * z1) + (2 * t * (1 - t) * zs) + (t * t * z2);

        glVertex3d(xk, yk, zk);
    }
    glEnd();
}

//2dの，端の接続を描画する処理
void create2dBezier(float x, float y, float z) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xF0F0);
    float kyori_x_x = (a * k) + a + di
        , kyori_x_y = -di;
    float x_x = x - a
        , x_y = y
        , x_z = z;
    float kyori_y_x = -di
        , kyori_y_y = (a * k) + a + di;
    float y_x = x + di + di
        , y_y = y - a
        , y_z = z;

    for (int i = 0; i < k; i++) 
    {
        glColor3f(0.6, 0.1, 0.1);
        if (x_disp)bezier2dX(x_x, x_y + (a * i), x_z, x_x + kyori_x_x, x_y + (a * i) + kyori_x_y, x_z);
        glColor3f(0.1, 0.1, 0.6);
        if (y_disp)bezier2dY(y_x + (a * i), y_y, y_z, y_x + (a * i) + kyori_y_x, y_y + kyori_y_y, y_z);
    }
    glColor3f(1, 1, 1);
    glDisable(GL_LINE_STIPPLE);
}

void create3dCycle(float x, float y, float z) {
    createSphere(x, y, z);
    createSphere(x + di, y + di, z);
    createSphere(x + di + di, y + di, z);
    createSphere(x + di + di + di, y, z);
    createSphere(x + di + di, y - di, z);
    createSphere(x + di, y - di, z);

    createLine(x, y, z, x + di, y + di, z);
    createLine(x + di, y + di, z, x + di + di, y + di, z);
    createLine(x + di + di, y + di, z, x + di + di + di, y, z);
    createLine(x + di + di + di, y, z, x + di + di, y - di, z);
    createLine(x + di + di, y - di, z, x + di, y - di, z);
    createLine(x + di, y - di, z, x, y, z);
}

//3dアドレスの文字を描画する処理
void createXYNstring3d(float x, float y, float z, int o, int p, int q, int node) {
    char xyzn[] = "(,,,)";

    glRasterPos3d(x, y, z);
    for (int t = 0; t < strlen(xyzn); t++) {
        glutBitmapCharacter(font, xyzn[t]);
        switch (t) {
        case 0:
            int_char_disp(o);
            break;
        case 1:
            int_char_disp(p);
            break;
        case 2:
            int_char_disp(q);
            break;
        case 3:
            glutBitmapCharacter(font, node + '0');
            break;
        }
    }
}

//3dのアドレスの文字を全て描画する処理
void create3dXYN(float x, float y, float z, int o, int p, int q) {

    createXYNstring3d(x, y, z, o, p, q, 0);
    createXYNstring3d(x + di, y + di, z, o, p, q, 1);
    createXYNstring3d(x + di + di, y + di, z, o, p, q, 2);
    createXYNstring3d(x + di + di + di, y, z, o, p, q, 3);
    createXYNstring3d(x + di + di, y - di, z, o, p, q, 4);
    createXYNstring3d(x + di, y - di, z, o, p, q, 5);

}

void create3dConnection(float x, float y, float z) {
    glColor3f(0.8, 0.6, 0.7);
    //横
    if(x_disp)createLine(x + di + di - a, y - di, z, x + di, y - di, z);

    //縦
    glColor3f(0.6, 0.7, 0.8);
    if (y_disp)createLine(y, x - a, z, y + di, x + di, z);

    //奥
    glColor3f(0.7, 0.8, 0.6);
    if (z_disp)createLine(y + di + di, -z + di, -(x - a), y + di + di + di, -z, -x);
    glColor3f(1, 1, 1);
}

//3次元のTCCを作成する関数
void create3dTCC(float x, float y, float z) {
    for (int o = 0; o < k + 1; o++) {
        for (int p = 0; p < k; p++) {
            for (int q = 0; q < k; q++) {
                float kyori_x = a * o, kyori_y = a * p, kyori_z = a * q;
                if (o < k) {
                    create3dCycle(x + kyori_x, y + kyori_y, -(z + kyori_z));
                    if (xyn_disp)create3dXYN(x + kyori_x, y + kyori_y, -(z + kyori_z), o, p, q);
                }
                create3dConnection(x + kyori_x, y + kyori_y, -(z + kyori_z));
            }
        }
    }
}

void bezier3dX(float x1, float y1, float z1, float x2, float y2, float z2) {

    float xs = ((x2 - x1) / 2) + x1, ys = y1, zs = z1 - a;
    //createSphere(xs, ys, zs); //制御点

    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 1.0; t += 0.01) {
        float xk = ((1 - t) * (1 - t) * x1) + (2 * t * (1 - t) * xs) + (t * t * x2);
        float yk = ((1 - t) * (1 - t) * y1) + (2 * t * (1 - t) * ys) + (t * t * y2);
        float zk = ((1 - t) * (1 - t) * z1) + (2 * t * (1 - t) * zs) + (t * t * z2);

        glVertex3d(xk, yk, zk);
    }
    glEnd();
}

void bezier3dY(float x1, float y1, float z1, float x2, float y2, float z2) {

    float xs = x1 + (x2 - x1), ys = ((y2 - y1) / 2) + y1, zs = z1 + a;
    //createSphere(xs, ys, zs); //制御点

    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 1.0; t += 0.01) {
        float xk = ((1 - t) * (1 - t) * x1) + (2 * t * (1 - t) * xs) + (t * t * x2);
        float yk = ((1 - t) * (1 - t) * y1) + (2 * t * (1 - t) * ys) + (t * t * y2);
        float zk = ((1 - t) * (1 - t) * z1) + (2 * t * (1 - t) * zs) + (t * t * z2);

        glVertex3d(xk, yk, zk);
    }
    glEnd();
}

void bezier3dZ(float x1, float y1, float z1, float x2, float y2, float z2) {

    float xs = x1 + di, ys = y1 + di + di, zs = ((z2 - z1) / 2) + z1;
    //createSphere(xs, ys, zs); //制御点

    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 1.0; t += 0.01) {
        float xk = ((1 - t) * (1 - t) * x1) + (2 * t * (1 - t) * xs) + (t * t * x2);
        float yk = ((1 - t) * (1 - t) * y1) + (2 * t * (1 - t) * ys) + (t * t * y2);
        float zk = ((1 - t) * (1 - t) * z1) + (2 * t * (1 - t) * zs) + (t * t * z2);

        glVertex3d(xk, yk, zk);
    }
    glEnd();
}

//3dの，端の接続を描画する処理
void create3dBezier(float x, float y, float z) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xF0F0);
    float kyori_x = (a * k) + a - di;
    float x_x = x - a + di + di
        , x_y = y - di
        , x_z = -z;
    float kyori_y_x = di
        , kyori_y_y = (a * k) + a + di;
    float y_x = x
        , y_y = y - a
        , y_z = -z;
    float kyori_z_x = di
        , kyori_z_y = -di
        , kyori_z_z = (a * k) + a;
    float z_x = x + di + di
        , z_y = y + di
        , z_z = -z + a;


    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            glColor3f(0.6, 0.1, 0.1);
            if (x_disp)bezier3dX(x_x, x_y + (a * i), x_z - (a * j), x_x + kyori_x, x_y + (a * i), x_z - (a * j));
            glColor3f(0.1, 0.1, 0.6);
            if (y_disp)bezier3dY(y_x + (a * i), y_y, y_z - (a * j), y_x + (a * i) + kyori_y_x, y_y + kyori_y_y, y_z - (a * j));
            glColor3f(0.1, 0.6, 0.1);
            if (z_disp)bezier3dZ(z_x + (a * j), z_y + (a * i), z_z, z_x + (a * j) + kyori_z_x, z_y + (a * i) + kyori_z_y, z_z - kyori_z_z);
        }
    }
    glDisable(GL_LINE_STIPPLE);
}

//画面に映る関数
void display(void) {
    glutSetWindow(winid[0]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //バッファの消去x

    glPushMatrix();

    glTranslatef(moveX, moveY, moveZ);
    glRotatef(angle, xRotation, yRotation, zRotation);
    glColor3f(1, 1, 1);
    //createAxis(); //軸を作成

    if (n == 2) {
        create2dTCC(my_x, my_y, -my_z);
        if (cd_disp)create2dBezier(my_x, my_y, -my_z);
    }
    else if (n == 3) {
        create3dTCC(my_x, my_y, my_z);
        if (cd_disp)create3dBezier(my_x, my_y, my_z);
    }

    glPopMatrix();

    glFlush();

    
    //ここから2つ目のウィンドウの描画
    glutSetWindow(winid[1]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //バッファの消去x

    glPushMatrix();
    //createAxis(); //軸を作成

    char n_info[] = "n = ";
    createString(n_info, nsXY);
    int_char_disp(n);
    if (n == 2)glColor3f(1, 1, 0.2);
    createQuadH(nc2X, nc2Y);
    createQuadString('2', nc2X, nc2Y);
    if (n == 3)glColor3f(1, 1, 0.2);
    createQuadH(nc3X, nc3Y);
    createQuadString('3', nc3X, nc3Y);

    char k_info[] = "k = ";
    createString(k_info, ksXY);
    int_char_disp(k);
    createQuadH(kMX, kMY);
    createQuadString('-', kMX, kMY);
    createQuadH(kPX, kPY);
    createQuadString('+', kPX, kPY);

    char a_info[] = "a = ";
    createString(a_info, asXY);
    float_char_disp(a);
    createQuadH(aMX, aMY);
    createQuadString('-', aMX, aMY);
    createQuadH(aPX, aPY);
    createQuadString('+', aPX, aPY);

    char di_info[] = "di = ";
    createString(di_info, disXY);
    float_char_disp(di);
    createQuadH(diMX, diMY);
    createQuadString('-', diMX, diMY);
    createQuadH(diPX, diPY);
    createQuadString('+', diPX, diPY);

    char nd_info[] = "Address";
    createString(nd_info, nd_strXY);
    if (xyn_disp) {
        glColor3f(0.6, 0.6, 1);
        createQuadH(nd_btnX, nd_btnY);
        glColor3f(1, 1, 1);
    }
    else {
        glColor3f(1, 0.6, 0.6);
        createQuadH(nd_btnX, nd_btnY);
        glColor3f(1, 1, 1);
    }

    char cd_info[] = "End connection";
    createString(cd_info, cd_strXY);
    if (cd_disp) {
        glColor3f(0.6, 0.6, 1);
        createQuadH(cd_btnX, cd_btnY);
        glColor3f(1, 1, 1);
    }
    else {
        glColor3f(1, 0.6, 0.6);
        createQuadH(cd_btnX, cd_btnY);
        glColor3f(1, 1, 1);
    }
    

    createString_single('x', x_disp_strXY);
    if (x_disp) {
        glColor3f(0.6, 0.6, 1);
        createQuadH(x_disp_btnX, x_disp_btnY);
        glColor3f(1, 1, 1);
    }
    else {
        glColor3f(1, 0.6, 0.6);
        createQuadH(x_disp_btnX, x_disp_btnY);
        glColor3f(1, 1, 1);
    }

    createString_single('y', y_disp_strXY);
    if (y_disp) {
        glColor3f(0.6, 0.6, 1);
        createQuadH(y_disp_btnX, y_disp_btnY);
        glColor3f(1, 1, 1);
    }
    else {
        glColor3f(1, 0.6, 0.6);
        createQuadH(y_disp_btnX, y_disp_btnY);
        glColor3f(1, 1, 1);
    }
    createString_single('z', z_disp_strXY);
    if (z_disp) {
        glColor3f(0.6, 0.6, 1);
        createQuadH(z_disp_btnX, z_disp_btnY);
        glColor3f(1, 1, 1);
    }
    else {
        glColor3f(1, 0.6, 0.6);
        createQuadH(z_disp_btnX, z_disp_btnY);
        glColor3f(1, 1, 1);
    }

    char reset_info[] = "Reset";
    createString(reset_info, reset_strXY);
    createQuadH(reset_btnX, reset_btnY);



    /*
    for (int i = 0; i <= 300; i++) {
        glColor3f(1, 0, 0); //色を赤に変更
        createLine(-1000.0, i, 0, 1000.0, i, 0); //x軸

        glColor3f(0, 0, 1); //色を青に変更
        createLine(i, -1000.0, 0, i, 1000.0, 0); //y軸

        glColor3f(1, 1, 1); //色を白に変更
    }
    */
    

    char test4[] = "test";

    glPopMatrix();

    glFlush();
}

//キーボードで操作する関数
void keyboardFunctions(unsigned char key, int a, int b) {
    //printf("%hhu ", key);

    switch (key) {
    case 27://escキーで終了
        exit(0);

    case'2':
        n = 2;
        break;

    case '3':
        n = 3;
        break;

    case 'w':
        moveY = moveY - 0.1;
        //gluLookAt(0, 0.1, 0, 0, 0.1, -1, 0, 1, 0);
        break;

    case 'a':
        moveX = moveX + 0.1;
        //gluLookAt(-0.1, 0, 0, -0.1, 0, -1, 0, 1, 0);
        break;

    case 's':
        moveY = moveY + 0.1;
        //gluLookAt(0, -0.1, 0, 0, -0.1, -1, 0, 1, 0);
        break;

    case 'd':
        moveX = moveX - 0.1;
        //gluLookAt(0.1, 0, 0, 0.1, 0, -1, 0, 1, 0);
        break;

    case 'c':
        moveZ = moveZ + 0.1;
        //gluLookAt(0, 0, -0.1, 0, 0, -1, 0, 1, 0);
        break;

    case 'z':
        moveZ = moveZ - 0.1;
        //gluLookAt(0, 0, 0.1, 0, 0, -1, 0, 1, 0);
        break;

    case 'r':
        /*
        xRotation = 1;
        yRotation = 0;
        zRotation = 0;
        angle = angle + 10;
        */
        glutSetWindow(winid[0]);
        gluLookAt(0.0, 0.0, 0.0,
            0, 1.0, -10.0,
            0.0, 1.0, 0.0);
        break;

    case 'f':
        /*
        xRotation = 1;
        yRotation = 0;
        zRotation = 0;
        angle = angle - 10;
        */
        glutSetWindow(winid[0]);
        gluLookAt(0.0, 0.0, 0.0,
            0, -1.0, -10.0,
            0.0, 1.0, 0.0);
        break;

    case 'q':
        
        xRotation = 0;
        yRotation = 1;
        zRotation = 0;
        angle = angle + 10;
        /*
        gluLookAt(0.0, 0.0, 0.0,
            -1, 0.0, -10.0,  
            0.0, 1.0, 0.0);
        */
        break;

    case 'e':
        
        xRotation = 0;
        yRotation = 1;
        zRotation = 0;
        angle = angle - 10;
        /*
        gluLookAt(0.0, 0.0, 0.0, 
            1, 0.0, -10.0, 
            0.0, 1.0, 0.0);
        */
        break;

    case '+':
        k = k + 1;
        break;

    case '-':
        if (k > 1) {
            k = k - 1;
        }
        break;

    case 'u':
        if (xyn_disp) {
            xyn_disp = false;
        }
        else {
            xyn_disp = true;
        }
        break;

    case 'i':
        if(cd_disp) {
            cd_disp = false;
        }else {
            cd_disp = true;
        }
        break;

    case 'n':
        glTranslatef(0, 0, 0);
        break;
    case '0':
        reset();
        break;
    }

    glutPostRedisplay();
}

//特殊キー入力    
void specialkeydown(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        moveY = moveY - 0.1;
        break;

    case GLUT_KEY_LEFT:
        moveX = moveX + 0.1;
        break;

    case GLUT_KEY_DOWN:
        moveY = moveY + 0.1;
        break;

    case GLUT_KEY_RIGHT:
        moveX = moveX - 0.1;
        break;
    }

    glutPostRedisplay();
}

//ボタンが押せるかの判定
//座標を引数として，マウスの座標と同じであればtrueを返す
bool checkPos(float x[2][2], float y[2][2]) {
    if (((WindowWidth_h / x[0][0]) * x[0][1]) <= mpos_down[0]) {
        if (((WindowWidth_h / x[1][0]) * x[1][1]) >= mpos_down[0]) {
            if (((WindowHeight / y[0][0]) * y[0][1]) <= mpos_down[1]) {
                if (((WindowHeight / y[1][0]) * y[1][1]) >= mpos_down[1]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        mpos_down[0] = x;
        mpos_down[1] = y;
    }
    else if (state == GLUT_UP) {
        mpos_up[0] = x;
        mpos_up[1] = y;
    }

    //マウス座標確認
    //printf("(%d,%d)", x,y);
    //printf(" %d", state);

    if (state == GLUT_DOWN) {
        if (checkPos(nc2X, nc2Y))n = 2;
        if (checkPos(nc3X, nc3Y))n = 3;
        if (checkPos(kMX, kMY))k = k - 1;
        if (checkPos(kPX, kPY))k = k + 1;
        if (checkPos(aMX, aMY))a = a - 0.1;
        if (checkPos(aPX, aPY))a = a + 0.1;
        if (checkPos(diMX, diMY))di = di - 0.1;
        if (checkPos(diPX, diPY))di = di + 0.1;
        if (checkPos(nd_btnX, nd_btnY)) {
            if (xyn_disp) {
                xyn_disp = false;
            }
            else {
                xyn_disp = true;
            }
        }

        if (checkPos(cd_btnX, cd_btnY)) {
            if (cd_disp) {
                cd_disp = false;
            }
            else {
                cd_disp = true;
            }
        }

        if (checkPos(x_disp_btnX, x_disp_btnY)) {
            if (x_disp) {
                x_disp = false;
            }
            else {
                x_disp = true;
            }
        }
        if (checkPos(y_disp_btnX, y_disp_btnY)) {
            if (y_disp) {
                y_disp = false;
            }
            else {
                y_disp = true;
            }
        }
        if (checkPos(z_disp_btnX, z_disp_btnY)) {
            if (z_disp) {
                z_disp = false;
            }
            else {
                z_disp = true;
            }
        }

        if (checkPos(reset_btnX, reset_btnY))reset();
    }
}

void GLUT_CALL_FUNC()
{
    glutDisplayFunc(display); //画面に映る関数をここで呼び出す
    glutKeyboardFunc(keyboardFunctions);
    glutSpecialFunc(specialkeydown);//特殊キー入力
}

//初期設定の関数
void initialize(void) {
    glViewport(0, 0, WindowWidth, WindowHeight);
    glEnable(GL_DEPTH_TEST); //デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する

    //透視投影法の視体積gluPerspactive
    gluPerspective(30.0,                                       //縦角度
        (double)WindowWidth / (double)WindowHeight, //横角度
        0.1,                                        //一番近いｚ軸
        1200);                                      //一番遠いｚ軸

    gluLookAt(0.0, 0.0, 10.0, //視点の位置→座標変えてる
        0.0, 0.0, 0.0,  //視点の位置からの視点の中心
        0.0, 1.0, 0.0); //視点の上

}

void GLUT_CALL_FUNC2()
{
    glutDisplayFunc(display); //画面に映る関数をここで呼び出す
    glutKeyboardFunc(keyboardFunctions);
    glutSpecialFunc(specialkeydown);//特殊キー入力
    glutMouseFunc(mouse);
}


//初期設定の関数
void initialize2(void) {
    glViewport(0, 0, WindowWidth, WindowHeight);
    glEnable(GL_DEPTH_TEST); //デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する

    //透視投影法の視体積gluPerspactive
    gluPerspective(90.0,                                       //縦角度
        (double)WindowWidth_h / (double)WindowHeight, //横角度
        0.1,                                        //一番近いｚ軸
        1200);                                      //一番遠いｚ軸

    gluLookAt(0.0,0.0, WindowHeight / 2, //視点の位置
        0.0, 0.0, 0.0,  //視点の位置からの視点の中心
        0.0, 1.0, 0.0); //視点の上
}

//プログラムの開始位置
int main(int argc, char** argv) {
    /*
    printf("n = ");
    scanf_s("%d", &n);

    while (true) {
        if (n == 2 || n == 3) {
            break;
        }
        printf("no\n");
        printf("n = ");
        scanf_s("%d", &n);
    }
    
    printf("k = ");
    scanf_s("%d", &k);//サイクルをいくつ作るかー自
    */

    glutInit(&argc, argv);
    glutInitWindowPosition(WindowWidth, 0);//kaeta
    glutInitWindowSize(WindowWidth / 2, WindowHeight);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    winid[1] = glutCreateWindow("Setting");
    GLUT_CALL_FUNC2();
    initialize2(); //初期設定

    glutInitWindowPosition(0, 0);//kaeta
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    winid[0] = glutCreateWindow("We love TCC!");
    GLUT_CALL_FUNC();//コールバック関数　メインループの処理を行う？
    initialize(); //初期設定

    glutMainLoop();
    return 0;
}