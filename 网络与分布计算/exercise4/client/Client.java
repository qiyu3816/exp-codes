package exercise4.client;

import exercise4.service.MyWebService;
import exercise4.service.WebServerService;
import exercise4.service.User;
import exercise4.service.ToDoList;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

import javax.xml.datatype.DatatypeConfigurationException;
import javax.xml.datatype.DatatypeFactory;
import javax.xml.datatype.XMLGregorianCalendar;


/**
 * 客户端主类
 *
 * @author 梁芮槐-2019302789
 */
public class Client {

    private static SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd/HH:mm");
    private static User user = new User();
    private static WebServerService webService;
    private static MyWebService service;

    /**
     * 默认构造函数
     */
    public Client() {}

    /**
     * 主程序入口
     *
     * @param args 命令行参数
     */
    public static void main(String[] args) {
        webService = new WebServerService();
        service = webService.getMyWebServicePort();
        System.out.println("Client successfully obtained the WebService port.");

        Scanner in = new Scanner(System.in);
        System.out.println("Registering for...");
        while (true) {
            System.out.println("Please enter the user name");
            String username = in.nextLine();
            System.out.println("Please enter your password.");
            String password = in.nextLine();
            user.setUsername(username);
            user.setPassword(password);
            if (service.userRegister(user)) {
                System.out.println("Registered/Logined successfully.");
                break;
            } else {
                System.err.println("Registration failed, the user name already exists !");
            }
        }

        int quit = 0;
        while (true) {
            printHelp();
            String command = in.nextLine();
            quit = handle(command);
            if (quit == 1) {
                break;
            }
        }
        in.close();
    }

    /**
     * 处理命令
     *
     * @param line 命令
     * @return 处理状态
     */
    public static int handle(String line) {
        if (line.equals("quit")) {
            System.out.println("Bye");
            return 1;
        } else if (line.equals("help")) {
            printHelp();
            return 0;
        } else if (line.startsWith("add")) {
            addItem(line);
            return 0;
        } else if (line.startsWith("query")) {
            queryItem(line);
            return 0;
        } else if (line.startsWith("delete")) {
            deleteItem(line);
            return 0;
        } else if (line.equals("clear")) {
            service.clearItem(user.getUsername());
            System.out.println("Empty completed.");
            return 0;
        } else {
            System.err.println("Illegal command");
            return 0;
        }
    }

    /**
     * 添加项目
     *
     * @param line 命令
     */
    public static void addItem(String line) {
        String[] command = line.split(" ");
        if (command.length != 4) {
            System.err.println("Parameter number error !");
        } else if (!command[0].equals("add")) {
            System.err.println("Illegal command !");
        } else {
            try {
                Date start = format.parse(command[1]);
                Date end = format.parse(command[2]);

                if (start.before(end)) {
                    ToDoList item = new ToDoList();
                    item.setCreator(user.getUsername());
                    item.setStartTime(transform(start));
                    item.setEndTime(transform(end));
                    item.setTitle(command[3]);
                    if (service.addItem(user.getUsername(), item)) {
                        String str = "TO DO LIST: ID=" + item.getID() + ", creator=" + item.getCreator() + ", title=" + item.getTitle() + "\n"
                                + "from " + item.getStartTime() + " to " + item.getEndTime();
                        System.out.println("Successfully added." + "\n" + str);
                    } else {
                        System.err.println("Failed to add because of conflicted time !");
                    }
                } else {
                    System.err.println("Start time must before end time !");
                }
            } catch (ParseException e) {
                System.err.println("Date format resolution error !");
            }
        }
    }

    /**
     * 处理排序展示
     *
     * @param line 命令
     */
    public static void queryItem(String line) {
        String[] command = line.split(" ");
        if (command.length != 3) {
            System.err.println("Parameter number error !");
            return;
        } else if (!command[0].equals("query")) {
            System.err.println("Illegal command !");
            return;
        } else {
            try {
                Date start = format.parse(command[1]);
                Date end = format.parse(command[2]);
                if (!start.before(end)) {
                    System.err.println("Start time must before end time !");
                    return;
                }
                List<ToDoList> result = new ArrayList<ToDoList>();
                result = service.queryItem(user.getUsername(), transform(start), transform(end));
                if (result.isEmpty()) {
                    System.out.println("None item !");
                    return;
                } else {
                    for (ToDoList i : result) {
                        String str = "TO DO LIST: ID=" + i.getID() + ", creator=" + i.getCreator() + ", title=" + i.getTitle() + "\n"
                                + "from " + i.getStartTime() + " to " + i.getEndTime();
                        System.out.println(str);
                    }
                    return;
                }
            } catch (ParseException e) {
                System.err.println("Date format resolution error !");
            }

        }
    }

    /**
     * 将Date转换为XMLGregorianCalendar类型
     *
     * @param date 输入日期
     * @return 处理后的日期
     */
    public static XMLGregorianCalendar transform(Date date) {
        XMLGregorianCalendar result = null;
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date);
        try {
            DatatypeFactory factory = DatatypeFactory.newInstance();
            result = factory.newXMLGregorianCalendar();
            result.setYear(calendar.get(Calendar.YEAR));
            result.setMonth(calendar.get(Calendar.MONTH) + 1);
            result.setDay(calendar.get(Calendar.DAY_OF_MONTH));
            result.setHour(calendar.get(Calendar.HOUR_OF_DAY));
            result.setMinute(calendar.get(Calendar.MINUTE));
            result.setSecond(calendar.get(Calendar.SECOND));
            return result;
        } catch (DatatypeConfigurationException e) {
            e.printStackTrace();
        }
        return null;
    }

    /**
     * 处理删除命令
     *
     * @param line 命令
     */
    public static void deleteItem(String line) {
        String[] command = line.split(" ");
        if (command.length != 2) {
            System.err.println("Parameter number error !");
        } else if (!command[0].equals("delete")) {
            System.err.println("Illegal command !");
        } else {
            int id = Integer.parseInt(command[1]);
            if (service.deleteItem(user.getUsername(), id)) {
                System.out.println("Deleted successfully.");
            } else {
                System.err.println("Failed to delete !");
            }
        }
    }

    /**
     * 输出菜单提示
     */
    public static void printHelp() {
        System.out.println();
        System.out.println("Web Menu");
        System.out.println("1.add:");
        System.out.println("<startTime> <endTime> <title> timeFormat:year-month-day/hour:min");
        System.out.println("2.query:");
        System.out.println("<startTime> <endTime>");
        System.out.println("3.delete:");
        System.out.println("<itemID>");
        System.out.println("4.clear:");
        System.out.println("5.quit:");
    }

}
