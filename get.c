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

        // Add custom headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "origin: https://acas.edu.bd");
        headers = curl_slist_append(headers, "referer: https://acas.edu.bd/");
        headers = curl_slist_append(headers, "sec-ch-ua: \"Chromium\";v=\"130\", \"Brave\";v=\"130\", \"Not?A_Brand\";v=\"99\"");
        headers = curl_slist_append(headers, "sec-ch-ua-mobile: ?0");
        headers = curl_slist_append(headers, "sec-ch-ua-platform: \"Windows\"");
        headers = curl_slist_append(headers, "user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36");
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
