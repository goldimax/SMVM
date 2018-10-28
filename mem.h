//
// Created by goldimax on 18-10-28.
//

#pragma once

#include <sys/mman.h>
#include "global.h"
#include "i18n/i18n.h"

void *getMen(size_t size) {
    void *ptr = mmap(NULL, size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, 0, 0);
    if (ptr == (void*)-1) throw;
    return ptr;
}
