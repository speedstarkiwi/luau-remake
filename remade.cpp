namespace luau {
    //extreme messy bcuz no time i did this while studying for final exams so mb skid
    void setobj69(uintptr_t L, void* obj1, const void* obj2) {
        const void* o2 = obj2;
        void* o1 = obj1;
        memcpy(o1, o2, sizeof(void*));
    }

    inline void lua_pushnil(std::uintptr_t rL) {//only push nil or nothing lmao
        const std::uintptr_t top_ptr = rL + top;
        const std::uintptr_t topp = *reinterpret_cast<std::uintptr_t*>(top_ptr);
        *reinterpret_cast<std::uintptr_t*>(topp) = LUA_TNIL;
        *reinterpret_cast<std::uintptr_t*>(top_ptr) += sizeof(std::uintptr_t);
    }

    inline std::uintptr_t lua_gettop(std::uintptr_t rL) {//used for arguments stupid skid
        const std::uintptr_t top_ptr = rL + top;
        const std::uintptr_t base_ptr = rL + base;
        const std::uintptr_t top_val = *reinterpret_cast<std::uintptr_t*>(top_ptr);
        const std::uintptr_t base_val = *reinterpret_cast<std::uintptr_t*>(base_ptr);
        return (top_val - base_val) >> 4;
    }

    inline void lua_settop(std::uintptr_t rL, int idx) {//tells us to set the top
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

    std::uintptr_t lua_index2addr(uintptr_t rL, std::int32_t idx)//index2 addr or cases to pseudo2 if idx is not matched correct
    {
        std::uintptr_t basee = rL + top;
        std::uintptr_t topp = rL + base;

        if (idx > 0)//if its greater then NULL lool
        {
            std::uintptr_t o = (*reinterpret_cast<std::uintptr_t*>(basee) + (idx - 1) * sizeof(std::uintptr_t));
            if (o >= *reinterpret_cast<std::uintptr_t*>(top))
                return (nilobject_address);
            else
                return o;
        }
        else if (idx > LUA_REGISTRYINDEX)//-10000 negative
        {
            return *reinterpret_cast<std::uintptr_t*>(top) + idx * sizeof(std::uintptr_t);//return this
        }
        else//none of the index match -> go to pseudo2 and let it handle the rest of the cases
        {
           // return lua_pseudo2addr(rL, idx);
        }
    }

    const uintptr_t luaA_toobject(uintptr_t rL, int idx)//technically converts a  stack index to a ptr
    {
        const uintptr_t p = lua_index2addr(rL, idx);
        return (p == nilobject_address) ? NULL : p;
    }

    uintptr_t lua_newthread(uintptr_t rL) {//no i didnt make cuz skid moment but it works tho :troll:
        return rL;
    }

    void lua_pushnumber(uintptr_t rL, double n)//spent 69 hours making it
    {
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(rL + top); 
        *(lua_Number*)(i_o) = (n); //is a lua numbar

        *reinterpret_cast<std::uintptr_t*>(rL + top) += sizeof(TValue);
    }
}
