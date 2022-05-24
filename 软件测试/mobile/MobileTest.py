from appium import webdriver
from time import sleep

def anjukeMobileTest():
    desired_caps = {
      "platformName": "Android",
      "platformVersion": "10",
      "deviceName": "MQS7N19527013421",
      "app": "D:/chlpack-207867-anjuke_15.23.1_322112_b688.apk",
      "appPackage": "com.anjuke.android.app",
      "appActivity": "com.anjuke.android.app.mainmodule.WelcomeActivity",
    }
    # 不要每次测试都重装软件
    desired_caps['noReset'] = True
    # unicode编码
    desired_caps['unicodeKeyboard'] = True
    # 初始化键盘状态
    desired_caps['resetKeyboard'] = True

    # ##################### 1 #####################
    driver = webdriver.Remote(command_executor='http://localhost:4723/wd/hub',
                              desired_capabilities=desired_caps)
    sleep(5) # 刚打开有广告 多等一会

    size = driver.get_window_size()
    sleep(3)
    # 先整一堆要用的量 后面拿来滑手势
    x0 = 1
    x0_ = size['width'] * 0.999
    x1 = size['width'] * 0.75
    y1 = size['height'] * 0.25
    x2 = size['width'] * 0.25
    y2 = size['height'] * 0.75
    y3 = 157.0
    y4 = size['height'] * 0.5

    # 不知道所谓的介绍页面是什么 于是把“新房” “二手房”那一堆是个选项的栏滑到右边
    driver.swipe(x1, y1, x2, y1, 500)
    sleep(3)

    # 点击城市选择
    driver.find_element_by_id("com.anjuke.android.app:id/city_name_text_view").click()
    sleep(3)

    # 在输入框输入“南京”
    driver.find_element_by_id("com.anjuke.android.app:id/edittext").send_keys("南京")
    sleep(3)

    # 点击“南京”
    driver.find_element_by_id("com.anjuke.android.app:id/select_city_tv_item").click()
    sleep(3)

    # ##################### 2 #####################
    # 点击“南京房价”
    driver.find_element_by_id("com.anjuke.android.app:id/price_address_text_view").click()
    sleep(3)

    # 点击“关注”
    driver.find_element_by_id("com.anjuke.android.app:id/title_text_view").click()
    sleep(3)

    # 点击“新房”
    driver.find_element_by_id("com.anjuke.android.app:id/new_house_tv").click()
    sleep(3)

    # 点击“近1年”
    driver.find_element_by_id("com.anjuke.android.app:id/housePriceTrendOneYearTitle").click()
    sleep(3)

    # 点击“近3年”
    driver.find_element_by_id("com.anjuke.android.app:id/housePriceTrendThreeYearTitle").click()
    sleep(3)

    # ##################### 3 #####################
    # 点击返回键返回主页面
    driver.find_element_by_id("com.anjuke.android.app:id/communityReportBackBtn").click()
    sleep(3)

    # 刚才滑了一遍 现在得滑回来
    driver.swipe(x2, y1, x1, y1, 500)
    sleep(3)

    # 点击“新房”
    driver.find_element_by_id("com.anjuke.android.app:id/item_biz_name").click()
    sleep(8)

    # 点击“房贷计算”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.RelativeLayout/android.view.ViewGroup/android.widget.LinearLayout/android.widget.LinearLayout/android.widget.LinearLayout/android.widget.LinearLayout/android.widget.LinearLayout[2]/android.widget.LinearLayout[2]/android.widget.TextView").click()
    sleep(10)

    # 点击“按房屋总价”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup[2]/android.widget.ScrollView/android.view.ViewGroup/android.widget.TextView[3]").click()
    sleep(10)

    # 输入“房屋总价”为500
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup[2]/android.widget.ScrollView/android.view.ViewGroup/android.widget.EditText[1]").send_keys("500")
    sleep(10)

    # 点击“开始计算”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup[2]/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.widget.TextView").click()
    sleep(10)

    # 点击“查看历史” !!!!!! “查看历史”点不动 怀疑是bug !!!!!!
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup[2]/android.widget.ScrollView/android.view.ViewGroup/android.view.ViewGroup[1]/android.widget.ImageView[3]").click()
    sleep(10)

    # ##################### 4 #####################
    # 返回“新房”页面
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup/android.view.ViewGroup[1]/android.view.ViewGroup[1]/android.widget.ImageView").click()
    sleep(10)

    # 点击第一条房源
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.RelativeLayout/android.view.ViewGroup/android.widget.RelativeLayout/android.widget.FrameLayout/android.widget.RelativeLayout/androidx.recyclerview.widget.RecyclerView/android.view.ViewGroup[1]/android.view.ViewGroup[2]/android.widget.LinearLayout/android.widget.TextView[2]").click()
    sleep(8)

    # 有广告 上滑
    driver.swipe(x2, y2, x2, y1, 500)
    sleep(3)

    # 点击“变价通知”
    driver.find_element_by_id("com.anjuke.android.app:id/bianJiaTextView").click()
    sleep(8)

    # 点击“我知道了”
    driver.find_element_by_id("com.anjuke.android.app:id/confirmButton").click()
    sleep(8)

    # 点击“关注” 其实点了变价通知就自动关注了 但是我还是点一下
    driver.find_element_by_id("com.anjuke.android.app:id/followIcon").click()
    sleep(8)

    # 为了能点“对比” 上滑
    driver.swipe(x2, y2, x2, y1, 500)
    sleep(3)
    driver.swipe(x2, y2, x2, y1, 500)
    sleep(3)

    # 点击右上角“对比”
    driver.find_element_by_id("com.anjuke.android.app:id/compareImageView").click()
    sleep(8)

    # 原文档要点击左上角“比价” 但并没有这个选项 跳过

    # 选择“猜你喜欢”的前两套房源
    # 它总是根据我的浏览记录推荐很多东西把那个栏目遮住了
    # 我试了下滑但还是不能准确选中 干脆随便选两个 >=|=>
    # driver.swipe(x2, size['height'] - 200, x2, size['height'] - 1740, 500)
    # sleep(3)
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.view.ViewGroup/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.RelativeLayout/androidx.recyclerview.widget.RecyclerView/android.view.ViewGroup[3]/android.widget.RadioButton").click()
    sleep(8)
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.view.ViewGroup/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.RelativeLayout/androidx.recyclerview.widget.RecyclerView/android.view.ViewGroup[5]/android.widget.RadioButton").click()
    sleep(8)

    # 点击“开始对比”
    driver.find_element_by_id("com.anjuke.android.app:id/new_house_building_compare_list_begin_compare").click()
    sleep(8)

    # ##################### 5 #####################
    # 返回主页面
    driver.swipe(x0, y4, x2, y4, 500)
    sleep(8)
    driver.swipe(x0, y4, x2, y4, 500)
    sleep(8)
    driver.swipe(x0, y4, x2, y4, 500)
    sleep(8)
    driver.swipe(x0, y4, x2, y4, 500)
    sleep(8)

    # 点击“消息”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.TabWidget/android.widget.RelativeLayout[2]").click()
    sleep(8)

    # 点击第一个“热门去聊”去围观
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/androidx.viewpager.widget.ViewPager/android.widget.LinearLayout/androidx.viewpager.widget.ViewPager/android.widget.FrameLayout/android.widget.FrameLayout[1]/androidx.recyclerview.widget.RecyclerView/android.widget.LinearLayout[1]/android.widget.RelativeLayout/android.widget.Button").click()
    sleep(8)
    driver.find_element_by_xpath("//android.widget.ImageButton[@content-desc=\"nothing\"]").click()
    sleep(8)

    # 点击“优秀置业顾问”微聊
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/androidx.viewpager.widget.ViewPager/android.widget.LinearLayout/androidx.viewpager.widget.ViewPager/android.widget.FrameLayout/android.widget.FrameLayout[1]/androidx.recyclerview.widget.RecyclerView/android.widget.LinearLayout[4]/android.widget.RelativeLayout/android.widget.Button").click()
    sleep(8)
    driver.swipe(x0, y4, x2, y4, 500)
    sleep(10)

    # ##################### 6 #####################
    # 点击“有料”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.TabWidget/android.widget.RelativeLayout[3]").click()
    sleep(8)

    # 遍历“推荐”一栏五项
    for i in range(1, 6):
        driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.TabWidget/android.widget.RelativeLayout[" + str(i) + "]").click()
        sleep(8)

    # ##################### 7 #####################
    # 先回“消息”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.TabWidget/android.widget.RelativeLayout[3]").click()
    sleep(8)

    # 点击问答模块
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/androidx.viewpager.widget.ViewPager/android.widget.FrameLayout/android.widget.LinearLayout/android.view.ViewGroup/android.widget.RelativeLayout/android.widget.LinearLayout/android.widget.RelativeLayout/android.widget.HorizontalScrollView/android.widget.LinearLayout/android.widget.LinearLayout[3]/android.widget.LinearLayout/android.widget.TextView").click()
    sleep(8)

    # 点击“我要提问”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/androidx.viewpager.widget.ViewPager/android.widget.FrameLayout/android.widget.LinearLayout/android.view.ViewGroup/android.widget.RelativeLayout/android.widget.LinearLayout/androidx.viewpager.widget.ViewPager/android.widget.FrameLayout/android.widget.RelativeLayout/android.widget.FrameLayout/android.view.ViewGroup/android.widget.RelativeLayout/android.view.ViewGroup/android.widget.TextView").click()
    sleep(8)

    # 输入“南大和园多少钱一平方”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.RelativeLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.RelativeLayout/android.widget.RelativeLayout/android.view.ViewGroup/android.widget.FrameLayout/android.webkit.WebView/android.webkit.WebView/android.view.View/android.view.View/android.view.View[3]/android.widget.EditText").send_keys("南大和园多少钱一平方")
    sleep(8)

    # 点击“提交” 点“提交”要钱 我点完直接返回
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.RelativeLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.RelativeLayout/android.widget.RelativeLayout/android.view.ViewGroup/android.widget.FrameLayout/android.webkit.WebView/android.webkit.WebView/android.view.View/android.view.View/android.view.View[9]/android.view.View[2]").click()
    sleep(8)
    driver.swipe(x0, y4, x2, y4, 500)
    sleep(5)

    # ##################### 8 #####################
    # 点击“推荐”
    driver.find_element_by_xpath("/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/android.widget.TabWidget/android.widget.RelativeLayout[4]").click()
    sleep(8)

    # 从左往右 遍历顶部栏模块
    driver.swipe(x0, y3, x2, y3, 500)
    sleep(8)
    for i in range(1, 8):
            m_xpath = "/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/androidx.viewpager.widget.ViewPager/android.widget.RelativeLayout/android.widget.RelativeLayout/android.widget.HorizontalScrollView/android.widget.LinearLayout/android.widget.RelativeLayout[" + str(i) + "]/android.widget.TextView"
            if(i == 2):
                m_xpath += ("[" + str(1) + "]")
            if(i == 6):
                m_xpath = "/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/androidx.viewpager.widget.ViewPager/android.widget.RelativeLayout/android.widget.RelativeLayout/android.widget.HorizontalScrollView/android.widget.LinearLayout/android.widget.RelativeLayout[" + str(5) + "]/android.widget.TextView"
            if(i == 7):
                m_xpath = "/hierarchy/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.LinearLayout/android.widget.FrameLayout/android.widget.FrameLayout/androidx.viewpager.widget.ViewPager/android.widget.RelativeLayout/android.widget.RelativeLayout/android.widget.HorizontalScrollView/android.widget.LinearLayout/android.widget.RelativeLayout[" + str(6) + "]/android.widget.TextView"
            driver.find_element_by_xpath(m_xpath).click()
            sleep(8)


if __name__ == "__main__":
    anjukeMobileTest()