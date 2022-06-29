#include <vector>

template <typename U, typename... T>
class vectorHolder;

template <typename U, typename... T>
static inline std::vector<U>& getVectorFromHolder (vectorHolder<U, T...>& ii);

template <typename U, typename... T>
static inline const std::vector<U>& getVectorFromHolder (const vectorHolder<U, T...>& ii);

template <typename U, typename... T>
class vectorHolder {
    private: 
        std::vector<U> vec;
        vectorHolder<T...> vh;
    public:
        std::vector<U>& getOwnVector () {
            return vec;
        }
        const std::vector<U>& getOwnVector () const {
            return vec;
        }
        template <typename M>
            std::vector<M>& fwdVector () {
                return getVectorFromHolder<M> (vh); 
            }
        template <typename M>
            std::vector<M>& getVector () {
                return getVectorFromHolder <M> (*this);
            }
        template <typename M>
            const std::vector<M>& fwdVector () const {
                return getVectorFromHolder<M> (vh); 
            }
        template <typename M>
            const std::vector<M>& getVector () const {
                return getVectorFromHolder <M> (*this);
            }
        void clear () {
            vec.clear();
            vh.clear();
        }
};

template <typename U>
class vectorHolder<U> {
    private:
        std::vector<U> vec;
    public:
        std::vector<U>& getOwnVector () {
            return vec;
        }
        const std::vector<U>& getOwnVector () const {
            return vec;
        }
        template <typename M>
            std::vector<M>& fwdVector () = delete;

        template <typename M>
            std::vector<M>& getVector () {
                return getVectorFromHolder <M> (*this); 
            }
        template <typename M>
            const std::vector<M>& getVector () const {
                return getVectorFromHolder <M> (*this); 
            }
        void clear () {
            vec.clear();
        }
};


template <typename U, typename... T>
static inline std::vector<U>& getVectorFromHolder (vectorHolder<U, T...>& ii) {
    return ii.getOwnVector();    
}

template <typename U, typename... T>
static inline std::vector<U>& getVectorFromHolder (vectorHolder<T...>& ii) {
    return ii.template fwdVector<U>();
}

template <typename U, typename... T>
static inline const std::vector<U>& getVectorFromHolder (const vectorHolder<U, T...>& ii) {
    return ii.getOwnVector();    
}

template <typename U, typename... T>
static inline const std::vector<U>& getVectorFromHolder (const vectorHolder<T...>& ii) {
    return ii.template fwdVector<U>();
}
