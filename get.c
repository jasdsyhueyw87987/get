#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl = curl_easy_init();
    if(curl) {
        // Set the URL for the GET request from command line argument
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);

        // Set HTTPS options for secure connection
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Verify the peer's SSL certificate
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); // Verify the certificate hostname

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
