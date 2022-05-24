package ssd8.socket.http;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.net.Socket;

/**
 * Class <em>HttpClient</em> is a class representing a simple HTTP client.
 *
 * @author wben
 */
public class HttpClient {

	/**
	 * default HTTP port is port 80
	 */
	private static int port = 80;

	/**
	 * Allow a maximum buffer size of 8192 bytes
	 */
	private static int buffer_size = 8192;

	/**
	 * Response is stored in a byte array.
	 */
	private byte[] buffer;

	/**
	 * My socket to the world.
	 */
	Socket socket = null;

	/**
	 * Default port is 80.
	 */
	private static final int PORT = 80;

	/**
	 * Output stream to the socket.
	 */
	BufferedOutputStream ostream = null;

	/**
	 * Input stream from the socket.
	 */
	BufferedInputStream istream = null;

	/**
	 * StringBuffer storing the header
	 */
	private StringBuffer header = null;

	/**
	 * StringBuffer storing the response.
	 */
	private StringBuffer response = null;
	
	/**
	 * String to represent the Carriage Return and Line Feed character sequence.
	 */
	static private String CRLF = "\r\n";

	/**
	 * 客户端根目录
	 */
	static String clientDir;

	/**
	 * HttpClient constructor;
	 */
	public HttpClient(String clientDir) {
		this.clientDir = clientDir;
		buffer = new byte[buffer_size];
		header = new StringBuffer();
		response = new StringBuffer();
	}

	/**
	 * <em>connect</em> connects to the input host on the default http port --
	 * port 80. This function opens the socket and creates the input and output
	 * streams used for communication.
	 * @param host 服务端主机地址
	 * @throws Exception
	 */
	public void connect(String host) throws Exception {

		/**
		 * Open my socket to the specified host at the default port.
		 */
		socket = new Socket(host, PORT);

		/**
		 * Create the output stream.
		 */
		ostream = new BufferedOutputStream(socket.getOutputStream());

		/**
		 * Create the input stream.
		 */
		istream = new BufferedInputStream(socket.getInputStream());
	}

	/**
	 * <em>processGetRequest</em> process the input GET request.
	 * @param request 当前命令
	 * @throws Exception
	 */
	public void processGetRequest(String request) throws Exception {
		/**
		 * Send the request to the server.
		 */
		request += CRLF + CRLF;
		buffer = request.getBytes();
		ostream.write(buffer, 0, request.length());
		ostream.flush();
		/**
		 * waiting for the response.
		 */
		processResponse();
	}
	
	/**
	 * <em>processPutRequest</em> process the input PUT request.
	 * @param request 当前命令
	 * @author 梁芮槐 2019302789
	 * @throws Exception
	 */
	public void processPutRequest(String request) throws Exception {
		//=======start your job here============//
		String filePath = request.split(" ")[1];
		File file = new File(clientDir + filePath);

		if(!file.exists() || file.isDirectory()) {
			System.out.println("Unknown path !!!");
			return;
		}
		request += (CRLF + "Content-length: " + file.length() + CRLF + CRLF);
		// System.out.println("length " + file.length());
		ostream.write(request.getBytes());

		FileInputStream fileInputStream = new FileInputStream(file);
		while((fileInputStream.read(buffer)) != -1) {
			ostream.write(buffer, 0, buffer.length);
		}

		ostream.flush();
		
		processResponse();
		//=======end of your job============//
	}
	
	/**
	 * <em>processResponse</em> process the server response.
	 * @throws Exception
	 */
	public void processResponse() throws Exception {
		char last = 0, c = 0;
		/**
		 * Process the header and add it to the header StringBuffer.
		 */
		boolean inHeader = true; // loop control
		while (inHeader && ((c = (char) istream.read()) != -1)) {
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
				header.append("\n");
				break;
			default:
				last = c;
				header.append(c);
			}
		}

		/**
		 * Read the contents and add it to the response StringBuffer.
		 */
		while (istream.read(buffer) != -1) {
			response.append(new String(buffer,"iso-8859-1")); // 设定字符集
		}
	}

	/**
	 * Get the response header.
	 */
	public String getHeader() {
		return header.toString();
	}

	/**
	 * Get the server's response.
	 */
	public String getResponse() {
		return response.toString();
	}

	/**
	 * Close all open connections -- sockets and streams.
	 * @throws IOException
	 */
	public void close() throws Exception {
		socket.close();
		istream.close();
		ostream.close();
	}
}
