#include <stdio.h>
#include <curl/curl.h>

int main(void) {
    CURL *curl;
    CURLcode res;

    // Initialize the libcurl session
    curl = curl_easy_init();
    if(curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com/api/resource");

        // Add a custom header
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Custom-Header: CustomValue");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}
