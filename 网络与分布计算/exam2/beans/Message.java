package exam2.beans;

import java.io.Serializable;

/**
 * 消息主类
 * 
 * @author 梁芮槐-2019302789
 */
public class Message implements Serializable {
    private String content;
    private String senderName;
    private String receiverName;

    /**
     * 构造函数
     * 
     * @param content 消息内容
     * @param senderName 发送者用户名
     * @param receiverName 接收者用户名
     */
    public Message(String senderName, String receiverName, String content) {
        this.senderName = senderName;
        this.receiverName = receiverName;
        this.content = content;
    }

    /**
     * 获取消息内容
     * 
     * @return 消息内容
     */
    public String getContent() {
        return content;
    }

    /**
     * 设置消息内容
     * 
     * @param content 消息内容
     */
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * 获取发送者用户名
     * 
     * @return 发送者用户名
     */
    public String getSenderName() {
        return senderName;
    }

    /**
     * 设置发送者用户名
     * 
     * @param senderName 发送者用户名
     */
    public void setSenderName(String senderName) {
        this.senderName = senderName;
    }

    /**
     * 获取接收者用户名
     * 
     * @return 接收者用户名
     */
    public String getReceiverName() {
        return receiverName;
    }

    /**
     * 设置接收者用户名
     * 
     * @param receiverName 接收者用户名
     */
    public void setReceiverName(String receiverName) {
        this.receiverName = receiverName;
    }

    /**
     * 将消息转换成易读输出
     * 
     * @return 易读输出
     */
    @Override
    public String toString() {
        return senderName + "->" + receiverName + ", content:\n" + content;
    }
}
