package exercise3.implements_;

import exercise3.beans.Meeting;
import exercise3.beans.User;
import exercise3.interfaces_.MeetingInterface;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Date;

/**
 * MeetingInterface的远程方法实现类
 * 
 * @author 梁芮槐-2019302789
 */
public class MeetingImplement extends UnicastRemoteObject implements MeetingInterface {
	private static final long serialVersionUID = 1L;
	private ArrayList<Meeting> meetingList = new ArrayList<Meeting>();

    /**
     * 默认构造函数
     * 
     * @throws RemoteException
     */
    public MeetingImplement() throws RemoteException {}

    /**
     * 获取所有会议列表
     * 
     * @return 会议列表
     * 
     * @throws RemoteException
     */
    @Override
    public ArrayList<Meeting> getMeetingList() throws RemoteException {
    	return this.meetingList;
    }

    /**
     * 根据跟定时间段查询会议列表
     * 
     * @param startTime 开始时间
     * @param endTime 结束时间
     * @param user 操作者
     *
     * @return 与给定时间段相关的按开始时间先后排序的会议列表
     * 
     * @throws RemoteException
     */
    @Override
    public ArrayList<Meeting> queryByTime(Date startTime, Date endTime, User user) throws RemoteException {

    	if(meetingList.isEmpty()) return null;
    	ArrayList<Meeting> inPeriod = new ArrayList<Meeting>();
    
        // 只有该用户处于会议中 且会议时间段被包含于给定时间段的会议纳入排序
        boolean inMeeting = false;
    	for(Meeting m:meetingList) {
            ArrayList<User> mParticipants = m.getParticipants();
            for(User u:mParticipants) {
                if(u.getName().equals(user.getName())) {
                    // System.out.println("inMeeting=true");
                    inMeeting = true;
                }
            }
    	    if(inMeeting) {
                if((m.getEndTime().before(endTime) && m.getStartTime().after(startTime)) || 
                    (m.getEndTime().after(startTime) && m.getStartTime().before(startTime)) ||
                    (m.getEndTime().after(endTime) && m.getStartTime().before(endTime))) {
                    inPeriod.add(m);
                }
                inMeeting = false;
            }
        }

    	if(inPeriod.isEmpty()) return null;
    
    	Meeting[] meetings = new Meeting[inPeriod.size()];
    	inPeriod.toArray(meetings);
    	Sort(meetings);
    	ArrayList<Meeting> result = new ArrayList<Meeting>();
    	for(int i = 0; i < inPeriod.size(); i++) {
    		result.add(meetings[i]);
    }
    	return result;
    }

    /**
     * 对会议列表进行从先到后排序
     * 
     * @param a 输入会议列表
     */
    private static void Sort(Meeting[] a) {
    	int length = a.length;
    	for(int i = 0; i < length - 1; i++) {
    		for(int j = 0; j < length - i - 1; j++) {
    			if(a[j].getStartTime().after(a[j + 1].getStartTime())) {
    				swap(a, j, j + 1);
    			}
    		}
    	}
    }

    /**
     * 交换会议列表中的对应两个元素
     *
     * @param list 输入列表
     * @param a 下标1
     * @param b 下标2
     */
    private static void swap(Meeting[] list, int a, int b) {
    	Meeting temp = list[a];
    	list[a] = list[b];
    	list[b] = temp;
    }

    /**
     * 添加会议
     * 
     * @param meeting 会议
     * 
     * @return 是否添加成功
     * 
     * @throws RemoteException
     */
    @Override
    public boolean addMeeting(Meeting meeting, User user) throws RemoteException {
    	Date start = meeting.getStartTime();
    	Date end = meeting.getEndTime();
    
        boolean conflictSign = false;
    	if(!meetingList.isEmpty()) {
    		for(Meeting m:meetingList) {
    			if(m.getStartTime().before(start) && m.getEndTime().after(start)) {
                    conflictSign = true;
                } else if (m.getStartTime().before(end) && m.getEndTime().after(end)) {
                    conflictSign = true;
                } else if (m.getStartTime().after(start) && m.getEndTime().before(end)) {
                    conflictSign = true;
                }
                if(conflictSign) {
                    ArrayList<User> users = meeting.getParticipants();
                    for(User u:users) {
                        ArrayList<User> users2 = m.getParticipants();
                        for(User u2:users2) {
                            if(u2.getName().equals(u.getName())) {
                                // System.out.println("Confirm false");
                                return false;
                            }
                        }
                    }
                }
    		}
    	}
    	this.meetingList.add(meeting);
        System.out.println("<------------------------>\n" + user.toString() + " added meeting: \n" + meeting.toString());
    	return true;
    }

    /**
     * 清空该操作者创建的所有会议
     * 
     * @param user 操作者
     * 
     * @return 会议列表
     * 
     * @throws RemoteException
     */
    @Override
    public void clearMeeting(User user) throws RemoteException {
        Meeting m;
    	for(int i = 0; i < this.meetingList.size(); i++) {
            m = meetingList.get(i);
            if(m.getParticipants().get(0).getName().equals(user.getName())) {
                System.out.println("<------------------------>\n" + user.toString() + " deleted meeting [" + m.getMeetingId() + "]");
                meetingList.remove(m);
                i--;
            }
        }
    }

    /**
     * 根据会议ID删除会议 只能删除操作者创建的会议
     * 
     * @param meetingID 会议ID
     * @param user 执行此操作的用户
     * 
     * @return 是否删除成功
     * 
     * @throws RemoteException
     */
    @Override
    public boolean deleteById(int meetingID, User user) throws RemoteException {
        for (Meeting m : meetingList) {
        	if (m.getMeetingId() == meetingID) {
        		ArrayList<User> users = m.getParticipants();
        		if(users.get(0).getName().equals(user.getName())) {
        			meetingList.remove(m);
                    System.out.println("<------------------------>\n" + user.toString() + " deleted meeting [" + meetingID + "]");
        			return true;
        		}
        	}
        }
        return false;
    }

}