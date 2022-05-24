import sys
import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
 
if __name__ == '__main__':
    # 手机照片尺寸3648*2736 先给左图加个边框
    top, bot, left, right = 100, 100, 0, 3748
    if len(sys.argv) != 3:
        print("Usage: python3 fusion.py <leftimg> <rightimg>\n")
        exit()
    
    img1 = cv.imread(sys.argv[1])
    img2 = cv.imread(sys.argv[2])
    srcImg = cv.copyMakeBorder(img1, top, bot, left, right, cv.BORDER_CONSTANT, value=(0, 0, 0))
    testImg = cv.copyMakeBorder(img2, top, bot, left, right, cv.BORDER_CONSTANT, value=(0, 0, 0))
    img1gray = cv.cvtColor(srcImg, cv.COLOR_BGR2GRAY)
    img2gray = cv.cvtColor(testImg, cv.COLOR_BGR2GRAY)

    # SIFT特征检测
    sift = cv.xfeatures2d_SIFT().create()
    kp1, des1 = sift.detectAndCompute(img1gray, None)
    kp2, des2 = sift.detectAndCompute(img2gray, None)
    # FLANN 特征匹配参数
    FLANN_INDEX_KDTREE = 1
    index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
    search_params = dict(checks=50)
    flann = cv.FlannBasedMatcher(index_params, search_params)
    matches = flann.knnMatch(des1, des2, k=2)
 
    # 内部匹配掩码
    matchesMask = [[0, 0] for i in range(len(matches))]
 
    good = []
    pts1 = []
    pts2 = []
    # 根据特征点接近程度筛选相邻匹配
    for i, (m, n) in enumerate(matches):
        if m.distance < 0.7*n.distance:
            good.append(m)
            pts1.append(kp1[m.queryIdx].pt)
            pts2.append(kp2[m.trainIdx].pt)
            matchesMask[i] = [1, 0]
 
    # 画出部分匹配点
    draw_params = dict(matchColor=(0, 255, 0),
                       singlePointColor=(255, 0, 0),
                       matchesMask=matchesMask[:5000],
                       flags=0)
    img3 = cv.drawMatchesKnn(img1gray, kp1, img2gray, kp2, matches[:5000], None, **draw_params)
    # plt.imshow(img3)
    # plt.show()
 
    rows, cols = srcImg.shape[:2]
    MIN_MATCH_COUNT = 10
    if len(good) > MIN_MATCH_COUNT:
        src_pts = np.float32([kp1[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
        dst_pts = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)
        # RANSAC计算单应矩阵
        M, mask = cv.findHomography(src_pts, dst_pts, cv.RANSAC, 5.0)
        # 透视变换
        warpImg = cv.warpPerspective(testImg, np.array(M), (testImg.shape[1], testImg.shape[0]), flags=cv.WARP_INVERSE_MAP)
 
        for col in range(0, cols):
            if srcImg[:, col].any() and warpImg[:, col].any():
                left = col
                break
        for col in range(cols-1, 0, -1):
            if srcImg[:, col].any() and warpImg[:, col].any():
                right = col
                break
 
        res = np.zeros([rows, cols, 3], np.uint8)
        for row in range(0, rows):
            for col in range(0, cols):
                if not srcImg[row, col].any():
                    res[row, col] = warpImg[row, col]
                elif not warpImg[row, col].any():
                    res[row, col] = srcImg[row, col]
                else:
                    srcImgLen = float(abs(col - left))
                    testImgLen = float(abs(col - right))
                    alpha = srcImgLen / (srcImgLen + testImgLen)
                    res[row, col] = np.clip(srcImg[row, col] * (1-alpha) + warpImg[row, col] * alpha, 0, 255)
 
        # 把opencv的图像转到matplotlib显示
        res = cv.cvtColor(res, cv.COLOR_BGR2RGB)
        # 显示结果
        plt.figure()
        plt.imshow(res)
        plt.show()
    else:
        print("Not enough matches are found - {}/{}".format(len(good), MIN_MATCH_COUNT))
        matchesMask = None