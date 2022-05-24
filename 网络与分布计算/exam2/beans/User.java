package exam2.beans;

import java.io.Serializable;

/**
 * 用户主类
 * 
 * @author 梁芮槐-2019302789
 */
public class User implements Serializable {

	private String name;
	private String password;
	
	/**
	 * 默认构造函数
	 */
	public User() {}

	/**
	 * 构造函数
	 * @param name 用户名
	 * @param password 密码
	 */
	public User(String name, String password) {
		super();
		this.name = name;
		this.password = password;
		
	}

    /**
     * 获取用户名
     * @return 用户名
     */
	public String getName() {
		return name;
	}

    /**
     * 设置用户名
     * @param name 用户名
     */
	public void setName(String name) {
		this.name = name;
	}

    /**
     * 获取密码
     * @return 密码
     */
	public String getPassword() {
		return password;
	}

    /**
     * 设置密码
     * @param password 用户名
     */
	public void setPassword(String password) {
		this.password = password;
	}

    /**
     * 将用户名转化为易读输出
     * @return 易读用户输出
     */
	@Override
	public String toString() {
		return "User \"" + name + "\"";
	}
}
