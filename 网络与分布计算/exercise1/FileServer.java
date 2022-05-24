package exercise1;

import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 服务器主类
 * 
 * @author 梁芮槐 2019302789
 */
public class FileServer {
    static final int TCP_PORT = 2021;

    Socket socket;
    ServerSocket serverSocket;
    static String rootDirectory;

    ExecutorService executorService;
    static final int POOL_SIZE = 4;

    /**
     * 构造函数
     * 
     * @param rootDirectory 获取root目录位置
     * 
     * @throws IOException
     */
    public FileServer(String rootDirectory) throws IOException {
        this.rootDirectory = rootDirectory;
        serverSocket = new ServerSocket(TCP_PORT);
        executorService = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors() * POOL_SIZE);
        System.out.println("server launched >>>>>>>>>");
    }

    /**
     * 服务器主函数
     * 
     * @param args 输入root文件夹位置
     * 
     * @throws IOException
     */
    public static void main(String[] args) throws IOException {
    	if(args.length != 1) {
            System.out.println("Input a param as the root directory!");
            return;
        }
        File checkRootPath = new File(args[0]);
        if(!(checkRootPath.exists() && checkRootPath.isAbsolute())) {
            System.out.println("Unknown root directory!");
            return;
        }
        new FileServer(args[0]).servive();
    }

    /**
     * 服务主循环 如果队列够 接收到新的连接请求就分离线程
     */
    public void servive(){
        while(true) {
            try {
                socket = serverSocket.accept();
                executorService.execute(new ServerHandler(socket, rootDirectory));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
