package exam2.server;

import exam2.interfaces_.UserInterface;
import exam2.interfaces_.MessageInterface;
import exam2.implements_.UserImplement;
import exam2.implements_.MessageImplement;

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

	    UserInterface userInterface = new UserImplement();
	    MessageInterface messageInterface = new MessageImplement();
		
	    LocateRegistry.createRegistry(1099);

	    Naming.rebind("//127.0.0.1:1099/UserRemote", userInterface);
	    Naming.rebind("//127.0.0.1:1099/MessageRemote", messageInterface);
	    
	    System.out.println("remote objects binded ---------->");
	}
}
