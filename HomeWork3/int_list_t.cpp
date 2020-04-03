#include "int_list_t.h"

int_list_t::int_list_t() {
    head = new node_t(-1, nullptr, nullptr);
    tail = new node_t(-2, head, nullptr);
    head->next = tail;
    _size = 0;
    is_reversed = false;
}

int_list_t::~int_list_t() {
    clear();
    delete get_head();
    delete get_tail();
}

size_t int_list_t::size() const {
    return _size;
}

bool int_list_t::empty() const {
    return _size == 0;
}

void int_list_t::reverse() {
    is_reversed = !is_reversed;
}

void int_list_t::swap(int_list_t &other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(is_reversed, other.is_reversed);
}

int_list_t::node_t *int_list_t::get_head() const {
    return !is_reversed ? head : tail;
}

int_list_t::node_t *int_list_t::get_tail() const {
    return !is_reversed ? tail : head;
}

int &int_list_t::back() {
    return !is_reversed ? tail->prev->value : head->next->value;
}

const int int_list_t::back() const {
    return !is_reversed ? tail->prev->value : head->next->value;
}

int &int_list_t::front() {
    return !is_reversed ? head->next->value : tail->prev->value;
}

const int int_list_t::front() const {
    return !is_reversed ? head->next->value : tail->prev->value;
}

int_list_t::node_t *int_list_t::get(int pos) const {
    if (pos <= size() / 2) {
        node_t *pointer = get_head();
        do {
            pointer = pointer->get_next(is_reversed);
        } while (pos--);

        return pointer;
    } else {
        node_t *pointer = get_tail();
        do {
            pointer = pointer->get_prev(is_reversed);
        } while (pos--);

        return pointer;
    }

}

void int_list_t::insert(size_t pos, int new_val) {
    if (!is_reversed) {
        node_t *pointer = get(pos);
        node_t *new_node = new node_t(new_val, pointer->get_prev(is_reversed), pointer);
        pointer->get_prev(is_reversed)->set_next(is_reversed, new_node);
        pointer->set_prev(is_reversed, new_node);
    } else {
        node_t *pointer = get(pos);
        node_t *new_node = new node_t(new_val, pointer, pointer->get_prev(is_reversed));
        pointer->get_prev(is_reversed)->set_next(is_reversed, new_node);
        pointer->set_prev(is_reversed, new_node);
    }
    _size++;
}

int &int_list_t::operator[](size_t pos) {
    node_t *pointer = get(pos);
    return pointer->value;
}

const int &int_list_t::operator[](size_t pos) const {
    node_t *pointer = get(pos);
    return pointer->value;
}

void int_list_t::push_front(int new_val) {
    insert(0, new_val);
}

void int_list_t::push_back(int new_val) {
    reverse();
    insert(0, new_val);
    reverse();
}

void int_list_t::erase(size_t pos) {
    node_t *pointer = get(pos);
    pointer->get_prev(is_reversed)->set_next(is_reversed, pointer->get_next(is_reversed));
    pointer->get_next(is_reversed)->set_prev(is_reversed, pointer->get_prev(is_reversed));
    delete pointer;
    _size--;
}

void int_list_t::pop_front() {
    erase(0);
}

void int_list_t::pop_back() {
    reverse();
    erase(0);
    reverse();
}

int_list_t::int_list_t(const int_list_t &other) {
    _size = other.size();
    head = new node_t(0, nullptr, nullptr);
    node_t *pointer = other.head;
    node_t *prev = head;
    for (int i = 0; i < _size; ++i) {
        node_t *new_node = new node_t(pointer->next->value, prev, nullptr);
        prev->next = new_node;
        prev = new_node;
        pointer = pointer->next;
    }
    tail = new node_t(0, prev, nullptr);
    prev->next = tail;

    is_reversed = other.is_reversed;
}

int_list_t::int_list_t(size_t count, int value) {
    head = new node_t(-1, nullptr, nullptr);
    tail = new node_t(-2, head, nullptr);
    head->next = tail;
    is_reversed = false;
    _size = 0;
    for (int i = 0; i < count; ++i) {
        push_back(value);
    }

}

int_list_t &int_list_t::operator=(const int_list_t &other) {
    if (this != &other) {
        clear();
        node_t *pointer = other.head;
        node_t *prev = head;
        _size = other._size;
        for (int i = 0; i < _size; ++i) {
            node_t *new_node = new node_t(pointer->next->value, prev, nullptr);
            prev->next = new_node;
            prev = new_node;
            pointer = pointer->next;
        }
        tail->prev = prev;
        prev->next = tail;

        is_reversed = other.is_reversed;
    }
    return *this;
}

void int_list_t::clear() {
    if (!empty()) {
        return;
    }
    node_t *pointer = head->next;
    node_t *next = pointer->next;
    for (int i = 0; i < size(); ++i) {
        delete pointer;
        pointer = next;
        next = pointer->next;
    }
    head->next = tail;
    tail->prev = head;
}

std::ostream &operator<<(std::ostream &stream, const int_list_t &list) {
    auto pointer = list.get_head();
    pointer = pointer->get_next(list.is_reversed);
    while (pointer != list.get_tail()) {
        stream << pointer->value << ' ';
        pointer = pointer->get_next(list.is_reversed);
    }
    return stream;
}

int_list_t int_list_t::splice(size_t start_pos, size_t count) {
    int_list_t new_list;
    new_list.is_reversed = is_reversed;
    node_t *pointer = get_head();

    for (int i = 0; i < start_pos + 1; ++i)
        pointer = pointer->get_next(is_reversed);

    node_t *prev_p = pointer->get_prev(is_reversed);

    new_list.get_head()->set_next(is_reversed, pointer);

    for (int i = 0; i < count - 1; ++i)
        pointer = pointer->get_next(is_reversed);

    new_list.get_tail()->set_prev(is_reversed, pointer);

    node_t *next_p = pointer->get_next(is_reversed);

    prev_p->set_next(is_reversed, next_p);
    next_p->set_prev(is_reversed, prev_p);

    _size -= count;
    new_list._size = count;

    return new_list;
}

std::istream &operator>>(std::istream &stream, int_list_t &list) {
    int tmp = 0;
    list.clear();
    while (stream >> tmp) {
        list.push_back(tmp);
    }
    return stream;
}


int_list_t &int_list_t::merge(int_list_t &other) {
    if (is_reversed == other.is_reversed) {
        get_tail()->get_prev(is_reversed)->set_next(is_reversed, other.get_head()->get_next(is_reversed));
        other.get_tail()->get_prev(is_reversed)->set_next(is_reversed, get_tail());
        other.get_head()->set_next(is_reversed, other.get_tail());
        other.get_tail()->set_prev(is_reversed, other.get_head());
        _size += other.size();
        other._size = 0;
        return *this;
    }
    if (is_reversed) {
        true_revers();
        get_tail()->get_prev(is_reversed)->set_next(is_reversed, other.get_head()->get_next(is_reversed));
        other.get_tail()->get_prev(is_reversed)->set_next(is_reversed, get_tail());
        other.get_head()->set_next(is_reversed, other.get_tail());
        other.get_tail()->set_prev(is_reversed, other.get_head());
        _size += other.size();
        other._size = 0;
        return *this;
    }
    return *this;
}

void int_list_t::true_revers() {
//    is_reversed = false;
//    node_t *tmp = head->next;
//    node_t *pointer = head->next;
//    node_t *new_tmp;
//
//    for (int i = 0; i < size(); ++i) {
//        new_tmp = pointer->prev;
//        pointer->prev = pointer->next;
//        pointer->next = new_tmp;
//        pointer = pointer->prev;
//    }
//    head->next = tail->prev;
//    tail->prev = tmp;

}

