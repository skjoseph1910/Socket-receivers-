#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <queue>

void error(std::string msg);
void socket(int argc, char *argv[]);
std::string dectobinary(char n);
std::queue<int> bintoencode(std::string bit, int num);
int check(char a);
std::queue<int> bintoencode(std::string bit, int num);
std::string straightup(std::string, std::string, std::string, char);
std::string littytitty(std::queue<int> alright);
std::queue<int> combine(std::queue<int> a, std::queue<int> b, std::queue<int> c);
std::string lala(char buffer[]);
std::string oof(std::string line);

int main(int argc, char *argv[])
{
    socket(argc, argv);

    return 0;
}

std::string lala(char buffer[])
{
    std::string line="";
    for (int i=0;i<strlen(buffer);i++)
        line.push_back(buffer[i]);
    return line;
}

std::string straightup(std::string a, std::string b, std::string c, char num)
{
    if (a[1]==num)
        return std::to_string(a[0]-48);
    else if (b[1]==num)
        return std::to_string(b[0]-48);
    else if (c[1]==num)
        return std::to_string(c[0]-48);
    else
        return "";
}

std::string littytitty(std::queue<int> alright)
{
    std::string line="";
    while (!alright.empty())
    {
        line+=std::to_string(alright.front());
        line+=" ";
        alright.pop();
    }
    return line;
}

std::queue<int> combine(std::queue<int> a, std::queue<int> b, std::queue<int> c)
{
    int sum=0;
    std::queue<int> alright;
    while (!a.empty() && !b.empty() && !c.empty())
    {
        sum=a.front()+b.front()+c.front();
        a.pop(); b.pop(); c.pop();
        alright.push(sum);
    }
    return alright;
}

int check(char a)
{
    if (isdigit(a))
        return 1;
    else
        return -1;
}

std::queue<int> bintoencode(std::string bit, std::string wash)
{
    std::queue<int> a;
    int count=0, p=0;
    for (int i=0;i<12;i++)
    {
        if (i%4==0 && i!=0)
        {
            p++;
            count=0;
        }
        a.push(check(bit[p])*check(wash[count]));
        count++;
    }
    return a;
}

std::string dectobinary(char n)
{
    std::string line="---";
    int a=int(n)-48;
    for (int i=2;i>=0;i--)
    {
        if (a%2!=0)
            line[i] = std::to_string(a % 2)[0];
        a = a / 2;
    }
    return line;
}

void error(std::string msg)
{
    std::cout<<msg<<std::endl;
    exit(1);
}

void socket(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen,newsockfd1,newsockfd2;
    std::string line, wash, test1="", test2="", test3="", testing="";
    std::queue<int> a, b, c, alright;
    char buffer[256], buffer1[256], buffer2[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    line=dectobinary(buffer[2]);
    wash=lala(buffer);
    wash=wash.substr(3,7);
    std::cout<<"Here is the message from child "<<buffer[0]<<": Value = "<<buffer[2]<<", "<<" Destination = "<<buffer[1]<<"\n";
    a=bintoencode(line,wash);
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd1 = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
    if (newsockfd1 < 0)
        error("ERROR on accept");
    bzero(buffer1,256);
    n = read(newsockfd1,buffer1,255);
    if (n < 0) error("ERROR reading from socket");
    line=dectobinary(buffer1[2]);
    wash=lala(buffer1);
    wash=wash.substr(3,7);
    std::cout<<"Here is the message from child "<<buffer1[0]<<": Value = "<<buffer1[2]<<", "<<" Destination = "<<buffer1[1]<<"\n";
    b=bintoencode(line,wash);

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd2 = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
    if (newsockfd2 < 0)
        error("ERROR on accept");
    bzero(buffer2,256);
    n = read(newsockfd2,buffer2,255);
    if (n < 0) error("ERROR reading from socket");
    line=dectobinary(buffer2[2]);
    wash=lala(buffer2);
    wash=wash.substr(3,7);
    std::cout<<"Here is the message from child "<<buffer2[0]<<": Value = "<<buffer2[2]<<", "<<" Destination = "<<buffer2[1]<<"\n";
    c=bintoencode(line,wash);
    
    std::cout<<newsockfd<<"\n"<<newsockfd1<<"\n"<<newsockfd2<<"\n";
    
    alright=combine(a, b, c);
    line=littytitty(alright);
    
    test1+=std::to_string(buffer[0]-48); test1+=std::to_string(buffer[1]-48);
    test2+=std::to_string(buffer1[0]-48); test2+=std::to_string(buffer1[1]-48);
    test3+=std::to_string(buffer2[0]-48); test3+=std::to_string(buffer2[1]-48);
    
    testing=straightup(test1,test2,test3, '1')+line;
    testing=oof(testing);
    bzero(buffer,256);
    for (int i=0;i<testing.length();i++)
        buffer[i]=testing[i];
    n = write(newsockfd, buffer, strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
    sleep(1);
    
    testing=straightup(test1,test2,test3, '2')+line;
    testing=oof(testing);
    bzero(buffer,256);
    for (int i=0;i<testing.length();i++)
        buffer[i]=testing[i];
    n = write(newsockfd1,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
    sleep(1);
    
    
    testing=straightup(test1,test2,test3, '3')+line;
    testing=oof(testing);
    bzero(buffer,256);
    for (int i=0;i<testing.length();i++)
        buffer[i]=testing[i];
    n = write(newsockfd2,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
    sleep(1);
    
}

std::string oof(std::string line)
{
    if (line[0]=='1')
        line+=",-1-1";
    else if (line[0]=='2')
        line+=",--11";
    else if (line[0]=='3')
        line+=",-11-";
    return line;
}
