#include <cstdlib>

//=============================================================================
//== NodeSkipList =============================================================
//=============================================================================

template<class Value, class Key, int numLevels>
void NodeSkipList<Value, Key, numLevels>::clear(void) {
    for (int i = 0; i < numLevels; ++i) {
        this->m_nextjump[i] = 0;
    }
    this->m_levelHighest = -1;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void) {
    clear();
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key) {
    clear();

    this->m_key = key;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key, Value value) {
    clear();

    this->m_key = key;
    this->m_value = value;
}
//=============================================================================
//== End of: NodeSkipList =====================================================
//=============================================================================

//=============================================================================
//== SkipList =================================================================
//=============================================================================
template<class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability) {
    m_probability = probability;
    for (int i = 0; i < numLevels; ++i) {
        // Lets use m_pPreHead as a final sentinel element
        // Lets not. Lets use NULL as a final sentinel element because
        // it is default value in m_nextjump of a cleared node.
        this->m_pPreHead->m_nextjump[i] = NULL;
    }
    this->m_pPreHead->m_levelHighest = numLevels - 1;
}


template<class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(Value value, Key key) {
    int maxH = -1;
    int prob_margin = m_probability * RAND_MAX;
    while (rand() > prob_margin && (maxH < numLevels - 1)) {
        maxH++;
    }
    auto node = new TypeNode(key, value);
    node->m_levelHighest = maxH;
    auto current = this->m_pPreHead;
    TypeNode *next;
    int currentH = maxH;
    while (true) {
        if (currentH == -1) {
            next = current;
            while ((next = next->m_next) != this->m_pPreHead && next->m_key < key) {
                current = next;
            }
            node->m_next = next;
            current->m_next = node;
            break;
        }
        /*
        if (current->m_levelHighest<currentH){
            currentH = current->m_levelHighest;
        }
         */
        next = current->m_nextjump[currentH];
        while (next != NULL && next->m_key < key) {
            current = next;
            next = current->m_nextjump[currentH];
        }
        // next == this->m_prehead || next != value -> next should be driven to the end if height<=i
        if (currentH <= maxH) {
            node->m_nextjump[currentH] = next;
            current->m_nextjump[currentH] = node;
        }
        --currentH;
    }
}

template<class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::remove(TypeNode *node) {
    int currentH = numLevels - 1;
    auto current = this->m_pPreHead;
    TypeNode *next;
    while (true) {
        if (currentH == -1) {
            // usual orderlist search
            next = current;
            while ((next = next->m_next) != this->m_pPreHead && next->m_key < node->m_key) {
                current = next;
            }
            if (next != this->m_pPreHead && next->m_key == node->m_key) {
                current->m_next = next->m_next;
                delete next; // delete
            }
            break;
        }
        if (current->m_levelHighest < currentH) {
            currentH = current->m_levelHighest;
        }
        next = current->m_nextjump[currentH];
        while (next != NULL && next->m_key < node->m_key) {
            current = next;
            next = current->m_nextjump[currentH];
        }
        if (next == NULL || next->m_key != node->m_key) {
            --currentH;
            continue;
        }
        // next->m_key==key
        current->m_nextjump[currentH] = next->m_nextjump[currentH];
        --currentH;
    }
}

template<class Value, class Key, int numLevels>
auto SkipList<Value, Key, numLevels>::findLastLessThan(Key key) const -> TypeNode * {
    int currentH = numLevels - 1;
    auto current = this->m_pPreHead;
    TypeNode *next;
    while (true) {
        if (currentH == -1) {
            // usual orderlist search
            next = current;
            while ((next = next->m_next) != this->m_pPreHead && next->m_key < key) {
                current = next;
            }
            return current == this->m_pPreHead ? NULL : current; //returns NULL if all elements >= key
        }
        if (current->m_levelHighest < currentH) {
            currentH = current->m_levelHighest;
        }
        auto next = current->m_nextjump[currentH];
        while (next != NULL && next->m_key < key) {
            current = next;
            next = next->m_nextjump[currentH];
        }
        --currentH;
    }
}

template<class Value, class Key, int numLevels>
auto SkipList<Value, Key, numLevels>::findFirst(Key key) const -> TypeNode * {
    int currentH = numLevels - 1;
    auto current = this->m_pPreHead;
    while (true) {
        if (current->m_levelHighest < currentH) {
            currentH = current->m_levelHighest;
        }
        auto next = current->m_nextjump[currentH];
        while (next != NULL && next->m_key < key) {
            current = next;
            next = next->m_next;
        }
        if (next == NULL || next->m_key != key) {
            if (currentH == 0) {
                // usual orderlist search
                next = current;
                while ((next = next->m_next) != this->m_pPreHead && next->m_key < key) {
                    current = next;
                }
                if (current != this->m_pPreHead && current->m_key == key) {
                    return current;
                }
                return NULL;
            }
            --currentH;
            continue;
        }
        // next->m_key==key
        return next;
    }
}









// Put your code here

//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================
