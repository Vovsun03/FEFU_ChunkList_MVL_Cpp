#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

struct Chunk {
    int value;
    int count;
    Chunk* next;
};

class ChunkList{
public:
ChunkList(int chunkSize) : chunkSize(chunkSize), last(nullptr) {}

void add(int value) {
    if (last && last->count < chunkSize) {
        last->count++;
        last->value = value;
    } else {
        Chunk* newChunk = new Chunk{value, 1, nullptr};
        if (last) last->next = newChunk;
        last = newChunk;
    }
}

void remove(int value) {
    Chunk* prev = nullptr;
    Chunk* curr = root;
    while (curr) {
        if (curr->value == value) {
            if (curr->count > 1) {
                curr->count--;
                if (curr == last && curr->count == 0) {
                    last =prev;
                    delete curr;
                }
            } else if (curr == root) {
                root = curr->next;
                delete curr;
            } else {
                prev->next = curr->next;
                delete curr;
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

bool find(int value) {
    Chunk* curr = root;
    while (curr) {
        if (curr->value == value) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

int size() {
    int count = 0;
    Chunk* curr = root;
    while (curr) {
        count += curr->count;
        curr = curr->next;
    }
    return count;
}

private:
int chunkSize;
Chunk* root = nullptr;
Chunk* last = nullptr;
};

TEST(ChunkListTest, Add) {
ChunkList list(2);
list.add(1);
list.add(2);
list.add(3);
list.add(4);
ASSERT_EQ(list.size(), 4);
}

TEST(ChunkListTest, Remove) {
ChunkList list(2);
list.add(1);
list.add(2);
list.add(3);
list.add(4);
list.remove(2);
ASSERT_EQ(list.size(), 3);
}

TEST(ChunkListTest, Find) {
ChunkList list(2);
list.add(1);
list.add(2);
list.add(3);
list.add(4);
ASSERT_TRUE(list.find(2));
ASSERT_FALSE(list.find(5));
}

TEST(ChunkListTest, Size) {
ChunkList list(2);
list.add(1);
list.add(2);
list.add(3);
list.add(4);
list.remove(2);
ASSERT_EQ(list.size(), 3);
}