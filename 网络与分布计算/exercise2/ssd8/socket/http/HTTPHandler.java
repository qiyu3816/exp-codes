package ssd8.socket.http;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileOutputStream;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.Scanner;

/**
 * HTTP服务器处理类 安装Runnable接口实现run()方法
 * 
 * @author 梁芮槐 2019302789
 */
public class HTTPHandler implements Runnable {
	private static int buffer_size = 8192;
    private byte[] buffer;

    static private String CRLF = "\r\n";
    StringBuffer header;

    BufferedInputStream bufferedInputStream;
    BufferedOutputStream bufferedOutputStream;

    Socket socket;
    SocketAddress socketAddress;

    String disconnectMsg;

    String rootPath;
    File targetFile;

    /**
     * 构造函数
     * 
     * @param socket 传入新的socket连接
     * @param rootPath 获取root文件夹位置
     * 
     * @throws IOException
     */
    public HTTPHandler(Socket socket, String rootPath) throws IOException {
        this.socket = socket;
        this.rootPath = rootPath;
    }

    /**
     * 初始化输入输出流
     * 
     * @throws IOException
     */
    private void initStream() throws IOException {
        buffer = new byte[buffer_size];
        header = new StringBuffer();
        bufferedInputStream = new BufferedInputStream(socket.getInputStream());
        bufferedOutputStream = new BufferedOutputStream(socket.getOutputStream());
    }

    /**
     * 线程主循环函数 处理GET, PUT, Unknown Request
     */
    @Override
    public void run() {
        try {
            this.initStream();
            System.out.println(socket.getInetAddress() + ":" + socket.getPort() + " > connected successfully");
            disconnectMsg = socket.getInetAddress() + ":" + socket.getPort() + " > disconnected successfully";
            
            processRequest();

            System.out.println("header from " + socket.getInetAddress() + " : ");
            System.out.println(header.toString());

            processResponse();

            close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
        	if (null != socket) {
    			try {
                    bufferedInputStream.close();
                    bufferedOutputStream.close();
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
     * 客户请求处理函数
     * 
     * @throws IOException
     */
    private void processRequest() throws IOException {
        char last = 0, c = 0;

        // 只读header
        boolean endHeader = false;
        while(!endHeader && ((c = (char) bufferedInputStream.read()) != -1)) {
            switch(c) {
                case '\r':
                    break;
                case '\n':
                {
                    if(c == last)
                    {
                        endHeader = true;
                        break;
                    }
                    last = c;
                    header.append(c);
                    break;
                }
                default:
                {
                    last = c;
                    header.append(c);
                }
            }
        }
    }

    /**
     * 回复客户端函数
     * 
     * @throws IOException
     */
    private void processResponse() throws IOException {
        Scanner scanner = new Scanner(header.toString());
        String line = null;
        while((line = scanner.next()) != null) {
            // 处理GET
            if(line.startsWith("GET")) {
                String filePath = scanner.next();

                // int index = filePath.split(":").length; // 测试代理服务器
                // String tmp = filePath.split(":")[index - 1]; // 测试代理服务器
                // tmp = tmp.substring(tmp.indexOf("/")); // 测试代理服务器
                // filePath = tmp; // 测试代理服务器
                
                targetFile = new File(rootPath + filePath);

                String fileType = null;
                if(targetFile.exists() && targetFile.isFile()) {
                    if(filePath.endsWith(".hml") || filePath.endsWith(".html")) {
                        fileType = "text/html";
                    } else if (filePath.endsWith(".jpeg") || filePath.endsWith(".jpg")) {
                        fileType = "image/jpeg";
                    } else if (filePath.endsWith(".csv")) {
                        fileType = "text/csv";
                    }

                    responseMessage(fileType, "200 OK", targetFile);
                } else {
                    responseMessage("text/html", "404 Not Found");
                }
            } else if (line.startsWith("PUT")) {
                String filePath = scanner.next();
				targetFile = new File(rootPath + filePath);

				if (targetFile.exists()) {
					if (!targetFile.delete()) {
						System.out.println("Error(s) : delete" + filePath + " failed !!!");
					}
				}

                // 开始接收文件
                FileOutputStream fileOutputStream = new FileOutputStream(targetFile);
				scanner.next(); // 读取 HTTP/1.0
				scanner.next(); // 读取 Content-Length:
				int fileLength = Integer.parseInt(scanner.next()); // 获取文件长度大小以便解算收包个数
                // System.out.println("File length: " + fileLength);
                int packetCount = (int) (fileLength / buffer_size) + ((fileLength % buffer_size) == 0 ? 0 : 1);
				for(int i = 0; i < packetCount; i++) {
					bufferedInputStream.read(buffer);
					fileOutputStream.write(buffer);
				}
				
				fileOutputStream.close();
				responseMessage("text/html", "201 Created");
            } else {
                responseMessage("text/html", "501 Not Implemented");
            }
            break;
        }
    }

    /**
     * 回应客户端并传递相应的信息和文件 专用于客户端的GET命令
     * 
     * @param fileType 文件类型
     * @param status 请求状态
     * @param file 目标文件
     * 
     * @throws IOException
     */
    private void responseMessage(String fileType, String status, File file) throws IOException {
        StringBuffer message = new StringBuffer();

		message.append("HTTP/1.0 ").append(status).append(CRLF);
		message.append("Server: HttpServer/1.0").append(CRLF);
		message.append("Content-type: ").append(fileType).append(CRLF);
		message.append("Content-length: ").append(file.length()).append(CRLF);
		message.append(CRLF);
		this.bufferedOutputStream.write(message.toString().getBytes());

        // 开始传输文件
		FileInputStream fileStream = new FileInputStream(file);
		while (fileStream.read(buffer) != -1) {
			this.bufferedOutputStream.write(buffer);
		}
		this.bufferedOutputStream.flush();
		fileStream.close();
    }

    /**
     * 回复客户端并传递信息 专用于回复客户端的PUT命令
     * 
     * @param fileType 文件类型
     * @param status 请求状态
     * 
     * @throws IOException
     */
    private void responseMessage(String fileType, String status) throws IOException {
        StringBuffer message = new StringBuffer();
		String htmlContent = "<html><body>" + status + "</body></html>";

		message.append("HTTP/1.0 ").append(status).append(CRLF);
		message.append("Server: HttpServer/1.0").append(CRLF);
		message.append("Content-type: ").append(fileType).append(CRLF);
		message.append("Content-length: ").append(htmlContent.length()).append(CRLF);
		message.append(CRLF);
		message.append(htmlContent);
		this.bufferedOutputStream.write(message.toString().getBytes());
		this.bufferedOutputStream.flush();
    }

    /**
     * 关闭所有流
     * 
     * @throws IOException
     */
    private void close() throws IOException{
        socket.close();
        bufferedOutputStream.close();
        bufferedInputStream.close();
    }

}
