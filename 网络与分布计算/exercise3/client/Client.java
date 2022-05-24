package exercise3.client;

import exercise3.beans.User;
import exercise3.interfaces_.MeetingInterface;
import exercise3.interfaces_.UserInterface;
import exercise3.beans.Meeting;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

/**
 * 客户端主进程类
 * 
 * @author 梁芮槐-2019302789
 */
public class Client {

	static Meeting meeting;
	static int meetingID = 0;
	static User user;
	static MeetingInterface meetingInterface;
	static UserInterface userInterface;
	static SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd/HH:mm"); // ex. 2021-10-16/17:17
	static boolean success;
	static Scanner scanner = new Scanner(System.in);
	static String[] myArgs;

	/**
	 * 构造函数
	 * 
	 * @param args 初始化参数
	 * 
	 * @throws RemoteException
	 * @throws MalformedURLException
	 * @throws NotBoundException
	 * @throws ParseException
	 */
	public Client(String[] args) throws RemoteException, MalformedURLException, 
										NotBoundException, ParseException {
		String str = "//" + args[0] + ":" + args[1] + "/MeetingRemote";
		meetingInterface = (MeetingInterface)Naming.lookup(str);
		str = "//" + args[0] + ":" + args[1] + "/UserRemote";
		userInterface = (UserInterface)Naming.lookup(str);

		String name = args[3];
		String password = args[4];
		user = new User(name, password);
		if(args[2].equals("register")) {
			if(userInterface.addUser(user)) {
				success = true;
				// 如果用户存在且密码输入正确就直接登录
				System.out.println("Successfully registered/login " + user.toString());
			} else {
				success = false;
				// 如果用户存在但密码输入错误就报错
				System.out.println(user.toString() + " already exists or password is wrong !");
			}
		} else if (args[2].equals("login")) {
			if(userInterface.getUserByName(name) == null) {
				success = false;
				System.err.println(user.toString() + " not fount !");
			} else {
				success = true;
				System.out.println("Successfully logged in.");
			}
		}
	}

	/**
	 * 主函数
	 * 
	 * @param args 命令行参数
	 * 
	 * @throws RemoteException
	 * @throws ParseException
	 * @throws NotBoundException
	 * @throws MalformedURLException
	 */
	public static void main(String[] args) throws RemoteException, MalformedURLException, 
												NotBoundException, ParseException {
		if(args.length != 5) {
			System.out.println("Usage: java [Client] [servername] [portnumber] register/login [username] [password]");
			return;
		}
		Client client = new Client(args);
		client.handle();
	}

	/**
	 * 主处理函数
	 * 
	 * @throws RemoteException
	 * @throws ParseException
	 */
	public void handle() throws RemoteException, ParseException {
		if(!success) return;
		String line;
		boolean quit = false;
		while(!quit) {
			printMenu();
			line = scanner.nextLine();
			// System.out.println("Get cmd=" + line);
			myArgs = line.split(" ");
			if(myArgs.length == 0) continue;
			if(myArgs[0].equals("add")) {
				addMeeting();
			} else if (myArgs[0].equals("delete")) {
				deleteMeeting();
			} else if (myArgs[0].equals("clear")) {
				clearMeeting();
			} else if (myArgs[0].equals("query")) {
				queryMeeting();
			} else if (myArgs[0].equals("quit")) {
				quit = true;
			} else {
				System.out.println("Unknown cmd !");
			}
		}
	}

	/**
	 * 添加会议
	 * 
	 * @throws RemoteException
	 */
	public static void addMeeting() throws RemoteException {
		if(myArgs.length < 5) {
			System.err.println("Unknown params !");
		} else {
			try {
				Date start = format.parse(myArgs[myArgs.length - 3]);
				Date end = format.parse(myArgs[myArgs.length - 2]);

				if (start.after(end) || start.equals(end)) {
					System.err.println("End time should be after start time !");
					return;
				}
				ArrayList<User> participants = new ArrayList<User>();
				User participant;
				int index = 1;
				participants.add(user);
				while(index < myArgs.length - 3) {
					participant = userInterface.getUserByName(myArgs[index]);
					if(participant == null) {
						System.err.println("User \"" + myArgs[index] + "\" not found !");
						return;
					} else {
						participants.add(participant);
						System.out.println("Found user \"" + myArgs[index] + "\"");
					}
					index++;
				}
				String title = myArgs[myArgs.length - 1];
				meeting = new Meeting(meetingID, start, end, title, participants);
				if (!meetingInterface.addMeeting(meeting, user)) {
					System.err.println("Time conflicted !");
					return;
				} else {
					meetingID++;
					System.out.println("Successfully added " + meeting.toString());
				}
			} catch (ParseException e) {
				System.err.println("Unknown date format !");
				return;
			}
		}
	}
	
	/**
	 * 删除会议
	 * 
	 * @throws RemoteException
	 */
	public static void deleteMeeting() throws RemoteException {
		if (myArgs.length != 2) {
			System.err.println("Unknow params !");
		} else {
			int id = Integer.parseInt(myArgs[1]);
			boolean deleteSuccess = meetingInterface.deleteById(id, user);
			if (deleteSuccess) {
				System.out.println("Deleted meeting[" + myArgs[1] + "]");
			} else {
				System.err.println("Meeting [" + myArgs[1] + "] not found or you have not right to delete it !");
			}
		}
	}

	/**
	 * 清除所有会议
	 * 
	 * @throws RemoteException
	 */
	public static void clearMeeting() throws RemoteException {
		if(myArgs.length != 1) {
			System.err.println("Unknow params !");
			return;
		}
		meetingInterface.clearMeeting(user);
	}

	/**
	 * 查询会议
	 * 
	 * @throws RemoteException
	 */
	public static void queryMeeting() throws RemoteException {
		ArrayList<Meeting> meetingList;
		if (myArgs.length != 3) {
			System.err.println("Unknown params !");
			return;
		} else {
			try {
				Date start = format.parse(myArgs[1]);
				Date end = format.parse(myArgs[2]);

				if(start.after(end) || start.equals(end)) {
					System.err.println("End time should be after start time !");
					return;
				}
				meetingList = meetingInterface.queryByTime(start, end, user);
				if(meetingList == null) {
					System.out.println("None meeting !");
					return;
				} else {
					for (Meeting i : meetingList) {
						System.out.println(i.toString());
					}
				}
			} catch (ParseException e) {
				System.err.println("Unknown date format !");
				return;
			}
		}
	}

	/**
	 * 打印提示菜单
	 */
	public static void printMenu() {
		System.out.println("<------------------------>");
		System.out.println("RMI Menu: ");
		System.out.println("    1.add");
		System.out.println("        arguments: <username> <start> <end> <title> (enter time in this format \"2021-10-16/17:17\")");
		System.out.println("    2.delete");
		System.out.println("        arguments: meetingid");
		System.out.println("    3.clear");
		System.out.println("        arguments: no args");
		System.out.println("    4.query");
		System.out.println("        arguments: <start> <end> (enter time in this format \"2021-10-16/17:17\")");
		System.out.println("    5.quit");
		System.out.println("        arguments: no args");
	}
}
