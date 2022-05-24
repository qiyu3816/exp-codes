import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.action_chains import ActionChains

# 梁芮槐-2019302789
# Web功能测试
def test():
    # 打开浏览器 浏览目的主页
    driver = webdriver.Chrome()
    driver.get("https://nj.zu.anjuke.com/")  # 主页
    time.sleep(10) # 等待10s 以防网速不好后续找不到元素

    # 找到并点击“租房”
    driver.find_element(By.XPATH, "/html/body/div[2]/div/ul/li[4]/a").click()
    time.sleep(5)

    # 找到并点击“南京”
    driver.find_element(By.XPATH, "/html/body/div[3]/div/div[2]/dl[2]/dd/a[4]")
    time.sleep(5)

    # 找到并点击“地铁租房”
    driver.find_element(By.XPATH, "/html/body/div[4]/ul/li[2]").click()
    time.sleep(5)

    # 找到并点击“2号线”
    driver.find_element(By.XPATH, "/html/body/div[5]/div[2]/div[1]/span[2]/div/a[3]").click()
    time.sleep(5)

    # 找到并点击“马群”
    driver.find_element(By.XPATH, "/html/body/div[5]/div[2]/div[1]/span[2]/div/div/a[20]").click()
    time.sleep(5)

    # 找到并设置价格区间
    driver.find_element(By.ID, "from-price").send_keys("5000")
    time.sleep(5)
    driver.find_element(By.ID, "to-price").send_keys("8000")
    time.sleep(5)
     # 找到并点击“确定”
    driver.find_element(By.ID, "pricerange_search").click()
    time.sleep(5)

    # 找到并点击“整租”
    driver.find_element(By.XPATH, "/html/body/div[5]/div[2]/div[4]/span[2]/a[2]").click()
    time.sleep(5)

    # 找到并将鼠标移动到“房屋类型”
    house_type = driver.find_element(By.ID, "condhouseage_txt_id")
    time.sleep(5)
    ActionChains(driver).move_to_element(house_type).perform()
    time.sleep(3)
    # 找到并点击“普通住宅”
    driver.find_element(By.XPATH, "/html/body/div[5]/div[2]/div[5]/div/ul/li[2]/ul/li[2]/a").click() # 点了普通住宅
    time.sleep(5)

    # 在搜索框输入“经天路”
    driver.find_element(By.ID, "search-rent").send_keys("经天路")
    time.sleep(5)
    # 找到并点击“搜索”
    driver.find_element(By.ID, "search-button").click()
    time.sleep(5)

    # 找到并点击“视频看房”
    driver.find_element_by_xpath("/html/body/div[5]/div[3]/div[1]/div[1]/a[2]").click()
    time.sleep(5)

    # 找到并点击“租金”
    driver.find_element_by_xpath("/html/body/div[5]/div[3]/div[1]/div[2]/div/a[2]").click()
    time.sleep(5)

    # 找到并点击“最新”
    driver.find_element_by_xpath("/html/body/div[5]/div[3]/div[1]/div[2]/div/a[3]").click()
    time.sleep(5)

    # 找到并点击第一个房源
    driver.find_element_by_xpath("/html/body/div[5]/div[3]/div[1]/div[3]/div[1]/h3/a").click()
    time.sleep(30)

    driver.quit()

if __name__ == "__main__":
    test()