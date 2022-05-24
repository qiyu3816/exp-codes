package proxy;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileOutputStream;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;
import java.util.Scanner;

/**
 * HTTP服务器处理类 安装Runnable接口实现run()方法
 * 
 * @author 梁芮槐 2019302789
 */
public class HTTPProxyHandler implements Runnable {
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

    // 代理服务器专用
    StringBuffer proxyHeader;
    String targetURL;
    boolean proxy200 = false;
    Socket proxySocket;
    String targetFilePath;

    /**
     * 构造函数
     * 
     * @param socket 传入新的socket连接
     * @param rootPath 获取root文件夹位置
     * 
     * @throws IOException
     */
    public HTTPProxyHandler(Socket socket, String rootPath) throws IOException {
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
     * 线程主循环函数 处理GET, Unknown Request
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
                targetURL = scanner.next();
                System.out.println("targetURL=" + targetURL);

                processProxyRequest(); // 处理客户端请求并将处理后的Request发到目标网站
                processProxyResponse(); // 将目标文件获取到root目录下并保持名称一致

                int index = targetURL.split("/").length;
                String filePath = targetURL.split("/")[index - 1];
                targetFile = new File(rootPath + "\\" + filePath);

                String fileType = null;
                if(targetFile.exists() && targetFile.isFile() && proxy200) {
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
            
            } else {
                responseMessage("text/html", "501 Not Implemented");
            }
            break;
        }
    }

    /**
     * 根据客户端Request的Header加载相应的文件到本地root目录
     * @throws IOException
     * @throws UnknownHostException
     */
    private void processProxyRequest() throws UnknownHostException, IOException {
        String[] ss = targetURL.split(":");
        String targetHost = ss[1].substring(2);
        System.out.println("targetHost=" + targetHost);
        int targetPort;
        if(ss.length == 2) {
            targetPort = 80;
        } else {
            targetPort = Integer.parseInt(ss[2].split("/")[0]);
        }
        System.out.println("targetPort=" + targetPort);
        proxySocket = new Socket(targetHost, targetPort);
        if(proxySocket.isConnected())
            System.out.println("socket-connected=true");
        BufferedOutputStream bufferedProxyOutputStream = new BufferedOutputStream(proxySocket.getOutputStream());
        
        String request = ("GET " + targetURL + " HTTP/1.0" + CRLF);
        request += ("From: " + targetHost + CRLF);
        request += ("User-Agent: " + "HTTPTool/1.0" + CRLF + CRLF);

		buffer = request.getBytes();
		bufferedProxyOutputStream.write(buffer, 0, request.length());
		bufferedProxyOutputStream.flush();
    }

    /**
     * 处理目标网站的回复
     * @throws IOException
     */
    private void processProxyResponse() throws IOException {
        proxyHeader = new StringBuffer();
        BufferedInputStream bufferedProxyInputStream = new BufferedInputStream(proxySocket.getInputStream());
        char last = 0, c = 0;
		/**
		 * Process the header and add it to the header StringBuffer.
		 */
		boolean inHeader = true; // loop control
		while (inHeader && ((c = (char) bufferedProxyInputStream.read()) != -1)) {
			switch (c) {
			case '\r':
				break;
			case '\n':
			// header这一行 遇到最后一个\n时加上一个\n是为下一次循环直接结束读取 跳出while
				if (c == last) {
					inHeader = false;
					break;
				}
				last = c;
				proxyHeader.append("\n");
				break;
			default:
				last = c;
				proxyHeader.append(c);
			}
        }
        System.out.println("\nresponse header:\n" + proxyHeader.toString());
        /**
		 * Read the contents and add it to the response StringBuffer.
		 */
        StringBuffer response = new StringBuffer();
		while (bufferedProxyInputStream.read(buffer) != -1) {
			response.append(new String(buffer,"iso-8859-1")); // 设定字符集
		}

        String[] ss1 = proxyHeader.toString().split(" ");
        System.out.println("status=" + ss1[1]);
        if(ss1[1].equals("200")) {
            proxy200 = true;
            int index = targetURL.split("/").length;
            String filename = targetURL.split("/")[index - 1];
			System.out.println("Start recv " + filename);
			FileOutputStream outfile = new FileOutputStream(rootPath + "\\" + filename);

			/**
			 * Save the response to the specified file.
			 */
			String content = response.toString();
			outfile.write(content.getBytes("iso-8859-1"));
			outfile.flush();
			outfile.close();
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
