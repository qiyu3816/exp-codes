package exercise3.server;

import exercise3.implements_.UserImplement;
import exercise3.interfaces_.MeetingInterface;
import exercise3.interfaces_.UserInterface;
import exercise3.implements_.MeetingImplement;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

/**
 * RMI 服务端主进程类
 * 
 * @author 梁芮槐-2019302789
 */
public class RMIServer {
	static boolean useYamlData = false;

	/**
	 * RMI 服务端主进程
	 * 
	 * @param args 命令行输入
	 * 
	 * @throws RemoteException
	 * @throws MalformedURLException
	 */
	public static void main(String[] args) throws RemoteException, MalformedURLException {

	    MeetingInterface meetingInterface = new MeetingImplement();
	    UserInterface userInterface = new UserImplement();
	
	    LocateRegistry.createRegistry(1099);
	    
	    Naming.rebind("//127.0.0.1:1099/MeetingRemote", meetingInterface);
	    Naming.rebind("//127.0.0.1:1099/UserRemote", userInterface);
	    
	    System.out.println("remote objects binded ---------->");
	}
}
