#pragma once
#include "api.h"
#include <stdexcept>
#include <vector>
#include <memory>


/// Template class for storing an array of element along with additional data  
template <typename Element, typename ContainerData>
class EXPORT_API ContainerBase {
public:
    /// Type alias for shared pointer to element
    using ElementPointer = std::shared_ptr<Element>;
    /// Type alias for an array of element pointers
    using ElementArray = std::vector<ElementPointer>;
    /// Type alias for a const iterator of element array
    using ElementArrayIterator = ElementArray::const_iterator;

protected:
    /// Constructs a container
    /// \param data data to be stored in the container
    ContainerBase(const ContainerData &data) {
        Update(data);
    }

public:
    /// Get element using an iterator
    /// \return pointer to element at specified position
    /// \throws std::out_of_range if iterator is invalid/out of range
    ElementPointer& At(ElementArrayIterator iter) {
        return At(AsIndex(iter));
    }

    /// Get element using an index
    /// \return reference to a pointer to element at specified position
    /// \throws std::out_of_range if index is out of range
    ElementPointer& At(int index) {
        if (!IsValid(index))
            throw std::out_of_range(invalidIndex);

        return m_array.at((uint32_t)index);
    }

    /// Get element array
    /// \return const reference to stored array
    const ElementArray &GetElementArray() const {
        return m_array;
    }

    /// Get container data
    /// \return copy of stored container data
    ContainerData GetData() const {
        return m_data;
    }

    /// Get container data
    /// \return const reference of stored container data
    const ContainerData& GetDataRef() const {
        return m_data;
    }

    /// Overwrites container's data
    /// \param data new data to store
    void Update(const ContainerData &data) {
        m_data = data;
    }

    /// Adds new element at the end of the array
    /// \param element new to be added
    void AddElement(const Element &element) {
        AddElement(std::make_shared<Element>(element));
    }

    /// Adds new element at the end of the array
    /// \param element pointer to the new element
    void AddElement(const ElementPointer &element) {
        m_array.push_back(element);
    }

    /// Removes element at specified location
    /// \throws std::out_of_range if iterator is invalid/out of range
    void RemoveElement(ElementArrayIterator it) {
        if (!IsValid(it))
            throw std::out_of_range(invalidIterator);
        m_array.erase(it);
    }

    /// Removes element at specified index
    /// \throws std::out_of_range if index is out of range
    void RemoveElement(int index) {
        if (!IsValid(index))
            throw std::out_of_range(invalidIndex);
        RemoveElement(m_array.begin() + index);
    }

    /// Inserts an element at specified index
    /// \param element new element to be stored
    /// \param index index at which new element will be inserted
    /// \warning index == -1 is special and it will insert element at the end of the array
    /// \warning index can be equal to the size of the array (it will insert the element at the end of the array)
    /// \throws std::out_of_range if index is out of range
    void InsertElement(const ElementPointer &element, int index) {
        if (index == -1 || index == m_array.size())
            m_array.push_back(element);
        else if (IsValid(index))
            m_array.insert(m_array.begin() + index, element);
        else
            throw std::out_of_range(invalidIndex);
    }

    /// Changes iterator to an index
    /// \throws std::out_of_range if iterator is invalid/out of range
    int AsIndex(ElementArrayIterator iter) const {
        if (!IsValid(iter))
            throw std::out_of_range(invalidIterator);
        return std::distance((ElementArrayIterator)m_array.begin(), iter);
    }

    /// Changes index to a iterator
    /// \throws std::out_of_range if index is out of range
    ElementArrayIterator AsIterator(int index) const {
        if (!IsValid(index))
            throw std::out_of_range(invalidIndex);
        return m_array.begin() + index;
    }

protected:
    /// Array of stored elements
    ElementArray m_array;

    /// Additional container data
    ContainerData m_data;
   
protected:
    /// Checks if the index is valid
    /// \return true if the index is valid
    bool IsValid(int index) const {
        return index >= 0 && index < m_array.size();
    }

    /// Checks if the iterator is valid
    /// \return true if the iterator is valid
    bool IsValid(ElementArrayIterator iter) const {
        return iter >= m_array.begin() && iter < m_array.end();
    }


    /// (TODO: move this to a header file with constant strings/values)
    inline static const char* invalidIterator = "Invalid iterator!";
    inline static const char* invalidIndex = "Invalid index!";
};