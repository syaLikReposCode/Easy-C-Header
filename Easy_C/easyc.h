#if defined(__AUTHOR__)
#undef __AUTHOR__
#endif
#if defined(__EASY_C_HEADER__)
#undef __EASY_C_HEADER__
#endif
// above lines are important if __AUTHOR__ or __EASY_C_HEADER__ is defined in the current file
#ifndef __AUTHOR__
#define __AUTHOR__ "syaLikShreer"
// above lines are unnecessary, you can delete it or modify it as you want
// to delete it you need to remove '#endif' line at the very bottom of this file
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <setjmp.h>


#ifdef _WIN32
#include <WinSock2.h>
#include <ws2def.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define OS "Windows"
typedef uint16_t in_port_t;
#else
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#define OS "Linux"
#endif

jmp_buf ex_buf;
#define try if(setjmp(ex_buf)==0)
#define catch(x) else if(x)
#define finally else
#define throw(x) longjmp(ex_buf,x)


#ifndef __EASY_C_HEADER__
#define __EASY_C_HEADER__ 1
#define equals(X, Y)((strcmp(X, Y) == 0) ? true : false)
#define typecheck(T) _Generic( (T), int: "integer", \
                              _Bool: "boolean", \
                              char*: "string",\
                              char: "character", \
                              double: "double", \
                              long double: "double", \
                              float: "float", \
                              long: "long",\
                              short: "short", \
                              void *: "null", \
                               default: "unknown")
typedef _Bool bools;
typedef char* string;
char * toLowerCase(char * t){
   char me[] = "";
    strcpy(me, t);
  char res[] = "";
  for(int i = 0; i <= strlen(t); i++)
  {
    //   printf("%c\n", me[i]);
    res[i] = tolower(me[i]);
  }
  char * s = strdup(res);
  return s;
}
char * toUpperCase(char * t){
    char me[] = "";
    strcpy(me, t);
  char res[] = "";
  for(int i = 0; i <= strlen(t); i++)
  {
    //   printf("%c\n", me[i]);
    res[i] = toupper(me[i]);
  }
  char * s = strdup(res);
    return s;
}

void printString(char * arg){
    printf("%s", arg);
}
void printInt(int arg){
    printf("%d", arg);
}
void printChar(char arg){
    printf("%c", arg);
}
void printBool(_Bool arg){
    printf("%s", (arg) ? "true" : "false");
}
void printNone(){
    printf("");
}
void printDouble(double arg){
    printf("%lf", arg);
}
void printLongDb(long double arg){
    printf("%Lf", arg);
}
void printFloat(float arg){
    printf("%f",arg);
}


#define print(X) _Generic((X), int: printInt, \
                              _Bool: printBool, \
                              char*: printString,\
                              char: printChar, \
                              double: printDouble, \
                              long double: printLongDb, \
                              float: printFloat, \
                              size_t: printInt, \
                               default: printNone)(X)
void printStringln(char * arg){
    printf("%s\n", arg);
}
void printIntln(int arg){
    printf("%d\n", arg);
}
void printCharln(char arg){
    printf("%c\n", arg);
}
void printBoolln(_Bool arg){
    printf("%s\n", (arg) ? "true" : "false");
}
void printNoneln(){
    printf("\n");
}
void printDoubleln(double arg){
    printf("%lf\n", arg);
}
void printLongDbln(long double arg){
    printf("%Lf\n", arg);
}
void printFloatln(float arg){
    printf("%f\n",arg);
}

#define println(X) _Generic((X), int: printIntln, \
                              _Bool: printBoolln, \
                              char*: printStringln,\
                              char: printCharln, \
                              double: printDoubleln, \
                              long double: printLongDbln, \
                              float: printFloatln, \
                              size_t: printIntln, \
                               default: printNoneln)(X)

char * concat(char * t, char * c){
    // allocate memory for the result
    char *result = (char *)malloc(strlen(t) + strlen(c) + 1);
    strcpy(result, t);
    strcat(result, c);
    return result;
}

char * input(char * text){
    char * res = (char *)malloc(sizeof(char) * 100);
    printf("%s", text);
    scanf("%s", res);
    return res;
}


char * intToString(int number){
    char * res = (char *)malloc(sizeof(char) * 10);
    sprintf(res, "%d", number);
    return res;
}

char * doubleToString(double number){
    char * res = (char *)malloc(sizeof(char) * 10);
    sprintf(res, "%lf", number);
    return res;
}

char * floatToString(float number){
    char * res = (char *)malloc(sizeof(char) * 10);
    sprintf(res, "%f", number);
    return res;
}

#define toString(X) _Generic((X), int: intToString, double: doubleToString, float: floatToString, uint16_t: intToString,\
unsigned int: intToString,\
 default: "unknown")(X)

int toInt(char * arg){
    int res = atoi(arg);
    return res;
}

double toDouble(char * arg){
    double res = atof(arg);
    return res;
}

float toFloat(char * arg){
    float res = atof(arg);
    return res;
}
void writeFile(char * filename, char * text, _Bool append){
    if(append){
    FILE * fp = fopen(filename, "a");
    fprintf(fp, "%s", text);
    fclose(fp);
    free(fp);
    }else{
    FILE * fp = fopen(filename, "w");
    fprintf(fp, "%s", text);
    fclose(fp);
    free(fp);
    }
}
void rm(char * filename){
    if(remove(filename) == 0){
        printf("File %s removed successfully.\n", filename);
    }else{
        printf("Unable to remove the file %s.\n", filename);
    }
}

char * readFile(char * filename){
    FILE * fp = fopen(filename, "r");
    char * res = (char *)malloc(sizeof(char) * 100);
    fgets(res, 100, fp);
    fclose(fp);
    return res;
}

void writeBinary(char * filename, char * text, _Bool append){
    if(append){
    FILE * fp = fopen(filename, "ab");
    fprintf(fp, "%s", text);
    fclose(fp);
    free(fp);
    }else{
    FILE * fp = fopen(filename, "wb");
    fprintf(fp, "%s", text);
    fclose(fp);
    free(fp);
    }
}
char * readBinary(char * filename){
    FILE * fp = fopen(filename, "rb");
    char * res = (char *)malloc(sizeof(char) * 100);
    fread(res, 1, 100, fp);
    fclose(fp);
    return res;
}

void readEOF(char * filename, void(*callback)(char *), _Bool binary){
    FILE * fp;
    if(binary){
    fp = fopen(filename, "rb");
    char line[2048]= ""; // change the size of this array to allow more characters, as long it's not above allowed C numbers and must be unsigned
    while(fgets(line, sizeof(line), fp)){
        callback(line);
    }
    }else{
    fp = fopen(filename, "r");
    char line[2048]= ""; // change the size of this array to allow more characters, as long it's not above allowed C numbers and must be unsigned
    while(fgets(line, sizeof(line), fp)){
        callback(line);
    }
    }
    fclose(fp);
}

char * repstr(char * text, char * old, char * newstr){
    char * res = (char *)malloc(sizeof(char) * 100);
    strcpy(res, text);
    char * p = strstr(res, old);
    while(p){
        strcpy(p, newstr);
        p += strlen(newstr);
        p = strstr(p, old);
    }
    return res;
}

_Bool sbs_char_arr(char d[], char* t){
    char stringified[] = "";
    for(int i = 0; i<sizeof(d); i++){
    stringified[i] = d[i];
    if(i == sizeof(d)-1){
        stringified[i+1] = '\0';
    }
    }
    char * res = strstr(stringified, t);
    if(res){
        return true;
    }else{
        return false;
    }
}
_Bool sbs_str_arr(char * d[], char * t){
    char * stringified;
    size_t size = sizeof(d) / sizeof(*d);
    for(int i = 0; i <= size; i++){
       concat(stringified, d[i]);
       println(d[i]);
       if(i == size){
           concat(stringified, "\0");
       }
    }
    println(stringified);
    char * res = strstr(stringified, t);
    if(res){
        return true;
    }else{
        return false;
    }
}


#if defined( _WIN32)

char * getIP(char * hostname){
    // start a WSA (Windows Socket API) initialization, coz this is windows basically you need to turn on
    // the Socket support -.-
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
        return NULL;
    }

    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    int error;
    char *ipstr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    error = getaddrinfo(hostname, NULL, &hints, &result);
    if(error != 0){
        printf("getaddrinfo failed with error: %d\n", error);
        return NULL;
    }
    ipstr = inet_ntoa(((struct sockaddr_in *)result->ai_addr)->sin_addr);
    return ipstr;
    }
SOCKET createConnection(char * host, in_port_t port, _Bool showLog){
    SOCKET so;
    if(showLog){
    WSADATA wsa;
    struct sockaddr_in addr;
    print("Starting Initialization for WSA...\n");
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return -1;
    }
    print("Initialization for WSA done.\n");
    print("Creating socket...\n");
    so = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(so == INVALID_SOCKET){
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        return -1;
    }
    print("Socket created.\n");
    print("Setting up address...\n");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(getIP(host));
    print("Address set.\n");
    print("Connecting...\n");
    if(connect(so, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR){
        printf("Connection failed with error: %d\n", WSAGetLastError());
        return -1;
    }
    printf("Connected. With hostname: %s\n", host);

    }else{

        WSADATA wsa;
    struct sockaddr_in addr;
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return -1;
    }
    so = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(so == INVALID_SOCKET){
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        return -1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(getIP(host));
    if(connect(so, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR){
        printf("Connection failed with error: %d\n", WSAGetLastError());
        return -1;
    }

    }
    return so;
}

#else
int createConnection(char * host, in_port_t port){
    struct hostent *hp;
    struct sockaddr_in server;
    int on = 1, sock;
    print("Creating socket...\n");
    if((hp=gethostbyname(host))==NULL){
        printf("%s: unknown host\n", host);
        exit(1);
    }
    print("Copying Host...\n");
    copy(hp->h_addr, &server.sin_addr, hp->h_length);
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
    if(sock == -1){
        printf("socket failed\n");
        exit(1);
    }
    print("Connecting...\n");
    if(connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == -1){
        printf("connect failed\n");
        exit(1);
    }
    return sock;

}

#endif

#endif
#endif
