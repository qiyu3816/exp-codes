# coding:utf-8
def Main():
      import time
      print 'Hello world'
      seekresult=TCP服务端_服务器.Clear()
      # 开关锁指令.服务器开关锁指令.Value = 0xFFFFFFFF #关锁
      # bool=开关锁指令.Write()
      # 开关锁指令.服务器开关锁指令.Value = 0 #开锁
      # bool=开关锁指令.Write()
      f = 0 #费用
      time0 = time.time()
      for i in range(50):
           bool=开关锁指令反馈和行程信息.BlockRead() 
#           print 开关锁指令反馈和行程信息.标识.Value
           if 开关锁指令反馈和行程信息.标识.Value ==2:
                 time1 = time.time()
                 timeS = 开关锁指令反馈和行程信息.负载.Case2.行驶时长.Value
                 # timeS = time1-time0
                 if timeS < 300:
                       s=int( (timeS)/60)+1
                 else :
                       s=5
                 print '计费时间：%s，预期费用%d，实际费用：%s'%(timeS,s,开关锁指令反馈和行程信息.负载.Case2.费用.Value)
           API.Common.Timer.Normal.Sleep(300)
         
Main()
