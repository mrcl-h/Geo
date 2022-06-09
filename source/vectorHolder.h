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
        template <typename F>
            void execute (F& actingObject) {
                for (unsigned int i = 0; i < vec.size(); i++) {
                    actingObject.act (vec[i]);
                }
                vh.execute (actingObject);
            }
        template <typename F>
            bool executeTillTrue (F& actingObject) {
                for (unsigned int i = 0; i < vec.size(); i++) {
                    if (actingObject.act (vec[i])) {
                        return true;
                    }
                }
                return vh.executeTillTrue (actingObject);
            }
        template <typename F>
            void executeReverse (F& actingObject) {
                vh.executeReverse (actingObject);
                unsigned int s = vec.size();
                for (unsigned int i = 1; i <= s; i++) {
                    actingObject.act (vec[s-i]);
                }
            }
        template <typename F>
            bool executeReverseTillTrue (F& actingObject) {
                if (vh.executeReverseTillTrue (actingObject)) {
                    return true;
                }
                unsigned int s = vec.size();
                for (unsigned int i = 1; i <= s; i++) {
                    if (actingObject.act (vec[s-i])) {
                        return true;
                    }
                }
                return false;
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
        template <typename f>
            void execute (f& actingobject) {
                for (unsigned int i = 0; i < vec.size(); i++) {
                    actingobject.act (vec[i]);
                }
            }
        template <typename F>
            bool executeTillTrue (F& actingObject) {
                for (unsigned int i = 0; i < vec.size(); i++) {
                    if (actingObject.act (vec[i])) {
                        return true;
                    }
                }
                return false;
            }
        template <typename F>
            void executeReverse (F& actingObject) {
                unsigned int s = vec.size();
                for (unsigned int i = 1; i <= s; i++) {
                    actingObject.act (vec[s-i]);
                }
            }
        template <typename F>
            bool executeReverseTillTrue (F& actingObject) {
                unsigned int s = vec.size();
                for (unsigned int i = 1; i <= s; i++) {
                    if (actingObject.act (vec[s-i])) {
                        return true;
                    }
                }
                return false;
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

