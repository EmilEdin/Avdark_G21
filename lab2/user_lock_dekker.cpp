#include "user_locks.hpp"

user_lock_dekker::user_lock_dekker()
    : user_lock() {
    m_flag[0] = m_flag[1] = false;
    m_turn = false;
}

void user_lock_dekker::lock(int thread_id) {
    // TODO: Implement the lock acquire part of the Dekker algorithm here
    int i = thread_id;
    int j = 1 - thread_id;
    
    m_flag[i].store(true);
    // fence
    while (m_flag[j] == true) {
        if (m_turn != i) {
            m_flag[i].store(false);
            while (m_turn != i) {
                // do nothing
            }
            m_flag[i].store(true);
            // fence
        }   
    }
}

void user_lock_dekker::unlock(int thread_id) {
    // TODO: Implement the lock release part of the Dekker algorithm here
    int i = thread_id;
    int j = 1 - thread_id;
    
    m_turn.store(j);
    m_flag[i].store(false);
}
