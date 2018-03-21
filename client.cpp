#include <bits/stdc++.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout<<"Invalid number of arguments\n"<<endl;
        exit(1);
    }

    string kous;
    std::ifstream kosaksi(argv[2], std::ios::in | std::ios::binary);
    if (kosaksi)
    {
        kosaksi.seekg(0, std::ios::end);
        kous.resize(kosaksi.tellg());
        kosaksi.seekg(0, std::ios::beg);
        kosaksi.read(&kous[0], kous.size());
        kosaksi.close();
    }
    else 
    {
        cout<<"No such file"<<endl;
        exit(1);
    }

    CURL *curl;
    CURLcode res;
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    struct curl_slist *headerlist = NULL;
    static const char buf[] =  "Expect:";

    curl_global_init(CURL_GLOBAL_ALL);

    curl_formadd(&formpost,
        &lastptr,
        CURLFORM_COPYNAME, "cache-control:",
        CURLFORM_COPYCONTENTS, "hurray",
        CURLFORM_END);

    curl_formadd(&formpost,
        &lastptr,
        CURLFORM_COPYNAME, "content-type:",
        CURLFORM_COPYCONTENTS, "multipart/form-data",
        CURLFORM_END);

    curl_formadd(&formpost, &lastptr,
        CURLFORM_COPYNAME, "file",  
        CURLFORM_BUFFER, "data",
        CURLFORM_BUFFERPTR, kous.data(),
        CURLFORM_BUFFERLENGTH, kous.size(),
        CURLFORM_END);

    curl = curl_easy_init();
    headerlist = curl_slist_append(headerlist, buf);
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL,argv[1]);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        // Uncomment this section if you want details about the connection
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        curl_slist_free_all(headerlist);
    }
    else
    {
        cout<<"Unable to establish connection"<<endl;
        exit(1);
    }
}