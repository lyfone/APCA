//
// Created by zzhfeng on 2018/3/7.
//

#ifndef APCA_APCA_H
#define APCA_APCA_H

#pragma once

#include <vector>
#include <math.h>

/**
 * PCA数据结构
 */
struct APCA_DATA {
    int counter;
    float avg;
};

/**
 * APCA类，实现相关功能
 */
class APCA {
private:
    //PCA数据结构
    APCA_DATA apca_data;
    //编码的数据点集合
    std::vector<float> points;
    //数据点总值
    double sum;
    //方差阈值
    float variance;
    //计算方差
    double compute_variance(std::vector<float> &points, float avg);

public:
    //构造函数
    APCA(float variance);

    //读取编码数据点的跨度，即使数量
    int get_width();

    //读取编码后的均值
    float get_avg();

    //加入新的数据点
    bool push(float f);

    //读取编码数据点集合
    std::vector<float> get_points();

    //读取和
    double get_sum();

    //重置
    void reset();
};

/**
 * 构造函数初始化
 * @param width
 */
APCA::APCA(float f) {
    apca_data.counter = 0;
    apca_data.avg = 0;
    sum = 0.0;
    variance = f;
}

/**
 * 读取编码均值结果
 * @return
 */
float APCA::get_avg() {
    return apca_data.avg;
}

/**
 * 读取编码跨度（数量）
 * @return
 */
int APCA::get_width() {
    return apca_data.counter;
}

/**
 * 写入数据点
 * @param f
 * @return 返回编码是否完成
 */
bool APCA::push(float f) {
    points.push_back(f);
    apca_data.counter++;
    sum += f;
    apca_data.avg = sum / apca_data.counter;
    double sum_x = compute_variance(points,apca_data.avg);
    bool flag = sum_x <= variance;
    if(flag) return flag;
    points.pop_back();
    sum -= f;
    apca_data.counter--;
    apca_data.avg = sum / apca_data.counter;
    return flag;
}

/**
 * 读取被编码的数据集合
 * @return
 */
std::vector<float> APCA::get_points() {
    return points;
}

/**
 * 读取和
 * @return
 */
double APCA::get_sum() {
    return sum;
}

/**
 * 重置
 */
void APCA::reset() {
    apca_data.avg = 0.0;
    apca_data.counter = 0;
    sum = 0.0;
    points.clear();
}

/**
 * 计算当前数据点的方差
 * @param points
 * @param avg
 * @return
 */
double APCA::compute_variance(std::vector<float> &points, float avg) {
    double sum;
    int len = points.size();
    for (auto it = points.begin(); it != points.end(); it++) {
        sum += (*it - avg) * (*it - avg);
    }
    return sqrt(sum / len);
}

#endif //APCA_APCA_H
