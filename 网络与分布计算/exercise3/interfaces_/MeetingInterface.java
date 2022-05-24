package exercise3.interfaces_;

import exercise3.beans.Meeting;
import exercise3.beans.User;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Date;


/**
 * Meeting的远程方法声明接口类
 * 
 * @author 梁芮槐-2019302789
 */
public interface MeetingInterface extends Remote {

	/**
	 * 按照时间对所有会议进行排序
     * 
	 * @param startTime 会议开始时间
	 * @param endTime 会议结束时间
	 * @param user 操作者
     * 
	 * @return 排序后的会议列表
     * 
	 * @throws RemoteException
	 */
	ArrayList<Meeting> queryByTime(Date startTime, Date endTime, User user)
			throws RemoteException;

	/**
	 * 添加会议
     * 
	 * @param meeting 会议
	 * @param user 操作者
     * 
	 * @return 是否添加成功
     * 
	 * @throws RemoteException
	 */
	boolean addMeeting(Meeting meeting, User user) throws RemoteException;

	/**
	 * 清空所有该操作者创建的会议
	 * 
	 * @param usr 操作者
     * 
	 * @throws RemoteException
	 */
	void clearMeeting(User user) throws RemoteException;

	/**
	 * 通过会议ID查找并删除会议
     * 
	 * @param meetingID 会议ID
	 * @param user 执行此操作的用户
     * 
	 * @return 是否找到并删除
     * 
	 * @throws RemoteException
	 */
	boolean deleteById(int meetingID, User user) throws RemoteException;

	/**
	 * 查询当前会议的列表
     * 
	 * @return 会议列表
     * 
	 * @throws RemoteException
	 */
	ArrayList<Meeting> getMeetingList() throws RemoteException;

}
