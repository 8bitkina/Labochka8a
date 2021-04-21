//На плоскости задано множество точек А и множество прямых В.
//Найти две такие различные точки из А, чтобы проходящая через них прямая
//была параллельна наибольшему количеству  прямых из В.

#include <iostream>
#include <vector>
#include <GLUT/glut.h>
#include <fstream>
#include <set>
#include <string>
using namespace std;

vector<pair<float, float>> points;
vector<pair<pair<float, float>, pair<float, float>>> lines;
pair<pair<pair<float, float>, pair<float, float>>, int> mx;

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClearColor(0.5, 0.0, 0.7, 1) ;
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(5);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    for (int i = 0; i < lines.size(); i++) {
        glColor3d(0,1,1) ;
        glVertex2i(lines[i].first.first, lines[i].first.second);
        glVertex2i(lines[i].second.first, lines[i].second.second);
    }
    glEnd();

    glPointSize(5);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); i++) {
        glColor3d(1,0.3,0) ;
        glVertex2i(points[i].first, points[i].second);
    }
    glEnd();

    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    glColor3d(1,0,0) ;
    glVertex2i(mx.first.first.first, mx.first.first.second);
    glColor3d(0,0,1) ;
    glVertex2i(mx.first.second.first, mx.first.second.second);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    int A, B;
    ifstream in("input.txt");
    if (!in.is_open()) {
        cout << "A Ваш файлик не открылся!!!";
    }
    else {
        in >> A >> B;
        pair<int, int> a;
        pair<pair<int, int>, pair<int, int>> b;
        for (int i = 0; i < A; i++) {
            in >> a.first >> a.second;
            points.push_back(a);
        }
        for (int i = 0; i < B; i++) {
            in >> b.first.first >> b.first.second >> b.second.first >> b.second.second;
            lines.push_back(b);
        }

        mx.second = 0;
        mx.first.first.first = points[0].first;
        mx.first.first.second = points[0].second;
        mx.first.second.first = points[1].first;
        mx.first.second.second = points[1].second;
        for (int i = 0; i < A - 1; i++) {
            for (int j = i + 1; j < A; j++) {
                int n = 0;
                for (int y = 0; y < B; y++) {
                    if (points[i].second - points[j].second == 0 || lines[y].first.second - lines[y].second.second == 0) {
                        if (points[i].second - points[j].second == lines[y].first.second - lines[y].second.second)
                            n++;
                    }
                    else {
                        if ((points[i].first - points[j].first) * (lines[y].first.second - lines[y].second.second) ==
                        (lines[y].first.first - lines[y].second.first) * (points[i].second - points[j].second))
                            n++;
                    }
                }
                if (n > mx.second) {
                    mx.second = n;
                    mx.first.first.first = points[i].first;
                    mx.first.first.second = points[i].second;
                    mx.first.second.first = points[j].first;
                    mx.first.second.second = points[j].second;
                }
            }
        }

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);

        glutInitWindowSize(800, 600);
        glutCreateWindow("Labochka8(a)");


        glutReshapeFunc(reshape);
        glutDisplayFunc(display);

        glutMainLoop();
    }
}
