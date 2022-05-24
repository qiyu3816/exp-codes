package exercise3.interfaces_;

import exercise3.beans.User;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;


/**
 * User的远程方法声明接口类
 * 
 * @author 梁芮槐-2019302789
 */
public interface UserInterface extends Remote {

	/**
	 * 通过用户名获取用户
     * 
	 * @param name 用户名
     * 
	 * @return 用户
     * 
	 * @throws RemoteException
	 */
	public User getUserByName(String name) throws RemoteException;

	/**
	 * 添加用户
     * 
	 * @param user 用户
     * 
	 * @return 是否添加成功
     * 
	 * @throws RemoteException
	 */
	public boolean addUser(User user) throws RemoteException;

	/**
	 * 获取当前所有已注册用户的列表
     * 
	 * @return 用户列表
     * 
	 * @throws RemoteException
	 */
	public ArrayList<User> getUserList() throws RemoteException;
	
}
