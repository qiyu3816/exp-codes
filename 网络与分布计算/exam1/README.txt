java ssd8/socket/http/HTTPServer <rootDir>
java proxy/HTTPProxy/HTTPProxyServer <proxyDir>
java proxy/Client <proxyServerAddress>
	GET http://HTTPServerAddress:<port>/<fileName> HTTP/1.0


仅测试了用Exercise2的HTTPServer当目标服务器，仅支持html(hml)和jpg(jpeg)文件
HTTPServer的port是80