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
  string s="127.0.0.1:";
  for(int i=0;i<strlen(argv[1]);i++)
  s+= argv[1][i];
  s+="/";
  for(int i=0;i<strlen(argv[2]);i++)
  s+= argv[2][i];
  curl_easy_setopt(pos,CURLOPT_URL,"127.0.0.1:8000/hurray.csv");
  curl_easy_setopt(pos, CURLOPT_VERBOSE, 1L);
  result = curl_easy_perform(pos);
  curl_global_cleanup();
  return 0;
}