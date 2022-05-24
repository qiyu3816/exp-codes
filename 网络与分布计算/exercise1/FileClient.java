package exercise1;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import java.util.Scanner;

/**
 * 文件传输客户端
 * 
 * @author 梁芮槐 2019302789
 */
public class FileClient{
    private static final int TCP_PORT = 2021;                // 服务器TCP端口
    private static final int UDP_PORT = 2020;                // 服务器UDP端口
    private static final String remoteAddress = "127.0.0.1"; // IP地址

    Socket socket;

    private static final int PACKET_SIZE = 1024;
    String recvPath = "D:\\Codes\\eclipse_ws_socket\\Socket_tests\\recv";
    File targetFile;

    /**
     * 客户类构造函数
     * 
     * @throws UnknownHostException
     * @throws IOException
     */
    public FileClient() throws UnknownHostException, IOException {
        socket = new Socket(remoteAddress, TCP_PORT);
    }

    /**
     * 客户端主函数
     * 
     * @param args 未使用
     * 
     * @throws IOException
     */
    public static void main(String[] args) throws IOException {
        new FileClient().request();
    }

    /**
     * 客户请求主循环 以客户端与服务端的对话为主 有get命令且收到服务器确认回复时调用接收函数
     * 
     * @throws UnknownHostException
     * @throws IOException
     */
    public void request() throws UnknownHostException, IOException {
        try {
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            PrintWriter printWriter = new PrintWriter(bufferedWriter, true);
            Scanner scanner = new Scanner(System.in);

            System.out.println(bufferedReader.readLine());

            String cmd = null;
            String response = null;
            while((cmd = scanner.next()) != null) {
                printWriter.println(cmd);
                if((cmd.equals("cd")) || (cmd.equals("get"))) {
                    String dir = scanner.next();
                    targetFile = new File(recvPath, dir);
                    printWriter.println(dir);
                    if(cmd.equals("get")) {
                        if(null != (response = bufferedReader.readLine())) {
                            // 服务器接收到get命令后且该目标文件存在就应回传"Length<...>" 使客户端获取到该文件的大小并决定接收包数目
                            if(response.startsWith("Length")) {
                                getFile(Long.parseLong(response.substring(6)));
                            } else {
                                System.out.println(response);
                            }
                        }
                    }
                }

                while(null != (response = bufferedReader.readLine())) {
                    if(response.equals("ResponseFinished")) {
                        break;
                    }
                    System.out.println(response);
                }

                if(cmd.equals("bye")) {
                    break;
                }
            }
            scanner.close();
            bufferedReader.close();
            bufferedWriter.close();
            printWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if(null != socket){try {socket.close();} catch (IOException e) {e.printStackTrace();}}
        }
    }

    /**
     * 客户端get命令文件接收函数 这个函数只有当服务端查询确认有这个文件时才会回传文件大小
     * 
     * @param fileLength 文件大小 单位为Byte
     * 
     * @throws IOException
     */
    public void getFile(long fileLength) throws IOException {
        int packetCount = (int) (fileLength / PACKET_SIZE) + ((fileLength % PACKET_SIZE) == 0 ? 0 : 1);
        DatagramSocket datagramSocket = new DatagramSocket(UDP_PORT);
        datagramSocket.setReceiveBufferSize(PACKET_SIZE * 8); // 设置缓冲区减少丢包
        DatagramPacket dataPacket = new DatagramPacket(new byte[PACKET_SIZE], PACKET_SIZE);
        FileOutputStream fileOutputStream = new FileOutputStream(targetFile);
        byte[] bytes = new byte[PACKET_SIZE];
        while((packetCount--) > 0) {
            datagramSocket.receive(dataPacket);
            bytes = dataPacket.getData();
            fileOutputStream.write(bytes, 0, dataPacket.getLength());
            fileOutputStream.flush();
        }
        datagramSocket.close();
        fileOutputStream.close();
        System.out.println("Successfully received " + targetFile.getName() + " to " + recvPath);
    }
    
}
