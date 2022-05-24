# coding:utf-8
def Main():
      print 'Hello world'
      import time
      seekresult=TCP服务端_服务器.Clear()
      开关锁指令.服务器开关锁指令.Value = 0x0 #先开锁
      bool=开关锁指令.Write()
      开关锁指令反馈和行程信息.BlockRead()
      开关锁指令.服务器开关锁指令.Value = 0xFFFFFFFF #关锁指令
      bool=开关锁指令.Write()
      time0=time.time()
      while 1:
            bool = 开关锁指令反馈和行程信息.Read()
            if bool and 开关锁指令反馈和行程信息.负载.Case1.结果值.Value == 0:
                  print '开锁状态下关锁，测试通过'
                  break
            time1=time.time()
            if time1-time0>2:
                 print '开锁状态下关锁，测试不通过'
                 break
      
      开关锁指令.服务器开关锁指令.Value = 0xFFFFFFFF #关锁指令
      bool=开关锁指令.Write()
      time0=time.time()
      while 1:
            bool = 开关锁指令反馈和行程信息.Read()
            #print 开关锁指令反馈和行程信息.负载.Case1.结果值.Value
            if bool and 开关锁指令反馈和行程信息.负载.Case1.结果值.Value == 1:
                  print '关锁状态下关锁，测试通过'
                  print 开关锁指令反馈和行程信息
                  break
            time1=time.time()
            if time1-time0>2:
                 print '关锁状态下关锁，测试不通过'
                 break
                 
Main()