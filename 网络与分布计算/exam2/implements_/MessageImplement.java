package exam2.implements_;

import exam2.beans.Message;
import exam2.interfaces_.MessageInterface;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

/**
 * 留言实现类
 * 
 * @author 梁芮槐-2019302789
 */
public class MessageImplement extends UnicastRemoteObject implements MessageInterface {
	private static final long serialVersionUID = 1L;
    private static ArrayList<Message> messages = new ArrayList<Message>();

    /**
     * 默认构造函数
     * 
     * @throws RemoteException
     */
    public MessageImplement() throws RemoteException {}

    /**
	 * 添加留言
     * 
	 * @param message 留言
     * 
	 * @return 是否添加成功
     * 
	 * @throws RemoteException
	 */
    @Override
    public boolean addMessage(Message message) throws RemoteException {
        messages.add(message);
        return false;
    }

    /**
	 * 获取留言列表
	 * 
	 * @return 留言列表
	 * 
	 * @throws RemoteException
	 */
    @Override
    public ArrayList<Message> getMessageList() throws RemoteException {
        return messages;
    }
}
