package exercise1;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.concurrent.TimeUnit;

/**
 * 服务器处理类 安装Runnable接口实现run()方法
 * 
 * @author 梁芮槐 2019302789
 */
public class ServerHandler implements Runnable {
    static final int UDP_PORT = 2020; 
    static final String HOST = "127.0.0.1";
    static final int PACKET_SIZE = 1024;

    BufferedReader bufferedReader;
    BufferedWriter bufferedWriter;
    PrintWriter printWriter;

    Socket socket;
    DatagramSocket datagramSocket;
    SocketAddress socketAddress;

    String disconnectMsg;
    String rootPath;
    File targetFile;
    String curPath;

    /**
     * 构造函数
     * 
     * @param socket 传入新的socket连接
     * @param rootPath 获取root文件夹位置
     * 
     * @throws IOException
     */
    public ServerHandler(Socket socket, String rootPath) throws IOException {
        this.socket = socket;
        this.rootPath = rootPath;
        this.curPath = this.rootPath;
    }

    /**
     * 初始化输入输出流
     * 
     * @throws IOException
     */
    private void initStream() throws IOException {
        bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        printWriter = new PrintWriter(bufferedWriter, true);
    }

    /**
     * 线程主循环函数 处理ls, cd, cd.., get命令
     */
    @Override
    public void run() {
        try {
            this.initStream();
            printWriter.println(socket.getInetAddress() + ":" + socket.getPort() + " > connected successfully");
            System.out.println(socket.getInetAddress() + ":" + socket.getPort() + " > connected successfully");
            disconnectMsg = socket.getInetAddress() + ":" + socket.getPort() + " > disconnected successfully";
            
            String cmd = null;
            String dir = null;
            while(null != (cmd = bufferedReader.readLine())) {
                if(cmd.equals("bye")) {
                    printWriter.println("Goodbye");
                    break;
                } else {
                    // 如果没有bye 那就正常检查命令
                    switch(cmd) {
                        case "ls":
                        {
                            ls();
                            break;
                        }
                        case "cd..":
                        {
                            cdparent();
                            break;
                        }
                        case "cd":
                        {
                            if(null != (dir = bufferedReader.readLine())) {
                                cd(dir);
                            } else {
                                printWriter.println("\"cd\" needs a param!");
                            }
                            break;
                        }
                        case "get":
                        {
                            if(null != (dir = bufferedReader.readLine())) {
                                sendFile(dir);
                            } else {
                                printWriter.println("\"get\" needs a param!");
                            }
                            break;
                        }
                        default:
                            printWriter.println("Inappropriate command");
                    }
                    printWriter.println("ResponseFinished");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch(InterruptedException e) {
            e.printStackTrace();
        } finally {
        	if (null != socket) {
    			try {
    				bufferedReader.close();
    				bufferedWriter.close();
    				printWriter.close();
    				socket.close();
    				System.out.println(disconnectMsg);
    				disconnectMsg = null;
    			} catch (IOException e) {
    				e.printStackTrace();
    			}
    		}
        }
    }

    /**
     * ls命令处理函数 输出当前目录下所有文件的类型, 名称, 大小
     */
    public void ls() {
        targetFile = new File(curPath);
        File[] files = targetFile.listFiles();
        if(files.length >= 1) {
            for(File file:files) {
                if(file.isFile()) {
                    printWriter.println("<file>\t\t" + file.getName() + "\t\t" + file.length() + "B");
                } else if(file.isDirectory()) {
                    printWriter.println("<dir>\t\t" + file.getName() + "\t\t" + file.length() + "B");
                }
            }
        } else {
            printWriter.println("Empty.");
        }
    }

    /**
     * cd..命令处理函数 但会上一级目录 若已在root则报错
     */
    public void cdparent() {
        if(curPath.equals(rootPath)) {
            printWriter.println("You've already in the root directory");
            return;
        }
        targetFile = new File(curPath).getParentFile();
        curPath = targetFile.getAbsolutePath();
        printWriter.println(targetFile.getName() + "\t > OK");
    }

    /**
     * cd命令处理函数 改变当前所在目录
     * 
     * @param dir 目的目录 如果存在就将当前所在目录改为目的目录
     */
    public void cd(String dir) throws IOException {
        targetFile = new File(curPath, dir);
        if(!targetFile.getCanonicalPath().startsWith(rootPath)) {
        	printWriter.println("You've already in the root directory");
        } else if(targetFile.exists() && targetFile.isDirectory()) {
            curPath = targetFile.getAbsolutePath();
            printWriter.println(targetFile.getName() + "\t > OK");
            return;
        } else if(targetFile.exists() && targetFile.isFile()) {
            printWriter.println("\"" + targetFile.getName() + "\" is a file!");
            return;
        } else {
            printWriter.println("\"" + targetFile.getName() + "\" doesn't exist!");
        }
    }

    /**
     * get命令处理函数 如果目标文件存在就返回LengthNum形式的回复告知客户端该文件大小 然后开始传输
     * 
     * @param dir 目标文件名
     * 
     * @throws IOException
     * @throws InterruptedException
     */
    public void sendFile(String dir) throws IOException, InterruptedException {
        targetFile = new File(curPath, dir);
        if(targetFile.exists() && targetFile.isFile() && targetFile.canRead()) {
            printWriter.println("Length" + targetFile.length());
        } else if(targetFile.exists() && targetFile.isDirectory()) {
            printWriter.println("\"" + targetFile.getName() + "\" is a directory!");
            return;
        } else if(!targetFile.exists()){
            printWriter.println("\"" + targetFile.getName() + "\" doesn't exist!");
            return;
        }

        BufferedInputStream bufferedInputStream = new BufferedInputStream(new FileInputStream(targetFile));

        datagramSocket = new DatagramSocket();
        datagramSocket.setSendBufferSize(PACKET_SIZE * 8);
        socketAddress = new InetSocketAddress(HOST, UDP_PORT);
        byte[] bytes = new byte[PACKET_SIZE];
        DatagramPacket datagramPacket = new DatagramPacket(bytes, bytes.length, socketAddress);
        
        int readSize;
        while((readSize = bufferedInputStream.read(bytes)) > 0) {
            datagramPacket.setData(bytes);
            datagramSocket.send(datagramPacket);
            bytes = new byte[PACKET_SIZE];
            // 控制频率尽量避免丢包
            // TimeUnit.MILLISECONDS.sleep(500);
            Thread.currentThread();
            Thread.sleep(500);
        }
        datagramSocket.close();
        bufferedInputStream.close();
        System.out.println("Successfully sent \"" + dir + "\" to " + socketAddress);
    }
    
}
