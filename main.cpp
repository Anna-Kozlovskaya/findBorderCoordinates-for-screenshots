#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <opencv4/opencv2/highgui.hpp>
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/core.hpp"
using namespace cv;
using namespace std;
vector <Point> SortPoints(const vector <vector <Point>>& contours)
{
    vector <Point> result;
    for (const auto& cur_contour: contours)
    {
        for (const auto& cur_point: cur_contour)
        {
            result.push_back(cur_point);
        }
    }
    sort(result.begin(), result.end(), [](const Point& a, const Point& b){return a.x < b.x;});
    return result;
}
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Ошибка. Не введен адрес исходного или выходного файла." << endl;
    }
    //подготовка изображения
    Mat image = imread(argv[1]); //считывание изображения
    cvtColor(image, image, COLOR_BGR2GRAY); //перевод в серый
    threshold(image, image, 88, 255, THRESH_BINARY); //

    //выделение горизонтальных линий
    Mat kernel = (Mat_<int>(3,2) << -1, -1, 2, 2, -1, -1);
    filter2D(image, image, -1, kernel);

    //инвертируем изображение
    bitwise_not(image, image);

    //нахождение контуров и сортировка точек в них
    vector <vector <Point>> contours;
    findContours(image, contours, RETR_TREE, CHAIN_APPROX_TC89_L1);
    vector <Point> sorted_points = SortPoints(contours);

    //запись результата в файл
    ofstream out_file(argv[2]);
    for (const auto& cur_point: sorted_points)
    {
        out_file << cur_point.x << " " << cur_point.y << endl;
    }

    return 0;
}
