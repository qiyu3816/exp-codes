import cv2
import matplotlib.pyplot as plt

img1 = cv2.cvtColor(cv2.imread('pics/mountain1.png'), cv2.COLOR_BGR2GRAY)
img2 = cv2.cvtColor(cv2.imread('pics/mountain2.png'), cv2.COLOR_BGR2GRAY)

sift = cv2.xfeatures2d.SIFT_create()

"""
得出关键点和关键点描述子
"""
keypoints_1, descriptors_1 = sift.detectAndCompute(img1, None)
keypoints_2, descriptors_2 = sift.detectAndCompute(img2, None)

bf = cv2.BFMatcher(cv2.NORM_L1, crossCheck=True)    # 建立匹配关系
matches = bf.match(descriptors_1, descriptors_2)    # 匹配描述子
matches = sorted(matches, key=lambda  x:x.distance) # 根据距离排序

img3 = cv2.drawMatches(img1, keypoints_1, img2, keypoints_2, matches[:100], img2, flags=2) # 画出相关特征点

plt.imshow(img3)
plt.show()