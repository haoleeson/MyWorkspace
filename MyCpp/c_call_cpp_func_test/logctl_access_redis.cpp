#include "logctl_access_redis.h"

LogctlPublisher::LogctlPublisher() : LogctlSingleton() {
    COUT_DEBUG("#### LogctlPublisher::constructor() ####");
}

LogctlPublisher::~LogctlPublisher() {
    COUT_DEBUG("#### LogctlPublisher::destructor() ####");
}

void LogctlPublisher::update_a_logctl_configuration(const std::string& process, const std::string& container,
        const std::string& loglevel, const std::string& facility) {
    if (!m_db || !m_redis_client || process.length() <= 0 || container.length() <= 0) {
        COUT_ERROR("Can not exec update_a_logctl_configuration() with invalid param.");
        return;
    }
    std::vector<FieldValueTuple> fieldValues;
    if (loglevel.length() > 0) {
        fieldValues.push_back(std::make_pair(DB_LOGLEVEL_FIELD, loglevel));
    }
    if (facility.length() > 0) {
        fieldValues.push_back(std::make_pair(DB_FACILITY_FIELD, facility));
    }
    if (fieldValues.size() == 0) {
        COUT_ERROR("The both params of loglevel and facility are empty.");
        return;
    }

    if (is_swss_key_format(container, process)) {
//        swss::ProducerStateTable table(m_db, process);
//        table.set(process, fieldValues);
    } else {
        std::string redis_key = build_redis_key(process, container, true);
        for (const FieldValueTuple& fieldValue : fieldValues) {
//            m_redis_client->hset(redis_key, fvField(fieldValue), fvValue(fieldValue));
        }
//        swss::ProducerTable table(m_db, redis_key);
//        table.set(g_empty_str, fieldValues);
    }
}

void LogctlPublisher::update_mul_logctl_configuration(const std::vector<std::string>& process_vec,
        const std::string& container, const std::string& loglevel, const std::string& facility) {
    if (!m_db || container.length() <= 0 || (loglevel.length() <= 0 && facility.length() <= 0)) {
        COUT_ERROR("Can not exec update_mul_logctl_configuration() with invalid param.");
        return;
    }
    for (const std::string& process : process_vec) {
        update_a_logctl_configuration(process, container, loglevel, facility);
    }
}

LogctlSubscriber::LogctlSubscriber() : LogctlSingleton(), m_subscribeThread(nullptr), m_stop_flag(false),
        m_logctl_facility(g_empty_str), m_logctl_loglevel(g_empty_str) {
    m_facility_val = DEFAULT_LOGCTL_FACILITY_VAL;
    m_loglevel_val = DEFAULT_LOGCTL_LOGLEVEL_VAL;
    COUT_DEBUG("#### LogctlSubscriber::constructor() ####");
}

LogctlSubscriber::~LogctlSubscriber() {
    if (this->m_subscribeThread) {
        destroy_subscribe_thread();
    }
    COUT_DEBUG("#### LogctlSubscriber::destructor() ####");
}

int LogctlSubscriber::get_facility_val() {
    return m_facility_val;
}

int LogctlSubscriber::get_loglevel_val() {
    return m_loglevel_val;
}

void LogctlSubscriber::initialization(std::string container_name, std::string process_name, bool b_start_sub_thread) {
    m_container_name = valid_container(container_name) ? container_name : g_empty_str;
    m_process_name = valid_process(process_name, container_name) ? process_name : obtain_current_process_name();
    try {
//        m_db = new swss::DBConnector(LOGCTL_DB_INDEX, swss::DBConnector::DEFAULT_UNIXSOCKET, 0);
//        m_redis_client = new swss::RedisClient(m_db);
    } catch (const std::system_error& e) {
        COUT_ERROR("Logctl catches a system_error when new a swss::DBConnector: %s", e.what());
        m_db = nullptr;
        m_redis_client = nullptr;
        return;
    }
    if (b_start_sub_thread) {
        running_subscribe_thread();
    }
}

bool LogctlSubscriber::query_hashtab_value(const std::string& redis_key, const std::string& field,
        std::shared_ptr<std::string>& value) {
    if (!m_redis_client) {
        COUT_ERROR("Can not exec query_hashtab_value() with invalid param.");
        value = g_empty_str_ptr;
        return false;
    }
//    try {
//        value = m_redis_client->hget(redis_key, field);
//    } catch (std::runtime_error& e) {
//        value = g_empty_str_ptr;
//        return false;
//    }
    if (value == std::shared_ptr<std::string>(NULL)) {
        value = g_empty_str_ptr;
    }
    return true;
}

bool LogctlSubscriber::query_a_logctl_configuration(const std::string& process, const std::string& container,
        std::shared_ptr<std::string>& level, std::shared_ptr<std::string>& facility) {
    const std::string redis_key = build_redis_key(process, container);
    return query_hashtab_value(redis_key, DB_LOGLEVEL_FIELD, level) |
           query_hashtab_value(redis_key, DB_FACILITY_FIELD, facility);
}

/**
 * 监听线程服务函数
 * */
void LogctlSubscriber::logctl_val_syncd_func() {
    std::string sub_tab_key = build_redis_key(m_process_name, m_container_name);
//    std::shared_ptr<swss::DBConnector> db_loglevel = nullptr;
//    std::unique_ptr<swss::ConsumerTable> logctl_sub_table = nullptr;
//    std::shared_ptr<swss::Select> select = std::make_shared<swss::Select>();

    try {
//        db_loglevel = std::make_shared<swss::DBConnector>(LOGCTL_DB_INDEX, swss::DBConnector::DEFAULT_UNIXSOCKET, 0);
        // Add the subscribe table (eg. container#process or process:process)
        COUT_INFO("-------- thread : Start subscriber Table(%s) successfully --------", sub_tab_key.c_str());
//        logctl_sub_table = std::unique_ptr<swss::ConsumerTable>(new swss::ConsumerTable(db_loglevel.get(), sub_tab_key));
        COUT_INFO("-------- thread : Subscriber Table(%s) successfully --------", sub_tab_key.c_str());
//        select->addSelectable(logctl_sub_table.get());
    } catch (const std::system_error& e) {
        COUT_ERROR("System_error: \"%s\" had been thrown in logctl_val_syncd_func()", e.what());
        return;
    } catch (const std::exception& e) {
        COUT_ERROR("Exception: \"%s\" had been thrown in logctl_val_syncd_func()", e.what());
        return;
    }

    // Looping, Selecting and processing 
    while (!this->m_stop_flag) {
        COUT_DEBUG("-------- thread: while(true){...} Looping --------");

        // Get the events of change operation
//        swss::Selectable *sel = nullptr;
//        int ret = swss::Select::ERROR;
        try {
            COUT_DEBUG("-------- thread: Exec select()... start --------");
//            ret = select->select(&sel, SELECT_TIMEOUT_MS);
            COUT_DEBUG("-------- thread: Exec select()... end --------");
        } catch (const std::exception& e) {
            COUT_ERROR("Exception ERROR \"%s\" had been thrown in logctl_val_syncd_func() when exec select.", e.what());
        }

        // Check ret
//        if (ret != swss::Select::OBJECT) {
//            switch (ret) {
//                case swss::Select::ERROR:
//                    COUT_ERROR("-------- thread : no event occur.--------");
//                    break;
//                case swss::Select::TIMEOUT:
//                    COUT_DEBUG("-------- thread : select timeout.--------");
//                    break;
//                default:
//                    COUT_ERROR("-------- thread : select unknown return.--------");
//                    break;
//            }
//            continue;
//        }

        // Check select
//        if (sel != logctl_sub_table.get()) {
//            COUT_DEBUG("-------- thread : no change happened in target table.--------");
//            continue;
//        }

        // Extra data
        COUT_DEBUG("-------- thread : Start to extra data.--------");
        std::deque<KeyOpFieldsValuesTuple> entries;
//        dynamic_cast<swss::ConsumerTable *>(sel)->pops(entries);

        // Handle all popped change events of all selected tables
        for (const KeyOpFieldsValuesTuple& entry: entries) {
            const std::string key = kfvKey(entry);
            const std::string op = kfvOp(entry);
            // 【调测】
           COUT_DEBUG("-------- thread: start extra change TABLE(%s)\n    get data, key =\"%s\", op =\"%s\" --------",
                      sub_tab_key.c_str(), key.c_str(), op.c_str());
            
            // Ignore operations other than SET
            if (op != "SET") {
                continue;
            }

            // Extra the changed values of target key and deal with them based on different fields
            const std::vector<FieldValueTuple> values = kfvFieldsValues(entry);
            for (const FieldValueTuple& valuePair : values){
                const std::string& field = fvField(valuePair);
                const std::string& value = fvValue(valuePair);
                COUT_INFO("-------- thread: extra value \n    field = %s, value = %s --------", field.c_str(), value.c_str());
        
                // If the LOGLEVEL field changes, update m_logctl_loglevel and m_loglevel_val
                if (field == "LOGLEVEL" && value != m_logctl_loglevel) {
                    // 【调测】
                    COUT_INFO("-------- thread : LOGLEVEL has changed from %s to %s", m_logctl_loglevel.c_str(), value.c_str());

                    m_logctl_loglevel = value;
                    int val = conv_loglevel_str_2_int(value);
                    // auto lock = this->unique_lock();
                    m_loglevel_val = val;
                    // this->unlock(lock);
                }

                // If the FACILITY field changes, update m_logctl_facility and m_facility_val
                if (field == "FACILITY" && value != m_logctl_facility) {
                    // 【调测】
                    COUT_INFO("-------- thread : FACILITY has changed from %s to %s", m_logctl_facility.c_str(), value.c_str());

                    m_logctl_facility = value;
                    int val = conv_facility_str_2_int(value);
                    // auto lock = this->unique_lock();
                    m_facility_val = val;
                    // this->unlock(lock);
                }
            }
        }
    }
}

void LogctlSubscriber::destroy_subscribe_thread() {
    if (!this->m_subscribeThread) {
        return;
    }
    // auto lock = this->unique_lock();
    this->m_stop_flag = true;
    // this->unlock(lock);
    if (this->m_subscribeThread->joinable()) {
        this->m_subscribeThread->join(); // wait for thread finished
    }
    COUT_DEBUG("++++++ main. m_subscribeThread destory successfully ++++++");
    delete this->m_subscribeThread;
    this->m_subscribeThread = nullptr;
}

void LogctlSubscriber::running_subscribe_thread() {
    if (!m_redis_client) {
        COUT_ERROR("Can not exec running_subscribe_thread() when m_redis_client is nullptr.");
        return;
    }
    std::string sub_tab_key = build_redis_key(m_process_name, m_container_name);
    std::shared_ptr<std::string> value;

    if (query_hashtab_value(sub_tab_key, DB_LOGLEVEL_FIELD, value)) {
        m_logctl_loglevel = *value;
    } else {
        m_logctl_loglevel = DEFAULT_LOGCTL_LOGLEVEL;
//        m_redis_client->hset(sub_tab_key, DB_LOGLEVEL_FIELD, DEFAULT_LOGCTL_LOGLEVEL);
    }
    m_loglevel_val = conv_loglevel_str_2_int(m_logctl_loglevel);

    if (query_hashtab_value(sub_tab_key, DB_FACILITY_FIELD, value)) {
        m_logctl_facility = *value;
    } else {
        m_logctl_facility = DEFAULT_LOGCTL_FACILITY;
//        m_redis_client->hset(sub_tab_key, DB_FACILITY_FIELD, DEFAULT_LOGCTL_FACILITY);
    }
    m_facility_val = conv_facility_str_2_int(m_logctl_facility);

    // 起线程，创建线程监听 Redis 对应表
    if (this->m_subscribeThread) {
        destroy_subscribe_thread();
    }
    // auto lock = this->unique_lock();
    this->m_stop_flag = false;
    // this->unlock(lock);
    COUT_INFO("Ready to create a subscribeThread.");
    this->m_subscribeThread = new std::thread(&LogctlSubscriber::logctl_val_syncd_func, this);
    this->m_subscribeThread->detach();
}
