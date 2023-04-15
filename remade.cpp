namespace rewritten {
    inline void lua_pushnil(std::uintptr_t rL) {
        const std::uintptr_t top_ptr = rL + top;
        const std::uintptr_t topp = *reinterpret_cast<std::uintptr_t*>(top_ptr);
        *reinterpret_cast<std::uintptr_t*>(topp) = LUA_TNIL;
        *reinterpret_cast<std::uintptr_t*>(top_ptr) += sizeof(std::uintptr_t);
    }

    inline std::uintptr_t lua_gettop(std::uintptr_t rL) {
        const std::uintptr_t top_ptr = rL + top;
        const std::uintptr_t base_ptr = rL + base;
        const std::uintptr_t top_val = *reinterpret_cast<std::uintptr_t*>(top_ptr);
        const std::uintptr_t base_val = *reinterpret_cast<std::uintptr_t*>(base_ptr);
        return (top_val - base_val) >> 4;
    }

    inline void lua_settop(std::uintptr_t rL, std::int32_t idx) {
        const std::uintptr_t top_ptr = rL + top;
        const std::uintptr_t base_ptr = rL + base;
        std::uintptr_t top_val = *reinterpret_cast<std::uintptr_t*>(top_ptr);
        std::uintptr_t base_val = *reinterpret_cast<std::uintptr_t*>(base_ptr);

        if (idx >= 0) {
            while (top_val < base_val + (idx << 4))
                *reinterpret_cast<std::uintptr_t*>(top_val++) = 0;
            *reinterpret_cast<std::uintptr_t*>(top_ptr) = base_val + (idx << 4);
        }
        else {
            top_val += (idx << 4) + 16;
            if (top_val < base_val)
                top_val = base_val;
            *reinterpret_cast<std::uintptr_t*>(top_ptr) = top_val;
        }
    }

    std::uintptr_t lua_index2addr(uintptr_t rL, std::int32_t idx)
    {
        std::uintptr_t basee = rL + top;
        std::uintptr_t topp = rL + base;

        if (idx > 0)
        {
            std::uintptr_t o = (*reinterpret_cast<std::uintptr_t*>(basee) + (idx - 1) * sizeof(std::uintptr_t));
            if (o >= *reinterpret_cast<std::uintptr_t*>(top))
                return reinterpret_cast<std::uintptr_t>(nullptr);
            else
                return o;
        }
        else if (idx > -10000)
        {
            return *reinterpret_cast<std::uintptr_t*>(top) + idx * sizeof(std::uintptr_t);
        }
        else
        {
            return lua_pseudo2addr(rL, idx);
        }
    }

}
