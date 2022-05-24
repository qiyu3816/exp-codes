package exercise3.beans;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;

/**
 * 会议主类
 * 
 * @author 梁芮槐-2019302789
 */
public class Meeting implements Serializable {
	private int meetingId;
	private Date startTime;
	private Date endTime;
	private String title;
	private ArrayList<User> participants = new ArrayList<User>();

	/**
	 * 默认构造函数
	 */
	public Meeting() {}

	/**
	 * 构造函数
     * 
	 * @param meetingId 会议ID
	 * @param startTime 会议开始时间
	 * @param endTime 会议结束时间
	 * @param title 会议标题
	 * @param participants 与会者
	 */
	public Meeting(int meetingId, Date startTime, Date endTime, String title, 
                    ArrayList<User> participants) {
		super();
		this.meetingId = meetingId;
		this.startTime = startTime;
		this.endTime = endTime;
		this.title = title;
		this.participants = participants;
	}

    /**
     * 获取会议ID
     * @return 会议ID
     */
	public int getMeetingId() {
		return meetingId;
	}

    /**
     * 设置会议ID
     * @param meetingId 会议ID
     */
	public void setMeetingId(int meetingId) {
		this.meetingId = meetingId;
	}

    /**
     * 获取会议开始时间
     * @return 会议开始时间
     */
	public Date getStartTime() {
		return startTime;
	}

    /**
     * 设置会议开始时间
     * @param startTime 开始时间
     */
	public void setStartTime(Date startTime) {
		this.startTime = startTime;
	}

    /**
     * 获取会议结束时间
     * @return 会议结束时间
     */
	public Date getEndTime() {
		return endTime;
	}

    /**
     * 设置会议结束时间
     * @param endTime 会议结束时间
     */
	public void setEndTime(Date endTime) {
		this.endTime = endTime;
	}

    /**
     * 获取会议标题
     * @return 会议标题
     */
	public String getTitle() {
		return title;
	}

    /**
     * 设置会议标题
     * @param title 会议标题
     */
	public void setTitle(String title) {
		this.title = title;
	}

    /**
     * 获取与会者列表
     * @return 与会者列表
     */
	public ArrayList<User> getParticipants() {
		return participants;
	}

    /**
     * 设置与会者
     * @param participants 与会者
     */
	public void setParticipants(ArrayList<User> participants) {
		this.participants = participants;
	}

    /**
     * 将会议转成易读字符串
     */
	@Override
	public String toString() {
		return "Meeting \"" + this.title + "\""
                + " ID=" + this.meetingId
                + "\nstartTime=" + this.startTime
                + "\nendTime=" + this.endTime
                + "\nparticipants: " + this.participants;
	}
	
}
