#include <curl/curl.h>
#include <curl/easy.h>
#include <string.h>

#include "POSTRequest.h"

/* function prototypes to define later */
char *do_web_request(char *url,char* args);
size_t static write_callback_func(void *buffer, size_t size,size_t nmemb,void *userp);

/* the main function invoking 
int main(){
    char *url = "http://requestb.in/o3r7poo3";
    char *content = NULL;
    char *args = "name=zarioh&project=stage";

    content = do_web_request(url,args);

    printf("%s", content);
}
*/

/* the function to return the content for a url */
char *do_web_request(char *url, char* args){
    /* keeps the handle to the curl object */
    CURL *curl_handle = NULL;
    /* to keep the response */
    char *response = NULL;

    /* initializing curl and setting the url */
    curl_handle = curl_easy_init();
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    /* Now specify the POST data */ 
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, args);

    /* follow locations specified by the response header */
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);

    /* setting a callback function to return the data */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback_func);

    /* passing the pointer to the response as the callback parameter */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

    /* perform the request */
    curl_easy_perform(curl_handle);

    /* cleaning all curl stuff */
    curl_easy_cleanup(curl_handle);

    return response;
}

/* the function to invoke as the data recieved */
size_t static write_callback_func(void *buffer,size_t size,size_t nmemb,void *userp){
    char **response_ptr =  (char**)userp;

    /* assuming the response is a string */
    *response_ptr = strndup(buffer, (size_t)(size *nmemb));

}