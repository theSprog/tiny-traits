#pragma once

#define DENY_COPY(Type)      \
    Type(const Type&) = delete; \
    Type& operator=(const Type&) = delete;

#define DENY_MOVE(Type) \
    Type(Type&&) = delete; \
    Type& operator=(Type&&) = delete;

#define DENY_COPY_MOVE(Type) \
    DENY_COPY(Type)              \
    DENY_MOVE(Type)

