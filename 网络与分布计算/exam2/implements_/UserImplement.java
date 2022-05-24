package exam2.implements_;

import exam2.beans.User;
import exam2.interfaces_.UserInterface;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

/**
 * UserInterface的远程方法实现类
 * 
 * @author 梁芮槐-2019302789
 */
public class UserImplement extends UnicastRemoteObject implements UserInterface {

	private static final long serialVersionUID = 1L;
	private ArrayList<User> userList = new ArrayList<User>();

	/**
	 * 构造函数
	 * @throws RemoteException
	 */
	public UserImplement() throws RemoteException {}

    /**
     * 所有获取用户列表
     * 
     * @return 用户列表
     * 
     * @throws RemoteException
     */
	@Override
	public ArrayList<User> getUserList() throws RemoteException {
		return this.userList;
	}

    /**
     * 通过用户名获取用户
     * 
     * @param name 用户名
     * 
     * @return 用户
     * 
     * @throws RemoteException
     */
	@Override
	public User getUserByName(String name) throws RemoteException {
		for(User user:userList) {
			if(user.getName().equals(name)) {
				return user;
			}
		}
		return null;
	}

    /**
     * 添加用户
     * 
     * @param user 用户
     * 
     * @return 是否添加成功
     * 
     * @throws RemoteException
     */
	@Override
	public boolean addUser(User user) throws RemoteException {
		for(User i:userList) {
			if(i.getName().equals(user.getName())) {
				return false;
			}
		}
		userList.add(user);
		return true;
	}

}
