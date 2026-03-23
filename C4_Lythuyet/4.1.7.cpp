if (fork() == 0) {
    close(listener); // dóng socket l?ng nghe
    // x? lý client
}
