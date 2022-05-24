package exam2.client;

import exam2.beans.User;
import exam2.beans.Message;
import exam2.interfaces_.UserInterface;
import exam2.interfaces_.MessageInterface;
import exam2.implements_.UserImplement;
import exam2.implements_.MessageImplement;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.text.ParseException;
import java.util.ArrayList;

/**
 * 客户端主进程类
 * 
 * @author 梁芮槐-2019302789
 */
public class Client {

	static MessageInterface messageInterface;
	static UserInterface userInterface;
	static String[] myArgs;
	static String cmd;

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
										NotBoundException {
		String str = "//" + args[0] + ":" + args[1] + "/MessageRemote";
		messageInterface = (MessageInterface)Naming.lookup(str);
		str = "//" + args[0] + ":" + args[1] + "/UserRemote";
		userInterface = (UserInterface)Naming.lookup(str);
		
		myArgs = args;
		cmd = myArgs[2];
		handle();
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
												NotBoundException {
		if(args.length < 3) {
			printHelp();
			return;
		}
		Client client = new Client(args);
		printHelp();
	}

	/**
	 * 主处理函数
	 * 
	 * @throws RemoteException
	 * @throws ParseException
	 */
	public void handle() throws RemoteException {
		if(cmd.equals("register")) {
			register();
		} else if(cmd.equals("showusers")) {
			showUsers();
		} else if(cmd.equals("check")) {
			checkMessages();
		} else if (cmd.equals("leave")) {
			leaveMessage();
		} else {
			System.err.println("Unknown cmd !");
		}
	}

	/**
	 * 注册用户
	 * 
	 * @throws RemoteException
	 */
	public static void register() throws RemoteException {
		if(myArgs.length != 5){
			System.err.println("Unknown params !");
			return;
		}
		User user = new User(myArgs[3], myArgs[4]);
		if(userInterface.addUser(user)) {
			System.out.println("Successfully registered " + user.toString());
		} else {
			System.err.println(myArgs[3] + " already exists !");
		}
	}

	/**
	 * 查询用户列表
	 * 
	 * @throws RemoteException
	 */
	public static void showUsers() throws RemoteException {
		if(myArgs.length != 3) {
			System.err.println("Unknown params !");
			return;
		}
		ArrayList<User> users = userInterface.getUserList();
		if(users.isEmpty()) {
			System.err.println("None user !");
			return;
		}
		System.out.println("<--- UserList --->");
		for(User user:users) {
			System.out.println(user.toString() + "\n");
		}
		System.out.println("<---------------->");
	}

	/**
	 * 添加留言
	 * 
	 * @throws RemoteException
	 */
	public static void leaveMessage() throws RemoteException {
		if(myArgs.length != 7) {
			System.err.println("Unknown params !");
		} else {
			boolean validSender = false, validReceiver = false;
			ArrayList<User> users = userInterface.getUserList();
			for(User user:users) {
				if(user.getName().equals(myArgs[3]) && user.getPassword().equals(myArgs[4])) {
					validSender = true;
					continue;
				}
				if(user.getName().equals(myArgs[5])) {
					validReceiver = true;
					continue;
				}
			}
			if(!validSender) {
				System.out.println("Unknown sender !");
				return;
			}
			if(!validReceiver) {
				System.out.println("Unknown receiver !");
				return;
			}

			Message message = new Message(myArgs[3], myArgs[5], myArgs[6]);
			messageInterface.addMessage(message);
			System.out.println(myArgs[3] + " left message to " + myArgs[5] + " successfully.");
		}
	}
	
	/**
	 * 查询留言
	 * 
	 * @throws RemoteException
	 */
	public static void checkMessages() throws RemoteException {
		if (myArgs.length != 5) {
			System.err.println("Unknown params !");
			return;
		} else {
			boolean valid = false;
			ArrayList<User> users = userInterface.getUserList();
			for(User user:users) {
				if(user.getName().equals(myArgs[3]) && user.getPassword().equals(myArgs[4])) {
					valid = true;
					continue;
				}
			}
			if(!valid) {
				System.out.println("Unknown user !");
				return;
			}

			ArrayList<Message> messages = messageInterface.getMessageList();
			ArrayList<Message> recv = new ArrayList<Message>();
			ArrayList<Message> send = new ArrayList<Message>();
			for(Message message:messages) {
				if(message.getReceiverName().equals(myArgs[3])) {
					recv.add(message);
				} else if(message.getSenderName().equals(myArgs[3])) {
					send.add(message);
				}
			}

			System.out.println("<---------->recv: ");
			for(Message message:recv) {
				System.out.println(message.toString());
			}
			System.out.println("<---------->send: ");
			for(Message message:send) {
				System.out.println(message.toString());
			}
		}
	}


	/**
	 * 打印命令帮助
	 */
	public static void printHelp() {
		System.out.println("Usage: \n" + 
							"java [Client] [servername] [portnumber] register [username] [password]\n" + 
							"java [Client] [servername] [portnumber] showusers\n" + 
							"java [Client] [servername] [portnumber] check [username] [password]\n" + 
							"java [Client] [servername] [portnumber] leave [username] [password] [receivername] [content]\n");
	}
}
