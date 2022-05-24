package exercise4.bean;

import java.util.Date;

/**
 * 项目列表基类
 *
 * @author 梁芮槐-2019302789
 */
public class ToDoList {

    private int ID;

    private String creator;

    private Date startTime;
    private Date endTime;

    private String title;

    /**
     * 默认构造函数
     */
    public ToDoList() {
    }

    /**
     * 构造函数
     *
     * @param ID        项目ID
     * @param creator   创建者
     * @param startTime 开始时间
     * @param endTime   结束时间
     * @param title     项目标题
     */
    public ToDoList(int ID, String creator, Date startTime, Date endTime, String title) {
        super();
        this.ID = ID;
        this.creator = creator;
        this.startTime = startTime;
        this.endTime = endTime;
        this.title = title;
    }

    /**
     * 获取创建者名称
     *
     * @return 创建者名称
     */
    public String getCreator() {
        return creator;
    }

    /**
     * 设置创建者名称
     *
     * @param creator 创建者名称
     */
    public void setCreator(String creator) {
        this.creator = creator;
    }

    /**
     * 获取项目ID
     *
     * @return 项目ID
     */
    public int getID() {
        return ID;
    }

    /**
     * 设置项目ID
     *
     * @param ID 项目ID
     */
    public void setID(int ID) {
        this.ID = ID;
    }

    /**
     * 获取项目开始时间
     *
     * @return 项目开始时间
     */
    public Date getStartTime() {
        return startTime;
    }

    /**
     * 设置项目开始时间
     *
     * @param date 项目开始时间
     */
    public void setStartTime(Date date) {
        this.startTime = date;
    }

    /**
     * 获取项目结束时间
     *
     * @return 项目结束时间
     */
    public Date getEndTime() {
        return endTime;
    }

    /**
     * 设置项目结束时间
     *
     * @param date 项目结束时间
     */
    public void setEndTime(Date date) {
        this.endTime = date;
    }

    /**
     * 获取项目标题
     *
     * @return 项目标题
     */
    public String getTitle() {
        return title;
    }

    /**
     * 设置项目标题
     *
     * @param title 项目标题
     */
    public void setTitle(String title) {
        this.title = title;
    }

    @Override
    public String toString() {
        return "TO DO LIST: ID=" + ID + ", creator=" + creator + ", title=" + title + "\n"
                + "from " + startTime + " to " + endTime;
    }

}
