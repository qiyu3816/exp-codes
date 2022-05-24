package exercise4.bean;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.xml.ws.Endpoint;

/**
 * Web服务器基类
 *
 * @author 梁芮槐-2019302789
 */
@WebService(name = "MyWebService", portName = "MyWebServicePort", targetNamespace = "http://www.service.com")
public class WebServer {
    private List<User> userList = new ArrayList<User>();
    private List<ToDoList> itemList = new ArrayList<ToDoList>();

    private int itemId = 0;

    /**
     * 默认构造函数
     */
    public WebServer() {}

    /**
     * 主函数入口
     *
     * @param args 命令行参数
     */
    public static void main(String[] args) {
        Endpoint.publish("http://127.0.0.1:8001/mywebservice/myservice", new WebServer());
        System.out.println("Server published successfully ---------->");
    }

    /**
     * 用户注册
     *
     * @param user 用户
     * @return 是否注册成功
     */
    @WebMethod
    public boolean userRegister(User user) {
        if (userList == null) {
            userList.add(user);
            return true;
        }
        for (User i : userList) {
            if (i.getUsername().equals(user.getUsername())) {
                if(i.getPassword().equals(user.getPassword())) {
                    return true;
                }
                return false;
            }
        }
        userList.add(user);
        return true;
    }

    /**
     * 添加代办项目
     *
     * @param creator 创建者
     * @param item    项目
     * @return 是否添加成功
     */
    @WebMethod
    public boolean addItem(String creator, ToDoList item) {
        ArrayList<ToDoList> list = new ArrayList<ToDoList>();
        for (ToDoList i : itemList) {
            if (i.getCreator().equals(creator)) {
                list.add(i);
            }
        }

        if (list.isEmpty()) {
            System.out.println(creator + " empty");
            itemId++;
            item.setID(itemId);
            itemList.add(item);
            return true;
        }

        Date start = item.getStartTime();
        Date end = item.getEndTime();

        for (ToDoList i : list) {
            if (start.before(i.getStartTime()) && end.after(i.getStartTime())) {
                return false;
            } else if (start.before(i.getEndTime()) && end.after(i.getEndTime())) {
                return false;
            } else if (start.after(i.getStartTime()) && end.before(i.getEndTime())) {
                return false;
            } else if (i.getStartTime().equals(start) && i.getEndTime().equals(end)) {
                return false;
            }
        }
        itemId++;
        item.setID(itemId);
        itemList.add(item);
        return true;
    }

    /**
     * 排序对应时间区间内的事项
     *
     * @param creator 创建者
     * @param start   开始时间
     * @param end     结束时间
     * @return 排序后的项目列表
     */
    @WebMethod
    public ArrayList<ToDoList> queryItem(String creator, Date start, Date end) {

        if (itemList.isEmpty()) {
            return null;
        }

        ArrayList<ToDoList> result = new ArrayList<ToDoList>();
        for (ToDoList i : itemList) {
            if (!start.after(i.getStartTime()) && !end.before(i.getEndTime()) && i.getCreator().equals(creator)) {
                result.add(i);
            }
        }

        if (result.isEmpty()) {
            return null;
        } else {
            return result;
        }
    }

    /**
     * 根据创建者和项目ID删除项目
     *
     * @param creator 创建者
     * @param id      项目ID
     * @return 是否删除成功
     */
    @WebMethod
    public boolean deleteItem(String creator, int id) {
        ToDoList deleted = null;

        for (ToDoList i : itemList) {
            if (i.getID() == id && i.getCreator().equals(creator)) {
                deleted = i;
                break;
            }
        }
        if (deleted == null) {
            return false;
        } else {
            itemList.remove(deleted);
            return true;
        }
    }

    /**
     * 清空目标用户的待办事项列表
     *
     * @param creator 创建者
     * @return 是否清空成功
     */
    @WebMethod
    public boolean clearItem(String creator) {
        ArrayList<ToDoList> deleteList = new ArrayList<ToDoList>();

        for (ToDoList i : itemList) {
            if (i.getCreator().equals(creator)) {
                deleteList.add(i);
            }
        }
        if (deleteList.isEmpty()) {
            return true;
        }
        for (ToDoList i : deleteList) {
            itemList.remove(i);
        }
        return true;
    }

}
