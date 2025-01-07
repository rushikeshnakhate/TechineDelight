
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
                delete this->ptr;
                this->ptr = uniqPtr.ptr;
                delete uniqPtr.ptr;
                uniqPtr.ptr = nullptr;
            }
        }

        T *operator->() {
            return ptr;
        }

        //the release() function relinquishes ownership of the managed object. It returns the raw pointer to the caller and sets the std::unique_ptr internal pointer to nullptr.
        T release() {
            T *temp = ptr;
            ptr = nullptr;
            return temp;
        }

        //Deletes the currently managed object (if any) and takes ownership of a new object provided as input.
        void reset(T *newPtr = nullptr) {
            delete this->ptr;
            this->ptr = newPtr;
        }
    };
}
