
//
// Created by USER on 1/6/2025.
//
namespace custom {
    template<typename T>
    class UniqPtr {
        T *ptr{nullptr};
    public:
        explicit UniqPtr(T *t = nullptr) : ptr{t} {}

        ~UniqPtr() {
            delete ptr;
        }

        UniqPtr(const UniqPtr &ptr) = delete;

        UniqPtr &operator=(const UniqPtr &ptr) = delete;

        UniqPtr(const UniqPtr &&newObject) noexcept: ptr{newObject.ptr} {
            newObject.ptr = nullptr;
        }

        UniqPtr &operator=(UniqPtr &&uniqPtr) noexcept {
            if (this != uniqPtr) {
                delete uniqPtr;
                this->ptr = uniqPtr.ptr;
                uniqPtr.ptr = nullptr;
            }
        }

        T *operator->() {
            return ptr;
        }

    };
}
