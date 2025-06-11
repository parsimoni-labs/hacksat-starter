#include <memory.h>
#include <stdlib.h>
#include <curl/curl.h>

// Unikernel demonstrating how to interact with the on-board system:
// ping, get orbital parameters, get latest sensor picture

struct memory {
  char *response;
  size_t size;
};
 
// source: https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
static size_t cb(char *data, size_t size, size_t nmemb, void *clientp) {
  size_t realsize = size * nmemb;
  struct memory *mem = (struct memory *)clientp;
 
  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if(!ptr)
    return 0;  /* out of memory */
 
  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;
 
  return realsize;
}

struct memory get(CURL* curl, char* uri) {
    struct memory chunk = {0};
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, uri);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n\
                Ensure you have specified a valid IP as the runtime argument. See the docs.\n",
                curl_easy_strerror(res));
    }
    return chunk;
}

#define RESPONSE_THRESHOLD 500

void print_get(CURL* curl, char* uri) {
    struct memory res = get(curl, uri);
    if (res.size >= RESPONSE_THRESHOLD) {
        res.response[RESPONSE_THRESHOLD] = 0;
        puts(res.response);
        printf("\n(response truncated, %zu bytes total)", res.size);
    } else {
        puts(res.response);
    }
    printf("\n");
    free(res.response);
}

int main(void)
{
    printf("Unikernel started\n");
    CURL* curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        printf("\n- Printing result of GET 10.0.42.2/ping:\n");
        print_get(curl, "http://10.0.42.2/ping");
        printf("\n- Printing result of GET 10.0.42.2/orbital-parameters:\n");
        print_get(curl, "http://10.0.42.2/orbital-parameters");
        printf("\n- Printing result of GET 10.0.42.2/sensors/imaging-01:\n");
        print_get(curl, "http://10.0.42.2/sensors/imaging-01");
        curl_easy_cleanup(curl);
    } else {
        printf("Curl initialization failed\n");
    }
    fflush(stdout);
    return 0;
}
