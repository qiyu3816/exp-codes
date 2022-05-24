import cv2
import numpy as np
import matplotlib
import math
from matplotlib import pyplot as plt  

# 计算x方向的梯度的函数 索贝尔算子
def grad_x(matrix, gray):
    """ 使用Sobel算子进行梯度及其方向的计算
         -1 0 1        -1 -2 -1
    Gx = -2 0 2   Gy =  0  0  0
         -1 0 1         1  2  1

    params:
        matrix: 原图像矩阵
        gray: 原灰度图

    return:
        matrix: x方向梯度大小
    """
    a = int(gray.shape[0])
    b = int(gray.shape[1])
    for i in range(a):
        for j in range(b):
            if i-1>=0 and i+1<a and j-1>=0 and j+1<b:
                c = abs(int(gray[i-1,j-1]) - int(gray[i+1,j-1]) + 2*(int(gray[i-1,j]) - 2*int(gray[i+1,j])) + int(gray[i-1,j+1]) - int(gray[i+1,j+1]))
                if c>255: # 限制超界
                    c = 255
                matrix[i,j] = c
            else:
                matrix[i,j] = 0
    return matrix

# 计算y方向的梯度的函数 索贝尔算子
def grad_y(matrix, gray):
    """ 使用Sobel算子进行梯度及其方向的计算
         -1 0 1        -1 -2 -1
    Gx = -2 0 2   Gy =  0  0  0
         -1 0 1         1  2  1

    params:
        matrix: 原图像矩阵
        gray: 原灰度图

    return:
        matrix: y方向梯度大小
    """
    a = int(gray.shape[0])
    b = int(gray.shape[1])
    for i in range(a):
        for j in range(b):
            if i-1>= 0 and i+1<a and j-1>= 0 and j+1<b:
                c = abs(int(gray[i-1,j-1]) - int(gray[i-1,j+1]) + 2*(int(gray[i,j-1]) - 2*int(gray[i,j+1])) + (int(gray[i+1,j-1]) - int(gray[i+1,j+1])))
                if c>255: # 限制超界
                    c = 255
                matrix[i, j] = c
            else:
                matrix[i, j] = 0
    return matrix

def myHarris(filename, savename, sigmax, sigmay, kfactor):
    src = cv2.imread(filename)

    # 转换为灰度图
    gray = cv2.cvtColor(src, cv2.COLOR_RGB2GRAY)

    # 转换为矩阵
    m = np.matrix(gray)

    # 根据索贝尔算子 求x,y的梯度
    delta_h = m
    dx = np.array(grad_x(delta_h, gray))
    dy = np.array(grad_y(delta_h, gray))

    # 根据梯度计算 Ix^2 Iy^2 Ix*Iy
    A = dx * dx
    B = dy * dy 
    C = dx * dy

    A1 = A
    B1 = B
    C1 = C

    A1 = cv2.GaussianBlur(A1, (3, 3), sigmax, sigmay)
    B1 = cv2.GaussianBlur(B1, (3, 3), sigmax, sigmay)
    C1 = cv2.GaussianBlur(C1, (3, 3), sigmax, sigmay)

    a = int(gray.shape[0])
    b = int(gray.shape[1])

    final_harris = np.zeros(gray.shape)
    for i in range(a):
        for j in range(b):
            # 从梯度相乘结果得出M矩阵
            M = [[A1[i, j], C1[i, j]], [C1[i, j], B1[i, j]]]

            final_harris[i,j] = np.linalg.det(M) - kfactor * (np.trace(M)) * (np.trace(M))

    cv2.namedWindow('Harris', cv2.WINDOW_NORMAL)
    cv2.imshow('Harris', final_harris)
    cv2.namedWindow('src', cv2.WINDOW_NORMAL)
    cv2.imshow('src', src)
    cv2.imwrite(savename, final_harris * 255)

    while(True):
        c = cv2.waitKey(1)
        if c == 27:
            break

if __name__ == '__main__':
    # 读取图片
    filename = 'pics/check_board.png'
    savename = 'pics/harris_check_board_sobel.png'
    myHarris(filename, savename, 1.5, 1.5, 0.06)
