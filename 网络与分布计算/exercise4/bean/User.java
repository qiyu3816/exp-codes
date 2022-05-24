package exercise4.bean;

/**
 * 用户基类
 *
 * @author 梁芮槐-2019302789
 */
public class User {

    private String username;
    private String password;

    /**
     * 默认构造函数
     */
    public User() {
    }

    /**
     * 构造函数
     *
     * @param username 用户名
     * @param password 密码
     */
    public User(String username, String password) {
        super();
        this.username = username;
        this.password = password;
    }

    /**
     * 获取用户名
     *
     * @return 用户名
     */
    public String getUsername() {
        return username;
    }

    /**
     * 设置用户名
     *
     * @param username 用户名
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * 获取密码
     *
     * @return 密码
     */
    public String getPassword() {
        return password;
    }

    /**
     * 设置密码
     *
     * @param password 密码
     */
    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "User [" + username + "]";
    }

}
