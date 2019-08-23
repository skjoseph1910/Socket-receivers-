#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sstream>
#include <sys/wait.h>
#include <queue>
using namespace std;

struct code
{
    string info="";
};

void readfile(code p[3]);
void error(string);
void socket(int argc, char *argv[], string a);
void itslit(code p[3], int argc, char *argv[]);
string lala(char buffer[]);
void toarr(string line, int array[4]);
int check(char a);
queue<int> calcul(string ya[12]);
void mult(queue<int>, int array[4], int ya[12]);
void addit(int omg[12], int ahh[3]);
int binaryToDecimal(string n);



int main(int argc, char *argv[])
{
    code test[3];
    readfile(test);
    itslit(test, argc, argv);

    return 0;
}



int check(char a)
{
    if (isdigit(a))
        return 1;
    else
        return -1;
}

string lala(char buffer[])
{
    string line="";
    for (int i=1;i<strlen(buffer);i++)
        line.push_back(buffer[i]);
    return line;
}


void itslit(code p[3], int argc, char *argv[])
{
    for (int i=0;i<3;i++)
    {
        int pid=fork();
        if (pid==0)
        {
            socket(argc, argv, p[i].info);
            exit(0);
        }
        else
            sleep(1);
    }
    for (int i=0;i<3;i++)
        waitpid(-1, NULL, 0);
}

void readfile(code p[3])
{
    std::string line;
    for (int i=0;i<3;i++)
    {
        getline(std::cin, line);
        p[i].info+=to_string(i+1);
        p[i].info+=line[0];
        p[i].info+=line[2];
        if (i==0)
            p[i].info+="-1-1";
        else if (i==1)
            p[i].info+="--11";
        else if (i==2)
            p[i].info+="-11-";
    }
}

void error(string msg)
{
    std::cout<<msg<<std::endl;
    exit(0);
}

void socket(int argc, char *argv[], string a)
{
    int sockfd, portno, n, pepe;
    queue<int> que;
    string line, arr[2], token, signal, co="", rec="", ya[12];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256], temp;
    if (argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    
    bzero(buffer,256);
    for (int i=0;i<a.length();i++)
        buffer[i]=a[i];
    
    temp=buffer[0];
    cout<<"Child "<<buffer[0]<<", sending value: "<<buffer[2]<<" to child process "<<buffer[1]<<endl;
    n = write(sockfd,buffer,strlen(buffer));
    sleep(1);
    if (n < 0)
        error("ERROR writing to socket");
    
    cout<<sockfd<<endl;
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
        error("ERROR reading from socket");
    
    line=lala(buffer);
    istringstream ss(line);
    int i=0, array[4], omg[12], ahh[3];
    while (getline(ss, token, ','))
    {
        arr[i]=token;
        i++;
    }
    signal=arr[0];
    i=0;
    toarr(arr[1], array);
    istringstream ss1(arr[0]);
    while (getline(ss1, token, ' '))
    {
        ya[i]=token;
        i++;
    }
    que=calcul(ya);
    mult(que, array, omg);
    addit(omg, ahh);
    
    for (int i=0;i<4;i++)
    {
        co+=to_string(array[i]);
        co+=" ";
    }
    
    for (int i=0;i<3;i++)
        rec+=to_string(ahh[i]);
    pepe=binaryToDecimal(rec);
    
    cout<<"\nChild "<<temp<<"\nSignal:"<<signal<<"\nCode: "<<co<<endl<<"Received value = "<<pepe<<endl;
    
}

void addit(int omg[12], int ahh[3])
{
    int a=0,b=1,c=2,d=3;
    for (int i=0;i<3;i++)
    {
        ahh[i]=omg[a]+omg[b]+omg[c]+omg[d];
        a+=4; b+=4; c+=4; d+=4;
        ahh[i]=ahh[i]/4;
    }
    
    for (int i=0;i<3;i++)
        if (ahh[i]==-1)
            ahh[i]=0;
    
}

void toarr(string line, int array[4])
{
    for (int i=0;i<4;i++)
        array[i]=check(line[i]);
}

queue<int> calcul(string array[12])
{
    queue<int> a;
    for (int i=0;i<12;i++)
    {
        if (isdigit(array[i][0]))
            a.push(array[i][0]-48);
        else
            a.push(-1*(array[i][1]-48));
    }
    
    return a;
}

void mult(queue<int> a, int array[4], int ya[12])
{
    int j=0;
    for (int i=0;i<12;i++)
    {
        if (j==4)
            j=0;
        ya[i]=a.front()*array[j];
        a.pop();
        j++;
    }
}

int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;
    int base = 1;
    int len = num.length();
    for (int i=len-1;i>=0;i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}
