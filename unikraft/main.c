#include <curl/curl.h>

// Most basic interaction with the on-board system,
// simply getting a ping from it

int main(void)
{
    CURL *curl;
    CURLcode res;

    printf("Unikernel started\n");
    curl = curl_easy_init();
    if(curl) {
        printf("Printing result of GET 10.0.42.2/ping:\n");
        curl_easy_setopt(curl, CURLOPT_URL, "http://10.0.42.2/ping");
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    } else {
        printf("Curl initialization failed\n");
    }
    fflush(stdout);
    return 0;
}


