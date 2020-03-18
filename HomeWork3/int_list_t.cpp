#include "int_list_t.h"


int_list_t::int_list_t() {
    head = new node_t(0, nullptr, nullptr);
    tail = new node_t(0, head, nullptr);
    head->next = tail;
    _size = 0;
};

int_list_t::~int_list_t() {
}

void int_list_t::push_front(int new_val) {
    node_t *tmp = head->next;
    node_t *node = new node_t(new_val, head, tmp);
    tmp->prev = node;
    head->next = node;
    _size++;
}

void int_list_t::push_back(int new_val) {
    node_t *tmp = tail->prev;
    node_t *node = new node_t(new_val, tmp, tail);
    tmp->next = node;
    tail->prev = node;
    _size++;
}

const int &int_list_t::front() const {
    if (_size == 0) {
        std::cout << "Out of bounds" << std::endl;
    }
    return head->next->value;
}


int &int_list_t::front() {
    if (_size == 0) {
        std::cout << "Out of bounds" << std::endl;
    }
    return head->next->value;
}

const int &int_list_t::back() const {
    if (empty()) {
        std::cout << "Out of bounds" << std::endl;
        exit(-1);
    }
    return tail->prev->value;
}

int &int_list_t::back() {
    if (empty()) {
        std::cout << "Out of bounds" << std::endl;
        exit(-1);
    }
    return tail->prev->value;
}


size_t int_list_t::size() const {
    return _size;
}

void int_list_t::pop_front() {
    node_t *del_note = head->next;
    node_t *tmp = del_note->next;
    tmp->prev = head;
    head->next = tmp;
    delete del_note;
}

bool int_list_t::empty() const {
    return _size == 0;
}

void int_list_t::pop_back() {
    node_t *del_note = tail->prev;
    node_t *tmp = del_note->prev;
    tmp->next = tail;
    tail->prev = tmp;
    delete del_note;
}

void int_list_t::clear() {
    if (_size > 0) {
        node_t *pointer = head->next;
        for (int i = 0; i < _size; ++i) {
            node_t *tmp = pointer;
            pointer = pointer->next;
            delete tmp;
        }
        head->next = tail;
        tail->prev = head;
        _size = 0;
    }
}

int &int_list_t::operator[](size_t pos) {
    if (pos <= _size - 1) {
        node_t *pointer;
        if (pos <= _size / 2) {
            pointer = head->next;
            for (int i = 0; i < pos; ++i) {
                pointer = pointer->next;
            }
            return pointer->value;
        } else {
            pointer = tail->prev;
            for (int i = 0; i < _size - pos - 1; ++i) {
                pointer = pointer->prev;
            }
            return pointer->value;
        }
    } else {
        std::cout << "Out of bounds" << std::endl;
        exit(-1);
    }
}

const int &int_list_t::operator[](size_t pos) const {
    if (pos <= _size - 1) {
        node_t *pointer;
        if (pos <= _size / 2) {
            pointer = head->next;
            for (int i = 0; i < pos; ++i) {
                pointer = pointer->next;
            }
            return pointer->value;
        } else {
            pointer = tail->prev;
            for (int i = 0; i < _size - pos - 1; ++i) {
                pointer = pointer->prev;
            }
            return pointer->value;
        }
    } else {
        std::cout << "Out of bounds" << std::endl;
        exit(-1);
    }
}

void int_list_t::insert(size_t pos, int new_val) {
    if (pos <= _size - 1) {
        node_t *pointer;
        if (pos <= _size / 2) {
            pointer = head->next;
            for (int i = 0; i < pos; ++i) {
                pointer = pointer->next;
            }
            node_t *tmp = pointer->prev;
            node_t *new_node = new node_t(new_val, tmp, pointer);
            tmp->next = new_node;
            pointer->prev = new_node;
        } else {
            pointer = tail->prev;
            for (int i = 0; i < _size - pos - 1; ++i) {
                pointer = pointer->prev;
            }
            node_t *tmp = pointer->prev;
            node_t *new_node = new node_t(new_val, tmp, pointer);
            tmp->next = new_node;
            pointer->prev = new_node;
        }
        _size++;
    } else {
        std::cout << "Out of bounds" << std::endl;
        exit(-1);
    }
}

void int_list_t::swap(int_list_t &other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

void int_list_t::erase(size_t pos) {
    if (pos <= _size - 1) {
        node_t *pointer;
        if (pos <= _size / 2) {
            pointer = head->next;
            for (int i = 0; i < pos; ++i) {
                pointer = pointer->next;
            }
            pointer->prev->next = pointer->next;
            pointer->next->prev = pointer->prev;
            delete pointer;
        } else {
            pointer = tail->prev;
            for (int i = 0; i < _size - pos - 1; ++i) {
                pointer = pointer->prev;
            }
            pointer->prev->next = pointer->next;
            pointer->next->prev = pointer->prev;
            delete pointer;
        }
        _size--;
    } else {
        std::cout << "Out of bounds" << std::endl;
        exit(-1);
    }
}

int_list_t::int_list_t(const int_list_t &other) {
    head = new node_t(0, nullptr, nullptr);
    tail = new node_t(0, head, nullptr);
    head->next = tail;
    _size = other._size;
    for (int i = 0; i < _size; ++i) {
        push_back(other[i]);
    }
}




