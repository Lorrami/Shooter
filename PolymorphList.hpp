#ifndef POLYMORPH_LIST_HPP
#define POLYMORPH_LIST_HPP

#include <utility>
#include <cmath>
#include <cstdlib>
#include <typeindex>
#include <type_traits>
#include <vector>
#include <cassert>

class UntypedList{
    using TypeMoveCtor = void (*)(void *src_obj, void *dst_obj);
    using TypeCopyCtor = void (*)(const void *src_obj, void *dst_obj);
    using TypeDtor = void (*)(void *obj);
private:
    void *m_Memory = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;
    size_t m_TypeSize = 0;
    TypeMoveCtor m_MoveCtor = nullptr;
    TypeCopyCtor m_CopyCtor = nullptr;
    TypeDtor m_Dtor = nullptr;
private:

    template<typename Type, std::enable_if_t<std::is_move_constructible<Type>::value, bool> = true>
    void AssignMove(void *){
        m_MoveCtor = [](void *src, void *dst) {
            new(dst)Type(std::move((Type &&) (*(Type *) src)));
        };
    }

    template<typename Type>
    void AssignMove(...){ }

    template<typename Type, std::enable_if_t<std::is_copy_constructible<Type>::value, bool> = true>
    void AssignCopy(void *){
        m_CopyCtor = [](const void *src, void *dst) {
            new(dst)Type(((const Type &) (*(const Type *) src)));
        };
    }

    template<typename Type>
    void AssignCopy(...){ }
public:

    template<typename Type>
    UntypedList(Type *):
            m_TypeSize(sizeof(Type))
    {
        AssignMove<Type>(nullptr);
        AssignCopy<Type>(nullptr);

        m_Dtor = [](void *obj){
            ((Type*)obj)->~Type();
        };
    }

    UntypedList(UntypedList &&other)noexcept:
            m_TypeSize(other.m_TypeSize)
    {
        *this = std::move(other);
    }

    ~UntypedList(){
        Clear();
    }

    UntypedList &operator=(UntypedList &&other)noexcept{
        m_Memory = other.m_Memory;
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        m_TypeSize = other.m_TypeSize;
        m_MoveCtor = other.m_MoveCtor;
        m_CopyCtor = other.m_CopyCtor;
        m_Dtor = other.m_Dtor;

        other.m_Memory = nullptr;
        other.m_Size = 0;
        other.m_Capacity = 0;
        other.m_TypeSize = 0;
        other.m_MoveCtor = nullptr;
        other.m_CopyCtor = nullptr;
        other.m_Dtor = nullptr;

        return *this;
    }

    void AddMove(void *obj){
        Reserve(m_Size + 1);

        m_MoveCtor(obj, operator[](m_Size++));
    }
    void AddCopy(const void *obj){
        Reserve(m_Size + 1);

        m_CopyCtor(obj, operator[](m_Size++));
    }

    void Reserve(size_t size){
        if(size <= m_Capacity)return;

        m_Capacity = (m_Capacity + 1) * 2;

        uint8_t *new_array = (uint8_t*)std::malloc(m_TypeSize * m_Capacity);
        uint8_t *old_array = (uint8_t*)m_Memory;

        for(int i = 0; i<m_Size; i++){
            uint8_t *src = old_array + m_TypeSize * i;
            uint8_t *dst = new_array + m_TypeSize * i;

            MoveOrCopy(src, dst);

            m_Dtor(src);
        }

        std::free(old_array);
        m_Memory = new_array;
    }

    void Clear(){
        for(int i = 0; i<m_Size; i++){
            void *obj = operator[](i);
            m_Dtor(obj);
        }
        m_Size = 0;
    }

    void UnorderedRemove(void *ptr) {
        assert(InRange(ptr));

        size_t index = ((uint8_t*)m_Memory - (uint8_t*)ptr) / m_TypeSize;
        m_Dtor(operator[](index));
        MoveOrCopy(operator[](index + Size() - 1), operator[](index));
        m_Dtor(operator[](index + Size() - 1));
        m_Size--;
    }

    bool InRange(void* ptr) {
        return ptr >= m_Memory && ptr <= (uint8_t*)m_Memory + (m_Size - 1) * m_TypeSize;
    }

    void *operator[](size_t index){
        return (uint8_t*)m_Memory + m_TypeSize * index;
    }

    const void *operator[](size_t index)const{
        return (uint8_t*)m_Memory + m_TypeSize * index;
    }

    size_t Size()const{
        return m_Size;
    }

    size_t Capacity()const{
        return m_Capacity;
    }

private:
    void MoveOrCopy(void *src, void *dst){
        assert(m_MoveCtor || m_CopyCtor);

        if(m_MoveCtor)
            m_MoveCtor(src, dst);
        else
            m_CopyCtor(src, dst);
    }

};

template <typename BaseType>
class PolymorphList{
private:

    template <typename CastType, typename ListType>
    struct IteratorBase{
        ListType *List = nullptr;
        size_t Sublist = 0;

        IteratorBase& operator++() {
            if (Sublist == List->Size() - 1) {
                ++List;
                Sublist = 0;
            }else{
                ++Sublist;
            }
            return *this;
        }

        IteratorBase operator++(int) {
            Iterator tmp = *this;
            operator++();
            return tmp;
        }

        bool operator!=(const IteratorBase &other) {
            return !(*this == other);
        }

        bool operator==(const IteratorBase &other) {
            return List == other.List && Sublist == other.Sublist;
        }

        CastType& operator*() {
            return *(CastType*)(*List)[Sublist];
        }
        CastType* operator->() {
            return &operator*();
        }
    };

    using Iterator = IteratorBase<BaseType, UntypedList>;
    using ConstIterator = IteratorBase<const BaseType, const UntypedList>;

private:
    std::vector<std::type_index> m_Types;
    std::vector<UntypedList> m_Lists;
public:
    PolymorphList() = default;

    ~PolymorphList() {
        Clear();
    }

    template<typename Type, std::enable_if_t<std::is_copy_constructible_v<Type>, bool> = true>
    void Add(const Type &obj){
        static_assert(IsDerivedOrBase<Type>(), "Type should be derived or equal to BaseType");

        GetOrCreate<Type>().AddCopy(static_cast<const void *>(&obj));
    }

    template<typename Type, std::enable_if_t<std::is_move_constructible_v<Type>, bool> = true>
    void Add(std::remove_reference_t<std::remove_const_t<Type>> &&obj){
        static_assert(IsDerivedOrBase<Type>(), "Type should be derived or equal to BaseType");

        GetOrCreate<Type>().AddMove(static_cast<void *>(&obj));
    }

    template<typename Type>
    void Remove(Type *obj){
        static_assert(IsDerivedOrBase<Type>(), "Type should be derived or equal to BaseType");

        Get(typeid(*obj)).UnorderedRemove(obj);
    }

    template<typename Type>
    void RemoveByType(){
        static_assert(IsDerivedOrBase<Type>(), "Type should be derived or equal to BaseType");

        Get(typeid(Type)).Clear();
    }

    template <typename Functor>
    void ForEach(Functor f){
        for(auto &list: m_Lists){
            for(int i = 0; i<list.Size(); i++)
                f((BaseType*)list[i]);
        }
    }

    void Clear() {
        m_Types.clear();
        m_Lists.clear();
    }

    Iterator begin() {
        return {m_Lists.data(), 0};
    }

    Iterator end() {
        return {m_Lists.data() + m_Lists.size(), 0};
    }

    ConstIterator begin()const{
        return {m_Lists.data(), 0};
    }

    ConstIterator end()const{
        return {m_Lists.data() + m_Lists.size(), 0};
    }

private:
    template<typename Type>
    static constexpr bool IsDerivedOrBase(){
        using NonCVType = std::remove_reference<std::remove_cv<Type>::type>::type;
        return std::is_base_of<BaseType, NonCVType>::value || std::is_same<BaseType, NonCVType>::value;
    }

    template<typename Type>
    UntypedList& GetOrCreate() {
        size_t index = -1;

        for (int i = 0; i < m_Types.size(); i++) {
            if (m_Types[i] == std::type_index(typeid(Type))) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            index = m_Types.size();
            m_Types.emplace_back(std::type_index(typeid(Type)));
            m_Lists.emplace_back((std::remove_reference<std::remove_pointer<Type>::type>::type*)nullptr);
        }

        return m_Lists[index];
    }

    UntypedList& Get(std::type_index type_index) {
        return m_Lists[GetTypeIndex(type_index)];
    }

    size_t GetTypeIndex(std::type_index index) {
        return std::find(m_Types.begin(), m_Types.end(), index) - m_Types.begin();
    }

};

#endif //POLYMORPH_LIST_HPP