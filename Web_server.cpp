#define _WINSOCK_DEPRECATED_NO_WARNINGS //Directive used to end warning related to deprecated functions in winsock library//
#pragma comment(lib,"ws2_32.lib") //pragma directive tells the linker to link the library necessary for winsock fxns//
#include<iostream>//input-output stream headerfile for cout and cin//
#include <winsock2.h>//winscok2 header file provides functions and structures for network programming(helps us create sockets that we need to create web servers//
#include <string>//string header file to enable string datatype and work with strings//
int main()
{
    std::cout<<"Request-Response Web Server using C++";
    SOCKET wsocket; //declared a socket variable called wsocket that will be used for create a socket for webserver//
    SOCKET new_socket; //Socket to Accept Incoming Connections//
    WSADATA wsaData;//holds info about windows socket im[]
    sockaddr_in server;
    int server_len;
    int BUFFER_SIZE=30720;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)//If successful, the WSAStartup function returns zero. Otherwise, it returns one of the error codes listed below.//
    {
        std::cout<<"Could not Intialize";
    }
    //create a socket//
    wsocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(wsocket==INVALID_SOCKET)
    {
        std::cout<<"Could not create socket";
    }
    //bind socket to address
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port = htons(8888); // or any other port number you want to use
    server_len=sizeof(server);

    if(bind(wsocket,(sockaddr *)&server,server_len)!=0)
    {
        std::cout<<"Could not bind socket";
    }
    //listen to address//
    if(listen(wsocket,20)!=0){
        std::cout<<"could not start listening";
    }
    std::cout<<"Listening on 127.0.0.1:8888\n";
    while(true)
    {
        new_socket=accept(wsocket,(sockaddr*)&server, &server_len);
        if(new_socket==INVALID_SOCKET)
        {
            std::cout<<"Can't Accept\n";
        }
        //Reading Requested data
        char buffer[30720]={ 0 };
        int bytes=recv(new_socket,buffer,BUFFER_SIZE,0);
        if(bytes<0)
        {
            std::cout<<"Unable to read Client Request";
        }
        std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
        std::string response="<html><h1>Web server made by using win32API in c++</h1></html>";
        serverMessage.append(std::to_string(response.size()));
        serverMessage.append("\n\n");
        serverMessage.append(response);
        int bytesSent=0;
        int totalBytesSent=0;
        while(totalBytesSent < serverMessage.size()){
            bytesSent=send(new_socket,serverMessage.c_str()+totalBytesSent,serverMessage.size()-totalBytesSent,0);
            if(bytesSent<0)
            {
                std::cout<<"Could not send response";
            }
            totalBytesSent+=bytesSent;
        }
        std::cout<<"Sent response to the client";

        closesocket(new_socket);

    }
    closesocket(wsocket);
    WSACleanup();
    return 0;
}
