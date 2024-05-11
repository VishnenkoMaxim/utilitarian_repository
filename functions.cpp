int WriteData(int fd, uint8_t* data, unsigned int size) {
    int res = 0;
    unsigned int sent_bytes = 0;
    while (sent_bytes < size) {
        res = write(fd, data + sent_bytes, size - sent_bytes);
        if (res <= 0) return -1;
        sent_bytes += res;
    }
    return sent_bytes;
}

int ReadData(int fd, uint8_t* data, int size, unsigned int timeout){
    int co = 0;
    int rval = -1;
    struct timeval tv;
    fd_set rfd;

    if( fd < 0 || !data || size <= 0 ) return 0;
    for(co = 0; ;){
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        FD_ZERO(&rfd);
        FD_SET( fd, &rfd );
        //usleep(10);
        rval = select(fd + 1, &rfd, nullptr, nullptr, &tv);
        if( rval < 0 ) return -1;
        if (rval == 0) return co;

        rval = read(fd, data + co, size - co );
        if(rval <= 0) return co;

        co+=rval;
        if( co >= size ) break;
    }
    return co;
}

uint16_t ConvertToHost2Bytes(const uint8_t* buf){
    uint16_t val;
    memcpy(&val, buf, sizeof(val));
    return ntohs(val);
}

uint32_t ConvertToHost4Bytes(const uint8_t* buf){
    uint32_t val;
    memcpy(&val, buf, sizeof(val));
    return ntohl(val);
}

#include <chrono>
class CTimeMeasurer {
public:
    CTimeMeasurer() {
        start_time = system_clock::now();
    }

    void start() {
        start_time = system_clock::now();
    }

    void stop() {
        stop_time = system_clock::now();

        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(stop_time-start_time).count();
        auto m_sec = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time-start_time).count() - seconds*100;
        cout << "Total elapsed time: " << seconds << "." << m_sec << " sec" << endl;
    }

private:
    system_clock::time_point start_time;
    system_clock::time_point stop_time;
};
