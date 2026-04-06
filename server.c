#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
  #include <winsock2.h>
  #pragma comment(lib, "ws2_32.lib")
  typedef int socklen_t;
#else
  #include <unistd.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #define closesocket close
#endif

#define PORT      5000
#define BUF_SIZE  8192
#define CSV_FILE  "testinout.csv"

/* -------- extract value from JSON -------- */
static void json_get(const char *body, const char *key, char *out, int max) {
    char search[64];
    snprintf(search, sizeof(search), "\"%s\"", key);
    const char *p = strstr(body, search);
    if (!p) { out[0] = '\0'; return; }
    p += strlen(search);
    while (*p == ' ' || *p == ':') p++;
    if (*p == '"') {
        p++;
        int i = 0;
        while (*p && *p != '"' && i < max - 1) out[i++] = *p++;
        out[i] = '\0';
    } else {
        /* non-string value (true/false/number) */
        int i = 0;
        while (*p && *p != ',' && *p != '}' && i < max - 1) out[i++] = *p++;
        out[i] = '\0';
    }
}

/* -------- count rows in CSV -------- */
static int count_rows() {
    FILE *f = fopen(CSV_FILE, "r");
    if (!f) return 0;
    int n = 0; char buf[512];
    while (fgets(buf, sizeof(buf), f)) n++;
    fclose(f);
    return n;
}

/* -------- ensure CSV header -------- */
static void ensure_header() {
    FILE *f = fopen(CSV_FILE, "r");
    if (f) { fclose(f); return; }
    f = fopen(CSV_FILE, "w");
    if (!f) return;
    fprintf(f, "\xEF\xBB\xBF"); /* UTF-8 BOM */
    fprintf(f, "ชื่อ,นามสกุล,เบอร์โทร,อีเมล,วันเริ่มเช่า,วันสิ้นสุดการเช่า,ต้องการให้ส่งรถ,วันที่บันทึก\n");
    fclose(f);
}

/* -------- HTTP helpers -------- */
static void send_str(int sock, const char *s) {
    send(sock, s, (int)strlen(s), 0);
}
static void cors_headers(int sock) {
    send_str(sock,
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type\r\n");
}

/* -------- POST /save -------- */
static void handle_save(int sock, const char *body) {
    char firstname[128]={0}, lastname[128]={0}, phone[64]={0};
    char email[128]={0}, start[32]={0}, end_[32]={0}, delivery[16]={0};

    json_get(body, "firstname", firstname, sizeof(firstname));
    json_get(body, "lastname",  lastname,  sizeof(lastname));
    json_get(body, "phone",     phone,     sizeof(phone));
    json_get(body, "email",     email,     sizeof(email));
    json_get(body, "start",     start,     sizeof(start));
    json_get(body, "end",       end_,      sizeof(end_));
    json_get(body, "delivery",  delivery,  sizeof(delivery));

    if (!firstname[0] || !lastname[0] || !phone[0]) {
        send_str(sock,
            "HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: application/json\r\n");
        cors_headers(sock);
        send_str(sock, "\r\n{\"success\":false,\"error\":\"กรุณากรอกข้อมูลให้ครบ\"}\n");
        return;
    }

    ensure_header();
    int row_num = count_rows();

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char ts[32];
    strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M", t);

    FILE *f = fopen(CSV_FILE, "a");
    if (!f) {
        send_str(sock,
            "HTTP/1.1 500 Internal Server Error\r\n"
            "Content-Type: application/json\r\n\r\n"
            "{\"success\":false,\"error\":\"cannot open file\"}\n");
        return;
    }
    fprintf(f, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
            firstname, lastname, phone, email, start, end_, delivery, ts);
    fclose(f);

    send_str(sock, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n");
    cors_headers(sock);
    send_str(sock, "\r\n{\"success\":true}\n");
}

/* -------- GET /export -------- */
static void handle_export(int sock) {
    FILE *f = fopen(CSV_FILE, "rb");
    if (!f) {
        send_str(sock, "HTTP/1.1 404 Not Found\r\n\r\nยังไม่มีข้อมูล\n");
        return;
    }
    fseek(f, 0, SEEK_END); long size = ftell(f); rewind(f);

    char header[512];
    snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/csv; charset=utf-8\r\n"
        "Content-Disposition: attachment; filename=\"customers.csv\"\r\n"
        "Content-Length: %ld\r\n", size);
    send_str(sock, header);
    cors_headers(sock);
    send_str(sock, "\r\n");

    char buf[4096]; size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
        send(sock, buf, (int)n, 0);
    fclose(f);
}

/* ======== main ======== */
int main(void) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 10);

    printf("Server running on http://localhost:%d\n", PORT);
    printf("Press Ctrl+C to stop.\n");

    while (1) {
        struct sockaddr_in ca; socklen_t cl = sizeof(ca);
        int client_fd = accept(server_fd, (struct sockaddr*)&ca, &cl);
        if (client_fd < 0) continue;

        char buf[BUF_SIZE] = {0};
        recv(client_fd, buf, sizeof(buf)-1, 0);

        char method[8]={0}, path[128]={0};
        sscanf(buf, "%7s %127s", method, path);

        if (strcmp(method, "OPTIONS") == 0) {
            send_str(client_fd, "HTTP/1.1 204 No Content\r\n");
            cors_headers(client_fd);
            send_str(client_fd, "\r\n");

        } else if (strcmp(method, "POST") == 0 && strcmp(path, "/save") == 0) {
            char *body = strstr(buf, "\r\n\r\n");
            if (body) body += 4; else body = "";
            handle_save(client_fd, body);

        } else if (strcmp(method, "GET") == 0 && strcmp(path, "/export") == 0) {
            handle_export(client_fd);

        } else {
            send_str(client_fd, "HTTP/1.1 404 Not Found\r\n\r\nNot Found\n");
        }

        closesocket(client_fd);
    }

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}