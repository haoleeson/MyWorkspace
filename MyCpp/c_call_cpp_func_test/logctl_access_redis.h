#ifndef LOGCTL_ACCESS_REDIS_H
#define LOGCTL_ACCESS_REDIS_H

#include <iostream>
#include <vector>
#include <string>
#include <atomic> // std::atomic_bool, std::atomic_int
#include <memory> // std::shared_ptr
#include <thread> // detach(), reset(), sleep_for()
#include <deque> // std::deque
// #include <pthread.h>
// #include <mutex> // std::mutex(), std::unique_lock
// #include <chrono> // std::chrono
#include <unistd.h> // getpid()
#include <stdexcept> // std::runtime_error
#include <system_error> // std::system_error
#include <functional> // std::bind()
// #include <dirent.h>
// #include <cstdio>
//#include "../common/dbconnector.h" // DBConnector
//#include "../common/redisclient.h" // RedisClient, keys()
//#include "../common/producerstatetable.h" // Producerstatetable::set() (swss process)
//#include "../common/producertable.h" // ProducerTable::set() (common process)
//#include "../common/consumertable.h" // ConsumerTable
//#include "../common/select.h" // Select
//#include "../common/selectable.h" // Selectable
#include "common_data_definition.h"


// #define MAIN_THREAD_SLEEP_SEC           5
// #define SUB_THREAD_SLEEP_SEC            2
// #define SUB_TABLE_NAME                  "radv#radvd"

/**
 * @brief Logctl singleton base class which records database connection information
 * @describe: CRTP(Curiously recurring template pattern) 奇异循环模板模式；
 */
template<typename T>
class LogctlSingleton {
public:
    LogctlSingleton(const LogctlSingleton&) = delete;
    LogctlSingleton& operator =(const LogctlSingleton&) = delete;
    static T* get_instance() noexcept(std::is_nothrow_constructible<T>::value) {
        // Thread safe
        static T m_instance;
        return &m_instance;
    }

protected:
    LogctlSingleton() : m_container_name(g_empty_str), m_process_name(g_empty_str),
                        m_db(nullptr), m_redis_client(nullptr) {
        COUT_DEBUG("#### LogctlSingleton::constructor() ####");
    }

    ~LogctlSingleton() {
        if (m_db) {
            delete m_db;
        }
        if (m_redis_client) {
            delete m_redis_client;
        }
        COUT_DEBUG("#### LogctlSingleton::destructor() ####");
    }

public:
    std::string get_process_name() {
        return m_process_name;
    }

    std::string get_container_name() {
        return m_container_name;
    }

    void initialization(std::string container_name = g_empty_str, std::string process_name = g_empty_str) {
        m_container_name = container_name;
        m_process_name = (process_name != g_empty_str) ? process_name : obtain_current_process_name();
        try {
//            m_db = new swss::DBConnector(LOGCTL_DB_INDEX, swss::DBConnector::DEFAULT_UNIXSOCKET, 0);
//            m_redis_client = new swss::RedisClient(m_db);
        } catch (const std::system_error& e) {
            COUT_ERROR("Logctl catches a system_error when new a swss::DBConnector: %s", e.what());
            m_db = nullptr;
            m_redis_client = nullptr;
        }
    }

protected:
    std::string obtain_current_process_name() {
        static const int MAX_PROC_SIZE = 1024;
        bool b_obtain_suss = false;
        char buf[MAX_PROC_SIZE];
        char proc_name[MAX_PROC_SIZE] = {0};
        int cur_pid = getpid();
        std::string pidPath = std::string("/proc/").append(std::to_string(cur_pid)).append("/status");

        FILE *fp = fopen(pidPath.c_str(), "r");
        if (fp != NULL && fgets(buf, MAX_PROC_SIZE - 1, fp) != NULL) {
            sscanf(buf, "%*s %s", proc_name);
            b_obtain_suss = true;
        }
        if (fp) {
            fclose(fp);
        }
        return b_obtain_suss ? std::string(proc_name) : std::string(g_empty_str);
    }

protected:
    std::string         m_process_name;
    std::string         m_container_name;
//    swss::DBConnector*  m_db;
//    swss::RedisClient*  m_redis_client;
    void*  m_db;
    void*  m_redis_client;
};

/**
 * @brief Logctl Singleton publisher class to update the logctl configuration value to redis
 * 
 */
class LogctlPublisher : public LogctlSingleton<LogctlPublisher> {
    // NOTICE: needs to be friend in order to access the private constructor/destructor
    friend class LogctlSingleton<LogctlPublisher>;

public:
    LogctlPublisher(const LogctlPublisher&) = delete;
    LogctlPublisher& operator =(const LogctlPublisher&) = delete;

private:
    LogctlPublisher();
    ~LogctlPublisher();

public:
    void update_a_logctl_configuration(const std::string& process, const std::string& container,
        const std::string& loglevel, const std::string& facility);
    void update_mul_logctl_configuration(const std::vector<std::string>& process_vec, const std::string& container,
        const std::string& loglevel, const std::string& facility);
};

/**
 * @brief Logctl Singleton subscriber class to query the logctl configuration value from redis
 * 
 */
class LogctlSubscriber : public LogctlSingleton<LogctlSubscriber> {
    // NOTICE: needs to be friend in order to access the private constructor/destructor
    friend class LogctlSingleton<LogctlSubscriber>;

public:
    LogctlSubscriber(const LogctlSubscriber&) = delete;
    LogctlSubscriber& operator =(const LogctlSubscriber&) = delete;

private:
    LogctlSubscriber();
    ~LogctlSubscriber();

public:
    void initialization(std::string container_name = g_empty_str, std::string process_name = g_empty_str, 
        bool b_start_sub_thread = false);
    int get_facility_val();
    int get_loglevel_val();
    bool query_a_logctl_configuration(const std::string& process, const std::string& container,
        std::shared_ptr<std::string>& level, std::shared_ptr<std::string>& facility);

private:
    bool query_hashtab_value(const std::string& redis_key, const std::string& field,
        std::shared_ptr<std::string>& value);
    // using UniqueLock = std::unique_lock<std::mutex>;
    // UniqueLock unique_lock() const { return UniqueLock(m_mutex); }
    // // NOLINTNEXTLINE (runtime/references)
    // void unlock(UniqueLock &lock) const { lock.unlock(); }
    void logctl_val_syncd_func();
    void destroy_subscribe_thread();
    void running_subscribe_thread();

private:
    std::thread* m_subscribeThread;
    std::string m_logctl_facility;
    std::string m_logctl_loglevel;
    std::atomic_int m_facility_val;
    std::atomic_int m_loglevel_val;
    std::atomic_bool m_stop_flag;
    // volatile int m_facility_val;
    // volatile int m_loglevel_val;
    // mutable std::mutex m_mutex{};
};


#endif /* LOGCTL_ACCESS_REDIS_H */
