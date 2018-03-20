#include <bits/stdc++.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[])
{
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *pos;
  CURLcode result;
  pos = curl_easy_init();
  if(!pos)
  {
    cout<<"Unable to initialise the connection\n";
    exit(1);
  }
  char s[100]="127.0.0.1:";
  int k=10;
  for(int i=0;i<strlen(argv[1]);i++)
  s[k++]= argv[1][i];
  s[k++]='/';
  for(int i=0;i<strlen(argv[2]);i++)
  s[k++]= argv[2][i];
  
  curl_easy_setopt(pos,CURLOPT_URL,s);
  curl_easy_setopt(pos, CURLOPT_VERBOSE, 1L);
  result = curl_easy_perform(pos);
  
  if(result != CURLE_OK)
  {
    cout<<"Error connecting with the server\n\n\n";
    exit(1);
  }
  curl_global_cleanup();
  return 0;
}