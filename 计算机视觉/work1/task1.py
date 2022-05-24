import cv2

def task1():
    kernel_max = 29
    kernel_min = 3
    kernel_size = kernel_min
    kernel_step = 2
    sigma_max = 11
    sigma_min = 1
    sigma_factor = sigma_min
    sigma_step = 1

    blur_kernel = "kernel=" + str(kernel_size) + "*" + str(kernel_size)
    blur_sigma = "sigma=" + str(sigma_factor)

    low_threshold = 50
    high_threshold = 150

    lena_gray = cv2.imread('pics/lena512.bmp', 0)
    lena_color = cv2.imread('pics/lena512color.tiff', 1)
    # lena_gray = cv2.cvtColor(lena_color, cv2.COLOR_BGR2GRAY)
    lena_gray_guassian_blur = cv2.GaussianBlur(lena_gray, (kernel_size, kernel_size), sigma_factor, sigma_factor)
    cv2.putText(lena_gray_guassian_blur, blur_kernel, (15, 18), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
    cv2.putText(lena_gray_guassian_blur, blur_sigma, (15, 34), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
    lena_gray_canny = cv2.Canny(lena_gray, low_threshold, high_threshold)
    cv2.imshow("raw", lena_gray)
    cv2.imshow("gaussion_blur", lena_gray_guassian_blur)
    cv2.imshow("canny", lena_gray_canny)

    while True:
        c = cv2.waitKey(1)
        if c & 0xFF == ord('1'): # 减小滤波窗口大小
            if kernel_size - kernel_step >= kernel_min:
                kernel_size -= kernel_step
            lena_gray_guassian_blur = cv2.GaussianBlur(lena_gray, (kernel_size, kernel_size), sigma_factor, sigma_factor)
            blur_kernel = "kernel=" + str(kernel_size) + "*" + str(kernel_size)
            blur_sigma = "sigma=" + str(sigma_factor)
            cv2.putText(lena_gray_guassian_blur, blur_kernel, (15, 18), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
            cv2.putText(lena_gray_guassian_blur, blur_sigma, (15, 34), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
            lena_gray_canny = cv2.Canny(lena_gray, low_threshold, high_threshold)
            cv2.imshow("raw", lena_gray)
            cv2.imshow("gaussion_blur", lena_gray_guassian_blur)
            cv2.imshow("canny", lena_gray_canny)
        elif c & 0xFF == ord('2'): # 增大滤波窗口大小
            if kernel_size + kernel_step <= kernel_max:
                kernel_size += kernel_step
            lena_gray_guassian_blur = cv2.GaussianBlur(lena_gray, (kernel_size, kernel_size), sigma_factor, sigma_factor)
            blur_kernel = "kernel=" + str(kernel_size) + "*" + str(kernel_size)
            blur_sigma = "sigma=" + str(sigma_factor)
            cv2.putText(lena_gray_guassian_blur, blur_kernel, (15, 18), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
            cv2.putText(lena_gray_guassian_blur, blur_sigma, (15, 34), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
            lena_gray_canny = cv2.Canny(lena_gray, low_threshold, high_threshold)
            cv2.imshow("raw", lena_gray)
            cv2.imshow("gaussion_blur", lena_gray_guassian_blur)
            cv2.imshow("canny", lena_gray_canny)
        elif c & 0xFF == ord('3'): # 减小尺度因子
            if sigma_factor - sigma_step >= sigma_min:
                sigma_factor -= sigma_step
            lena_gray_guassian_blur = cv2.GaussianBlur(lena_gray, (kernel_size, kernel_size), sigma_factor, sigma_factor)
            blur_kernel = "kernel=" + str(kernel_size) + "*" + str(kernel_size)
            blur_sigma = "sigma=" + str(sigma_factor)
            cv2.putText(lena_gray_guassian_blur, blur_kernel, (15, 18), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
            cv2.putText(lena_gray_guassian_blur, blur_sigma, (15, 34), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
            lena_gray_canny = cv2.Canny(lena_gray, low_threshold, high_threshold)
            cv2.imshow("raw", lena_gray)
            cv2.imshow("gaussion_blur", lena_gray_guassian_blur)
            cv2.imshow("canny", lena_gray_canny)
        elif c & 0xFF == ord('4'): # 增大尺度因子
            if sigma_factor + sigma_step <= sigma_max:
                sigma_factor += sigma_step
            lena_gray_guassian_blur = cv2.GaussianBlur(lena_gray, (kernel_size, kernel_size), sigma_factor, sigma_factor)
            blur_kernel = "kernel=" + str(kernel_size) + "*" + str(kernel_size)
            blur_sigma = "sigma=" + str(sigma_factor)
            cv2.putText(lena_gray_guassian_blur, blur_kernel, (15, 18), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
            cv2.putText(lena_gray_guassian_blur, blur_sigma, (15, 34), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (255, 255, 0), 2)
            lena_gray_canny = cv2.Canny(lena_gray, low_threshold, high_threshold)
            cv2.imshow("raw", lena_gray)
            cv2.imshow("gaussion_blur", lena_gray_guassian_blur)
            cv2.imshow("canny", lena_gray_canny)
        if c & 0xFF == ord('r'): # 存储图片
            cv2.imwrite(blur_kernel + blur_sigma + ".bmp", lena_gray_canny)
        elif c == 27:
            break

    cv2.destroyWindows()

if __name__ == "__main__":
    task1()