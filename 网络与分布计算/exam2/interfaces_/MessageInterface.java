package exam2.interfaces_;

import exam2.beans.Message;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

/**
 * 留言方法声明接口类
 * 
 * @author 梁芮槐-2919302789
 */
public interface MessageInterface extends Remote {
    /**
	 * 添加留言
     * 
	 * @param message 留言
     * 
	 * @return 是否添加成功
     * 
	 * @throws RemoteException
	 */
	boolean addMessage(Message message) throws RemoteException;

	/**
	 * 获取留言列表
	 * 
	 * @return 留言列表
	 * 
	 * @throws RemoteException
	 */
	ArrayList<Message> getMessageList() throws RemoteException;
}
